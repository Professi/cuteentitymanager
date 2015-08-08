#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QObject>
#include <QHash>
#include "param.h"
#include "errormsg.h"
namespace CuteEntityManager {
class Validator : public QObject {
    Q_OBJECT
  public:
    Validator();
    virtual ~Validator();
    static const QHash<QString, QString> builtInValidators();
    virtual QList<ErrorMsg> validate(QVariant value, QList<Param> params) const;
    QString generateErrorMsg(ErrorMsg msg);

  protected:
    virtual ErrorMsg validateParam(QVariant value, Param param) const = 0;
};
}
#endif // VALIDATOR_H
