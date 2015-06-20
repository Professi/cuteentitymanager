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

#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QtSql/QSqlError>
#include <QStringList>
#include <QList>
#include <QString>
#include <QDebug>
#include "enums/databasetype.h"
namespace CuteEntityManager {

class Database {
  private:
    QSqlDatabase database;
    QString connectionName;
    bool seqTable;
    bool supportTransactions;
    void init();

  public:
    Database(QSqlDatabase database);
    ~Database();
    Database(QString databaseType, QString databasename);
    Database(QString databaseType, QString connectionName, QString databasename);
    Database(QString databaseType, QString connectionName = "",
             QString hostname = "",
             QString databasename = "" ,
             QString username = "", QString password = "", qint64 port = 0);
    QSqlDatabase getDatabase();
    QString getConnectionName();
    QSqlQuery getQuery();
    QSqlQuery getQuery(const QString &prepare);
    bool transaction(const QString &query);
    bool transaction(const QStringList &queries);
    bool transaction(QSqlQuery &query);
    bool transaction(QList<QSqlQuery> &queries);
    bool exec(const QString &query);
    bool exec(QStringList queries);
    bool exec(QSqlQuery &query);
    bool exec(QList<QSqlQuery> queries);
    void debugQuery(const QSqlQuery &query) const;
    bool select(QSqlQuery &query);
    QSqlQuery select(const QString &query);
    void startTransaction();
    bool commitTransaction();
    static DatabaseType getDatabaseType(QString s);
    static QSharedPointer<Schema> getSchema(int db,
                                            QSharedPointer<Database> database);

};
}
#endif // DATABASE_H
