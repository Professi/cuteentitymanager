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

#include "expression.h"
using namespace CuteEntityManager;
Expression::Expression() {
}

Expression::Expression(QString expression, QHash<QString, QVariant> params,
                       bool onlyColumn) {
    this->expression = expression;
    this->params = params;
    this->onlyColumn = onlyColumn;
}

Expression::Expression(QString expression, bool onlyColumn) {
    this->expression = expression;
    this->onlyColumn = onlyColumn;
}

QString Expression::getExpression() const {
    return this->expression;
}

void Expression::setExpression(const QString &value) {
    this->expression = value;
}

QString Expression::toString() const {
    return this->expression;
}

bool Expression::getOnlyColumn() const {
    return onlyColumn;
}

void Expression::setOnlyColumn(bool value) {
    onlyColumn = value;
}

void Expression::appendParam(const QString &key, const QVariant &value) {
    this->params.insert(key, value);
}

QHash<QString, QVariant> Expression::getParams() const {
    return params;
}

void Expression::setParams(const QHash<QString, QVariant> &value) {
    params = value;
}


