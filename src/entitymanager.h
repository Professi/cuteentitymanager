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

  private:
    static QStringList connectionNames;
    QSharedPointer<Schema> schema;
    static void setConnectionNames(QStringList list);
    QSharedPointer<Database> db;
    Cache cache;
    QString createConnection();
    QList<QHash<QString, QVariant> > convertQueryResult(QSqlQuery &q);
    bool checkTable(const QSharedPointer<Entity> &entity);

  protected:
    void init();
    QList<QHash<QString, QVariant> > findAll(const QSharedPointer<Entity> &e);
    void resolveRelations(const QSharedPointer<Entity> &entity,
                          const QHash<QString, QVariant> &map, const bool refresh = false);
    QHash<QString, QVariant> findByPk(qint64 id, const QSharedPointer<Entity> &e);
    QSharedPointer<Entity> convert(const QHash<QString, QVariant> &map,
                                   const char *classname, const bool refresh = false);
    QList<QSharedPointer<Entity>> convert(QList<QHash<QString, QVariant> > maps,
                                          const char *classname, const bool refresh = false);
    void manyToOne(const QSharedPointer<Entity> &entity, const QVariant &id,
                   const QMetaProperty &property, const bool refresh = false);
    void oneToMany(const QSharedPointer<Entity> &entity, const Relation &r,
                   const QMetaProperty &property, const bool refresh = false);
    void manyToMany(const QSharedPointer<Entity> &entity,
                    const QMetaProperty &property, const bool refresh = false);
    void oneToOne(const QSharedPointer<Entity> &entity, const Relation &r,
                  const QMetaProperty &property, const bool refresh = false,
                  const QVariant &id = "");
    bool canPersistRelation(const Relation &relation, const RelationType &r,
                            const QVariant &var) const;
    void persistManyToMany(const QSharedPointer<Entity> &entity, const Relation &r,
                           QVariant &property);
    QList<QHash<QString, QVariant> > findAllByAttributes(const
            QSharedPointer<Entity> &entity,
            bool ignoreID = false);
    QList<QHash<QString, QVariant> > findAllByAttributes(const
            QHash<QString, QVariant> &m,
            const QString &tblname,
            bool ignoreID = false);
    QSharedPointer<Entity> findById(const qint64 &id, QSharedPointer<Entity> &e,
                                    const bool refresh = false);
    void addEntityToListProperty(const QSharedPointer<Entity> &entity,
                                 QSharedPointer<Entity> add, const QMetaProperty &property);
    void setListProperty(const QSharedPointer<Entity> &entity,
                         QList<QSharedPointer<Entity>> &list,
                         const QMetaProperty &property) const;
    void setProperty(const QSharedPointer<Entity> &entiy,
                     QSharedPointer<Entity> value,
                     const QMetaProperty &property) const;
    void saveRelations(const QSharedPointer<Entity> &entity);
    QList<QSharedPointer<Entity>> saveRelationEntities(const
                               QList<QSharedPointer<Entity>> &list, const Relation &r);
    void persistMappedByRelation(const QList<QSharedPointer<Entity>> &list,
                                 QSqlQuery &q, const QSharedPointer<Entity> &entity, const QSharedPointer<Entity> &ptr, const Relation &r,
                                 const QString &tblName);
    bool shouldBeSaved(QSharedPointer<Entity> &entity , const Relation &r);
    void removeRelations(const QSharedPointer<Entity> &entity);
    void removeEntityList(QVariant &var);
    void removeManyToManyEntityList(const QSharedPointer<Entity> &e,
                                    const Relation &r, QVariant &var);
    void removeEntity(QVariant &var);
    void setNullOneToManyRelation(QVariant &var, const Relation &r);
    void setNullEntityPropertyRelation(QVariant &var, const Relation &r);
    QMetaProperty mappedProperty(const Relation &r,const QSharedPointer<Entity> &foreignEntity) const;

  public:
    EntityManager(QSqlDatabase database);
    EntityManager(const QString &databaseType, QString databasename = "" ,
                  QString hostname = "",
                  QString username = "",
                  QString password = "", QString port = "");
    ~EntityManager();
    static QStringList getConnectionNames();
    /**
     * @brief startup
     * @param version must be unique
     * @param toInitialize list of entity classnames which database tables should be created
     * @return
     */
    public slots:
    bool startup(QString version, QStringList toInitialize);
    bool executeQuery(const QString &query);
    static void removeConnectionName(const QString &name);
    QSharedPointer<Entity> findById(const qint64 &id, const QString &classname);
    QList<QSharedPointer<Entity>> findEntityByAttributes(const
                               QSharedPointer<Entity> &entity,
                               bool ignoreID = false);
    bool create(QList<QSharedPointer<Entity>> entities,
                const bool persistRelations = true);
    bool create(QSharedPointer<Entity> &entity, const bool persistRelations = true,
                const bool checkDuplicate = false);
    bool save(QSharedPointer<Entity> &entity, const bool persistRelations = true);
    qint64 findId(QSharedPointer<Entity> &entity);
    bool merge(QSharedPointer<Entity> &entity, bool withRelations = true);
    bool remove(QSharedPointer<Entity> &entity);
    bool removeAll(QString tblname);
    bool createTable(const QSharedPointer<Entity> &entity, bool createRelationTables=true);
    qint8 count(const QSharedPointer<Entity> &entity, bool ignoreID = true);
    qint8 count(const QString &tableName);
    QSharedPointer<Database> getDb() const;
    void setDb(const QSharedPointer<Database> &value);
    QSharedPointer<Schema> getSchema() const;
    void refresh(QSharedPointer<Entity> &entity);
    void setSchema(const QSharedPointer<Schema> &value);
    /**
     *@TODO use conditions
     */
