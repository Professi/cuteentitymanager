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
class Relation;
class Person: public Entity {

    Q_OBJECT
    Q_PROPERTY(QString firstName READ getFirstName WRITE setFirstName)
    Q_PROPERTY(QString familyName READ getFamilyName WRITE setFamilyName)
    Q_PROPERTY(QString nickName READ getNickName WRITE setNickName)
    Q_PROPERTY(QDate birthday READ getBirthday WRITE setBirthday)
    Q_PROPERTY(Gender gender READ getGender WRITE setGender)
    Q_PROPERTY(QList<QSharedPointer<Group>> groups READ getGroups WRITE setGroups)
    Q_PROPERTY(QList<QSharedPointer<Group>> maintainedGroups READ
               getMaintainedGroups WRITE setMaintainedGroups)

  public:
    enum class Gender {MALE=109, FEMALE=102, UNKNOWNGENDER=0};
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
    Q_ENUM(Gender)
#else
    Q_ENUMS(Gender)
#endif
    enum class NameOrder {FIRST_FAMILY_NAME_ORDER, FAMILY_FIRST_NAME_ORDER};
    Q_INVOKABLE explicit Person(QObject *parent = 0);
    Person(QString firstName, QString familyName,
           Gender gender = Gender::UNKNOWNGENDER,
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

    QString getNickName() const;
    void setNickName(const QString &value);

    QDate getBirthday() const;
    void setBirthday(const QDate &value);

    Gender getGender() const;
    void setGender(const Gender &value);

    QList<QSharedPointer<Group>> getGroups() const;
    void setGroups(const QList<QSharedPointer<Group>> &value);

    QList<QSharedPointer<Group>> getMaintainedGroups() const;
    void setMaintainedGroups(const QList<QSharedPointer<Group>> &value);
    virtual QList<ValidationRule> validationRules() const override;

  protected:
    QString firstName;
    QString familyName;
    QString nickName;
    QDate birthday;
    Gender gender;
    QList <QSharedPointer<Group>> groups;
    QList <QSharedPointer<Group>> maintainedGroups;
};

class Employee : public Person {
    Q_OBJECT
    Q_PROPERTY(QString department READ getDepartment WRITE setDepartment)
    Q_PROPERTY(quint64 persNumber READ getPersNumber WRITE setPersNumber)
    Q_PROPERTY(bool manager READ isManager WRITE setManager)
  public:
    Employee() : Person() { }
    Employee(quint64 persNumber, QString firstName, QString familyName,
             Gender gender = Gender::UNKNOWNGENDER,
             QString nickName = QString(), QDate birthday = QDate(), QString department = QString(),
             bool manager = false, QObject *parent = 0) : Person(firstName, familyName, gender,
                         nickName, birthday, parent) {
        this->department = department;
        this->manager = manager;
        this->persNumber = persNumber;
    }

    virtual const QHash<QString, CuteEntityManager::Relation> getRelations() const
    override;
    QString getDepartment() const;
    void setDepartment(const QString &value);

    bool isManager() const;
    void setManager(bool value);

    quint64 getPersNumber() const;
    void setPersNumber(const quint64 &value);


  private:
    QString department;
    quint64 persNumber;
    bool manager = false;
};


class WorkerGroup : public Entity {
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName)
    Q_PROPERTY(quint32 efficiency READ getEfficiency WRITE setEfficiency)
    Q_PROPERTY(bool active READ isActive WRITE setActive)
    Q_PROPERTY(QList<QSharedPointer<Employee>> workers READ getWorkers WRITE
               setWorkers)
  public:
    WorkerGroup() : Entity() { }
    WorkerGroup(QString name, quint32 efficiency, bool active = true) : Entity() {
        this->name = name;
        this->efficiency = efficiency;
        this->active = active;
    }
    virtual const QHash<QString, CuteEntityManager::Relation> getRelations() const
    override;
    QString getName() const;
    void setName(const QString &value);

    quint32 getEfficiency() const;
    void setEfficiency(const quint32 &value);

    bool isActive() const;
    void setActive(bool value);

    QList<QSharedPointer<Employee>> getWorkers() const;
    void setWorkers(const QList<QSharedPointer<Employee>> &value);
    void addWorker(const QSharedPointer<Employee> &value);

  private:
    QString name;
    quint32 efficiency;
    bool active = true;
    QList<QSharedPointer<Employee>> workers;
};



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
    Group(QString name) : Entity() {
        this->name = name;
    }
    QString getName() const;
    void setName(const QString &value);
    QSharedPointer<Person> getLeader() const;
    void setLeader(const QSharedPointer<Person> &value);
    QList<QSharedPointer<Person>> getPersons() const;
    void addPerson(const QSharedPointer<Person> &value);
    void setPersons(const QList<QSharedPointer<Person>> &value);
    void removePerson(const QSharedPointer<Person> &value);

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
