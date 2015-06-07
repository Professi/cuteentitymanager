#ifndef PUPIL_H
#define PUPIL_H
#include "person.h"
#include "relation.h"
using namespace CuteEntityManager;

class Pupil : public Person
{
    Q_OBJECT
//    Q_PROPERTY(QSharedPointer<Person> parent READ getParent WRITE setParent NOTIFY
//               parentChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
signals:
    void parentChanged();
    void nameChanged();


public:
    Pupil();
    virtual const QHash<QString, Relation> getRelations() const;


    QSharedPointer<Person> getParent() const;
    void setParent(const QSharedPointer<Person> &value);

    QString getName() const;
    void setName(const QString &value);

private:
    QSharedPointer<Person> parent;
    QString name;
};

#endif // PUPIL_H
