#ifndef ENUMS_H
#define ENUMS_H

#include <QObject>
#include <QDate>
#include <QMetaEnum>
#include <QDebug>
#include <QMetaObject>

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * Do NOT change any number assignments, as that might/will
 * invalidate existing dataBases!
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * When creating new types, check for enum doublettes as
 * we do not have strong types in qml - Enums is the
 * common space and the last Enum's number is taken.
 * Better keep numbers synchronized (see
 * DataFieldPosition vs IconPosition)
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * Always do:
 * Q_ENUM beneath class
 * Q_DECLARE_METATYPE (see below) for QML<->C++ (slots/invokables)
 * qRegisterMetaType (main.cpp) for QML<->C++ (slots/invokables)
 * (Registration for use in QML is already done by qmlRegisterType<Enums>)
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */
class Enums: public QObject
{
    Q_OBJECT

public:
    static constexpr qreal EPSILON_CALCULATION = 0.001;
    static constexpr qreal EPSILON_SCREEN = 0.001;

    enum class Gender {
        MALE = 0,
        FEMALE = 1,
        UNKNOWNGENDER = -1
    };
    Q_ENUM(Gender)

    enum class IncidentRetrievalPolicy {
        NEW_PER_LESSON = 1,         // if recent: return same Incident, else: create new (entirely)
                                    //      (Example: "Attendance" App)
        CHANGE_PER_LESSON = 2,      // if recent: return same Incident, else: clone a new (based on last)
                                    //      (Example: cycling "Status" App)
        NEW = 3,                    // create a new (entirely), allows multiple entries per lesson
                                    //      (Example: grading multiple contributions with "Grade" App)
        CHANGE = 4                  // clone a new (based on last), allows logging of multiple changes per lesson
                                    //      (Example: logging disturbances with a "count" App)
                                    //      (unsuitable for cyclic status apps)
///@todo        SINGLETON = 5               // only one Incident per pupil and group shall exist.
    };
    Q_ENUM(IncidentRetrievalPolicy)

    enum class AttendanceState {
        PRESENT=1,
        MISSING=2,
        LATE=3,
        ATSCHOOL=4,
        UNDEFINED=-1
    };
    Q_ENUM(AttendanceState)

//    enum class CalendarEventType {
//        STANDARDLESSON=0,
//        LESSON=1,
//        SCHOOLPERSONAL=2,
//        SCHOOLGENERAL=3,
//        PERSONAL=4
//    };
//    Q_ENUM(CalendarEventType)
    enum class CalendarPlacementResult {
        OFFBEFORE=-1,
        OFFAFTER=-2,
        FITSIN=0,
        CUTATSTART=1,
        CUTATEND=2,
        CUTATBOTH=3
    };
    Q_ENUM(CalendarPlacementResult)

    enum class DayOfWeek {
        SUNDAY=0,
        MONDAY=1,
        TUESDAY=2,
        WEDNESDAY=3,
        THURSDAY=4,
        FRIDAY=5,
        SATURDAY=6,
        UNDEFINED=-1
    };
    Q_ENUM(DayOfWeek)

    enum class Orientation {
        LANDSCAPE,
        PORTRAIT,
        LANDSCAPE_180,
        PORTRAIT_180
    };
    Q_ENUM(Orientation)

    enum class NameOrder {
        FIRST_FAMILY=0,
        FAMILY_FIRST=1
    };
    Q_ENUM(NameOrder)

    enum class AppMode {
        SEATINGPLAN=1,
        TABLE=2,
        CALENDAR=3,
        SPECIAL=0,
        UNDEFINED=-1
    }; //APPBUTTONS,GROUPBUTTONS,ROOMEDIT,SEATEDIT, SCHEDULE
    Q_ENUM(AppMode)

    enum class AppType {
        NOAPP=-1,
        ATTENDANCE=1,
        HOMEWORK=2,
        RATING=3,
        STATUS=4,
        CHECKLIST=5,
        GROUPS=6,
        APPS=7,
        ROOMS=8,
        SEATS=9,
        COUNT=10,
        BASEDATA=11,
        SCHEDULE=12,
        GRADES=13,
        MEDIA=14

    };
    Q_ENUM(AppType)

    enum class ToolType {
        UNDEFINED=-1,
        RANDOM_PUPIL=0,
        ADD_MEDIA=1,
        TOGGLE_RASTER=2,
    };
    Q_ENUM(ToolType)

    enum class DataFieldPosition {
        // always keep numbers synchronized with IconPosition,
        // as in qml mix-up confusion is possible (not strongly typed there)

