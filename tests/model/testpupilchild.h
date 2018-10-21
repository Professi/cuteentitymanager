#ifndef TESTPUPILCHILD_H
#define TESTPUPILCHILD_H

#include <QObject>
#include "testpupil.h"
#include "entitymanager.h"

class TestPupilChild : public TestPupil
{
    Q_OBJECT
    Q_PROPERTY(QString childPropertyString READ childPropertyString WRITE setChildPropertyString)
    Q_PROPERTY(QList<QSharedPointer<TestPerson>> childPropertyPersons READ childPropertyPersons WRITE setChildPropertyPersons)

public:
    EM_MACRO(TestPupilChild)
    Q_INVOKABLE TestPupilChild();
    virtual ~TestPupilChild() override {}

    QString childPropertyString() const;
    void setChildPropertyString(const QString &childPropertyString);

    QList<QSharedPointer<TestPerson> > childPropertyPersons() const;
    void setChildPropertyPersons(const QList<QSharedPointer<TestPerson> > &childPropertyPersons);

    virtual const QHash<QString, CuteEntityManager::Relation> getRelations() const override;
    virtual InheritanceStrategy getInheritanceStrategy() const override { return InheritanceStrategy::JOINED_TABLE; }

signals:

public slots:
private:
    QString m_childPropertyString = "m_childPropertyString";
    QList<QSharedPointer<TestPerson>> m_childPropertyPersons = QList<QSharedPointer<TestPerson>>();

};

#endif // TESTPUPILCHILD_H
