#include "testgroup.h"
#include "testperson.h"
#include "testpupil.h"
#include <QDebug>

TestGroup::TestGroup() : Entity() {
}

const QHash<QString, CuteEntityManager::Relation> TestGroup::getRelations() const {
    auto hash = QHash<QString, CuteEntityManager::Relation>();
    hash.insert("pupils", CuteEntityManager::Relation(
                    "pupils", CuteEntityManager::RelationType::MANY_TO_MANY));
    return hash;
}


QList<QSharedPointer<TestPupil> > TestGroup::pupils() const {
    return m_pupils;
}

void TestGroup::setPupils(const QList<QSharedPointer<TestPupil> > &pupils) {
    m_pupils = pupils;
}

QString TestGroup::name() const {
    return m_name;
}

void TestGroup::setName(const QString &value) {
    m_name = value;
}


