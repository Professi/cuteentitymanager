#include "models.h"

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
                QString("leader")));
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

QList<QSharedPointer<Group> > Person::getGroups() const {
    return groups;
}

void Person::setGroups(const QList<QSharedPointer<Group> > &value) {
    groups = value;
}

QList<QSharedPointer<Group> > Person::getMaintainedGroups() const {
    return maintainedGroups;
}

void Person::setMaintainedGroups(const QList<QSharedPointer<Group> > &value) {
    maintainedGroups = value;
}

Group::Group() : Entity() {
}

const QHash<QString, CuteEntityManager::Relation> Group::getRelations() const {
    auto hash = QHash<QString, CuteEntityManager::Relation>();
    hash.insert("persons", CuteEntityManager::Relation("persons",
                RelationType::MANY_TO_MANY));
    hash.insert("leader", CuteEntityManager::Relation("leader",
                RelationType::MANY_TO_ONE));
    return hash;
}

QString Group::getName() const {
    return name;
}

void Group::setName(const QString &value) {
    name = value;
}

QSharedPointer<Person> Group::getLeader() const {
    return leader;
}

void Group::setLeader(const QSharedPointer<Person> &value) {
    leader = value;
}

QList<QSharedPointer<Person> > Group::getPersons() const {
    return persons;
}

void Group::setPersons(const QList<QSharedPointer<Person> > &value) {
    persons = value;
}


double Article::getPrice() const
{
    return price;
}

void Article::setPrice(double value)
{
    price = value;
}

QString Article::getName() const
{
    return name;
}

void Article::setName(const QString &value)
{
    name = value;
}

Article::~Article() {

}

Article::Article() {
    this->price = 0.0;
}

Article::Article(double price, QString name) {
    this->price = price;
    this->name = name;
}
