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


using namespace CuteEntityManager;
int main(int argc, char *argv[]) {
    Q_UNUSED(argc) Q_UNUSED(argv);
    EntityInstanceFactory::registerClass<Address>();
    EntityInstanceFactory::registerClass<Contact>();
    EntityInstanceFactory::registerClass<Person>();
    EntityInstanceFactory::registerClass<Pupil>();
    EntityInstanceFactory::registerClass<Group>();
//    EntityInstanceFactory::registerClass<Occasion>();
//    EntityInstanceFactory::registerClass<Incident>();
//    EntityInstanceFactory::registerClass<RatingMarkDefinition>();
//    EntityInstanceFactory::registerClass<RatingMarkIncident>();
//    EntityInstanceFactory::registerClass<RatingMarkSystem>();



    QSharedPointer<CuteEntityManager::EntityManager> e =
        QSharedPointer<CuteEntityManager::EntityManager>(new
                CuteEntityManager::EntityManager("QSQLITE",
                        QDir::currentPath() + "/db.sqlite"));
    qDebug()<<QDir::currentPath();
    QStringList inits = QStringList() << "Address" << "Contact" << "Person" << "Pupil" << "Group";

    // << "Incident" << "Occasion" << "RatingMarkDefinition" << "RatingMarkIncident" << "RatingMarkSystem";
    e->startup("0.1", inits);


//    auto entities = DataCreation::createRatingEntities();
//    e->save(entities);

//    QSharedPointer<Pupil> pupil = QSharedPointer<Pupil>(new Pupil("Vorname","Nachname","","","Keks"));
//    e->save(pupil);

    QSharedPointer<Pupil> pupil = QSharedPointer<Pupil>(new Pupil());
    pupil->setLegalGuardianNote("note");
    try {
    e->save(QList<QSharedPointer<Entity>>()<<pupil);
    } catch(QString s) {
    qDebug()<<s;
    }
//    QSharedPointer<Person> person = QSharedPointer<Person>(new Person("Vorname","Nachname","","","Keks"));
//    e->save(person);

/*

    QSharedPointer<Occasion> occasion = QSharedPointer<Occasion>(new Occasion("IrgendeinAnlass"));
    QSharedPointer<RatingMarkIncident> inc = QSharedPointer<RatingMarkIncident>(new RatingMarkIncident());
    inc->setAdditionalInfo("addInf");
    inc->setBookedAt(QDateTime::currentDateTime());
    inc->setBookedFor(QDateTime::currentDateTime());
    inc->setOccasion(occasion);
//    inc->setPupil(pupil);
    inc->setRateable(true);
//    inc->setRatingMarkSystem(system);
    inc->setSymbol("z");
    inc->setValue(23);

    e->save(inc);


*/
    return 0;
}
