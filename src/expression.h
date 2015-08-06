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
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <QHash>
#include <QString>
#include <QVariant>
namespace CuteEntityManager {
class Expression {
  public:
    Expression();
    Expression(QString expression,
               bool onlyColumn = false);
    QString getExpression() const;
    void setExpression(const QString &value);

    QString toString() const;

    bool getOnlyColumn() const;
    void setOnlyColumn(bool value);

  private:
    QString expression;
    bool onlyColumn;
};
}
#endif // EXPRESSION_H
