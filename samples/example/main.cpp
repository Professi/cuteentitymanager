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
    EntityInstanceFactory::registerClass<Group>();
    EntityInstanceFactory::registerClass<Person>();
    EntityInstanceFactory::registerClass<Pupil>();
    EntityInstanceFactory::registerClass<Contact>();
    EntityInstanceFactory::registerClass<Address>();
    QThread *entityManager = new QThread();
    e->moveToThread(entityManager);
    QStringList inits = QStringList() << "Contact" << "Address" << "Person" <<
                        "Pupil" << "Group";
    e->startup("0.1", inits);

    QSharedPointer<CuteEntityManager::Entity> p =
        QSharedPointer<CuteEntityManager::Entity>(new Person("Max", "Mustermann",
                Person::Gender::MALE, "", "", "",
                QDate::currentDate()));
    /** ---------------------------------
     * PERSIST
     * ---------------------------------
     */
    Group *g = new Group();
    g->setName("9b");
    CreateFakeModelData::fillGroup(g);
    QSharedPointer<Group> gPtr = QSharedPointer<Group>(g);
    e->createTable(gPtr);
    QSharedPointer<Entity> groupPtr = gPtr.objectCast<Entity>();
    QSharedPointer<Person> mainTeacher = QSharedPointer<Person>(new Person("Max",
                                         "Mustermann", Person::Gender::MALE));
    gPtr->setMainTeacher(mainTeacher);
    //Persons will also persisted
    e->create(groupPtr, true, true);

    /** ---------------------------------
     * FIND
     * ---------------------------------
     */
    QSharedPointer<Entity> groupFindPtr = e->findById<Group *>(1);
    QSharedPointer<Group> grp = groupFindPtr.objectCast<Group>();
    qDebug()<< "Group:" << groupFindPtr->toString();
    qDebug() << "PersonSize:" << grp->getPersons().size();
    qDebug() << "MainTeacher:" << grp->getMainTeacher()->toString();
    qDebug() << "Duration:" << t.elapsed();
    return 0;
}
