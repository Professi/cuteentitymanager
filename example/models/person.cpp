#include "person.h"

QString Person::toString()
{
    return Entity::toString() + " " + this->firstName();
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
