#include "ratingmarkdefinition.h"

RatingMarkDefinition::RatingMarkDefinition()
    :Incident()
{
    m_ratingMarkSystem = QSharedPointer<RatingMarkSystem>();
    m_symbol = QString();
    m_valueEquivalent = -999;
    m_minValue = -999;
    m_percentEquivalent = -999;
    m_minPercent = -999;
    m_rateable = true;
    m_panelColumn = -1;
    m_panelRow = -1;
}

QSharedPointer<RatingMarkSystem> RatingMarkDefinition::ratingMarkSystem() const
{
    return m_ratingMarkSystem;
}

void RatingMarkDefinition::setRatingMarkSystem(const QSharedPointer<RatingMarkSystem> &ratingMarkSystem)
{
    m_ratingMarkSystem = ratingMarkSystem;
}

QString RatingMarkDefinition::symbol() const
{
    return m_symbol;
}

void RatingMarkDefinition::setSymbol(const QString &symbol)
{
    m_symbol = symbol;
}

qreal RatingMarkDefinition::valueEquivalent() const
{
    return m_valueEquivalent;
}

void RatingMarkDefinition::setValueEquivalent(const qreal &valueEquivalent)
{
    m_valueEquivalent = valueEquivalent;
}

qreal RatingMarkDefinition::minValue() const
{
    return m_minValue;
}

void RatingMarkDefinition::setMinValue(const qreal &minValue)
{
    m_minValue = minValue;
}

qreal RatingMarkDefinition::percentEquivalent() const
{
    return m_percentEquivalent;
}

void RatingMarkDefinition::setPercentEquivalent(const qreal &percentEquivalent)
{
    m_percentEquivalent = percentEquivalent;
}

qreal RatingMarkDefinition::minPercent() const
{
    return m_minPercent;
}

void RatingMarkDefinition::setMinPercent(const qreal &minimumPercent)
{
    m_minPercent = minimumPercent;
}

bool RatingMarkDefinition::rateable() const
{
    return m_rateable;
}

void RatingMarkDefinition::setRateable(bool rateable)
{
    m_rateable = rateable;
}

int RatingMarkDefinition::panelColumn() const
{
    return m_panelColumn;
}

void RatingMarkDefinition::setPanelColumn(int panelColumn)
{
    m_panelColumn = panelColumn;
}

int RatingMarkDefinition::panelRow() const
{
    return m_panelRow;
}

void RatingMarkDefinition::setPanelRow(int panelRow)
{
    m_panelRow = panelRow;
}

const QHash<QString, Relation> RatingMarkDefinition::getRelations() const
{
        auto hash = Incident::getRelations();
        hash.insert("ratingMarkSystem",Relation("ratingMarkSystem",CuteEntityManager::RelationType::MANY_TO_ONE));

        return hash;
}

bool RatingMarkDefinition::lessThanPercent(const QSharedPointer<RatingMarkDefinition> &a, const QSharedPointer<RatingMarkDefinition> &b)
{
    return a->percentEquivalent() < b->percentEquivalent();
}
