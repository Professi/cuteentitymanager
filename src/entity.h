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
#include "enums/persistencetype.h"
#include "enums/databasetype.h"
namespace CuteEntityManager {

class Entity
{
public:
    qint64 getId();
    void setId(qint64 id);
    Entity* getEntity();
    void addAttributeVal(const QString name, QVariant *var);
    virtual ~Entity();
    virtual QHash<QString, QString> getProperties(DatabaseType type) = 0;
    virtual PersistenceType getPersistenceType() = 0;
    virtual QHash<QString,Entity*>* getRelations() = 0;
    virtual QHash<QString, QVariant>* getAttributeValues() = 0;
    virtual void setAttributes(QHash<QString, QVariant>) = 0;
    virtual QString getTablename() = 0;
    virtual QString idColumnSQL();
    //  virtual QMap<QString, QString> getManyToManyRelations() = 0;   //Key = Table, Value = joined Table Column
protected:
    Entity();
    qint64 id;
    QHash<QString,QVariant> *attributeValues;
    QHash<QString,Entity*> *relations;
};
}
#endif // MODEL_H
