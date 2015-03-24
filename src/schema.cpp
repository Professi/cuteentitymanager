#include "schema.h"
using namespace CuteEntityManager;

Schema::Schema() {
    this->typeMap = QSharedPointer<QHash<QString,QString>>(new QHash<QString,QString>());
}

Schema::~Schema() {

}

