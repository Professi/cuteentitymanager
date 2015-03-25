/*
 * Copyright (C) 2015 Christian Ehringfeld <c.ehringfeld@t-online.de>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DATABASETYPE_H
#define DATABASETYPE_H
#include <QString>
#include "../schema.h"
#include "../schema/sqliteschema.h"
#include "../schema/pgsqlschema.h"
#include "../schema/mysqlschema.h"
#include <memory>

namespace CuteEntityManager {
enum DatabaseType {
    SQLITE=0,
    PGSQL=1,
    MYSQL=2
};

static const DatabaseType getDatabaseType(QString s) {
    if(s == "qmysql") {
        return CuteEntityManager::MYSQL;
    } else if(s == "qpgsql") {
        return CuteEntityManager::PGSQL;
    } else {
        return CuteEntityManager::SQLITE;
    }
}

static const std::shared_ptr<Schema> getSchema(int db) {
    switch (db) {
    case SQLITE:
        return std::shared_ptr<Schema>(new SqliteSchema());
        break;
    case PGSQL:
        return std::shared_ptr<Schema>(new PgSqlSchema());
        break;
    case MYSQL:
        return std::shared_ptr<Schema>(new MysqlSchema());
        break;
    default:
        return std::shared_ptr<Schema>(new SqliteSchema());
        break;
    }
}


}
#endif // DATABASETYPE_H
