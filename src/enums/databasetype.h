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
#include <QSharedPointer>
#include "../schema/sqliteschema.h"

namespace CuteEntityManager {
class Schema;
class Database;
enum DatabaseType {
    SQLITE = 0,
    PGSQL = 1,
    MYSQL = 2
};

static const DatabaseType getDatabaseType(QString s) {
    if (s == "qmysql") {
        return CuteEntityManager::MYSQL;
    } else if (s == "qpgsql") {
        return CuteEntityManager::PGSQL;
    } else {
        return CuteEntityManager::SQLITE;
    }
}

static const QSharedPointer<Schema> getSchema(int db, QSharedPointer<Database> database) {
    switch (db) {
    case SQLITE:
        return QSharedPointer<Schema>(new SqliteSchema(database));;
        break;
//    case PGSQL:
//        return QSharedPointer<Schema>(new PgSqlSchema());
//        break;
//    case MYSQL:
//        return QSharedPointer<Schema>(new MysqlSchema());
//        break;
    default:
        return QSharedPointer<Schema>(new SqliteSchema(database));
        break;
    }
}


}
#endif // DATABASETYPE_H
