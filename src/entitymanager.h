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

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlField>
#include <QString>
#include <QStringList>
#include <QObject>
#include <QSharedPointer>
#include <QDebug>
#include <QtSql/QSqlError>
#include <QMetaType>
#include "schema.h"
#include "entity.h"
#include "database.h"
#include "entityinstancefactory.h"
#include "queryinterpreter.h"
#include "cache.h"
#include "querybuilder.h"
#include "validators/errormsg.h"
#include "attribute.h"
namespace CuteEntityManager {
#ifdef QT_DEBUG
#define DEFAULTMSGTYPE MsgType::DEBUG
#define INSPECTENTITIES true
#else
#define DEFAULTMSGTYPE MsgType::CRITICAL
#define INSPECTENTITIES false
#endif

class AttributeResolver;
class Logger;
class QueryInterpreter;
class EntityManager : public QObject {
    Q_OBJECT
  public slots:
    /**
     * @brief startup
     * @param version must be unique
     * @param toInitialize list of entity classnames which database tables should be created
     * @return
     */
    bool startup(QString version, QStringList toInitialize,
                 bool createIndices = false);
    bool executeQuery(const QString &query);
    QSharedPointer<Entity> findById(const qint64 &id, const QString &classname);
    QList<QSharedPointer<Entity>> findEntityByAttributes(const
                               QSharedPointer<Entity> &entity,
                               bool ignoreID = false, const bool refresh = false, const bool resolveRelations = true);
    qint64 findId(QSharedPointer<Entity> &entity);
    /**
     * @todo should be an insert statement with many values
     * @todo error handling
     * @brief EntityManager::create
     * @param entities
     * @return
     */
    bool create(QList<QSharedPointer<Entity>> &entities, const bool persistRelations = true,
                const bool checkDuplicate = false, const bool validate = true,
                const bool relationsIgnoreHasChanged = false);
    /**
     * @brief EntityManager::create
     * Will persist an entity in the database. Before its persisted it has the id -1(invalid id). If database persisting was succesfull it has a valid id.
     * @param entity
     * @param persistRelations
     * @param checkDuplicate
     * @param validate
     * @return
     */
    bool create(QSharedPointer<Entity> &entity, const bool persistRelations = true,
                const bool checkDuplicate = false, const bool validate = true,
                const bool relationsIgnoreHasChanged = false) ;
    /**
     * @brief EntityManager::save
     * If the entity has no valid ID, this method will call the create() method. Else it would call the merge method.
     * @param entity
     * @param persistRelations
     * @param ignoreHasChanged
     * @param validate
     * @return bool
     */
    bool save(QSharedPointer<Entity> &entity, const bool persistRelations = true,
              const bool ignoreHasChanged = false, const bool validate = true,
              const bool relationsIgnoreHasChanged = false);
    bool save(QList<QSharedPointer<Entity>> &entities,
              const bool persistRelations = true,
              const bool ignoreHasChanged = false, const bool validate = true,
              const bool relationsIgnoreHasChanged = false);
    bool merge(QSharedPointer<Entity> &entity, bool withRelations = true,
               const bool validate = true, const bool relationsIgnoreHasChanged = false);
    bool remove(QSharedPointer<Entity> &entity);
    bool removeAll(QString tblname);
    bool createTable(const QSharedPointer<Entity> &entity,
                     bool createRelationTables = true);
    bool createTable(QString className, bool createRelationTables = true);
    bool removeTable(QString className);
    quint32 count(const QSharedPointer<Entity> &entity, bool ignoreID = true,
                  bool followInheritance = false);
    quint32 count(const QString &tableName);
    QSharedPointer<Database> getDb() const;
    void setDb(const QSharedPointer<Database> &value);
    QSharedPointer<Schema> getSchema() const;
    /**
     * @brief EntityManager::refresh
     * fetches an entity again from the database
     * @param entity
     */
    void refresh(QSharedPointer<Entity> &entity);
    QList<QHash<QString, QVariant>> selectByQuery(Query &query);
    QList<QHash<QString, QVariant>> selectBySql(const QString &sql);
    quint32 count(Query &query);
    /**
     * @brief EntityManager::validate
     * This validates an entity. Its uses the validationRules() method of the specified entity.
     * If there are validation errors, this method will set these errors in the entity object.
     * You can check them with entity->hasErrors(), entity->getErrors() or entity->getErrorsAsString()
     * @param entity
     * @return true if it has no validation errors, false if it has errors
     */
    bool validate(QSharedPointer<Entity> &entity);
    /**
     * @brief hasChanged
     * @param entity
     * @todo check manyToMany relations
     * @return
     */
    bool hasChanged(QSharedPointer<Entity> &entity);

