/*
 * Copyright (C) 2015 Christian Ehringfeld <c.ehringfeld@t-online.de>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */
#include "querybuilder.h"
#include "database.h"
#include <QMetaObject>
#include "entity.h"
#include <QRegularExpression>
#include "entityinstancefactory.h"
#include "entityhelper.h"

using namespace CuteEntityManager;

QueryBuilder::QueryBuilder(QSharedPointer<Schema> schema,
                           QSharedPointer<Database> database) {
    this->schema = schema;
    this->database = database;
    this->separator = " ";
}

QueryBuilder::~QueryBuilder() {
}

bool QueryBuilder::createTable(const QSharedPointer<Entity> &entity,
                               bool createRelationTables) const {
    bool rc = false;
    if (entity) {
        auto tableDefinition = this->generateTableDefinition(entity);
        QString tableName = entity->getTablename();
        this->schema->containsTable(tableName) ? rc = true : rc = false;
        if (!rc) {
            QSqlQuery q = this->database->getQuery(this->createTable(tableName,
                                                   tableDefinition));
            if (this->database->exec(q)) {
                if (createRelationTables) {
                    auto relTables = this->generateRelationTables(entity);
                    auto i = relTables.constBegin();
                    while (i != relTables.constEnd()) {
                        auto query = this->database->getQuery(this->createTable(i.key(),
                                                              i.value()));
                        this->database->exec(query);
                        ++i;
                    }
                }
                this->schema->getTableSchema(tableName);
                rc = true;
                if (rc) {
                    rc = this->createIndices(entity);
                }
            }
        }
    }
    return rc;
}

bool QueryBuilder::createIndices(const QSharedPointer<Entity> &entity) const {
    bool ok = true;
    QStringList queries = QStringList();
    QString superIndex = this->createFkSuperClass(entity.data());
    if (!superIndex.isEmpty()) {
        queries.append(superIndex);
    }
    queries.append(this->relationFks(entity));
    ok = this->database->transaction(queries);
    return ok;
}


QStringList QueryBuilder::relationFks(const QSharedPointer<Entity> &entity)
const {
    QStringList queries = QStringList();
    if (this->supportsForeignKeys()) {
        auto relations = EntityHelper::getNonInheritedRelations(entity.data());
        auto props = EntityHelper::getMetaProperties(entity.data());
        auto iterator = relations.constBegin();
        while (iterator != relations.constEnd()) {
            auto relation = iterator.value();
            if (relation.getMappedBy().isEmpty() && !relation.getCascadeType().isEmpty()) {
                QString update = relation.getCascadeType().contains(CascadeType::MERGE)
                                 || relation.getCascadeType().contains(CascadeType::ALL) ?
                                 this->getForeignKeyCascade(
                                     CASCADE) : this->getForeignKeyCascade(NO_ACTION);
                QString remove = relation.getCascadeType().contains(CascadeType::REMOVE)
                                 || relation.getCascadeType().contains(CascadeType::ALL) ?
                                 this->getForeignKeyCascade(
                                     CASCADE) : this->getForeignKeyCascade(DbForeignKeyCascade::SET_NULL);
                this->createRelationFK(queries, entity, relation,
                                       props.value(relation.getPropertyName()), update, remove);
            }
            ++iterator;
        }
    }
    return queries;
}

bool QueryBuilder::supportsForeignKeys() const {
    return true;
}

void QueryBuilder::createRelationFK(QStringList &queries,
                                    const QSharedPointer<Entity> &entity, const Relation &relation,
                                    const QMetaProperty &metaProperty, const QString &update,
                                    const QString &remove) const {
    auto ptr = QSharedPointer<Entity>
               (EntityInstanceFactory::createInstance(metaProperty.type()));
    if (ptr) {
        if (relation.getType() == RelationType::ONE_TO_ONE
                || relation.getType() == RelationType::MANY_TO_ONE) {
            QString indexName = this->generateIndexName(relation.getPropertyName(),
                                entity->getTablename(),
                                this->generateColumnNameID(relation.getPropertyName()),
                                ptr->getTablename(), true);
            queries.append(this->addForeignKey(indexName, entity->getTablename(),
                                               QStringList(this->generateColumnNameID(relation.getPropertyName())),
                                               ptr->getTablename(),
                                               QStringList(ptr->getPrimaryKey()), remove, update));

        } else if (relation.getType() == RelationType::MANY_TO_MANY) {
            QString tableName = this->generateManyToManyTableName(entity, ptr, relation);
            queries.append(this->createForeignKeyManyToMany(tableName, entity, update,
                           remove));
            queries.append(this->createForeignKeyManyToMany(tableName, ptr, update,
                           remove));
        }
    }
}

QString QueryBuilder::createForeignKeyManyToMany(const QString &tableName,
        const QSharedPointer<Entity> &entity, const QString &update,
        const QString &remove) const {
    QString fkColumn = this->generateManyToManyColumnName(entity);
    QString indexName = this->generateIndexName(fkColumn,
                        tableName, fkColumn,
                        entity->getTablename(), true);
    return this->addForeignKey(indexName, tableName, QStringList(fkColumn),
                               entity->getTablename(), QStringList(entity->getPrimaryKey()),
                               remove, update);
}

QString QueryBuilder::createTable(const QString &tableName,
                                  const QHash<QString, QString> &tableDefinition) const {
    return this->createTableQuery(tableName,
                                  tableDefinition);
}

