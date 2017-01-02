#ifndef RATINGMARKDEFINITION_H
#define RATINGMARKDEFINITION_H

#include <QObject>

#include "entity.h"
#include "incident.h"
#include "enums.h"

class RatingMarkSystem;

using namespace CuteEntityManager;

/**
 * @brief The RatingMarkDefinition class
 *
 */
class RatingMarkDefinition : public Incident
{
    Q_OBJECT
    EM_MACRO(RatingMarkDefinition)
    Q_PROPERTY(QSharedPointer<RatingMarkSystem> ratingMarkSystem READ ratingMarkSystem WRITE setRatingMarkSystem)
    Q_PROPERTY(QString symbol READ symbol WRITE setSymbol)
    Q_PROPERTY(qreal valueEquivalent READ valueEquivalent WRITE setValueEquivalent)
    Q_PROPERTY(qreal minValue READ minValue WRITE setMinValue)
    Q_PROPERTY(qreal percentEquivalent READ percentEquivalent WRITE setPercentEquivalent)
    Q_PROPERTY(qreal minPercent READ minPercent WRITE setMinPercent)
    Q_PROPERTY(bool rateable READ rateable WRITE setRateable)
    Q_PROPERTY(int panelColumn READ panelColumn WRITE setPanelColumn)
    Q_PROPERTY(int panelRow READ panelRow WRITE setPanelRow)

public:
    Q_INVOKABLE RatingMarkDefinition();

    QSharedPointer<RatingMarkSystem> ratingMarkSystem() const;
    void setRatingMarkSystem(const QSharedPointer<RatingMarkSystem> &ratingMarkSystem);

    QString symbol() const;
    void setSymbol(const QString &symbol);

    qreal valueEquivalent() const;
    void setValueEquivalent(const qreal &valueEquivalent);

    qreal minValue() const;
    void setMinValue(const qreal &minValue);

    qreal percentEquivalent() const;
    void setPercentEquivalent(const qreal &percentEquivalent);

    qreal minPercent() const;
    void setMinPercent(const qreal &minPercent);

    bool rateable() const;
    void setRateable(bool rateable);

    int panelColumn() const;
    void setPanelColumn(int panelColumn);

    int panelRow() const;
    void setPanelRow(int panelRow);

    virtual const QHash<QString, CuteEntityManager::Relation> getRelations() const override;
    virtual InheritanceStrategy getInheritanceStrategy() const override { return InheritanceStrategy::PER_CLASS_TABLE; }


    static bool lessThanPercent(const QSharedPointer<RatingMarkDefinition> &a, const QSharedPointer<RatingMarkDefinition> &b);

protected:
    QSharedPointer<RatingMarkSystem> m_ratingMarkSystem;
    QString m_symbol;
    qreal m_valueEquivalent;
    qreal m_minValue;
    qreal m_percentEquivalent;
    qreal m_minPercent;
    bool m_rateable;
    int m_panelColumn;
    int m_panelRow;
};

#endif // RATINGMARKDEFINITION_H
