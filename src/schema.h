#ifndef SCHEMA_H
#define SCHEMA_H
#include <QString>
#include "tableschema.h"

namespace CuteEntityManager {

class Schema {
public:
    Schema();
    ~Schema();
protected:
    virtual QList<QString> findTableNames(QString schema = "");
    virtual QList<QString> findUniqueIndexes(QString tableName);
    virtual TableSchema findConstraints(TableSchema ts);
    virtual QString getCreateTableSql(TableSchema ts);
   virtual bool findColumns(TableSchema ts);


};
}
#endif // SCHEMA_H
