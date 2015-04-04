#ifndef SQLITESCHEMA_H
#define SQLITESCHEMA_H
#include "../schema.h"
namespace CuteEntityManager {
class TableSchema;
class SqliteSchema : public Schema {
  public:
    SqliteSchema(QSharedPointer<Database> database);
    ~SqliteSchema();
    QHash<QString, QString> *getTypeMap();
protected:

    virtual QStringList findTableNames(QString schema = "");
    virtual QHash<QString, QStringList> findUniqueIndexes(const QSharedPointer<TableSchema> &table);
    virtual void findConstraints(const QSharedPointer<TableSchema> &ts);
    virtual bool findColumns(const QSharedPointer<TableSchema> &ts);
    virtual QSharedPointer<TableSchema> loadTableSchema(QString name);
};
}
#endif // SQLITESCHEMA_H
