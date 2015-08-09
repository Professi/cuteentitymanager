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
#include "querybuilder.h"
#include "orderby.h"
#include "sqlitebackupprocessor.h"

using namespace CuteEntityManager;
int main(int argc, char *argv[]) {
    Q_UNUSED(argc) Q_UNUSED(argv)
    QTime t;
    t.start();

    CuteEntityManager::EntityManager *e = new
//    CuteEntityManager::EntityManager("QSQLITE",
//                                     QDir::currentPath() + "/db.sqlite", "", "", "", 0, true);
    CuteEntityManager::EntityManager("QSQLITE",
                                     ":memory:", "", "", "", "", true, "foreign_keys = ON");
    SqliteBackupProcessor *sqliteproc = new SqliteBackupProcessor(e->getDb(),
            QDir::currentPath());
    qWarning() << "DB Loaded:" << sqliteproc->sqliteDBMemFile(false, "db.sqlite");
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
    qWarning() << "-----------------------------";
    qWarning() << "Create Contact, Address, Pupil and Group Tables";
    qWarning() << "-----------------------------";
    QStringList inits = QStringList() << "Contact" << "Address" <<
                        "Pupil" << "Group";
    /**
      * Instead of startup(version,qstringlist) you can call method createTable of EntityManager (e->create(sharedptr))
      * startup will create tables inclusive relation tables for classes in QStringList inits
      */
    qWarning() << "Tables created or already set up:" << e->startup("0.1", inits,
               true);
    QSharedPointer<CuteEntityManager::Entity> p =
        QSharedPointer<CuteEntityManager::Entity>(new Person("Max", "Mustermann",
                Person::Gender::MALE, "", "", "",
                QDate::currentDate()));
    qWarning() << "-----------------------------";
    qWarning() << "Persist Group with Relations";
    qWarning() << "-----------------------------";
    QSharedPointer<Group> gPtr = QSharedPointer<Group>(new Group());
    CreateFakeModelData::fillGroup(gPtr.data());
    gPtr->setName("9b");
    QSharedPointer<Entity> groupPtr = gPtr.objectCast<Entity>();
    QSharedPointer<Person> mainTeacher = QSharedPointer<Person>(new Person("Max",
                                         "Mustermann", Person::Gender::MALE));
    gPtr->setMainTeacher(mainTeacher);
    //Persons will also persisted
    if (e->count(groupPtr->getTablename()) <= 0) {
        e->create(groupPtr, true, true);
    }
    qWarning() << "-----------------------------";
    qWarning() << "Find All Groups";
    qWarning() << "-----------------------------";
    QList<QSharedPointer<Group>> groups = e->findAll<Group>();
    QSharedPointer<Group> groupFindPtr = groups.at(0);
    qWarning() << "Group:" << groupFindPtr->toString();
    qWarning() << "MainTeacher:" << groupFindPtr->getMainTeacher()->toString();

    qWarning() << "-----------------------------";
    qWarning() << "Find Person By Id Version 1";
    qWarning() << "-----------------------------";

    QSharedPointer<Entity> personFindPtr = e->findById(1, QString("Person"));
    qDebug() << "HASCHANGED:" << e->hasChanged(personFindPtr);
    e->refresh(personFindPtr);
    QSharedPointer<Person> pers = personFindPtr.objectCast<Person>();
    qWarning() << "MainTeacher:" << personFindPtr->toString();
    qWarning() << "-----------------------------";
    qWarning() << "Find Person By Id Version 2";
    qWarning() << "-----------------------------";

    QSharedPointer<Person> foundMainTeacher = e->findById<Person>(1);
    qWarning() << "FoundMainTeacher:" << foundMainTeacher->toString();

    qWarning() << "-----------------------------";
    qWarning() << "Find Pupil with Query Class";
    qWarning() << "-----------------------------";

    Query q = Query();
    q.appendWhere(e->getQueryBuilder()->like(QString("firstname"), QString("Tim"),
                  JokerPosition::BEHIND));
    q.appendWhere(e->getQueryBuilder()->andOperator());
    q.appendWhere(e->getQueryBuilder()->arbitraryOperator("<", "birthday",
                  QDate(2000, 10, 10)));
    //q.appendJoin(Join("person", "pupil.id = person.id"));
    q.setDistinct(true);
    q.appendOrderBy(OrderBy(QString("birthday"), Direction::SORT_DESC));
    q.setLimit(10);
    QList<QSharedPointer<Pupil>> list = e->find<Pupil>(q, true);
    for (int i = 0; i < list.size(); ++i) {
//        qWarning() << "-----------------------------";
//        qWarning() << "Merge Pupil";
//        qWarning() << "-----------------------------";
//        list.at(i)->setBirthday(QDate(2222,12,22));
//        QSharedPointer<Entity> pupilE = list.at(i).objectCast<Entity>();
//        e->merge(pupilE,true);
        qWarning() << list.at(i)->toString();
    }
    qWarning() << "-----------------------------";
    qWarning() << "Find Pupil by Attributes";
    qWarning() << "-----------------------------";

    QHash<QString, QVariant> attributes;
    attributes["familyName"] = QString("Dunst");
    QSharedPointer<Pupil> pupil = e->findEntityByAttributes<Pupil>
                                  (attributes, true);
    qWarning() << pupil->toString();
    qWarning() << "-----------------------------";
    qWarning() << "Merge Group";
    qWarning() << "-----------------------------";
    groupFindPtr->setName("10b");
    qWarning() << groupFindPtr->toString();
    QSharedPointer<Entity> entityGroupFindPtr = groupFindPtr.objectCast<Entity>();
    e->save(entityGroupFindPtr, false);

    qWarning() << "-----------------------------";
    qWarning() << "Remove Group";
    qWarning() << "-----------------------------";
    e->remove(entityGroupFindPtr);




    sqliteproc->sqliteDBMemFile(true, "db.sqlite");
    qWarning() << "Duration:" << t.elapsed();
    delete sqliteproc;
    return 0;
}
