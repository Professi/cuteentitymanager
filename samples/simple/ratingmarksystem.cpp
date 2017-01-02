#include "ratingmarksystem.h"
#include "ratingmarkincident.h"
#include "occasion.h"

#include <QDebug>
#include <QtMath>

RatingMarkSystem::RatingMarkSystem()
{

}

QString RatingMarkSystem::name() const
{
    return m_name;
}

void RatingMarkSystem::setName(const QString &name)
{
    m_name = name;
}

QList<QSharedPointer<RatingMarkDefinition> > RatingMarkSystem::ratingMarkDefinitions() const
{
    return m_ratingMarkDefinitions;
}

void RatingMarkSystem::setRatingMarkDefinitions(const QList<QSharedPointer<RatingMarkDefinition> > &ratingMarkDefinitions)
{
    m_ratingMarkDefinitions = ratingMarkDefinitions;
}

bool RatingMarkSystem::valuesComputable() const
{
    return m_valuesComputable;
}

void RatingMarkSystem::setValuesComputable(bool valuesComputable)
{
    m_valuesComputable = valuesComputable;
}

bool RatingMarkSystem::higherValueBetter() const
{
    return m_higherValueBetter;
}

void RatingMarkSystem::setHigherValueBetter(bool value)
{
    m_higherValueBetter = value;
}

int RatingMarkSystem::digits() const
{
    return m_digits;
}

void RatingMarkSystem::setDigits(int value)
{
    m_digits = value;
}

const QHash<QString, Relation> RatingMarkSystem::getRelations() const
{
        auto hash = Incident::getRelations();
        hash.insert("ratingMarkDefinitions",Relation("ratingMarkDefinitions",CuteEntityManager::RelationType::ONE_TO_MANY,QString("ratingMarkSystem")));

        return hash;
}

QSharedPointer<RatingMarkDefinition> RatingMarkSystem::ratingMarkDefinitionAtPanelPosition(int col, int row)
{
    for (int i = 0; i < this->ratingMarkDefinitions().count(); i++) {
        QSharedPointer<RatingMarkDefinition> rmd = this->ratingMarkDefinitions().at(i);
        if (rmd->panelColumn() == col) {
            if (rmd->panelRow() == row) {
                return rmd;
            }
        }
    }
    return QSharedPointer<RatingMarkDefinition>();
}

int RatingMarkSystem::panelColumns() const
{
    return m_panelColumns;
}

void RatingMarkSystem::setPanelColumns(int panelColumns)
{
    m_panelColumns = panelColumns;
}

int RatingMarkSystem::panelRows() const
{
    return m_panelRows;
}

void RatingMarkSystem::setPanelRows(int panelRows)
{
    m_panelRows = panelRows;
}

bool RatingMarkSystem::lessThanPercent(const QSharedPointer<RatingMarkIncident> &a, const QSharedPointer<RatingMarkIncident> &b)
{
    return a->percentValue() < b->percentValue();
}
bool RatingMarkSystem::moreThanPercent(const QSharedPointer<RatingMarkIncident> &a, const QSharedPointer<RatingMarkIncident> &b)
{
    return a->percentValue() > b->percentValue();
}
bool RatingMarkSystem::lessThanValue(const QSharedPointer<RatingMarkIncident> &a, const QSharedPointer<RatingMarkIncident> &b)
{
    return a->value() < b->value();
}
bool RatingMarkSystem::moreThanValue(const QSharedPointer<RatingMarkIncident> &a, const QSharedPointer<RatingMarkIncident> &b)
{
    return a->value() > b->value();
}
QList<QSharedPointer<RatingMarkIncident> > RatingMarkSystem::sortPercent(QList<QSharedPointer<RatingMarkIncident> > list, Qt::SortOrder sortOrder)
{
    if (sortOrder == Qt::AscendingOrder) {
        std::sort(list.begin(),list.end(),RatingMarkSystem::lessThanPercent);
    } else {
        std::sort(list.begin(),list.end(),RatingMarkSystem::moreThanPercent);
    }
    return list;
}

QList<QSharedPointer<RatingMarkIncident> > RatingMarkSystem::sortValue(QList<QSharedPointer<RatingMarkIncident> > list, Qt::SortOrder sortOrder)
{
    if (sortOrder == Qt::AscendingOrder) {
        std::sort(list.begin(),list.end(),RatingMarkSystem::lessThanValue);
    } else {
        std::sort(list.begin(),list.end(),RatingMarkSystem::moreThanValue);
    }
    return list;
}

