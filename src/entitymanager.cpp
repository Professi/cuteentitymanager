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

QStringList EntityManager::getConnectionNames() {
    return EntityManager::connectionNames;
}

EntityManager::EntityManager(QSqlDatabase database) : QObject() {
    auto db = new Database(database);
    this->db = QSharedPointer<Database>(db);
    this->init();
}

EntityManager::EntityManager(const QString &databaseType, QString databasename ,
                             QString hostname,
                             QString username,
                             QString password, QString port) : QObject() {
    auto db = new Database(databaseType, this->createConnection(), hostname,
                           databasename, username,
                           password,
                           port.toInt());
    this->db = QSharedPointer<Database>(db);
    this->init();
}

void EntityManager::init() {
    auto schema = Database::getSchema(Database::getDatabaseType(
                                          this->db->getDatabase().driverName()), this->db);
    this->schema = QSharedPointer<Schema>(schema);
    this->schema->setTables(this->schema->getTableSchemas());
}

EntityManager::~EntityManager() {
    EntityManager::removeConnectionName(this->db->getConnectionName());
}

bool EntityManager::startup(QString version, QStringList toInitialize) {
    DatabaseMigration *dbm = new DatabaseMigration();
    QSharedPointer<Entity> ptrDbm = QSharedPointer<DatabaseMigration>(dbm);
    QHash<QString, QVariant> map = QHash<QString, QVariant>();
    bool ok = true;
    map.insert("version", version);
    if (!this->schema->getTableNames().contains(dbm->getTablename())) {
        this->createTable(ptrDbm, true);
    }
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
        this->schema->setTables(this->schema->getTableSchemas());
    }
    return ok;
}

bool EntityManager::executeQuery(const QString &query) {
    return this->db->transaction(query);
}

