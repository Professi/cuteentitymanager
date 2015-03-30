#include "schema.h"
using namespace CuteEntityManager;

Schema::Schema() {
    this->typeMap = QSharedPointer<QHash<QString, QString>>(new QHash<QString, QString>());
}

Schema::~Schema() {

}

QString Schema::quoteSimpleTableName(QString name) {
    return name.indexOf("`") ? name : "`" + name + "`";
}

QString Schema::quoteTableName(QString name) {

}

QString Schema::quoteColumnName(QString name) {

}

QString Schema::quoteSimpleColumnName(QString name) {
    return name.indexOf("`") || name == "*" ? name : "`" + name + "`";
}

QList<TableSchema> Schema::getTableSchemas(QString schema) {

}

QStringList Schema::getTableNames(QString schema) {
    //7QStringList QSqlDriver::tables(QSql::TableType tableType) const
}

QStringList Schema::findUniqueIndexes(TableSchema schema) {

}

QString Schema::getLastInsertID(QString sequenceName) {

}

void Schema::refresh() {

}

QString Schema::getRawTable(QString name) {

}

QStringList Schema::findTableNames(QString schema) {

}

QStringList Schema::findUniqueIndexes(QString tableName) {

}

TableSchema Schema::findConstraints(TableSchema ts) {
}

QString Schema::getCreateTableSql(TableSchema ts) {

}

bool Schema::findColumns(TableSchema ts) {

}

TableSchema Schema::getTableSchema(QString name, bool refresh) {

}

