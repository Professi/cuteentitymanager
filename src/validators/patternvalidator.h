#ifndef PATTERNVALIDATOR_H
#define PATTERNVALIDATOR_H
#include "validator.h"
namespace CuteEntityManager {
class PatternValidator : public Validator {
    Q_OBJECT
  public:
    PatternValidator();
    ErrorMsg validateParam(QVariant value, Param param) const final override;
};
}
#endif // PATTERNVALIDATOR_H
