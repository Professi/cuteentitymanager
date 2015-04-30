/*
    Small test class
    Copyright (C) 2013 Christian Ehringfeld <c.ehringfeld@t-online.de>

    This file is part of OpenTeacherTool.

    OpenTeacherTool is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenTeacherTool is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with OpenTeacherTool.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ARTIKEL_H
#define ARTIKEL_H
#include "entity.h"
#include <QHash>
#include <QVariant>

class Artikel : public CuteEntityManager::Entity {
    Q_OBJECT
    Q_PROPERTY(double preis READ getPreis WRITE setPreis)
    Q_PROPERTY(QString name READ getName WRITE setName)
  private:
    double preis;
    QString name;

  public:
    ~Artikel();
    explicit Artikel(QObject *parent = 0);
    Artikel(double preis, QString name);
    double getPreis() const;
    void setPreis(double value);
    QString getName() const;
    void setName(const QString &value);
};
#endif // ARTIKEL_H
