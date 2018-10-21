#ifndef TESTPUPIL_H
#define TESTPUPIL_H

#include "testperson.h"

class TestPupil : public TestPerson
{
    Q_OBJECT
    Q_PROPERTY(QString legalGuardianNote READ legalGuardianNote WRITE setLegalGuardianNote)
    Q_PROPERTY(QList<QSharedPointer<TestGroup>> groups READ groups WRITE setGroups)
public:
    EM_MACRO(TestPupil)
    Q_INVOKABLE TestPupil();
    virtual ~TestPupil() override {}

    virtual const QHash<QString, CuteEntityManager::Relation> getRelations() const override;

    QList<QSharedPointer<TestGroup> > groups() const;
    void setGroups(const QList<QSharedPointer<TestGroup> > &groups);

    QString legalGuardianNote() const;
    void setLegalGuardianNote(const QString &legalGuardianNote);

protected:
    QString m_legalGuardianNote = QString();
    QList<QSharedPointer<TestGroup>> m_groups = QList<QSharedPointer<TestGroup>>();
};

#endif // TESTPUPIL_H
