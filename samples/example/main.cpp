#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QThread>
#include "../src/entity.h"
#include "../src/entitymanager.h"
#include "../src/relation.h"
#include "entityinstancefactory.h"
#include "models/pupil.h"
#include "models/address.h"
#include "models/contact.h"
#include "models/group.h"
#include "models/faker/createfakemodeldata.h"

using namespace CuteEntityManager;
int main(int argc, char *argv[]) {
    Q_UNUSED(argc) Q_UNUSED(argv)
    QTime t;
    t.start();
    CuteEntityManager::EntityManager *e = new
    CuteEntityManager::EntityManager("QSQLITE",
                                     QDir::currentPath() + "/db.sqlite");
//            CuteEntityManager::EntityManager("QSQLITE",
//                                                 ":memory:");

    /**
     * @brief EntityInstanceFactory::registerClass<EntityClass>
     * You must register every EntityClass, cause Qt is not creating all meta object informations for entity manager
     */
    EntityInstanceFactory::registerClass<Group>();
    EntityInstanceFactory::registerClass<Person>();
    EntityInstanceFactory::registerClass<Pupil>();
    EntityInstanceFactory::registerClass<Contact>();
    EntityInstanceFactory::registerClass<Address>();
    QThread *entityManager = new QThread();
    e->moveToThread(entityManager);
    QStringList inits = QStringList() << "Contact" << "Address" <<
                        "Pupil" << "Group";
    /**
      * Instead of startup(version,qstringlist) you can call method createTable of EntityManager (e->create(sharedptr))
      * startup will create tables inclusive relation tables for classes in QStringList inits
      */
    e->startup("0.1", inits);

    QSharedPointer<CuteEntityManager::Entity> p =
        QSharedPointer<CuteEntityManager::Entity>(new Person("Max", "Mustermann",
                Person::Gender::MALE, "", "", "",
                QDate::currentDate()));
    /** ---------------------------------
     * PERSIST
     * ---------------------------------
     */

    QSharedPointer<Group> gPtr = QSharedPointer<Group>(new Group());
    CreateFakeModelData::fillGroup(gPtr.data());
    gPtr->setName("9b");
    QSharedPointer<Entity> groupPtr = gPtr.objectCast<Entity>();
    QSharedPointer<Person> mainTeacher = QSharedPointer<Person>(new Person("Max",
                                         "Mustermann", Person::Gender::MALE));
    gPtr->setMainTeacher(mainTeacher);
    //Persons will also persisted
    //e->create(groupPtr, true, true);

    /** ---------------------------------
     * FIND Group
     * ---------------------------------
     */
qDebug() << "-----------------------------";
    QSharedPointer<Entity> groupFindPtr = e->findById<Group *>(1);
    QSharedPointer<Group> grp = groupFindPtr.objectCast<Group>();
    qDebug() << "Group:" << groupFindPtr->toString();
    qDebug() << "PersonSize:" << grp->getPersons().size();
    qDebug() << "PupilsSize:" << grp->getPupils().size();
    qDebug() << "MainTeacher:" << grp->getMainTeacher()->toString();

    /** ---------------------------------
     * FIND Person
     * ---------------------------------
     */
    qDebug() << "-----------------------------";
    QSharedPointer<Entity> personFindPtr = e->findById(1, QString("Person*"));
    e->refresh(personFindPtr);
    QSharedPointer<Person> pers = personFindPtr.objectCast<Person>();
    qDebug() << "MainTeacher:" << personFindPtr->toString();
    qDebug() << "MaintainedGroupSize:" << pers->getMaintainedGroups().size();
    qDebug() << "GroupSize:" << pers->getGroups().size();

    /**
     * or you can use following syntax:
     */
    qDebug() << "-----------------------------";
    QSharedPointer<Person> foundMainTeacher = e->findById<Person *>
            (1).objectCast<Person>();
    qDebug() << "FoundMainTeacher:" << foundMainTeacher->toString();
    qDebug() << "FoundMainTeacherGroupSize:" <<
             foundMainTeacher->getMaintainedGroups().size();

    qDebug() << "-----------------------------";
    QSharedPointer<Pupil> foundPupil = e->findById<Pupil *>
            (20).objectCast<Pupil>();
    qDebug() << "FoundPupil:" << foundPupil->toString();
    qDebug() << "FoundPupilGroupSize:" <<
             foundPupil->getGroups().size();

    qDebug() << "-----------------------------";

    qDebug() << "Duration:" << t.elapsed();

    return 0;
}
