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

#include "database.h"
#include "logger.h"
#include <QDir>
#include "schema/mysqlschema.h"
using namespace CuteEntityManager;

Database::Database(QSqlDatabase database, bool logQueries,
                   bool logErrors, MsgType type) {
    this->database = database;
    this->init();
    this->connectionName = this->database.connectionName();
    this->initLogger(logQueries, logErrors, type);
}

Database::Database(QString databaseType, QString connectionName,
                   QString hostname,
                   QString databasename,
                   QString username, QString password, qint64 port,
                   bool logQueries, bool logErrors, QString databaseOptions, MsgType type) {
    this->database = QSqlDatabase::addDatabase(databaseType, connectionName);
    this->connectionName = connectionName;
    if (!hostname.isEmpty()) {
        this->database.setHostName(hostname);
    }
    if (!databasename.isEmpty()) {
        this->database.setDatabaseName(databasename);
    }
    if (!username.isEmpty()) {
        this->database.setUserName(username);
    }
    if (!password.isEmpty()) {
        this->database.setPassword(password);
    }
    if (port != 0) {
        this->database.setPort(port);
    }
    if (!databaseOptions.isEmpty()) {
        this->database.setConnectOptions(databaseOptions);
    }
    this->init();
    this->initLogger(logQueries, logErrors, type);
}

Logger *Database::getLogger() const {
    return logger;
}

void Database::init() {
    this->database.open();
    this->supportTransactions = this->database.driver()->hasFeature(
                                    QSqlDriver::Transactions);
}

void Database::initLogger(bool logQueries, bool logErrors,
                          MsgType type) {
    this->logQueries = logQueries;
    this->logErrors = logErrors;
    this->logger = new Logger(QDir::currentPath() + "/db" + this->connectionName +
                              ".log", type);
}

Database::~Database() {
    if (this->logger) {
        delete this->logger;
        this->logger = nullptr;
    }
    if (this->database.isOpen()) {
        this->database.close();
    }
    QSqlDatabase::removeDatabase(this->connectionName);
}

QString Database::getConnectionName() {
    return this->connectionName;
}

QSqlQuery Database::getQuery() {
    return QSqlQuery(this->database);
}

QSqlQuery Database::getQuery(const QString &prepare) {
    QSqlQuery q = QSqlQuery(this->database);
    q.prepare(prepare);
    return q;
}

bool Database::transaction(const QStringList &queries) {
    bool ok = false;
    if (this->supportTransactions) {
        this->database.transaction();
        QSqlQuery sqlquery = QSqlQuery(this->database);
        for (int var = 0; var < queries.size(); ++var) {
            sqlquery.exec(queries.at(var));
            this->debugQuery(sqlquery);
        }
        ok = this->commitTransaction();
    } else {
        ok = this->exec(queries);
    }
    return ok;
}

bool Database::transaction(QList<QSqlQuery> &queries) {
    this->startTransaction();
    QSqlQuery q;
    for (int var = 0; var < queries.size(); ++var) {
        q = queries.at(var);
        q.exec();
        this->debugQuery(q);
    }
    return this->commitTransaction();
}


bool Database::commitTransaction() {
    return this->supportTransactions && this->database.commit();
}

bool Database::rollbackTransaction() {
    this->logger->logMsg("Transaction rolled back!" + this->database.lastError().text(),MsgType::WARNING);
    return supportTransactions && this->database.rollback();
}

DatabaseType Database::getDatabaseType(QString s) {
    if (s == "qmysql") {
        return DatabaseType::MYSQL;
    } else if (s == "qpgsql") {
        return DatabaseType::PGSQL;
    } else {
        return DatabaseType::SQLITE;
    }
}

QSharedPointer<Schema> Database::getSchema(DatabaseType db,
        QSharedPointer<Database> database) {
    switch (db) {
    case DatabaseType::SQLITE:
        return QSharedPointer<Schema>(new SqliteSchema(database));;
        break;
    //    case PGSQL:
    //        return QSharedPointer<Schema>(new PgSqlSchema());
    //        break;
    case DatabaseType::MYSQL:
        return QSharedPointer<Schema>(new MysqlSchema(database));
        break;
    default:
        return QSharedPointer<Schema>(new SqliteSchema(database));
        break;
    }
}

bool Database::exec(const QString &query) {
    QSqlQuery q = QSqlQuery(this->database);
    bool ok = q.exec(query);
    this->debugQuery(q);
    return ok;
}

bool Database::exec(QStringList queries) {
    QSqlQuery q = QSqlQuery(this->database);
    bool ok = true;
    for (int var = 0; var < queries.size() && ok; ++var) {
        ok = q.exec(queries.at(var));
        this->debugQuery(q);
        if (!ok) {
            break;
        }
    }
    return ok;
}

bool Database::exec(QSqlQuery &query) {
    bool ok = query.exec();
    this->debugQuery(query);
    return ok;
}

bool Database::exec(QList<QSqlQuery> queries) {
    bool ok = true;
    QSqlQuery q = QSqlQuery(this->database);
    for (int var = 0; var < queries.size() && ok; ++var) {
        q = queries.at(var);
        ok = q.exec();
        this->debugQuery(q);
        if (!ok) {
            break;
        }
    }
    return ok;
}

void Database::debugQuery(const QSqlQuery &query) const {
    if (this->logger && this->logErrors) {
        this->logger->lastError(query, this->logQueries);
    } else {
        qDebug() << query.executedQuery();
    }
}

bool Database::select(QSqlQuery &query) {
    query.setForwardOnly(true);
    bool ok = query.exec();
    this->debugQuery(query);
    return ok;
}

QSqlQuery Database::select(const QString &query) {
    QSqlQuery q = QSqlQuery(this->database);
    q.exec(query);
    this->debugQuery(q);
    return q;
}

void Database::startTransaction() {
    this->database.transaction();
}

QSqlDatabase Database::getDatabase() {
    return this->database;
}