bool EntityManager::checkTable(const QSharedPointer<Entity> &entity) {
    bool rc = true;
    if (!this->schema->containsTable(entity->getTablename())
            && this->schema->getQueryBuilder()->createTable(entity)) {
        this->schema->getTableSchema(entity->getTablename(), true);
        rc = this->schema->getTables().contains(entity->getTablename());
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
    entity = this->findById(entity->getProperty(
                                entity->getPrimaryKey()).toLongLong(),
                            QString(entity->getClassname()));
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

QSharedPointer<Entity> EntityManager::findById(const qint64 &id,
        QSharedPointer<Entity> &e,
        const bool refresh) {
    QSharedPointer<Entity> r;
    if (!e.isNull() && (refresh
                        || !(r = this->cache.get(id, QString(e->getClassname()))))) {
        e->setId(id);
        auto map  = this->findByPk(id, e);
        r = this->convert(map, e->getClassname(), refresh);
    }
    return r;
}

QSharedPointer<Entity> EntityManager::findById(const qint64 &id,
        const QString &classname) {
    QSharedPointer<Entity> e = QSharedPointer<Entity>
                               (EntityInstanceFactory::createInstance(classname));
    return this->findById(id, e);
}

QSharedPointer<Entity> EntityManager::convert(const QHash<QString, QVariant>
        &map,
        const char *classname, const bool refresh) {
    auto e = EntityInstanceFactory::createInstance(
                 classname, map);
    auto ptr = QSharedPointer<Entity>(e);
    this->cache.insert(ptr);
    this->resolveRelations(ptr, map, refresh);
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
    if ((convertedId = id.toLongLong(&ok)) && ok && convertedId > -1) {
        QString className = EntityInstanceFactory::extractEntityType(
                                property.typeName());
        QSharedPointer<Entity> ptr = QSharedPointer<Entity>();
        if (refresh || !(this->cache.contains(convertedId, className)
                         && (ptr = this->cache.get(convertedId, className)) && ptr)) {
            ptr = this->findById(convertedId, className);
        }
        this->setProperty(entity, ptr, property);
    }
}

void EntityManager::oneToMany(const QSharedPointer<Entity> &entity,
                              const Relation &r,
                              const QMetaProperty &property, const bool refresh) {
    if (entity.data() && entity->getId() > -1) {
        auto e = QSharedPointer<Entity>(EntityInstanceFactory::createInstance(
                                            EntityInstanceFactory::extractEntityType(
                                                property.typeName())));
        if (e) {
            QSqlQuery q = this->schema->getQueryBuilder()->oneToMany(e->getTablename(),
                          this->schema->getQueryBuilder()->generateColumnNameID(r.getMappedBy()),
                          entity->getId());
            auto listMap = this->convertQueryResult(q);
            auto entities = this->convert(listMap, e->getClassname(), refresh);
            this->setListProperty(entity, entities, property);
        }
    }
}


void EntityManager::oneToOne(const QSharedPointer<Entity> &entity,
                             const Relation &r,
                             const QMetaProperty &property, const bool refresh,
                             const QVariant &id) {
    if (r.getMappedBy().isEmpty()) {
        this->manyToOne(entity, id, property);
    } else {
        auto e = QSharedPointer<Entity>(EntityInstanceFactory::createInstance(
                                            EntityInstanceFactory::extractEntityType(property.typeName())));
        if (e) {
            QSqlQuery q = this->schema->getQueryBuilder()->oneToMany(
                              e->getTablename(),
                              this->schema->getQueryBuilder()->generateColumnNameID(
                                  r.getMappedBy()),
                              entity->getProperty(entity->getPrimaryKey()).toLongLong(), 1);
            auto listMap = this->convertQueryResult(q);
            auto entities = this->convert(listMap, e->getClassname(), refresh);
            if (!entities.isEmpty()) {
                QSharedPointer<Entity> ptr = entities.at(0);
                this->setProperty(entity, ptr, property);
            }
        }
    }
}

bool EntityManager::canPersistRelation(const Relation &relation,
                                       const RelationType &r, const QVariant &var) const {
    return relation.getType() == r  && var.canConvert<QVariantList>();
}

void EntityManager::setListProperty(const QSharedPointer<Entity> &entity,
                                    QList<QSharedPointer<Entity> > &list,
                                    const QMetaProperty &property) const {
    QVariant var;
    var.setValue<QList<QSharedPointer<Entity>>>(list);
    property.write(entity.data(), var);
}

void EntityManager::addEntityToListProperty(const QSharedPointer<Entity>
        &entity, QSharedPointer<Entity> add, const QMetaProperty &property) {
    QVariant var = property.read(entity.data());
    if (!var.isNull() && var.canConvert<QList<QVariant>>()) {
        auto list = EntityInstanceFactory::castQVariantList(var);
        if (!list.contains(add)) {
            list.append(add);
            this->setListProperty(entity, list, property);
        }
    }
}

void EntityManager::setProperty(const QSharedPointer<Entity> &entity,
                                QSharedPointer<Entity> value,
                                const QMetaProperty &property) const {
    if (value && value->getProperty(value->getPrimaryKey()).toLongLong()
            > -1) {
        QVariant var;
        var.setValue<QSharedPointer<Entity>>(value);
        property.write(entity.data(), var);
    }
}

void EntityManager::savePrePersistedRelations(const QSharedPointer<Entity>
        &entity) {
    auto relations = entity->getRelationProperties();
    auto iterator = relations.constBegin();
    while (iterator != relations.constEnd()) {
        const Relation r = iterator.key();
        auto var = iterator.value().read(entity.data());
        if (!var.isNull()) {
            if (r.getType() == RelationType::MANY_TO_ONE) {
                auto e = EntityInstanceFactory::castQVariant(var);
                if (this->shouldBeSaved(e, r)) {
                    this->save(e);
                }
            } else if (r.getType() == RelationType::ONE_TO_ONE
                       && r.getMappedBy().isEmpty()) {
                auto entity =  EntityInstanceFactory::castQVariant(var);
                this->save(entity);
            }
        }
        ++iterator;
    }
}

void EntityManager::savePostPersistedRelations(const QSharedPointer<Entity>
        &entity) {
    auto relations = entity->getRelationProperties();
    auto iterator = relations.constBegin();
    while (iterator != relations.constEnd()) {
        const Relation r = iterator.key();
        auto var = iterator.value().read(entity.data());
        if (!var.isNull()) {
            if (this->canPersistRelation(r, RelationType::MANY_TO_MANY, var)) {
                this->persistManyToMany(entity, r, var);
            } else if (this->canPersistRelation(r, RelationType::ONE_TO_MANY, var)) {
                QList<QSharedPointer<Entity>> list = EntityInstanceFactory::castQVariantList(
                        var);
                for (int var = 0; var < list.size(); ++var) {
                    auto entity = list.at(var);
                    if (this->shouldBeSaved(entity, r)) {
                        this->save(entity);
                    }
                }
            } else if (r.getType() == RelationType::ONE_TO_ONE
                       && !r.getMappedBy().isEmpty()) {
                auto entity =  EntityInstanceFactory::castQVariant(var);
                this->save(entity);
            }
        }
        ++iterator;
    }
}

void EntityManager::persistMappedByRelation(const QList<QSharedPointer<Entity> >
        &list, QSqlQuery &q, const QSharedPointer<Entity> &entity,
        const QSharedPointer<Entity> &ptr, const Relation &r,
        const QString &tblName) {
    q.clear();
    QList<QSharedPointer<Entity>> saved = r.getCascadeType().contains(
            CascadeType::ALL)
                                          || r.getCascadeType().contains(CascadeType::MERGE)
                                          || r.getCascadeType().contains(CascadeType::PERSIST) ?
                                          this->saveRelationEntities(list,
                                                  r) : list;
    this->db->startTransaction();
    auto builder = this->schema->getQueryBuilder();
    q = builder->manyToManyInsert(tblName,
                                  builder->generateManyToManyColumnName(entity),
                                  builder->generateManyToManyColumnName(ptr));
    q.bindValue(0, entity->getProperty(entity->getPrimaryKey()));
    auto prop = this->mappedProperty(r, ptr);
    QSharedPointer<Entity> item;
    for (int var = 0; var < saved.size(); ++var) {
        item = list.at(var);
        if (item->getProperty(item->getPrimaryKey()).toLongLong() > -1) {
            q.bindValue(1, item->getProperty(ptr->getPrimaryKey()));
            q.exec();
            if (prop.isReadable()) {
                this->addEntityToListProperty(entity, ptr, prop);
            } else {
                qDebug() << "Query exec for many to many relation failed." <<
                         q.lastError().text();
                qDebug() << "Involved entities: " << entity->getClassname() <<
                         "(MainEntitiy) and "  << entity->getClassname();
                qDebug() << "Relation:" << r.getPropertyName();
            }
        }
    }
    if (!this->db->commitTransaction()) {
        this->db->rollbackTransaction();
    }
}


QMetaProperty EntityManager::mappedProperty(const Relation &r,
        const QSharedPointer<Entity> &foreignEntity) const {
    QMetaProperty prop;
    auto props = foreignEntity->getMetaProperties();
    if (!r.getMappedBy().isEmpty() && props.contains(r.getMappedBy())) {
        prop = props.value(r.getMappedBy());
    } else {
        auto relations = foreignEntity->getRelations();
        for (auto iterator = relations.constBegin(); iterator != relations.constEnd();
                ++iterator) {
            auto rel = iterator.value();
            if (rel.getMappedBy() == r.getPropertyName()) {
                prop = props.value(rel.getPropertyName());
                break;
            }
        }
    }
    return prop;
}

bool EntityManager::shouldBeSaved(QSharedPointer<Entity> &entity,
                                  const Relation &r) {
    return entity && (r.getCascadeType().contains(CascadeType::ALL)
                      || (entity->getProperty(entity->getPrimaryKey()) > -1
                          && r.getCascadeType().contains(CascadeType::MERGE))
                      || (entity->getProperty(entity->getPrimaryKey()) <= -1
                          && r.getCascadeType().contains(CascadeType::PERSIST)));
}

void EntityManager::removeRelations(const QSharedPointer<Entity> &entity) {
    auto props = entity->getRelationProperties();
    auto iterator = props.constBegin();
    while (iterator != props.constEnd()) {
        const Relation r = iterator.key();
        auto property = iterator.value();
        auto var = property.read(entity.data());
        if (r.getType() == RelationType::MANY_TO_MANY) {
            this->removeManyToManyEntityList(entity, r, var);
        } else if (r.getType() == RelationType::ONE_TO_MANY) {
            if (r.getCascadeType().contains(CascadeType::REMOVE)
                    || r.getCascadeType().contains(CascadeType::ALL)) {
                this->removeEntityList(var);
            } else {
                this->setNullOneToManyRelation(var, r);
            }
        }  else if (r.getType() == RelationType::MANY_TO_ONE
                    || r.getType() == RelationType::MANY_TO_ONE) {
            this->setNullEntityPropertyRelation(var, r);
        }
        ++iterator;
    }
}


void EntityManager::setNullOneToManyRelation(QVariant &var, const Relation &r) {
    if (!r.getMappedBy().isEmpty() && !var.isNull()
            && var.canConvert<QVariantList>()) {
        auto list = EntityInstanceFactory::castQVariantList(var);
        if (!list.isEmpty()) {
            auto metas = list.at(0)->getMetaProperties();
            if (metas.contains(r.getMappedBy())) {
                for (int var = 0; var < list.size(); ++var) {
                    auto entity = list.at(var);
                    this->setProperty(entity, QSharedPointer<Entity>(),
                                      metas.value(r.getMappedBy()));
                    this->save(entity);
                }
            }
        }
    }
}

void EntityManager::setNullEntityPropertyRelation(QVariant &var,
        const Relation &r) {
    if (r.getCascadeType().contains(CascadeType::REMOVE)
            || r.getCascadeType().contains(CascadeType::ALL)) {
        this->removeEntity(var);
    } else if (!r.getMappedBy().isEmpty() && !var.isNull()) {
        auto e = EntityInstanceFactory::castQVariant(var);
        auto metas = e->getMetaProperties();
        if (metas.contains(r.getMappedBy())) {
            this->setProperty(e, QSharedPointer<Entity>(), metas.value(r.getMappedBy()));
            this->save(e);
        }
    }
}


void EntityManager::removeEntity(QVariant &var) {
    if (!var.isNull()) {
        auto e = EntityInstanceFactory::castQVariant(var);
        this->remove(e);
    }
}

void EntityManager::removeEntityList(QVariant &var) {
    if (var.canConvert<QVariantList>()) {
        auto list = EntityInstanceFactory::castQVariantList(var);
        for (int var = 0; var < list.size(); ++var) {
            auto entity = list.at(var);
            this->remove(entity);
        }
    }
}

void EntityManager::removeManyToManyEntityList(const QSharedPointer<Entity> &e,
        const Relation &r,
        QVariant &var) {
    if (!var.isNull() && var.canConvert<QVariantList>()) {
        auto list = EntityInstanceFactory::castQVariantList(var);
        if (!list.isEmpty()) {
            auto builder = this->schema->getQueryBuilder();
            auto ptr = list.at(0);
            QString tblName = builder->generateManyToManyTableName(e, ptr);
            if (this->schema->getTables().contains(tblName)) {
                QSqlQuery q = builder->manyToManyDelete(
                                  tblName, builder->generateManyToManyColumnName(e),
                                  e->getProperty(e->getPrimaryKey()).toLongLong());
                bool refresh = r.getCascadeType().contains(CascadeType::REFRESH)
                               || r.getCascadeType().contains(CascadeType::ALL);
                bool remove = r.getCascadeType().contains(CascadeType::REMOVE)
                              || r.getCascadeType().contains(CascadeType::ALL);
                if (q.exec()) {
                    for (int var = 0; var < list.size(); ++var) {
                        auto entity = list.at(var);
                        if (remove) {
                            this->remove(entity);
                        } else if (refresh) {
                            /**
                              not really with good performance, alternatively iterate over relation attribute and delete pointer from list
                              **/
                            this->refresh(entity);
                        }
                    }
                }
            }
        }
    }
}

QList<QSharedPointer<Entity>> EntityManager::saveRelationEntities(
const QList<QSharedPointer<Entity> > &list, const Relation &r) {
    QList<QSharedPointer<Entity>> saved = QList<QSharedPointer<Entity>>();
    QSharedPointer<Entity> ptr;
    for (int var = 0; var < list.size(); ++var) {
        ptr = list.at(var);
        if (this->shouldBeSaved(ptr, r) && this->save(ptr)) {
            saved.append(ptr);
        }
    }
    return saved;
}

void EntityManager::persistManyToMany(const QSharedPointer<Entity> &entity,
                                      const Relation &r, QVariant &property) {
    Q_UNUSED(r)
    auto list = property.value<QList<QVariant>>();
    if (!list.isEmpty() && !(list.at(0).isNull())) {
        auto var = list.at(0);
        auto ptr = EntityInstanceFactory::castQVariant(var);
        auto builder = this->schema->getQueryBuilder();
        QString tblName = builder->generateManyToManyTableName(entity, ptr);
        if (this->schema->getTables().contains(tblName)) {
            QSqlQuery q = builder->manyToManyDelete(
                              tblName, builder->generateManyToManyColumnName(entity),
                              entity->getProperty(entity->getPrimaryKey()).toLongLong());
            if (this->db->transaction(q)) {
                auto nList = EntityInstanceFactory::castQVariantList(property);
                this->persistMappedByRelation(nList, q, entity, ptr, r, tblName);
            }
        } else {
            qDebug() << "MANY_TO_MANY Table " << tblName << " not exists";
        }
    }
}



void EntityManager::manyToMany(const QSharedPointer<Entity> &entity,
                               const QMetaProperty &property, const bool refresh) {
    QSharedPointer<Entity> secEntityPtr = QSharedPointer<Entity>
                                          (EntityInstanceFactory::createInstance(EntityInstanceFactory::extractEntityType(
                                                  QString(property.typeName()))));
    auto builder = this->schema->getQueryBuilder();
    if (secEntityPtr) {
        QString tblName = builder->generateManyToManyTableName(entity, secEntityPtr);
        if (this->schema->getTables().contains(tblName)) {
            QSqlQuery q = builder->manyToMany(tblName,
                                              builder->generateManyToManyColumnName(entity),
                                              entity->getProperty(entity->getPrimaryKey()).toLongLong());
            auto listMap = this->convertQueryResult(q);
            auto entities = QList<QSharedPointer<Entity> >();
            for (int var = 0; var < listMap.size(); ++var) {
                auto id = listMap.at(var).value(builder->generateManyToManyColumnName(
                                                    secEntityPtr));
                if (!refresh
                        && this->cache.contains(id.toLongLong(), secEntityPtr->getClassname())) {
                    entities.append(this->cache.get(id.toLongLong(), secEntityPtr->getClassname()));
                } else {
                    entities.append(this->findById(id.toLongLong(), secEntityPtr->getClassname()));
                }
            }
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
    return this->convert(maps, entity->getClassname());
}

/**
 * @todo should be an insert statement with many values
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
                           const bool persistRelations, const bool checkDuplicate) {
    bool rc = false;
    if (this->checkTable(entity) && !(checkDuplicate && this->count(entity) == 0)) {
        if (persistRelations) {
            this->savePrePersistedRelations(entity);
        }
        this->db->startTransaction();
        QList<QSqlQuery> q = this->schema->getQueryBuilder()->create(
                                 entity);
        bool first = true;
        for (int var = 0; var < q.size(); ++var) {
            auto query = q.at(var);
            rc = this->db->exec(query);
            if (!rc) {
                qDebug() << "Query failed:" << query.lastError().text() << " of class " <<
                         entity->getClassname();
                break;
            }
            if (first) {
                entity->setProperty(entity->getPrimaryKey(), query.lastInsertId());
                first = false;
            }
        }
        if (!rc || !this->db->commitTransaction()) {
            this->db->rollbackTransaction();
            entity->setId(-1);
            rc = false;
        } else {
            this->cache.insert(entity);
            if (persistRelations) {
                this->savePostPersistedRelations(entity);
            }
            rc = true;
        }
    }
    return rc;
}

bool EntityManager::merge(QSharedPointer<Entity> &entity, bool withRelations) {
    if (entity->getId() > -1 && this->count(entity) == 1) {
        if (withRelations) {
            this->savePrePersistedRelations(entity);
        }
        this->db->startTransaction();
        QList<QSqlQuery> q = this->schema->getQueryBuilder()->merge(
                                 entity);
        bool ok = true;
        for (int var = 0; var < q.size(); ++var) {
            auto query = q.at(var);
            ok = this->db->exec(query);
            if (!ok) {
                qDebug() << query.lastError().text();
                break;
            }
        }
        if (!ok || !this->db->commitTransaction()) {
            this->db->rollbackTransaction();
            return false;
        } else if (ok && withRelations) {
            this->savePostPersistedRelations(entity);
        }
    }
    return false;
}

QHash<QString, QVariant> EntityManager::findByPk(qint64 id,
        const QSharedPointer<Entity>
        &e) {
    QSqlQuery q = this->schema->getQueryBuilder()->find(id, e, 0,
                  e->getPrimaryKey());
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
    QSqlQuery q = this->schema->getQueryBuilder()->findByAttributes(
                      entity, ignoreID);
    return this->convertQueryResult(q);
}

QList<QHash <QString, QVariant> > EntityManager::findAllByAttributes(
    const QHash<QString, QVariant> &m, const QString &tblname, bool ignoreID) {
    QSqlQuery q = this->schema->getQueryBuilder()->findByAttributes(m,
                  tblname, ignoreID);
    return this->convertQueryResult(q);
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

QList<QHash <QString, QVariant> > EntityManager::findAll(
    const QSharedPointer<Entity> &e) {
    QSqlQuery q = this->schema->getQueryBuilder()->findAll(e);
    return this->convertQueryResult(q);
}

void EntityManager::resolveRelations(const QSharedPointer<Entity> &entity,
                                     const QHash<QString, QVariant> &map, const bool refresh) {
    auto props = entity->getRelationProperties();
    auto iterator = props.constBegin();
    while (iterator != props.constEnd()) {
        const Relation r = iterator.key();
        const QMetaProperty property = iterator.value();
        QString colName = this->schema->getQueryBuilder()->generateColumnNameID(
                              r.getPropertyName());
        switch (r.getType()) {
        case RelationType::MANY_TO_ONE:
            if (map.contains(colName)) {
                this->manyToOne(entity, map.value(colName), property, refresh);
            }
            break;
        case RelationType::MANY_TO_MANY:
            this->manyToMany(entity, property, refresh);
            break;
        case RelationType::ONE_TO_MANY:
            this->oneToMany(entity, r, property, refresh);
            break;
        case RelationType::ONE_TO_ONE:
            this->oneToOne(entity, r, property, refresh, map.value(colName));
            break;
        }
        ++iterator;
    }
}

bool EntityManager::save(QSharedPointer<Entity> &entity,
                         const bool persistRelations) {
    if (entity->getProperty(entity->getPrimaryKey()) > -1) {
        return this->merge(entity, persistRelations);
    } else {
        return this->create(entity, persistRelations);
    }
}

qint64 EntityManager::findId(QSharedPointer<Entity> &entity) {
    qint64 r = -1;
    QSqlQuery q = this->schema->getQueryBuilder()->findId(entity);
    this->db->select(q);
    if (q.next()) {
        r = q.value(0).toLongLong();
    }
    return r;
}

bool EntityManager::remove(QSharedPointer<Entity> &entity) {
    bool rc = false;
    this->db->startTransaction();
    this->removeRelations(entity);
    auto queries = this->schema->getQueryBuilder()->remove(entity);
    bool ok = true;
    for (int var = 0; var < queries.size(); ++var) {
        auto q = queries.at(var);
        if (!q.exec()) {
            this->db->rollbackTransaction();
            ok = false;
            break;
        }
    }
    if (ok && this->db->commitTransaction()) {
        this->cache.remove(entity);
        entity.clear();
        rc = true;
    }
    return rc;
}

bool EntityManager::removeAll(QString tblname) {
    return this->schema->getQueryBuilder()->removeAll(tblname).exec();
}

bool EntityManager::createTable(const QSharedPointer<Entity> &entity,
                                bool createRelationTables) {
    return this->schema->getQueryBuilder()->createTable(entity,
            createRelationTables);
}

qint8 EntityManager::count(const QSharedPointer<Entity> &entity,
                           bool ignoreID) {
    qint8 rc = -1;
    QSqlQuery q = this->schema->getQueryBuilder()->count(entity,
                  ignoreID);
    this->db->select(q);
    if (q.next()) {
        rc = q.value(0).toInt();
    }
    return rc;
}

qint8 EntityManager::count(const QString &tableName) {
    qint8 rc = -1;
    QSqlQuery q = this->schema->getQueryBuilder()->count(tableName);
    this->db->select(q);
    if (q.next()) {
        rc = q.value(0).toInt();
    }
    return rc;
}

void EntityManager::setConnectionNames(QStringList list) {
    EntityManager::connectionNames = list;
}
