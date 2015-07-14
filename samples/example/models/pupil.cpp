#include "pupil.h"

Pupil::Pupil() : Person() {

}

Pupil::Pupil(QString firstName, QString familyName, Gender gender,
             QString customPictureFileName, QString namePrefix, QString nickName,
             QDate birthday, QString form, QObject *parent)
    : Person(firstName, familyName, gender, customPictureFileName, namePrefix,
             nickName, birthday, parent) {
    setFirstName(firstName);
    setFamilyName(familyName);
    setNamePrefix(namePrefix);
    setNickName(nickName);
    setBirthday(birthday);
    setGender(gender);
    setCustomPictureFileName(customPictureFileName);
    setForm(form);
}

QString Pupil::getForm() const {
    return form;
}

void Pupil::setForm(const QString &value) {
    form = value;
}
QString Pupil::getLegalGuardianNote() const
{
    return legalGuardianNote;
}

void Pupil::setLegalGuardianNote(const QString &value)
{
    legalGuardianNote = value;
}


