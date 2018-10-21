#include "testpupilgreatgrandchild.h"

TestPupilGreatGrandChild::TestPupilGreatGrandChild() : TestPupilGrandChild()
{
}

QString TestPupilGreatGrandChild::greatGrandChildPropertyString() const
{
    return m_greatGrandChildPropertyString;
}

void TestPupilGreatGrandChild::setGreatGrandChildPropertyString(const QString &greatGrandChildPropertyString)
{
    m_greatGrandChildPropertyString = greatGrandChildPropertyString;
}

QList<QSharedPointer<TestPerson> > TestPupilGreatGrandChild::greatGrandChildPropertyPersons() const
{
    return m_greatGrandChildPropertyPersons;
}

void TestPupilGreatGrandChild::setGreatGrandChildPropertyPersons(const QList<QSharedPointer<TestPerson> > &greatGrandChildPropertyPersons)
{
    m_greatGrandChildPropertyPersons = greatGrandChildPropertyPersons;
}

const QHash<QString, Relation> TestPupilGreatGrandChild::getRelations() const
{
    auto hash = TestPupilGrandChild::getRelations();
//    hash.insert("greatGrandChildPropertyPersons", Relation("greatGrandChildPropertyPersons",RelationType::MANY_TO_MANY));
    return hash;
}

