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

#include <QVariantList>
#include <QHash>
#include <QDir>
#include "entitymanager.h"
#include "enums/databasetype.h"
#include "databasemigration.h"
#include "validators/validatorfactory.h"
#include "validators/validator.h"
#include "validators/validatorrule.h"
#include "entityinspector.h"

using namespace CuteEntityManager;

QStringList EntityManager::connectionNames = QStringList();

QHash<QString, EntityManager *> EntityManager::instances =
    QHash<QString, EntityManager *>();

QStringList EntityManager::getConnectionNames() {
    return EntityManager::connectionNames;
}

EntityManager::EntityManager(QSqlDatabase database, bool logQueries,
                             const bool inspectEntities,
                             MsgType logActions) : QObject() {
    this->db = QSharedPointer<Database>(new Database(database, true, logQueries, logActions));
    this->init(inspectEntities, logActions);
}

void EntityManager::init(bool inspect, const MsgType msgType) {
    EntityInstanceFactory::registerClass<DatabaseMigration>();
    this->schema = QSharedPointer<Schema>(Database::getSchema(Database::getDatabaseType(
            this->db->getDatabase().driverName()), this->db));
    this->schema->setTables(this->schema->getTableSchemas());
    this->queryInterpreter = QSharedPointer<QueryInterpreter>(new QueryInterpreter(
                                 this->schema->getQueryBuilder().data()));
    this->appendToInstanceList();
    if (inspect) {
        EntityInspector inspector = EntityInspector(msgType);
        inspector.checkRegisteredEntities();
    }
    QString loggerFile = this->objectName() + ".log";
    loggerFile.replace("[", "");
    loggerFile.replace("]", "");
    this->logger = QSharedPointer<Logger>(new Logger(QDir::currentPath() + "/" +
                                          loggerFile, msgType));
}

EntityManager::EntityManager(const QString &databaseType, QString databasename,
                             QString hostname, QString username, QString password, QString port,
                             bool logQueries, QString databaseOptions, const bool inspectEntities,
                             CuteEntityManager::MsgType logActions) : QObject() {
    this->db = QSharedPointer<Database>(new Database(databaseType, this->createConnection(),
                                        hostname,
                                        databasename, username,
                                        password,
                                        port.toInt(), true, logQueries, databaseOptions, logActions));
    this->init(inspectEntities, logActions);
}

EntityManager::~EntityManager() {
    EntityManager::removeConnectionName(this->db->getConnectionName());
    EntityManager::instances.remove(this->objectName());
}


QSharedPointer<QueryBuilder> EntityManager::getQueryBuilder() const {
    return this->schema->getQueryBuilder();
}

bool EntityManager::saveObject(QSharedPointer<Entity> &entity,
                               QList<Entity *> &mergedObjects, const bool persistRelations,
                               const bool ignoreHasChanged, const bool validate,
                               const bool relationsIgnoreHasChanged) {
    bool merged =  mergedObjects.contains(entity.data());
    if (entity && !merged && (ignoreHasChanged || this->hasChanged(entity))) {
        if (entity->getProperty(entity->getPrimaryKey()).toLongLong() > -1) {
            return this->mergeObject(entity, mergedObjects, persistRelations, validate,
                                     relationsIgnoreHasChanged);
        } else {
            return this->createObject(entity, mergedObjects, persistRelations, false,
                                      validate, relationsIgnoreHasChanged);
        }
    }
    return merged ? true : false;
}

bool EntityManager::mergeObject(QSharedPointer<Entity> &entity,
                                QList<Entity *> &mergedObjects, bool withRelations, const bool validate,
                                const bool relationsIgnoreHasChanged) {
    bool ok = true;
    if (entity && !mergedObjects.contains(entity.data())) {
        mergedObjects.append(entity.data());
        ok = false;
        if (entity->getId() > -1 && (!validate || this->validate(entity))) {
            if (withRelations) {
                this->savePrePersistedRelations(entity, mergedObjects,
                                                relationsIgnoreHasChanged);
            }
            this->db->startTransaction();
            QList<QSqlQuery> q = this->schema->getQueryBuilder()->merge(
                                     entity);
            ok = this->db->exec(q);
            if (!ok || !this->db->commitTransaction()) {
                this->db->rollbackTransaction();
                ok = false;
            } else if (ok && withRelations) {
                this->savePostPersistedRelations(entity, mergedObjects,
                                                 relationsIgnoreHasChanged);
            }
        }
    }
    return ok;
}

