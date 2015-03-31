#ifndef PGSQLSCHEMA_H
#define PGSQLSCHEMA_H
#include <memory>
#include "../database.h"
#include "../schema.h"
namespace CuteEntityManager {
class PgSqlSchema : public Schema {
  public:
    PgSqlSchema(std::shared_ptr<Database>database);
    ~PgSqlSchema();
    QHash<QString, QString> *getTypeMap();
};
}

#endif // PGSQLSCHEMA_H
