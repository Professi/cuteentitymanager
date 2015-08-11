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
#include "validators/validatorrule.h"
#include "validators/errormsg.h"
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
    virtual QString toString() const;
    virtual ~Entity();
    virtual QList<ValidationRule> validationRules() const;
    virtual QString getTablename() const;
    virtual const QHash<QString, Relation> getRelations() const;
    virtual const QStringList getTransientAttributes() const;
    virtual const QStringList getBLOBColumns() const;
    virtual InheritanceStrategy getInheritanceStrategy() const;
    virtual bool isInheritanceCascaded() const;
    //return value must be the exact name defined in Q_PROPERTY
    virtual QString getPrimaryKey() const;

    QVariant getProperty(const QString &name) const;
    bool setProperty(const QString &name, const QVariant &value);
    qint64 getId() const;
    void setId(const qint64 &value);

    bool hasErrors() const;

    QList<ErrorMsg> getErrors() const;
    QString getErrorsAsString() const;
    void setErrors(const QList<ErrorMsg> &value);

protected:
    explicit Entity (QObject *parent = 0);
    virtual QString slimToString() const;
    QList<ErrorMsg> errors;
    qint64 id;
};
}
#endif // ENTITY_H