bool EntityManager::createObject(QSharedPointer<Entity> &entity,
                                 QList<Entity *> &mergedObjects, const bool persistRelations,
                                 const bool checkDuplicate, const bool validate,
                                 const bool relationsIgnoreHasChanged) {
    bool rc = true;
    if (entity && !mergedObjects.contains(entity.data())) {
        mergedObjects.append(entity.data());
        rc = false;
        if (this->checkTable(entity) && (!validate || this->validate(entity))
                && (!checkDuplicate || this->count(entity) <= 0)) {
            if (persistRelations) {
                this->savePrePersistedRelations(entity, mergedObjects,
                                                relationsIgnoreHasChanged);
            }
            this->db->startTransaction();
            QList<QSqlQuery> q = this->schema->getQueryBuilder()->create(
                                     entity);
            bool first = true;
            QVariant id = -1;
            for (int var = 0; var < q.size(); ++var) {
                auto query = q.at(var);
                if (!first) {
                    this->schema->getQueryBuilder()->bindValue(entity->getPrimaryKey(), id, query);
                }
                rc = this->db->exec(query);
                if (!rc) {
                    this->logger->logMsg("class is erroneous:" +  EntityHelper::getClassName(
                                             entity.data()), MsgType::WARNING);
                    break;
                }
                if (first) {
                    id = query.lastInsertId();
                    entity->setProperty(entity->getPrimaryKey(), id);
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
                    this->savePostPersistedRelations(entity, mergedObjects,
                                                     relationsIgnoreHasChanged, true);
                }
                rc = true;
            }
        }
        entity->idChanged();
    }
    return rc;
}


bool EntityManager::merge(QSharedPointer<Entity> &entity, bool withRelations,
                          const bool validate, const bool relationsIgnoreHasChanged) {
    auto merged = QList<Entity *>();
    return this->mergeObject(entity, merged, withRelations, validate,
                             relationsIgnoreHasChanged);
}

bool EntityManager::create(QSharedPointer<Entity> &entity,
                           const bool persistRelations, const bool checkDuplicate, const bool validate,
                           const bool relationsIgnoreHasChanged) {
    auto merged = QList<Entity *>();
    return this->createObject(entity, merged, persistRelations,
                              checkDuplicate, validate, relationsIgnoreHasChanged);
}

bool EntityManager::create(QList<QSharedPointer<Entity>> &entities,
                           const bool persistRelations, const bool checkDuplicate, const bool validate,
                           const bool relationsIgnoreHasChanged) {
    bool ok = true;
    auto merged = QList<Entity *>();
    foreach (QSharedPointer<Entity> ent, entities) {
        this->createObject(ent, merged, persistRelations,
                           checkDuplicate, validate, relationsIgnoreHasChanged);
    }
    return ok;
}

bool EntityManager::save(QSharedPointer<Entity> &entity,
                         const bool persistRelations, const bool ignoreHasChanged, const bool validate,
                         const bool relationsIgnoreHasChanged) {
    auto merged = QList<Entity *>();
    return this->saveObject(entity, merged, persistRelations,
                            ignoreHasChanged, validate, relationsIgnoreHasChanged);
}

bool EntityManager::save(QList<QSharedPointer<Entity>> &entities,
                         const bool persistRelations, const bool ignoreHasChanged, const bool validate,
                         const bool relationsIgnoreHasChanged) {
    bool ok = true;
    auto merged = QList<Entity *>();
    foreach (QSharedPointer<Entity> entity, entities) {
        ok = this->saveObject(entity, merged, persistRelations,
                              ignoreHasChanged, validate, relationsIgnoreHasChanged);
        if (!ok) {
            break;
            /**
              * @todo error handling
              */
        }
    }
    return ok;
}

