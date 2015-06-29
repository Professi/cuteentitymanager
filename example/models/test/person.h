#ifndef PERSON_H
#define PERSON_H

#include <QDateTime>
#include <QString>
#include <QList>
#include <QObject>
#include "group.h"
#include "contact.h"
#include "address.h"
#include <QAbstractListModel>
#include <QDebug>
#include "../../entitymanager/src/entity.h"

using namespace CuteEntityManager;
class Group;
class Person: public Entity
{

    Q_OBJECT
    Q_ENUMS(Gender)

    //[1] We don't want the id to be set from QML
    //[2] Notification via inherited signals is not allowed
//    Q_PROPERTY(int personId READ entityId /*[1]WRITE setId [2]NOTIFY idChanged*/)
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY firstNameChanged)
    Q_PROPERTY(QString familyName READ familyName WRITE setFamilyName NOTIFY familyNameChanged)
    Q_PROPERTY(QString namePrefix READ namePrefix WRITE setNamePrefix NOTIFY namePrefixChanged)
    Q_PROPERTY(QString nickName READ nickName WRITE setNickName NOTIFY nickNameChanged)
    Q_PROPERTY(QString customPictureFileName READ customPictureFileName WRITE setCustomPictureFileName NOTIFY customPictureFileNameChanged)
    Q_PROPERTY(QDate birthday READ birthday WRITE setBirthday NOTIFY birthdayChanged)
    Q_PROPERTY(Gender gender READ gender WRITE setGender NOTIFY genderChanged)
    Q_PROPERTY(QList<QSharedPointer<Group>> groups READ groups WRITE setGroups)



signals:
    void firstNameChanged();
    void familyNameChanged();
    void namePrefixChanged();
    void nickNameChanged();
    void birthdayChanged();
    void genderChanged();
    void customPictureFileNameChanged();
    void formChanged();

public slots:
    void testSlot(){qDebug()<<"testslot clicked";}

public:
    enum Gender {MALE,FEMALE,UNKNOWNGENDER};

    Q_INVOKABLE explicit Person(QObject *parent = 0);
    Person(QString firstName,
           QString familyName,
           Gender gender = Person::UNKNOWNGENDER,
           QString customPictureFileName = QString(),
           QString namePrefix = QString(),
           QString nickName = QString(),
           QDate birthday = QDate(),
           QObject *parent = 0);

    virtual const QHash<QString, CuteEntityManager::Relation> getRelations() const;

    bool isPresent(QDateTime date=QDateTime::currentDateTime());
    QString fullName(NameOrder nameOrder=FAMILY_FIRST_NAME_ORDER) const;

    // getters
    QString firstName() const {return m_firstName;}
    QString familyName() const {return m_familyName;}
    QString namePrefix() const {return m_namePrefix;}
    QString nickName() const {return m_nickName;}

    QDate birthday() const {return m_birthday;}
    Gender gender() const {return m_gender;}
    QString customPictureFileName() const {return m_customPictureFileName;}


    // setters
    void setFirstName(QString firstName) {m_firstName=firstName; emit firstNameChanged();}
    void setFamilyName(QString familyName) {m_familyName=familyName; emit familyNameChanged();}
    void setNamePrefix(QString namePrefix) {m_namePrefix=namePrefix; emit namePrefixChanged();}
    void setNickName(QString nickName) {m_nickName=nickName; emit nickNameChanged();}
    void addGroup(Group *group) {m_groups.append(QSharedPointer<Group>(group));}
    //void removeGroup(Group *group) {m_groups.removeOne(group);}
    void setBirthday(QDate birthday) {m_birthday=birthday; emit birthdayChanged();}
    void setGender(Gender gender) {m_gender=gender; emit genderChanged();}
    void setCustomPictureFileName(QString fileName) {m_customPictureFileName=fileName; emit customPictureFileNameChanged();}
    void addContact(Contact* contact) {m_contacts.append(QSharedPointer<Contact>(contact));}
    //void removeContact(Contact* contact) {m_contacts.removeOne(contact);}
    void addAddress(Address* address) {m_addresses.append(QSharedPointer<Address>(address));}
    //void removeAddress(Address* address) {m_addresses.removeOne(address);}



    QList<QSharedPointer<Group> > groups() const;
    void setGroups(const QList<QSharedPointer<Group> > &groups);

    QList<QSharedPointer<Address> > addresses() const;
    void setAddresses(const QList<QSharedPointer<Address> > &addresses);

    QList<QSharedPointer<Contact> > contacts() const;
    void setContacts(const QList<QSharedPointer<Contact> > &contacts);

protected:
    // members
    QString m_firstName;
    QString m_familyName;
    QString m_namePrefix;
    QString m_nickName;
    QDate m_birthday;
    Gender m_gender;
    QString m_customPictureFileName;
    QList <QSharedPointer<Contact>> m_contacts;
    QList <QSharedPointer<Address>> m_addresses;

    QList<QSharedPointer<Group>> m_groups;



};


#endif // PERSON_H
