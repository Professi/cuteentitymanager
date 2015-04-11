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
#include "entity.h"
#include "database.h"

namespace CuteEntityManager {

class EntityManager {
  private:
    static QStringList connectionNames;
    QSharedPointer<Schema> schema;
    static void setConnectionNames(QStringList list);
    QSharedPointer<Database> db;
    QString createConnection();
    QString createTableQuery(const QSharedPointer<Entity> &entity);
    QString attributes(const QHash<QString, QVariant> &m, const QString &conjunction = ",", bool ignoreID = false);
    QList<QHash<QString, QVariant> > convertQueryResult(QSqlQuery &q);
    bool checkTable(const QSharedPointer<Entity> &entity);
    QString buildCreateQuery(QHash<QString, QVariant>::const_iterator i, QHash<QString, QVariant>::const_iterator end,
                             QString &p1, QString &p2);
    void bindValues(const QHash<QString, QVariant> &h, QSqlQuery &q, bool ignoreID = false);

  protected:
    void init();
    QString where(const QSharedPointer<Entity> &entity, QString conjunction = ",", bool ignoreID = false);
    QString where(const QHash<QString, QVariant> &m, const QString &conjunction = ",", bool ignoreID = false);

  public:
    EntityManager(QSqlDatabase database);
    EntityManager(const QString &databaseType, QString databasename = "" , QString hostname = "", QString username = "",
                  QString password = "", QString port = "");
    ~EntityManager();
    static QStringList getConnectionNames();
    static void removeConnectionName(const QString &name);
    bool create(QSharedPointer<Entity> &entity);
    bool save(QSharedPointer<Entity> &entity);
    qint64 findId(QSharedPointer<Entity> &entity);
    QList<QHash<QString, QVariant> > findAll(QString tblname);
    QHash<QString, QVariant> find(qint64 id, QString tblname);
    QList<QHash<QString, QVariant> > findByAttributes(const QSharedPointer<Entity> &entity, bool ignoreID = false);
    QList<QHash<QString, QVariant> > findByAttributes(const QHash<QString, QVariant> &m, const QString &tblname,
            bool ignoreID = false);
    bool merge(QSharedPointer<Entity> &entity);
    bool remove(QSharedPointer<Entity> &entity);
    bool removeAll(QString tblname);
    bool createTable(QSharedPointer<Entity> &entity);
    qint8 count(Entity *entity, bool ignoreID = true);
    QSharedPointer<Database> getDb() const;
    void setDb(const QSharedPointer<Database> &value);
    QSharedPointer<Schema> getSchema() const;
    void setSchema(const QSharedPointer<Schema> &value);

};
}
#endif // ENTITYMANAGER_H
