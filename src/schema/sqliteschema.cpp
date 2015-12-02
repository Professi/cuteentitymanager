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
#include "sqliteschema.h"
#include "../database.h"
#include <QSqlRecord>
#include <QSqlResult>
#include "sqlitequerybuilder.h"
using namespace CuteEntityManager;

SqliteSchema::SqliteSchema(QSharedPointer<Database> database) : Schema(
        database, QSharedPointer<QueryBuilder>(new SqliteQueryBuilder(this, database))) {
}

SqliteSchema::~SqliteSchema() {
}

QSharedPointer<QHash<QString, QString>> SqliteSchema::getTypeMap() {
    if (this->typeMap->empty()) {
        this->typeMap->insert(TYPE_PK,
                              "integer PRIMARY KEY AUTOINCREMENT NOT NULL");
        this->typeMap->insert(TYPE_BIGPK,
                              "integer PRIMARY KEY AUTOINCREMENT NOT NULL");
        this->typeMap->insert(TYPE_BOOLEAN, "boolean");
        this->typeMap->insert(TYPE_SMALLINT, "integer");
        this->typeMap->insert(TYPE_INTEGER, "integer");
        this->typeMap->insert(TYPE_BIGINT, "integer");
        this->typeMap->insert(TYPE_FLOAT, "float");
        this->typeMap->insert(TYPE_DOUBLE, "double");
        this->typeMap->insert(TYPE_FLOAT, "real");
        this->typeMap->insert(TYPE_DECIMAL, "decimal(10,0)");
        this->typeMap->insert(TYPE_TEXT, "text");
        this->typeMap->insert(TYPE_STRING, "text");
        this->typeMap->insert(TYPE_CHAR, "char");
        this->typeMap->insert(TYPE_BINARY, "blob");
        this->typeMap->insert(TYPE_DATETIME, "datetime");
        this->typeMap->insert(TYPE_DATE, "date");
        this->typeMap->insert(TYPE_TIME, "time");
        this->typeMap->insert(TYPE_TIMESTAMP, "timestamp");
        this->typeMap->insert(TYPE_MONEY, "decimal(19,4)");
    }
    return this->typeMap;
}

QStringList SqliteSchema::findTableNames(QString schema) {
    Q_UNUSED(schema)
    auto l = QStringList();
    QString sql =
        "SELECT DISTINCT tbl_name FROM sqlite_master WHERE tbl_name<>'sqlite_sequence' ORDER BY tbl_name";
    auto q = this->database->getQuery();
    q.prepare(sql);
    this->database->select(q);
    while (q.next()) {
        l.append(q.value(0).toString());
    }
    return l;
}

QHash<QString, QStringList> SqliteSchema::findUniqueIndexes(
    const QSharedPointer<TableSchema>
    &table) {
    QHash<QString, QStringList> uniqueIndexes = QHash<QString, QStringList>();
    QSqlQuery q = this->database->getQuery();
    q.setForwardOnly(true);
    q.exec("PRAGMA index_list(" + this->quoteSimpleTableName(
               table->getName()) + ')');
    while (q.next()) {
        QString indexName = q.value("name").toString();
        QSqlQuery q2 = this->database->getQuery();
        q2.setForwardOnly(true);
        if (q.value("unique").toBool()) {
            q2.exec("PRAGMA index_info(" + this->quoteSimpleTableName(indexName) + ")");
            QStringList indexInfo = QStringList();
            while (q2.next()) {
                indexInfo.append(q2.value("name").toString());
            }
            uniqueIndexes.insert(indexName, indexInfo);
        }
    }
    return uniqueIndexes;
}

void SqliteSchema::findConstraints(const QSharedPointer<TableSchema> &ts) {
    QSqlQuery q = this->database->getQuery();
    q.setForwardOnly(true);
    q.exec("PRAGMA foreign_key_list(" + this->quoteSimpleTableName(
               ts->getName()) + ')');
    auto foreignKeys = ts->getRelations();
    while (q.next()) {
        bool ok;
        int id = q.value("id").toInt(&ok);
        if (ok) {
            auto rel = new QSqlRelation(q.value("table").toString(),
                                        q.value("from").toString(),
                                        q.value("to").toString());
            auto ptr = QSharedPointer<QSqlRelation>(rel);
            foreignKeys.insert(QString::number(id), ptr);
        }
    }
    ts->setRelations(foreignKeys);
}

QSharedPointer<TableSchema> SqliteSchema::loadTableSchema(QString name) {
    auto ptr = QSharedPointer<TableSchema>(new TableSchema());
    ptr->setName(name);
    ptr->setFullName(name);
    if (this->findColumns(ptr)) {
        this->findConstraints(ptr);
    } else {
        ptr.clear();
    }
    return ptr;
}
