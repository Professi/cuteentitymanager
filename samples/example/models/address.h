#ifndef ADDRESS_H
#define ADDRESS_H

#include <QString>
//#iclude "../../em/entitymanager/src/entity.h"
#include "entity.h"

class Address: public CuteEntityManager::Entity
{
    Q_OBJECT

    Q_PROPERTY(QString label READ label WRITE setLabel)
    Q_PROPERTY(QString street READ street WRITE setStreet)
    Q_PROPERTY(QString postcode READ postcode WRITE setPostcode)
    Q_PROPERTY(QString city READ city WRITE setCity)

public:
    Q_INVOKABLE Address() {}
    Address(QString label, QString street, QString postcode, QString city);

    QString label() const;
    void setLabel(const QString &label);

    QString street() const;
    void setStreet(const QString &street);

    QString postcode() const;
    void setPostcode(const QString &postcode);

    QString city() const;
    void setCity(const QString &city);

protected:
    // members
    QString m_label;
    QString m_street;
    QString m_postcode;
    QString m_city;
};

#endif // ADDRESS_H
