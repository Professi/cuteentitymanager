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

#include "entity.h"

using namespace CuteEntityManager;

Entity::Entity(QObject *parent) : QObject(parent) {
    this->id = -1;
}

QString Entity::toString() {
    return this->getTablename() + ":" + QString::number(this->id);
}

Entity::~Entity() {

}

QString Entity::getTablename() {
    return QString(this->metaObject()->className()).toLower();
}

const QHash<QString, Relation> Entity::getRelations() const {
    return QHash<QString, Relation>();
}

const QStringList Entity::getTransientAttributes() const {
    return QStringList();
}

const QStringList Entity::getBLOBColumns() const {
    return QStringList();
}

QString Entity::getPrimaryKey() {
    return "id";
}

const QHash<QString, QMetaProperty> Entity::getMetaProperties() const {
    auto h = QHash<QString, QMetaProperty>();
    for (int var = 0; var < this->metaObject()->propertyCount(); ++var) {
        QMetaProperty m = this->metaObject()->property(var);
        if (m.isValid() && m.name() != QString("objectName")) {
            h.insert(m.name(), m);
        }
    }
    return h;
}

const QHash<Relation, QMetaProperty> Entity::getRelationProperties() const {
    auto h = QHash<Relation, QMetaProperty>();
    auto relations = this->getRelations();
    for (int var = 0; var < this->metaObject()->propertyCount(); ++var) {
        QMetaProperty m = this->metaObject()->property(var);
        if (m.isValid() && relations.contains(QString(m.name()))) {
            h.insert(relations.value(m.name()), m);
        }
    }
    return h;
}

const char *Entity::getClassname() const {
    return this->metaObject()->className();
}

qint64 Entity::getId() const {
    return id;
}

void Entity::setId(const qint64 &value) {
    if (value != this->id) {
        id = value;
        emit idChanged();
    }
}
