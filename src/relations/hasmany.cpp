#include "hasmany.h"
#include "entityinstancefactory.h"
#include "entityhelper.h"
#include "database.h"
#include "resolver.h"
using namespace CuteEntityManager;

HasMany::HasMany(const QSharedPointer<Entity> &entity, const Relation &r, const QSharedPointer<Schema> schema)
{
    this->entity = entity;
    this->relation = r;
    this->schema = schema;
}

void HasMany::persist(
        QVariant &property, QList<Entity *> &mergedObjects,
        const bool newItem, EntityManager *em) {
    auto list = property.value<QList<QVariant>>();
    auto ptr = QSharedPointer<Entity>(EntityInstanceFactory::createInstance(
                                          EntityInstanceFactory::extractEntityType(QString(property.typeName()))));
    auto builder = this->schema->getQueryBuilder();
    QString tblName = builder->generateManyToManyTableName(this->entity, ptr, this->relation);
    if (this->schema->containsTable(tblName)) {
        bool ok = newItem;
        QSqlQuery q;
        if (!newItem) {
            /**
              * @todo diff and remove entity from relational object when association is deleted
              */
            q = builder->manyToManyDelete(
                        tblName, builder->generateManyToManyColumnName(this->entity, this->relation.getPropertyName()),
                        this->entity->getProperty(this->entity->getPrimaryKey()).toLongLong());
            ok = this->schema->getDatabase()->exec(q);
        } else {
            q = builder->getQuery();
        }
        if (ok && !list.isEmpty() && list.at(0).data()) {
            auto nList = EntityInstanceFactory::castQVariantList(property);
            QList<QSharedPointer<Entity>> saved =
                    this->relation.getCascadeType().contains(CascadeType::ALL) ||
                    this->relation.getCascadeType().contains(CascadeType::MERGE) ||
                    this->relation.getCascadeType().contains(CascadeType::PERSIST) ?
                        em->saveRelationEntities(nList, this->relation, mergedObjects) : nList;
            this->persistMappedByRelation(saved, q, this->entity, ptr, this->relation, tblName);
        }
    } else {
        this->missingTable(tblName);
    }
}

void HasMany::missingTable(const QString &tblName) {
    QString text = "MANY_TO_MANY Table " + tblName + " is missing.\n" +
            "Entity " + EntityHelper::getClassName(this->entity.data()) +
            " is affected.\n" + "Relation of property: " + this->relation.getPropertyName();
    throw QString(text);
}

void HasMany::persistMappedByRelation(const QList<QSharedPointer<Entity>>
                                      &list, QSqlQuery &q, const QSharedPointer<Entity> &entity,
                                      const QSharedPointer<Entity> &ptr, const Relation &r,
                                      const QString &tblName) {
    q.clear();
    this->schema->getDatabase()->startTransaction();
    auto builder = this->schema->getQueryBuilder();
    q = builder->manyToManyInsert(tblName,
                                  builder->generateManyToManyColumnName(entity, r.getPropertyName()),
                                  builder->generateManyToManyColumnName(ptr, r.getMappedBy()));
    q.bindValue(0, entity->getProperty(entity->getPrimaryKey()));
    auto prop = EntityHelper::mappedProperty(r, ptr);
    QSharedPointer<Entity> item;
    for (int var = 0; var < list.size(); ++var) {
        item = list.at(var);
        if (item->getProperty(item->getPrimaryKey()).toLongLong() > -1) {
            q.bindValue(1, item->getProperty(ptr->getPrimaryKey()));
            bool ok = this->schema->getDatabase()->exec(q);
            if (ok) {
                EntityHelper::addEntityToListProperty(item, entity, prop);
            }
        }
    }
    if (!this->schema->getDatabase()->commitTransaction()) {
        this->schema->getDatabase()->rollbackTransaction();
    }
}

void HasMany::removeEntityList(QVariant &var, EntityManager *em) {
    if (!var.isNull() && var.canConvert<QVariantList>()) {
        auto list = EntityInstanceFactory::castQVariantList(var);
        if (!list.isEmpty()) {
            auto builder = this->schema->getQueryBuilder();
            auto ptr = list.at(0);
            QString tblName = builder->generateManyToManyTableName(this->entity, ptr, this->relation);
            if (this->schema->getTables().contains(tblName)) {
                QSqlQuery q = builder->manyToManyDelete(
                            tblName, builder->generateManyToManyColumnName(this->entity, this->relation.getPropertyName()),
                            this->entity->getProperty(this->entity->getPrimaryKey()).toLongLong());
                if (this->schema->getDatabase()->exec(q)) {
                    bool refresh = this->relation.getCascadeType().contains(CascadeType::REFRESH)
                            || this->relation.getCascadeType().contains(CascadeType::ALL);
                    bool remove = this->relation.getCascadeType().contains(CascadeType::REMOVE)
                            || this->relation.getCascadeType().contains(CascadeType::ALL);
                    auto fkProp = EntityHelper::mappedProperty(this->relation, ptr);
                    for (int var = 0; var < list.size(); ++var) {
                        auto removeEntity = list.at(var);
                        if (remove) {
                            em->remove(removeEntity);
                        } else if (refresh) {
                            EntityHelper::removeEntityFromListProperty(removeEntity, this->entity, fkProp);
                        }
                    }
                }
            }
        }
    }
}

void HasMany::resolve(const QSharedPointer<Entity> &entity,
                      Attribute *&attr, Cache &cache, EntityManager *em) {
    QSharedPointer<Entity> secEntityPtr = QSharedPointer<Entity>
            (EntityInstanceFactory::createInstance(attr->getRelatedClass()->className()));
    auto builder = this->schema->getQueryBuilder();
    EntityHelper::clearEntityListProperty(entity, attr->getMetaProperty());
    if (secEntityPtr) {
        if (this->schema->getTables().contains(attr->getTableName())) {
            QSqlQuery q = builder->manyToMany(attr->getConjunctedTable(),
                                              attr->getColumnName(),
                                              entity->getProperty(entity->getPrimaryKey()).toLongLong());
            Resolver r(this->schema->getDatabase());
            auto listMap = r.convertQueryResult(q);
            auto secClassName = attr->getRelatedClass()->className();
            for (int var = 0; var < listMap.size(); ++var) {
                QSharedPointer<Entity> e;
                auto id = listMap.at(var).value(attr->getRelatedColumnName());
                if (!(cache.contains(id.toLongLong(), secClassName) &&
                      (e = cache.get(id.toLongLong(), secClassName)))) {
                    e = em->findById(id.toLongLong(), secClassName);
                }
                if (e) {
                    EntityHelper::addEntityToListProperty(entity, e, attr->getMetaProperty());
                    e = QSharedPointer<Entity>();
                }
            }
        } else {
            this->missingTable(attr->getConjunctedTable());
        }
    }
}
