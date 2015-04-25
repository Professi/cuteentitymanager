#include "querybuilder.h"
#include "database.h"
#include <QMetaObject>
#include <QMetaProperty>
#include "entity.h"
#include <QRegularExpression>

using namespace CuteEntityManager;

QueryBuilder::QueryBuilder(QSharedPointer<Schema> schema, QSharedPointer<Database> database) {
    this->schema = schema;
    this->database = database;
}

QueryBuilder::~QueryBuilder() {

}

bool QueryBuilder::createTable(const QSharedPointer<Entity> &entity) const {
    return this->createTable(entity.data()->getTablename(), this->generateTableDefinition(entity));
}

bool QueryBuilder::createTable(const QString &tableName, const QHash<QString, QString> &tableDefinition) const {
    bool rc = false;
    this->schema.data()->containsTable(tableName) ? rc = true : rc = false;
    if (!rc) {
        QSqlQuery q = this->database.data()->getQuery(this->createTableQuery(tableName, tableDefinition));
        if (this->database.data()->transaction(q)) {
            this->schema.data()->getTableSchema(tableName);
            rc = true;
        }
    }
    return rc;
}

QString QueryBuilder::createTableQuery(const QString &tableName, const QHash<QString, QString> &tableDefinition) const {
    bool first = true;
    QString s = "CREATE TABLE ";
    s.append(this->schema.data()->quoteTableName(tableName).append(" (\n"));
    QHash<QString, QString>::const_iterator i = tableDefinition.constBegin();
    while (i != tableDefinition.constEnd()) {
        if (first) {
            first = false;
        } else {
            s.append(", ");
        }
        s.append(this->schema.data()->quoteColumnName(i.key())).append(" " + this->getColumnType(i.value()));
        ++i;
    }
    s.append("\n);");
    return s;
}

QString QueryBuilder::renameTable(QString tableName, QString newName) const {
    return "RENAME TABLE " + this->schema.data()->quoteTableName(tableName) + " TO " + this->schema.data()->quoteTableName(
               newName);
}

QString QueryBuilder::dropTable(QString tableName) const {
    return "DROP TABLE " + this->schema.data()->quoteTableName(tableName);
}

QString QueryBuilder::truncateTable(QString tableName) const {
    return "TRUNCATE TABLE " + this->schema.data()->quoteTableName(tableName);
}

QString QueryBuilder::addColumn(QString tableName, QString columnName, QString columnType) const {
    return "ALTER TABLE " + this->schema.data()->quoteTableName(tableName) + " ADD " + this->schema.data()->quoteColumnName(
               columnName) + " " + this->getColumnType(columnType);
}

QString QueryBuilder::dropColumn(QString tableName, QString columName) const {
    return "ALTER TABLE " + this->schema.data()->quoteTableName(tableName) + " DROP COLUMN " +
           this->schema.data()->quoteColumnName(columName);
}

QString QueryBuilder::renameColumn(QString tableName, QString oldName, QString newName) const {
    return "ALTER TABLE " + this->schema.data()->quoteTableName(tableName) + " RENAME COLUMN " +
           this->schema.data()->quoteColumnName(oldName) + " TO " + this->schema.data()->quoteColumnName(newName);
}

QString QueryBuilder::alterColumn(QString tableName, QString columnName, QString newType) const {
    return "ALTER TABLE " + this->schema.data()->quoteTableName(tableName) + " CHANGE " +
           this->schema.data()->quoteColumnName(columnName) + " " +
           this->schema.data()->quoteColumnName(columnName) + this->getColumnType(newType);
}

QString QueryBuilder::addPrimaryKey(QString name, QString tableName, QStringList columns) const {
    return "ALTER TABLE " + this->schema.data()->quoteTableName(tableName) + " ADD CONSTRAINT " +
           this->schema.data()->quoteColumnName(name) + "PRIMARY KEY (" + this->buildColumns(columns) + " )";
}

QString QueryBuilder::dropPrimaryKey(QString name, QString tableName) const {
    return "ALTER TABLE " + this->schema.data()->quoteTableName(tableName) + " DROP CONSTRAINT " +
           this->schema.data()->quoteColumnName(name);
}

