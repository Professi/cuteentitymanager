#include <QCoreApplication>
#include <typeinfo>
#include <QDir>
#include <QDebug>
#include "models/artikel.h"
#include "models/person.h"
#include <typeinfo>
#include <QMetaMethod>
#include <QMetaProperty>
#include "models/group.h"
#include "../src/entity.h"
#include "../src/entitymanager.h"
#include "../src/relation.h"
#include <QGenericReturnArgument>
#include "entityinstancefactory.h"
/**
  * create,remove und merge funktionieren
 */
using namespace CuteEntityManager;
int main(int argc, char *argv[]) {
//    Q_UNUSED(argc) Q_UNUSED(argv)
//    CuteEntityManager::EntityManager *e = new CuteEntityManager::EntityManager("QSQLITE",
//            QDir::currentPath() + "/db.sqlite");
//    QSharedPointer<Artikel> a = QSharedPointer<Artikel>(new Artikel(20.0, "Müsli"));
//    auto ep = a.dynamicCast<CuteEntityManager::Entity>();
//    qDebug() << e;
//    qDebug() << "Tabelle artikel erstellt:" << e->createTable(ep);
//    e->create(ep);

//    QSharedPointer<CuteEntityManager::Entity> p = QSharedPointer<CuteEntityManager::Entity>(new Person("Max", "Mustermann", Person::MALE, "", "", "",
//                               QDate::currentDate()));
//    auto pptr = p.dynamicCast<CuteEntityManager::Entity>();
//    e->createTable(pptr);
//    e->create(pptr);
//e->createTable(grp.dynamicCast<CuteEntityManager::Entity>());

    QSharedPointer<Group> grp = QSharedPointer<Group>(new Group());

    grp.data()->setTeacher(new Person("Test", "Test12345"));
    grp.data()->setTeacherP(QSharedPointer<Person>(new Person("Max", "Mustermann")));
    auto meta = grp.data()->getRelationProperties();
    auto iterator = meta.constBegin();
    while(iterator != meta.constEnd()) {
        qDebug() << EntityInstanceFactory::extractEntityType(iterator.value().typeName());
        //qDebug() << e.Type;
        ++iterator;
    }

    return 0;
}