QString QueryBuilder::createFkSuperClass(const Entity *e) const {
    QString r = "";
    auto superMetaObject = e->metaObject()->superClass();
    if (e->getInheritanceStrategy() == InheritanceStrategy::JOINED_TABLE
            && QString(superMetaObject->className()) !=
            this->entityClassname()) {
        Entity *superClass  = EntityInstanceFactory::createInstance(
                                  superMetaObject->className());
        if (superClass) {
            QString refColumn = superClass->getPrimaryKey();
            QString refTable = superClass->getTablename();
            r = this->addForeignKey(this->generateIndexName(e->getPrimaryKey(),
                                    e->getTablename(), refColumn, refTable, true), e->getTablename(),
                                    QStringList(e->getPrimaryKey()), refTable, QStringList(refColumn),
                                    this->getForeignKeyCascade(CASCADE),
                                    this->getForeignKeyCascade(CASCADE));
            delete superClass;
        }
    }
    return r;
}

QString QueryBuilder::createTableQuery(const QString &tableName,
                                       const QHash<QString, QString> &tableDefinition) const {
    bool first = true;
    QString s = "CREATE TABLE ";
    s.append(this->schema->quoteTableName(tableName).append(" ("));
    auto i = tableDefinition.constBegin();
    while (i != tableDefinition.constEnd()) {
        if (first) {
            first = false;
        } else {
            s.append(", ");
        }
        s.append(this->schema->quoteColumnName(i.key())).append(" " +
                this->getColumnType(
                    i.value()));
        ++i;
    }
    s.append(");");
    return s;
}

QString QueryBuilder::renameTable(QString tableName, QString newName) const {
    return "RENAME TABLE " + this->schema->quoteTableName(
               tableName) + " TO " +
           this->schema->quoteTableName(
               newName);
}

QString QueryBuilder::dropTable(QString tableName) const {
    return "DROP TABLE " + this->schema->quoteTableName(tableName);
}

QString QueryBuilder::truncateTable(QString tableName) const {
    return "TRUNCATE TABLE " + this->schema->quoteTableName(tableName);
}

QString QueryBuilder::addColumn(QString tableName, QString columnName,
                                QString columnType) const {
    return "ALTER TABLE " + this->schema->quoteTableName(
               tableName) + " ADD " +
           this->schema->quoteColumnName(
               columnName) + " " + this->getColumnType(columnType);
}

QString QueryBuilder::dropColumn(QString tableName, QString columName) const {
    return "ALTER TABLE " + this->schema->quoteTableName(
               tableName) + " DROP COLUMN " +
           this->schema->quoteColumnName(columName);
}

QString QueryBuilder::renameColumn(QString tableName, QString oldName,
                                   QString newName) const {
    return "ALTER TABLE " + this->schema->quoteTableName(
               tableName) + " RENAME COLUMN " +
           this->schema->quoteColumnName(oldName) + " TO " +
           this->schema->quoteColumnName(
               newName);
}

QString QueryBuilder::alterColumn(QString tableName, QString columnName,
                                  QString newType) const {
    return "ALTER TABLE " + this->schema->quoteTableName(
               tableName) + " CHANGE " +
           this->schema->quoteColumnName(columnName) + " " +
           this->schema->quoteColumnName(columnName) + this->getColumnType(newType);
}

QString QueryBuilder::addPrimaryKey(QString name, QString tableName,
                                    QStringList columns) const {
    return "ALTER TABLE " + this->schema->quoteTableName(
               tableName) + " ADD CONSTRAINT " +
           this->schema->quoteColumnName(name) + "PRIMARY KEY (" +
           this->buildColumns(columns) + " )";
}

QString QueryBuilder::dropPrimaryKey(QString name, QString tableName) const {
    return "ALTER TABLE " + this->schema->quoteTableName(
               tableName) + " DROP CONSTRAINT " +
           this->schema->quoteColumnName(name);
}

QString QueryBuilder::addForeignKey(QString name, QString tableName,
                                    QStringList columns,
                                    QString refTableName,
                                    QStringList refColumns, QString deleteConstraint,
                                    QString updateConstraint) const {
    QString r = "ALTER TABLE " + this->schema->quoteTableName(
                    tableName) + "ADD CONSTRAINT " +
                this->schema->quoteColumnName(name)
                + " FOREIGN KEY (" +  this->buildColumns(columns) + ")" + " REFERENCES " +
                this->schema->quoteTableName(
                    refTableName) +
                " (" + this->buildColumns(refColumns) + ")";
    if (!deleteConstraint.isEmpty()) {
        r.append(" ON DELETE " + deleteConstraint);
    }
    if (!updateConstraint.isEmpty()) {
        r.append(" ON UPDATE " + updateConstraint);
    }
    return r;
}

QString QueryBuilder::generateIndexName(const QString &name,
                                        const QString &table, const QString &refColumn, const QString &refTable,
                                        const bool fk) const {
    return QString(fk ? "fk" : "idx").append("_").append(name).append(table).append(
               refColumn).append(refTable);
}

QString QueryBuilder::generateColumnNameID(QString name) const {
    return name.append("_id");
}

QString QueryBuilder::getForeignKeyCascade(DbForeignKeyCascade cascade) const {
    QString r = "";
    switch (cascade) {
    case RESTRICT:
        r = "RESTRICT";
        break;
    case CASCADE:
        r = "CASCADE";
        break;
    case NO_ACTION:
        r = "NO ACTION";
        break;
    case SET_DEFAULT:
        r = "SET DEFAULT";
        break;
    case SET_NULL:
        r = "SET NULL";
        break;
    }
    return r;
}

QString QueryBuilder::dropForeignKey(QString name, QString tableName) const {
    return "ALTER TABLE " + this->schema->quoteTableName(
               tableName) + " DROP CONSTRAINT " +
           this->schema->quoteColumnName(name);
}

QString QueryBuilder::createIndex(QString name, QString tableName,
                                  QStringList columns,
                                  bool unique) const {
    QString s = (unique ? "CREATE UNIQUE INDEX " : "CREATE INDEX ") +
                this->schema->quoteTableName(
                    name) + " ON " + this->schema->quoteTableName(tableName) + " (";
    s.append(this->buildColumns(columns));
    s.append(");");
    return s;
}

