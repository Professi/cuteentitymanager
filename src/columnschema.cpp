#include "columnschema.h"
using namespace CuteEntityManager;

ColumnSchema::ColumnSchema() {

}

ColumnSchema::~ColumnSchema() {

}

QString ColumnSchema::getName() const {
    return name;
}

void ColumnSchema::setName(const QString &value) {
    name = value;
}

bool ColumnSchema::getAllowNull() const {
    return allowNull;
}

void ColumnSchema::setAllowNull(bool value) {
    allowNull = value;
}

QString ColumnSchema::getDbType() const {
    return dbType;
}

void ColumnSchema::setDbType(const QString &value) {
    dbType = value;
}

QString ColumnSchema::getDefaultValue() const {
    return defaultValue;
}

void ColumnSchema::setDefaultValue(const QString &value) {
    defaultValue = value;
}

QList<QString> ColumnSchema::getEnumValues() const {
    return enumValues;
}

void ColumnSchema::setEnumValues(const QList<QString> &value) {
    enumValues = value;
}

quint8 ColumnSchema::getSize() const {
    return size;
}

void ColumnSchema::setSize(const quint8 &value) {
    size = value;
}

quint8 ColumnSchema::getPrecision() const {
    return precision;
}

void ColumnSchema::setPrecision(const quint8 &value) {
    precision = value;
}

quint8 ColumnSchema::getScale() const {
    return scale;
}

void ColumnSchema::setScale(const quint8 &value) {
    scale = value;
}

bool ColumnSchema::getPrimaryKey() const {
    return primaryKey;
}

void ColumnSchema::setPrimaryKey(bool value) {
    primaryKey = value;
}

bool ColumnSchema::getAutoIncrement() const {
    return autoIncrement;
}

void ColumnSchema::setAutoIncrement(bool value) {
    autoIncrement = value;
}

bool ColumnSchema::getUnsignedColumn() const {
    return unsignedColumn;
}

void ColumnSchema::setUnsignedColumn(bool value) {
    unsignedColumn = value;
}

QString ColumnSchema::getComment() const {
    return comment;
}

void ColumnSchema::setComment(const QString &value) {
    comment = value;
}

