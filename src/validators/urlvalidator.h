#ifndef URLVALIDATOR_H
#define URLVALIDATOR_H

#include "validator.h"
namespace CuteEntityManager {
class UrlValidator : public Validator {
    Q_OBJECT
  public:
    UrlValidator();
    ErrorMsg validateParam(QVariant value, Param param) const final override;
    QStringList getValidSchemes() const;
    void setValidSchemes(const QStringList &value);

    QString getPattern() const;
    void setPattern(const QString &value);

  protected:
    QString pattern =
        QStringLiteral("/^{schemes}:\\/\\/(([A-Z0-9][A-Z0-9_-]*)(\\.[A-Z0-9][A-Z0-9_-]*)+)/i");
    QStringList validSchemes = {"http", "https"};
};
}

#endif // URLVALIDATOR_H
