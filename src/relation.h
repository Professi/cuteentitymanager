#ifndef RELATION_H
#define RELATION_H
#include <QString>
namespace CuteEntityManager {
enum RelationType {
    BELONGS_TO,
    HAS_MANY,
    HAS_ONE,
    MANY_MANY,
};

class Relation {
  public:
    Relation();
    Relation(QString propertyName, RelationType type, bool optional = true);
    ~Relation();
    RelationType getType() const;
    void setType(const RelationType &value);

    QString getPropertyName() const;
    void setPropertyName(const QString &value);

    bool getOptional() const;
    void setOptional(bool value);

  protected:
    QString propertyName;
    RelationType type;
    bool optional;

};
}

#endif // RELATION_H
