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
#include "article.h"

QString Article::getName() const {
    return name;
}

void Article::setName(const QString &value) {
    name = value;
}

Article::~Article() {

}

Article::Article() : Entity() {
    this->price = 0.0;
    this->name = "";
}

Article::Article(double preis, QString name) : Entity() {
    this->price = preis;
    this->name = name;
}

double Article::getPrice() const
{
    return price;
}

void Article::setPrice(double value)
{
    price = value;
}
