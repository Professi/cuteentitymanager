#include "tableschema.h"
using namespace CuteEntityManager;

TableSchema::TableSchema() {

}

TableSchema::~TableSchema() {

}

const ColumnSchema TableSchema::getColumn(QString name) const {

}

const QList<QString> TableSchema::getColumnNames() {

}

QString TableSchema::getSchemaName() const {
    return schemaName;
}

void TableSchema::setSchemaName(const QString &value) {
    schemaName = value;
}
QString TableSchema::getName() const {
    return name;
}

void TableSchema::setName(const QString &value) {
    name = value;
}
QString TableSchema::getFullName() const {
    return fullName;
}

void TableSchema::setFullName(const QString &value) {
    fullName = value;
}
QList<QString> TableSchema::getPrimaryKeys() const {
    return primaryKeys;
}

void TableSchema::setPrimaryKeys(const QList<QString> &value) {
    primaryKeys = value;
}
QString TableSchema::getSequenceName() const {
    return sequenceName;
}

void TableSchema::setSequenceName(const QString &value) {
    sequenceName = value;
}
QHash<QString, QString> TableSchema::getForeignKeys() const {
    return foreignKeys;
}

void TableSchema::setForeignKeys(const QHash<QString, QString> &value) {
    foreignKeys = value;
}
QList<ColumnSchema> TableSchema::getColumns() const {
    return columns;
}

void TableSchema::setColumns(const QList<ColumnSchema> &value) {
    columns = value;
}
