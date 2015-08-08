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

Schema::Schema(QSharedPointer<Database> database,
               QSharedPointer<QueryBuilder> builder) {
    this->database = database;
    this->abstractTypeMap = QSharedPointer<QHash<QString, QString>>
                            (new QHash<QString, QString>());
    this->queryBuilder = builder;
    this->typeMap = QSharedPointer<QHash<QString, QString>>(new
                    QHash<QString, QString>());
    this->initAbstractDatabaseTypes();
}

Schema::~Schema() {
}

void Schema::initAbstractDatabaseTypes() {
    this->abstractTypeMap->insert("bool", TYPE_SMALLINT);
    this->abstractTypeMap->insert("short", TYPE_SMALLINT);
    this->abstractTypeMap->insert("int", TYPE_INTEGER);
    this->abstractTypeMap->insert("long", TYPE_INTEGER);
    this->abstractTypeMap->insert("long long", TYPE_INTEGER);
    this->abstractTypeMap->insert("qlonglong", TYPE_INTEGER);
    this->abstractTypeMap->insert("float", TYPE_FLOAT);
    this->abstractTypeMap->insert("double", TYPE_FLOAT);
    this->abstractTypeMap->insert("long double", TYPE_FLOAT);
    this->abstractTypeMap->insert("qint", TYPE_INTEGER);
    this->abstractTypeMap->insert("quint", TYPE_INTEGER);
    this->abstractTypeMap->insert("quuid", TYPE_INTEGER);
    this->abstractTypeMap->insert("qfloat", TYPE_FLOAT);
    this->abstractTypeMap->insert("unsigned short", TYPE_SMALLINT);
    this->abstractTypeMap->insert("unsigned int", TYPE_INTEGER);
    this->abstractTypeMap->insert("unsigned long", TYPE_INTEGER);
    this->abstractTypeMap->insert("unsigned long long", TYPE_INTEGER);
    this->abstractTypeMap->insert("char", TYPE_CHAR);
    this->abstractTypeMap->insert("std::string", TYPE_TEXT);
    this->abstractTypeMap->insert("std::wstring", TYPE_TEXT);
    this->abstractTypeMap->insert("QString", TYPE_TEXT);
    this->abstractTypeMap->insert("QVariant", TYPE_TEXT);
    this->abstractTypeMap->insert("QUuid", TYPE_TEXT);
    this->abstractTypeMap->insert("QDate", TYPE_DATE);
    this->abstractTypeMap->insert("QTime", TYPE_TIME);
    this->abstractTypeMap->insert("QDateTime", TYPE_DATETIME);
    this->abstractTypeMap->insert("QByteArray", TYPE_BINARY);
    this->abstractTypeMap->insert("QBitArray", TYPE_BINARY);
}

QString Schema::quoteSimpleTableName(QString name) {
    return name.indexOf("`") != -1 ? name : ("`" + name + "`");
}

QString Schema::quoteTableName(QString name) {
    if (name.indexOf("(") != -1 || name.indexOf("{{") != -1) {
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
    if (name.indexOf("(") != -1 || name.indexOf("[[") != -1
            || name.indexOf("{{") != -1) {
        return name;
    }
    int pos = name.indexOf(".");
    QString prefix = "";
    if (pos != -1 ) {
        prefix = this->quoteTableName(name.mid(0, pos)) + ".";
        name = name.mid(pos + 1);
    }
    return prefix + this->quoteSimpleColumnName(name);
}

QString Schema::quoteSimpleColumnName(QString name) {
    return name.indexOf("`") != -1 || name == "*" ? name : ("`" + name + "`");
}

QHash<QString, QSharedPointer<TableSchema> > Schema::getTableSchemas(
    QString schema, bool refresh) {
    QStringList names = this->getTableNames();
    for (int i = 0; i < names.size(); ++i) {
        QString name = names.at(i);
        if (schema != "") {
            name = schema + "." + name;
        }
        this->getTableSchema(name, refresh);
    }
    return this->tables;
}

QStringList Schema::getTableNames(QString schema) {
    Q_UNUSED(schema)
    return this->database->getDatabase().tables();
}

QVariant Schema::getLastInsertID() {
    QSqlQuery q(this->database->getDatabase());
    auto lastId = q.lastInsertId();
    return lastId;
}

void Schema::refresh() {
    this->tables.clear();
}

QString Schema::getRawTable(QString name) {
    if (name.indexOf("{{")) {
        QRegularExpression re(QRegularExpression::escape("/\\{\\{(.*?)\\}\\}/"));
        return name.replace(re, QRegularExpression::escape("\\1"));
    }
    return name;
}

bool Schema::containsTable(QString tblname) {
    if (this->tables.size() !=
            this->database->getDatabase().tables().size()) {
        this->setTables(this->getTableSchemas());
    }
    return this->database->getDatabase().tables().contains(tblname);
}

QSharedPointer<TableSchema> Schema::getTableSchema(QString name, bool refresh) {
    if (this->tables.contains(name) && !refresh) {
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

void Schema::setAbstractTypeMap(const QSharedPointer<QHash<QString, QString> >
                                &value) {
    abstractTypeMap = value;
}

QString Schema::buildColumnSchema(QString type, QString length, bool notNull,
                                  QString defaultValue,
                                  bool unique, QString checkConstraint) const {
    return type + this->buildLengthString(length) + this->buildNotNullString(
               notNull) + this->buildUniqueString(unique) + this->buildDefaultString(
               defaultValue) + this->buildCheckString(checkConstraint);
}

QString Schema::buildLengthString(QString length) const {
    return length.isEmpty() ? "" : "(" + length + ")";
}

QString Schema::buildNotNullString(bool notNull) const {
    return notNull ? " NOT NULL" : "";
}

QString Schema::buildUniqueString(bool unique) const {
    return unique ? " UNIQUE" : "";
}

QString Schema::buildDefaultString(QString def) const {

}

QString Schema::buildCheckString(QString check) const {
    return check.isEmpty() ? "" : (" CHECK (" + check + ")");
}


QHash<QString, QSharedPointer<TableSchema> > Schema::getTables() const {
    return this->tables;
}

void Schema::setTables(const QHash<QString, QSharedPointer<TableSchema> >
                       &value) {
    tables = value;
}

