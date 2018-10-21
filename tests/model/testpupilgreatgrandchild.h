#ifndef TESTPUPILGREATGRANDCHILD_H
#define TESTPUPILGREATGRANDCHILD_H

#include <QObject>
#include "testpupilgrandchild.h"
#include "entitymanager.h"

class TestPupilGreatGrandChild : public TestPupilGrandChild
{
    Q_OBJECT
    Q_PROPERTY(QString greatGrandChildPropertyString READ greatGrandChildPropertyString WRITE setGreatGrandChildPropertyString)

public:
    EM_MACRO(TestPupilGreatGrandChild)
    Q_INVOKABLE TestPupilGreatGrandChild();
    virtual ~TestPupilGreatGrandChild() override {}

    QString greatGrandChildPropertyString() const;
    void setGreatGrandChildPropertyString(const QString &greatGrandChildPropertyString);

    // not used with Q_PROPERTY, nor in getRelations
    QList<QSharedPointer<TestPerson> > greatGrandChildPropertyPersons() const;
    void setGreatGrandChildPropertyPersons(const QList<QSharedPointer<TestPerson> > &greatGrandChildPropertyPersons);

    virtual const QHash<QString, CuteEntityManager::Relation> getRelations() const override;
    virtual InheritanceStrategy getInheritanceStrategy() const override { return InheritanceStrategy::JOINED_TABLE; }

signals:

public slots:
private:
    QString m_greatGrandChildPropertyString = "m_greatGrandChildPropertyString";
    QList<QSharedPointer<TestPerson>> m_greatGrandChildPropertyPersons;
};


#endif // TESTPUPILGREATGRANDCHILD_H