bool EntityManager::startup(QString version, QStringList toInitialize,
                            bool createIndices) {
    QSharedPointer<Entity> dbm = QSharedPointer<DatabaseMigration>
                                 (new DatabaseMigration());
    QHash<QString, QVariant> map = QHash<QString, QVariant>();
    bool ok = true;
    map.insert("version", version);
    if (!this->schema->getTableNames().contains(dbm->getTablename())) {
        this->createTable(dbm, true);
    }
    if (this->findAllByAttributes(map, dbm->getTablename()).isEmpty()) {
        QList<QSharedPointer<Entity>> entities = QList<QSharedPointer<Entity>>();
        for (int var = 0; var < toInitialize.size(); ++var) {
            if (ok) {
                QString c = toInitialize.at(var);
                auto entity = QSharedPointer<Entity>
                              (EntityInstanceFactory::createInstance(c));
                ok = this->createTable(entity, false);
                entities.append(entity);
            } else {
                this->logger->logMsg("startup of version " + version + " failed",
                                     MsgType::CRITICAL);
                this->logger->logMsg( "erroneous entity:" + (var == 0 ?
                                      "null, this should not happen!" : toInitialize.at(var - 1)), MsgType::CRITICAL);
                break;
            }
        }
        if (ok) {
            for (int i = 0; i < entities.size(); ++i) {
                ok = this->schema->getQueryBuilder()->createRelationTables(entities.at(i));
                if (!ok) {
                    break;
                }
            }
        }
        if (ok && createIndices) {
            for (int i = 0; i < entities.size(); ++i) {
                ok = this->schema->getQueryBuilder()->createIndices(entities.at(i));
                if (!ok) {
                    break;
                }
            }
        }
        if (ok) {
            auto dbmPtr = dbm.objectCast<DatabaseMigration>();
            dbmPtr->setVersion(version);
            dbmPtr->setApplyTime(QDateTime::currentDateTime());
            this->create(dbm);
        }
        this->schema->setTables(this->schema->getTableSchemas());
    }
    return ok;
}

bool EntityManager::executeQuery(const QString &query) {
    return this->db->exec(query);
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
    if(entity) {
        auto map  = this->findByPk(entity->getId(), entity);
        this->convert(map, entity, true);
    }
}

QList<QHash<QString, QVariant>> EntityManager::selectByQuery(Query &query) {
    QSqlQuery q = this->queryInterpreter->build(query);
    return this->convertQueryResult(q);
}

QList<QHash<QString, QVariant>> EntityManager::selectBySql(
const QString &sql) {
    QSqlQuery q = this->db->select(sql);
    return this->convertQueryResult(q);
}

bool EntityManager::validate(QSharedPointer<Entity> &entity) {
    QList<ValidationRule> rules = entity->validationRules();
    QList<ErrorMsg> list = QList<ErrorMsg>();
    for (int i = 0; i < rules.size(); ++i) {
        ValidationRule rule = rules.at(i);
        QSharedPointer<Validator> validator = ValidatorFactory::getValidatorObject(
                rule.getValidatorName());
        if (validator) {
            for (int var = 0; var < rule.getAttributes().size(); ++var) {
                QString attr = rule.getAttributes().at(var);
                QList<ErrorMsg> msgs = validator->validate(entity->getProperty(attr),
                                       rule.getParams());
                for (int i = 0; i < msgs.size(); ++i) {
                    QString emsg = msgs.at(i).getErrorMsg().replace("<property>", attr);
                    ErrorMsg m = msgs.at(i);
                    m.setErrorMsg(emsg);
                    list.append(m);
                }
            }
        }
    }
    entity->setErrors(list);
    return !entity->hasErrors();
}

