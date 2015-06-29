#ifndef PUPIL_H
#define PUPIL_H

#include "person.h"

class Pupil : public Person
{
public:
    Pupil();
    Pupil(QString firstName,
          QString familyName,
          Gender gender = Person::UNKNOWNGENDER,
          QString customPictureFileName = QString(),
          QString namePrefix = QString(),
          QString nickName = QString(),
          QDate birthday = QDate(),
          QString form = QString(),
          QObject *parent = 0);

    QString form() const { return m_form; }

    void setForm(QString form) { m_form = form; }

protected:
    QString m_form;

};

#endif // PUPIL_H