  public:
    EntityManager(QSqlDatabase database, bool logQueries = false,
                  const bool inspectEntities = INSPECTENTITIES,
                  MsgType logActions = DEFAULTMSGTYPE);
    EntityManager(const QString &databaseType, QString databasename = "" ,
                  QString hostname = "",
                  QString username = "",
                  QString password = "", QString port = "", bool logQueries = false,
                  QString databaseOptions = "", const bool inspectEntities = INSPECTENTITIES,
                  MsgType logActions = DEFAULTMSGTYPE);
    virtual ~EntityManager();
    static QStringList getConnectionNames();
    static void removeConnectionName(const QString &name);
    static QHash<QString, EntityManager *> getInstances();
    static EntityManager *getDefaultInstance();
    static EntityManager *getInstance(QString name);
    QSharedPointer<QueryBuilder> getQueryBuilder() const;

    template<class T> QList<QSharedPointer<T>> find(Query &q,
                                            const bool joinBaseClasses = false, const bool resolveRelations = true,
    const bool refresh = false) {
        QSharedPointer<Entity> ptr = QSharedPointer<Entity>
                                     (EntityInstanceFactory::createInstance<T *>());
        if (ptr) {
            if (q.getFrom().isEmpty()) {
                q.setFrom(QStringList(ptr->getTablename()));
            }
            if (joinBaseClasses) {
                q.appendJoins(this->schema->getQueryBuilder()->joinBaseClasses(ptr));
            }
            QSqlQuery query = this->queryInterpreter->build(q);
            auto maps = this->convertQueryResult(query);
            auto converted = this->convert(maps, EntityHelper::getClassname(ptr.data()),
                                           refresh,
                                           resolveRelations);
            return EntityManager::convertList<T>(converted);
        }
        return QList<QSharedPointer<T>>();
    }

    template<class T> QList<QSharedPointer<T>> findAll(const bool resolveRelations =
    true, const bool refresh = false) {
        QSharedPointer<Entity> ptr = QSharedPointer<Entity>
                                     (EntityInstanceFactory::createInstance<T *>());
        if (ptr) {
            auto maps = this->findAll(ptr);
            auto converted = this->convert(maps, EntityHelper::getClassname(ptr.data()),
                                           refresh,
                                           resolveRelations);
            return EntityManager::convertList<T>(converted);
        }
        return QList<QSharedPointer<T>>();
    }

    template<class T> QSharedPointer<T> findById(const qint64 &id,
            const bool refresh = false) {
        auto e = EntityInstanceFactory::createInstance<T *>();
        QSharedPointer<Entity> ptr = QSharedPointer<Entity>(e);
        return this->findById(id, ptr, refresh).objectCast<T>();
    }

    template<class T>
    QSharedPointer<T> findEntityByAttributes(
        const QHash<QString, QVariant>
        &attributes, const bool joinBaseClasses = false,
        const bool resolveRelations = true, const bool refresh=false) {
        auto list = this->findAllEntitiesByAttributes<T>(attributes, 1, 0,
                    joinBaseClasses, resolveRelations, refresh);
        if (list.isEmpty()) {
            return QSharedPointer<T>();
        }
        QSharedPointer<Entity> obj = list.at(0);
        return obj.objectCast<T>();
    }

