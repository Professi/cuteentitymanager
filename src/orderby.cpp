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

#include "orderby.h"
using namespace CuteEntityManager;
OrderBy::OrderBy() {
    this->direction = Direction::DEFAULT;
}

OrderBy::OrderBy(QString column, Direction direction) {
    this->column = column;
    this->direction = direction;
}

OrderBy::OrderBy(Expression direction) {
    this->column = "";
    this->direction = Direction::DEFAULT;
    this->expressedDirection = direction;
}

QString OrderBy::getColumn() const {
    return column;
}

void OrderBy::setColumn(const QString &value) {
    column = value;
}

Direction OrderBy::getDirection() const {
    return direction;
}

void OrderBy::setDirection(const Direction &value) {
    direction = value;
}

Expression OrderBy::getExpressedDirection() const {
    return expressedDirection;
}

void OrderBy::setExpressedDirection(const Expression &value) {
    expressedDirection = value;
}