bool EntityManager::hasChanged(QSharedPointer<Entity> &entity) {
    bool changed = true;
    if (entity && entity->getId() > -1) {
        changed = false;
        auto listmap = this->findByPk(entity->getId(), entity);
        auto relations = entity->getRelations();
        QStringList rels = QStringList();
        for (auto i = relations.constBegin(); i != relations.constEnd(); ++i) {
            if (i.value().getType() == RelationType::MANY_TO_ONE
                    || (i.value().getType() == RelationType::ONE_TO_ONE
                        && i.value().getMappedBy().isEmpty())) {
                rels.append(this->schema->getQueryBuilder()->generateColumnNameID(i.key()));
            }
        }
        for (auto i = listmap.constBegin(); i != listmap.constEnd(); ++i) {
            if (rels.contains(i.key())) {
                QString appendix =
                    this->schema->getQueryBuilder()->columnNameIDAppendix();
                QString relKey = i.key();
                QVariant v = entity->getProperty(relKey.remove(relKey.size() - appendix.size(),
                                                 appendix.size()));
                if (!v.isNull() && v.data()) {
                    auto e = EntityInstanceFactory::castQVariant(v);
                    if (e && e->getProperty(e->getPrimaryKey()) != i.value()) {
                        changed = true;
                        break;
                    }
                }
            } else {
                QVariant property = entity->getProperty(i.key());
                changed = i.value() != property;
                if (changed) {
                    break;
                }
            }
        }
    }
    return changed;
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
    if (e && (refresh
              || !(r = this->cache.get(id, EntityHelper::getClassname(e.data()))))) {
        auto map  = this->findByPk(id, e);
        r = this->convert(map, EntityHelper::getClassname(e.data()), refresh);
    }
    return r;
}

QSharedPointer<Entity> EntityManager::findById(const qint64 &id,
        const QString &classname) {
    QSharedPointer<Entity> e = QSharedPointer<Entity>
                               (EntityInstanceFactory::createInstance(classname));
    return this->findById(id, e);
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
        EntityHelper::setProperty(entity, ptr, property);
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
            auto entities = this->convert(listMap, EntityHelper::getClassname(e.data()),
                                          refresh);
            EntityHelper::setListProperty(entity, entities, property);
        }
    }
}


void EntityManager::oneToOne(const QSharedPointer<Entity> &entity,
                             const Relation &r, const QMetaProperty &property, const bool refresh,
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
            auto entities = this->convert(listMap, EntityHelper::getClassname(e.data()),
                                          refresh);
            if (!entities.isEmpty()) {
                QSharedPointer<Entity> ptr = entities.at(0);
                EntityHelper::setProperty(entity, ptr, property);
            }
        }
    }
}

void EntityManager::savePrePersistedRelations(const QSharedPointer<Entity>
        &entity, QList<Entity *> &mergedObjects, bool ignoreHasChanged) {
    auto relations = EntityHelper::getRelationProperties(entity.data());
    auto iterator = relations.constBegin();
    while (iterator != relations.constEnd()) {
        const Relation r = iterator.key();
        auto var = iterator.value().read(entity.data());
        if (r.getType() == RelationType::MANY_TO_ONE) {
            auto e = EntityInstanceFactory::castQVariant(var);
            if (this->shouldBeSaved(e, r)) {
                this->saveObject(e, mergedObjects, true, ignoreHasChanged);
                auto fkProp = EntityHelper::mappedProperty(r, e);
                if (e && fkProp.isValid()) {
                    EntityHelper::addEntityToListProperty(e, entity, fkProp);
                }
            }
        } else if (r.getType() == RelationType::ONE_TO_ONE
                   && r.getMappedBy().isEmpty()) {
            auto e =  EntityInstanceFactory::castQVariant(var);
            this->saveObject(e, mergedObjects, true, ignoreHasChanged);
            auto prop = EntityHelper::mappedProperty(r, e);
            EntityHelper::setProperty(e, entity, prop);
        }
        ++iterator;
    }
}

