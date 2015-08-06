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
#ifndef ORDERBY_H
#define ORDERBY_H

#include <QString>
#include "expression.h"
namespace CuteEntityManager {
enum class Direction {
    SORT_ASC,
    SORT_DESC,
    DEFAULT
};

//class Expression;
class OrderBy {
  public:
    OrderBy();
    OrderBy(QString column, Direction direction = Direction::DEFAULT);
    OrderBy(Expression direction);
    QString getColumn() const;
    void setColumn(const QString &value);

    Direction getDirection() const;
    void setDirection(const Direction &value);

    Expression getExpressedDirection() const;
    void setExpressedDirection(const Expression &value);

  private:
    QString column;
    Direction direction;
    Expression expressedDirection;
};
}
#endif // ORDERBY_H
