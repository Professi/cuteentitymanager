#ifndef TESTPERSON_H
#define TESTPERSON_H

#include <QDateTime>
#include <QDebug>

#include "entity.h"
#include "testgroup.h"

using namespace CuteEntityManager;

class Gender;
class NameOrder;

class TestPerson: public Entity
{
    Q_OBJECT
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName)
    Q_PROPERTY(QString familyName READ familyName WRITE setFamilyName)
    Q_PROPERTY(QString namePrefix READ namePrefix WRITE setNamePrefix)
    Q_PROPERTY(QString nickName READ nickName WRITE setNickName)
    Q_PROPERTY(QDate birthday READ birthday WRITE setBirthday)
    Q_PROPERTY(Gender gender READ gender WRITE setGender)
    Q_PROPERTY(QString customPictureFileName READ customPictureFileName WRITE setCustomPictureFileName)

signals:
    void firstNameChanged();
    void familyNameChanged();
    void namePrefixChanged();
    void nickNameChanged();
    void birthdayChanged();
    void genderChanged();
    void customPictureFileNameChanged();

public:
    EM_MACRO(TestPerson)

    enum class Gender {
        MALE = 0,
        FEMALE = 1,
        UNKNOWNGENDER = -1
    };
    Q_ENUM(Gender)

    enum class NameOrder {
        FIRST_FAMILY=0,
        FAMILY_FIRST=1
    };
    Q_ENUM(NameOrder)


    Q_INVOKABLE explicit TestPerson();
    virtual ~TestPerson() override {}

    virtual const QHash<QString, CuteEntityManager::Relation> getRelations() const override;

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

    void setBirthday(QDate birthday) {m_birthday=birthday; emit birthdayChanged();}
    void setGender(Gender gender) {m_gender=gender; emit genderChanged();}
    void setCustomPictureFileName(QString fileName) {m_customPictureFileName=fileName; emit customPictureFileNameChanged();}

    QList<QSharedPointer<TestGroup> > groups() const;
    void setGroups(const QList<QSharedPointer<TestGroup> > &groups);

protected:
    // members
    QString m_firstName = QString();
    QString m_familyName = QString();
    QString m_namePrefix = QString();
    QString m_nickName = QString();
    QDate m_birthday = QDate();
    Gender m_gender = Gender::UNKNOWNGENDER;
    QString m_customPictureFileName = QString();
};

#endif // TESTPERSON_H
