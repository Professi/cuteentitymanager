#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include "entitymanager.h"

#include "person.h"
#include "pupil.h"
#include "group.h"
#include "address.h"
#include "contact.h"

#include "occasion.h"
#include "ratingmarkdefinition.h"
#include "ratingmarksystem.h"
#include "ratingmarkincident.h"
#include "datacreation.h"
#include "incident.h"

#include "stuff.h"

using namespace CuteEntityManager;
int main(int argc, char *argv[]) {
    Q_UNUSED(argc) Q_UNUSED(argv);
    EntityInstanceFactory::registerClass<Address>();
    EntityInstanceFactory::registerClass<Contact>();
    EntityInstanceFactory::registerClass<Person>();
    EntityInstanceFactory::registerClass<Pupil>();
    EntityInstanceFactory::registerClass<Group>();
    EntityInstanceFactory::registerClass<Occasion>();
    EntityInstanceFactory::registerClass<Incident>();
    EntityInstanceFactory::registerClass<RatingMarkDefinition>();
    EntityInstanceFactory::registerClass<RatingMarkIncident>();
    EntityInstanceFactory::registerClass<RatingMarkSystem>();

    QSharedPointer<CuteEntityManager::EntityManager> e =
            QSharedPointer<CuteEntityManager::EntityManager>(new
                                                             CuteEntityManager::EntityManager("QSQLITE",
                                                                                              QDir::currentPath() + "/db.sqlite"));
    qDebug()<<QDir::currentPath();
    QStringList inits = QStringList() << "Address" << "Contact" << "Person" << "Pupil" << "Group" << "Incident" << "Occasion" << "RatingMarkDefinition" << "RatingMarkIncident" << "RatingMarkSystem";
    e->startup("0.1", inits);

    try {
        auto entities = DataCreation::createRatingEntities();
        e->save(entities);

        QSharedPointer<Pupil> pupil1 = QSharedPointer<Pupil>(new Pupil("Vorname1","Nachname1","","","Keks1"));
        QSharedPointer<Pupil> pupil2 = QSharedPointer<Pupil>(new Pupil("Vorname2","Nachname2","","","Keks2"));
        QSharedPointer<Group> firstGroup = QSharedPointer<Group>(new Group());
        firstGroup->setName("05c");
        firstGroup->addPerson(pupil1);
        firstGroup->addPerson(pupil2);



        e->save(QList<QSharedPointer<Entity>>()<<pupil1<<pupil2<<firstGroup);

        QSharedPointer<Occasion> occasion = QSharedPointer<Occasion>(new Occasion(""));
        QSharedPointer<RatingMarkIncident> firstInc = QSharedPointer<RatingMarkIncident>(new RatingMarkIncident());
        firstInc->setAdditionalInfo("addInf");
        firstInc->setBookedAt(QDateTime::currentDateTime());
        firstInc->setBookedFor(QDateTime::currentDateTime());
        firstInc->setOccasion(occasion);
        firstInc->setPupil(pupil1);
        firstInc->setRateable(true);
        auto system = e->findAll<RatingMarkSystem>().first();
        firstInc->setRatingMarkSystem(system);
        firstInc->setSymbol("NB");
        firstInc->setValue(0.0);
        firstInc->setPercentValue(0.0);
        firstInc->setWeight(1.0);
        firstInc->setGroup(firstGroup);
        firstInc->setSignatureNeeded(false);
        firstInc->setLocked(false);

        e->save(firstInc);


// ----------------------------------------------------------------------------------------------------------------------
        auto oldInc = e->findById<RatingMarkIncident>(1);
        e->refresh(oldInc, true);
        e->refresh(oldInc->group());
        e->refresh(oldInc->pupil());
        QSharedPointer<RatingMarkIncident> inc = Stuff::makeTwin(oldInc, QDateTime::currentDateTime());
        if (oldInc) {
            oldInc->setCancelledAt(QDateTime::currentDateTime());
        }
        inc->setCancelledAt(QDateTime());
        QSharedPointer<Pupil> pupil = e->findById<Pupil>(1);
        inc->setLocked(false);
        inc->setBookedAt(QDateTime::currentDateTime());
        inc->setBookedFor(QDateTime::currentDateTime());
        inc->setPupil(pupil);

        auto group = e->findById<Group>(1);
        e->refresh(group,false);
        inc->setGroup(group);
        inc->setSymbol("NB");
        inc->setPercentValue(0.0);
        inc->setValue(0.0);
        inc->setWeight(1.0);
        inc->setRateable(true);
        inc->setSignatureNeeded(false);
        inc->setOccasion(e->findById<Occasion>(1));
        auto rateSys = e->findById<RatingMarkSystem>(1);
        e->refresh(rateSys);
        inc->setRatingMarkSystem(rateSys);


        // ---------------------------------------------------------------------


        bool success;
        success = oldInc.isNull() || e->save(oldInc);
        // only save new version if old version could is successfully cancelled
        if (success) {
            success &= e->save(inc);
            success &= inc->getId() >= 0; // check
        }


    } catch(QString s) {
        qDebug()<<s;
    }
    return 0;
}
