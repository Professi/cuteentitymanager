#include "contact.h"
#include "pupil.h"

Contact::Contact(QString label, Category category, QString content) {
    this->label = label;
    this->category = category;
    this->content = content;
}

const QHash<QString, CuteEntityManager::Relation> Contact::getRelations()
const {
    auto hash = Entity::getRelations();
//    hash.insert("persons", CuteEntityManager::Relation("persons",
//                RelationType::MANY_TO_MANY,
//                QString("contacts")));
    hash.insert("pupils", CuteEntityManager::Relation("pupils",
                RelationType::MANY_TO_MANY,
                QString("contacts")));
    return hash;
}

QString Contact::getContent() const {
    return content;
}

void Contact::setContent(const QString &value) {
    content = value;
}

QString Contact::getLabel() const {
    return label;
}

void Contact::setLabel(const QString &value) {
    label = value;
}
Contact::Category Contact::getCategory() const {
    return category;
}

void Contact::setCategory(const Category &value) {
    category = value;
}

QList<QSharedPointer<Person> > Contact::getPersons() const {
    return persons;
}

void Contact::setPersons(const QList<QSharedPointer<Person> > &value) {
    persons = value;
}

QList<QSharedPointer<Pupil> > Contact::getPupils() const {
    return pupils;
}

void Contact::setPupils(const QList<QSharedPointer<Pupil> > &value) {
    pupils = value;
}
