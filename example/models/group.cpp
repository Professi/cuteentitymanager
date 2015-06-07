#include "group.h"

#include "models/person.h"
#include "models/group.h"
#include "../src/relation.h"
//#include <QQmlListProperty>
#include <QDebug>

Group::Group() : Entity() {
}

QString Group::getName() const
{
    return name;
}

void Group::setName(const QString &value)
{
    name = value;
}
QSharedPointer<Teacher> Group::getTeacher() const
{
    return teacher;
}

void Group::setTeacher(const QSharedPointer<Teacher> &value)
{
    teacher = value;
}
QList<QSharedPointer<Pupil> > Group::getPupils() const
{
    return pupils;
}

void Group::setPupils(const QList<QSharedPointer<Pupil> > &value)
{
    pupils = value;
}
QList<QSharedPointer<Pupil> > Group::getClassPrefects() const
{
    return classPrefects;
}

void Group::setClassPrefects(const QList<QSharedPointer<Pupil> > &value)
{
    classPrefects = value;
}
QList<QSharedPointer<Person> > Group::getParentSpeakers() const
{
    return parentSpeakers;
}

void Group::setParentSpeakers(const QList<QSharedPointer<Person> > &value)
{
    parentSpeakers = value;
}

const QHash<QString, Relation> Group::getRelations() const
{
    auto hash = Entity::getRelations();
    hash.insert("teacher",Relation("teacher",MANY_TO_ONE,false));
    hash.insert("pupils",Relation("pupils",MANY_TO_MANY));
    hash.insert("classPrefects",Relation("classPrefects",MANY_TO_MANY));
    hash.insert("parentSpeakers",Relation("parentSpeakers",MANY_TO_MANY));
    return hash;
}









