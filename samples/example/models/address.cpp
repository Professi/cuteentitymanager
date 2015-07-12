#include "address.h"

Address::Address(QString label, QString street, QString postcode, QString city) {
    m_label=label;
    m_street=street;
    m_postcode=postcode;
    m_city=city;
}
QString Address::label() const
{
    return m_label;
}

void Address::setLabel(const QString &label)
{
    m_label = label;
}
QString Address::street() const
{
    return m_street;
}

void Address::setStreet(const QString &street)
{
    m_street = street;
}
QString Address::postcode() const
{
    return m_postcode;
}

void Address::setPostcode(const QString &postcode)
{
    m_postcode = postcode;
}
QString Address::city() const
{
    return m_city;
}

void Address::setCity(const QString &city)
{
    m_city = city;
}





