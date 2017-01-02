#ifndef INCIDENT_H
#define INCIDENT_H
#include <QDateTime>
#include <QObject>

#include "entity.h"

//#include "src/enums.h"

using namespace CuteEntityManager;

//class AppData;
class Pupil;
class Group;
//class Room;
//class SeatingPlan;

class Incident : public Entity
{
    Q_OBJECT
    EM_MACRO(Incident)
    Q_PROPERTY(bool locked READ locked WRITE setLocked) // i.e.: has had impacts on not undoable events

    Q_PROPERTY(QDateTime bookedFor READ bookedFor WRITE setBookedFor)
    Q_PROPERTY(QDateTime bookedAt READ bookedAt WRITE setBookedAt)
    Q_PROPERTY(QDateTime cancelledAt READ cancelledAt WRITE setCancelledAt)

    Q_PROPERTY(QSharedPointer<Pupil> pupil READ pupil WRITE setPupil)
//    Q_PROPERTY(QSharedPointer<AppData> appData READ appData WRITE setAppData)
    Q_PROPERTY(QSharedPointer<Group> group READ group WRITE setGroup)
//    Q_PROPERTY(QSharedPointer<Room> room READ room WRITE setRoom)
//    Q_PROPERTY(QSharedPointer<SeatingPlan> seatingPlan READ seatingPlan WRITE setSeatingPlan)

    Q_PROPERTY(QString additionalInfo READ additionalInfo WRITE setAdditionalInfo)
    Q_PROPERTY(QSharedPointer<Incident> predecessor READ predecessor WRITE setPredecessor)

public:
    Q_INVOKABLE Incident();

    void initIncident(
            const QSharedPointer<Pupil> pupil,
            const QSharedPointer<Group> group,
//            const QSharedPointer<Room> room,
//            const QSharedPointer<AppData> appData,
            const QDateTime dateTime);

//    virtual Enums::AppType appType() {return Enums::AppType::NOAPP; }

    QDateTime bookedFor() const;
    void setBookedFor(const QDateTime &bookedFor);

    QDateTime bookedAt() const;
    void setBookedAt(const QDateTime &bookedAt);

    QDateTime cancelledAt() const;
    void setCancelledAt(const QDateTime &cancelledAt, bool forceOverwrite = false);

    QSharedPointer<Pupil> pupil() const;
    void setPupil(const QSharedPointer<Pupil> &pupil);

//    QSharedPointer<AppData> appData() const;
//    void setAppData(const QSharedPointer<AppData> &appData);

    QSharedPointer<Group> group() const;
    void setGroup(const QSharedPointer<Group> &group);

    bool cancelled(QDateTime dateTime) const;

    bool locked() const;
    void setLocked(bool locked);

//    QSharedPointer<Room> room() const;
//    void setRoom(const QSharedPointer<Room> &room);

    QString additionalInfo() const;
    void setAdditionalInfo(const QString &additionalInfo);

    virtual const QHash<QString, CuteEntityManager::Relation> getRelations() const override;

//    QSharedPointer<SeatingPlan> seatingPlan() const;
//    void setSeatingPlan(const QSharedPointer<SeatingPlan> &seatingPlan);

    QSharedPointer<Incident> predecessor() const;
    void setPredecessor(const QSharedPointer<Incident> &predecessor);

    static bool lessThanBookedFor(const QSharedPointer<Incident> &a, const QSharedPointer<Incident> &b);
    static bool moreThanBookedFor(const QSharedPointer<Incident> &a, const QSharedPointer<Incident> &b);
    static bool lessThanBookedAt(const QSharedPointer<Incident> &a, const QSharedPointer<Incident> &b);
    static bool moreThanBookedAt(const QSharedPointer<Incident> &a, const QSharedPointer<Incident> &b);
protected:
    QDateTime m_bookedFor;
    QDateTime m_bookedAt;
    QDateTime m_cancelledAt;
    QSharedPointer<Pupil> m_pupil;
//    QSharedPointer<AppData> m_appData;
    QSharedPointer<Group> m_group;
//    QSharedPointer<Room> m_room;
//    QSharedPointer<SeatingPlan> m_seatingPlan;
    bool m_cancelled = false;
    bool m_locked = false;
    QString m_additionalInfo;
    QSharedPointer<Incident> m_predecessor;



};

#endif // INCIDENT_H
