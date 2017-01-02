#ifndef GROUP_H
#define GROUP_H
#include "entity.h"
#include <QDebug>

class Teacher;
class Person;
class Pupil;
//class Relation;
using namespace CuteEntityManager;

class Group: public CuteEntityManager::Entity {
    Q_OBJECT
    EM_MACRO(Group)
    Q_PROPERTY(QList<QSharedPointer<Pupil>> pupils READ getPupils WRITE setPupils)
    Q_PROPERTY(QList<QSharedPointer<Person>> persons READ getPersons WRITE
               setPersons)
    Q_PROPERTY(QString name READ getName WRITE setName)
    Q_PROPERTY(QSharedPointer<Person> mainTeacher READ getMainTeacher WRITE
               setMainTeacher)

  public:
    Q_INVOKABLE Group();
    const QHash<QString, CuteEntityManager::Relation> getRelations() const override;

    QString getName() const;
    void setName(const QString &value);

    QList<QSharedPointer<Pupil> > getPupils() const;
    void setPupils(const QList<QSharedPointer<Pupil> > &value);
    void addPupil(Pupil *pupil);
    QSharedPointer<Pupil> pupilAt(int i);

    QSharedPointer<Person> getMainTeacher() const;
    void setMainTeacher(const QSharedPointer<Person> &value);

    QList<QSharedPointer<Person> > getPersons() const;
    void addPerson(Person *person);
    void setPersons(const QList<QSharedPointer<Person> > &value);

  protected:
    QList<QSharedPointer<Pupil>> pupils;
    QList<QSharedPointer<Person>> persons;
    QSharedPointer<Person> mainTeacher;
    QString name;
};

#endif // GROUP_H
