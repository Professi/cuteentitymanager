﻿#include "schema.h"
#include <QRegularExpression>
#include <QSqlRecord>
#include <QSqlQuery>
#include "database.h"
using namespace CuteEntityManager;

Schema::Schema(QSharedPointer<Database> database) {
    this->database = database;
    this->typeMap = QSharedPointer<QHash<QString, QString>>(new QHash<QString, QString>());
}

Schema::~Schema() {

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
        TableSchema *t = this->getTableSchema(name, refresh);
        if (t) {
            this->tables.insert(name, QSharedPointer<TableSchema>(t));
        }
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
        QRegularExpression re("/\\{\\{(.*?)\\}\\}/");
        return name.replace(re, "\\1");
    }
    return name;
}

bool Schema::containsTable(QString tblname) {
    return this->tables.contains(tblname);
}

QString Schema::quoteValue(QString str) {

}

TableSchema *Schema::getTableSchema(QString name, bool refresh) {
    if (refresh) {
        this->refresh();
    }
    if (this->tables.contains(name)) {
        return this->tables.value(name).data();
    }
    QString realName = this->getRawTable(name);
    auto ts = this->loadTableSchema(realName);
    if (ts.data()) {
        this->tables.insert(name, ts);
    }
    return ts.data();
}

QSharedPointer<Database> Schema::getDatabase() const {
    return database;
}

void Schema::setDatabase(const QSharedPointer<Database> &value) {
    database = value;
}

QHash<QString, QSharedPointer<TableSchema> > Schema::getTables() const {
    return this->tables;
}

void Schema::setTables(const QHash<QString, QSharedPointer<TableSchema> > &value) {
    tables = value;
}

