#include "datacreation.h"
#include "ratingmarksystem.h"


DataCreation::DataCreation() {
}

QList<QSharedPointer<Entity>> DataCreation::createRatingEntities() {
    QList<QSharedPointer<Entity>> resultList;
    QSharedPointer<RatingMarkSystem>ratingSystem2;
    ratingSystem2 = QSharedPointer<RatingMarkSystem>(new RatingMarkSystem());
    ratingSystem2->setName("15 bis 0 Punkte als 1+ bis 6");
    ratingSystem2->setPanelColumns(4);
    ratingSystem2->setPanelRows(6);
    ratingSystem2->setValuesComputable(true);
    ratingSystem2->setDigits(0);
    ratingSystem2->setHigherValueBetter(true);
    resultList.append(ratingSystem2);
    QList<QSharedPointer<RatingMarkDefinition>> rateSystem2Definitions;
    QSharedPointer<RatingMarkDefinition>def2_1p;
    def2_1p = QSharedPointer<RatingMarkDefinition>(new RatingMarkDefinition());
    def2_1p->setSymbol("1+");
    def2_1p->setMinValue(14.5);
    def2_1p->setValueEquivalent(15);
    def2_1p->setMinPercent(95);
    def2_1p->setPercentEquivalent(97.5);
    def2_1p->setRateable(true);
    def2_1p->setRatingMarkSystem(ratingSystem2);
    def2_1p->setPanelColumn(1);
    def2_1p->setPanelRow(1);
    resultList.append(def2_1p);
    rateSystem2Definitions.append(resultList.last().objectCast<RatingMarkDefinition>());
    ratingSystem2->setRatingMarkDefinitions(rateSystem2Definitions);
    ratingSystem2->setAdditionalInfo("sys2");
    auto now = QDateTime::currentDateTime();
    ratingSystem2->setBookedAt(now);
    ratingSystem2->setBookedFor(now);
    return resultList;
}
