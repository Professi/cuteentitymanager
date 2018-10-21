#include "testpupilchild.h"

TestPupilChild::TestPupilChild() : TestPupil()
{
}

QString TestPupilChild::childPropertyString() const
{
    return m_childPropertyString;
}

void TestPupilChild::setChildPropertyString(const QString &childPropertyString)
{
    m_childPropertyString = childPropertyString;
}

QList<QSharedPointer<TestPerson> > TestPupilChild::childPropertyPersons() const
{
    return m_childPropertyPersons;
}

void TestPupilChild::setChildPropertyPersons(const QList<QSharedPointer<TestPerson> > &childPropertyPersons)
{
    m_childPropertyPersons = childPropertyPersons;
}

const QHash<QString, Relation> TestPupilChild::getRelations() const
{
    auto hash = TestPupil::getRelations();
    hash.insert("childPropertyPersons", Relation("childPropertyPersons",RelationType::MANY_TO_MANY));
    return hash;
}