bool RatingMarkSystem::shallBeCalculated(QSharedPointer<RatingMarkIncident> inc, QSharedPointer<Occasion> occasion, bool respectRateabilityProperty) {
    if (!occasion.isNull() && (occasion != inc->occasion())) {
        return false;
    }
    if (respectRateabilityProperty && !inc->rateable()) {
        return false;
    }
    return true;

}

qreal RatingMarkSystem::averageSomeFloatProperty(QList<QSharedPointer<RatingMarkIncident> > list,
                                                 QString propertyName,
                                                 QSharedPointer<Occasion> occasion,
                                                 int digits,
                                                 Enums::RoundingOption rounding,
                                                 bool respectWeight,
                                                 bool respectRateabilityProperty)
{
    qreal sum = 0;
    qreal weightSum = 0;
    QListIterator<QSharedPointer<RatingMarkIncident> > iter(list);
    bool ok = true;

    while (ok && iter.hasNext()) {
        QSharedPointer<RatingMarkIncident> inc = iter.next();
        qreal addValue;
        QVariant var = inc->getProperty(propertyName);
        if (var.isValid() && !var.isNull()) {
            addValue = var.toFloat(&ok);
            if (!ok) {
                qDebug()<<"RatingMarkSystem::averageSomeFloatProperty:  Float conversion of "<<propertyName<<" was not successful. ";
            }
        } else {
            ok = false;
            qDebug()<<"RatingMarkSystem::averageSomeFloatProperty:  "<<propertyName<<" was not found - typo?";
        }
        if (ok && this->shallBeCalculated(inc, occasion, respectRateabilityProperty)) {
            qreal weight = respectWeight ? inc->weight() : 1;
            if (weight < -Enums::EPSILON_CALCULATION) {
                ok = true;
            }
            sum += weight * addValue;
            weightSum += weight;
        }
    }
    Q_ASSERT(ok);
    return !ok? -1 : ((qAbs(weightSum) < Enums::EPSILON_CALCULATION)? -1 : this->shortenNumber(sum / weightSum, digits, rounding));
}

qreal RatingMarkSystem::averagePercent(const QList<QSharedPointer<RatingMarkIncident> > list,
                                       QSharedPointer<Occasion> occasion,
                                       int digits,
                                       Enums::RoundingOption rounding,
                                       bool respectWeight,
                                       bool respectRateabilityProperty)
{
    return this->averageSomeFloatProperty(list,"percentValue", occasion, digits, rounding, respectWeight, respectRateabilityProperty);
}

qreal RatingMarkSystem::averageValueSimple(QList<QSharedPointer<RatingMarkIncident> > list,
                                           QSharedPointer<Occasion> occasion,
                                           int digits,
                                           Enums::RoundingOption rounding,
                                           bool respectWeight,
                                           bool respectRateabilityProperty)
{
    return this->averageSomeFloatProperty(list,"value", occasion, digits, rounding, respectWeight, respectRateabilityProperty);
}

qreal RatingMarkSystem::symbolToPercent(QString symbol)
{
    QListIterator<QSharedPointer<RatingMarkDefinition>>iter (this->ratingMarkDefinitions());
    bool found = false;
    QSharedPointer<RatingMarkDefinition> def;
    while (!found && iter.hasNext()) {
        def = iter.next();
        if (def->symbol() == symbol) {
            found = true;
        }
    }
    return found? def->percentEquivalent() : -1;
}

QString RatingMarkSystem::percentToSymbol(qreal percent)
{
    QListIterator<QSharedPointer<RatingMarkDefinition>>iter (this->ratingMarkDefinitions());
    QSharedPointer<RatingMarkDefinition> candidate;
    while (iter.hasNext()) {
       QSharedPointer<RatingMarkDefinition> def;
       def = iter.next();
        if (def->minPercent() <= percent){
            if (candidate.isNull()) {
                candidate = def;
            } else {
                if (def->minPercent() > candidate->minPercent()) {
                    candidate = def;
                }
            }
        }

    }
    return candidate.isNull()? QString() : candidate->symbol();
}

qreal RatingMarkSystem::shortenNumber(qreal nr, int digits, Enums::RoundingOption rounding)
{
    if (digits >= 0) {
        int factor = 1;
        if (digits > 0) {
            factor = qPow(10, digits);
            nr *= factor;
        }
        qDebug()<<"Factor: "<<factor;
        switch (rounding) {
        case Enums::RoundingOption::ROUND:
            nr = qRound(nr);
            break;
        case Enums::RoundingOption::CEILING:
            nr = qCeil(nr);
            break;
        case Enums::RoundingOption::FLOOR:
            nr = qFloor(nr);
            break;
        }
        if (digits > 0) {
            nr /= factor;
        }
    }
    return nr;
}



