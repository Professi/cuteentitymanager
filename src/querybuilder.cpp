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

using namespace CuteEntityManager;

QueryBuilder::QueryBuilder(QSharedPointer<Schema> schema,
                           QSharedPointer<Database> database) {
    this->schema = schema;
    this->database = database;
}

QueryBuilder::~QueryBuilder() {
}

bool QueryBuilder::createTable(const QSharedPointer<Entity> &entity) const {
    bool rc = false;
    if (entity.data()) {
        auto tableDefinition = this->generateTableDefinition(entity);
        QString tableName = entity.data()->getTablename();
        this->schema.data()->containsTable(tableName) ? rc = true : rc = false;
        if (!rc) {
            QSqlQuery q = this->database.data()->getQuery(this->createTable(tableName,
                          tableDefinition));
            if (this->database.data()->transaction(q)) {
                this->schema.data()->getTableSchema(tableName);
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
    Entity *e = entity.data();
    bool ok = true;
    QStringList queries = QStringList();
    QString superIndex = this->createFkSuperClass(e);
    if (!superIndex.isEmpty()) {
        queries.append(superIndex);
    }
    queries.append(this->relationFks(entity));
    ok = this->database.data()->transaction(queries);
    return ok;
}


QStringList QueryBuilder::relationFks(const QSharedPointer<Entity> &entity)
const {
    QStringList queries = QStringList();
    if (this->supportsForeignKeys()) {
        auto relations = entity.data()->getNonInheritedRelations();
        auto props = entity.data()->getMetaProperties();
        auto iterator = relations.constBegin();
        while (iterator != relations.constEnd()) {
            auto relation = iterator.value();
            if (relation.getMappedBy().isEmpty() && !relation.getCascadeType().isEmpty()) {
                QString update = relation.getCascadeType().contains(MERGE)
                                 || relation.getCascadeType().contains(ALL) ?  this->getForeignKeyCascade(
                                     CASCADE) : this->getForeignKeyCascade(NO_ACTION);
                QString remove = relation.getCascadeType().contains(REMOVE)
                                 || relation.getCascadeType().contains(ALL) ?  this->getForeignKeyCascade(
                                     CASCADE) : this->getForeignKeyCascade(SET_NULL);
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
    QSharedPointer<Entity> ptr = QSharedPointer<Entity>
                                 (EntityInstanceFactory::createInstance(metaProperty.type()));
    if (ptr.data()) {
        if (relation.getType() == ONE_TO_ONE || relation.getType() == MANY_TO_ONE) {
            QString indexName = this->generateIndexName(relation.getPropertyName(),
                                entity.data()->getTablename(),
                                this->generateColumnNameID(relation.getPropertyName()),
                                ptr.data()->getTablename(), true);
            queries.append(this->addForeignKey(indexName, entity.data()->getTablename(),
                                               QStringList(this->generateColumnNameID(relation.getPropertyName())),
                                               ptr.data()->getTablename(),
                                               QStringList(ptr.data()->getPrimaryKey()), remove, update));

        } else if (relation.getType() == MANY_TO_MANY) {
            QString tableName = this->generateManyToManyTableName(entity, ptr);
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
                        entity.data()->getTablename(), true);
    return this->addForeignKey(indexName, tableName, QStringList(fkColumn),
                               entity.data()->getTablename(), QStringList(entity.data()->getPrimaryKey()),
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
    if (e->getInheritanceStrategy() == JOINED_TABLE
            && QString(superMetaObject->className()) !=
            QString("CuteEntityManager::Entity")) {
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
    s.append(this->schema.data()->quoteTableName(tableName).append(" (\n"));
    auto i = tableDefinition.constBegin();
    while (i != tableDefinition.constEnd()) {
        if (first) {
            first = false;
        } else {
            s.append(", ");
        }
        s.append(this->schema.data()->quoteColumnName(i.key())).append(" " +
                this->getColumnType(
                    i.value()));
        ++i;
    }
    s.append("\n);");
    return s;
}

QString QueryBuilder::renameTable(QString tableName, QString newName) const {
    return "RENAME TABLE " + this->schema.data()->quoteTableName(
               tableName) + " TO " +
           this->schema.data()->quoteTableName(
               newName);
}

QString QueryBuilder::dropTable(QString tableName) const {
    return "DROP TABLE " + this->schema.data()->quoteTableName(tableName);
}

QString QueryBuilder::truncateTable(QString tableName) const {
    return "TRUNCATE TABLE " + this->schema.data()->quoteTableName(tableName);
}

QString QueryBuilder::addColumn(QString tableName, QString columnName,
                                QString columnType) const {
    return "ALTER TABLE " + this->schema.data()->quoteTableName(
               tableName) + " ADD " +
           this->schema.data()->quoteColumnName(
               columnName) + " " + this->getColumnType(columnType);
}

QString QueryBuilder::dropColumn(QString tableName, QString columName) const {
    return "ALTER TABLE " + this->schema.data()->quoteTableName(
               tableName) + " DROP COLUMN " +
           this->schema.data()->quoteColumnName(columName);
}

QString QueryBuilder::renameColumn(QString tableName, QString oldName,
                                   QString newName) const {
    return "ALTER TABLE " + this->schema.data()->quoteTableName(
               tableName) + " RENAME COLUMN " +
           this->schema.data()->quoteColumnName(oldName) + " TO " +
           this->schema.data()->quoteColumnName(
               newName);
}

QString QueryBuilder::alterColumn(QString tableName, QString columnName,
                                  QString newType) const {
    return "ALTER TABLE " + this->schema.data()->quoteTableName(
               tableName) + " CHANGE " +
           this->schema.data()->quoteColumnName(columnName) + " " +
           this->schema.data()->quoteColumnName(columnName) + this->getColumnType(newType);
}

QString QueryBuilder::addPrimaryKey(QString name, QString tableName,
                                    QStringList columns) const {
    return "ALTER TABLE " + this->schema.data()->quoteTableName(
               tableName) + " ADD CONSTRAINT " +
           this->schema.data()->quoteColumnName(name) + "PRIMARY KEY (" +
           this->buildColumns(columns) + " )";
}

QString QueryBuilder::dropPrimaryKey(QString name, QString tableName) const {
    return "ALTER TABLE " + this->schema.data()->quoteTableName(
               tableName) + " DROP CONSTRAINT " +
           this->schema.data()->quoteColumnName(name);
}

QString QueryBuilder::addForeignKey(QString name, QString tableName,
                                    QStringList columns,
                                    QString refTableName,
                                    QStringList refColumns, QString deleteConstraint,
                                    QString updateConstraint) const {
    QString r = "ALTER TABLE " + this->schema.data()->quoteTableName(
                    tableName) + "ADD CONSTRAINT " +
                this->schema.data()->quoteColumnName(name)
                + " FOREIGN KEY (" +  this->buildColumns(columns) + ")" + " REFERENCES " +
                this->schema.data()->quoteTableName(
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
    return "ALTER TABLE " + this->schema.data()->quoteTableName(
               tableName) + " DROP CONSTRAINT " +
           this->schema.data()->quoteColumnName(name);
}

QString QueryBuilder::createIndex(QString name, QString tableName,
                                  QStringList columns,
                                  bool unique) const {
    QString s = (unique ? "CREATE UNIQUE INDEX " : "CREATE INDEX ") +
                this->schema.data()->quoteTableName(
                    name) + " ON " + this->schema.data()->quoteTableName(tableName) + " (";
    s.append(this->buildColumns(columns));
    s.append(");");
    return s;
}

QString QueryBuilder::dropIndex(QString name, QString tableName) const {
    return "DROP INDEX " + this->schema.data()->quoteTableName(name) + " ON " +
           this->schema.data()->quoteTableName(
               tableName);
}

QSharedPointer<Database> QueryBuilder::getDatabase() const {
    return database;
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
        p1 += this->schema.data()->quoteColumnName(i.key());
        p2 += ":" + i.key();
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
    auto o = entity.data()->metaObject();
    auto superMetaObject = entity.data()->metaObject()->superClass();
    auto superMetaObjectPropertyMap = entity.data()->getSuperMetaProperties();
    QHash<QString, Relation> relations = entity.data()->getRelations();
    for (int var = 0; var < o->propertyCount(); ++var) {
        auto m = o->property(var);
        if (!superMetaObjectPropertyMap.contains(QString(m.name()))
                && m.name() != QString("objectName") && m.isReadable()
                && !entity.data()->getTransientAttributes().contains(m.name())) {
            if (m.isEnumType()) {
                map.insert(m.name(), this->schema.data()->getTypeMap().data()->value(
                               this->schema.data()->TYPE_INTEGER));
            } else if (relations.contains(m.name())) {
                Relation r = relations.value(m.name());
                if (r.getType() == RelationType::MANY_TO_ONE
                        || (r.getType() == RelationType::ONE_TO_ONE
                            && r.getMappedBy().isEmpty())) {
                    map.insert(this->generateColumnNameID(QString(m.name())),
                               this->schema.data()->TYPE_BIGINT);
                }
            } else if (entity.data()->getBLOBColumns().contains(m.name())) {
                map.insert(m.name(), this->schema.data()->getTypeMap().data()->value(
                               this->schema.data()->TYPE_BINARY));
            } else {
                map.insert(m.name(), this->transformAbstractTypeToRealDbType(
                               this->transformTypeToAbstractDbType(
                                   m.typeName())));
            }
        }
    }
    if (!(QString(superMetaObject->className()) !=
            QString("CuteEntityManager::Entity")
            && entity.data()->getInheritanceStrategy() == JOINED_TABLE)) {
        map.insert(entity.data()->getPrimaryKey(), this->schema.data()->TYPE_BIGPK);
    }
    return map;
}

QString QueryBuilder::generateManyToManyTableName(const QSharedPointer<Entity>
        &firstEntity,
        const QSharedPointer<Entity> &secondEntity) const {
    QString first = QString(firstEntity.data()->getClassname());
    QString second = QString(secondEntity.data()->getClassname());
    if (QString::compare(first, second, Qt::CaseSensitive) <= 0) {
        return firstEntity.data()->getTablename() + "_" +
               secondEntity.data()->getTablename();
    } else {
        return secondEntity.data()->getTablename() + "_" +
               firstEntity.data()->getTablename();
    }
}

QHash<QString, QHash<QString, QString>> QueryBuilder::generateRelationTables(
        const QSharedPointer<Entity> &entity)
const {
    auto relations = QHash<QString, QHash<QString, QString>>();
    QHash<QString, Relation> m = entity.data()->getRelations();
    auto props = entity.data()->getMetaProperties();
    for (auto i = m.begin(); i != m.end(); ++i) {
        Relation r = i.value();
        if (r.getType() == MANY_TO_MANY && r.getMappedBy().isEmpty()) {
            QHash<QString, QString> h = QHash<QString, QString>();
            h.insert(entity.data()->getPrimaryKey(), this->schema.data()->TYPE_BIGPK);
            h.insert(this->generateManyToManyColumnName(entity),
                     this->schema.data()->TYPE_BIGINT);
            auto m = props.value(r.getPropertyName());
            QSharedPointer<Entity> ptr = QSharedPointer<Entity>
                                         (EntityInstanceFactory::createInstance(m.type()));
            h.insert(this->generateManyToManyColumnName(ptr),
                     this->schema.data()->TYPE_BIGINT);
            relations.insert(this->generateManyToManyTableName(entity, ptr), h);
        }
    }
    return relations;
}


QString QueryBuilder::transformTypeToAbstractDbType(QString typeName) const {
    QHash<QString, QString> *m = this->schema.data()->getAbstractTypeMap().data();
    if (m->contains(typeName)) {
        return m->value(typeName);
    }
    for (auto i = m->begin(); i != m->end(); ++i) {
        if (i.key().contains(typeName)) {
            return i.value();
        }
    }
    return this->schema.data()->TYPE_TEXT;
}

QString QueryBuilder::transformAbstractTypeToRealDbType(
    QString typeName) const {
    return this->schema.data()->getTypeMap().data()->value(typeName);
}

QString QueryBuilder::getColumnType(const QString &type) const {
    /**
      * @WARNING
      */
    QHash<QString, QString> *tMap = this->schema.data()->getTypeMap().data();
    if (tMap->contains(type)) {
        return this->transformAbstractTypeToRealDbType(type);
    }
    //cant believe that this could work in Qt
    //https://github.com/yiisoft/yii2/blob/master/framework/db/QueryBuilder.php
    QRegularExpression reg = QRegularExpression(
                                 QRegularExpression::escape("/^(\\w+)\((.+?)\\)(.*)$/"));
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
    QSqlQuery q = this->database.data()->getQuery(this->selectBase(QStringList(
                      tableName)) + " WHERE id= :id LIMIT 1;");
    q.bindValue(":id", id);
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
            r.append(this->schema.data()->quoteColumnName(columns.at(var)));
        }
    }
    r.append(" FROM");
    for (int var = 0; var < tables.size(); ++var) {
        r.append(" ");
        r.append(this->schema.data()->quoteTableName(tables.at(var)));
    }
    return r;
}

QSqlQuery QueryBuilder::find(const qint64 &id,
                             const QSharedPointer<Entity> &entity, qint64 offset) const {
    QSqlQuery q = this->database.data()->getQuery(this->selectBase(QStringList(
                      entity.data()->getTablename())) + this->joinSuperClasses(
                      entity) + " WHERE id= :id" + this->limit(1, offset));
    q.bindValue(":id", id);
    return q;
}

QSqlQuery QueryBuilder::findAll(const QSharedPointer<Entity> &entity,
                                const qint64 limit, qint64 offset) {
    return this->database->getQuery(this->selectBase(QStringList(
                                        entity.data()->getTablename())) + " " + this->joinSuperClasses(
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
    QSqlQuery q = this->database.data()->getQuery(this->selectBase(QStringList(
                      tableName)) + this->where(m, "AND", ignoreID) + this->limit(limit, offset));
    this->bindValues(m, q, ignoreID);
    return q;
}

QSqlQuery QueryBuilder::findByAttributes(const QSharedPointer<Entity> &e,
        bool ignoreID,
        const qint64 limit,
        const qint64 offset) {
    QHash<QString, QVariant> values = this->getEntityAttributes(
                                          e.data()->getMetaProperties(), e);
    return this->findByAttributes(values, e.data()->getTablename(), ignoreID, limit,
                                  offset);
}

QSqlQuery QueryBuilder::findAll(const QString &tableName) const {
    return this->database->getQuery(this->selectBase(QStringList(tableName)) + ";");
}

QList<QSqlQuery> QueryBuilder::remove(const QSharedPointer<Entity> &entity)
const {
    QList<QSqlQuery> queries = QList<QSqlQuery>();
    queries.append(this->remove(entity.data()->getTablename(),
                                entity.data()->property(entity.data()->getPrimaryKey()).toLongLong()));
    if (entity.data()->getInheritanceStrategy() != PER_CLASS_TABLE
            && entity.data()->isInheritanceCascaded()) {
        auto classes = entity.data()->superClasses(true);
        for (int var = 0; var < classes.size(); ++var) {
            auto item = classes.at(var);
            auto instance = EntityInstanceFactory::createInstance(item->className());
            if (instance) {
                queries.append(this->remove(instance->getTablename(),
                                            entity.data()->property(entity.data()->getPrimaryKey()).toLongLong()));
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
                                           this->schema.data()->quoteTableName(
                                                   tableName) + " WHERE " +
                                           this->schema.data()->quoteColumnName(primaryKey) + "=:id;");
    q.bindValue(":id", id);
    return q;
}

QSqlQuery QueryBuilder::findId(const QSharedPointer<Entity> &entity) const {
    QHash<QString, QVariant> values = this->getEntityAttributes(
                                          entity.data()->getMetaProperties(),
                                          entity);
    QSqlQuery q = this->database.data()->getQuery(this->selectBase(QStringList(
                      entity.data()->getTablename()),
                  QStringList(entity.data()->getPrimaryKey())) + this->where(values,
                          "AND", true) + " LIMIT 1");
    this->bindValues(values, q);
    return q;
}

QSqlQuery QueryBuilder::count(const QSharedPointer<Entity> &entity,
                              bool ignoreID) const {
    QHash<QString, QVariant> values = this->getEntityAttributes(
                                          entity.data()->getMetaProperties(),
                                          entity);
    QSqlQuery q = this->database.data()->getQuery(this->selectBase(QStringList(
                      entity.data()->getTablename()),
                  QStringList(this->countFunction())) + this->where(
                      values, "AND", ignoreID));
    this->bindValues(values, q, ignoreID);
    return q;
}

QSqlQuery QueryBuilder::count(const QString &tableName) const {
    QSqlQuery q = this->database.data()->getQuery(this->selectBase(QStringList(
                      tableName), QStringList(this->countFunction())) + ";");
    return q;
}

QSqlQuery QueryBuilder::merge(const QSharedPointer<Entity> &entity) const {
    QHash<QString, QVariant> values = this->saveAttributes(entity);
    QSqlQuery q = this->database.data()->getQuery("UPDATE " +
                  this->schema.data()->quoteTableName(
                      entity->getTablename()) + " SET " + this->attributes(
                      values) + " WHERE " + this->schema.data()->quoteColumnName(
                      entity.data()->getPrimaryKey()) + "=:id;");
    this->bindValues(values, q);
    return q;
}

QList<QSqlQuery> QueryBuilder::create(const QSharedPointer<Entity> &entity)
const {
    auto attrs = this->inheritedAttributes(entity);
    auto queries = QList<QSqlQuery>();
    for (int var = 0; var < attrs.size(); ++var) {
        auto attr = attrs.at(var);
        auto attrHash = attr.getAttributes();
        queries.append(this->insert(attr.getName(), attrHash, attr.getPk()));
    }
    return queries;
}

QSqlQuery QueryBuilder::insert(const QString &tableName,
                               QHash<QString, QVariant> &attributes, const QString &primaryKey) const {
    attributes.remove(primaryKey);
    QSqlQuery q = this->database.data()->getQuery();
    QString p1 = "INSERT INTO " + this->schema.data()->quoteTableName(
                     tableName) + "(";
    QString p2 = "VALUES(";
    if (!attributes.isEmpty()) {
        q.prepare(this->buildCreateQuery(attributes.constBegin(), attributes.constEnd(),
                                         p1, p2));
    }
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
                                   const qint64 &id,
                                   const QString &foreignKey, const QString &foreignTable) {
    QSqlQuery q = this->database.data()->getQuery();
    QString sql = this->selectBase(QStringList(tableName),
                                   QStringList(foreignTable + ".*")) + " " + this->leftJoin(
                      foreignTable, tableName,
                      foreignKey) + " WHERE " + this->schema.data()->quoteColumnName(
                      attribute) + "=:id;";
    q.prepare(sql);
    q.bindValue(":id", id);
    return q;
}

QSqlQuery QueryBuilder::manyToManyDelete(const QString &tableName,
        const QString &attribute, const qint64 &id) {
    QSqlQuery q = this->database.data()->getQuery();
    QString sql = "DELETE FROM " + this->schema.data()->quoteTableName(
                      tableName) + " WHERE " + this->schema.data()->quoteColumnName(
                      attribute) + "=:id";
    q.prepare(sql);
    q.bindValue(":id", id);
    return q;
}

QSqlQuery QueryBuilder::manyToManyInsert(const QString &tableName,
        const QString &col1, const QString &col2) const {
    QSqlQuery q = this->database.data()->getQuery();
    QString sql = "INSERT INTO " + this->schema.data()->quoteTableName(
                      tableName) + "(" + col1 + "," + col2 + ")"
                  + "VALUES(?, ?);";
    q.prepare(sql);
    return q;
}

QString QueryBuilder::superClassColumnName(const QMetaObject *&superMeta)
const {
    return QString(superMeta->className()).toLower();
}

QString QueryBuilder::joinSuperClasses(const QSharedPointer<Entity> &entity)
const {
    auto classes = entity.data()->superClasses(true);
    QString joined = "";
    Entity *e = 0;
    for (int var = 0; var < classes.size(); ++var) {
        auto metaObject = classes.at(var);
        e = EntityInstanceFactory::createInstance(metaObject->className());
        if (e) {
            joined.append(" ");
            joined.append(this->leftJoin(e->getTablename(), entity.data()->getTablename(),
                                         e->getPrimaryKey(), entity.data()->getPrimaryKey()));
        }
        delete e;
        e = 0;
    }
    return joined;
}

QString QueryBuilder::countFunction(const QString &distinctColumn) const {
    return QString("COUNT(" + distinctColumn.isEmpty() ? "*" : (this->distinct() +
                   this->schema.data()->quoteColumnName(distinctColumn)) + ")");
}

QString QueryBuilder::distinct() const {
    return "DISTINCT";
}

QString QueryBuilder::limit(const qint64 &limit, const qint64 &offset) const {
    QString s = "";
    if (limit > 0) {
        s.append(" LIMIT ").append(QString::number(limit));
    }
    if (offset > 0) {
        s.append(" OFFSET ").append(QString::number(offset));
    }
    return s;
}

QString QueryBuilder::generateManyToManyColumnName(const QSharedPointer<Entity>
        &entity) const {
    return this->generateColumnNameID(entity.data()->getTablename());
}

QSqlQuery QueryBuilder::getQuery() const {
    return this->database.data()->getQuery();
}


QHash<QString, QVariant> QueryBuilder::saveAttributes(const
        QSharedPointer<Entity> &entity, QHash<QString, QMetaProperty> props,
        QHash<QString, Relation> relations) const {
    if (props.isEmpty()) {
        props = entity.data()->getMetaProperties();
    }
    auto values = this->getEntityAttributes(props, entity);
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
    auto properties = e.data()->getMetaProperties();
    auto i = QMutableHashIterator<QString, QMetaProperty>(properties);
    while (i.hasNext()) {
        if (usedProperties.contains(i.key()) && i.key() != e.data()->getPrimaryKey()) {
            properties.remove(i.key());
        } else {
            usedProperties.insert(i.key(), i.value());
        }
        i.next();
    }
    return properties;
}

QHash<QString, Relation> QueryBuilder::processRelations(
    const QSharedPointer<Entity> &e,
    QHash<QString, Relation> &usedRelations) const {
    auto relations = e.data()->getRelations();
    auto i = QMutableHashIterator<QString, Relation>(relations);
    while (i.hasNext()) {
        if (usedRelations.contains(i.key())) {
            relations.remove(i.key());
        } else {
            usedRelations.insert(i.key(), i.value());
        }
        i.next();
    }
    return relations;
}

QList<QueryBuilder::ClassAttributes> QueryBuilder::inheritedAttributes(
    const QSharedPointer<Entity> &entity) const {
    auto list = QList<QueryBuilder::ClassAttributes>();
    if (entity.data()->getInheritanceStrategy() == JOINED_TABLE) {
        auto classes = QList<const QMetaObject *>();
        classes.append(entity.data()->metaObject());
        classes.append(entity.data()->superClasses(true));
        auto usedProperties = QHash<QString, QMetaProperty>();
        auto usedRelations = QHash<QString, Relation>();
        QSharedPointer<Entity> e;
        for (int var = classes.size(); var >= 0; --var) {
            auto metaObj = classes.at(var);
            e = QSharedPointer<Entity>(EntityInstanceFactory::createInstance(
                                           metaObj->className()));
            if (e) {
                list.append(QueryBuilder::ClassAttributes(e.data()->getTablename(),
                            this->saveAttributes(entity, this->processProperties(e, usedProperties),
                                                 this->processRelations(e, usedRelations)), e.data()->getPrimaryKey()));
            } else {
                qDebug() << "Instance of " << metaObj->className() << " could not created";
                break;
            }
        }
    } else {
        list.append(QueryBuilder::ClassAttributes(entity.data()->getTablename(),
                    this->saveAttributes(entity), entity.data()->getPrimaryKey()));
    }
    return list;
}

QString QueryBuilder::leftJoin(const QString &foreignTable,
                               const QString &tableName, const QString &foreignKey,
                               const QString &primaryKey) const {
    return "LEFT JOIN " + this->schema.data()->quoteTableName(
               foreignTable) + " ON " +
           this->schema.data()->quoteColumnName(foreignTable + "." + primaryKey) + "=" +
           this->schema.data()->quoteColumnName(
               tableName + "." + foreignKey);
}

QHash<QString, QVariant> QueryBuilder::getEntityAttributes(
    const QHash<QString, QMetaProperty>
    &props,
    const QSharedPointer<Entity> &entity) const {
    Entity *e = entity.data();
    auto map = QHash<QString, QVariant>();
    auto transientAttrs = e->getTransientAttributes();
    auto relations = e->getRelations();
    auto i = props.constBegin();
    while (i != props.constEnd()) {
        if (!transientAttrs.contains(i.key()) && !relations.contains(i.key())) {
            map.insert(i.key(), i.value().read(e));
        }
        ++i;
    }
    return map;
}

QHash<QString, QVariant> QueryBuilder::getManyToOneAttributes(
    QHash<QString, QMetaProperty>
    props,
    const QSharedPointer<Entity> &entity,
    QHash<QString, Relation> relations) const {
    Entity *e = entity.data();
    auto map = QHash<QString, QVariant>();
    if (relations.isEmpty()) {
        relations = e->getRelations();
    }
    auto i = relations.constBegin();
    while (i != relations.constEnd()) {
        Relation r = i.value();
        if ((r.getType() == MANY_TO_ONE && props.contains(i.key()))
                || (r.getType() == ONE_TO_ONE && r.getMappedBy().isEmpty())) {
            auto v = props.value(i.key()).read(e);
            if (v.canConvert<Entity *>()) {
                this->insertRelationId(qvariant_cast<Entity *>(v), map, i.key());
            } else if (v.canConvert<QSharedPointer<Entity>>()) {
                this->insertRelationId(qvariant_cast<QSharedPointer<Entity>>(v).data(), map,
                                       i.key());
            } else if (v.canConvert<QPointer<Entity>>()) {
                this->insertRelationId(qvariant_cast<QPointer<Entity>>(v).data(), map, i.key());
            }
            ++i;
        }
    }
    return map;
}

void QueryBuilder::insertRelationId(const Entity *e,
                                    QHash<QString, QVariant> &map,
                                    QString relName) const {
    if (e && e->property(e->getPrimaryKey()).toLongLong() > -1) {
        map.insert(this->generateColumnNameID(relName),
                   e->property(e->getPrimaryKey()));
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
        if (!ignoreID || (ignoreID && !(i.key() == primaryKey))) {
            q.bindValue(":" + i.key(), i.value());
        }
        ++i;
    }
}

QString QueryBuilder::where(const QSharedPointer<Entity> &entity,
                            QString conjunction,
                            bool ignoreID) const {
    return this->where(this->getEntityAttributes(entity.data()->getMetaProperties(),
                       entity),
                       conjunction, ignoreID, entity.data()->getPrimaryKey());
}

QString QueryBuilder::where(const QHash<QString, QVariant> &m,
                            const QString &conjunction,
                            bool ignoreID, const QString &primaryKey) const {
    if (m.size() == 0 || (ignoreID && m.contains(primaryKey) && m.size() == 1)) {
        return "";
    }
    return " WHERE " + this->attributes(m, conjunction, ignoreID, primaryKey);
}

QString QueryBuilder::attributes(const QHash<QString, QVariant> &m,
                                 const QString &conjunction,
                                 bool ignoreID, const QString &primaryKey) const {
    QString rc = "";
    if (!m.isEmpty()) {
        QHash<QString, QVariant>::const_iterator i = m.constBegin();
        while (i != m.constEnd()) {
            if (!ignoreID || (ignoreID && !(i.key() == primaryKey))) {
                if (!(rc == "")) {
                    rc += " " + conjunction + " ";
                }
                rc += this->schema.data()->quoteColumnName(i.key()) + "=:" + i.key();
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

