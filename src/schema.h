#ifndef SCHEMA_H
#define SCHEMA_H
#include <QString>
#include "tableschema.h"
#include <QHash>
#include <QSharedPointer>

namespace CuteEntityManager {

class Schema {
public:
    Schema();
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
    virtual QString quoteSimpleColumnName(QString name);
    virtual QList<TableSchema> getTableSchemas(QString schema = "", bool refresh = false);
    virtual QList<QString> getTableNames(QString schema = "", $refresh = false);
    //virtual QueryBuilder getQueryBuilder();
    //virtual QueryBuilder createQueryBuilder();
    virtual QList<QString> findUniqueIndexes(TableSchema schema);
    virtual QString getLastInsertID(QString sequenceName = "");
    virtual void refresh();

protected:
    virtual QList<QString> findTableNames(QString schema = "");
    virtual QList<QString> findUniqueIndexes(QString tableName);
    virtual TableSchema findConstraints(TableSchema ts);
    virtual QString getCreateTableSql(TableSchema ts);
    virtual bool findColumns(TableSchema ts);
    QSharedPointer<QHash<QString, QString>> typeMap;
    virtual TableSchema loadTableSchema(QString name)  = 0;
    virtual TableSchema getTableSchema(QString name, bool refresh = false);
    virtual QList<QString> findTableNames(QString schema = "");

};
}
#endif // SCHEMA_H
