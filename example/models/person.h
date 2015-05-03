#ifndef PERSON_H
#define PERSON_H

#include <QDateTime>
#include <QString>
#include <QList>
#include <QObject>
#include "../../src/entity.h"
#include <QAbstractListModel>
#include <QDebug>

class Person: public CuteEntityManager::Entity {

    Q_OBJECT
    Q_ENUMS(Gender)

    //[1] We don't want the id to be set from QML
    //[2] Notification via inherited signals is not allowed
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY firstNameChanged)
    Q_PROPERTY(QString familyName READ familyName WRITE setFamilyName NOTIFY familyNameChanged)
    Q_PROPERTY(QString namePrefix READ namePrefix WRITE setNamePrefix NOTIFY namePrefixChanged)
    Q_PROPERTY(QString nickName READ nickName WRITE setNickName NOTIFY nickNameChanged)
    Q_PROPERTY(QString customPictureFileName READ customPictureFileName WRITE setCustomPictureFileName NOTIFY
               customPictureFileNameChanged)
    Q_PROPERTY(QDate birthday READ birthday WRITE setBirthday NOTIFY birthdayChanged)
    Q_PROPERTY(Gender gender READ gender WRITE setGender NOTIFY genderChanged)



  signals:
    void firstNameChanged();
    void familyNameChanged();
    void namePrefixChanged();
    void nickNameChanged();
    void birthdayChanged();
    void genderChanged();
    void customPictureFileNameChanged();

  public slots:
    void testSlot() {
        qDebug() << "testslot clicked";
    }

  public:
    QString toString();
    enum Gender {MALE, FEMALE, UNKNOWNGENDER};
    Person(QObject *parent=0);
    Person(QString firstName,
           QString familyName,
           Gender gender = Person::UNKNOWNGENDER,
           QString customPictureFileName = QString(),
           QString namePrefix = QString(),
           QString nickName = QString(),
           QDate birthday = QDate(),
           QObject *parent = 0);



    bool isPresent(QDateTime date = QDateTime::currentDateTime());
    QString fullName();

    // getters
    QString firstName() const {
        return m_firstName;
    }
    QString familyName() const {
        return m_familyName;
    }
    QString namePrefix() const {
        return m_namePrefix;
    }
    QString nickName() const {
        return m_nickName;
    }
    QDate birthday() const {
        return m_birthday;
    }
    Gender gender() const {
        return m_gender;
    }
    QString customPictureFileName() const {
        return m_customPictureFileName;
    }


    // setters
    void setFirstName(QString firstName) {
        m_firstName = firstName;
        emit firstNameChanged();
    }
    void setFamilyName(QString familyName) {
        m_familyName = familyName;
        emit familyNameChanged();
    }
    void setNamePrefix(QString namePrefix) {
        m_namePrefix = namePrefix;
        emit namePrefixChanged();
    }
    void setNickName(QString nickName) {
        m_nickName = nickName;
        emit nickNameChanged();
    }
    void setBirthday(QDate birthday) {
        m_birthday = birthday;
        emit birthdayChanged();
    }
    void setGender(Gender gender) {
        m_gender = gender;
        emit genderChanged();
    }
    void setCustomPictureFileName(QString fileName) {
        m_customPictureFileName = fileName;
        emit customPictureFileNameChanged();
    }


  protected:
    // members
    QString m_firstName;
    QString m_familyName;
    QString m_namePrefix;
    QString m_nickName;
    QDate m_birthday;
    Gender m_gender;
    QString m_customPictureFileName;

};
Q_DECLARE_METATYPE(Person*)
Q_DECLARE_METATYPE(QList<Person*>)
#endif // PERSON_H
