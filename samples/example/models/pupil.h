#ifndef PUPIL_H
#define PUPIL_H
#include "person.h"

class Pupil : public Person {
    Q_OBJECT
    Q_PROPERTY(QString legalGuardianNote READ getLegalGuardianNote WRITE
               setLegalGuardianNote)
  public:
    Q_INVOKABLE Pupil();
    Pupil(QString firstName, QString familyName, Gender gender = UNKNOWNGENDER,
          QString customPictureFileName = QString(), QString namePrefix = QString(),
          QString nickName = QString(), QDate birthday = QDate(),
          QString form = QString(), QObject *parent = 0);
    QString getForm() const;
    void setForm(const QString &value);

    QString getLegalGuardianNote() const;
    void setLegalGuardianNote(const QString &value);

  protected:
    QString form;
    QString legalGuardianNote;

};

#endif // PUPIL_H
