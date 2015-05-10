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

#include "entitymanager.h"
#include "enums/databasetype.h"
#include "databasemigration.h"
using namespace CuteEntityManager;

QStringList EntityManager::connectionNames = QStringList();

void EntityManager::init() {
    auto schema = Database::getSchema(Database::getDatabaseType(
                                          this->db.data()->getDatabase().driverName()), this->db);
    this->schema = QSharedPointer<Schema>(schema);
    this->schema.data()->setTables(this->schema.data()->getTableSchemas());
}

EntityManager::EntityManager(QSqlDatabase database) {
    auto db = new Database(database);
    this->db = QSharedPointer<Database>(db);
    this->init();
}

bool EntityManager::startup(QString version, QStringList toInitialize) {
    DatabaseMigration *dbm = new DatabaseMigration();
    QSharedPointer<Entity> ptrDbm = QSharedPointer<Entity>(dbm);
    QHash<QString, QVariant> map = QHash<QString, QVariant>();
    bool ok = true;
    map.insert("version", version);
    if (this->findAllByAttributes(map, dbm->getTablename()).isEmpty()) {
        for (int var = 0; var < toInitialize.size(); ++var) {
            if (ok) {
                QString c = toInitialize.at(var);
                ok = this->createTable(QSharedPointer<Entity>
                                       (EntityInstanceFactory::createInstance(c)));
            } else {
                break;
            }
        }
        if (ok) {
            dbm->setVersion(version);
            dbm->setApplyTime(QDateTime::currentDateTime());
            this->create(ptrDbm);
        }
    }
    delete dbm;
    return ok;
}

bool EntityManager::executeQuery(const QString &query) {
    return this->db.data()->transaction(query);
}

EntityManager::EntityManager(const QString &databaseType, QString databasename ,
                             QString hostname,
                             QString username,
                             QString password, QString port) {
    auto db = new Database(databaseType, this->createConnection(), hostname,
                           databasename, username,
                           password,
                           port.toInt());
    this->db = QSharedPointer<Database>(db);
    this->init();
}

bool EntityManager::checkTable(const QSharedPointer<Entity> &entity) {
    bool rc = true;
    if (!this->schema.data()->containsTable(entity.data()->getTablename())) {
        if (this->schema.data()->getQueryBuilder().data()->createTable(entity)) {
            this->schema.data()->getTableSchema(entity.data()->getTablename(), true);
            rc = this->schema.data()->getTables().contains(entity.data()->getTablename());
        }
    }
    return rc;
}

QSharedPointer<Database> EntityManager::getDb() const {
    return db;
}

void EntityManager::setDb(const QSharedPointer<Database> &value) {
    db = value;
}

QSharedPointer<Schema> EntityManager::getSchema() const {
    return schema;
}

void EntityManager::refresh(QSharedPointer<Entity> &entity) {
    entity = this->findById(entity.data()->getId(),
                            QString(entity.data()->getClassname()));
}

void EntityManager::setSchema(const QSharedPointer<Schema> &value) {
    schema = value;
}

QString EntityManager::createConnection() {
    QStringList l = EntityManager::getConnectionNames();
    QString conName = "";
    bool ok = false;
    qint16 i = 0;
    while (!ok) {
        if (l.contains("con" + QString::number(i))) {
            ++i;
        } else {
            l.append("con" + QString::number(i));
            ok = true;
            conName = "con" + QString::number(i);
            EntityManager::setConnectionNames(l);
        }
    }
    return conName;
}

void EntityManager::removeConnectionName(const QString &name) {
    EntityManager::connectionNames.removeOne(name);
}

QSharedPointer<Entity> EntityManager::findById(const qint64 &id, Entity *&e,
        const bool refresh) {
    QSharedPointer<Entity> r;
    if (e) {
        if (refresh || ((r = this->cache.get(id, QString(e->getClassname())))
                        && !r.data())) {
            auto map  = this->findByPk(id, e->getTablename());
            r = this->convert(map, e->getClassname(), refresh);
        }
        delete e;
    }
    return r;
}

