#include "datacreation.h"
#include "ratingmarksystem.h"


DataCreation::DataCreation()
{

}

QList<QSharedPointer<Entity> > DataCreation::createRatingEntities()
{
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

    QSharedPointer<RatingMarkDefinition>def2_1;
    def2_1 = QSharedPointer<RatingMarkDefinition>(new RatingMarkDefinition());
    def2_1->setSymbol("1");
    def2_1->setMinValue(13.5);
    def2_1->setValueEquivalent(14);
    def2_1->setMinPercent(90);
    def2_1->setPercentEquivalent(92.5);
    def2_1->setRateable(true);
    def2_1->setRatingMarkSystem(ratingSystem2);
    def2_1->setPanelColumn(2);
    def2_1->setPanelRow(1);
    resultList.append(def2_1);
    rateSystem2Definitions.append(resultList.last().objectCast<RatingMarkDefinition>());

    QSharedPointer<RatingMarkDefinition>def2_1m;
    def2_1m = QSharedPointer<RatingMarkDefinition>(new RatingMarkDefinition());
    def2_1m->setSymbol("1-");
    def2_1m->setMinValue(12.5);
    def2_1m->setValueEquivalent(13);
    def2_1m->setMinPercent(85);
    def2_1m->setPercentEquivalent(87.5);
    def2_1m->setRateable(true);
    def2_1m->setRatingMarkSystem(ratingSystem2);
    def2_1m->setPanelColumn(3);
    def2_1m->setPanelRow(1);
    resultList.append(def2_1m);
    rateSystem2Definitions.append(resultList.last().objectCast<RatingMarkDefinition>());

    QSharedPointer<RatingMarkDefinition>def2_2p;
    def2_2p = QSharedPointer<RatingMarkDefinition>(new RatingMarkDefinition());
    def2_2p->setSymbol("2+");
    def2_2p->setMinValue(11.5);
    def2_2p->setValueEquivalent(12);
    def2_2p->setMinPercent(80);
    def2_2p->setPercentEquivalent(82.5);
    def2_2p->setRateable(true);
    def2_2p->setRatingMarkSystem(ratingSystem2);
    def2_2p->setPanelColumn(1);
    def2_2p->setPanelRow(2);
    resultList.append(def2_2p);
    rateSystem2Definitions.append(resultList.last().objectCast<RatingMarkDefinition>());

    QSharedPointer<RatingMarkDefinition>def2_2;
    def2_2 = QSharedPointer<RatingMarkDefinition>(new RatingMarkDefinition());
    def2_2->setSymbol("2");
    def2_2->setMinValue(10.5);
    def2_2->setValueEquivalent(11);
    def2_2->setMinPercent(75);
    def2_2->setPercentEquivalent(77.5);
    def2_2->setRateable(true);
    def2_2->setRatingMarkSystem(ratingSystem2);
    def2_2->setPanelColumn(2);
    def2_2->setPanelRow(2);
    resultList.append(def2_2);
    rateSystem2Definitions.append(resultList.last().objectCast<RatingMarkDefinition>());

    QSharedPointer<RatingMarkDefinition>def2_2m;
    def2_2m = QSharedPointer<RatingMarkDefinition>(new RatingMarkDefinition());
    def2_2m->setSymbol("2-");
    def2_2m->setMinValue(9.5);
    def2_2m->setValueEquivalent(10);
    def2_2m->setMinPercent(70);
    def2_2m->setPercentEquivalent(72.5);
    def2_2m->setRateable(true);
    def2_2m->setRatingMarkSystem(ratingSystem2);
    def2_2m->setPanelColumn(3);
    def2_2m->setPanelRow(2);
    resultList.append(def2_2m);
    rateSystem2Definitions.append(resultList.last().objectCast<RatingMarkDefinition>());

    QSharedPointer<RatingMarkDefinition>def2_3p;
    def2_3p = QSharedPointer<RatingMarkDefinition>(new RatingMarkDefinition());
    def2_3p->setSymbol("3+");
    def2_3p->setMinValue(8.5);
    def2_3p->setValueEquivalent(9);
    def2_3p->setMinPercent(65);
    def2_3p->setPercentEquivalent(67.5);
    def2_3p->setRateable(true);
    def2_3p->setRatingMarkSystem(ratingSystem2);
    def2_3p->setPanelColumn(1);
    def2_3p->setPanelRow(3);
    resultList.append(def2_3p);
    rateSystem2Definitions.append(resultList.last().objectCast<RatingMarkDefinition>());

    QSharedPointer<RatingMarkDefinition>def2_3;
    def2_3 = QSharedPointer<RatingMarkDefinition>(new RatingMarkDefinition());
    def2_3->setSymbol("3");
    def2_3->setMinValue(7.5);
    def2_3->setValueEquivalent(8);
    def2_3->setMinPercent(60);
    def2_3->setPercentEquivalent(62.5);
    def2_3->setRateable(true);
    def2_3->setRatingMarkSystem(ratingSystem2);
    def2_3->setPanelColumn(2);
    def2_3->setPanelRow(3);
    resultList.append(def2_3);
    rateSystem2Definitions.append(resultList.last().objectCast<RatingMarkDefinition>());

    QSharedPointer<RatingMarkDefinition>def2_3m;
    def2_3m = QSharedPointer<RatingMarkDefinition>(new RatingMarkDefinition());
    def2_3m->setSymbol("3-");
    def2_3m->setMinValue(6.5);
    def2_3m->setValueEquivalent(7);
    def2_3m->setMinPercent(55);
    def2_3m->setPercentEquivalent(57.5);
    def2_3m->setRateable(true);
    def2_3m->setRatingMarkSystem(ratingSystem2);
    def2_3m->setPanelColumn(3);
    def2_3m->setPanelRow(3);
    resultList.append(def2_3m);
    rateSystem2Definitions.append(resultList.last().objectCast<RatingMarkDefinition>());

    QSharedPointer<RatingMarkDefinition>def2_4p;
    def2_4p = QSharedPointer<RatingMarkDefinition>(new RatingMarkDefinition());
    def2_4p->setSymbol("4+");
    def2_4p->setMinValue(5.5);
    def2_4p->setValueEquivalent(6);
    def2_4p->setMinPercent(50);
    def2_4p->setPercentEquivalent(52.5);
    def2_4p->setRateable(true);
    def2_4p->setRatingMarkSystem(ratingSystem2);
    def2_4p->setPanelColumn(1);
    def2_4p->setPanelRow(4);
    resultList.append(def2_4p);
    rateSystem2Definitions.append(resultList.last().objectCast<RatingMarkDefinition>());

    QSharedPointer<RatingMarkDefinition>def2_4;
    def2_4 = QSharedPointer<RatingMarkDefinition>(new RatingMarkDefinition());
    def2_4->setSymbol("4");
    def2_4->setMinValue(4.5);
    def2_4->setValueEquivalent(5);
    def2_4->setMinPercent(45);
    def2_4->setPercentEquivalent(47.5);
    def2_4->setRateable(true);
    def2_4->setRatingMarkSystem(ratingSystem2);
    def2_4->setPanelColumn(2);
    def2_4->setPanelRow(4);
    resultList.append(def2_4);
    rateSystem2Definitions.append(resultList.last().objectCast<RatingMarkDefinition>());

    QSharedPointer<RatingMarkDefinition>def2_4m;
    def2_4m = QSharedPointer<RatingMarkDefinition>(new RatingMarkDefinition());
    def2_4m->setSymbol("4-");
    def2_4m->setMinValue(3.5);
    def2_4m->setValueEquivalent(4);
    def2_4m->setMinPercent(39);
    def2_4m->setPercentEquivalent(42);
    def2_4m->setRateable(true);
    def2_4m->setRatingMarkSystem(ratingSystem2);
    def2_4m->setPanelColumn(3);
    def2_4m->setPanelRow(4);
    resultList.append(def2_4m);
    rateSystem2Definitions.append(resultList.last().objectCast<RatingMarkDefinition>());

    QSharedPointer<RatingMarkDefinition>def2_5p;
    def2_5p = QSharedPointer<RatingMarkDefinition>(new RatingMarkDefinition());
    def2_5p->setSymbol("5+");
    def2_5p->setMinValue(2.5);
    def2_5p->setValueEquivalent(3);
    def2_5p->setMinPercent(33);
    def2_5p->setPercentEquivalent(36);
    def2_5p->setRateable(true);
    def2_5p->setRatingMarkSystem(ratingSystem2);
    def2_5p->setPanelColumn(1);
    def2_5p->setPanelRow(5);
    resultList.append(def2_5p);
    rateSystem2Definitions.append(resultList.last().objectCast<RatingMarkDefinition>());

    QSharedPointer<RatingMarkDefinition>def2_5;
    def2_5 = QSharedPointer<RatingMarkDefinition>(new RatingMarkDefinition());
    def2_5->setSymbol("5");
    def2_5->setMinValue(1.5);
    def2_5->setValueEquivalent(2);
    def2_5->setMinPercent(27);
    def2_5->setPercentEquivalent(30);
    def2_5->setRateable(true);
    def2_5->setRatingMarkSystem(ratingSystem2);
    def2_5->setPanelColumn(2);
    def2_5->setPanelRow(5);
    resultList.append(def2_5);
    rateSystem2Definitions.append(resultList.last().objectCast<RatingMarkDefinition>());

    QSharedPointer<RatingMarkDefinition>def2_5m;
    def2_5m = QSharedPointer<RatingMarkDefinition>(new RatingMarkDefinition());
    def2_5m->setSymbol("5-");
    def2_5m->setMinValue(0.5);
    def2_5m->setValueEquivalent(1);
    def2_5m->setMinPercent(20);
    def2_5m->setPercentEquivalent(23.5);
    def2_5m->setRateable(true);
    def2_5m->setRatingMarkSystem(ratingSystem2);
    def2_5m->setPanelColumn(3);
    def2_5m->setPanelRow(5);
    resultList.append(def2_5m);
    rateSystem2Definitions.append(resultList.last().objectCast<RatingMarkDefinition>());

    QSharedPointer<RatingMarkDefinition>def2_6;
    def2_6 = QSharedPointer<RatingMarkDefinition>(new RatingMarkDefinition());
    def2_6->setSymbol("6");
    def2_6->setMinValue(0);
    def2_6->setValueEquivalent(0);
    def2_6->setMinPercent(0);
    def2_6->setPercentEquivalent(10);
    def2_6->setRateable(true);
    def2_6->setRatingMarkSystem(ratingSystem2);
    def2_6->setPanelColumn(0);
    def2_6->setPanelRow(5);
    resultList.append(def2_6);
    rateSystem2Definitions.append(resultList.last().objectCast<RatingMarkDefinition>());

    QSharedPointer<RatingMarkDefinition>def2_NotRated;
    def2_NotRated = QSharedPointer<RatingMarkDefinition>(new RatingMarkDefinition());
    def2_NotRated->setSymbol("NB");
    def2_NotRated->setMinValue(9999);
    def2_NotRated->setValueEquivalent(9999);
    def2_NotRated->setMinPercent(9999);
    def2_NotRated->setPercentEquivalent(9999);
    def2_NotRated->setRateable(false);
    def2_NotRated->setRatingMarkSystem(ratingSystem2);
    def2_NotRated->setPanelColumn(0);
    def2_NotRated->setPanelRow(4);
    resultList.append(def2_NotRated);
    rateSystem2Definitions.append(resultList.last().objectCast<RatingMarkDefinition>());

    ratingSystem2->setRatingMarkDefinitions(rateSystem2Definitions);




//    QSharedPointer<AppRatingData>appRatingData = QSharedPointer<AppRatingData>(new AppRatingData());
//    appRatingData->setRatingMarkSystem(ratingSystem2);
//    appRatingData->setIconName("ratingIcon.svg");
//    appRatingData->setAllowMultipleRatingsPerLesson(true);

//    appRatingData->setName("Bewertung1-6");
//    appRatingData->setTeachersDeskPosition(4);
//    resultList.append(appRatingData);


    ratingSystem2->setAdditionalInfo("sys2");
    auto now = QDateTime::currentDateTime();
    ratingSystem2->setBookedAt(now);
    ratingSystem2->setBookedFor(now);

    return resultList;



}
