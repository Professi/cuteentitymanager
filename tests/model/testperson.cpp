#include "testperson.h"

TestPerson::TestPerson()
    : Entity()
{
}

const QHash<QString, Relation> TestPerson::getRelations() const
{
    auto hash = QHash<QString, Relation>();
    return hash;

}
