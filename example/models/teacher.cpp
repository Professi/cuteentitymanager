#include "teacher.h"

Teacher::Teacher(QSharedPointer<Person> parent) : Person() {
    this->parent = parent;
}

const QHash<QString, Relation> Teacher::getRelations() const {
    auto hash = Person::getRelations();
    hash.insert("parent", Relation("parent", ONE_TO_ONE));
    hash.insert("groups", Relation("groups", ONE_TO_MANY, "teacher"));
    return hash;
}

QList<QSharedPointer<Group> > Teacher::getGroups() const {
    return groups;
}

void Teacher::setGroups(const QList<QSharedPointer<Group> > &value) {
    groups = value;
}

QSharedPointer<Person> Teacher::getParent() const {
    return parent;
}

void Teacher::setParent(const QSharedPointer<Person> &value) {
    parent = value;
}



