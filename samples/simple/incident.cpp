#include "incident.h"
#include <QDebug>

Incident::Incident() :
    Entity()
{

}

void Incident::initIncident(const QSharedPointer<Pupil> pupil,
        const QSharedPointer<Group> group,
        const QDateTime dateTime)
{
    this->setPupil(pupil);
    this->setGroup(group);
//    this->setRoom(room);
//    this->setAppData(appData);
    this->setBookedFor(dateTime);
    this->setBookedAt(dateTime);
    m_cancelledAt = QDateTime();
    this->setLocked(false);
    this->setPredecessor(QSharedPointer<Incident>());
}

QDateTime Incident::bookedFor() const
{
    return m_bookedFor;
}

void Incident::setBookedFor(const QDateTime &bookedFor)
{
    m_bookedFor = bookedFor;
}

QDateTime Incident::bookedAt() const
{
    return m_bookedAt;
}

void Incident::setBookedAt(const QDateTime &bookedAt)
{
    m_bookedAt = bookedAt;
}

QDateTime Incident::cancelledAt() const
{
    return m_cancelledAt;
}

void Incident::setCancelledAt(const QDateTime &cancelledAt, bool forceOverwrite)
{
    if (m_cancelledAt.isValid() && !forceOverwrite) {
        // sometimes an EntityManager metacall reaches this, too. Immediately after setting it manually. (<= 1ms?)
        // reproduce: change attendanceIncident, ok, change again
        // qint64 diff = qAbs(m_cancelledAt.secsTo(cancelledAt));
        // if (diff > 10) { // giving some delay headroom for a possible double call
        qDebug()<< "\n\n-------------------------------\n-------------------------------\n-------------------------------\nWHY DOES THIS HAPPEN? \nEach incident's cancelledAt has been invalidated in the ctor!\n------------------------\n-------------------------------\n-------------------------------\n-------------------------------";
        // Q_ASSERT(!m_cancelledAt.isValid());
        // THROW_MODERATE_ERROR_CIT("Das Canceln eines Ereignisses ist fehlgeschlagen, das Ereignis war bereits vorher gecancelt!");
        // }
    }
    m_cancelledAt = cancelledAt;
}

QSharedPointer<Pupil> Incident::pupil() const
{
    return m_pupil;
}

void Incident::setPupil(const QSharedPointer<Pupil> &pupil)
{
    m_pupil = pupil;
}

QSharedPointer<Group> Incident::group() const
{
    return m_group;
}

void Incident::setGroup(const QSharedPointer<Group> &group)
{
    m_group = group;
}

bool Incident::cancelled(QDateTime dateTime) const
{
    if (!m_cancelledAt.isValid()) {
        return false;
    }
    return (dateTime>cancelledAt());
}

bool Incident::locked() const
{
    return m_locked;
}

void Incident::setLocked(bool locked)
{
    m_locked = locked;
}

QString Incident::additionalInfo() const
{
    return m_additionalInfo;
}

void Incident::setAdditionalInfo(const QString &additionalInfo)
{
    m_additionalInfo = additionalInfo;
}

const QHash<QString, Relation> Incident::getRelations() const
{
    auto hash = QHash<QString, CuteEntityManager::Relation>();

    hash.insert("pupil",CuteEntityManager::Relation(
                    "pupil",CuteEntityManager::RelationType::MANY_TO_ONE));
    hash.insert("group",CuteEntityManager::Relation(
                    "group",CuteEntityManager::RelationType::MANY_TO_ONE));
    hash.insert("predecessor", CuteEntityManager::Relation("predecessor", true, CuteEntityManager::RelationType::ONE_TO_ONE));
    return hash;
}

QSharedPointer<Incident> Incident::predecessor() const
{
    return m_predecessor;
}

void Incident::setPredecessor(const QSharedPointer<Incident> &predecessor)
{
    m_predecessor = predecessor;
}

bool  Incident::lessThanBookedFor(const QSharedPointer<Incident> &a, const QSharedPointer<Incident> &b) {
        return a->bookedFor() < b->bookedFor();
}

bool  Incident::moreThanBookedFor(const QSharedPointer<Incident> &a, const QSharedPointer<Incident> &b) {
        return a->bookedFor() > b->bookedFor();
}

bool Incident::lessThanBookedAt(const QSharedPointer<Incident> &a, const QSharedPointer<Incident> &b) {
        return a->bookedAt() < b->bookedAt();
}

bool Incident::moreThanBookedAt(const QSharedPointer<Incident> &a, const QSharedPointer<Incident> &b) {
        return a->bookedAt() > b->bookedAt();
}













