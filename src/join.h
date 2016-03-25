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
#ifndef JOIN_H
#define JOIN_H
#include <QString>
#include "expression.h"
namespace CuteEntityManager {
class Join {
  public:
    Join();
    explicit Join(QString foreignTable, QString expression,
                  QString type = QStringLiteral("LEFT JOIN"));
    explicit Join(QString foreignTable, Expression expression,
                  QString type = QStringLiteral("LEFT JOIN"));
    explicit Join(QString attribute);

    QString getType() const;
    void setType(const QString &value);

    QString getForeignTable() const;
    void setForeignTable(const QString &value);

    Expression getExpression() const;
    void setExpression(const Expression &value);

    QString getAttribute() const;
    void setAttribute(const QString &value);

    QString getAlias() const;
    void setAlias(const QString &value);

  private:
    QString type = QStringLiteral("LEFT JOIN");
    QString foreignTable;
    QString attribute;
    QString alias;
    Expression expression;

};
inline bool operator==(const Join &e1, const Join &e2) {
    return (e1.getForeignTable() == e2.getForeignTable()
            && e1.getExpression() == e2.getExpression()) || (!e1.getAttribute().isEmpty() &&
                    e1.getAttribute() == e2.getAttribute()) || (e1.getAlias().isEmpty() &&
                            e1.getAlias() == e2.getAlias());
}

}
#endif // JOIN_H
