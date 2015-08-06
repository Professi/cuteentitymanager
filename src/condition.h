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
#ifndef CONDITION_H
#define CONDITION_H

#include <QStringList>
namespace CuteEntityManager {
class Condition {
  public:
    Condition();
    Condition(QString condition);
    void appendCondition(const QString &value);
    QStringList getConditions() const;
    void setConditions(const QStringList &value);

    void addSubCondition(const Condition &value);
    QList<Condition> getSubConditions() const;
    void setSubConditions(const QList<Condition> &value);

  private:
    QStringList conditions;
    QList<Condition> subConditions;
};
}

#endif // CONDITION_H
