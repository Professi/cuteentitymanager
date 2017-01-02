#include "ratingmarkincident.h"

RatingMarkIncident::RatingMarkIncident()
{

}

QString RatingMarkIncident::symbol() const
{
    return m_symbol;
}

void RatingMarkIncident::setSymbol(const QString &symbol)
{
    m_symbol = symbol;
}

qreal RatingMarkIncident::value() const
{
    return m_value;
}

void RatingMarkIncident::setValue(const qreal &value)
{
    m_value = value;
}

qreal RatingMarkIncident::percentValue() const
{
    return m_percentValue;
}

void RatingMarkIncident::setPercentValue(const qreal &percentValue)
{
    m_percentValue = percentValue;
}

qreal RatingMarkIncident::weight() const
{
    return m_weight;
}

void RatingMarkIncident::setWeight(const qreal &weight)
{
    m_weight = weight;
}

bool RatingMarkIncident::rateable() const
{
    return m_rateable;
}

void RatingMarkIncident::setRateable(bool rateable)
{
    m_rateable = rateable;
}

QSharedPointer<Occasion> RatingMarkIncident::occasion() const
{
    return m_occasion;
}

void RatingMarkIncident::setOccasion(const QSharedPointer<Occasion> &occasion)
{
    m_occasion = occasion;
}

const QHash<QString, Relation> RatingMarkIncident::getRelations() const
{
    auto hash = Incident::getRelations();
    hash.insert("occasion",Relation("occasion",CuteEntityManager::RelationType::MANY_TO_ONE));
    hash.insert("ratingMarkSystem", Relation("ratingMarkSystem",RelationType::MANY_TO_ONE));
    return hash;
}

QSharedPointer<RatingMarkSystem> RatingMarkIncident::ratingMarkSystem() const
{
    return m_ratingMarkSystem;
}

void RatingMarkIncident::setRatingMarkSystem(const QSharedPointer<RatingMarkSystem> &ratingMarkSystem)
{
    m_ratingMarkSystem = ratingMarkSystem;
}

bool RatingMarkIncident::signatureNeeded() const
{
    return m_signatureNeeded;
}

void RatingMarkIncident::setSignatureNeeded(bool signatureNeeded)
{
    m_signatureNeeded = signatureNeeded;
}
