#ifndef DATACREATION_H
#define DATACREATION_H

#include <QSharedPointer>

#include "entitymanager.h"
//#include "src/model/persons/group.h"
//#include "src/controller/appcontroller.h"

//class StandardLesson;
//class TimeEntity;
//class CalendarEvent;
//class Room;
//class AppController;
//class AppSeatingData;
//class AppMediaData;

using namespace CuteEntityManager;

class DataCreation
{
public:
    DataCreation();
    static QList<QSharedPointer<Entity>> createRatingEntities();

};

#endif // DATACREATION_H
