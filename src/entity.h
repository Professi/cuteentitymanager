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

#ifndef MODEL_H
#define MODEL_H
#include <QtGlobal>
#include <QMap>
#include <QDebug>
#include <QObject>
#include "enums/databasetype.h"
namespace CuteEntityManager {

class Entity : public QObject {
    Q_OBJECT
public:
    qint64 getId() = 0;
    void setId(qint64 id) = 0;
    virtual ~Entity();
    virtual QString getTablename() = 0;
    //  virtual QMap<QString, QString> getManyToManyRelations() = 0;   //Key = Table, Value = joined Table Column
protected:
    Entity();
};
}
#endif // MODEL_H