QString QueryBuilder::dropIndex(QString name, QString tableName) const {
    return "DROP INDEX " + this->schema->quoteTableName(name) + " ON " +
           this->schema->quoteTableName(
               tableName);
}

QSharedPointer<Database> QueryBuilder::getDatabase() const {
    return this->database;
}

void QueryBuilder::setDatabase(const QSharedPointer<Database> &value) {
    database = value;
}

QString QueryBuilder::buildCreateQuery(QHash<QString, QVariant>::const_iterator
                                       i,
                                       QHash<QString, QVariant>::const_iterator end,
                                       QString &p1, QString &p2) const {
    bool first = true;
    while (i != end) {
        if (!first) {
            p1 += ",";
            p2 += ",";
        } else {
            first = false;
        }
        p1 += this->schema->quoteColumnName(i.key());
        p2 += this->placeHolder(i.key());
        ++i;
    }
    p1 += ")";
    p2 += ");";
    return p1 + p2;
}

QHash<QString, QString> QueryBuilder::generateTableDefinition(
    const QSharedPointer<Entity> &entity)
const {
    auto map = QHash<QString, QString>();
    auto o = entity->metaObject();
    auto superMetaObject = entity->metaObject()->superClass();
    auto superMetaObjectPropertyMap = EntityHelper::getSuperMetaProperties(
                                          entity.data());
    QHash<QString, Relation> relations = entity->getRelations();
    for (int var = 0; var < o->propertyCount(); ++var) {
        auto m = o->property(var);
        if ((!superMetaObjectPropertyMap.contains(QString(m.name()))
                || entity->getInheritanceStrategy() == InheritanceStrategy::PER_CLASS_TABLE)
                && m.name() != QString("objectName") && m.isReadable()
                && !entity->getTransientAttributes().contains(m.name())) {
            if (m.isEnumType()) {
                map.insert(m.name(), this->schema->getTypeMap()->value(
                               this->schema->TYPE_INTEGER));
            } else if (relations.contains(m.name())) {
                Relation r = relations.value(m.name());
                if (r.getType() == RelationType::MANY_TO_ONE
                        || (r.getType() == RelationType::ONE_TO_ONE
                            && r.getMappedBy().isEmpty())) {
                    map.insert(this->generateColumnNameID(QString(m.name())),
                               this->schema->TYPE_BIGINT);
                }
            } else if (entity->getBLOBColumns().contains(m.name())) {
                map.insert(m.name(), this->schema->getTypeMap()->value(
                               this->schema->TYPE_BINARY));
            } else {
                map.insert(m.name(), this->transformAbstractTypeToRealDbType(
                               this->transformTypeToAbstractDbType(
                                   m.typeName())));
            }
        }
    }
    if (QString(superMetaObject->className()) ==
            this->entityClassname()
            || entity->getInheritanceStrategy() == InheritanceStrategy::PER_CLASS_TABLE) {
        map.insert(entity->getPrimaryKey(), this->schema->TYPE_BIGPK);
    } else {
        map.insert(entity->getPrimaryKey(), this->schema->TYPE_BIGINT);
    }
    return map;
}

QString QueryBuilder::generateManyToManyTableName(const QSharedPointer<Entity>
        &firstEntity,
        const QSharedPointer<Entity> &secondEntity, const Relation &r) const {
    if (r.getMappedBy().isEmpty()) {
        return firstEntity->getTablename() + "_" + r.getPropertyName();
    } else {
        return secondEntity->getTablename() + "_" + r.getMappedBy();
    }
}

QHash<QString, QHash<QString, QString>> QueryBuilder::generateRelationTables(
        const QSharedPointer<Entity> &entity)
const {
    auto relations = QHash<QString, QHash<QString, QString>>();
    QHash<QString, Relation> m = entity->getRelations();
    auto props = EntityHelper::getMetaProperties(entity.data());
    for (auto i = m.begin(); i != m.end(); ++i) {
        Relation r = i.value();
        if (r.getType() == RelationType::MANY_TO_MANY && r.getMappedBy().isEmpty()) {
            QHash<QString, QString> h = QHash<QString, QString>();
            h.insert(entity->getPrimaryKey(), this->schema->TYPE_BIGPK);
            h.insert(this->generateManyToManyColumnName(entity),
                     this->schema->TYPE_BIGINT);
            auto meta = props.value(r.getPropertyName());
            QSharedPointer<Entity> ptr = QSharedPointer<Entity>
                                         (EntityInstanceFactory::createInstance(EntityInstanceFactory::extractEntityType(
                                                 QMetaType::typeName(meta.userType()))));
            h.insert(this->generateManyToManyColumnName(ptr),
                     this->schema->TYPE_BIGINT);
            relations.insert(this->generateManyToManyTableName(entity, ptr, r), h);
        }
    }
    return relations;
}


QString QueryBuilder::transformTypeToAbstractDbType(QString typeName) const {
    auto m = this->schema->getAbstractTypeMap();
    if (m->contains(typeName)) {
        return m->value(typeName);
    }
    for (auto i = m->begin(); i != m->end(); ++i) {
        if (i.key().contains(typeName)) {
            return i.value();
        }
    }
    return this->schema->TYPE_TEXT;
}

QString QueryBuilder::transformAbstractTypeToRealDbType(
    QString typeName) const {
    return this->schema->getTypeMap()->value(typeName);
}

