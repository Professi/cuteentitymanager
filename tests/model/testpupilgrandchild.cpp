#include "testpupilgrandchild.h"

TestPupilGrandChild::TestPupilGrandChild() : TestPupilChild()
{
}

QString TestPupilGrandChild::grandChildPropertyString() const
{
    return m_grandChildPropertyString;
}

void TestPupilGrandChild::setGrandChildPropertyString(const QString &grandChildPropertyString)
{
    m_grandChildPropertyString = grandChildPropertyString;
}

QList<QSharedPointer<TestPerson> > TestPupilGrandChild::grandChildPropertyPersons() const
{
    return m_grandChildPropertyPersons;
}

void TestPupilGrandChild::setGrandChildPropertyPersons(const QList<QSharedPointer<TestPerson> > &grandChildPropertyPersons)
{
    m_grandChildPropertyPersons = grandChildPropertyPersons;
}

const QHash<QString, Relation> TestPupilGrandChild::getRelations() const
{
    auto hash = TestPupilChild::getRelations();
    hash.insert("grandChildPropertyPersons", Relation("grandChildPropertyPersons",RelationType::MANY_TO_MANY));
    return hash;
}
