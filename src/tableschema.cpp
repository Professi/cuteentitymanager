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
#include "tableschema.h"
using namespace CuteEntityManager;

TableSchema::TableSchema() {
}

TableSchema::~TableSchema() {
}

const QSharedPointer<QSqlField> TableSchema::getColumn(QString name) const {
    auto columns = this->getColumns();
    foreach (auto schema, columns) {
        if (schema->name() == name) {
            return schema;
        }
    }
    return QSharedPointer<QSqlField>();
}

const QStringList TableSchema::getColumnNames() {
    QStringList l;
    auto columns = this->getColumns();
    foreach (auto schema, columns) {
        l.append(schema->name());
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

void TableSchema::setColumns(const QHash<QString, QSharedPointer<QSqlField> >
                             &value) {
    columns = value;
}
QHash<QString, QSharedPointer<QSqlRelation> > TableSchema::getRelations()
const {
    return relations;
}

void TableSchema::setRelations(
    const QHash<QString, QSharedPointer<QSqlRelation> > &value) {
    relations = value;
}

QSharedPointer<QSqlRelationalTableModel> TableSchema::getTableModel() const {
    QSqlRelationalTableModel *model = new QSqlRelationalTableModel;
    model->setTable(this->getName());
    return QSharedPointer<QSqlRelationalTableModel>(model);
}