QString QueryBuilder::getColumnType(const QString &type) const {
    /**
      * @WARNING
      */
    auto tMap = this->schema->getTypeMap();
    if (tMap->contains(type)) {
        return this->transformAbstractTypeToRealDbType(type);
    }
    //cant believe that this could work in Qt
    //https://github.com/yiisoft/yii2/blob/master/framework/db/QueryBuilder.php
    QRegularExpression reg = QRegularExpression(
                                 QRegularExpression::escape("/^(\\w+)\\((.+?)\\)(.*)$/"));
    reg.optimize();
    QRegularExpressionMatchIterator i = reg.globalMatch(type, 0,
                                        QRegularExpression::PartialPreferFirstMatch);
    short s = 0;
    bool ok = false;
    QString before = "";
    while (i.hasNext() && s < 2) {
        before = i.next().captured();
        if (tMap->contains(before)) {
            ok = true;
        }
        if (ok) {
            return before.replace(QRegularExpression::escape("/\\(.+\\)/"),
                                  "(" + i.next().captured() + ")");
        }
        s++;
    }
    reg = QRegularExpression(QRegularExpression::escape("/^(\\w+)\\s+/"));
    i = reg.globalMatch(type, 0, QRegularExpression::PartialPreferFirstMatch);
    if (i.hasNext()) {
        return before.replace(QRegularExpression::escape("/^w+/"), i.next().captured());
    }
    return type;
}

/**
 * @brief QueryBuilder::find
 * @param id
 * @param tableName
 * @return
 */
QSqlQuery QueryBuilder::find(const qint64 &id, const QString &tableName) const {
    QString pk = "id";
    QSqlQuery q = this->database->getQuery(this->selectBase(QStringList(
            tableName)) + " WHERE " + this->schema->quoteColumnName(
                    pk) + " = " + this->placeHolder(pk) + " LIMIT 1;");
    this->bindValue(pk, id, q);
    return q;
}

QString QueryBuilder::selectBase(const QStringList &tables,
                                 const QStringList &columns) const {
    QString r = "SELECT ";
    if (columns.isEmpty()) {
        r.append("*");
    } else {
        for (int var = 0; var < columns.size(); ++var) {
            if (var != 0) {
                r.append(" ");
            }
            r.append(this->schema->quoteColumnName(columns.at(var)));
        }
    }
    r.append(" FROM");
    for (int var = 0; var < tables.size(); ++var) {
        r.append(" ");
        r.append(this->schema->quoteTableName(tables.at(var)));
    }
    return r;
}

QSqlQuery QueryBuilder::find(const qint64 &id,
                             const QSharedPointer<Entity> &entity, qint64 offset, QString pk) const {
    QSqlQuery q = this->database->getQuery(this->selectBase(QStringList(
            entity->getTablename())) + this->joinSuperClasses(
                    entity) + " WHERE " + this->schema->quoteColumnName(entity->getTablename() + "."
                                           + pk) + "= " + this->placeHolder(pk) + this->limit(1, offset));
    this->bindValue(pk, id, q);
    return q;
}

QSqlQuery QueryBuilder::findAll(const QSharedPointer<Entity> &entity,
                                const qint64 limit, qint64 offset) {
    return this->database->getQuery(this->selectBase(QStringList(
                                        entity->getTablename())) + " " + this->joinSuperClasses(
                                        entity) + this->limit(limit, offset) + ";");
}

/**
 * @brief QueryBuilder::findByAttributes
 * @param m
 * @param tableName
 * @param ignoreID
 * @return
 */
QSqlQuery QueryBuilder::findByAttributes(const QHash<QString, QVariant> &m,
        const QString &tableName,
        const bool &ignoreID, const qint64 limit, const qint64 offset) const {
    QSqlQuery q = this->database->getQuery(this->selectBase(QStringList(
            tableName)) + this->where(m, this->andKeyword(), ignoreID) + this->limit(limit,
                                           offset));
    this->bindValues(m, q, ignoreID);
    return q;
}

QSqlQuery QueryBuilder::findByAttributes(const QSharedPointer<Entity> &e,
        bool ignoreID,
        const qint64 limit,
        const qint64 offset) {
    QHash<QString, QVariant> values = EntityHelper::getEntityAttributes(
                                          EntityHelper::getMetaProperties(e.data()), e);
    return this->findByAttributes(values, e->getTablename(), ignoreID, limit,
                                  offset);
}

QSqlQuery QueryBuilder::findAll(const QString &tableName) const {
    return this->database->getQuery(this->selectBase(QStringList(tableName)) + ";");
}

QList<QSqlQuery> QueryBuilder::remove(const QSharedPointer<Entity> &entity)
const {
    QList<QSqlQuery> queries = QList<QSqlQuery>();
    queries.append(this->remove(entity->getTablename(),
                                entity->getProperty(entity->getPrimaryKey()).toLongLong()));
    if (entity->getInheritanceStrategy() != InheritanceStrategy::PER_CLASS_TABLE
            && entity->isInheritanceCascaded()) {
        auto classes = EntityHelper::superClasses(entity.data(), true);
        for (int var = 0; var < classes.size(); ++var) {
            auto item = classes.at(var);
            auto instance = EntityInstanceFactory::createInstance(item->className());
            if (instance) {
                queries.append(this->remove(instance->getTablename(),
                                            entity->getProperty(entity->getPrimaryKey()).toLongLong()));
                delete instance;
                instance = 0;
            }
        }
    }
    return queries;
}


QSqlQuery QueryBuilder::remove(const QString &tableName,
                               const qint64 &id, const QString &primaryKey) const {
    QSqlQuery q = this->database->getQuery("DELETE FROM " +
                                           this->schema->quoteTableName(
                                                   tableName) + " WHERE " +
                                           this->schema->quoteColumnName(primaryKey) + "=" + this->placeHolder(
                                                   primaryKey) + ";");
    this->bindValue(primaryKey, id, q);
    return q;
}

QSqlQuery QueryBuilder::findId(const QSharedPointer<Entity> &entity) const {
    QHash<QString, QVariant> values = EntityHelper::getEntityAttributes(
                                          EntityHelper::getMetaProperties(entity.data()),
                                          entity);
    QSqlQuery q = this->database->getQuery(this->selectBase(QStringList(
            entity->getTablename()),
                                           QStringList(entity->getPrimaryKey())) + this->where(values,
                                                   this->andKeyword(), true) + " LIMIT 1");
    this->bindValues(values, q);
    return q;
}