QSharedPointer<Entity> EntityManager::findById(const qint64 &id,
        const QString &classname) {
    Entity *e = EntityInstanceFactory::createInstance(classname);
    return this->findById(id, e);
}

QSharedPointer<Entity> EntityManager::convert(const QHash<QString, QVariant>
        &map,
        const char *classname, const bool refresh) {
    auto ptr = QSharedPointer<Entity>(EntityInstanceFactory::createInstance(
                                          classname, map));
    this->resolveRelations(ptr, map, refresh);
    this->cache.insert(ptr);
    return ptr;
}

QList<QSharedPointer<Entity> > EntityManager::convert(
    QList<QHash<QString, QVariant> > maps,
    const char *classname, const bool refresh) {
    auto list = QList<QSharedPointer<Entity> >();
    for (int var = 0; var < maps.size(); ++var) {
        auto ptr = this->convert(maps.at(var), classname, refresh);
        list.append(ptr);
        this->cache.insert(ptr);
    }
    return list;
}

void EntityManager::manyToOne(const QSharedPointer<Entity> &entity,
                              const QVariant &id,
                              const QMetaProperty &property, const bool refresh) {
    qint64 convertedId = -1;
    bool ok = false;
    if ((convertedId == id.toLongLong(&ok)) && ok && convertedId > -1) {
        QString className = EntityInstanceFactory::extractEntityType(
                                property.typeName());
        QSharedPointer<Entity> ptr = QSharedPointer<Entity>();
        if (refresh || !(this->cache.contains(convertedId, className)
                         && (ptr = this->cache.get(convertedId, className)) && ptr.data())) {
            ptr = this->findById(convertedId, className);
        }
        this->setProperty(entity, ptr, property);
    }
}

void EntityManager::oneToMany(const QSharedPointer<Entity> &entity,
                              const Relation &r,
                              const QMetaProperty &property, const bool refresh) {
    if (entity.data() && entity.data()->getId() > -1) {
        Entity *e = EntityInstanceFactory::createInstance(
                        EntityInstanceFactory::extractEntityType(
                            property.typeName()));
        QSqlQuery q = this->schema.data()->getQueryBuilder().data()->oneToMany(
                          e->getTablename(),
                          r.getMappedBy() + "_id", entity.data()->getId());
        auto listMap = this->convertQueryResult(q);
        auto entities = this->convert(listMap, e->getClassname(), refresh);
        delete e;
        this->setListProperty(entity, entities, property);
    }
}


void EntityManager::oneToOne(const QSharedPointer<Entity> &entity,
                             const Relation &r,
                             const QMetaProperty &property, const bool refresh,
                             const QVariant &id) {
    if (r.getMappedBy().isEmpty()) {
        this->manyToOne(entity, id, property);
    } else {
        Entity *e = EntityInstanceFactory::createInstance(
                        EntityInstanceFactory::extractEntityType(
                            property.typeName()));
        QSqlQuery q = this->schema.data()->getQueryBuilder().data()->oneToMany(
                          e->getTablename(),
                          r.getMappedBy() + "_id", entity.data()->getId(), 1);
        auto listMap = this->convertQueryResult(q);
        auto entities = this->convert(listMap, e->getClassname(), refresh);
        if (!entities.isEmpty()) {
            QSharedPointer<Entity> ptr = entities.at(0);
            this->setProperty(entity, ptr, property);
        }
        delete e;
    }
}

bool EntityManager::canPersistRelation(const Relation &relation,
                                       const RelationType &r, const QVariant &var) const {
    return relation.getType() == r
           && var.canConvert<QList<QSharedPointer<Entity>>>();
}

