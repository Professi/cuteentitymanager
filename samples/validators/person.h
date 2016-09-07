#ifndef PERSON_H
#define PERSON_H

#include <QDateTime>
#include <QString>
#include <QList>
#include <QObject>
#include <QAbstractListModel>
#include <QDebug>
#include "entity.h"

using namespace CuteEntityManager;
class Group;
class Contact;
class Address;

class Person: public Entity {
    Q_OBJECT
    EM_MACRO(Person)
    Q_PROPERTY(QString firstName READ getFirstName WRITE setFirstName)
    Q_PROPERTY(QString familyName READ getFamilyName WRITE setFamilyName)
    Q_PROPERTY(QString namePrefix READ getNamePrefix WRITE setNamePrefix)
    Q_PROPERTY(QString nickName READ getNickName WRITE setNickName)
    Q_PROPERTY(QString customPictureFileName READ getCustomPictureFileName WRITE
               setCustomPictureFileName)
    Q_PROPERTY(QDate birthday READ getBirthday WRITE setBirthday)
    Q_PROPERTY(Gender gender READ getGender WRITE setGender)
    Q_PROPERTY(QList<QSharedPointer<Address>> addresses READ
               getAddresses WRITE setAddresses)

  public:
    enum class Gender {MALE, FEMALE, UNKNOWNGENDER};
    enum class NameOrder {FIRST_FAMILY_NAME_ORDER, FAMILY_FIRST_NAME_ORDER};

#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(Gender)
    Q_ENUM(NameOrder)
#else
    Q_ENUMS(Gender)
    Q_ENUMS(NameOrder)
#endif
    Q_INVOKABLE explicit Person(QObject *parent = 0);
    Person(QString firstName, QString familyName,
           Gender gender = Gender::UNKNOWNGENDER,
           QString customPictureFileName = QString(), QString namePrefix = QString(),
           QString nickName = QString(), QDate birthday = QDate(), QObject *parent = 0);

    virtual const QHash<QString, CuteEntityManager::Relation> getRelations() const override;
    virtual QList<ValidationRule> validationRules() const override;


    bool isPresent(QDateTime date = QDateTime::currentDateTime());
    QString fullName(NameOrder nameOrder = NameOrder::FAMILY_FIRST_NAME_ORDER)
    const;

    QString getFirstName() const;
    void setFirstName(const QString &value);

    QString getFamilyName() const;
    void setFamilyName(const QString &value);

    QString getNamePrefix() const;
    void setNamePrefix(const QString &value);

    QString getNickName() const;
    void setNickName(const QString &value);

    QDate getBirthday() const;
    void setBirthday(const QDate &value);

    Gender getGender() const;
    void setGender(const Gender &value);

    QString getCustomPictureFileName() const;
    void setCustomPictureFileName(const QString &value);

    QList<QSharedPointer<Address>> getAddresses() const;
    void setAddresses(const QList<QSharedPointer<Address>> &value);

    void addAddress(Address *address);

  protected:
    QString firstName;
    QString familyName;
    QString namePrefix;
    QString nickName;
    QDate birthday;
    Gender gender;
    QString customPictureFileName;
    QList <QSharedPointer<Address>> addresses;


};


#endif // PERSON_H
