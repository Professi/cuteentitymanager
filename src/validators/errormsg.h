#ifndef ERRORMSG_H
#define ERRORMSG_H
#include <QString>
namespace CuteEntityManager {
class ErrorMsg {
public:
    ErrorMsg();
    ~ErrorMsg();
    ErrorMsg(QString param, QString errorMsg, QString propertyName = "");

    QString getParam() const;
    void setParam(const QString &value);

    QString getPropertyName() const;
    void setPropertyName(const QString &value);

    QString getErrorMsg() const;
    void setErrorMsg(const QString &value);

private:
    QString param;
    QString propertyName;
    QString errorMsg;
};
}
#endif // ERRORMSG_H