void EntityManager::setListProperty(const QSharedPointer<Entity> &entity,
                                    QList<QSharedPointer<Entity> > &list,
                                    const QMetaProperty &property) const {
    QVariant var;
    var.setValue<QList<QSharedPointer<Entity>>>(list);
    property.write(entity.data(), var);
}

void EntityManager::setProperty(const QSharedPointer<Entity> &entiy,
                                QSharedPointer<Entity> value,
                                const QMetaProperty &property) const {
    if (value.data() && value.data()->getId() > -1) {
        property.write(entiy.data(), QVariant(value));
    }
}

void EntityManager::saveRelations(const QSharedPointer<Entity> &entity) {
    auto relations = entity.data()->getRelationProperties();
    auto iterator = relations.constBegin();
    while (iterator != relations.constEnd()) {
        const Relation r = iterator.key();
        /**
         * @TODO cascade types
         */
        auto var = iterator.value().read(entity.data());
        if (this->canPersistRelation(r, MANY_TO_MANY, var)) {
            this->persistManyToMany(entity, r, var);
        } else if (this->canPersistRelation(r, ONE_TO_MANY, var)) {
            QList<QSharedPointer<Entity>> list =
                                           qvariant_cast<QList<QSharedPointer<Entity>>>(var);
            for (int var = 0; var < list.size(); ++var) {
                auto entity = list.at(var);
                this->save(entity);
            }
        } else if (r.getType() == ONE_TO_ONE && !r.getMappedBy().isEmpty()
                   && var.canConvert<QSharedPointer<Entity>>()) {
            auto entity =  qvariant_cast<QSharedPointer<Entity>>(var);
            this->save(entity);
        }
        ++iterator;
    }
}


void EntityManager::persistManyToMany(const QSharedPointer<Entity> &entity,
                                      const Relation &r, const QVariant &property) {
    QList<QSharedPointer<Entity>> list =
                                   qvariant_cast<QList<QSharedPointer<Entity>>>(property);
    if (!list.isEmpty()) {
        auto ptr = list.at(0);
        auto builder = this->schema.data()->getQueryBuilder();
        QString tblName = builder.data()->generateManyToManyTableName(entity, ptr);
        if (this->schema.data()->getTables().contains(tblName)) {
            QSqlQuery q = builder.data()->manyToManyDelete(
                              tblName, builder.data()->generateManyToManyColumnName(entity),
                              entity.data()->getId());
            if (this->db.data()->transaction(q)) {
                q.clear();
                QList<QSharedPointer<Entity>> persisted = QList<QSharedPointer<Entity>>();
                q = builder.data()->manyToManyInsert(tblName,
                                                     builder.data()->generateManyToManyColumnName(entity),
                                                     builder.data()->generateManyToManyColumnName(ptr));
                q.bindValue(0, entity.data()->getId());
                for (int var = 0; var < list.size(); ++var) {
                    ptr = list.at(var);
                    if (ptr.data() && ((ptr.data()->getId() > -1 && r.getCascadeType() == MERGE)
                                       || r.getCascadeType() == ALL || r.getCascadeType() == PERSIST)) {
                        if (this->save(ptr)) {
                            persisted.append(ptr);
                        }
                    }
                }
                //maybe use transaction
                //this->db.data()->startTransaction();
                for (int var = 0; var < persisted.size(); ++var) {
                    ptr = list.at(var);
                    q.bindValue(1, ptr.data()->getId());
                    q.exec();
                    /**
                      * @TODO append to attribute list
                      * */
                }
                //this->db.data()->commitTransaction();
                /**
                  * cascade types remove/refresh will be ignored atm
                  * */
            }
        } else {
            qDebug() << "MANY_TO_MANY Table " << tblName << " not exists";
        }
    }
}



