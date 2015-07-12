#ifndef GROUP_H
#define GROUP_H

#include "enums.h"
#include "entity.h"
#include "contact.h"
#include "pupil.h"
#include <QDebug>
//#include <QQuickView>



class Teacher;
class Person;
class Pupil;
class Relation;
using namespace CuteEntityManager;

class Group: public CuteEntityManager::Entity {
    Q_OBJECT
    Q_PROPERTY(QList<QSharedPointer<Pupil>> pupils READ getPupils WRITE setPupils)
    Q_PROPERTY(QString name READ getName WRITE setName)
    Q_PROPERTY(QSharedPointer<Person> mainTeacher READ getMainTeacher WRITE
               setMainTeacher)

  public:
    Q_INVOKABLE Group();
    virtual const QHash<QString, CuteEntityManager::Relation> getRelations() const;

    QString getName() const;
    void setName(const QString &value);

    QList<QSharedPointer<Pupil> > getPupils() const;
    void setPupils(const QList<QSharedPointer<Pupil> > &value);
    void addPupil(Pupil *pupil);
    QSharedPointer<Pupil> pupilAt(int i);

    QSharedPointer<Person> getMainTeacher() const;
    void setMainTeacher(const QSharedPointer<Person> &value);

  protected:
    QList<QSharedPointer<Pupil>> pupils;
    QSharedPointer<Person> mainTeacher;
    QString name;
};

#endif // GROUP_H
