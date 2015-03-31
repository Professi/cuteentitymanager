#ifndef SQLITESCHEMA_H
#define SQLITESCHEMA_H
#include <memory>
#include "../database.h"
#include "../schema.h"
namespace CuteEntityManager {
class SqliteSchema : public Schema {
  public:
    SqliteSchema(std::shared_ptr<Database> database);
    ~SqliteSchema();
    QHash<QString, QString> *getTypeMap();
};
}
#endif // SQLITESCHEMA_H
