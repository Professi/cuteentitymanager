#include "group.h"

#include "enums.h"

#include "person.h"
#include "group.h"
#include "contact.h"
#include <QDebug>

Group::Group() : Entity() {

}

const QHash<QString, CuteEntityManager::Relation> Group::getRelations() const {
    auto hash = QHash<QString, CuteEntityManager::Relation>();
    hash.insert("pupils", CuteEntityManager::Relation("pupils", MANY_TO_MANY));
    hash.insert("mainTeacher", CuteEntityManager::Relation("mainTeacher",
                MANY_TO_ONE));
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



