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
    for(auto i = params.begin(); i != params.end(); ++i) {
        QString ikey = i.key();
        expression.replace(":" + ikey.replace('.','_'),":" + this->generateParam());
        this->appendParam(i.key(),i.value());
    }
    this->expression = expression;
    this->onlyColumn = onlyColumn;
}

Expression::Expression(QString expression, QString key, QVariant value, bool onlyColumn) {
    this->expression = expression.replace(":" + key.replace('.','_'), ":" + this->generateParam());
    this->appendParam(key, value);
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

QString Expression::generateParam() {
    return (QString("emP") + QString::number(this->params.size() + 1));
}

void Expression::appendParam(QString key, const QVariant &value) {
    this->params.insert(this->generateParam(), value);
    /**
      @todo remove
      */
    this->params.insert(key.replace('.','_'), value);
}

QHash<QString, QVariant> Expression::getParams() const {
    return params;
}

void Expression::setParams(const QHash<QString, QVariant> &value) {
    params = value;
}


