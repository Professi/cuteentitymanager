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

#ifndef ARTICLE_H
#define ARTICLE_H
#include "entity.h"

class Article : public CuteEntityManager::Entity {
    Q_OBJECT
    EM_MACRO(Article)
    Q_PROPERTY(double price READ getPrice WRITE setPrice)
    Q_PROPERTY(QString name READ getName WRITE setName)
  private:
    double price;
    QString name;

  public:
    virtual ~Article();
    Q_INVOKABLE Article();
    Article(double price, QString name);
    QString getName() const;
    void setName(const QString &value);
    double getPrice() const;
    void setPrice(double value);
};
#endif // ARTIKEL_H
