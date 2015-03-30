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
namespace CuteEntityManager {

Database::Database(QSqlDatabase database) {
    this->database = database;
    this->init();
    this->connectionName = this->database.connectionName();

}

Database::Database(QString databaseType, QString connectionName, QString databasename) {
    this->database = QSqlDatabase::addDatabase(databaseType, connectionName);
    this->connectionName = connectionName;
    this->database.setDatabaseName(databasename);
    this->init();
}

Database::Database(QString databaseType, QString connectionName, QString hostname, QString databasename,
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
    this->databasetype = this->getDatabaseType();
    this->supportTransactions = this->database.driver()->hasFeature(QSqlDriver::Transactions);
    this->tableList = new QStringList();
    this->getTableListFromDatabase();
    this->createSequenceTable();
}


DatabaseType Database::getDatabaseType() {
    return CuteEntityManager::getDatabaseType(this->database.driverName());
}

void Database::getTableListFromDatabase() {
    if (this->database.open()) {
        QString q = "";
        if (this->databasetype == CuteEntityManager::SQLITE) {
            q = this->sqliteTableList();
        } else if (this->databasetype == CuteEntityManager::MYSQL) {
            q = this->mysqlTableList();
        } else if (this->databasetype == CuteEntityManager::PGSQL) {
            q = this->pgsqlSeqTable();
        }
        QSqlQuery query = QSqlQuery(this->database);
        query.prepare(q);
        this->select(query);
        this->setTableList(query);
    }
}

void Database::setTableList(QSqlQuery &q) {
    while (q.next()) {
        this->tableList->append(q.value(0).toString());
    }
}


//QString Database::mysqlTableList() {
//    return "SHOW TABLES;";
//}

//QString Database::pgsqlTableList() {
//    return "SELECT table_name FROM information_schema.tables WHERE table_catalog = '"+this->database.databaseName()+"';";
//}

Database::~Database() {
    if (this->database.isOpen()) {
        this->database.close();
    }
    QSqlDatabase::removeDatabase(this->connectionName);
    delete this->tableList;
}

QString Database::getConnectionName() {
    return this->connectionName;
}

void Database::setSeqTable(bool seqTable) {
    this->seqTable = seqTable;
}

bool Database::isSeqTable() {
    return this->seqTable;
}

//QString Database::pgsqlSeqTable() {
//    return "CREATE TABLE IF NOT EXISTS sequence (SEQ_NAME varchar(255) NOT NULL UNIQUE , SEQ_COUNT bigint NOT NULL);";
//}

//QString Database::mysqlSeqTable() {
//    return "CREATE TABLE IF NOT EXISTS `sequence` (`SEQ_NAME` varchar(255) NOT NULL UNIQUE , `SEQ_COUNT` bigint(20) unsigned NOT NULL) CHARSET = utf8";
//}

//QString Database::sqliteSeqTable() {
//    return "CREATE TABLE  IF NOT EXISTS \"sequence\" (\"SEQ_NAME\" TEXT PRIMARY KEY  NOT NULL , \"SEQ_COUNT\" INTEGER NOT NULL );";
//}

QChar Database::escapeChar() {
    QChar c = QChar();
    if (this->databasetype == CuteEntityManager::SQLITE) {
        c = '\'';
    } else if (this->databasetype == CuteEntityManager::MYSQL) {
        c = '`';
    }
    return c;
}


bool Database::transaction(const QString &query) {
    bool rc = false;
    if (supportTransactions) {
        this->database.transaction();
        QSqlQuery sqlquery = QSqlQuery(this->database);
        sqlquery.exec(query);
        if (!this->database.commit()) {
            this->database.rollback();
        }
    } else {
        rc = this->exec(query);
    }
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
        if (!this->database.commit()) {
            this->database.rollback();
        } else {
            ok = true;
        }
    } else {
        ok = this->exec(queries);
    }
    return ok;
}

bool Database::transaction(QSqlQuery &query) {
    this->database.transaction();
    query.exec();
    if (!this->database.commit()) {
        this->database.rollback();
        return false;
    }
    return true;
}

bool Database::transaction(QList<QSqlQuery> &queries) {
    this->database.transaction();
    QSqlQuery q;
    for (int var = 0; var < queries.size(); ++var) {
        q = queries.at(var);
        q.exec();
    }
    if (!this->database.commit()) {
        this->database.rollback();
        return false;
    }
    return true;
}

bool Database::exec(QString query) {
    this->database.transaction();
    QSqlQuery q = QSqlQuery(this->database);
    q.exec(query);
    if (!this->database.commit()) {
        this->database.rollback();
        return false;
    }
    return true;
}

bool Database::exec(QStringList queries) {
    QSqlQuery q = QSqlQuery(this->database);
    bool ok = true;
    for (int var = 0; var < queries.size() && ok; ++var) {
        ok = q.exec(queries.at(var));
        if (!ok) {
            break;
        }
    }
    return ok;
}

bool Database::exec(QSqlQuery query) {
    return query.exec();
}

bool Database::exec(QList<QSqlQuery> queries) {
    bool ok = true;
    QSqlQuery q = QSqlQuery(this->database);
    for (int var = 0; var < queries.size() && ok; ++var) {
        q = queries.at(var);
        ok = q.exec();
        if (!ok) {
            break;
        }
    }
    return ok;
}

bool Database::select(QSqlQuery &query) {
    query.setForwardOnly(true);
    return query.exec();
}

QSqlQuery Database::select(const QString &query) {
    QSqlQuery q = QSqlQuery(this->database);
    q.exec(query);
    return q;
}

QString Database::querySequenceCounter() {
    return "INSERT INTO sequence (SEQ_NAME, SEQ_COUNT) VALUES(\'id_count\',\'0\');";
}

void Database::refreshTableList() {
    this->tableList->clear();
    this->getTableListFromDatabase();
}

bool Database::containsTable(QString tblname) {
    return this->tableList->contains(tblname);
}

void Database::createSequenceTable() {
    if (this->database.open() && this->getLastId() == -1) {
        QString query = "";
        QStringList l = QStringList();
        if (this->databasetype == CuteEntityManager::MYSQL) {
            query = this->mysqlSeqTable();
        } else if (this->databasetype == CuteEntityManager::SQLITE) {
            query = this->sqliteSeqTable();
        } else if (this->databasetype == CuteEntityManager::PGSQL) {
            query = this->pgsqlSeqTable();
        }
        l.append(query);
        l.append(this->querySequenceCounter());
        if (this->transaction(l)) {
            this->setSeqTable(true);
        } else {
            this->setSeqTable(false);
        }
    } else {
        this->setSeqTable(true);
    }
}

bool Database::updateSequenceCounter(QSqlQuery &q) {
    QList<QSqlQuery> l = QList<QSqlQuery>();
    l.append(QSqlQuery("UPDATE sequence SET SEQ_COUNT=(SEQ_COUNT+1);", this->database));
    l.append(q);
    return this->transaction(l);
}

qint64 Database::getLastId() {
    qint64 id = -1;
    QSqlQuery q = this->select("SELECT SEQ_COUNT FROM sequence WHERE SEQ_NAME=\'id_count\';");
    if (q.next()) {
        id = q.value(0).toInt();
    }
    return id;
}

QSqlDatabase Database::getDatabase() {
    return this->database;
}

}
