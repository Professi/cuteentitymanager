#ifndef TEACHER_H
#define TEACHER_H
#include "person.h"
#include "relation.h"
using namespace CuteEntityManager;
class Group;

class Teacher : public Person {
    Q_OBJECT
    Q_PROPERTY(QList<QSharedPointer<Group>> groups READ getGroups WRITE setGroups
               NOTIFY groupsChanged)
    Q_PROPERTY(QSharedPointer<Person> parent READ getParent WRITE setParent NOTIFY
               parentChanged)
  signals:
    void groupsChanged();
    void parentChanged();

  public:
    Teacher(QSharedPointer<Person> parent);
    virtual const QHash<QString, Relation> getRelations() const;
    QList<QSharedPointer<Group> > getGroups() const;
    void setGroups(const QList<QSharedPointer<Group> > &value);

    QSharedPointer<Person> getParent() const;
    void setParent(const QSharedPointer<Person> &value);

  private:
    QList<QSharedPointer<Group>> groups;
    QSharedPointer<Person> parent;
};

#endif // TEACHER_H