        // ordinality is important. These fields are being iterated!
        TOP_LEFT=0,
        TOP=1,
        TOP_RIGHT=2,
        UPPER_LEFT=3,
        UPPER=4,
        UPPER_RIGHT=5,
        LOWER_LEFT=6,
        LOWER=7,
        LOWER_RIGHT=8,
        BOTTOM_LEFT=9,
        BOTTOM=10,
        BOTTOM_RIGHT=11,
        CENTER=12
    };
    Q_ENUM(Enums::DataFieldPosition)

    enum class IconPosition {
        // always keep numbers synchronized with DataFieldPosition,
        // as in qml mix-up confusion is possible (not strongly typed there)
        TOP_LEFT=0,
//        TOP=1,
        TOP_RIGHT=2,
//        UPPER_LEFT=3,
//        UPPER=4,
//        UPPER_RIGHT=5,
//        LOWER_LEFT=6,
//        LOWER=7,
//        LOWER_RIGHT=8,
        BOTTOM_LEFT=9,
//        BOTTOM=10,
        BOTTOM_RIGHT=11,
//        CENTER=12


    };
    Q_ENUM(IconPosition)

    enum class RecurrencePatternType {
        DAILY=0,
        WEEKLY=1,
        ABSOLUTEMONTHLY=2,
        RELATIVEMONTHLY=3,
        ABSOLUTEYEARLY=4,
        RELATIVEYEARLY=5
    };
    Q_ENUM(RecurrencePatternType)

    enum class RecurrenceRangeType {
        ENDDATE=0,
        NOEND=1,
        NUMBERED=2
    };
    Q_ENUM(RecurrenceRangeType)

    enum class ShadowPosition {
        TOP_LEFT_SHADOW=0,
        TOP_RIGHT_SHADOW=1,
        BOTTOM_LEFT_SHADOW=2,
        BOTTOM_RIGHT_SHADOW=3,
        INVALID_SHADOW=-1
    };
    Q_ENUM(ShadowPosition)

    enum class WeekIndex {
        FIRST=0,
        SECOND=1,
        THIRD=2,
        FOURTH=3,
        LAST=4
    };
    Q_ENUM(WeekIndex)

    enum class RoundingOption {
        ROUND = 0,
        CEILING = 1,
        FLOOR = 2
    };
    Q_ENUM(RoundingOption)


    enum class RandomPersonMode {
        UNDEFINED = -1,
        FREE_RANDOM = 0,
        ONLY_ONCE = 1,
        ONLY_ONCE_BEFORE_SECOND = 2,
        WEIGHED_RANDOM = 3
    };
    Q_ENUM(RandomPersonMode)

//    enum class RatingMarkIntendedEntry {
//        VALUE=0,
//        SYMBOL=1,
//        PERCENT=2,
//        UNRATEABLE=3,
//        UNDEFINED=-1
//    };
//    Q_ENUM(RatingMarkIntendedEntry)

    static DayOfWeek dayOfWeek(QDate date) {
        Q_ASSERT(date.isValid());
        if (!date.isValid()) {
             return DayOfWeek::UNDEFINED;
        }
        switch (date.dayOfWeek()) {
            case 1: return DayOfWeek::MONDAY;
        case 2: return DayOfWeek::TUESDAY;
        case 3: return DayOfWeek::WEDNESDAY;
        case 4: return DayOfWeek::THURSDAY;
        case 5: return DayOfWeek::FRIDAY;
        case 6: return DayOfWeek::SATURDAY;
        case 7: return DayOfWeek::SUNDAY;
        default: return DayOfWeek::UNDEFINED;
        }

    }

    static QMap<int, QString> toGenericStringMap(QString enumClassName) {
        QMap<int, QString> resultMap;
        const QMetaObject &mo = Enums::staticMetaObject;
        int index = mo.indexOfEnumerator(enumClassName.toLocal8Bit());
        QMetaEnum metaEnum = mo.enumerator(index);
        //Enums::AttendanceState test = Enums::AttendanceState::UNDEFINED;
        //QString enumString = metaEnum.valueToKey(static_cast<int>(test));
        for (int i=0; i<metaEnum.keyCount();i++) {
            resultMap.insert(metaEnum.value(i),metaEnum.key(i));
        }
        return resultMap;
    }

