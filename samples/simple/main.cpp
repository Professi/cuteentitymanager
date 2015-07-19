#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include "artikel.h"
#include "../../src/entitymanager.h"
#include "../../src/entityinstancefactory.h"
/**
  * create,remove und merge funktionieren
 */
using namespace CuteEntityManager;
int main(int argc, char *argv[]) {
    Q_UNUSED(argc) Q_UNUSED(argv)
    EntityInstanceFactory::registerClass<Artikel>();
    CuteEntityManager::EntityManager *e = new
    CuteEntityManager::EntityManager("QSQLITE",
                                     QDir::currentPath() + "/db.sqlite");
    QStringList inits = QStringList() << "Artikel";
    e->startup("0.1", inits);
    QSharedPointer<Artikel> a = QSharedPointer<Artikel>(new Artikel(20.0,
                                "Müsli"));
    auto ep = a.dynamicCast<CuteEntityManager::Entity>();
    e->create(ep, true, true);
//    auto artikel = e->findById<Artikel *>(1);
//    qDebug() << "ArtikelID:" << artikel.data()->getId();

    return 0;
}