QSqlQuery QueryBuilder::count(const QSharedPointer<Entity> &entity,
                              bool ignoreID) const {
    QHash<QString, QVariant> values = EntityHelper::getEntityAttributes(
                                          EntityHelper::getMetaProperties(entity.data()),
                                          entity);
    QSqlQuery q = this->database->getQuery(this->selectBase(QStringList(
            entity->getTablename()),
                                           QStringList(this->countFunction())) + this->where(
                                                   values, this->andKeyword(), ignoreID));
    this->bindValues(values, q, ignoreID);
    return q;
}

QSqlQuery QueryBuilder::count(const QString &tableName) const {
    QSqlQuery q = this->database->getQuery(this->selectBase(QStringList(
            tableName), QStringList(this->countFunction())) + ";");
    return q;
}

QList<QSqlQuery> QueryBuilder::merge(const QSharedPointer<Entity> &entity)
const {
    return this->createOrMerge(entity, false);
}


QList<QSqlQuery> QueryBuilder::createOrMerge(const QSharedPointer<Entity>
        &entity, bool insert) const {
    const QList<ClassAttributes> attrs = this->inheritedAttributes(entity);
    auto queries = QList<QSqlQuery>();
    bool first = true;
    for (int var = 0; var < attrs.size(); ++var) {
        auto attr = attrs.at(var);
        auto attrHash = attr.getAttributes();
        queries.append(insert ? this->insert(attr.getName(), attrHash,
                                             attr.getPk(), !first) : this->update(attr.getName(), attrHash, attr.getPk()));
        if (first) {
            first = false;
        }
    }
    return queries;
}

QList<QSqlQuery> QueryBuilder::create(const QSharedPointer<Entity> &entity)
const {
    return this->createOrMerge(entity, true);
}

QSqlQuery QueryBuilder::removeAll(const QString &tableName) const {
    return this->database->getQuery(this->truncateTable(tableName));
}

QSqlQuery QueryBuilder::insert(const QString &tableName,
                               QHash<QString, QVariant> &attributes, const QString &primaryKey,
                               bool withId) const {
    if (!withId) {
        attributes.remove(primaryKey);
    }
    QSqlQuery q = this->database->getQuery();
    QString p1 = "INSERT INTO " + this->schema->quoteTableName(
                     tableName) + "(";
    QString p2 = "VALUES(";
    if (!attributes.isEmpty()) {
        q.prepare(this->buildCreateQuery(attributes.constBegin(), attributes.constEnd(),
                                         p1, p2));
    }
    this->bindValues(attributes, q);
    return q;
}

QSqlQuery QueryBuilder::update(const QString &tableName,
                               QHash<QString, QVariant> &attributes, const QString &primaryKey) const {
    QSqlQuery q = this->database->getQuery("UPDATE " + this->schema->quoteTableName(
            tableName) + " SET " + this->attributes(attributes) + " " + this->whereKeyword()
                                           + " " +
                                           this->schema->quoteColumnName(primaryKey) + " = " + this->placeHolder(
                                                   primaryKey) + ";");
    this->bindValues(attributes, q);
    return q;
}


QSqlQuery QueryBuilder::oneToMany(const QString &tableName,
                                  const QString &attribute,
                                  const qint64 &id,
                                  const qint64 &limit) {
    QHash<QString, QVariant> values = QHash<QString, QVariant>();
    values.insert(attribute, id);
    return this->findByAttributes(values, tableName, false, limit);
}

QSqlQuery QueryBuilder::manyToMany(const QString &tableName,
                                   const QString &attribute,
                                   const qint64 &id) {
    QSqlQuery q = this->database->getQuery();
    QString sql = this->selectBase(QStringList(tableName), QStringList("*"));
    QString pk = "id";
    sql += " " + this->whereKeyword() + " ";
    sql += this->schema->quoteColumnName(
               attribute);
    sql += " = " + this->placeHolder(pk) + ";";
    q.prepare(sql);
    this->bindValue(pk, id, q);
    return q;
}

QSqlQuery QueryBuilder::manyToManyDelete(const QString &tableName,
        const QString &attribute, const qint64 &id) {
    QSqlQuery q = this->database->getQuery();
    QString pkCol = "id";
    QString sql = "DELETE FROM " + this->schema->quoteTableName(
                      tableName) + " WHERE " + this->schema->quoteColumnName(
                      attribute) + "=" + this->placeHolder(pkCol);
    q.prepare(sql);
    this->bindValue(pkCol, id, q);
    return q;
}

QSqlQuery QueryBuilder::manyToManyInsert(const QString &tableName,
        const QString &col1, const QString &col2) const {
    QSqlQuery q = this->database->getQuery();
    QString sql = "INSERT INTO " + this->schema->quoteTableName(
                      tableName) + "(" + col1 + "," + col2 + ")"
                  + "VALUES(?, ?);";
    q.prepare(sql);
    return q;
}

QString QueryBuilder::superClassColumnName(const QMetaObject *&superMeta)
const {
    return QString(superMeta->className()).toLower();
}

QString QueryBuilder::addWildcard(QVariant var, JokerPosition jp,
                                  QChar jokerChar) const {
    QString val = var.toString();
    if (!val.isEmpty())  {
        switch (jp) {
        case JokerPosition::BEHIND:
            val += jokerChar;
            break;
        case JokerPosition::BOTH:
            val = jokerChar + val + jokerChar;
            break;
        case  JokerPosition::FRONT:
            val = jokerChar + val;
            break;
        case JokerPosition::NONE:
            break;
        default:
            break;
        }
    }
    return val;
}

