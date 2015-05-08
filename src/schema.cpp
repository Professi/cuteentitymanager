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
#include "schema.h"
#include <QRegularExpression>
#include <QSqlRecord>
#include <QSqlQuery>
#include "database.h"
using namespace CuteEntityManager;

Schema::Schema(QSharedPointer<Database> database) {
    this->database = database;
    this->abstractTypeMap = QSharedPointer<QHash<QString, QString>>(new QHash<QString, QString>());
    this->queryBuilder = QSharedPointer<QueryBuilder>();
    this->typeMap = QSharedPointer<QHash<QString, QString>>(new QHash<QString, QString>());
    this->initAbstractDatabaseTypes();
}

Schema::~Schema() {

}

void Schema::initAbstractDatabaseTypes() {
    this->abstractTypeMap.create();
    this->abstractTypeMap.data()->insert("bool", TYPE_SMALLINT);
    this->abstractTypeMap.data()->insert("short", TYPE_SMALLINT);
    this->abstractTypeMap.data()->insert("int", TYPE_INTEGER);
    this->abstractTypeMap.data()->insert("long", TYPE_INTEGER);
    this->abstractTypeMap.data()->insert("long long", TYPE_INTEGER);
    this->abstractTypeMap.data()->insert("qlonglong", TYPE_INTEGER);
    this->abstractTypeMap.data()->insert("float", TYPE_FLOAT);
    this->abstractTypeMap.data()->insert("double", TYPE_FLOAT);
    this->abstractTypeMap.data()->insert("long double", TYPE_FLOAT);
    this->abstractTypeMap.data()->insert("qint", TYPE_INTEGER);
    this->abstractTypeMap.data()->insert("quint", TYPE_INTEGER);
    this->abstractTypeMap.data()->insert("quuid", TYPE_INTEGER);
    this->abstractTypeMap.data()->insert("qfloat", TYPE_FLOAT);
    this->abstractTypeMap.data()->insert("unsigned short", TYPE_SMALLINT);
    this->abstractTypeMap.data()->insert("unsigned int", TYPE_INTEGER);
    this->abstractTypeMap.data()->insert("unsigned long", TYPE_INTEGER);
    this->abstractTypeMap.data()->insert("unsigned long long", TYPE_INTEGER);
    this->abstractTypeMap.data()->insert("char", TYPE_CHAR);
    this->abstractTypeMap.data()->insert("std::string", TYPE_TEXT);
    this->abstractTypeMap.data()->insert("std::wstring", TYPE_TEXT);
    this->abstractTypeMap.data()->insert("QString", TYPE_TEXT);
    this->abstractTypeMap.data()->insert("QVariant", TYPE_TEXT);
    this->abstractTypeMap.data()->insert("QUuid", TYPE_TEXT);
    this->abstractTypeMap.data()->insert("QDate", TYPE_DATE);
    this->abstractTypeMap.data()->insert("QTime", TYPE_TIME);
    this->abstractTypeMap.data()->insert("QDateTime", TYPE_DATETIME);
    this->abstractTypeMap.data()->insert("QByteArray", TYPE_BINARY);
    this->abstractTypeMap.data()->insert("QBitArray", TYPE_BINARY);
}

QString Schema::quoteSimpleTableName(QString name) {
    return name.indexOf("`") ? name : "`" + name + "`";
}

QString Schema::quoteTableName(QString name) {
    if (name.indexOf("(") || name.indexOf("{{")) {
        return name;
    }
    if (name.indexOf(".") == -1) {
        return this->quoteSimpleTableName(name);
    }
    QStringList parts = name.split(".");
    for (int i = 0; i < parts.size(); ++i) {
        parts.replace(i, this->quoteSimpleTableName(parts.at(i)));
    }
    return parts.join(".");
}

QString Schema::quoteColumnName(QString name) {
    if (name.indexOf("(") || name.indexOf("[[") || name.indexOf("{{")) {
        return name;
    }
    int pos = name.indexOf(".");
    QString prefix = "";
    if (pos) {
        prefix = this->quoteTableName(name.mid(0, pos)) + ".";
        name = name.mid(pos + 1);
    }
    return prefix + this->quoteSimpleColumnName(name);
}

QString Schema::quoteSimpleColumnName(QString name) {
    return name.indexOf("`") || name == "*" ? name : "`" + name + "`";
}

QHash<QString, QSharedPointer<TableSchema> > Schema::getTableSchemas(QString schema, bool refresh) {
    QStringList names = this->getTableNames();
    for (int i = 0; i < names.size(); ++i) {
        QString name;
        if (schema != "") {
            name = schema + "." + names.at(i);
        }
        this->getTableSchema(name, refresh);
    }
    return this->tables;
}

QStringList Schema::getTableNames(QString schema) {
    return this->database.data()->getDatabase().tables();
}

QVariant Schema::getLastInsertID() {
    QSqlQuery q(this->database.data()->getDatabase());
    return q.lastInsertId();
}

void Schema::refresh() {
    this->tables.clear();
}

QString Schema::getRawTable(QString name) {
    if (name.indexOf("{{")) {
        QRegularExpression re(QRegularExpression::escape("/\\{\{(.*?)\\}\\}/"));
        return name.replace(re, QRegularExpression::escape("\\1"));
    }
    return name;
}

bool Schema::containsTable(QString tblname) {
    return this->tables.contains(tblname);
}

QSharedPointer<TableSchema> Schema::getTableSchema(QString name, bool refresh) {
    if (refresh) {
        this->refresh();
    }
    if (this->tables.contains(name)) {
        return this->tables.value(name);
    }
    QString realName = this->getRawTable(name);
    auto ts = this->loadTableSchema(realName);
    if (ts.data()) {
        this->tables.insert(name, ts);
    }
    return ts;
}

QSharedPointer<Database> Schema::getDatabase() const {
    return database;
}

void Schema::setDatabase(const QSharedPointer<Database> &value) {
    database = value;
}
QSharedPointer<QueryBuilder> Schema::getQueryBuilder() const {
    return queryBuilder;
}

QSharedPointer<QHash<QString, QString> > Schema::getAbstractTypeMap() const {
    return abstractTypeMap;
}

void Schema::setAbstractTypeMap(const QSharedPointer<QHash<QString, QString> > &value) {
    abstractTypeMap = value;
}


QHash<QString, QSharedPointer<TableSchema> > Schema::getTables() const {
    return this->tables;
}

void Schema::setTables(const QHash<QString, QSharedPointer<TableSchema> > &value) {
    tables = value;
}

