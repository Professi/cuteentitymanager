#ifndef PGSQLSCHEMA_H
#define PGSQLSCHEMA_H
#include "../schema.h"
namespace CuteEntityManager {
class PgSqlSchema : public Schema {
public:
    PgSqlSchema();
    ~PgSqlSchema();
    QHash<QString, QString> *getTypeMap();
};
}

#endif // PGSQLSCHEMA_H
