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

#ifndef ENTITY_H
#define ENTITY_H
#include <QtGlobal>
#include <QMap>
#include <QDebug>
#include <QObject>
#include <QMetaProperty>
#include "relation.h"
#include <QStringList>
#include <QSharedPointer>
namespace CuteEntityManager {

/**
 * You mustn't name any persisted property objectName, because its pre used by Qt and will be ignored by Entity Manager
 * @brief The Entity class
 */
class Entity : public QObject {
    Q_OBJECT
    Q_PROPERTY(qint64 id READ getId WRITE setId NOTIFY idChanged)

  signals:
    void idChanged();

  public:
    Entity (QObject *parent = 0);
    virtual QString toString();
    virtual ~Entity();
    virtual QString getTablename();
    /**
     * @brief getRelations
     * @return
     */
    virtual QHash<QString, Relation> getRelations();
    virtual QStringList getTransientAttributes();
    virtual QStringList getBLOBColumns();

    //return value must be the exact name defined in Q_PROPERTY
    virtual QString getPrimaryKey();
    QHash<QString, QMetaProperty> getMetaProperties() const;
    const char* getClassname() const;

    qint64 getId() const;
    void setId(const qint64 &value);

  protected:
    qint64 id;
};
}
#endif // ENTITY_H
