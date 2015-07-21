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
#include "schema.h"
#include <QtSql/QSqlError>
#include <QMetaType>
#include "entity.h"
#include "database.h"
#include "entityinstancefactory.h"
#include "cache.h"

namespace CuteEntityManager {

 class EntityManager : public QObject {
    Q_OBJECT
  signals:
    void actionFinished(qint64 id);
  public:
    Q_DECL_EXPORT EntityManager(QSqlDatabase database);
    Q_DECL_EXPORT EntityManager(const QString &databaseType, QString databasename = "" ,
                  QString hostname = "",
                  QString username = "",
                  QString password = "", QString port = "");
    Q_DECL_EXPORT ~EntityManager();
    static QStringList Q_DECL_EXPORT getConnectionNames();
    /**
     * @brief startup
     * @param version must be unique
     * @param toInitialize list of entity classnames which database tables should be created
     * @return
     */
  public slots:
    Q_DECL_EXPORT bool startup(QString version, QStringList toInitialize);
    Q_DECL_EXPORT bool executeQuery(const QString &query);
    static void removeConnectionName(const QString &name);
    Q_DECL_EXPORT QSharedPointer<Entity> findById(const qint64 &id, const QString &classname);
    Q_DECL_EXPORT QList<QSharedPointer<Entity>> findEntityByAttributes(const
                               QSharedPointer<Entity> &entity,
                               bool ignoreID = false);
    Q_DECL_EXPORT bool create(QList<QSharedPointer<Entity>> entities,
                const bool persistRelations = true);
    Q_DECL_EXPORT bool create(QSharedPointer<Entity> &entity, const bool persistRelations = true,
                const bool checkDuplicate = false);
    Q_DECL_EXPORT bool save(QSharedPointer<Entity> &entity, const bool persistRelations = true);
    Q_DECL_EXPORT qint64 findId(QSharedPointer<Entity> &entity);
    bool merge(QSharedPointer<Entity> &entity, bool withRelations = true);
    bool remove(QSharedPointer<Entity> &entity);
    bool removeAll(QString tblname);
    Q_DECL_EXPORT bool createTable(const QSharedPointer<Entity> &entity,
                     bool createRelationTables = true);
    qint8 count(const QSharedPointer<Entity> &entity, bool ignoreID = true);
    qint8 count(const QString &tableName);
    Q_DECL_EXPORT QSharedPointer<Database> getDb() const;
    Q_DECL_EXPORT void setDb(const QSharedPointer<Database> &value);
    Q_DECL_EXPORT QSharedPointer<Schema> getSchema() const;
    Q_DECL_EXPORT void refresh(QSharedPointer<Entity> &entity);
    Q_DECL_EXPORT void setSchema(const QSharedPointer<Schema> &value);
    /**
     *@TODO use conditions
     */
  public:
    template<class T> Q_DECL_EXPORT qint8 count(QHash<QString, QString> condition =
                                      QHash<QString, QString>()) {
        Entity *e = EntityInstanceFactory::createInstance<T>();
        qint8 rc = 0;
        if (e) {
            rc = this->count(e->getTablename());
            delete e;
        }
        return rc;
    }

     template<class T> Q_DECL_EXPORT QList<QSharedPointer<Entity>> findAll() {
        QSharedPointer<Entity> ptr = QSharedPointer<Entity>
                                     (EntityInstanceFactory::createInstance<T>());
        if (ptr) {
            auto maps = this->findAll(ptr);
            const char *className = ptr.data()->getClassname();
            return this->convert(maps, className);
        }
        return QList<QSharedPointer<Entity>>();
    }

    template<class T> Q_DECL_EXPORT QSharedPointer<Entity> findById(const qint64 &id) {
        auto e = EntityInstanceFactory::createInstance<T>();
        QSharedPointer<Entity> ptr = QSharedPointer<Entity>(e);
        return this->findById(id, ptr);
    }

    template<class T> Q_DECL_EXPORT QSharedPointer<Entity> findEntityByAttributes(
        const QHash<QString, QString>
        &attributes) {
        auto list = this->findAllEntitiesByAttributes<T>(attributes, 1, 0);
        if (list.isEmpty()) {
            return QSharedPointer<Entity>();
        }
        return list.at(0);
    }

    template<class T> Q_DECL_EXPORT QList<QSharedPointer<Entity>> findAllEntitiesByAttributes(
                const QHash<QString, QString> &attributes =
    QHash<QString, QString>(), quint32 limit = 0, quint32 offset = 0) {
        auto list = this->findAllEntitiesByAttributes<T>(attributes);
        return list;
    }

    template<class T> Q_DECL_EXPORT QList<QSharedPointer<Entity>> findEntitiesBySql(
    const QString &sql) {
        Entity *e = EntityInstanceFactory::createInstance<T>();
        if (e) {
            QSqlQuery q = this->db.data()->select(sql);
            auto result = this->convertQueryResult(q);
            auto ret = this->convert(result, e->getClassname());
            delete e;
            return ret;
        }
        return QList<QSharedPointer<Entity>>();
    }

    template<class T> Q_DECL_EXPORT bool remove(const QList<qint64> &ids) {
        bool ok = true;
        foreach (qint64 var, ids) {
            if (!this->remove<T>(var)) {
                ok = false;
                break;
            }
        }
        return ok;
    }