QString QueryBuilder::joinSuperClasses(const QSharedPointer<Entity> &entity)
const {
    auto classes = EntityHelper::superClasses(entity.data(), true);
    QString joined = "";
    Entity *e = 0;
    for (int var = 0; var < classes.size(); ++var) {
        auto metaObject = classes.at(var);
        e = EntityInstanceFactory::createInstance(metaObject->className());
        if (e) {
            joined.append(" ");
            joined.append(this->leftJoin(e->getTablename(), entity->getTablename(),
                                         e->getPrimaryKey(), entity->getPrimaryKey()));
        }
        delete e;
        e = 0;
    }
    return joined;
}

QString QueryBuilder::countFunction(const QString &distinctColumn) const {
    return QString(this->countKeyword() + "(" + (distinctColumn.isEmpty() ? "*" :
                   (this->distinct() +
                    this->schema->quoteColumnName(distinctColumn))) + ")");
}

QString QueryBuilder::distinct() const {
    return "DISTINCT";
}

QString QueryBuilder::notKeyword() const {
    return "NOT";
}

QString QueryBuilder::between() const {
    return "BETWEEN";
}

QString QueryBuilder::andKeyword() const {
    return "AND";
}

QString QueryBuilder::orKeyword() const {
    return "OR";
}

QString QueryBuilder::inKeyword() const {
    return "IN";
}

QString QueryBuilder::whereKeyword() const {
    return "WHERE";
}

QString QueryBuilder::countKeyword() const {
    return "COUNT";
}

Expression QueryBuilder::inFunction(QString column,
                                    QList<QVariant> values, bool notOp) {
    QString condition = "";
    Expression exp = Expression();
    if (!values.isEmpty()) {
        bool first = true;
        condition = this->schema->quoteColumnName(column) + " " + this->appendNot(
                        notOp) + this->inKeyword() +
                    " (";
        for (int var = 0; var < values.size(); ++var) {
            if (first) {
                first = false;
            } else {
                condition += ", ";
            }
            QString paramName = column + "_in" + var;
            condition += this->placeHolder(paramName);
            exp.addParam(paramName, values.at(var));
        }
        condition += ")";
    }
    exp.setExpression(condition);
    return exp;
}

QString QueryBuilder::between(QString colName, QString valName1,
                              QString valName2, bool notOp) {
    return "(" + this->schema->quoteColumnName(colName) + (notOp ? (" " +
            this->notKeyword() + " ") : " ") + this->between() +
           " " + this->placeHolder(valName1) + " " + this->andKeyword() + " " +
           this->placeHolder(valName2) + ")";
}

QString QueryBuilder::likeKeyword() const {
    return "LIKE";
}

QString QueryBuilder::limitKeyword() const {
    return "LIMIT";
}

QString QueryBuilder::offsetKeyword() const {
    return "OFFSET";
}

QString QueryBuilder::appendNot(bool notOp) {
    return (notOp ? (this->notKeyword() + " ") : "");
}

QString QueryBuilder::entityClassname() const {
    return QString("CuteEntityManager::Entity");
}

QStringList QueryBuilder::quoteTableNames(const QStringList &tables) {
    QStringList r = QStringList();
    for (int i = 0; i < tables.size(); ++i) {
        r.append(this->schema->quoteTableName(tables.at(i)));
    }
    return r;
}

QString QueryBuilder::getSeparator() const {
    return separator;
}

void QueryBuilder::setSeparator(const QString &value) {
    separator = value;
}


QString QueryBuilder::limit(const quint64 &limit, const quint64 &offset) const {
    QString s = "";
    if (limit > 0) {
        s.append(" " + this->limitKeyword() + " ").append(QString::number(limit));
    }
    if (offset > 0) {
        s.append(" " + this->offsetKeyword() + " ").append(QString::number(offset));
    }
    return s;
}

QString QueryBuilder::generateManyToManyColumnName(const QSharedPointer<Entity>
        &entity) const {
    if (entity) {
        return this->generateColumnNameID(entity->getTablename());
    }
    qDebug() << "Entity is empty!";
    return "";
}

QSqlQuery QueryBuilder::getQuery() const {
    return this->database->getQuery();
}


QHash<QString, QVariant> QueryBuilder::saveAttributes(const
        QSharedPointer<Entity> &entity, QHash<QString, QMetaProperty> props,
        QHash<QString, Relation> relations) const {
    if (props.isEmpty()) {
        props = EntityHelper::getMetaProperties(entity.data());
    }
    auto values = EntityHelper::getEntityAttributes(props, entity);
    auto relValues = this->getManyToOneAttributes(props, entity, relations);
    auto iterator = relValues.constBegin();
    while (iterator != relValues.constEnd()) {
        values.insert(iterator.key(), iterator.value());
        ++iterator;
    }
    return values;
}

QHash<QString, QMetaProperty> QueryBuilder::processProperties(
    const QSharedPointer<Entity> &e,
    QHash<QString, QMetaProperty> &usedProperties) const {
    auto properties = EntityHelper::getMetaProperties(e.data());
    QMutableHashIterator<QString, QMetaProperty> i(properties);
    while (i.hasNext()) {
        i.next();
        if (usedProperties.contains(i.key()) && i.key() != e->getPrimaryKey()) {
            properties.remove(i.key());
        } else {
            usedProperties.insert(i.key(), i.value());
        }

    }
    return properties;
}

QHash<QString, Relation> QueryBuilder::processRelations(
    const QSharedPointer<Entity> &e,
    QHash<QString, Relation> &usedRelations) const {
    auto relations = e->getRelations();
    auto i = QMutableHashIterator<QString, Relation>(relations);
    while (i.hasNext()) {
        i.next();
        if (usedRelations.contains(i.key())) {
            relations.remove(i.key());
        } else {
            usedRelations.insert(i.key(), i.value());
        }
    }
    return relations;
}

