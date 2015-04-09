#ifndef SCHEMA_H
#define SCHEMA_H
#include "tableschema.h"
#include <QStringList>
#include <QHash>
#include <QSharedPointer>
#include <QSqlField>
namespace CuteEntityManager {
class Database;
class Schema {
  public:
    Schema(QSharedPointer<Database> database);
    virtual ~Schema();
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

    //    /**
    //     * @var array list of ALL table names in the database
    //     */
    //    private $_tableNames = [];
    //    /**
    //     * @var array list of loaded table metadata (table name => TableSchema)
    //     */
    //    private $_tables = [];
    //    /**
    //     * @var QueryBuilder the query builder for this database
    //     */
    //    private $_builder;


    virtual QHash<QString, QString> *getTypeMap() = 0;
    virtual QString quoteSimpleTableName(QString name);
    virtual QString quoteTableName(QString name);
    virtual QString quoteColumnName(QString name);
    virtual QString quoteSimpleColumnName(QString name);
    virtual QHash<QString, QSharedPointer<TableSchema>> getTableSchemas(QString schema = "", bool refresh = false);
    virtual QStringList getTableNames(QString schema = "");
    //virtual QueryBuilder getQueryBuilder();
    //virtual QueryBuilder createQueryBuilder();
    virtual QVariant getLastInsertID();
    virtual void refresh();
    virtual QString getRawTable(QString name);
    virtual bool containsTable(QString tblname);
    virtual QString quoteValue(QString str);

    QHash<QString, QSharedPointer<TableSchema> > getTables() const;
    void setTables(const QHash<QString, QSharedPointer<TableSchema> > &value);

    QSharedPointer<Database> getDatabase() const;
    void setDatabase(const QSharedPointer<Database> &value);

protected:
    virtual QStringList findTableNames(QString schema = "") = 0;
    virtual QHash<QString, QStringList> findUniqueIndexes(const QSharedPointer<TableSchema> &table) = 0;
    virtual void findConstraints(const QSharedPointer<TableSchema> &ts) = 0;
    virtual bool findColumns(const QSharedPointer<TableSchema> &ts) = 0;
    virtual QSharedPointer<TableSchema> loadTableSchema(QString name)  = 0;
    virtual TableSchema *getTableSchema(QString name, bool refresh = false);
    QSharedPointer<Database> database;
    QSharedPointer<QHash<QString, QString>> typeMap;
    QHash<QString, QSharedPointer<TableSchema>> tables;


};
}
#endif // SCHEMA_H
