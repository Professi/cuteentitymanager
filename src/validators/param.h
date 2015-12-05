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
#ifndef PARAM_H
#define PARAM_H

#include <QString>
#include <QVariant>
namespace CuteEntityManager {
class Param {
  public:
    Param();
    ~Param();
    Param(QString name, QVariant value = QVariant());
    QVariant getValue() const;
    void setValue(QVariant value);

    QString getName() const;
    void setName(const QString &value);

  private:
    QVariant value;
    QString name;
};
}

#endif // PARAM_H
