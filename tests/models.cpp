#include "models.h"

Person::Person(QObject *parent): Entity(parent) {
}

Person::Person(QString firstName, QString familyName, Gender gender,
               QString nickName,
               QDate birthday, QObject *parent): Entity(parent) {
    setFirstName(firstName);
    setFamilyName(familyName);
    setNickName(nickName);
    setBirthday(birthday);
    setGender(gender);
}

const QHash<QString, CuteEntityManager::Relation> Person::getRelations() const {
    auto hash = QHash<QString, CuteEntityManager::Relation>();
    hash.insert("groups", CuteEntityManager::Relation("groups",
                RelationType::MANY_TO_MANY));
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
        name += this->getFirstName();
    } else {
        name += this->getFirstName();
        name += " ";
        name += this->getFamilyName();
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

QList<QSharedPointer<Group>> Person::getGroups() const {
    return groups;
}

void Person::setGroups(const QList<QSharedPointer<Group>> &value) {
    groups = value;
}

QList<QSharedPointer<Group>> Person::getMaintainedGroups() const {
    return maintainedGroups;
}

void Person::setMaintainedGroups(const QList<QSharedPointer<Group>> &value) {
    maintainedGroups = value;
}

Group::Group() : Entity() {
}

const QHash<QString, CuteEntityManager::Relation> Group::getRelations() const {
    auto hash = QHash<QString, CuteEntityManager::Relation>();
    hash.insert("persons", CuteEntityManager::Relation("persons",
                RelationType::MANY_TO_MANY, QString("groups")));
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

QList<QSharedPointer<Person>> Group::getPersons() const {
    return persons;
}

void Group::addPerson(const QSharedPointer<Person> &value) {
    this->persons.append(value);
}

void Group::setPersons(const QList<QSharedPointer<Person>> &value) {
    persons = value;
}

void Group::removePerson(const QSharedPointer<Person> &value) {
    this->persons.removeOne(value);
}


double Article::getPrice() const {
    return price;
}

void Article::setPrice(double value) {
    price = value;
}

QString Article::getName() const {
    return name;
}

void Article::setName(const QString &value) {
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

QList<CuteEntityManager::ValidationRule> Person::validationRules() const {
    QList<CuteEntityManager::ValidationRule> rules =
        QList<CuteEntityManager::ValidationRule>();
    rules.append(ValidationRule("length", {"firstName", "familyName"}, "min", 2));
    QList<Param> params = {Param("past"), Param("min", QDate(1970, 1, 1))};
    rules.append(ValidationRule("date", "birthday", params));
    return rules;
}

const QHash<QString, CuteEntityManager::Relation> Employee::getRelations() const {
    auto relations = Person::getRelations();
    return relations;
}

QString Employee::getDepartment() const {
    return department;
}

void Employee::setDepartment(const QString &value) {
    department = value;
}

bool Employee::isManager() const {
    return manager;
}

void Employee::setManager(bool value) {
    manager = value;
}

quint64 Employee::getPersNumber() const {
    return persNumber;
}

void Employee::setPersNumber(const quint64 &value) {
    persNumber = value;
}

const QHash<QString, CuteEntityManager::Relation> WorkerGroup::getRelations() const {
    auto hash = QHash<QString, CuteEntityManager::Relation>();
    hash.insert("workers", CuteEntityManager::Relation("workers",
                RelationType::MANY_TO_MANY));
    return hash;
}

QString WorkerGroup::getName() const {
    return name;
}

void WorkerGroup::setName(const QString &value) {
    name = value;
}

quint32 WorkerGroup::getEfficiency() const {
    return efficiency;
}

void WorkerGroup::setEfficiency(const quint32 &value) {
    efficiency = value;
}

bool WorkerGroup::isActive() const {
    return active;
}

void WorkerGroup::setActive(bool value) {
    active = value;
}

QList<QSharedPointer<Employee>> WorkerGroup::getWorkers() const {
    return workers;
}

void WorkerGroup::setWorkers(const QList<QSharedPointer<Employee>> &value) {
    workers = value;
}

void WorkerGroup::addWorker(const QSharedPointer<Employee> &value) {
    this->workers.append(value);
}
