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

#include "join.h"
using namespace CuteEntityManager;
Join::Join() {

}

Join::Join(QString foreignTable, QString expression, QString type) {
    this->foreignTable = foreignTable;
    this->expression = Expression(expression);
    this->type = type;
}

Join::Join(QString foreignTable, Expression expression, QString type) {
    this->foreignTable = foreignTable;
    this->expression = expression;
    this->type = type;
}

QString Join::getType() const {
    return type;
}

void Join::setType(const QString &value) {
    type = value;
}

QString Join::getForeignTable() const {
    return foreignTable;
}

void Join::setForeignTable(const QString &value) {
    foreignTable = value;
}

Expression Join::getExpression() const {
    return expression;
}

void Join::setExpression(const Expression &value) {
    expression = value;
}