void EntityManager::manyToMany(const QSharedPointer<Entity> &entity,
                               const Relation &r,
                               const QMetaProperty &property, const bool refresh) {
    Entity *secEntity = EntityInstanceFactory::createInstance(
                            EntityInstanceFactory::extractEntityType(
                                QString(
                                    property.typeName())));
    auto builder = this->schema.data()->getQueryBuilder();
    if (secEntity) {
        QSharedPointer<Entity> secEntityPtr = QSharedPointer<Entity>(secEntity);
        QString tblName = builder.data()->generateManyToManyTableName(entity,
                          secEntityPtr);
        /**
         * maybe it would be better, to fetch first the ids, look up cache and then request missing entities
         */
        if (this->schema.data()->getTables().contains(tblName)) {
            QSqlQuery q = builder.data()->manyToMany(tblName,
                          builder.data()->generateManyToManyColumnName(entity), entity.data()->getId(),
                          builder.data()->generateManyToManyColumnName(secEntityPtr),
                          secEntityPtr.data()->getTablename());
            auto listMap = this->convertQueryResult(q);
            auto entities = this->convert(listMap, entity.data()->getClassname(), refresh);
            this->setListProperty(entity, entities, property);
        } else {
            qDebug() << "MANY_TO_MANY Table " << tblName << " not exists";
        }
    }
}

QList<QSharedPointer<Entity> > EntityManager::findEntityByAttributes(
    const QSharedPointer<Entity>
    &entity,
    bool ignoreID) {
    auto maps = this->findAllByAttributes(entity, ignoreID);
    return this->convert(maps, entity.data()->getClassname());
}

/**
 * @todo should be an insert statement with many values
 * not really usefull atm
 * @brief EntityManager::create
 * @param entities
 * @return
 */
bool EntityManager::create(QList<QSharedPointer<Entity> > entities,
                           const bool persistRelations) {
    bool ok = true;
    foreach (QSharedPointer<Entity> ent, entities) {
        ok = this->create(ent, persistRelations);
        if (!ok) {
            break;
        }
    }
    return ok;
}

bool EntityManager::create(QSharedPointer<Entity> &entity,
                           const bool persistRelations) {
    bool rc = false;
    if (this->checkTable(entity) && this->count(entity) == 0) {
        QSqlQuery q = this->schema.data()->getQueryBuilder().data()->create(entity);
        rc = this->db->transaction(q);
        if (rc) {
            entity.data()->setId(this->schema.data()->getLastInsertID().toLongLong(&rc));
            if (persistRelations) {
                this->saveRelations(entity);
            }
            this->cache.insert(entity);
        }
    }
    return rc;
}

EntityManager::~EntityManager() {
    EntityManager::removeConnectionName(this->db->getConnectionName());
}

QStringList EntityManager::getConnectionNames() {
    return EntityManager::connectionNames;
}

QHash<QString, QVariant> EntityManager::findByPk(qint64 id, QString tblname) {
    QSqlQuery q = this->schema.data()->getQueryBuilder().data()->find(id, tblname);
    auto listMap  = this->convertQueryResult(q);
    if (!listMap.isEmpty()) {
        return listMap.at(0);
    }
    return QHash<QString, QVariant>();
}


QList<QHash<QString, QVariant> > EntityManager::findAllByAttributes(
    const QSharedPointer<Entity>
    &entity,
    bool ignoreID) {
    QSqlQuery q = this->schema.data()->getQueryBuilder().data()->findByAttributes(
                      entity, ignoreID);
    return this->convertQueryResult(q);
}

QList<QHash <QString, QVariant> > EntityManager::findAllByAttributes(
    const QHash<QString, QVariant>
    &m,
    const QString &tblname,
    bool ignoreID) {
    QSqlQuery q = this->schema.data()->getQueryBuilder().data()->findByAttributes(m,
                  tblname, ignoreID);
    return this->convertQueryResult(q);
}

bool EntityManager::merge(QSharedPointer<Entity> &entity, bool withRelations) {
    if (this->count(entity) == 0 && entity->getId() != -1) {
        QSqlQuery q = this->schema.data()->getQueryBuilder().data()->merge(entity);
        bool ok = this->db->transaction(q);
        if (ok && withRelations) {
            this->saveRelations(entity);
        }
        return ok;
    } else {
        return false;
    }
}

