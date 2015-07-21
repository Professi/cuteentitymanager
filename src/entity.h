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
#include <QStack>
#include <QQueue>
#include "entityinstancefactory.h"

#if defined CUTE_ENTITY_MANAGER_LIBRARY
 #define CUTE_ENTITY_MANAGER_LIBRARY_COMMON_DLLSPEC Q_DECL_EXPORT
#else
 #define CUTE_ENTITY_MANAGER_LIBRARY_COMMON_DLLSPEC Q_DECL_IMPORT
#endif


namespace CuteEntityManager {


/**
 * You mustn't name any persisted property objectName, because its pre used by Qt and will be ignored by Entity Manager
 * @brief The Entity class
 */
class Entity : public QObject {
    Q_OBJECT
    Q_PROPERTY(qint64 id READ getId WRITE setId NOTIFY idChanged)

  signals:
    Q_DECL_EXPORT void idChanged();

  public:
    Q_DECL_EXPORT explicit Entity (QObject *parent = 0);
    Q_DECL_EXPORT virtual QString toString() const;
    Q_DECL_EXPORT virtual ~Entity();
    Q_DECL_EXPORT virtual QString getTablename() const;
    Q_DECL_EXPORT virtual const QHash<QString, Relation> getRelations() const;
    Q_DECL_EXPORT virtual const QStringList getTransientAttributes() const;
    Q_DECL_EXPORT virtual const QStringList getBLOBColumns() const;
    Q_DECL_EXPORT virtual InheritanceStrategy getInheritanceStrategy() const;
    Q_DECL_EXPORT virtual bool isInheritanceCascaded() const;
    //return value must be the exact name defined in Q_PROPERTY
    Q_DECL_EXPORT virtual QString getPrimaryKey() const;
    Q_DECL_EXPORT const QHash<QString, Relation> getNonInheritedRelations() const;
    Q_DECL_EXPORT const QList<const QMetaObject *> superClasses(bool stopAtSingleTableInheritance
            = false) const;
    Q_DECL_EXPORT const QHash<QString, QMetaProperty> getMetaProperties() const;
    Q_DECL_EXPORT const QHash<QString, QMetaProperty> getSuperMetaProperties() const;
    Q_DECL_EXPORT static const QHash<QString, QMetaProperty> getMetaProperties(
        const QMetaObject *object);
    Q_DECL_EXPORT const QHash<QString, QMetaProperty> getInheritedMetaProperties() const;
    Q_DECL_EXPORT const QHash<Relation, QMetaProperty> getRelationProperties() const;
    Q_DECL_EXPORT const char *getClassname() const;

    Q_DECL_EXPORT QVariant getProperty(const QString &name) const;
    Q_DECL_EXPORT bool setProperty(const QString &name, const QVariant &value);

    Q_DECL_EXPORT qint64 getId() const;
    Q_DECL_EXPORT void setId(const qint64 &value);

  protected:
    Q_DECL_EXPORT virtual QString slimToString() const;
    qint64 id;
};
}
#endif // ENTITY_H
