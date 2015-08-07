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
#ifndef SCHEMA_H
#define SCHEMA_H
#include <QStringList>
#include <QHash>
#include <QSharedPointer>
#include <QSqlField>
#include "tableschema.h"
#include "querybuilder.h"
namespace CuteEntityManager {
class Database;
class Schema {
  public:
    Schema(QSharedPointer<Database> database, QSharedPointer<QueryBuilder> builder);
    virtual ~Schema();
    //http://doc.qt.io/qt-5/sql-types.html
    const QString TYPE_PK = "pk";
    const QString TYPE_BIGPK = "bigpk";
    const QString TYPE_STRING = "string";
    const QString TYPE_TEXT = "text";
    const QString TYPE_SMALLINT = "smallint";
    const QString TYPE_INTEGER = "integer";
    const QString TYPE_BIGINT = "bigint";
    const QString TYPE_FLOAT = "float";
    const QString TYPE_DOUBLE = "double";
    const QString TYPE_DECIMAL = "decimal";
    const QString TYPE_DATETIME = "datetime";
    const QString TYPE_TIMESTAMP = "timestamp";
    const QString TYPE_TIME = "time";
    const QString TYPE_DATE = "date";
    const QString TYPE_CHAR = "char";
    const QString TYPE_BINARY = "binary";
    const QString TYPE_BOOLEAN = "boolean";
    const QString TYPE_MONEY = "money";

    virtual QSharedPointer<QHash<QString, QString> >getTypeMap() = 0;
    virtual QString quoteSimpleTableName(QString name);
    virtual QString quoteTableName(QString name);
    virtual QString quoteColumnName(QString name);
    virtual QString quoteSimpleColumnName(QString name);
    virtual QHash<QString, QSharedPointer<TableSchema>> getTableSchemas(
                QString schema = "",
                bool refresh = false);
    virtual QSharedPointer<TableSchema> getTableSchema(QString name,
            bool refresh = false);
    virtual QStringList getTableNames(QString schema = "");
    virtual QVariant getLastInsertID();
    virtual void refresh();
    virtual QString getRawTable(QString name);
    virtual bool containsTable(QString tblname);

    QHash<QString, QSharedPointer<TableSchema> > getTables() const;
    void setTables(const QHash<QString, QSharedPointer<TableSchema> > &value);

    QSharedPointer<Database> getDatabase() const;
    void setDatabase(const QSharedPointer<Database> &value);

    QSharedPointer<QueryBuilder> getQueryBuilder() const;

    QSharedPointer<QHash<QString, QString> > getAbstractTypeMap() const;
    void setAbstractTypeMap(const QSharedPointer<QHash<QString, QString> > &value);

  protected:
    virtual QStringList findTableNames(QString schema = "") = 0;
    virtual QHash<QString, QStringList> findUniqueIndexes(const
            QSharedPointer<TableSchema>
            &table) = 0;
    virtual void findConstraints(const QSharedPointer<TableSchema> &ts) = 0;
    virtual bool findColumns(const QSharedPointer<TableSchema> &ts) = 0;
    virtual QSharedPointer<TableSchema> loadTableSchema(QString name)  = 0;
    virtual void initAbstractDatabaseTypes();
    QSharedPointer<Database> database;
    QSharedPointer<QHash<QString, QString>> typeMap;
    QSharedPointer<QHash<QString, QString>> abstractTypeMap;
    QHash<QString, QSharedPointer<TableSchema>> tables;
    QSharedPointer<QueryBuilder> queryBuilder;


};
}
#endif // SCHEMA_H
