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
#include "logger.h"
namespace CuteEntityManager {
#ifdef QT_DEBUG
#define DEFAULTMSGTYPE MsgType::DEBUG
#else
#define DEFAULTMSGTYPE MsgType::CRITICAL
#endif
class Database {

  public:
    Database(QSqlDatabase database, bool logQueries = false, bool logErrors = true,
             MsgType type = DEFAULTMSGTYPE);
    ~Database();
    Database(QString databaseType, QString connectionName = QString(""),
             QString hostname = QString(""),
             QString databasename = QString("") ,
             QString username = QString(""), QString password = QString(""),
             qint64 port = 0, bool logQueries = false,
             bool logErrors = true, QString databaseOptions = "",
             MsgType type = DEFAULTMSGTYPE);
    QSqlDatabase getDatabase();
    QString getConnectionName();
    QSqlQuery getQuery();
    QSqlQuery getQuery(const QString &prepare);
    bool transaction(const QStringList &queries);
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
    void logMsg(const QString &value);
    bool rollbackTransaction();
    static DatabaseType getDatabaseType(QString s);
    static Schema *getSchema(DatabaseType db,
                             QSharedPointer<Database> database);
    Logger *getLogger() const;
  private:
    QSqlDatabase database;
    QString connectionName;
    bool supportTransactions;
    Logger *logger = nullptr;
    void init();
    void initLogger(bool logQueries, bool logErrors, MsgType type);
    bool logQueries;
    bool logErrors;
};
}
#endif // DATABASE_H
