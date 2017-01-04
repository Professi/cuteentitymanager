#ifndef RATINGMARKINCIDENT_H
#define RATINGMARKINCIDENT_H

#include <QObject>

#include "incident.h"
#include "ratingmarksystem.h"

class AppData;
class RatingMarkIncident : public Incident
{
    Q_OBJECT
    EM_MACRO(RatingMarkIncident)
    Q_PROPERTY(QString symbol READ symbol WRITE setSymbol)
    Q_PROPERTY(qreal value READ value WRITE setValue)
    Q_PROPERTY(qreal percentValue READ percentValue WRITE setPercentValue)
    Q_PROPERTY(qreal weight READ weight WRITE setWeight)
    Q_PROPERTY(bool rateable READ rateable WRITE setRateable)
    Q_PROPERTY(bool signatureNeeded READ signatureNeeded WRITE setSignatureNeeded)
    // ratingMarkSystem scheint auf den ersten Blick ein Duplikat zu sein, da man es aus AppData
    // (zu AppRatingData gecastet) ermitteln könnte. In der TimeMachine ist es jedoch wichtig, dass
    // bei einem für die App geänderten RatingMarkSystem ein alter RatingMarkIncident noch sein
    // ursprüngliches RatingMarkSystem kennt.
    Q_PROPERTY(QSharedPointer<RatingMarkSystem> ratingMarkSystem READ ratingMarkSystem WRITE setRatingMarkSystem)
public:
    Q_INVOKABLE RatingMarkIncident();

    QString symbol() const;
    void setSymbol(const QString &symbol);

    qreal value() const;
    void setValue(const qreal &value);

    qreal percentValue() const;
    void setPercentValue(const qreal &percentValue);

    qreal weight() const;
    void setWeight(const qreal &weight);

    bool rateable() const;
    void setRateable(bool rateable);

    virtual const QHash<QString, CuteEntityManager::Relation> getRelations() const override;
    virtual InheritanceStrategy getInheritanceStrategy() const override { return InheritanceStrategy::PER_CLASS_TABLE; }

    QSharedPointer<RatingMarkSystem> ratingMarkSystem() const;
    void setRatingMarkSystem(const QSharedPointer<RatingMarkSystem> &ratingMarkSystem);

    bool signatureNeeded() const;
    void setSignatureNeeded(bool signatureNeeded);

protected:
    QString m_symbol = QString();
    qreal m_value = 0;
    qreal m_percentValue = 0;
    qreal m_weight = 1;
    bool m_rateable = true;
    bool m_signatureNeeded = false;
    QSharedPointer<RatingMarkSystem> m_ratingMarkSystem = QSharedPointer<RatingMarkSystem>();
};

#endif // RATINGMARK_H
