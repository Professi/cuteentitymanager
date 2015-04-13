#include "querybuilder.h"
#include "database.h"
#include <QMetaObject>
#include <QMetaProperty>
#include "entity.h"
using namespace CuteEntityManager;

//bool QueryBuilder::createTable(QString tablename, QHash<QString, QString> tableDefinition) {
////    QHash<QString, QString> Artikel::getProperties(DatabaseType type) {
////        QHash<QString, QString> h = QHash<QString, QString>();
////        h.insert("id",this->idColumnSQL());
////        h.insert("preis","DOUBLE");
////        h.insert("name","TEXT");
////        return h;
////    }
//}

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
            s.append(',');
        }
        s.append(this->schema.data()->quoteColumnName(i.key())).append(" " + i.value());
        ++i;
    }
    s.append("\n);");
    return s;
}

bool QueryBuilder::renameTable(QString tableName, QString newName) const {

}

bool QueryBuilder::dropTable(QString tableName) const {

}

bool QueryBuilder::truncateTable(QString tableName) const {

}

bool QueryBuilder::addColumn(QString tableName, QString columnName, QString columnType) const {

}

QString QueryBuilder::dropColumn(QString tableName, QString columName) const {

}

QString QueryBuilder::renameColumn(QString tableName, QString oldName, QString newName) const {

}

QString QueryBuilder::alterColumn(QString tableName, QString columnName, QString newType) const {

}

QString QueryBuilder::addPrimaryKey(QString name, QString tableName, QStringList columns) const {

}

QString QueryBuilder::dropPrimaryKey(QString name, QString tableName) const {

}

QString QueryBuilder::addForeignKey(QString name, QString tableName, QStringList columns, QString refTableName,
                                    QStringList refColumns, QString deleteConstraint, QString updateConstraint) {

}

QString QueryBuilder::dropForeignKey(QString name, QString tableName) const {

}

QString QueryBuilder::createIndex(QString name, QString tableName, QStringList columns, bool unique) const {

}

QString QueryBuilder::dropIndex(QString name, QString tableName) const {

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
    for (int var = 0; var < o->propertyCount(); ++var) {
        o->property(var);
        auto m = o->property(var);
        if (m.isReadable() && !entity.data()->getTransientAttributes().contains(m.name())) {
            if (m.isEnumType()) {
                map.insert(m.name(), this->schema.data()->getTypeMap().data()->value(this->schema.data()->TYPE_INTEGER));
            } else if (entity.data()->getRelations().contains(m.name())) {
                map.insert(QString(m.name()) + "_id", this->schema.data()->TYPE_INTEGER);
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

QString QueryBuilder::transformTypeToAbstractDbType(QString typeName) const {
    QHash<QString, QString> *m = this->schema.data()->getAbstractTypeMap().data();
    if (m->contains(typeName)) {
        return m->value(typeName);
    }
    QHash<QString, QString>::iterator i;
    for (i = m->begin(); i != m->end(); ++i) {
        if (i.key().contains(typeName)) {
            return i.value();
        }
    }
    return this->schema.data()->TYPE_TEXT;
}

QString QueryBuilder::transformAbstractTypeToRealDbType(QString typeName) const {
    return this->schema.data()->getTypeMap().data()->value(typeName);
}

QHash<QString, QVariant> QueryBuilder::getEntityAttributes(const QSharedPointer<Entity> &entity) {
    Entity *e = entity.data();
    auto map = QHash<QString, QVariant>();
    auto metaObject = e->metaObject();
    auto transientAttrs = e->getTransientAttributes();
    for (int var = 0; var < metaObject->propertyCount(); ++var) {
        auto p = metaObject->property(var);
        QString name = QString(p.name());
        if (p.isValid() && !transientAttrs.contains(name)) {
            QVariant v = p.read(e);
            //Relation
            if (v.canConvert<Entity *>()) {
                this->insertRelationId(qvariant_cast<Entity *>(v), map, name);
            } else if (v.canConvert<QSharedPointer<Entity>>()) {
                this->insertRelationId(qvariant_cast<QSharedPointer<Entity>>(v).data(), map, name);
            } else if (QString(p.typeName()).contains("QList")) {
                /**
                  @TODO
                  //List and/or ManyToManyRelation
                  */
                auto n = static_cast<QList<CuteEntityManager::Entity *>*>(v.data());
                for (int var = 0; var < n->size(); ++var) {
                    CuteEntityManager::Entity *entity = n->at(var);
                    qDebug() << entity->toString();
                }
            } else {
                map.insert(name, v);
            }
        }
    }
    return map;
}

void QueryBuilder::insertRelationId(const Entity *e, QHash<QString, QVariant> &map, QString relName) {
    if (e && e->getId() > -1) {
        map.insert(relName + "_id", e->getId());
    }
}

QSharedPointer<Schema> QueryBuilder::getSchema() const {
    return schema;
}

void QueryBuilder::setSchema(const QSharedPointer<Schema> &value) {
    schema = value;
}

