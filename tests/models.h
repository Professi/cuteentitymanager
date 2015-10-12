#ifndef MODELS_H
#define MODELS_H

#include <QDateTime>
#include <QString>
#include <QList>
#include <QObject>
#include <QDebug>
#include "entity.h"

using namespace CuteEntityManager;
class Group;
class Person: public Entity {
    Q_OBJECT
    Q_PROPERTY(QString firstName READ getFirstName WRITE setFirstName)
    Q_PROPERTY(QString familyName READ getFamilyName WRITE setFamilyName)
    Q_PROPERTY(QString namePrefix READ getNamePrefix WRITE setNamePrefix)
    Q_PROPERTY(QString nickName READ getNickName WRITE setNickName)
    Q_PROPERTY(QString customPictureFileName READ getCustomPictureFileName WRITE
               setCustomPictureFileName)
    Q_PROPERTY(QDate birthday READ getBirthday WRITE setBirthday)
    Q_PROPERTY(Gender gender READ getGender WRITE setGender)
    Q_PROPERTY(QList<QSharedPointer<Group>> groups READ getGroups WRITE setGroups)
    Q_PROPERTY(QList<QSharedPointer<Group>> maintainedGroups READ
               getMaintainedGroups WRITE setMaintainedGroups)

  public:
    enum class Gender {MALE, FEMALE, UNKNOWNGENDER};
    enum class NameOrder {FIRST_FAMILY_NAME_ORDER, FAMILY_FIRST_NAME_ORDER};
    Q_INVOKABLE explicit Person(QObject *parent = 0);
    Person(QString firstName, QString familyName,
           Gender gender = Gender::UNKNOWNGENDER,
           QString customPictureFileName = QString(), QString namePrefix = QString(),
           QString nickName = QString(), QDate birthday = QDate(), QObject *parent = 0);

    virtual const QHash<QString, CuteEntityManager::Relation> getRelations() const
    override;

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

    QList<QSharedPointer<Group> > getGroups() const;
    void setGroups(const QList<QSharedPointer<Group> > &value);

    QList<QSharedPointer<Group> > getMaintainedGroups() const;
    void setMaintainedGroups(const QList<QSharedPointer<Group> > &value);

  protected:
    QString firstName;
    QString familyName;
    QString namePrefix;
    QString nickName;
    QDate birthday;
    Gender gender;
    QString customPictureFileName;
    QList <QSharedPointer<Group>> groups;
    QList <QSharedPointer<Group>> maintainedGroups;
};

class Relation;
class Group: public CuteEntityManager::Entity {
    Q_OBJECT
    Q_PROPERTY(QList<QSharedPointer<Person>> persons READ getPersons WRITE
               setPersons)
    Q_PROPERTY(QString name READ getName WRITE setName)
    Q_PROPERTY(QSharedPointer<Person> leader READ getLeader WRITE
               setLeader)

  public:
    Q_INVOKABLE Group();
    const QHash<QString, CuteEntityManager::Relation> getRelations() const override;

    QString getName() const;
    void setName(const QString &value);

    QSharedPointer<Person> getLeader() const;
    void setLeader(const QSharedPointer<Person> &value);

    QList<QSharedPointer<Person> > getPersons() const;
    void setPersons(const QList<QSharedPointer<Person> > &value);

  protected:
    QList<QSharedPointer<Person>> persons;
    QSharedPointer<Person> leader;
    QString name;
};

class Article : public CuteEntityManager::Entity {
    Q_OBJECT
    Q_PROPERTY(double price READ getPrice WRITE setPrice)
    Q_PROPERTY(QString name READ getName WRITE setName)
  private:
    double price;
    QString name;

  public:
    virtual ~Article();
    Q_INVOKABLE Article();
    Article(double price, QString name);
    double getPrice() const;
    void setPrice(double value);
    QString getName() const;
    void setName(const QString &value);
};

#endif // MODELS_H
