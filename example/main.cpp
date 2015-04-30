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
#include "entity.h"
#include "entitymanager.h"
#include <QGenericReturnArgument>
/**
  * create,remove und merge funktionieren
 */

int main(int argc, char *argv[]) {
    CuteEntityManager::EntityManager *e = new CuteEntityManager::EntityManager("QSQLITE",
            QDir::currentPath() + "/db.sqlite");
    QSharedPointer<Artikel> a = QSharedPointer<Artikel>(new Artikel(20.0, "Müsli"));
    auto ep = a.dynamicCast<CuteEntityManager::Entity>();
    qDebug() << e;
    qDebug() << "Tabelle artikel erstellt:" << e->createTable(ep);
    e->create(ep);

    QSharedPointer<Person> p = QSharedPointer<Person>(new Person("Max", "Mustermann", Person::MALE, "", "", "",
                               QDate::currentDate()));
    auto pptr = p.dynamicCast<CuteEntityManager::Entity>();
    e->createTable(pptr);
    e->create(pptr);

    QSharedPointer<Group> grp = QSharedPointer<Group>(new Group());
    e->createTable(grp.dynamicCast<CuteEntityManager::Entity>());
    grp.data()->setTeacher(new Person("Test", "Test12345"));
    grp.data()->setTeacherP(QSharedPointer<Person>(new Person("Max", "Mustermann")));
    return 0;
}
