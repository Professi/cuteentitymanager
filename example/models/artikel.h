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
#include "src/base/entity.h"
#include <QHash>
#include <QVariant>

namespace OpenTeacherTool {
class Artikel : public Entity
{
private:
    double preis;
    QString name;

public:
    ~Artikel();
    QHash<QString, QString> getProperties(DatabaseType type);
    PersistenceType getPersistenceType();
    QHash<QString,Entity*>* getRelations();
    QHash<QString, QVariant>* getAttributeValues();
    void setAttributes(QHash<QString, QVariant> h);
    QString getTablename();
    void setPreis(double preis);
    void setName(QString name);
    Artikel();
    Artikel(double preis, QString name);
};
}
#endif // ARTIKEL_H