    template<class T> QList<QSharedPointer<T>> findAllEntitiesByAttributes(
            const QHash<QString, QVariant> &attributes =
                QHash<QString, QVariant>(), quint64 limit = 0, quint64 offset = 0,
            bool joinBaseClasses = false, const bool resolveRelations = true,
    const bool refresh = false) {
        QSharedPointer<Entity> e = QSharedPointer<Entity>
                                   (EntityInstanceFactory::createInstance<T*>());
        if (e) {
            Query query = Query(QStringList(e->getTablename()));
            if (joinBaseClasses) {
                query.appendJoins(this->schema->getQueryBuilder()->joinBaseClasses(e));
            }
            query.appendWhere(this->schema->getQueryBuilder()->where(attributes));
            query.setLimit(limit);
            query.setOffset(offset);
            QSqlQuery q = this->queryInterpreter->build(query);
            auto results = this->convertQueryResult(q);
            auto list = this->convert(results, EntityHelper::getClassname(e.data()), refresh,
                                      resolveRelations);
            return EntityManager::convertList<T>(list);
        }
        return QList<QSharedPointer<T>>();
    }

    template<class T> QList<QSharedPointer<T>> findEntitiesBySql(
    const QString &sql) {
        auto e = EntityInstanceFactory::createInstance<T *>();
        if (e) {
            QSqlQuery q = this->schema->getDatabase()->getQuery(sql);
            auto result = this->convertQueryResult(q);
            auto converted = this->convert(result, EntityHelper::getClassname(e));
            return EntityManager::convertList<T>(converted);
        }
        return QList<QSharedPointer<T>>();
    }

    template<class T> bool remove(const QList<qint64> &ids) {
        bool ok = true;
        foreach (qint64 var, ids) {
            if (!this->remove<T *>(var)) {
                ok = false;
                break;
            }
        }
        return ok;
    }

    template<class T> bool remove(qint64 id) {
        Entity *e = EntityInstanceFactory::createInstance<T *>();
        if (e) {
            QSharedPointer<Entity> ptr = QSharedPointer<Entity>(e);
            ptr->setId(id);
            return this->remove(ptr);
        }
        return false;
    }

    template<class T, class X>
    static QList<QSharedPointer<T>> convertList(const QList<QSharedPointer<X>> &list) {
        QList<QSharedPointer<T>> newList = QList<QSharedPointer<T>>();
        for (int i = 0; i < list.size(); ++i) {
            newList.append(qSharedPointerObjectCast<T>(list.at(i)));
        }
        return newList;
    }

  protected:
    bool saveObject(QSharedPointer<Entity> &entity, QList<Entity *> &mergedObjects,
                    const bool persistRelations = true,
                    const bool ignoreHasChanged = false, const bool validate = true,
                    const bool relationsIgnoreHasChanged = false);
    bool mergeObject(QSharedPointer<Entity> &entity, QList<Entity *> &mergedObjects,
                     bool withRelations,
                     const bool validate, const bool relationsIgnoreHasChanged = false);
    bool createObject(QSharedPointer<Entity> &entity,
                      QList<Entity *> &mergedObjects, const bool persistRelations,
                      const bool checkDuplicate, const bool validate,
                      const bool relationsIgnoreHasChanged = false);
    void init(bool inspect, const MsgType msgType);
    QList<QHash<QString, QVariant>> findAll(const QSharedPointer<Entity> &e);
    void resolveRelations(const QSharedPointer<Entity> &entity,
                          const QHash<QString, QVariant> &map, const bool refresh = false);
    QHash<QString, QVariant> findByPk(qint64 id, const QSharedPointer<Entity> &e);
    void manyToOne(const QSharedPointer<Entity> &entity, const QVariant &id,
                   Attribute *&attr, const bool refresh = false);
    void oneToMany(const QSharedPointer<Entity> &entity, Attribute *&attr,
                   const bool refresh = false);
    void manyToMany(const QSharedPointer<Entity> &entity, Attribute *&attr,
                    const bool refresh = false);
    void oneToOne(const QSharedPointer<Entity> &entity, Attribute *&attr,
                  const bool refresh = false,
                  const QVariant &id = "");
    void persistManyToMany(const QSharedPointer<Entity> &entity, const Relation &r,
                           QVariant &property, QList<Entity *> &mergedObjects,
                           const bool ignoreHasChanged = false, const bool newItem = false);
    QList<QHash<QString, QVariant>> findAllByAttributes(const
                                 QSharedPointer<Entity> &entity,
                                 bool ignoreID = false);
    QList<QHash<QString, QVariant>> findAllByAttributes(const
                                 QHash<QString, QVariant> &m,
                                 const QString &tblname,
                                 bool ignoreID = false);
    QSharedPointer<Entity> findById(const qint64 &id, QSharedPointer<Entity> &e,
                                    const bool refresh = false);
    /**
     * @brief EntityManager::savePrePersistedRelations
     * @param entity
     * @param mergedObjects
     * @throw can throw in debug mode a QString exception when the type of any Relation is wrong @see EntityManager::checkRelation
     */
    void savePrePersistedRelations(const QSharedPointer<Entity> &entity,
                                   QList<Entity *> &mergedObjects, bool ignoreHasChanged = false);
    /**
     * @brief EntityManager::savePostPersistedRelations
     * @param entity
     * @param mergedObjects
     * @throw can throw in debug mode a QString exception when the type of any Relation is wrong @see EntityManager::checkRelation
     */
    void savePostPersistedRelations(const QSharedPointer<Entity> &entity,
                                    QList<Entity *> &mergedObjects, bool ignoreHasChanged = false,
                                    bool newItem = false);

