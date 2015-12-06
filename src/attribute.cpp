#include "attribute.h"
#include "entityhelper.h"
using namespace CuteEntityManager;

Attribute::Attribute(QString name, QString columnName, QString tableName,
                     const QMetaObject *metaObj, QString relatedTable, const QMetaObject *relatedClass,
                     QString conjunctedTable,  QString relatedColumnName, QString baseTableName,
                     const QMetaObject *baseMetaObj) {
    this->name = name;
    this->columnName = columnName;
    this->tableName = tableName;
    this->metaObj = metaObj;
    this->relatedTable = relatedTable;
    this->relatedClass = relatedClass;
    this->conjunctedTable = conjunctedTable;
    this->relatedColumnName = relatedColumnName;
    this->baseMetaObj = baseMetaObj;
    this->baseTableName = baseTableName;
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

QString Attribute::getConjunctedTable() const {
    return conjunctedTable;
}

void Attribute::setConjunctedTable(const QString &value) {
    conjunctedTable = value;
}

QString Attribute::getBaseTableName() const {
    return baseTableName;
}

void Attribute::setBaseTableName(const QString &value) {
    baseTableName = value;
}

void Attribute::setInheritance(const QString &baseTableName,
                               const QMetaObject *baseMetaObj) {
    this->baseTableName = baseTableName;
    this->baseMetaObj = baseMetaObj;
}

void Attribute::setRelation(const QString &tableName, const QMetaObject *relatedMetaObj,
                            const QString &conjunctedTable, const QString &relatedColumnName) {
    this->relatedTable = tableName;
    this->relatedClass = relatedMetaObj;
    this->conjunctedTable = conjunctedTable;
    this->relatedColumnName = relatedColumnName;
}

const QMetaProperty Attribute::getMetaProperty() {
    return EntityHelper::getMetaProperties(this->getMetaObj()).value(this->getName());
}

const QMetaObject *Attribute::getMetaObj() const {
    return metaObj;
}

void Attribute::setMetaObj(const QMetaObject *value) {
    metaObj = value;
}

const QMetaObject *Attribute::getBaseMetaObj() const {
    return baseMetaObj;
}

void Attribute::setBaseMetaObj(const QMetaObject *value) {
    baseMetaObj = value;
}

const QMetaObject *Attribute::getRelatedClass() const {
    return relatedClass;
}

void Attribute::setRelatedClass(const QMetaObject *value) {
    relatedClass = value;
}

QString Attribute::getRelatedColumnName() const {
    return relatedColumnName;
}

void Attribute::setRelatedColumnName(const QString &value) {
    relatedColumnName = value;
}

