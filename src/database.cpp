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
using namespace CuteEntityManager;

Database::Database(QSqlDatabase database) {
    this->database = database;
    this->init();
    this->connectionName = this->database.connectionName();

}

Database::Database(QString databaseType, QString connectionName,
                   QString databasename) {
    this->database = QSqlDatabase::addDatabase(databaseType, connectionName);
    this->connectionName = connectionName;
    this->database.setDatabaseName(databasename);
    this->init();
}

Database::Database(QString databaseType, QString connectionName,
                   QString hostname,
                   QString databasename,
                   QString username, QString password, qint64 port) {
    this->database = QSqlDatabase::addDatabase(databaseType, connectionName);
    this->connectionName = connectionName;
    this->database.setHostName(hostname);
    this->database.setDatabaseName(databasename);
    this->database.setUserName(username);
    this->database.setPassword(password);
    this->database.setPort(port);
    this->init();
}

void Database::init() {
    this->database.open();
    this->supportTransactions = this->database.driver()->hasFeature(
                                    QSqlDriver::Transactions);
}

Database::~Database() {
    if (this->database.isOpen()) {
        this->database.close();
    }
    QSqlDatabase::removeDatabase(this->connectionName);
}

QString Database::getConnectionName() {
    return this->connectionName;
}

bool Database::transaction(const QString &query) {
    bool rc = false;
    if (supportTransactions) {
        this->startTransaction();
        QSqlQuery sqlquery = QSqlQuery(this->database);
        sqlquery.exec(query);
        this->commitTransaction();
    } else {
        rc = this->exec(query);
    }
    qDebug() << "Executed Query:" << query;
    return rc;
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
        }
        ok = this->commitTransaction();
    } else {
        ok = this->exec(queries);
    }
    return ok;
}

bool Database::transaction(QSqlQuery &query) {
    this->startTransaction();
    query.exec();
    this->debugQuery(query);
    return this->commitTransaction();
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
//    case MYSQL:
//        return QSharedPointer<Schema>(new MysqlSchema());
//        break;
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
    qDebug() << query.executedQuery();
}

bool Database::select(QSqlQuery &query) {
    query.setForwardOnly(true);
    bool ok  = query.exec();
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
