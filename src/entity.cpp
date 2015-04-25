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
    return QString(this->metaObject()->className());
}

QHash<QString, Relation> Entity::getRelations() {
    return QHash<QString, Relation>();
}

QHash<QString, QSharedPointer<Entity> > Entity::getRelationObjects() {
    return QHash<QString, QSharedPointer<Entity>>();
}

QStringList Entity::getTransientAttributes() {
    return QStringList();
}

QStringList Entity::getBLOBColumns() {
    return QStringList();
}

QString Entity::getPrimaryKey() {
    return "id";
}

QHash<QString, QMetaProperty> Entity::getMetaProperties() {
    QHash<QString, QMetaProperty> h = QHash<QString, QMetaProperty>();
    for (int var = 0; var < this->metaObject()->propertyCount(); ++var) {
        QMetaProperty m = this->metaObject()->property(var);
        if (m.name() != QString("objectName") && m.isValid()) {
            h.insert(m.name(), m);
        }
    }
    return h;
}

qint64 Entity::getId() const {
    return id;
}

void Entity::setId(const qint64 &value) {
    id = value;
}
