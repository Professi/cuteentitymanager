#include "sqlitequerybuilder.h"
#include "../schema.h"

CuteEntityManager::SqliteQueryBuilder::SqliteQueryBuilder(QSharedPointer<CuteEntityManager::Schema> schema,
        QSharedPointer<CuteEntityManager::Database> database) : QueryBuilder(schema, database) {

}

CuteEntityManager::SqliteQueryBuilder::~SqliteQueryBuilder() {

}

QString CuteEntityManager::SqliteQueryBuilder::truncateTable(QString tableName) const {
    return "DELETE FROM " + this->schema.data()->quoteTableName(tableName);
}

QString CuteEntityManager::SqliteQueryBuilder::dropIndex(QString name, QString tableName) const {
    return "DROP INDEX " + this->schema.data()->quoteTableName(name);
}

QString CuteEntityManager::SqliteQueryBuilder::dropColumn(QString tableName, QString columName) const {
    //not supported
    return "";
}

QString CuteEntityManager::SqliteQueryBuilder::renameColumn(QString tableName, QString oldName, QString newName) const {
    //not supported
    return "";
}

QString CuteEntityManager::SqliteQueryBuilder::addForeignKey(QString name, QString tableName, QStringList columns,
        QString refTableName, QStringList refColumns, QString deleteConstraint, QString updateConstraint) const {
    //not supported
    Q_UNUSED(refTableName)
    Q_UNUSED(refColumns)
    Q_UNUSED(name)
    Q_UNUSED(tableName)
    Q_UNUSED(deleteConstraint)
    Q_UNUSED(columns)
    Q_UNUSED(updateConstraint)
    return "";
}

QString CuteEntityManager::SqliteQueryBuilder::dropForeignKey(QString name, QString tableName) const {
    //not supported
    return "";
}

QString CuteEntityManager::SqliteQueryBuilder::alterColumn(QString tableName, QString columnName,
        QString newType) const {
    //not supported
    return "";
}

QString CuteEntityManager::SqliteQueryBuilder::addPrimaryKey(QString name, QString tableName,
        QStringList columns) const {
    //not supported
    return "";
}

QString CuteEntityManager::SqliteQueryBuilder::dropPrimaryKey(QString name, QString tableName) const {
    //not supported
    return "";
}
