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
#include "entityhelper.h"
using namespace CuteEntityManager;

Entity::Entity(QObject *parent) : QObject(parent) {
    this->id = -1;
}

QString Entity::toString() const {
    QString r = "";
    r.append(EntityHelper::getClassName(this));
    r.append(": {");
    auto properties = EntityHelper::getMetaProperties(this);
    for (auto var = properties.constBegin(); var != properties.constEnd(); ++var) {
        QString val = "";
        auto value = var.value().read(this);
        if (var.value().isEnumType()) {
            val = var.value().enumerator().valueToKey(var.value().read(this).toInt());
        } else if (value.canConvert<QList<QVariant>>()) {
            auto list = value.toList();
            val.append("[");
            for (int i = 0; i < list.size(); ++i) {
                val = list.at(i).toString();
            }
            val.append("]");
        } else {
            val = value.toString();
        }
        r.append(var.key() + ": " + val + ", ");
    }
    r.append("}");
    return r;
}

QString Entity::slimToString() const {
    QString r = "";
    r.append(EntityHelper::getClassName(this));
    r.append(": {");
    r.append("id: ") + this->getId() + "}";
    return r;
}

Entity::~Entity() {

}

QString Entity::getTablename() const {
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

InheritanceStrategy Entity::getInheritanceStrategy() const {
    return InheritanceStrategy::JOINED_TABLE;
}

bool Entity::isInheritanceCascaded() const {
    return true;
}

QString Entity::getPrimaryKey() const {
    return "id";
}

QVariant Entity::getProperty(const QString &name) const {
    if (!name.isEmpty()) {
        return QObject::property(name.toLatin1().constData());
    }
    return QVariant();
}

bool Entity::setProperty(const QString &name, const QVariant &value) {
    return QObject::setProperty(name.toLatin1().constData(), value);
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
