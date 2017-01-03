#ifndef STUFF_H
#define STUFF_H

#include "entity.h"

class Stuff {
public:
    Stuff(){}
    template <class T> static QSharedPointer<T> makeTwin(
            QSharedPointer<T> source,
            QDateTime bookedAt,
            bool setPredecessor = true)
    {
        QSharedPointer<T> twin;
        if (source.isNull()) {
            twin = QSharedPointer<T>(new T());
        } else {
            QSharedPointer<Entity> twinEntity = QSharedPointer<Entity>(source->copy());
            twin = twinEntity.objectCast<T>();
        }
        if (twin) {
            twin->setBookedAt(bookedAt);
            if (setPredecessor) {
                twin->setPredecessor(source);
            }
        }
        return twin;
    }
};

#endif // STUFF_H
