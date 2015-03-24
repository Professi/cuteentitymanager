#ifndef MYSQLSCHEMA_H
#define MYSQLSCHEMA_H
#include "../schema.h"
namespace CuteEntityManager {
class MysqlSchema : public Schema {
public:
    MysqlSchema();
    ~MysqlSchema();
    QHash<QString, QString> *getTypeMap();
};
}
#endif // MYSQLSCHEMA_H
