#ifndef SQLITEQUERYBUILDER_H
#define SQLITEQUERYBUILDER_H
#include "../querybuilder.h"
namespace CuteEntityManager {
class SqliteQueryBuilder : public QueryBuilder
{
public:
    SqliteQueryBuilder(QSharedPointer<Schema> schema, QSharedPointer<Database> database);
    ~SqliteQueryBuilder();

    virtual QString truncateTable(QString tableName) const;
    virtual QString dropIndex(QString name, QString tableName) const;
    virtual QString dropColumn(QString tableName, QString columName)const;
    virtual QString renameColumn(QString tableName, QString oldName, QString newName) const;
    virtual QString addForeignKey(QString name, QString tableName, QStringList columns, QString refTableName,
                                  QStringList refColumns, QString deleteConstraint, QString updateConstraint) const;
    virtual QString dropForeignKey(QString name, QString tableName) const;
    virtual QString alterColumn(QString tableName, QString columnName, QString newType) const;
    virtual QString addPrimaryKey(QString name, QString tableName, QStringList columns) const;
    virtual QString dropPrimaryKey(QString name, QString tableName) const;

};

}
#endif // SQLITEQUERYBUILDER_H
