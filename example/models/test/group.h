#ifndef GROUP_H
#define GROUP_H

#include "enums.h"
#include "entity.h"
#include "person.h"
#include "contact.h"
#include <QDebug>
//#include <QQuickView>



class Teacher;
class Person;
class Relation;
using namespace CuteEntityManager;

class Group: public CuteEntityManager::Entity
{
    Q_OBJECT
    Q_PROPERTY(QList<QSharedPointer<Person> > persons READ persons)

public:
    Q_INVOKABLE Group();

    virtual const QHash<QString, CuteEntityManager::Relation> getRelations() const;

    QList<QSharedPointer<Person> > persons() const;
    void setPersons(const QList<QSharedPointer<Person> > &persons);
    QSharedPointer<Person> personAt(int i) { return m_persons.at(i); }
    void addPerson(Person *p) {m_persons.append(QSharedPointer<Person>(p));}

    /*
    // getters
    QQmlListProperty <Person> persons();



    static void appendPerson(QQmlListProperty<Person> *list, Person *p);
    static int personsCount(QQmlListProperty<Person>*list);
    int personsCount() { return m_persons.count(); }
    static Person* personAt(QQmlListProperty<Person> *list, int i);

    static void personsClear(QQmlListProperty<Person> *list);

    // setters
    void setPersons(QList<Person*> persons) {m_persons = persons;}
    void removePerson(Person *p) {m_persons.removeOne(p);}

*/


    //    QList <SeatingPlan*> seatingPlans() {return m_seatingPlans;}
    //    QList <Teacher*> teachers() {return m_teachers;}
    //    QList <Person*> classPrefects() {return m_classPrefects;}
    //    QList <Person*> parentSpeakers() {return m_parentSpeakers;}



    //    void addSeatingPlan(SeatingPlan *s) {m_seatingPlans.append(s);}
    //    void removeSeatingPlan(SeatingPlan *s) {m_seatingPlans.removeOne(s);}
    //    void addTeacher(Teacher* t) {m_teachers.append(t);}
    //    void removeTeacher(Teacher* t) {m_teachers.removeOne(t);}
    //    void addClassPrefect(Person* p) {m_classPrefects.append(p);}
    //    void removeClassPrefect(Person* p) {m_classPrefects.removeOne(p);}
    //    void addParentSpeaker(Person* p) {m_parentSpeakers.append(p);}
    //    void removeParentSpeaker(Person* p) {m_parentSpeakers.removeOne(p);}





protected:
    // members
    QList<QSharedPointer<Person> > m_persons;

    //     QList <SeatingPlan*> m_seatingPlans;
//     QList <Teacher*> m_teachers;
//    QList <Person*> m_classPrefects;
//    QList <Person*> m_parentSpeakers;

};

#endif // GROUP_H
