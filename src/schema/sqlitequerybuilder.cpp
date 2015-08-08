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
    return "DELETE FROM " + this->schema->quoteTableName(tableName);
}

QString CuteEntityManager::SqliteQueryBuilder::dropIndex(QString name,
        QString tableName) const {
    Q_UNUSED(tableName)
    return "DROP INDEX " + this->schema->quoteTableName(name);
}

QString CuteEntityManager::SqliteQueryBuilder::dropColumn(QString tableName,
        QString columnName) const {
    Q_UNUSED(tableName)Q_UNUSED(columnName)
    //not supported
    return "";
}

QString CuteEntityManager::SqliteQueryBuilder::renameColumn(QString tableName,
        QString oldName,
        QString newName) const {
    Q_UNUSED(tableName)Q_UNUSED(oldName)Q_UNUSED(newName)
    //not supported
    return "";
}

QString CuteEntityManager::SqliteQueryBuilder::addForeignKey(QString name,
        QString tableName,
        QStringList columns,
        QString refTableName, QStringList refColumns, QString deleteConstraint,
        QString updateConstraint) const {
    Q_UNUSED(tableName)Q_UNUSED(name)Q_UNUSED(columns)Q_UNUSED(
        refTableName)Q_UNUSED(refColumns)Q_UNUSED(deleteConstraint)Q_UNUSED(
            updateConstraint)
    //not supported
    if (this->supportsForeignKeys()) {
        return QueryBuilder::addForeignKey(name, tableName, columns, refTableName,
                                           refColumns, deleteConstraint, updateConstraint);
    }
    return "";
}

QString CuteEntityManager::SqliteQueryBuilder::dropForeignKey(QString name,
        QString tableName) const {
    Q_UNUSED(name)Q_UNUSED(tableName)
    if (this->supportsForeignKeys()) {
        return QueryBuilder::dropForeignKey(name, tableName);
    }
    //not supported
    return "";
}

QString CuteEntityManager::SqliteQueryBuilder::alterColumn(QString tableName,
        QString columnName,
        QString newType) const {
    Q_UNUSED(tableName)Q_UNUSED(newType)Q_UNUSED(columnName)
    //not supported
    return "";
}

QString CuteEntityManager::SqliteQueryBuilder::addPrimaryKey(QString name,
        QString tableName,
        QStringList columns) const {
    Q_UNUSED(tableName)Q_UNUSED(name)Q_UNUSED(columns)
    //not supported
    return "";
}

QString CuteEntityManager::SqliteQueryBuilder::dropPrimaryKey(QString name,
        QString tableName) const {
    Q_UNUSED(tableName)Q_UNUSED(name)
    //not supported
    return "";
}

bool CuteEntityManager::SqliteQueryBuilder::supportsForeignKeys() const {
    return false;
}
