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
#include "relation.h"
using namespace CuteEntityManager;

Relation::Relation() {
}

Relation::Relation(QString propertyName, RelationType type, bool optional) {
    this->propertyName = propertyName;
    this->type = type;
    this->optional = optional;
    this->tableName = "";
    this->cascadeType = ALL;
}

Relation::Relation(QString propertyName, RelationType type, QString mappedBy, QString tableName,
                   CascadeType cascadeType) {
    this->propertyName = propertyName;
    this->type = type;
    this->mappedBy = mappedBy;
    this->optional = true;
    this->tableName = tableName;
    if (this->type == MANY_TO_ONE) {
        this->cascadeType = ALL;
    } else {
        this->cascadeType = cascadeType;
    }
}

Relation::~Relation() {
}

RelationType Relation::getType() const {
    return type;
}

void Relation::setType(const RelationType &value) {
    type = value;
}

QString Relation::getPropertyName() const {
    return propertyName;
}

void Relation::setPropertyName(const QString &value) {
    propertyName = value;
}
bool Relation::getOptional() const {
    return optional;
}

void Relation::setOptional(bool value) {
    optional = value;
}
QString Relation::getMappedBy() const {
    return mappedBy;
}

void Relation::setMappedBy(const QString &value) {
    mappedBy = value;
}
QString Relation::getTableName() const {
    return tableName;
}

void Relation::setTableName(const QString &value) {
    tableName = value;
}
CascadeType Relation::getCascadeType() const {
    return cascadeType;
}

void Relation::setCascadeType(const CascadeType &value) {
    cascadeType = value;
}



