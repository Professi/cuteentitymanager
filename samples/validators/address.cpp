#include "address.h"
#include "person.h"
Address::Address(QString label, QString street, QString postcode,
                 QString city) {
    this->label = label;
    this->street = street;
    this->postcode = postcode;
    this->city = city;
}

QList<ValidationRule> Address::validationRules() const {
    QList<ValidationRule> rules = QList<ValidationRule>();
    rules.append(ValidationRule("required", {"street", "postcode","label"}));
    //rules.append(ValidationRule("required"));
    return rules;
}

QString Address::getLabel() const {
    return label;
}

void Address::setLabel(const QString &value) {
    label = value;
}

QString Address::getStreet() const {
    return street;
}

void Address::setStreet(const QString &value) {
    street = value;
}

QString Address::getPostcode() const {
    return postcode;
}

void Address::setPostcode(const QString &value) {
    postcode = value;
}

QString Address::getCity() const {
    return city;
}

void Address::setCity(const QString &value) {
    city = value;
}

QList<QSharedPointer<Person> > Address::getPersons() const {
    return persons;
}

void Address::setPersons(const QList<QSharedPointer<Person> > &value) {
    persons = value;
}

const QHash<QString, CuteEntityManager::Relation> Address::getRelations()
const {
    auto hash = Entity::getRelations();
    hash.insert("persons", CuteEntityManager::Relation("persons",
                RelationType::MANY_TO_MANY,
                QString("addresses")));
    return hash;
}


