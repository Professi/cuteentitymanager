#ifndef GROUP_H
#define GROUP_H

#include "models/person.h"
//#include <QQmlListProperty>
#include <QDebug>
#include <QList>
#include <QVariantList>
//#include <QQuickView>
#include "artikel.h"
#include <QSharedPointer>



class SeatingPlan;
class Teacher;
class Person;
class Relation;

class Group: public CuteEntityManager::Entity {
    Q_OBJECT
    //Q_ENUMS(Gender)
    //Q_PROPERTY(QList<Person*> persons READ getPersons)

//    Q_PROPERTY(QList<Person*> persons READ get_persons WRITE set_persons RESET reset_persons)
//    BR_PROPERTY(QList<Person*>, persons, QList<Person*>())
Q_PROPERTY(QList<Person*> persons READ getPersons WRITE setPersons NOTIFY personsChanged)
    Q_PROPERTY(Person* teacher READ getTeacher WRITE setTeacher)
    Q_PROPERTY(QSharedPointer<Person> teacherP READ getTeacherP WRITE setTeacherP)
    Q_PROPERTY(QSharedPointer<Artikel> artikel READ getArtikel WRITE setArtikel)

  signals:
    void personsChanged();

  public slots:
    void personChangedSlot();

  public:
    virtual const QHash<QString, CuteEntityManager::Relation> getRelations() const;
    // constructor
    Group();

    // getters
//    QQmlListProperty <Person> persons();


//    static void appendPerson(QQmlListProperty<Person> *list, Person *p);
//    static int personsCount(QQmlListProperty<Person>*list);
//    static Person* personAt(QQmlListProperty<Person> *list, int i);
//    static void personsClear(QQmlListProperty<Person> *list);

    QList <Person *> classPrefects() {
        return m_classPrefects;
    }
    QList <Person *> parentSpeakers() {
        return m_parentSpeakers;
    }

    // setters
    void removePerson(Person *p) {
        persons.removeOne(p);
    }
    void addClassPrefect(Person *p) {
        m_classPrefects.append(p);
    }
    void removeClassPrefect(Person *p) {
        m_classPrefects.removeOne(p);
    }
    void addParentSpeaker(Person *p) {
        m_parentSpeakers.append(p);
    }
    void removeParentSpeaker(Person *p) {
        m_parentSpeakers.removeOne(p);
    }

    void addPerson(Person *p) {
        persons.append(p);
    }

    QList<Person *> getPersons() const;
    void setPersons(const QList<Person *> &value);

    QSharedPointer<Person> getTeacherP() const;
    void setTeacherP(const QSharedPointer<Person> &value);

    Person *getTeacher() const;
    void setTeacher(Person *value);

    QSharedPointer<Artikel> getArtikel() const;
    void setArtikel(const QSharedPointer<Artikel> &value);

protected:
    // members
    Person* teacher;
    QSharedPointer<Person> teacherP;
    QList<Person*> persons;
    QSharedPointer<Artikel> artikel;
    QList <Person *> m_classPrefects;
    QList <Person *> m_parentSpeakers;

//    PersonListModel* m_personListModel;
};
#endif // GROUP_H
