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
#include "entityinstancefactory.h"
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
            val.append("[");
            auto list = EntityInstanceFactory::castQVariantList(value);
            int size = list.size();
            val.append(QString::number(size));
            val.append(" ");
            val.append(size == 1 ? "element" : "elements");
            val.append("]");
        } else {
            val = value.toString();
        }
        r.append(var.key() + ": " + val + ", ");
    }
    r.append("}");
    return r;
}

Entity* Entity::copy() const {
    return EntityHelper::copyObject(this);
}

QString Entity::slimToString() const {
    QString r = "";
    r.append(EntityHelper::getClassName(this));
    r.append(": {");
    r.append("id: ") + this->getId() + "}";
    return r;
}
QList<ErrorMsg> Entity::getErrors() const {
    return errors;
}

QString Entity::getErrorsAsString() const {
    QList<ErrorMsg> errors = this->getErrors();
    bool first = true;
    QString r = "";
    for (int i = 0; i < errors.size(); ++i) {
        ErrorMsg msg = errors.at(i);
        if (first) {
            first = false;
        } else {
            r += ";";
        }
        r += msg.getErrorMsg();
    }
    return r;
}

void Entity::setErrors(const QList<ErrorMsg> &value) {
    this->errors = value;
}

Entity::~Entity() {

}

QList<ValidationRule> Entity::validationRules() const {
    return QList<ValidationRule>();
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

bool Entity::hasErrors() const {
    return !this->errors.isEmpty();
}
