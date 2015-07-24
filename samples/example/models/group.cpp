#include "group.h"
#include "pupil.h"
#include <QDebug>

Group::Group() : Entity() {

}

const QHash<QString, CuteEntityManager::Relation> Group::getRelations() const {
    auto hash = QHash<QString, CuteEntityManager::Relation>();
    hash.insert("pupils", CuteEntityManager::Relation("pupils",
                RelationType::MANY_TO_MANY));
    hash.insert("persons", CuteEntityManager::Relation("persons",
                RelationType::MANY_TO_MANY));
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
QList<QSharedPointer<Pupil> > Group::getPupils() const {
    return pupils;
}

void Group::setPupils(const QList<QSharedPointer<Pupil> > &value) {
    pupils = value;
}

void Group::addPupil(Pupil *pupil) {
    this->pupils.append(QSharedPointer<Pupil>(pupil));
}

QSharedPointer<Pupil> Group::pupilAt(int i) {
    return this->pupils.at(i);
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




