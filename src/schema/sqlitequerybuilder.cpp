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
#include "sqlitequerybuilder.h"
#include "../schema.h"

CuteEntityManager::SqliteQueryBuilder::SqliteQueryBuilder(
    QSharedPointer<CuteEntityManager::Schema>
    schema,
    QSharedPointer<CuteEntityManager::Database> database) : QueryBuilder(schema,
                database) {

}

CuteEntityManager::SqliteQueryBuilder::~SqliteQueryBuilder() {

}

QString CuteEntityManager::SqliteQueryBuilder::truncateTable(
    QString tableName) const {
    return "DELETE FROM " + this->schema.data()->quoteTableName(tableName);
}

QString CuteEntityManager::SqliteQueryBuilder::dropIndex(QString name,
        QString tableName) const {
    return "DROP INDEX " + this->schema.data()->quoteTableName(name);
}

QString CuteEntityManager::SqliteQueryBuilder::dropColumn(QString tableName,
        QString columName) const {
    //not supported
    return "";
}

QString CuteEntityManager::SqliteQueryBuilder::renameColumn(QString tableName,
        QString oldName,
        QString newName) const {
    //not supported
    return "";
}

QString CuteEntityManager::SqliteQueryBuilder::addForeignKey(QString name,
        QString tableName,
        QStringList columns,
        QString refTableName, QStringList refColumns, QString deleteConstraint,
        QString updateConstraint) const {
    //not supported
    return "";
}

QString CuteEntityManager::SqliteQueryBuilder::dropForeignKey(QString name,
        QString tableName) const {
    //not supported
    return "";
}

QString CuteEntityManager::SqliteQueryBuilder::alterColumn(QString tableName,
        QString columnName,
        QString newType) const {
    //not supported
    return "";
}

QString CuteEntityManager::SqliteQueryBuilder::addPrimaryKey(QString name,
        QString tableName,
        QStringList columns) const {
    //not supported
    return "";
}

QString CuteEntityManager::SqliteQueryBuilder::dropPrimaryKey(QString name,
        QString tableName) const {
    //not supported
    return "";
}
