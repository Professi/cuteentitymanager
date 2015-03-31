#ifndef SCHEMA_H
#define SCHEMA_H
#include "tableschema.h"
#include <QStringList>
#include <QHash>
#include <QSharedPointer>
#include <QSqlDatabase>
#include <memory>
#include "database.h"

namespace CuteEntityManager {

class Schema {
  public:
    Schema(std::shared_ptr<Database> database);
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
    virtual QStringList findUniqueIndexes(TableSchema schema);
    virtual QVariant getLastInsertID();
    virtual void refresh();
    virtual QString getRawTable(QString name);

    QHash<QString, QSharedPointer<TableSchema> > getTables() const;
    void setTables(const QHash<QString, QSharedPointer<TableSchema> > &value);

  protected:
    virtual QStringList findTableNames(QString schema = "") = 0;
    virtual QStringList findUniqueIndexes(QString tableName) = 0;
    virtual QSharedPointer<TableSchema> findConstraints(TableSchema ts) = 0;
    virtual QString getCreateTableSql(TableSchema ts) = 0;
    virtual bool findColumns(TableSchema ts) = 0;
    QSharedPointer<QHash<QString, QString>> typeMap;
    virtual QSharedPointer<TableSchema> *loadTableSchema(QString name)  = 0;
    virtual TableSchema *getTableSchema(QString name, bool refresh = false);
    std::shared_ptr<Database> database;
    QHash<QString, QSharedPointer<TableSchema>> tables;


};
}
#endif // SCHEMA_H
