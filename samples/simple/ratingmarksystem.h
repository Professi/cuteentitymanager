#ifndef RATINGMARKSYSTEM_H
#define RATINGMARKSYSTEM_H

#include "ratingmarkdefinition.h"

class RatingMarkIncident;
////////////////////////////////////////////////
/// \brief The RatingMarkSystem class
///
/// A rating mark system defines a set of rating marks that are able
/// to evaluate the achievement of pupils.
/// Rating marks can base on numbers or plain symbols, they not have to
/// be equidistant, not even ordinal.
///
/// "ratingMarkDefinitions" keeps the actual symbols, values and boundaries
///
/// "valuesComputable" means that intermediate values can be calculated,
/// e.g. 1.3 and 1.0 could be averaged to a value of 1.15.
///
/// "digits" states, how many digits after the decimal point are to be
/// kept and taken into calculation
///
/// "higherValueBetter" is true for a system, where a higher value means
/// a better mark (greater achievement).
///
/// "panelColumns" and "panelRows" give QML information about the layout of the input panel for this system

class RatingMarkSystem : public Incident
{
    Q_OBJECT
    EM_MACRO(RatingMarkSystem)
    Q_PROPERTY(QList<QSharedPointer<RatingMarkDefinition>> ratingMarkDefinitions READ ratingMarkDefinitions WRITE setRatingMarkDefinitions)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(bool valuesComputable READ valuesComputable WRITE setValuesComputable)
    Q_PROPERTY(int digits READ digits WRITE setDigits)
    Q_PROPERTY(bool higherValueBetter READ higherValueBetter WRITE setHigherValueBetter)
    Q_PROPERTY(int panelColumns READ panelColumns WRITE setPanelColumns)
    Q_PROPERTY(int panelRows READ panelRows WRITE setPanelRows)
public:
    Q_INVOKABLE RatingMarkSystem();


    QString name() const;
    void setName(const QString &name);

    QList<QSharedPointer<RatingMarkDefinition> > ratingMarkDefinitions() const;
    void setRatingMarkDefinitions(const QList<QSharedPointer<RatingMarkDefinition> > &ratingMarkDefinitions);

    bool valuesComputable() const;
    void setValuesComputable(bool valuesComputable);

    bool higherValueBetter() const;
    void setHigherValueBetter(bool value);

    int digits() const;
    void setDigits(int value);

    virtual const QHash<QString, CuteEntityManager::Relation> getRelations() const override;
    virtual InheritanceStrategy getInheritanceStrategy() const override { return InheritanceStrategy::PER_CLASS_TABLE; }


    QSharedPointer<RatingMarkDefinition>ratingMarkDefinitionAtPanelPosition(int col, int row);

    int panelColumns() const;
    void setPanelColumns(int panelColumns);

    int panelRows() const;
    void setPanelRows(int panelRows);

    static bool lessThanPercent(const QSharedPointer<RatingMarkIncident> &a, const QSharedPointer<RatingMarkIncident> &b);
    static bool moreThanPercent(const QSharedPointer<RatingMarkIncident> &a, const QSharedPointer<RatingMarkIncident> &b);
    static bool lessThanValue(const QSharedPointer<RatingMarkIncident> &a, const QSharedPointer<RatingMarkIncident> &b);
    static bool moreThanValue(const QSharedPointer<RatingMarkIncident> &a, const QSharedPointer<RatingMarkIncident> &b);
    virtual QList<QSharedPointer<RatingMarkIncident>> sortPercent(QList<QSharedPointer<RatingMarkIncident>> list, Qt::SortOrder sortOrder);
    virtual QList<QSharedPointer<RatingMarkIncident>> sortValue(QList<QSharedPointer<RatingMarkIncident>> list, Qt::SortOrder sortOrder);
    qreal symbolToPercent(QString symbol);
    QString percentToSymbol(qreal percent);
    qreal shortenNumber(qreal nr, int digits, Enums::RoundingOption rounding);
protected:
    QString m_name;
    QList<QSharedPointer<RatingMarkDefinition>> m_ratingMarkDefinitions;
    bool m_valuesComputable = false;
    bool m_higherValueBetter = true;
    int m_digits = -1;
    int m_panelColumns = -1;
    int m_panelRows = -1;
};

#endif // RATINGMARKSYSTEM_H
