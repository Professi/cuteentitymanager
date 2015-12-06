#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H
#include <QString>
namespace CuteEntityManager {


class Attribute {
  public:
    Attribute(QString name, QString columnName, QString tableName, QMetaObject *metaObj,
              QString relatedTable = "", QMetaObject *relatedClass = nullptr,
              QString conjunctedTable = "");
    QString getName() const;
    void setName(const QString &value);

    QString getColumnName() const;
    void setColumnName(const QString &value);

    QString getTableName() const;
    void setTableName(const QString &value);

    QString getRelatedTable() const;
    void setRelatedTable(const QString &value);

    QMetaObject *getRelatedClass() const;
    void setRelatedClass(QMetaObject *value);

    QString getConjunctedTable() const;
    void setConjunctedTable(const QString &value);

    QMetaObject *getMetaObj() const;
    void setMetaObj(QMetaObject *value);

  private:
    QString name;
    QString columnName;
    QString tableName;
    QMetaObject *metaObj;
    QString relatedTable;
    QMetaObject *relatedClass;
    QString conjunctedTable;
};
}
#endif // ATTRIBUTE_H