    QList<QSharedPointer<Entity>> saveRelationEntities(const
                               QList<QSharedPointer<Entity>> &list, const Relation &r,
                               QList<Entity *> &mergedObjects);
    /**
     * @brief EntityManager::persistManyToMany
     * @param entity
     * @param r
     * @param property
     * @param mergedObjects
     * @todo compare old values with new values if nothing has changed don't persist them
     */
    void persistMappedByRelation(const QList<QSharedPointer<Entity>> &list,
                                 QSqlQuery &q, const QSharedPointer<Entity> &entity,
                                 const QSharedPointer<Entity> &ptr, const Relation &r,
                                 const QString &tblName, QList<Entity *> &mergedObjects);
    bool shouldBeSaved(QSharedPointer<Entity> &entity , const Relation &r);
    void removeRelations(const QSharedPointer<Entity> &entity);
    void removeEntityList(QVariant &var);
    void removeManyToManyEntityList(const QSharedPointer<Entity> &e,
                                    const Relation &r, QVariant &var);
    void removeEntity(QVariant &var);
    void setNullOneToManyRelation(QVariant &var, const Relation &r);
    void setNullEntityPropertyRelation(QVariant &var, const Relation &r);
    QSharedPointer<Entity> convert(const QHash<QString, QVariant> &map,
                                   const char *classname, const bool refresh = false,
                                   const bool resolveRelations = true);
    void convert(const QHash<QString, QVariant> &map, QSharedPointer<Entity> &entity,
                 const bool refresh = false,
                 const bool resolveRelations = true);
    QList<QSharedPointer<Entity>> convert(QList<QHash<QString, QVariant>> maps,
                                          const char *classname, const bool refresh = false, const bool resolveRelations = true);
    void missingManyToManyTable(const QString &tblName,
                                const QSharedPointer<Entity> &e, const Relation &r);
    /**
     * @brief EntityManager::generateObjectName
     * Generates a object name with this scheme: em[anyNumber]
     * @return
     */
    QString generateObjectName();
    void appendToInstanceList();

  private:
    static QStringList connectionNames;
    static QHash<QString, EntityManager *> instances;
    QSharedPointer<Logger> logger;
    QSharedPointer<AttributeResolver> ar;
    QString id;
    QSharedPointer<Schema> schema;
    static void setConnectionNames(QStringList list);
    QSharedPointer<Database> db;
    Cache cache;
    QString createConnection();
    QList<QHash<QString, QVariant>> convertQueryResult(QSqlQuery &q);
    /**
     * @brief EntityManager::checkTable
     * Checks if a table has been already created, if not it will create it
     * @param entity
     * @return
     */
    bool checkTable(const QSharedPointer<Entity> &entity);
    QSharedPointer<QueryInterpreter> queryInterpreter;

};
}
Q_DECLARE_METATYPE(QSharedPointer<CuteEntityManager::Entity>)
#endif // ENTITYMANAGER_H
