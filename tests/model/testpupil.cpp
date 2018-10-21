#include "testpupil.h"

TestPupil::TestPupil()
    :TestPerson()
{
}

const QHash<QString, Relation> TestPupil::getRelations() const
{
    auto hash = TestPerson::getRelations();
    hash.insert("groups",Relation("groups",CuteEntityManager::RelationType::MANY_TO_MANY,QString("pupils")));
    return hash;
}
QList<QSharedPointer<TestGroup> > TestPupil::groups() const
{
    return m_groups;
}

void TestPupil::setGroups(const QList<QSharedPointer<TestGroup> > &groups)
{
    m_groups = groups;
}

QString TestPupil::legalGuardianNote() const
{
    return m_legalGuardianNote;
}

void TestPupil::setLegalGuardianNote(const QString &legalGuardianNote)
{
    m_legalGuardianNote = legalGuardianNote;
}
