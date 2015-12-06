#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H
#include <QString>
#include <QMetaObject>
namespace CuteEntityManager {
class Attribute {
  public:
    Attribute(QString name, QString columnName, QString tableName, const QMetaObject *metaObj,
              QString relatedTable = "", const QMetaObject *relatedClass = nullptr,
              QString conjunctedTable = "", QString relatedColumnName = "", QString baseTableName = "",
              const QMetaObject *baseMetaObj = nullptr);
    QString getName() const;
    void setName(const QString &value);

    QString getColumnName() const;
    void setColumnName(const QString &value);

    QString getTableName() const;
    void setTableName(const QString &value);

    QString getRelatedTable() const;
    void setRelatedTable(const QString &value);

    QString getConjunctedTable() const;
    void setConjunctedTable(const QString &value);

    QString getBaseTableName() const;
    void setBaseTableName(const QString &value);
    void setInheritance(const QString &baseTableName, const QMetaObject *baseMetaObj);
    void setRelation(const QString &tableName, const QMetaObject *relatedMetaObj,
                     const QString &conjunctedTable = "", const QString &relatedColumnName = "");
    const QMetaProperty getMetaProperty();
    const QMetaObject *getMetaObj() const;
    void setMetaObj(const QMetaObject *value);

    const QMetaObject *getBaseMetaObj() const;
    void setBaseMetaObj(const QMetaObject *value);

    const QMetaObject *getRelatedClass() const;
    void setRelatedClass(const QMetaObject *value);

    QString getRelatedColumnName() const;
    void setRelatedColumnName(const QString &value);

  private:
    QString name;
    QString columnName;
    QString tableName;
    const QMetaObject *metaObj;
    QString baseTableName;
    const QMetaObject *baseMetaObj;
    QString relatedTable;
    const QMetaObject *relatedClass;
    QString relatedColumnName;
    QString conjunctedTable;
};
}
#endif // ATTRIBUTE_H
