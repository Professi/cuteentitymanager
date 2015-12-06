#include "attribute.h"
using namespace CuteEntityManager;

Attribute::Attribute(QString name, QString columnName, QString tableName,
                     QMetaObject *metaObj, QString relatedTable, QMetaObject *relatedClass,
                     QString conjunctedTable) {
    this->name = name;
    this->tableName = tableName;
    this->metaObj = metaObj;
    this->relatedTable = relatedTable;
    this->relatedClass = relatedClass;
    this->conjunctedTable = conjunctedTable;
}

QString Attribute::getName() const {
    return name;
}

void Attribute::setName(const QString &value) {
    name = value;
}

QString Attribute::getColumnName() const {
    return columnName;
}

void Attribute::setColumnName(const QString &value) {
    columnName = value;
}

QString Attribute::getTableName() const {
    return tableName;
}

void Attribute::setTableName(const QString &value) {
    tableName = value;
}

QString Attribute::getRelatedTable() const {
    return relatedTable;
}

void Attribute::setRelatedTable(const QString &value) {
    relatedTable = value;
}

QMetaObject *Attribute::getRelatedClass() const {
    return relatedClass;
}

void Attribute::setRelatedClass(QMetaObject *value) {
    relatedClass = value;
}

QString Attribute::getConjunctedTable() const {
    return conjunctedTable;
}

void Attribute::setConjunctedTable(const QString &value) {
    conjunctedTable = value;
}

QMetaObject *Attribute::getMetaObj() const {
    return metaObj;
}

void Attribute::setMetaObj(QMetaObject *value) {
    metaObj = value;
}

