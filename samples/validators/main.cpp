#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include "person.h"
#include "address.h"
#include "../../src/entitymanager.h"
#include "../../src/entityinstancefactory.h"
/**
  * create,remove und merge funktionieren
 */
using namespace CuteEntityManager;
int main(int argc, char *argv[]) {
    Q_UNUSED(argc) Q_UNUSED(argv)
    CuteEntityManager::EntityManager *e = new
    CuteEntityManager::EntityManager("QSQLITE", QDir::currentPath() + "/db.sqlite");
    EntityInstanceFactory::registerClass<Person>();
    EntityInstanceFactory::registerClass<Address>();
    e->createTable("Person");
    e->createTable("Address");

    QSharedPointer<Entity> p1 = QSharedPointer<Person>(new Person("Thomas", "B",
                                Person::Gender::MALE, "", QString(), QString(), QDate(1971, 7, 13), 0));
    QSharedPointer<Entity>p2 = QSharedPointer<Person>(new Person("Teresa", "Conrad",
                               Person::Gender::FEMALE, "", QString(), QString(), QDate(1970, 7, 13), 0));
    QSharedPointer<Entity> p3 = QSharedPointer<Person>(new Person("Heinz", "Dunst",
                                Person::Gender::MALE, "", QString(), QString(), QDate(1972, 7, 13), 0));

    //validation takes also place before save/create/merge
    qDebug() << "p1 valid:" << e->validate(p1) << p1->getErrorsAsString();
    qDebug() << "p2 valid:" << e->validate(p2) << p2->getErrorsAsString();
    qDebug() << "p3 valid:" << e->validate(p3) << p3->getErrorsAsString();

    QSharedPointer<Entity> a1 = QSharedPointer<Address>(new Address("",
                                "Mentzelstraße 327",
                                "33617", "Bielefeld"));
    QSharedPointer<Entity> a2 = QSharedPointer<Address>(new Address("Erzieher",
                                "Bundesallee 252",
                                "4908", "Osnabrück"));

    qDebug() << "a1 valid:" << e->validate(a1) << a1->getErrorsAsString();
    qDebug() << "a2 valid:" << e->validate(a2) << a2->getErrorsAsString();
qDebug() << a2->getErrors().size();

    return 0;
}
