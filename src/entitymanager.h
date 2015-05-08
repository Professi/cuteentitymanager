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

namespace CuteEntityManager {

class EntityManager {
  signals:
    void actionFinished(qint64 id);

  private:
    static QStringList connectionNames;
    QSharedPointer<Schema> schema;
    static void setConnectionNames(QStringList list);
    QSharedPointer<Database> db;
    QString createConnection();
    QString createTableQuery(const QSharedPointer<Entity> &entity);
    QList<QHash<QString, QVariant> > convertQueryResult(QSqlQuery &q);
    bool checkTable(const QSharedPointer<Entity> &entity);

  protected:
    void init();
    QList<QHash<QString, QVariant> > findAll(QString tblname);
    QHash<QString, QVariant> find(QSharedPointer<Entity> entity);
    QHash<QString, QVariant> find(qint64 id, QString tblname);
    QSharedPointer<Entity> convert(const QHash<QString, QVariant> &map, const char *classname);
    QList<QSharedPointer<Entity>> convert(QList<QHash<QString, QVariant> > maps, const char *classname);

    QList<QHash<QString, QVariant> > findAllByAttributes(const QSharedPointer<Entity> &entity, bool ignoreID = false);
    QList<QHash<QString, QVariant> > findAllByAttributes(const QHash<QString, QVariant> &m, const QString &tblname,
            bool ignoreID = false);

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
    QList<QSharedPointer<Entity>> findAllEntities(QSharedPointer<Entity> entity);
    QSharedPointer<Entity> findEntity(QSharedPointer<Entity> entity);
    QList<QSharedPointer<Entity>> findEntityByAttributes(const QSharedPointer<Entity> &entity, bool ignoreID = false);
    template<class T> QSharedPointer<Entity> findById(const qint64 &id) {
        Entity *e = EntityInstanceFactory::createInstance<T>();
        QSharedPointer<Entity> ptr = QSharedPointer<Entity>(e);
        e->setId(id);
        return this->findEntity(ptr);
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

    bool create(QList<QSharedPointer<Entity>> entities);
    bool create(QSharedPointer<Entity> &entity);
    bool save(QSharedPointer<Entity> &entity);
    qint64 findId(QSharedPointer<Entity> &entity);
    bool merge(QSharedPointer<Entity> &entity, bool withRelations = true);
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
        QSharedPointer<Entity> ptr = QSharedPointer<Entity>(e);
        e->setId(id);
        return this->remove(ptr);
    }

    bool remove(QSharedPointer<Entity> &entity);
    bool removeAll(QString tblname);
    bool createTable(const QSharedPointer<Entity> &entity);
    qint8 count(const QSharedPointer<Entity> &entity, bool ignoreID = true);
    qint8 count(const QString &tableName);
    //template<class T> count(QHash<QString, QString> condition = QHash<QString, QString>());
    QSharedPointer<Database> getDb() const;
    void setDb(const QSharedPointer<Database> &value);
    QSharedPointer<Schema> getSchema() const;
    void setSchema(const QSharedPointer<Schema> &value);

};
}
#endif // ENTITYMANAGER_H
