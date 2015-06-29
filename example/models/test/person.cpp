#include "person.h"

Person::Person(QObject *parent): Entity(parent)
{
}
Person::Person(QString firstName,
                QString familyName,
                Gender gender,
                QString customPictureFileName,
                QString namePrefix,
                QString nickName,
                QDate birthday,
                QObject *parent):Entity(parent)
{
    setFirstName(firstName);
    setFamilyName(familyName);
    setNamePrefix(namePrefix);
    setNickName(nickName);
    setBirthday(birthday);
    setGender(gender);
    setCustomPictureFileName(customPictureFileName);
}

const QHash<QString, CuteEntityManager::Relation> Person::getRelations() const
{
    auto hash = QHash<QString, CuteEntityManager::Relation>();
    hash.insert("groups",CuteEntityManager::Relation("groups",MANY_TO_MANY,QString("persons")));
    return hash;
}

QString Person::fullName(NameOrder nameOrder) const {
    QString name=QString();
    if (nameOrder==FAMILY_FIRST_NAME_ORDER) {
        name+=this->familyName();
        name+=", ";
        if (!this->namePrefix().isEmpty()) {
            name+=this->namePrefix();
            name+=" ";
        }
        name+=this->firstName();
    } else {
        name+=this->firstName();
        name+=" ";
        name+=this->familyName();
        if (!this->namePrefix().isEmpty()) {
            name+=", ";
            name+=this->namePrefix();
        }
    }
    return name;
}
QList<QSharedPointer<Group> > Person::groups() const
{
    return m_groups;
}

void Person::setGroups(const QList<QSharedPointer<Group> > &groups)
{
    m_groups = groups;
}
QList<QSharedPointer<Address> > Person::addresses() const
{
    return m_addresses;
}

void Person::setAddresses(const QList<QSharedPointer<Address> > &addresses)
{
    m_addresses = addresses;
}
QList<QSharedPointer<Contact> > Person::contacts() const
{
    return m_contacts;
}

void Person::setContacts(const QList<QSharedPointer<Contact> > &contacts)
{
    m_contacts = contacts;
}