public:
    template<class T> qint8 count(QHash<QString, QString> condition =
                                      QHash<QString, QString>()) {
        Entity *e = EntityInstanceFactory::createInstance<T>();
        qint8 rc = 0;
        if (e) {
            rc = this->count(e->getTablename());
            delete e;
        }
        return rc;
    }

    template<class T> QList<QSharedPointer<Entity>> findAll() {
        QSharedPointer<Entity> ptr = QSharedPointer<Entity>
                                     (EntityInstanceFactory::createInstance<T>());
        if (ptr) {
            auto maps = this->findAll(ptr);
            const char *className = ptr.data()->getClassname();
            return this->convert(maps, className);
        }
        return QList<QSharedPointer<Entity>>();
    }

    template<class T> QSharedPointer<Entity> findById(const qint64 &id) {
        auto e = EntityInstanceFactory::createInstance<T>();
        QSharedPointer<Entity> ptr = QSharedPointer<Entity>(e);
        return this->findById(id, ptr);
    }

    template<class T> QSharedPointer<Entity> findEntityByAttributes(
        const QHash<QString, QString>
        &attributes) {
        auto list = this->findAllEntitiesByAttributes<T>(attributes, 1, 0);
        if (list.isEmpty()) {
            return QSharedPointer<Entity>();
        }
        return list.at(0);
    }

    template<class T> QList<QSharedPointer<Entity>> findAllEntitiesByAttributes(
                const QHash<QString, QString> &attributes =
    QHash<QString, QString>(), quint32 limit = 0, quint32 offset = 0) {
        auto list = this->findAllEntitiesByAttributes<T>(attributes);
        return list;
    }

    template<class T> QList<QSharedPointer<Entity>> findEntitiesBySql(
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

    template<class T> bool remove(const QList<qint64> &ids) {
        bool ok = true;
        foreach (qint64 var, ids) {
            if (!this->remove<T>(var)) {
                ok = false;
                break;
            }
        }
        return ok;
    }

    template<class T> bool remove(qint64 id) {
        Entity *e = EntityInstanceFactory::createInstance<T>();
        if (e) {
            QSharedPointer<Entity> ptr = QSharedPointer<Entity>(e);
            ptr->setId(id);
            return this->remove(ptr);
        }
        return false;
    }

};
}
Q_DECLARE_METATYPE(QSharedPointer<CuteEntityManager::Entity>)
#endif // ENTITYMANAGER_H
