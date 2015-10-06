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

    QString primaryKey(int length = 0) const;
    QString bigPrimaryKey(int length = 0) const;
    QString string(int length = 0, bool notNull = false,
                   QString defaultValue = "", bool unique = false,
                   QString checkConstraint = "") const;
    QString text(bool notNull = false, QString defaultValue = "",
                 bool unique = false, QString checkConstraint = "") const;
    QString smallInteger(int length = 0, bool notNull = false,
                         QString defaultValue = "", bool unique = false,
                         QString checkConstraint = "") const;
    QString integer(int length = 0, bool notNull = false,
                    QString defaultValue = "", bool unique = false,
                    QString checkConstraint = "") const;
    QString bigInteger(int length = 0, bool notNull = false,
                       QString defaultValue = "", bool unique = false,
                       QString checkConstraint = "") const;
    QString floatColumn(int precision = 0, bool notNull = false,
                        QString defaultValue = "", bool unique = false,
                        QString checkConstraint = "") const;
    QString doubleColumn(int precision = 0, bool notNull = false,
                         QString defaultValue = "", bool unique = false,
                         QString checkConstraint = "") const;
    QString decimal(int precision = 0, int scale = 0, bool notNull = false,
                    QString defaultValue = "", bool unique = false,
                    QString checkConstraint = "") const;
    QString dateTime(int precision = 0, bool notNull = false,
                     QString defaultValue = "", bool unique = false,
                     QString checkConstraint = "") const;
    QString timestamp(int precision = 0, bool notNull = false,
                      QString defaultValue = "", bool unique = false,
                      QString checkConstraint = "") const;
    QString time(int precision = 0, bool notNull = false,
                 QString defaultValue = "", bool unique = false,
                 QString checkConstraint = "") const;
    QString date( bool notNull = false, QString defaultValue = "") const;
    QString binary(int length = 0, bool notNull = false, bool unique = false,
                   QString checkConstraint = "") const;
    QString boolean(QString defaultValue = "", bool notNull = false) const;
    QString money(int precision = 0, int scale = 0, bool notNull = false,
                  QString defaultValue = "", bool unique = false,
                  QString checkConstraint = "") const;



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

    QHash<QString, QSharedPointer<TableSchema> > getTables();
    void setTables(const QHash<QString, QSharedPointer<TableSchema> > &value);

    QSharedPointer<Database> getDatabase() const;
    void setDatabase(const QSharedPointer<Database> &value);

    QSharedPointer<QueryBuilder> getQueryBuilder() const;

    QSharedPointer<QHash<QString, QString> > getAbstractTypeMap() const;
    void setAbstractTypeMap(const QSharedPointer<QHash<QString, QString> > &value);

  protected:
    virtual QString buildColumnSchema(QString type, QString length,
                                      bool notNull = false, QString defaultValue = "",
                                      bool unique = false, QString checkConstraint = "") const;
    virtual QString buildLengthString(QString length) const;
    virtual QString buildNotNullString(bool notNull) const;
    virtual QString buildUniqueString(bool unique) const;
    virtual QString buildDefaultString(QString def) const;
    virtual QString buildCheckString(QString check) const;
    virtual QString lengthToString(int length) const;
    virtual QString combineScaleAndPrecision(int precision, int scale) const;


    virtual QStringList findTableNames(QString schema = "") = 0;
    virtual QHash<QString, QStringList> findUniqueIndexes(const
            QSharedPointer<TableSchema>
            &table) = 0;
    virtual void findConstraints(const QSharedPointer<TableSchema> &ts) = 0;
    virtual bool findColumns(const QSharedPointer<TableSchema> &ts);
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
