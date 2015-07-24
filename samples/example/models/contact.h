#ifndef CONTACT_H
#define CONTACT_H

#include <QString>
#include "entity.h"

class Relation;
class Person;
class Pupil;
class Contact: public CuteEntityManager::Entity {
    Q_OBJECT

    Q_PROPERTY(QString content READ getContent WRITE setContent)
    Q_PROPERTY(Category category READ getCategory WRITE setCategory)
    Q_PROPERTY(QString label READ getLabel WRITE setLabel)
    Q_PROPERTY(QList<QSharedPointer<Person>> persons READ
               getPersons WRITE setPersons)
    Q_PROPERTY(QList<QSharedPointer<Pupil>> pupils READ
               getPupils WRITE setPupils)

  public:
    enum Category {EMAIL, MOBILE, LANDLINE, MESSENGER, EXTRA} ;
    Q_ENUM(Category)
    Q_INVOKABLE Contact() {}
    Contact(QString label, Category category, QString content);
    const QHash<QString, CuteEntityManager::Relation> getRelations() const
    override;

    QString getContent() const;
    void setContent(const QString &value);

    QString getLabel() const;
    void setLabel(const QString &value);

    Category getCategory() const;
    void setCategory(const Category &value);

    QList<QSharedPointer<Person> > getPersons() const;
    void setPersons(const QList<QSharedPointer<Person> > &value);

    QList<QSharedPointer<Pupil> > getPupils() const;
    void setPupils(const QList<QSharedPointer<Pupil> > &value);

protected:
    QString content;
    Category category;
    QString label;
    QList<QSharedPointer<Person>> persons;
    QList<QSharedPointer<Pupil>> pupils;
};

#endif // CONTACT_H
