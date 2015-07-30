#include "person.h"
#include "contact.h"
#include "address.h"

Person::Person(QObject *parent): Entity(parent) {
}
Person::Person(QString firstName, QString familyName, Gender gender,
               QString customPictureFileName, QString namePrefix, QString nickName,
               QDate birthday, QObject *parent): Entity(parent) {
    setFirstName(firstName);
    setFamilyName(familyName);
    setNamePrefix(namePrefix);
    setNickName(nickName);
    setBirthday(birthday);
    setGender(gender);
    setCustomPictureFileName(customPictureFileName);
}

const QHash<QString, CuteEntityManager::Relation> Person::getRelations() const {
    auto hash = QHash<QString, CuteEntityManager::Relation>();
    hash.insert("groups", CuteEntityManager::Relation("groups",
                RelationType::MANY_TO_MANY,
                QString("persons")));
    hash.insert("maintainedGroups", CuteEntityManager::Relation("maintainedGroups",
                RelationType::ONE_TO_MANY,
                QString("mainTeacher")));
    hash.insert("contacts", CuteEntityManager::Relation("contacts",
                RelationType::MANY_TO_MANY));
    hash.insert("addresses", CuteEntityManager::Relation("addresses",
                RelationType::MANY_TO_MANY));
    return hash;
}

QString Person::fullName(NameOrder nameOrder) const {
    QString name = QString();
    if (nameOrder == NameOrder::FAMILY_FIRST_NAME_ORDER) {
        name += this->getFamilyName();
        name += ", ";
        if (!this->getNamePrefix().isEmpty()) {
            name += this->getNamePrefix();
            name += " ";
        }
        name += this->getFirstName();
    } else {
        name += this->getFirstName();
        name += " ";
        name += this->getFamilyName();
        if (!this->getNamePrefix().isEmpty()) {
            name += ", ";
            name += this->getNamePrefix();
        }
    }
    return name;
}
QString Person::getFirstName() const {
    return firstName;
}

void Person::setFirstName(const QString &value) {
    firstName = value;
}
QString Person::getFamilyName() const {
    return familyName;
}

void Person::setFamilyName(const QString &value) {
    familyName = value;
}
QString Person::getNamePrefix() const {
    return namePrefix;
}

void Person::setNamePrefix(const QString &value) {
    namePrefix = value;
}
QString Person::getNickName() const {
    return nickName;
}

void Person::setNickName(const QString &value) {
    nickName = value;
}
QDate Person::getBirthday() const {
    return birthday;
}

void Person::setBirthday(const QDate &value) {
    birthday = value;
}
Person::Gender Person::getGender() const {
    return gender;
}

void Person::setGender(const Gender &value) {
    gender = value;
}
QString Person::getCustomPictureFileName() const {
    return customPictureFileName;
}

void Person::setCustomPictureFileName(const QString &value) {
    customPictureFileName = value;
}
QList<QSharedPointer<Contact> > Person::getContacts() const {
    return contacts;
}

void Person::setContacts(const QList<QSharedPointer<Contact> > &value) {
    contacts = value;
}
QList<QSharedPointer<Address> > Person::getAddresses() const {
    return addresses;
}

void Person::setAddresses(const QList<QSharedPointer<Address> > &value) {
    addresses = value;
}
QList<QSharedPointer<Group> > Person::getGroups() const {
    return groups;
}

void Person::setGroups(const QList<QSharedPointer<Group> > &value) {
    groups = value;
}

void Person::addContact(Contact *contact) {
    this->contacts.append(QSharedPointer<Contact>(contact));
}

void Person::addAddress(Address *address) {
    this->addresses.append(QSharedPointer<Address>(address));
}

QList<QSharedPointer<Group> > Person::getMaintainedGroups() const {
    return maintainedGroups;
}

void Person::setMaintainedGroups(const QList<QSharedPointer<Group> > &value) {
    maintainedGroups = value;

}

