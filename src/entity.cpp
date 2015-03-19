/*
    Base class for all models
    Copyright (C) 2013 Christian Ehringfeld <c.ehringfeld@t-online.de>

    This file is part of OpenTeacherTool.

    OpenTeacherTool is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenTeacherTool is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with OpenTeacherTool.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "entity.h"

namespace OpenTeacherTool {

Entity::Entity() {
    this->id = -1;
    this->relations = new QHash<QString,Entity*>();
    this->attributeValues = new QHash<QString, QVariant>();
}

qint64 Entity::getId() {
    return this->id;
}

void Entity::setId(qint64 id) {
        this->id = id;
}

Entity::~Entity() {
    delete this->relations;
    delete this->attributeValues;
}

Entity* Entity::getEntity() {
    return this;
}

QString Entity::idColumnSQL() {
    return "id BIGINT NOT NULL";
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
