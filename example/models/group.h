#ifndef GROUP_H
#define GROUP_H

#define BR_PROPERTY(TYPE,NAME,DEFAULT)                  \
TYPE NAME;                                              \
TYPE get_##NAME() const { return NAME; }                \
void set_##NAME(TYPE the_##NAME) { NAME = the_##NAME; } \
void reset_##NAME() { NAME = DEFAULT; }


#include "models/person.h"
//#include <QQmlListProperty>
#include <QDebug>
#include <QList>
#include <QVariantList>
//#include <QQuickView>



class SeatingPlan;
class Teacher;
class Person;


class Group: public CuteEntityManager::Entity {
    Q_OBJECT
    //Q_ENUMS(Gender)
    //Q_PROPERTY(QList<Person*> persons READ getPersons)

//    Q_PROPERTY(QList<Person*> persons READ get_persons WRITE set_persons RESET reset_persons)
//    BR_PROPERTY(QList<Person*>, persons, QList<Person*>())
Q_PROPERTY(QList<Person*> persons READ getPersons WRITE setPersons NOTIFY personsChanged)

  signals:
    void personsChanged();

  public slots:
    void personChangedSlot();

  public:
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

protected:
    // members
    QList<Person*> persons;
    QList <Person *> m_classPrefects;
    QList <Person *> m_parentSpeakers;

//    PersonListModel* m_personListModel;
};
#endif // GROUP_H
