#include "group.h"
#include "../samples/example/models/pupil.h"
#include <QDebug>

Group::Group() : Entity() {

}

const QHash<QString, CuteEntityManager::Relation> Group::getRelations() const {
    auto hash = QHash<QString, CuteEntityManager::Relation>();
    hash.insert("persons", CuteEntityManager::Relation("persons",
                RelationType::MANY_TO_MANY, QString("groups")));
    hash.insert("mainTeacher", CuteEntityManager::Relation("mainTeacher",
                RelationType::MANY_TO_ONE));
    return hash;
}

QString Group::getName() const {
    return name;
}

void Group::setName(const QString &value) {
    name = value;
}

QSharedPointer<Person> Group::getMainTeacher() const {
    return mainTeacher;
}

void Group::setMainTeacher(const QSharedPointer<Person> &value) {
    mainTeacher = value;
}
QList<QSharedPointer<Person> > Group::getPersons() const {
    return persons;
}

void Group::addPerson(Person *person) {
    this->persons.append(QSharedPointer<Person>(person));
}

void Group::setPersons(const QList<QSharedPointer<Person> > &value) {
    persons = value;
}




