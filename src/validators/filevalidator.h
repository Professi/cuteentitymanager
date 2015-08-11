#ifndef FILEVALIDATOR_H
#define FILEVALIDATOR_H
#include "validator.h"
#include <QFileInfo>
namespace CuteEntityManager {
class FileValidator : public Validator {
    Q_OBJECT
  public:
    FileValidator();
  protected:
    virtual ErrorMsg validateParam(QVariant value, Param param) const override;
    virtual ErrorMsg validateMIMEType(const QFileInfo &file,
                                      const Param &param) const;
    virtual ErrorMsg validateExtension(const QFileInfo &file,
                                       const Param &param) const;
};
}
#endif // FILEVALIDATOR_H
