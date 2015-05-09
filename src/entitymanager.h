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

class EntityManager {
  signals:
    void actionFinished(qint64 id);

  private:
    static QStringList connectionNames;
    QSharedPointer<Schema> schema;
    static void setConnectionNames(QStringList list);
    QSharedPointer<Database> db;
    Cache cache;
    QString createConnection();
    QString createTableQuery(const QSharedPointer<Entity> &entity);
    QList<QHash<QString, QVariant> > convertQueryResult(QSqlQuery &q);
    bool checkTable(const QSharedPointer<Entity> &entity);

  protected:
    void init();
    QList<QHash<QString, QVariant> > findAll(QString tblname);
    void resolveRelations(const QSharedPointer<Entity> &entity, const QHash<QString, QVariant> &map);
    QHash<QString, QVariant> findByPk(qint64 id, QString tblname);
    QSharedPointer<Entity> convert(const QHash<QString, QVariant> &map, const char *classname);
    QList<QSharedPointer<Entity>> convert(QList<QHash<QString, QVariant> > maps, const char *classname);
    void manyToOne(const QSharedPointer<Entity> &entity, const QVariant &id, const QMetaProperty &property);
    void oneToMany(const QSharedPointer<Entity> &entity, const Relation &r, const QMetaProperty &property);
    void manyToMany(const QSharedPointer<Entity> &entity, const Relation &r, const QMetaProperty &property);
    void oneToOne(const QSharedPointer<Entity> &entity, const Relation &r, const QMetaProperty &property,
                  const QVariant &id = "");
    QList<QHash<QString, QVariant> > findAllByAttributes(const QSharedPointer<Entity> &entity, bool ignoreID = false);
    QList<QHash<QString, QVariant> > findAllByAttributes(const QHash<QString, QVariant> &m, const QString &tblname,
            bool ignoreID = false);
    QSharedPointer<Entity> findById(const qint64 &id, Entity *&e);

  public:
    EntityManager(QSqlDatabase database);
    EntityManager(const QString &databaseType, QString databasename = "" , QString hostname = "", QString username = "",
                  QString password = "", QString port = "");
    ~EntityManager();
    static QStringList getConnectionNames();
    /**
     * @brief startup
     * @param version must be unique
     * @param toInitialize list of entity classnames which database tables should be created
     * @return
     */
    bool startup(QString version, QStringList toInitialize);
    static void removeConnectionName(const QString &name);
    QSharedPointer<Entity> findById(const qint64 &id, const QString &classname);
    QList<QSharedPointer<Entity>> findEntityByAttributes(const QSharedPointer<Entity> &entity, bool ignoreID = false);
    bool create(QList<QSharedPointer<Entity>> entities);
    bool create(QSharedPointer<Entity> &entity);
    bool save(QSharedPointer<Entity> &entity);
    qint64 findId(QSharedPointer<Entity> &entity);
    bool merge(QSharedPointer<Entity> &entity, bool withRelations = true);
    bool remove(QSharedPointer<Entity> &entity);
    bool removeAll(QString tblname);
    bool createTable(const QSharedPointer<Entity> &entity);
    qint8 count(const QSharedPointer<Entity> &entity, bool ignoreID = true);
    qint8 count(const QString &tableName);
    QSharedPointer<Database> getDb() const;
    void setDb(const QSharedPointer<Database> &value);
    QSharedPointer<Schema> getSchema() const;
    void setSchema(const QSharedPointer<Schema> &value);

    /**
     *@TODO use conditions
     */
    template<class T> qint8 count(QHash<QString, QString> condition = QHash<QString, QString>()) {
        Entity *e = EntityInstanceFactory::createInstance<T>();
        qint8 rc = 0;
        if (e) {
            rc = this->count(e->getTablename());
            delete e;
        }
        return rc;
    }

    template<class T> QList<QSharedPointer<Entity>> findAll() {
        Entity *e = EntityInstanceFactory::createInstance<T>();
        if (e) {
            auto maps = this->findAll(e->getTablename());
            const char *className = e->getClassname();
            delete e;
            return this->convert(maps, className);
        }
        return QList<QSharedPointer<Entity>>();
    }

    template<class T> QSharedPointer<Entity> findById(const qint64 &id) {
        Entity *e = EntityInstanceFactory::createInstance<T>();
        return this->findById(id, e);
    }

    template<class T> QSharedPointer<Entity> findEntityByAttributes(const QHash<QString, QString> &attributes) {
        auto list = this->findAllEntitiesByAttributes<T>(attributes, 1, 0);
        if (list.isEmpty()) {
            return QSharedPointer<Entity>();
        }
        return list.at(0);
    }

    template<class T> QList<QSharedPointer<Entity>> findAllEntitiesByAttributes(const QHash<QString, QString> &attributes =
    QHash<QString, QString>(), quint32 limit = 0, quint32 offset = 0) {
        auto list = this->findAllEntitiesByAttributes<T>(attributes);
        return list;
    }

    template<class T> QList<QSharedPointer<Entity>> findEntitiesBySql(const QString &sql) {
        Entity *e = EntityInstanceFactory::createInstance<T>();
        if (e) {
            QSqlQuery q = this->schema.data()->getQueryBuilder().data()->getQuery();
            q = this->db.data()->select(sql);
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
            e->setId(id);
            return this->remove(ptr);
        }
        return false;
    }

};
}
#endif // ENTITYMANAGER_H
