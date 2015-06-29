#include "pupil.h"

Pupil::Pupil() : Person() {

}
QSharedPointer<Person> Pupil::getParent() const
{
    return parent;
}

void Pupil::setParent(const QSharedPointer<Person> &value)
{
    parent = value;
}
QString Pupil::getName() const
{
    return name;
}

void Pupil::setName(const QString &value)
{
    name = value;
}

const QHash<QString, Relation> Pupil::getRelations() const {
    auto hash = Person::getRelations();
    hash.insert("parent", Relation("parent", true, ONE_TO_ONE));
    hash.insert("groups", Relation("groups", ONE_TO_MANY, "teacher"));
    return hash;
}
