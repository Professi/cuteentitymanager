#ifndef TESTPUPILGRANDCHILD_H
#define TESTPUPILGRANDCHILD_H

#include <QObject>
#include "testpupilchild.h"
#include "entitymanager.h"
#include "testpupilchild.h"

class TestPupilGrandChild : public TestPupilChild
{
    Q_OBJECT
    Q_PROPERTY(QString grandChildPropertyString READ grandChildPropertyString WRITE setGrandChildPropertyString)
    Q_PROPERTY(QList<QSharedPointer<TestPerson>> grandChildPropertyPersons READ grandChildPropertyPersons WRITE setGrandChildPropertyPersons)


public:
    EM_MACRO(TestPupilGrandChild)
    Q_INVOKABLE TestPupilGrandChild();
    virtual ~TestPupilGrandChild() override {}

    QString grandChildPropertyString() const;
    void setGrandChildPropertyString(const QString &grandChildPropertyString);

    QList<QSharedPointer<TestPerson> > grandChildPropertyPersons() const;
    void setGrandChildPropertyPersons(const QList<QSharedPointer<TestPerson> > &grandChildPropertyPersons);

    virtual const QHash<QString, CuteEntityManager::Relation> getRelations() const override;
    virtual InheritanceStrategy getInheritanceStrategy() const override { return InheritanceStrategy::JOINED_TABLE; }

private:
    QString m_grandChildPropertyString = "m_grandChildPropertyString";
    QList<QSharedPointer<TestPerson>> m_grandChildPropertyPersons = QList<QSharedPointer<TestPerson>>();

};

#endif // TESTPUPILGRANDCHILD_H
