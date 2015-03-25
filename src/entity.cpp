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

namespace CuteEntityManager {

Entity::Entity() : QObject() {
    this->id = -1;
}

qint64 Entity::getId() {
    return this->id;
}

void Entity::setId(qint64 id) {
    this->id = id;
}

Entity::~Entity() {
}

//QHash<QString, QString> OpenTeacherTool::Entity::getProperties(Datebasetype t) {
//    QMap<QString, QString> map = QMap<QString, QString>();
//    map.insert("id",this->idColumnSQL());
//    return map;
//}

//OpenTeacherTool::PersistenceType OpenTeacherTool::Entity::getPersistenceType() {
//    OpenTeacherTool::PersistenceType type = SQLITE;
//    return type;
//}

//QMap<QString, OpenTeacherTool::Entity> OpenTeacherTool::Entity::getRelations() {
//    QMap<QString, Entity> map;
//    return map;
//}



}
