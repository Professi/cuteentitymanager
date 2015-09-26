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
    EntityInstanceFactory::registerClass<Person>();
    EntityInstanceFactory::registerClass<Address>();
    CuteEntityManager::EntityManager *e = new
    CuteEntityManager::EntityManager("QSQLITE", QDir::currentPath() + "/db.sqlite");

    e->createTable("Person");
    e->createTable("Address");
    /**
     * You can define the following validators:
     * "compare" -> CompareValidator  (Params: ==, !=, <,>,<=,>=)
     * "default" -> DefaultValidator You must only provide a value. Param name can be empty.
     * "email" -> EmailValidator You can provide "full" param.
     *      It would check "Max Example<max.example@synlos.net>".
     *      Without this param it checks for "max.example@synlos.net"
     * "exists" -> ExistValidator Checks if a MANY_TO_ONE/ONE_TO_ONE Relation Entity already has a ID
     * "file" -> FileValidator (Params: mimeTypes, extensions, minSize, maxSize)
     * "image" -> ImageValidator !Only Available when the EM was compiled with QT += gui
     *      (Params: minWidth, maxWidth, minHeight, maxHeight)
     * "number" -> NumberValidator (Params: min, max)
     * "date" -> DateValidator (Params: future, past, min, max)
     * "required" -> RequiredValidator If specified it checks if a QVariant is null or a QString is empty
     * "unique" -> UniqueValidator - Not done, checks if a value was already used
     * "url" -> UrlValidator (Params: defaultSchemes) Checks for a valid URL(https://... or http://...)
     * "pattern" -> PatternValidator You can define a param Name, but you only need to provide a Param value with the Pattern for the regular expression
     * "length"-> LengthValidator (Params: min, max)
     *
     * You must override virtual QList<ValidationRule> validationRules() const; of Entity Class
     * You can define a ValidationRule for example with:
     * ValidationRule("length", {"firstName", "familyName"}, "min", 2);
     * First is everytime the shortcut of the specific validator
     * Second must be a single attribute or a list of attributes
     * Then you can specify the params with values.
     */

    QSharedPointer<Entity> p1 = QSharedPointer<Person>(new Person("Thomas", "B",
                                Person::Gender::MALE, "", QString(), QString(), QDate(), 0));
    QSharedPointer<Entity> p2 = QSharedPointer<Person>(new Person("Teresa",
                                "Conrad",
                                Person::Gender::FEMALE, "", QString(), QString(), QDate(2016, 7, 13), 0));
    QSharedPointer<Entity> p3 = QSharedPointer<Person>(new Person("Heinz", "Dunst",
                                Person::Gender::MALE, "", QString(), QString(), QDate(1972, 7, 13), 0));

    //validation takes also place before save/create/merge
    qDebug() << "p1 valid:" << e->validate(p1);
    qDebug() << p1->getErrorsAsString();
    qDebug() << "p2 valid:" << e->validate(p2);
    qDebug() << p2->getErrorsAsString();
    qDebug() << "p3 valid:" << e->validate(p3);
    qDebug() << p3->getErrorsAsString();
    QSharedPointer<Entity> a1 = QSharedPointer<Address>(new Address("",
                                "Mentzelstraße 327",
                                "33617", "Bielefeld"));
    QSharedPointer<Entity> a2 = QSharedPointer<Address>(new Address("Erzieher",
                                "Bundesallee 252",
                                "4908", "Osnabrück"));
    qDebug() << "a1 valid:" << e->validate(a1);
    qDebug() << a1->getErrorsAsString();
    qDebug() << "a2 valid:" << e->validate(a2);
    qDebug() << a2->getErrorsAsString();

    return 0;
}
