#include "schema.h"
using namespace CuteEntityManager;

Schema::Schema() {
    this->typeMap = QSharedPointer<QHash<QString, QString>>(new QHash<QString, QString>());
}

Schema::~Schema() {

}

QString Schema::quoteSimpleTableName(QString name) {
    //    return strpos($name, "`") !== false ? $name : "`" . $name . "`";
}

QString Schema::quoteTableName(QString name) {

}

QString Schema::quoteColumnName(QString name) {

}

QString Schema::quoteSimpleColumnName(QString name) {
    //return strpos($name, '`') !== false || $name === '*' ? $name : '`' . $name . '`';
}

QList<TableSchema> Schema::getTableSchemas(QString schema) {

}

QList<QString> Schema::getTableNames(QString schema) {

}

QList<QString> Schema::findUniqueIndexes(TableSchema schema) {

}

QString Schema::getLastInsertID(QString sequenceName) {

}

void Schema::refresh() {

}

void Schema::quoteValue(QString str) {

}

QString Schema::getRawTable(QString name) {

}

QList<QString> Schema::findTableNames(QString schema) {

}

QList<QString> Schema::findUniqueIndexes(QString tableName) {

}

TableSchema Schema::findConstraints(TableSchema ts) {
}

QString Schema::getCreateTableSql(TableSchema ts) {

}

bool Schema::findColumns(TableSchema ts) {

}

TableSchema Schema::getTableSchema(QString name, bool refresh) {

}

