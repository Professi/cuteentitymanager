#ifndef SQLITESCHEMA_H
#define SQLITESCHEMA_H

#include "../schema.h"
namespace CuteEntityManager {
class SqliteSchema : public Schema {
public:
    SqliteSchema();
    ~SqliteSchema();
};
}
#endif // SQLITESCHEMA_H
