#include "group.h"

#include "models/person.h"
#include "models/group.h"
#include "relation.h"
//#include <QQmlListProperty>
#include <QDebug>

Group::Group() : Entity() {
    connect(this, SIGNAL(personsChanged()), this, SLOT(personChangedSlot()));
    qDebug() << "Konstruktor!";
    persons = QList<Person *>();
    persons.append(new Person("Vera", "Geseke", Person::FEMALE, "Vera Geseke.jpg", "", "", QDate::currentDate()));
    persons.append(new Person("Harry", "Hirsch", Person::MALE));
    persons.append(new Person("Sibylle", "Mentzel", Person::FEMALE, "Sibylle Mentzel.jpg", "", "", QDate::currentDate()));
}

QList<Person *> Group::getPersons() const {
    return persons;
}

void Group::setPersons(const QList<Person *> &value) {
    qDebug() << "set!!!";
    persons = value;
}
QSharedPointer<Person> Group::getTeacherP() const {
    return teacherP;
}

void Group::setTeacherP(const QSharedPointer<Person> &value) {
    teacherP = value;
}
Person *Group::getTeacher() const {
    return teacher;
}

void Group::setTeacher(Person *value) {
    teacher = value;
}
QSharedPointer<Artikel> Group::getArtikel() const {
    return artikel;
}

void Group::setArtikel(const QSharedPointer<Artikel> &value) {
    artikel = value;
}

void Group::personChangedSlot() {
    qDebug() << "changed!";
}

QHash<QString, CuteEntityManager::Relation> Group::getRelations() {
    QHash<QString, CuteEntityManager::Relation> h = QHash<QString, CuteEntityManager::Relation>();
    CuteEntityManager::Relation r = CuteEntityManager::Relation("artikel", CuteEntityManager::MANY_TO_ONE);
    h.insert("artikel", r);
    return h;
}

//void Group::appendPerson(QQmlListProperty<Person> *list, Person *p) {
//    Group *group = qobject_cast<Group*>(list->object);
//    if(group && p) {
//        group->addPerson(p);
//        emit group->personsChanged();
//    }
//}

//int Group::personsCount(QQmlListProperty<Person>*list)
//{
//    Group *group = qobject_cast<Group*>(list->object);
//    if (group)
//        return group->m_persons.count();
//    return 0;
//}

//Person* Group::personAt(QQmlListProperty<Person> *list, int i)
//{
//    Group *group = qobject_cast<Group*>(list->object);
//    if (group)
//        return group->m_persons.at(i);
//    return 0;

//}

//void Group::personsClear(QQmlListProperty<Person> *list)
//{
//    Group *group = qobject_cast<Group*>(list->object);
//    if (group) {
//        group->m_persons.clear();
//        emit group->personsChanged();
//    }
//}



