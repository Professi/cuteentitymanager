#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include "article.h"
#include "entitymanager.h"
#include "entityinstancefactory.h"


using namespace CuteEntityManager;
int main(int argc, char *argv[]) {
    Q_UNUSED(argc) Q_UNUSED(argv)
    EntityInstanceFactory::registerClass<Article>();
    QSharedPointer<CuteEntityManager::EntityManager> e =
        QSharedPointer<CuteEntityManager::EntityManager>(new
                CuteEntityManager::EntityManager("QSQLITE",
                        QDir::currentPath() + "/db.sqlite"));
    QStringList inits = QStringList() << "Article";
    e->startup("0.1", inits);
    QSharedPointer<Article> a = QSharedPointer<Article>(new Article(5.0,
                                "muesli"));
    auto ep = a.objectCast<CuteEntityManager::Entity>();
    qDebug() << e->create(ep, true, true); //INSERT on database
    a->setPrice(6.0); //inflation
    a->setName("muesli improved"); //1337 muesli upgrade
    qDebug() << e->save(ep); //UPDATE on database
    qDebug() << e->remove(ep); //REMOVE on database
    return 0;
}
