#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H
#include <QString>
namespace CuteEntityManager {


class Attribute {
  public:
    Attribute();
private:
    QString name;
    QString className;
    QString relatedClass;
    QString relatedTable;
};
}
#endif // ATTRIBUTE_H