QString QueryBuilder::addForeignKey(QString name, QString tableName, QStringList columns, QString refTableName,
                                    QStringList refColumns, QString deleteConstraint, QString updateConstraint) const {
    QString r = "ALTER TABLE " + this->schema.data()->quoteTableName(tableName) + "ADD CONSTRAINT " +
                this->schema.data()->quoteColumnName(name)
                + " FOREIGN KEY (" +  this->buildColumns(columns) + ")" + " REFERENCES " + this->schema.data()->quoteTableName(
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

QString QueryBuilder::dropForeignKey(QString name, QString tableName) const {
    return "ALTER TABLE " + this->schema.data()->quoteTableName(tableName) + " DROP CONSTRAINT " +
           this->schema.data()->quoteColumnName(name);
}

QString QueryBuilder::createIndex(QString name, QString tableName, QStringList columns, bool unique) const {
    QString s = (unique ? "CREATE UNIQUE INDEX " : "CREATE INDEX ") + this->schema.data()->quoteTableName(
                    name) + " ON " + this->schema.data()->quoteTableName(tableName) + " (";
    s.append(this->buildColumns(columns));
    s.append(");");
    return s;
}

QString QueryBuilder::dropIndex(QString name, QString tableName) const {
    return "DROP INDEX " + this->schema.data()->quoteTableName(name) + " ON " + this->schema.data()->quoteTableName(
               tableName);
}

QSharedPointer<Database> QueryBuilder::getDatabase() const {
    return database;
}

void QueryBuilder::setDatabase(const QSharedPointer<Database> &value) {
    database = value;
}

QHash<QString, QString> QueryBuilder::generateTableDefinition(const QSharedPointer<Entity> &entity) const {
    auto map = QHash<QString, QString>();
    auto o = entity.data()->metaObject();
    QHash<QString, Relation> relations = entity.data()->getRelations();
    QHash<QString, QSharedPointer<Entity>> relationObjects = entity.data()->getRelationObjects();
    for (int var = 0; var < o->propertyCount(); ++var) {
        o->property(var);
        auto m = o->property(var);
        if (m.name() != QString("objectName") && m.isReadable()
                && !entity.data()->getTransientAttributes().contains(m.name())) {
            if (m.isEnumType()) {
                map.insert(m.name(), this->schema.data()->getTypeMap().data()->value(this->schema.data()->TYPE_INTEGER));
            } else if (relations.contains(m.name())) {
                Relation r = relations.value(m.name());
                if (r.getType() == RelationType::MANY_TO_ONE) {
                    map.insert(QString(m.name()) + "_id", this->schema.data()->TYPE_BIGINT);
                }
            } else if (entity.data()->getBLOBColumns().contains(m.name())) {
                map.insert(m.name(), this->schema.data()->getTypeMap().data()->value(this->schema.data()->TYPE_BINARY));
            } else {
                map.insert(m.name(), this->transformAbstractTypeToRealDbType(this->transformTypeToAbstractDbType(m.typeName())));
            }
        }
    }
    QString pkType = map.value(entity.data()->getPrimaryKey());
    if (pkType == this->schema.data()->TYPE_BIGINT) {
        map.insert(entity.data()->getPrimaryKey(), this->schema.data()->TYPE_BIGPK);
    } else {
        map.insert(entity.data()->getPrimaryKey(), this->schema.data()->TYPE_PK);
    }
    return map;
}

QString QueryBuilder::generateManyToManyTableName(const QSharedPointer<Entity> &firstEntity,
        const QSharedPointer<Entity> &secondEntity) const {
    return QString(firstEntity.data()->metaObject()->className()).toLower() + "_" + QString(
               secondEntity.data()->metaObject()->className()).toLower();
}

QHash<QString, QHash<QString, QString>> QueryBuilder::generateRelationTables(const QSharedPointer<Entity> &entity)
const {
    auto relations = QHash<QString, QHash<QString, QString>>();
    QHash<QString, Relation> m = entity.data()->getRelations();
    QHash<QString, QSharedPointer<Entity>> os = entity.data()->getRelationObjects();
    for (auto i = m.begin(); i != m.end(); ++i) {
        Relation r = i.value();
        if (r.getType() == MANY_TO_MANY && r.getMappedBy().isEmpty()) {
            QHash<QString, QString> h = QHash<QString, QString>();
            h.insert("id", this->schema.data()->TYPE_BIGPK);
            h.insert(QString(entity.data()->metaObject()->className()) + QString("_id"), this->schema.data()->TYPE_BIGINT);
            if (os.contains(i.key())) {
                h.insert(QString(os.value(i.key()).data()->metaObject()->className()) + QString("_id"),
                         this->schema.data()->TYPE_BIGINT);
                if (r.getTableName().isEmpty()) {
                    relations.insert(this->generateManyToManyTableName(entity, os.value(i.key())), h);
                } else {
                    relations.insert(r.getTableName(), h);
                }
            }
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

QString QueryBuilder::transformAbstractTypeToRealDbType(QString typeName) const {
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
    QRegularExpression reg = QRegularExpression(QRegularExpression::escape("/^(\\w+)\((.+?)\\)(.*)$/"));
    reg.optimize();
    QRegularExpressionMatchIterator i = reg.globalMatch(type, 0, QRegularExpression::PartialPreferFirstMatch);
    short s = 0;
    bool ok = false;
    QString before = "";
    while (i.hasNext() && s < 2) {
        before = i.next().captured();
        if (tMap->contains(before)) {
            ok = true;
        }
        if (ok) {
            return before.replace(QRegularExpression::escape("/\\(.+\\)/"), "(" + i.next().captured() + ")");
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

QHash<QString, QVariant> QueryBuilder::getEntityAttributes(const QHash<QString, QMetaProperty> &props,
        const QSharedPointer<Entity> &entity) {
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

QHash<QString, QVariant> QueryBuilder::getManyToOneAttributes(const QHash<QString, QMetaProperty> &props,
        const QSharedPointer<Entity> &entity) {
    Entity *e = entity.data();
    auto map = QHash<QString, QVariant>();
    auto relations = e->getRelations();
    auto i = relations.constBegin();
    while (i != relations.constEnd()) {
        Relation r = i.value();
        if (r.getType() == MANY_TO_ONE && props.contains(i.key())) {
            auto v = props.value(i.key()).read(e);
            if (v.canConvert<Entity *>()) {
                this->insertRelationId(qvariant_cast<Entity *>(v), map, i.key());
            } else if (v.canConvert<QSharedPointer<Entity>>()) {
                this->insertRelationId(qvariant_cast<QSharedPointer<Entity>>(v).data(), map, i.key());
            } else if (v.canConvert<QPointer<Entity>>()) {
                this->insertRelationId(qvariant_cast<QPointer<Entity>>(v).data(), map, i.key());
            }
            ++i;
        }
    }
    return map;
}


void QueryBuilder::insertRelationId(const Entity *e, QHash<QString, QVariant> &map, QString relName) {
    if (e && e->getId() > -1) {
        map.insert(relName + "_id", e->getId());
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



QSharedPointer<Schema> QueryBuilder::getSchema() const {
    return schema;
}

void QueryBuilder::setSchema(const QSharedPointer<Schema> &value) {
    schema = value;
}
