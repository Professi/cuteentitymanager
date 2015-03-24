#ifndef COLUMNSCHEMA_H
#define COLUMNSCHEMA_H
#include <QString>
#include <QList>

namespace CuteEntityManager {

class ColumnSchema
{
public:
    ColumnSchema();
    ~ColumnSchema();
    QString getName() const;
    void setName(const QString &value);

    bool getAllowNull() const;
    void setAllowNull(bool value);

    QString getDbType() const;
    void setDbType(const QString &value);

    QString getDefaultValue() const;
    void setDefaultValue(const QString &value);

    QList<QString> getEnumValues() const;
    void setEnumValues(const QList<QString> &value);

    quint8 getSize() const;
    void setSize(const quint8 &value);

    quint8 getPrecision() const;
    void setPrecision(const quint8 &value);

    quint8 getScale() const;
    void setScale(const quint8 &value);

    bool getPrimaryKey() const;
    void setPrimaryKey(bool value);

    bool getAutoIncrement() const;
    void setAutoIncrement(bool value);

    bool getUnsignedColumn() const;
    void setUnsignedColumn(bool value);

    QString getComment() const;
    void setComment(const QString &value);

private:
    QString name;
    bool allowNull;
    QString dbType;
    QString defaultValue;
    QList<QString> enumValues;
    quint8 size;
    quint8 precision;
    quint8 scale;
    bool primaryKey;
    bool autoIncrement;
    bool unsignedColumn;
    QString comment;
};
}
#endif // COLUMNSCHEMA_H