    template<class T> Q_DECL_EXPORT bool remove(qint64 id) {
        Entity *e = EntityInstanceFactory::createInstance<T>();
        if (e) {
            QSharedPointer<Entity> ptr = QSharedPointer<Entity>(e);
            ptr->setId(id);
            return this->remove(ptr);
        }
        return false;
    }

  protected:
    Q_DECL_EXPORT void init();
    Q_DECL_EXPORT QList<QHash<QString, QVariant> > findAll(const QSharedPointer<Entity> &e);
    Q_DECL_EXPORT void resolveRelations(const QSharedPointer<Entity> &entity,
                          const QHash<QString, QVariant> &map, const bool refresh = false);
    Q_DECL_EXPORT QHash<QString, QVariant> findByPk(qint64 id, const QSharedPointer<Entity> &e);
    Q_DECL_EXPORT QSharedPointer<Entity> convert(const QHash<QString, QVariant> &map,
                                   const char *classname, const bool refresh = false);
    Q_DECL_EXPORT QList<QSharedPointer<Entity>> convert(QList<QHash<QString, QVariant> > maps,
                                          const char *classname, const bool refresh = false);
    Q_DECL_EXPORT void manyToOne(const QSharedPointer<Entity> &entity, const QVariant &id,
                   const QMetaProperty &property, const bool refresh = false);
    Q_DECL_EXPORT void oneToMany(const QSharedPointer<Entity> &entity, const Relation &r,
                   const QMetaProperty &property, const bool refresh = false);
    Q_DECL_EXPORT void manyToMany(const QSharedPointer<Entity> &entity,
                    const QMetaProperty &property, const bool refresh = false);
    Q_DECL_EXPORT void oneToOne(const QSharedPointer<Entity> &entity, const Relation &r,
                  const QMetaProperty &property, const bool refresh = false,
                  const QVariant &id = "");
    Q_DECL_EXPORT bool canPersistRelation(const Relation &relation, const RelationType &r,
                            const QVariant &var) const;
    Q_DECL_EXPORT void persistManyToMany(const QSharedPointer<Entity> &entity, const Relation &r,
                           QVariant &property);
    Q_DECL_EXPORT QList<QHash<QString, QVariant> > findAllByAttributes(const
            QSharedPointer<Entity> &entity,
            bool ignoreID = false);
    Q_DECL_EXPORT QList<QHash<QString, QVariant> > findAllByAttributes(const
            QHash<QString, QVariant> &m,
            const QString &tblname,
            bool ignoreID = false);
    Q_DECL_EXPORT QSharedPointer<Entity> findById(const qint64 &id, QSharedPointer<Entity> &e,
                                    const bool refresh = false);
    Q_DECL_EXPORT void addEntityToListProperty(const QSharedPointer<Entity> &entity,
                                 QSharedPointer<Entity> add, const QMetaProperty &property);
    Q_DECL_EXPORT void setListProperty(const QSharedPointer<Entity> &entity,
                         QList<QSharedPointer<Entity>> &list,
                         const QMetaProperty &property) const;
    Q_DECL_EXPORT void setProperty(const QSharedPointer<Entity> &entity,
                     QSharedPointer<Entity> value,
                     const QMetaProperty &property) const;
    Q_DECL_EXPORT void savePrePersistedRelations(const QSharedPointer<Entity> &entity);
    Q_DECL_EXPORT void savePostPersistedRelations(const QSharedPointer<Entity> &entity);

    Q_DECL_EXPORT QList<QSharedPointer<Entity>> saveRelationEntities(const
                               QList<QSharedPointer<Entity>> &list, const Relation &r);
    Q_DECL_EXPORT void persistMappedByRelation(const QList<QSharedPointer<Entity>> &list,
                                 QSqlQuery &q, const QSharedPointer<Entity> &entity,
                                 const QSharedPointer<Entity> &ptr, const Relation &r,
                                 const QString &tblName);
    Q_DECL_EXPORT bool shouldBeSaved(QSharedPointer<Entity> &entity , const Relation &r);
    Q_DECL_EXPORT void removeRelations(const QSharedPointer<Entity> &entity);
    Q_DECL_EXPORT void removeEntityList(QVariant &var);
    Q_DECL_EXPORT void removeManyToManyEntityList(const QSharedPointer<Entity> &e,
                                    const Relation &r, QVariant &var);
    Q_DECL_EXPORT void removeEntity(QVariant &var);
    Q_DECL_EXPORT void setNullOneToManyRelation(QVariant &var, const Relation &r);
    Q_DECL_EXPORT void setNullEntityPropertyRelation(QVariant &var, const Relation &r);
    Q_DECL_EXPORT QMetaProperty mappedProperty(const Relation &r,
                                 const QSharedPointer<Entity> &foreignEntity) const;

  private:
    static QStringList connectionNames;
    QSharedPointer<Schema> schema;
    static void setConnectionNames(QStringList list);
    QSharedPointer<Database> db;
    Cache cache;
    QString createConnection();
    QList<QHash<QString, QVariant> > convertQueryResult(QSqlQuery &q);
    bool checkTable(const QSharedPointer<Entity> &entity);

};
}
Q_DECLARE_METATYPE(QSharedPointer<CuteEntityManager::Entity>)
#endif // ENTITYMANAGER_H
