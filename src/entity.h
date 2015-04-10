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
#include <QStringList>
namespace CuteEntityManager {

class Entity : public QObject {
    Q_OBJECT
    Q_PROPERTY(qint64 firstName READ getId WRITE setId NOTIFY idChanged)

signals:
  void idChanged();

  public:
    Entity (QObject *parent = 0);
    virtual qint64 getId();
    virtual void setId(qint64 id);
    virtual QString toString();
    virtual ~Entity();
    virtual QString getTablename();
    /**
     * You should return the names of properties which should not persisted e.g. Properties which are only exposed to qml
     * @brief getTransientAttributes
     * @return
     */
    virtual QStringList getTransientAttributes();
    //  virtual QMap<QString, QString> getManyToManyRelations() = 0;   //Key = Table, Value = joined Table Column
  protected:
    qint64 id;
};
}
#endif // MODEL_H