void EntityManager::savePostPersistedRelations(const QSharedPointer<Entity>
        &entity, QList<Entity *> &mergedObjects, bool ignoreHasChanged, bool newItem) {
    auto relations = EntityHelper::getRelationProperties(entity.data());
    for (auto i = relations.constBegin(); i != relations.constEnd(); ++i) {
        const Relation r = i.key();
        auto var = i.value().read(entity.data());
        if (r.getType() == RelationType::MANY_TO_MANY) {
            this->persistManyToMany(entity, r, var, mergedObjects, ignoreHasChanged,
                                    newItem);
        } else if (r.getType() == RelationType::ONE_TO_MANY) {
            QList<QSharedPointer<Entity>> list = EntityInstanceFactory::castQVariantList(
                    var);
            if (!list.isEmpty()) {
                auto fkProp = EntityHelper::mappedProperty(r, list.at(0));
                for (int var = 0; var < list.size(); ++var) {
                    auto e = list.at(var);
                    if (this->shouldBeSaved(e, r) && e) {
                        EntityHelper::setProperty(e, entity, fkProp);
                        this->saveObject(e, mergedObjects, true, ignoreHasChanged);
                    }
                }
            }
        } else if (r.getType() == RelationType::ONE_TO_ONE
                   && !r.getMappedBy().isEmpty()) {
            auto e =  EntityInstanceFactory::castQVariant(var);
            if(e) {
                auto fkProp = EntityHelper::mappedProperty(r, e);
                EntityHelper::setProperty(e, entity, fkProp);
                this->saveObject(e, mergedObjects, true, ignoreHasChanged);
            }
        }
    }
}

void EntityManager::persistMappedByRelation(const QList<QSharedPointer<Entity>>
        &list, QSqlQuery &q, const QSharedPointer<Entity> &entity,
        const QSharedPointer<Entity> &ptr, const Relation &r,
        const QString &tblName, QList<Entity *> &mergedObjects) {
    q.clear();
    QList<QSharedPointer<Entity>> saved =
                                   r.getCascadeType().contains(CascadeType::ALL) ||
                                   r.getCascadeType().contains(CascadeType::MERGE) ||
                                   r.getCascadeType().contains(CascadeType::PERSIST) ?
                                   this->saveRelationEntities(list, r, mergedObjects) : list;
    this->db->startTransaction();
    auto builder = this->schema->getQueryBuilder();
    q = builder->manyToManyInsert(tblName,
                                  builder->generateManyToManyColumnName(entity),
                                  builder->generateManyToManyColumnName(ptr));
    q.bindValue(0, entity->getProperty(entity->getPrimaryKey()));
    auto prop = EntityHelper::mappedProperty(r, ptr);
    QSharedPointer<Entity> item;
    for (int var = 0; var < saved.size(); ++var) {
        item = list.at(var);
        if (item->getProperty(item->getPrimaryKey()).toLongLong() > -1) {
            q.bindValue(1, item->getProperty(ptr->getPrimaryKey()));
            bool ok = this->db->exec(q);
            if (ok) {
                EntityHelper::addEntityToListProperty(item, entity, prop);
            }
        }
    }
    if (!this->db->commitTransaction()) {
        this->db->rollbackTransaction();
    }
}

QString EntityManager::generateObjectName() {
    int i = 0;
    QString name = "em[";
    while (true) {
        if (!EntityManager::instances.contains(name + QString::number(i) + "]")) {
            name += QString::number(i) + "]";
            break;
        }
    }
    return name;
}

void EntityManager::appendToInstanceList() {
    this->setObjectName(this->generateObjectName());
    EntityManager::instances.insert(this->objectName(), this);
}

QHash<QString, EntityManager *> EntityManager::getInstances() {
    return instances;
}

EntityManager *EntityManager::getDefaultInstance() {
    auto keys = EntityManager::instances.uniqueKeys();
    if(!keys.isEmpty()) {
        return EntityManager::instances.value(keys.first());
    }
    return nullptr;
}

EntityManager *EntityManager::getInstance(QString name) {
    if (EntityManager::instances.contains(name)) {
        return EntityManager::instances.value(name);
    }
    return nullptr;
}


bool EntityManager::shouldBeSaved(QSharedPointer<Entity> &entity,
                                  const Relation &r) {
    return r.getCascadeType().contains(CascadeType::ALL)
           || ((!entity || entity->getProperty(entity->getPrimaryKey()) > -1)
               && r.getCascadeType().contains(CascadeType::MERGE))
           || ((!entity || entity->getProperty(entity->getPrimaryKey()) <= -1)
               && r.getCascadeType().contains(CascadeType::PERSIST));
}

