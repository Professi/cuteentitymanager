#ifndef PUPIL_H
#define PUPIL_H
#include "person.h"

class Pupil : public Person {
    Q_OBJECT
    EM_MACRO(Pupil)
    Q_PROPERTY(QString legalGuardianNote READ getLegalGuardianNote WRITE
               setLegalGuardianNote)
  public:
    Q_INVOKABLE Pupil();
    Pupil(QString firstName, QString familyName,
          QString customPictureFileName = QString(), QString namePrefix = QString(),
          QString nickName = QString(), QDate birthday = QDate(), QString legalGuardianNote = "", QObject *parent = 0);

    QString getLegalGuardianNote() const;
    void setLegalGuardianNote(const QString &value);
    virtual const QHash<QString, CuteEntityManager::Relation> getRelations() const override;

    QString getForm() const;
    void setForm(const QString &value);

  protected:
    QString legalGuardianNote;

};

#endif // PUPIL_H
