#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include "artikel.h"
#include "entitymanager.h"
#include "entityinstancefactory.h"


using namespace CuteEntityManager;
int main(int argc, char *argv[]) {
    Q_UNUSED(argc) Q_UNUSED(argv)
    EntityInstanceFactory::registerClass<Artikel>();
    CuteEntityManager::EntityManager *e = new
    CuteEntityManager::EntityManager("QSQLITE",
                                     QDir::currentPath() + "/db.sqlite");
    EntityInstanceFactory::registerClass<Artikel>();
    QStringList inits = QStringList() << "Artikel";
    e->startup("0.1", inits);
    QSharedPointer<Artikel> a = QSharedPointer<Artikel>(new Artikel(20.0,
                                "Müsli"));
    auto ep = a.objectCast<CuteEntityManager::Entity>();
    qDebug() << e->create(ep, true, true);
    int i = 0;

    while(false); {
        i++;
    }
    qDebug()  << i;

    return 0;
}