    template<class T>
    static QMap<int, QString> toStringMap(QString enumClassName, bool omitValuesUnderZero = false) {
        QMap<int, QString> resultMap;
        const QMetaObject &mo = Enums::staticMetaObject;
        int index = mo.indexOfEnumerator(enumClassName.toLocal8Bit());
        QMetaEnum metaEnum = mo.enumerator(index);
        try {
            for (int i=0; i<metaEnum.keyCount();i++) {
                if (metaEnum.value(i) >= 0 || !omitValuesUnderZero) {
                    T instance = static_cast<T>(metaEnum.value(i));
                    resultMap.insert(metaEnum.value(i),toString(instance));
                }
            }
        } catch (...) {
            resultMap.clear();
        }
        Q_ASSERT (!resultMap.isEmpty());
        return resultMap;
    }
};
Q_DECLARE_METATYPE(Enums::AttendanceState)
Q_DECLARE_METATYPE(Enums::Orientation)
Q_DECLARE_METATYPE(Enums::AppMode)
Q_DECLARE_METATYPE(Enums::AppType)
Q_DECLARE_METATYPE(Enums::DataFieldPosition)
Q_DECLARE_METATYPE(Enums::IconPosition)
Q_DECLARE_METATYPE(Enums::ShadowPosition)
Q_DECLARE_METATYPE(Enums::Gender)
Q_DECLARE_METATYPE(Enums::ToolType)
Q_DECLARE_METATYPE(Enums::RandomPersonMode)

inline Enums::DayOfWeek &operator++( Enums::DayOfWeek &d, int ) {
    if (d == Enums::DayOfWeek::UNDEFINED) {
        return d;
    }
    int nr = static_cast<int>(d) + 1;
    if (nr > 6) {
        nr = 0;
    }
    d = static_cast<Enums::DayOfWeek>(nr);
  return d;
}

inline QString toString(Enums::DayOfWeek day, int limitLength=0) {
    if (limitLength == 0) {
        limitLength=100;
    }
    switch (day) {
        case Enums::DayOfWeek::MONDAY: return(QString("Montag").left(limitLength));
        case Enums::DayOfWeek::TUESDAY: return(QString("Dienstag").left(limitLength));
        case Enums::DayOfWeek::WEDNESDAY: return(QString("Mittwoch").left(limitLength));
        case Enums::DayOfWeek::THURSDAY: return(QString("Donnerstag").left(limitLength));
        case Enums::DayOfWeek::FRIDAY: return(QString("Freitag").left(limitLength));
        case Enums::DayOfWeek::SATURDAY: return(QString("Samstag").left(limitLength));
        case Enums::DayOfWeek::SUNDAY: return(QString("Sonntag").left(limitLength));
    default:
        return QString();
    }
}
inline QString toString(Enums::AppType appType, int limitLength=0) {
    if (limitLength == 0) {
        limitLength=100;
    }
    switch (appType) {
        case Enums::AppType::NOAPP: return(QString("Keine App").left(limitLength));
        case Enums::AppType::ATTENDANCE: return(QString("Anwesenheit").left(limitLength));
        case Enums::AppType::HOMEWORK: return(QString("Hausaufgaben").left(limitLength));
        case Enums::AppType::RATING: return(QString("Bewertung").left(limitLength));
        case Enums::AppType::STATUS: return(QString("Status").left(limitLength));
        case Enums::AppType::CHECKLIST: return(QString("Checkliste").left(limitLength));
        case Enums::AppType::GROUPS: return(QString("Gruppen").left(limitLength));
        case Enums::AppType::APPS: return(QString("Apps").left(limitLength));
        case Enums::AppType::ROOMS: return(QString("Raumbau").left(limitLength));
        case Enums::AppType::SEATS: return(QString("Sitzplan").left(limitLength));
        case Enums::AppType::COUNT: return(QString("Zählen").left(limitLength));
        case Enums::AppType::BASEDATA: return(QString("Basisdaten").left(limitLength));
        case Enums::AppType::SCHEDULE: return(QString("Termine").left(limitLength));
        case Enums::AppType::GRADES: return(QString("Zensuren").left(limitLength));
        case Enums::AppType::MEDIA: return(QString("Medien").left(limitLength));
    default:
        return QString();
    }
}

inline QString toString(Enums::AttendanceState state) {
    switch (state) {
    case Enums::AttendanceState::ATSCHOOL: return(QString("Schulisch abwesend"));
    case Enums::AttendanceState::LATE: return(QString("Verspätet"));
    case Enums::AttendanceState::MISSING: return(QString("Fehlstunde(n)"));
    case Enums::AttendanceState::PRESENT: return(QString("Anwesend"));
    case Enums::AttendanceState::UNDEFINED: return(QString("Nicht definiert"));
    default:
        return QString();
    }
}

template <class T> inline T fromString(QString stateString, QString className) {
    const QMetaObject &mo = Enums::staticMetaObject;
    int index = mo.indexOfEnumerator(className.toLocal8Bit()); // watch out during refactorings
    QMetaEnum metaEnum = mo.enumerator(index);
    for (int i = 0; i < metaEnum.keyCount(); i++) {
        int val = metaEnum.value(i);
        T enumVal = static_cast<T>(val);
        if (toString(enumVal) == stateString) {
            return enumVal;
        }
    }
    return static_cast<T>(-1);;
}

#endif // ENUMS_H