QList<QueryBuilder::ClassAttributes> QueryBuilder::inheritedAttributes(
    const QSharedPointer<Entity> &entity) const {
    auto list = QList<QueryBuilder::ClassAttributes>();
    if (entity->getInheritanceStrategy() == InheritanceStrategy::JOINED_TABLE) {
        auto classes = QList<const QMetaObject *>();
        classes.append(entity->metaObject());
        classes.append(EntityHelper::superClasses(entity.data(), true));
        auto usedProperties = QHash<QString, QMetaProperty>();
        auto usedRelations = QHash<QString, Relation>();
        QSharedPointer<Entity> e;
        for (int var = classes.size() - 1; var >= 0; --var) {
            auto metaObj = classes.at(var);
            e = QSharedPointer<Entity>(EntityInstanceFactory::createInstance(
                                           metaObj));
            if (e) {
                list.append(QueryBuilder::ClassAttributes(e->getTablename(),
                            this->saveAttributes(entity, this->processProperties(e, usedProperties),
                                                 this->processRelations(e, usedRelations)), e->getPrimaryKey()));
            } else {
                qDebug() << "Instance of " << metaObj->className() << " could not be created";
                break;
            }
        }
    } else {
        list.append(QueryBuilder::ClassAttributes(entity->getTablename(),
                    this->saveAttributes(entity), entity->getPrimaryKey()));
    }
    return list;
}

QString QueryBuilder::leftJoin(const QString &foreignTable,
                               const QString &tableName, const QString &foreignKey,
                               const QString &primaryKey) const {
    return "LEFT JOIN " + this->schema->quoteTableName(
               foreignTable) + " ON " +
           this->schema->quoteColumnName(foreignTable + "." + primaryKey) + "=" +
           this->schema->quoteColumnName(
               tableName + "." + foreignKey);
}

QHash<QString, QVariant> QueryBuilder::getManyToOneAttributes(
    QHash<QString, QMetaProperty>
    props,
    const QSharedPointer<Entity> &entity,
    QHash<QString, Relation> relations) const {
    auto map = QHash<QString, QVariant>();
    if (relations.isEmpty()) {
        relations = entity->getRelations();
    }
    auto i = relations.constBegin();
    while (i != relations.constEnd()) {
        Relation r = i.value();
        if ((r.getType() == RelationType::MANY_TO_ONE && props.contains(i.key()))
                || (r.getType() == RelationType::ONE_TO_ONE && r.getMappedBy().isEmpty())) {
            auto v = props.value(i.key()).read(entity.data());
            QSharedPointer<Entity> e = EntityInstanceFactory::castQVariant(v);
            if (e) {
                this->insertRelationId(e.data(), map, i.key());
            }
        }
        ++i;
    }
    return map;
}

void QueryBuilder::insertRelationId(const Entity *e,
                                    QHash<QString, QVariant> &map,
                                    QString relName) const {
    if (e && e->getProperty(e->getPrimaryKey()).toLongLong() > -1) {
        map.insert(this->generateColumnNameID(relName),
                   e->getProperty(e->getPrimaryKey()));
    }
}

QString QueryBuilder::buildColumns(const QStringList &columns) const {
    QString r = "";
    bool first = true;
    for (int var = 0; var < columns.size(); ++var) {
        if (!first) {
            r.append(",");
        } else {
            first = false;
        }
        r.append(columns.at(var));
    }
    return r;
}

void QueryBuilder::bindValues(const QHash<QString, QVariant> &h, QSqlQuery &q,
                              bool ignoreID, const QString &primaryKey) const {
    QHash<QString, QVariant>::const_iterator i = h.constBegin();
    while (i != h.constEnd()) {
        if ((!ignoreID || (ignoreID && !(i.key() == primaryKey)))
                && !i.value().isNull()) {
            this->bindValue(i.key(), i.value(), q);
        }
        ++i;
    }
}

void QueryBuilder::bindValue(const QString &key, const QVariant &value,
                             QSqlQuery &q) const {
    q.bindValue(this->placeHolder(key), value);
}

QString QueryBuilder::placeHolder(const QString &key) const {
    return QString(":" + key);
}

QString QueryBuilder::where(const QHash<QString, QVariant> &m,
                            const QString &conjunction,
                            bool ignoreID, const QString &primaryKey, bool withKeyword) const {
    if (m.size() == 0 || (ignoreID && m.contains(primaryKey) && m.size() == 1)) {
        return "";
    }
    return (withKeyword ? " WHERE " : "") + this->attributes(m, conjunction,
            ignoreID, primaryKey);
}

QString QueryBuilder::attributes(const QHash<QString, QVariant> &m,
                                 const QString &conjunction,
                                 bool ignoreID, const QString &primaryKey) const {
    QString rc = "";
    if (!m.isEmpty()) {
        QHash<QString, QVariant>::const_iterator i = m.constBegin();
        while (i != m.constEnd()) {
            if ((!ignoreID || (ignoreID && !(i.key() == primaryKey)))
                    && !i.value().isNull()) {
                if (!(rc == "")) {
                    rc += " " + conjunction + " ";
                }
                rc += this->schema->quoteColumnName(i.key()) + "=" + this->placeHolder(i.key());
            }
            ++i;
        }
    }
    return rc;
}

QSharedPointer<Schema> QueryBuilder::getSchema() const {
    return schema;
}

void QueryBuilder::setSchema(const QSharedPointer<Schema> &value) {
    schema = value;
}

QueryBuilder::ClassAttributes::ClassAttributes(const QString name,
        const QHash<QString, QVariant> attributes, QString pk) {
    this->name = name;
    this->attributes = attributes;
    this->pk = pk;
}

QString QueryBuilder::ClassAttributes::getName() const {
    return name;
}

void QueryBuilder::ClassAttributes::setName(const QString &value) {
    name = value;
}

QHash<QString, QVariant> QueryBuilder::ClassAttributes::getAttributes() const {
    return attributes;
}

void QueryBuilder::ClassAttributes::setAttributes(const QHash<QString, QVariant>
        &value) {
    attributes = value;
}

QString QueryBuilder::ClassAttributes::getPk() const {
    return pk;
}

