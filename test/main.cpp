#include <QCoreApplication>
#include "src/entitymanager.h"
#include <typeinfo>
#include <QDir>
#include <QDebug>
/**
  * create,remove und merge funktionieren
 */

int main(int argc, char *argv[])
{
    OpenTeacherTool::EntityManager *e = new OpenTeacherTool::EntityManager("QSQLITE",QDir::currentPath() + "/db.sqlite");

    OpenTeacherTool::Artikel *b= new OpenTeacherTool::Artikel(30,"Peter123");
    OpenTeacherTool::Entity *entity = b->getEntity();
    qDebug() << "findByAttributes:" << e->findByAttributes(entity,true);
    qDebug() << "create:" << e->create(entity);
    qDebug() << "findAll:" << e->findAll(entity->getTablename());
    entity->setAttributes(e->findByAttributes(entity,true).at(0));
    qDebug() << "AttributeValues, Artikel:" << *b->getAttributeValues();
    b->setName("Peter");
    b->setPreis(20);
    e->remove(entity);
    qDebug() << "TypID:" << typeid(entity).name();
    qDebug() << entity->getId();
    qDebug() << "merge:" << e->merge(entity);
    delete entity;

    return 0;
}
