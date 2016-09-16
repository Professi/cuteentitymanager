#ifndef ADDRESS_H
#define ADDRESS_H

#include <QString>
#include <QHash>
#include "entity.h"

class Person;
class Relation;
class Pupil;
class Address: public CuteEntityManager::Entity {
    Q_OBJECT

    Q_PROPERTY(QString label READ getLabel WRITE setLabel)
    Q_PROPERTY(QString street READ getStreet WRITE setStreet)
    Q_PROPERTY(QString postcode READ getPostcode WRITE setPostcode)
    Q_PROPERTY(QString city READ getCity WRITE setCity)
    Q_PROPERTY(QList<QSharedPointer<Person>> persons READ
               getPersons WRITE setPersons)
    Q_PROPERTY(QList<QSharedPointer<Pupil>> pupils READ
               getPupils WRITE setPupils)

  public:
    Q_INVOKABLE Address() {}
    Address(QString label, QString street, QString postcode, QString city);

    QString getLabel() const;
    void setLabel(const QString &value);

    QString getStreet() const;
    void setStreet(const QString &value);

    QString getPostcode() const;
    void setPostcode(const QString &value);

    QString getCity() const;
    void setCity(const QString &value);

    QList<QSharedPointer<Person> > getPersons() const;
    void setPersons(const QList<QSharedPointer<Person> > &value);

    const QHash<QString, CuteEntityManager::Relation> getRelations() const override;

    QList<QSharedPointer<Pupil> > getPupils() const;
    void setPupils(const QList<QSharedPointer<Pupil> > &value);

protected:
    QString label;
    QString street;
    QString postcode;
    QString city;
    QList<QSharedPointer<Person>> persons;
    QList<QSharedPointer<Pupil>> pupils;
};

#endif // ADDRESS_H
