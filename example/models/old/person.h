#ifndef PERSON_H
#define PERSON_H

#include <QDateTime>
#include <QString>
#include <QList>
#include <QObject>
#include "../../src/entity.h"
#include <QAbstractListModel>
#include <QDebug>

enum Gender {MALE, FEMALE, UNKNOWNGENDER};
Q_DECLARE_METATYPE(Gender)
class Person: public CuteEntityManager::Entity {

    Q_OBJECT

    //Q_ENUMS(Gender)
    Q_PROPERTY(QString firstName READ getFirstName WRITE setFirstName NOTIFY
               firstNameChanged)
    Q_PROPERTY(QString familyName READ getFamilyName WRITE setFamilyName NOTIFY
               familyNameChanged)
    Q_PROPERTY(QString namePrefix READ getNamePrefix WRITE setNamePrefix NOTIFY
               namePrefixChanged)
    Q_PROPERTY(QString nickName READ getNickName WRITE setNickName NOTIFY
               nickNameChanged)
    Q_PROPERTY(QString customPictureFileName READ getCustomPictureFileName WRITE
               setCustomPictureFileName NOTIFY
               customPictureFileNameChanged)
    Q_PROPERTY(QDate birthday READ getBirthday WRITE setBirthday NOTIFY
               birthdayChanged)
    Q_PROPERTY(Gender gender READ getGender WRITE setGender NOTIFY genderChanged)

  signals:
    void firstNameChanged();
    void familyNameChanged();
    void namePrefixChanged();
    void nickNameChanged();
    void birthdayChanged();
    void genderChanged();
    void customPictureFileNameChanged();

  public:
    QString toString();
    Person(QObject *parent = 0);
    Person(QString firstName,
           QString familyName,
           Gender gender = UNKNOWNGENDER,
           QString customPictureFileName = QString(),
           QString namePrefix = QString(),
           QString nickName = QString(),
           QDate birthday = QDate(),
           QObject *parent = 0);
    virtual ~Person() {}

    QString getCustomPictureFileName() const;
    void setCustomPictureFileName(const QString &value);

    Gender getGender() const;
    void setGender(const Gender &value);

    QDate getBirthday() const;
    void setBirthday(const QDate &value);

    QString getNickName() const;
    void setNickName(const QString &value);

    QString getNamePrefix() const;
    void setNamePrefix(const QString &value);

    QString getFamilyName() const;
    void setFamilyName(const QString &value);

    QString getFirstName() const;
    void setFirstName(const QString &value);

  protected:
    // members
    QString firstName;
    QString familyName;
    QString namePrefix;
    QString nickName;
    QDate birthday;
    Gender gender;
    QString customPictureFileName;

};

#endif // PERSON_H
