#include "group.h"

#include "enums.h"

#include "person.h"
#include "group.h"
#include "contact.h"
#include <QDebug>

Group::Group() : Entity()
{
    //connect(this,SIGNAL(personsChanged()),this,SLOT(personChangedSlot()));
//    m_persons.append(new Person("Vera","Geseke",Person::FEMALE,"Vera Geseke.jpg","","",QDate::currentDate()));
//    m_persons.append(new Person("Harry","Hirsch",Person::MALE));
//    m_persons.append(new Person("Sibylle","Mentzel",Person::FEMALE,"Sibylle Mentzel.jpg","","",QDate::currentDate()));

}

const QHash<QString, CuteEntityManager::Relation> Group::getRelations() const
{
        auto hash = QHash<QString, CuteEntityManager::Relation>();
        hash.insert("persons",CuteEntityManager::Relation("persons",MANY_TO_MANY,QString("")));
        return hash;
}

QList<QSharedPointer<Person> > Group::persons() const
{
    return m_persons;
}

void Group::setPersons(const QList<QSharedPointer<Person> > &persons)
{
    m_persons = persons;
}


/*void Group::personChangedSlot()
{
}

QQmlListProperty <Person> Group::persons()
{
    return QQmlListProperty<Person>(this,0, &appendPerson,&personsCount,&personAt,&personsClear);
}


void Group::appendPerson(QQmlListProperty<Person> *list, Person *p) {
    Group *group = qobject_cast<Group*>(list->object);
    if(group && p) {
        group->addPerson(p);
        emit group->personsChanged();
    }
}

int Group::personsCount(QQmlListProperty<Person>*list)
{
    Group *group = qobject_cast<Group*>(list->object);
    if (group)
        return group->m_persons.count();
    return 0;
}

Person* Group::personAt(QQmlListProperty<Person> *list, int i)
{
    Group *group = qobject_cast<Group*>(list->object);
    if (group)
        return group->m_persons.at(i);
    return 0;
}
Person* Group::personAt(int i)
{
    return this->m_persons.at(i);
}

void Group::personsClear(QQmlListProperty<Person> *list)
{
    Group *group = qobject_cast<Group*>(list->object);
    if (group) {
        group->m_persons.clear();
        emit group->personsChanged();
    }
}
*/