void QueryBuilder::ClassAttributes::setPk(const QString &value) {
    pk = value;
}

Expression QueryBuilder::andOperator(QHash<QString, QVariant> conditions) {
    bool first = true;
    Expression exp = Expression();
    QString condition = "";
    for (auto var = conditions.constBegin(); var != conditions.constEnd(); ++var) {
        if (first) {
            first = false;
        } else {
            condition += " " + this->andKeyword() + " ";
        }
        condition += this->schema->quoteColumnName(var.key()) + " = " +
                     this->placeHolder(var.key());
        exp.addParam(var.key(), var.value());
    }
    exp.setExpression(condition);
    return exp;
}

Expression QueryBuilder::arbitraryOperator(QString op, QString column,
        QVariant value) {
    Expression exp = Expression(this->schema->quoteColumnName(
                                    column) + " " + op + " " +
                                this->placeHolder(column));
    exp.addParam(column, value);
    return exp;

}

Expression QueryBuilder::isNull(QString column) {
    return Expression(this->schema->quoteColumnName(column) + " IS NULL");
}

Expression QueryBuilder::isNotNull(QString column) {
    return Expression(this->schema->quoteColumnName(column) + " IS " +
                      this->notKeyword() + " NULL");
}

Expression QueryBuilder::plainOr() {
    return Expression(this->orKeyword());
}

Expression QueryBuilder::plainNor() {
    return Expression(this->notKeyword() + " " + this->orKeyword());
}

Expression QueryBuilder::plainAnd() {
    return Expression(this->andKeyword());
}

Expression QueryBuilder::plainNand() {
    return Expression(this->notKeyword() + " " +  this->andKeyword());
}

Expression QueryBuilder::like(QString column, QVariant value,
                              JokerPosition jp, QChar wildcard) {
    return Expression(this->arbitraryOperator(this->likeKeyword(), column,
                      this->addWildcard(value, jp, wildcard)));
}

Expression QueryBuilder::like(QHash<QString, QVariant> conditions,
                              QString conjunction,
                              JokerPosition jp, QChar wildcard) {
    Expression exp = Expression();
    QString condition = "(";
    if (!conditions.isEmpty()) {
        bool first = true;
        for (auto i = conditions.constBegin(); i != conditions.constEnd(); ++i) {
            if (first) {
                first = false;
            } else {
                condition += conjunction;
            }
            condition += this->schema->quoteColumnName(i.key()) + " " + this->likeKeyword()
                         + " " +
                         this->placeHolder(i.key());
            QString newVal = this->addWildcard(i.value(), jp, wildcard);
            exp.addParam(i.key(), newVal.isEmpty() ? i.value() : newVal);
        }
        condition += ")";
        exp.setExpression(condition);
    }
    return exp;
}

Expression QueryBuilder::where(QString column, QVariant value) {
    QString placeholder = column + "_where";
    Expression exp = Expression(this->schema->quoteColumnName(column) + "=" +
                                this->placeHolder(placeholder));
    exp.addParam(placeholder, value);
    return exp;
}

Expression QueryBuilder::where(QHash<QString, QVariant> conditions,
                               QString conjunction) {
    Expression exp = Expression(this->where(conditions, conjunction, false, "id",
                                            false));
    for (auto i = conditions.constBegin(); i != conditions.constEnd(); ++i) {
        exp.addParam(i.key(), i.value());
    }
    return exp;
}

Expression QueryBuilder::where(QString condition,
                               QHash<QString, QVariant> values) {
    Expression exp = Expression(condition);
    for (auto i = values.constBegin(); i != values.constEnd(); ++i) {
        exp.addParam(i.key(), i.value());
    }
    return exp;
}

Expression QueryBuilder::between(QString column, QVariant firstValue,
                                 QVariant secondValue) {
    QString firstPh = column + "_bet1";
    QString secondPh = column + "_bet2";
    return this->appendCondition(firstPh, secondPh, firstValue, secondValue,
                                 this->between(column, firstPh, secondPh));
}

Expression QueryBuilder::notBetween(QString column, QVariant firstValue,
                                    QVariant secondValue) {
    QString firstPh = column + "_nbet1";
    QString secondPh = column + "_nbet2";
    return this->appendCondition(firstPh, secondPh, firstValue, secondValue,
                                 this->between(column, firstPh, secondPh, true));
}


Expression QueryBuilder::appendCondition(QString ph1, QString ph2,
        QVariant val1, QVariant val2, QString condition) {
    Expression exp = Expression(condition);
    exp.addParam(ph1, val1);
    exp.addParam(ph2, val2);
    return exp;
}

Expression QueryBuilder::in(QString column, QList<QVariant> values) {
    return this->inFunction(column, values);
}

Expression QueryBuilder::notIn(QString column, QList<QVariant> values) {
    return this->inFunction(column, values, true);
}

Expression QueryBuilder::orOperator(
    QHash<QString, QVariant> conditions, bool like) {
    Expression exp = Expression();
    if (!conditions.isEmpty()) {
        QString condition = "(";
        bool first = true;
        for (auto i = conditions.constBegin(); i != conditions.constEnd(); ++i) {
            if (first) {
                first = false;
            } else {
                condition += " " + this->orKeyword() + " ";
            }
            condition += this->schema->quoteColumnName(i.key()) + (like ? " " +
                         this->likeKeyword() + " " : "=") +
                         this->placeHolder(i.key());
            exp.addParam(i.key(), i.value());
        }
        condition += ")";
        exp.setExpression(condition);
    }
    return exp;
}

QString QueryBuilder::where(const QSharedPointer<Entity> &entity,
                            QString conjunction,
                            bool ignoreID) const {
    return this->where(EntityHelper::getEntityAttributes(
                           EntityHelper::getMetaProperties(
                               entity.data()),
                           entity),
                       conjunction, ignoreID, entity->getPrimaryKey());
}
