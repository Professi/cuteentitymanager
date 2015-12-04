#include <QtTest>
#include "tst_em.h"
#include "tst_querybuilder.h"

int main(int argc, char** argv) {
    EmTest em;
    QuerybuilderTest queryBuilderTest;
    return QTest::qExec(&em, argc, argv) |
           QTest::qExec(&queryBuilderTest, argc, argv);
}
