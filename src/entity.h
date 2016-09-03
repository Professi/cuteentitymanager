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
#include <QObject>
#include <QSharedPointer>
#include <QStringList>
#include <QMetaProperty>
#include "relation.h"
#include "validators/validatorrule.h"
#include "validators/errormsg.h"
#include <QDebug>
namespace CuteEntityManager {

/**
 * You must not name any persisted property objectName, because its pre used by Qt and will be ignored by Entity Manager
 * @brief The Entity class
 */
class ValidationRule;
class ErrorMsg;
class Entity : public QObject {
    Q_OBJECT
    Q_PROPERTY(qint64 id READ getId WRITE setId NOTIFY idChanged)

  signals:
    void idChanged();

#define EM_MACRO(type) \
    virtual void setAsListProperty(const QSharedPointer<Entity> &e,QList<QSharedPointer<Entity>> &entList, const QMetaProperty &property) override { \
        QList<QSharedPointer<type>> list = *reinterpret_cast<QList<QSharedPointer<type>>*>(&entList); \
        QVariant var; \
        var.setValue<QList<QSharedPointer<type>>>(list); \
        property.write(e.data(), var); \
    }

//#define EM_PROPERTY(type,attribute,getter,setter)
//    Q_PROPERTY(QSharedPointer<type> attribute READ getter WRITE setter)

//#define EM_LIST_PROPERTY(type,attribute,getter,setter)
//    Q_PROPERTY(QList<QSharedPointer<type>> attribute READ getter WRITE setter)
//    EM_MACRO(type)



  public:
    virtual QString toString() const;
    /**
     * @brief copy
     * depends on Q_PROPERTIES
     * Copies them with exceptions of primary key(mostly "id") and objectName
     * @return
     */
    virtual Entity* copy() const;
    virtual ~Entity();
    virtual QList<ValidationRule> validationRules() const;
    virtual QString getTablename() const;
    virtual QString getClassname() const;
    virtual const QHash<QString, Relation> getRelations() const;
    virtual const Relation getRelation(const QString &name) const;
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
 virtual void setAsListProperty(const QSharedPointer<Entity> &e, QList<QSharedPointer<Entity>> &entList, const QMetaProperty &property) = 0;

  protected:
    explicit Entity (QObject *parent = 0);
    virtual QString slimToString() const;
    QList<ErrorMsg> errors;
    qint64 id = -1;
};
}
#endif // ENTITY_H
