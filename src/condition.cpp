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

#include "condition.h"
using namespace CuteEntityManager;
Condition::Condition() {

}

Condition::Condition(QString condition) {
    if (!condition.isEmpty()) {
        this->conditions.append(condition);
    }
}

void Condition::appendCondition(const QString &value) {
    this->conditions.append(value);
}

QStringList Condition::getConditions() const {
    return conditions;
}

void Condition::setConditions(const QStringList &value) {
    conditions = value;
}

QList<Condition> Condition::getSubConditions() const {
    return subConditions;
}

void Condition::setSubConditions(const QList<Condition> &value) {
    subConditions = value;
}

void CuteEntityManager::Condition::addSubCondition(const
        CuteEntityManager::Condition &value) {
    this->subConditions.append(value);
}
