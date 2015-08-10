#ifndef FILEVALIDATOR_H
#define FILEVALIDATOR_H
#include "validator.h"
namespace CuteEntityManager {
class FileValidator : public Validator {
    Q_OBJECT
  public:
    FileValidator();
    virtual ErrorMsg validateParam(QVariant value, Param param) const override;
};
}
#endif // FILEVALIDATOR_H
