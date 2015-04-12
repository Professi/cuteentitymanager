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

QList<Relation> Entity::getRelations() {
    return QList<Relation>();
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
qint32 Entity::getId() const
{
    return id;
}

void Entity::setId(const qint32 &value)
{
    id = value;
}