void EntityManager::removeRelations(const QSharedPointer<Entity> &entity) {
    auto props = EntityHelper::getRelationProperties(entity.data());
    for (auto i = props.constBegin(); i != props.constEnd(); ++i) {
        const Relation r = i.key();
        auto property = i.value();
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
    }
}


void EntityManager::setNullOneToManyRelation(QVariant &var, const Relation &r) {
    if (!r.getMappedBy().isEmpty() && !var.isNull()
            && var.canConvert<QVariantList>()) {
        auto list = EntityInstanceFactory::castQVariantList(var);
        if (!list.isEmpty()) {
            auto metas = EntityHelper::getMetaProperties(list.at(0).data());
            if (metas.contains(r.getMappedBy())) {
                for (int var = 0; var < list.size(); ++var) {
                    auto entity = list.at(var);
                    EntityHelper::setProperty(entity, QSharedPointer<Entity>(),
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
    } else if (!r.getMappedBy().isEmpty() && var.data()) {
        auto e = EntityInstanceFactory::castQVariant(var);
        auto metas = EntityHelper::getMetaProperties(e.data());
        if (metas.contains(r.getMappedBy())) {
            EntityHelper::setProperty(e, QSharedPointer<Entity>(),
                                      metas.value(r.getMappedBy()));
            this->save(e);
        }
    }
}

void EntityManager::removeEntity(QVariant &var) {
    if (var.data()) {
        auto e = EntityInstanceFactory::castQVariant(var);
        if(e) {
            this->remove(e);
        }
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
            QString tblName = builder->generateManyToManyTableName(e, ptr, r);
            if (this->schema->getTables().contains(tblName)) {
                QSqlQuery q = builder->manyToManyDelete(
                                  tblName, builder->generateManyToManyColumnName(e),
                                  e->getProperty(e->getPrimaryKey()).toLongLong());
                if (this->db->exec(q)) {
                    bool refresh = r.getCascadeType().contains(CascadeType::REFRESH)
                                   || r.getCascadeType().contains(CascadeType::ALL);
                    bool remove = r.getCascadeType().contains(CascadeType::REMOVE)
                                  || r.getCascadeType().contains(CascadeType::ALL);
                    auto fkProp = EntityHelper::mappedProperty(r, ptr);
                    for (int var = 0; var < list.size(); ++var) {
                        auto entity = list.at(var);
                        if (remove) {
                            this->remove(entity);
                        } else if (refresh) {
                            EntityHelper::removeEntityFromListProperty(entity, e, fkProp);
                        }
                    }
                }
            }
        }
    }
}

QList<QSharedPointer<Entity>> EntityManager::saveRelationEntities(
                               const QList<QSharedPointer<Entity>> &list, const Relation &r,
QList<Entity *> &mergedObjects) {
    QList<QSharedPointer<Entity>> saved = QList<QSharedPointer<Entity>>();
    QSharedPointer<Entity> ptr;
    for (int var = 0; var < list.size(); ++var) {
        ptr = list.at(var);
        if ((this->shouldBeSaved(ptr, r) && this->saveObject(ptr, mergedObjects))
                || ptr->getProperty(ptr->getPrimaryKey()).toLongLong() > -1) {
            saved.append(ptr);
        }
    }
    return saved;
}

void EntityManager::persistManyToMany(const QSharedPointer<Entity> &entity,
                                      const Relation &r, QVariant &property, QList<Entity *> &mergedObjects,
                                      const bool ignoreHasChanged, const bool newItem) {
    auto list = property.value<QList<QVariant>>();
    auto ptr = QSharedPointer<Entity>(EntityInstanceFactory::createInstance(
                                          EntityInstanceFactory::extractEntityType(QString(property.typeName()))));
    auto builder = this->schema->getQueryBuilder();
    QString tblName = builder->generateManyToManyTableName(entity, ptr, r);
    if (this->schema->containsTable(tblName)) {
        bool ok = newItem;
        QSqlQuery q;
        if (!newItem) {
            /**
              * @todo diff and remove entity from relational object when association is deleted
              */
            q = builder->manyToManyDelete(
                    tblName, builder->generateManyToManyColumnName(entity),
                    entity->getProperty(entity->getPrimaryKey()).toLongLong());
            ok = this->db->exec(q);
        } else {
            q = builder->getQuery();
        }
        if (ok && !list.isEmpty() && list.at(0).data()) {
            auto nList = EntityInstanceFactory::castQVariantList(property);
            this->persistMappedByRelation(nList, q, entity, ptr, r, tblName, mergedObjects);
        }
    } else {
        this->missingManyToManyTable(tblName, entity, r);
    }
}

void EntityManager::missingManyToManyTable(const QString &tblName,
        const QSharedPointer<Entity> &e, const Relation &r) {
    this->logger->logMsg("MANY_TO_MANY Table " + tblName + " is missing.\n" +
                         "Entity " + EntityHelper::getClassName(e.data()) +
                         " is affected.\n" + "Relation of property: " + r.getPropertyName(),
                         MsgType::CRITICAL);
}

void EntityManager::manyToMany(const QSharedPointer<Entity> &entity,
                               const QMetaProperty &property, const Relation &relation, const bool refresh) {
    QSharedPointer<Entity> secEntityPtr = QSharedPointer<Entity>
                                          (EntityInstanceFactory::createInstance(EntityInstanceFactory::extractEntityType(
                                                  QString(property.typeName()))));
    auto builder = this->schema->getQueryBuilder();
    EntityHelper::clearEntityListProperty(entity, property);
    if (secEntityPtr) {
        QString tblName = builder->generateManyToManyTableName(entity, secEntityPtr,
                          relation);
        if (this->schema->getTables().contains(tblName)) {
            QSqlQuery q = builder->manyToMany(tblName,
                                              builder->generateManyToManyColumnName(entity),
                                              entity->getProperty(entity->getPrimaryKey()).toLongLong());
            auto listMap = this->convertQueryResult(q);
            QSharedPointer<Entity> e = QSharedPointer<Entity>();
            for (int var = 0; var < listMap.size(); ++var) {
                auto id = listMap.at(var).value(builder->generateManyToManyColumnName(
                                                    secEntityPtr));
                if (!refresh
                        && this->cache.contains(id.toLongLong(),
                                                EntityHelper::getClassname(secEntityPtr.data()))) {
                    e = this->cache.get(id.toLongLong(),
                                        EntityHelper::getClassname(secEntityPtr.data()));
                } else {
                    e = this->findById(id.toLongLong(),
                                       EntityHelper::getClassname(secEntityPtr.data()));
                }
                if (e) {
                    EntityHelper::addEntityToListProperty(entity, e, property);
                }
            }
        } else {
            this->missingManyToManyTable(tblName, entity, relation);
        }
    }
}

QList<QSharedPointer<Entity>> EntityManager::findEntityByAttributes(
                               const QSharedPointer<Entity>
                               &entity,
bool ignoreID) {
    auto maps = this->findAllByAttributes(entity, ignoreID);
    return this->convert(maps, EntityHelper::getClassname(entity.data()));
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


QList<QHash<QString, QVariant>> EntityManager::findAllByAttributes(
                                 const QSharedPointer<Entity>
                                 &entity,
bool ignoreID) {
    QSqlQuery q = this->schema->getQueryBuilder()->findByAttributes(
                      entity, ignoreID);
    return this->convertQueryResult(q);
}

QList<QHash <QString, QVariant>> EntityManager::findAllByAttributes(
const QHash<QString, QVariant> &m, const QString &tblname, bool ignoreID) {
    QSqlQuery q = this->schema->getQueryBuilder()->findByAttributes(m,
                  tblname, ignoreID);
    return this->convertQueryResult(q);
}

QList<QHash<QString, QVariant>> EntityManager::convertQueryResult(
QSqlQuery &q) {
    QList<QHash <QString, QVariant>> listmap = QList<QHash <QString, QVariant>>();
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

QList<QHash <QString, QVariant>> EntityManager::findAll(
const QSharedPointer<Entity> &e) {
    QSqlQuery q = this->schema->getQueryBuilder()->findAll(e);
    return this->convertQueryResult(q);
}

void EntityManager::resolveRelations(const QSharedPointer<Entity> &entity,
                                     const QHash<QString, QVariant> &map, const bool refresh) {
    auto props = EntityHelper::getRelationProperties(entity.data());
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
            this->manyToMany(entity, property, r, refresh);
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
    bool ok = this->db->exec(queries);
    if (ok && this->db->commitTransaction()) {
        this->cache.remove(entity);
        entity.clear();
        rc = true;
    } else {
        this->db->rollbackTransaction();
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

bool EntityManager::createTable(QString className, bool createRelationTables) {
    QSharedPointer<Entity> e = QSharedPointer<Entity>
                               (EntityInstanceFactory::createInstance(className));
    return this->schema->getQueryBuilder()->createTable(e, createRelationTables);
}

bool EntityManager::removeTable(QString className) {
    return this->executeQuery(this->schema->getQueryBuilder()->dropTable(className));
}

quint8 EntityManager::count(const QSharedPointer<Entity> &entity, bool ignoreID,
                            bool followInheritance) {
    Query q = Query();
    auto qb = this->schema->getQueryBuilder();
    QHash<QString, QVariant> values;
    if (followInheritance) {
        q.appendJoins(qb->joinBaseClasses(entity));
        values = EntityHelper::getEntityAttributes(EntityHelper::getMetaProperties(
                     entity.data()), entity);
    } else {
        values = EntityHelper::getEntityAttributes(
                     EntityHelper::getNonInheritedMetaProperties(entity.data()), entity);
    }
    //maybe filter MANY_TO_MANY and ONE_TO_MANY relations
    q.appendFrom(entity->getTablename());
    q.appendWhere(qb->where(values, qb->andKeyword(), ignoreID,
                            entity->getPrimaryKey(), false));
    q.appendParams(values);
    return this->count(q);
}

quint8 EntityManager::count(const QString &tableName) {
    qint8 rc = -1;
    QSqlQuery q = this->schema->getQueryBuilder()->count(tableName);
    this->db->select(q);
    if (q.next()) {
        rc = q.value(0).toInt();
    }
    return rc;
}

qint8 EntityManager::count(Query &query) {
    qint8 rc = 0;
    query.appendSelect("COUNT(*)");
    QSqlQuery q = this->queryInterpreter->build(query);
    this->db->select(q);
    if (q.next()) {
        rc = q.value(0).toInt();
    }
    return rc;
}

void EntityManager::setConnectionNames(QStringList list) {
    EntityManager::connectionNames = list;
}

QSharedPointer<Entity> EntityManager::convert(const QHash<QString, QVariant>
        &map,
        const char *classname, const bool refresh, const bool resolveRelations) {
    auto ptr = QSharedPointer<Entity>(EntityInstanceFactory::createInstance(
                                          classname, map));
    this->cache.insert(ptr);
    if (resolveRelations) {
        this->resolveRelations(ptr, map, refresh);
    }
    return ptr;
}

void EntityManager::convert(const QHash<QString, QVariant> &map,
                            QSharedPointer<Entity> &entity, const bool refresh, const bool resolveRelations) {
    this->cache.insert(entity);
    auto data = entity.data();
    EntityInstanceFactory::setAttributes(data, map);
    if (resolveRelations) {
        this->resolveRelations(entity, map, refresh);
    }
}

QList<QSharedPointer<Entity>> EntityManager::convert(
                               QList<QHash<QString, QVariant>> maps,
const char *classname, const bool refresh, const bool resolveRelations) {
    auto list = QList<QSharedPointer<Entity>>();
    for (int var = 0; var < maps.size(); ++var) {
        auto ptr = this->convert(maps.at(var), classname, refresh, resolveRelations);
        list.append(ptr);
        this->cache.insert(ptr);
    }
    return list;
}
