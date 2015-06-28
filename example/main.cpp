#include <QCoreApplication>
#include <typeinfo>
#include <QDir>
#include <QDebug>
#include "models/artikel.h"
#include "models/person.h"
#include <typeinfo>
#include <QThread>
#include <QMetaMethod>
#include <QMetaProperty>
#include "models/group.h"
#include "../src/entity.h"
#include "../src/entitymanager.h"
#include "../src/relation.h"
#include <QGenericReturnArgument>
#include "entityinstancefactory.h"
#include <exception>
#include "models/pupil.h"
/**
  * create,remove und merge funktionieren
 */
using namespace CuteEntityManager;
int main(int argc, char *argv[]) {
    Q_UNUSED(argc) Q_UNUSED(argv)
    CuteEntityManager::EntityManager *e = new
    CuteEntityManager::EntityManager("QSQLITE",
                                     QDir::currentPath() + "/db.sqlite");
    QTime t;
    t.start();
    QThread *entityManager = new QThread();
    e->moveToThread(entityManager);
    QSharedPointer<Artikel> a = QSharedPointer<Artikel>(new Artikel(20.0,
                                "Müsli"));
    auto ep = a.dynamicCast<CuteEntityManager::Entity>();
    qDebug() << "Tabelle artikel erstellt:" << e->createTable(ep);
    e->create(ep);
    qDebug() << "TEST12345678990";
    auto artikel = e->findById<Artikel *>(1);
    qDebug() << "ArtikelID:" << artikel.data()->getId();
//    QSharedPointer<CuteEntityManager::Entity> p = QSharedPointer<CuteEntityManager::Entity>(new Person("Max", "Mustermann", Person::MALE, "", "", "",
//                               QDate::currentDate()));
//    auto pptr = p.dynamicCast<CuteEntityManager::Entity>();
//    e->createTable(pptr);
//    e->create(pptr);
//e->createTable(grp.dynamicCast<CuteEntityManager::Entity>());

//    e->createTable(QSharedPointer<Artikel>(new Artikel()));

    //QSharedPointer<Artikel> aPtr = QSharedPointer<Artikel>(entity);
    //Pupil *p = new Pupil();

//    auto iterator = hash.constBegin();
//    while(iterator != hash.constEnd()) {
//        qDebug() << iterator.key() << " Value:" << iterator.value().read(p);
//        iterator++;
//    }
    qDebug() << "Duration:" << t.elapsed();
    return 0;
}