QList<QHash<QString, QVariant> > EntityManager::convertQueryResult(
    QSqlQuery &q) {
    QList<QHash <QString, QVariant> > listmap = QList<QHash <QString, QVariant> >();
    this->db->select(q);
    QSqlRecord rec = q.record();
    QStringList l = QStringList();
    qint16 field_count = rec.count();
    for (int var = 0; var < field_count; ++var) {
        l.append(rec.fieldName(var));
    }
    QHash<QString, QVariant> map = QHash<QString, QVariant>();
    while (q.next()) {
        for (int var = 0; var < field_count; ++var) {
            map.insert(l.at(var), q.value(rec.indexOf(l.at(var))));
        }
        listmap.append(map);
    }
    return listmap;
}

QList<QHash <QString, QVariant> > EntityManager::findAll(QString tblname) {
    QSqlQuery q = this->schema.data()->getQueryBuilder().data()->findAll(tblname);
    return this->convertQueryResult(q);
}

void EntityManager::resolveRelations(const QSharedPointer<Entity> &entity,
                                     const QHash<QString, QVariant> &map, const bool refresh) {
    auto props = entity.data()->getRelationProperties();
    auto iterator = props.constBegin();
    while (iterator != props.constEnd()) {
        const Relation r = iterator.key();
        const QMetaProperty property = iterator.value();
        switch (r.getType()) {
        case MANY_TO_ONE:
            if (map.contains(r.getPropertyName()) + "_id") {
                this->manyToOne(entity, property.read(entity.data()), property, refresh);
            }
            break;
        case MANY_TO_MANY:
            this->manyToMany(entity, r, property, refresh);
            break;
        case ONE_TO_MANY:
            this->oneToMany(entity, r, property, refresh);
            break;
        case ONE_TO_ONE:
            this->oneToOne(entity, r, property, refresh, property.read(entity.data()));
            break;
        }
        ++iterator;
    }
}

bool EntityManager::save(QSharedPointer<Entity> &entity,
                         const bool persistRelations) {
    if (entity.data()->getId() > -1) {
        return this->merge(entity, persistRelations);
    } else {
        return this->create(entity, persistRelations);
    }
}

qint64 EntityManager::findId(QSharedPointer<Entity> &entity) {
    qint64 r = -1;
    QSqlQuery q = this->schema.data()->getQueryBuilder().data()->findId(entity);
    this->db->select(q);
    if (q.next()) {
        r = q.value(0).toLongLong();
    }
    return r;
}

bool EntityManager::remove(QSharedPointer<Entity> &entity) {
    bool rc = false;
    QSqlQuery q = this->schema.data()->getQueryBuilder().data()->remove(entity);
    if (this->db->transaction(q)) {
        this->cache.remove(entity);
        entity.clear();
        rc = true;
    }
    return rc;
}

bool EntityManager::createTable(const QSharedPointer<Entity> &entity) {
    return this->schema.data()->getQueryBuilder().data()->createTable(entity);
}

qint8 EntityManager::count(const QSharedPointer<Entity> &entity,
                           bool ignoreID) {
    qint8 rc = -1;
    QSqlQuery q = this->schema.data()->getQueryBuilder().data()->count(entity,
                  ignoreID);
    this->db->select(q);
    if (q.next()) {
        rc = q.value(0).toInt();
    }
    return rc;
}

qint8 EntityManager::count(const QString &tableName) {
    qint8 rc = -1;
    QSqlQuery q = this->schema.data()->getQueryBuilder().data()->count(tableName);
    this->db->select(q);
    if (q.next()) {
        rc = q.value(0).toInt();
    }
    return rc;
}

void EntityManager::setConnectionNames(QStringList list) {
    EntityManager::connectionNames = list;
}
