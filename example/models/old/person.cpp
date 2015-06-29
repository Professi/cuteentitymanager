#include "person.h"

QString Person::toString()
{
    return Entity::toString() + " " + this->getFirstName();
}

Person::Person(QObject *parent) : Entity(parent)
{

}

Person::Person(QString firstName,
               QString familyName,
               Gender gender,
               QString customPictureFileName,
               QString namePrefix,
               QString nickName,
               QDate birthday,
               QObject *parent): CuteEntityManager::Entity(parent) {
    setFirstName(firstName);
    setFamilyName(familyName);
    setNamePrefix(namePrefix);
    setNickName(nickName);
    setBirthday(birthday);
    setGender(gender);
    setCustomPictureFileName(customPictureFileName);
}
QString Person::getCustomPictureFileName() const
{
    return customPictureFileName;
}

void Person::setCustomPictureFileName(const QString &value)
{
    customPictureFileName = value;
}

Gender Person::getGender() const
{
    return gender;
}

void Person::setGender(const Gender &value)
{
    gender = value;
}
QDate Person::getBirthday() const
{
    return birthday;
}

void Person::setBirthday(const QDate &value)
{
    birthday = value;
}
QString Person::getNickName() const
{
    return nickName;
}

void Person::setNickName(const QString &value)
{
    nickName = value;
}
QString Person::getNamePrefix() const
{
    return namePrefix;
}

void Person::setNamePrefix(const QString &value)
{
    namePrefix = value;
}
QString Person::getFamilyName() const
{
    return familyName;
}

void Person::setFamilyName(const QString &value)
{
    familyName = value;
}
QString Person::getFirstName() const
{
    return firstName;
}

void Person::setFirstName(const QString &value)
{
    firstName = value;
}







