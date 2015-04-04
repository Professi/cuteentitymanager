#include "tableschema.h"
using namespace CuteEntityManager;

TableSchema::TableSchema() {

}

TableSchema::~TableSchema() {

}

const QSharedPointer<QSqlField> TableSchema::getColumn(QString name) const {
    auto columns = this->getColumns();
    foreach (auto schema, columns) {
        if (schema.data()->name() == name) {
            return schema;
        }
    }
    return QSharedPointer<QSqlField>();
}

const QStringList TableSchema::getColumnNames() {
    QStringList l;
    auto columns = this->getColumns();
    foreach (auto schema, columns) {
        l.append(schema.data()->name());
    }
    return l;
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
QStringList TableSchema::getPrimaryKeys() const {
    return primaryKeys;
}

void TableSchema::setPrimaryKeys(const QStringList &value) {
    primaryKeys = value;
}
QString TableSchema::getSequenceName() const {
    return sequenceName;
}

void TableSchema::setSequenceName(const QString &value) {
    sequenceName = value;
}

QHash<QString, QSharedPointer<QSqlField> > TableSchema::getColumns() const {
    return columns;
}

void TableSchema::setColumns(const QHash<QString, QSharedPointer<QSqlField> > &value) {
    columns = value;
}
QHash<QString, QSharedPointer<QSqlRelation> > TableSchema::getRelations() const {
    return relations;
}

void TableSchema::setRelations(const QHash<QString, QSharedPointer<QSqlRelation> > &value) {
    relations = value;
}
