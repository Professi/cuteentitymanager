#ifndef GROUP_H
#define GROUP_H

#include "models/person.h"
//#include <QQmlListProperty>
#include <QDebug>
#include <QList>
#include <QVariantList>
//#include <QQuickView>
#include <QSharedPointer>
#include <QHash>
#include <QString>
#include "relation.h"
using namespace CuteEntityManager;


class SeatingPlan;
class Teacher;
class Pupil;
class Person;

class Group: public CuteEntityManager::Entity {
    Q_OBJECT

    Q_PROPERTY(QList<QSharedPointer<Pupil>> pupils READ getPupils WRITE setPupils
               NOTIFY pupilsChanged)
    Q_PROPERTY(QList<QSharedPointer<Pupil>> classPrefects READ getClassPrefects
               WRITE setClassPrefects NOTIFY classPrefectsChanged)
    Q_PROPERTY(QSharedPointer<Teacher> teacher READ getTeacher WRITE setTeacher
               NOTIFY teacherChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QList<QSharedPointer<Person> > parentSpeakers READ getParentSpeakers WRITE setParentSpeakers
               NOTIFY parentSpeakersChanged)

  signals:
    void pupilsChanged();
    void nameChanged();
    void teacherChanged();
    void classPrefectsChanged();
    void parentSpeakersChanged();

  public:
    virtual const QHash<QString, Relation> getRelations() const;
    Group();

    QString getName() const;
    void setName(const QString &value);

    QSharedPointer<Teacher> getTeacher() const;
    void setTeacher(const QSharedPointer<Teacher> &value);

    QList<QSharedPointer<Pupil> > getPupils() const;
    void setPupils(const QList<QSharedPointer<Pupil> > &value);

    QList<QSharedPointer<Pupil> > getClassPrefects() const;
    void setClassPrefects(const QList<QSharedPointer<Pupil> > &value);

    QList<QSharedPointer<Person> > getParentSpeakers() const;
    void setParentSpeakers(const QList<QSharedPointer<Person> > &value);

  private:

    QString name;
    QSharedPointer<Teacher> teacher;
    QList<QSharedPointer<Pupil>> pupils;
    QList<QSharedPointer<Pupil>> classPrefects;
    QList<QSharedPointer<Person>> parentSpeakers;


    //    PersonListModel* m_personListModel;
};
#endif // GROUP_H
