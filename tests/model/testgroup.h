#ifndef TESTGROUP_H
#define TESTGROUP_H

#include <QDebug>
#include "entitymanager.h"

class TestPupil;
class SeatingPlan;
class TestPerson;
class AppData;

using namespace CuteEntityManager;

class TestGroup: public CuteEntityManager::Entity
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QList<QSharedPointer<TestPupil>> pupils READ pupils WRITE setPupils)

public:
    EM_MACRO(TestGroup)
    Q_INVOKABLE TestGroup();
    virtual ~TestGroup() override {}

    QString name() const;
    void setName(const QString &value);

    QList<QSharedPointer<TestPupil> > pupils() const;
    void setPupils(const QList<QSharedPointer<TestPupil> > &pupils);
    QSharedPointer<TestPupil> pupilAt(int i) { return m_pupils.at(i); }
    void addPupil(QSharedPointer<TestPupil> p) {m_pupils.append(p);}

    virtual const QHash<QString, CuteEntityManager::Relation> getRelations() const override;

protected:
    // members
    QString m_name;
    QList<QSharedPointer<TestPupil> > m_pupils;
};

#endif // TESTGROUP_H
