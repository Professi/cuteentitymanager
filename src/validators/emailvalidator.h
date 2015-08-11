#ifndef EMAILVALIDATOR_H
#define EMAILVALIDATOR_H
#include "validator.h"
namespace CuteEntityManager {
class EmailValidator : public Validator {
    Q_OBJECT
  public:
    EmailValidator();
    QString getPattern() const;
    void setPattern(const QString &value);

    QString getFullPattern() const;
    void setFullPattern(const QString &value);

  protected:
    ErrorMsg validateParam(QVariant value, Param param) const final override;
    QString pattern =
        QStringLiteral("/^[a-zA-Z0-9!#$%&\'*+\\/=?^_`{|}~-]+(?:\\\\.[a-zA-Z0-9!#$%&\'*+\\\\/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?$/");
    QString fullPattern =
        QStringLiteral("/^[^@]*<[a-zA-Z0-9!#$%&'*+\\\\/=?^_`{|}~-]+(?:\\.[a-zA-Z0-9!#$%&\'*+\\\\/=?^_`{|}~-]+)*@(?:[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?\\.)+[a-zA-Z0-9](?:[a-zA-Z0-9-]*[a-zA-Z0-9])?>$/");
};
}
#endif // EMAILVALIDATOR_H
