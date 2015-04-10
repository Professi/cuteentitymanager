#include <QCoreApplication>
#include <typeinfo>
#include <QDir>
#include <QDebug>
#include "models/artikel.h"
#include "models/person.h"
#include <typeinfo>
#include <QMetaMethod>
#include <QMetaProperty>
#include "models/group.h"
#include "entity.h"
#include <QGenericReturnArgument>
/**
  * create,remove und merge funktionieren
 */

int main(int argc, char *argv[]) {
//    OpenTeacherTool::EntityManager *e = new OpenTeacherTool::EntityManager("QSQLITE",QDir::currentPath() + "/db.sqlite");

//    OpenTeacherTool::Artikel *b= new OpenTeacherTool::Artikel(30,"Peter123");
//    OpenTeacherTool::Entity *entity = b->getEntity();
//    qDebug() << "findByAttributes:" << e->findByAttributes(entity,true);
//    qDebug() << "create:" << e->create(entity);
//    qDebug() << "findAll:" << e->findAll(entity->getTablename());
//    entity->setAttributes(e->findByAttributes(entity,true).at(0));
//    qDebug() << "AttributeValues, Artikel:" << *b->getAttributeValues();
//    b->setName("Peter");
//    b->setPreis(20);
//    e->remove(entity);
//    qDebug() << "TypID:" << typeid(entity).name();
//    qDebug() << entity->getId();
//    qDebug() << "merge:" << e->merge(entity);
//    delete entity;
//    Artikel *a = new Artikel(10.0,"pew");
//    a->setId(100);
//    qDebug() << a->getTablename();
//    for (int var = 0; var < a->metaObject()->methodCount(); ++var) {
//    qDebug() << a->metaObject()->method(var).name();
//    }

//    Person *b = new Person();
//    b->setId(110);
//    qDebug() << b->getTablename();
//    for (int var = 0; var < b->metaObject()->propertyCount(); ++var) {
//        qDebug() << b->metaObject()->property(var).name();
//        qDebug() << b->metaObject()->property(var).read(b);
//    }
    Group *g = new Group();
    g->setTeacher(new Person("Test","Test12345"));
    g->setTeacherP(QSharedPointer<Person>(new Person("Max","Mustermann")));
    for (int var = 0; var < g->metaObject()->propertyCount(); ++var) {
        qDebug() << "Name:" << g->metaObject()->property(var).name();
        qDebug() << "Type:" << g->metaObject()->property(var).typeName();
        auto p = g->metaObject()->property(var).read(g);
        qDebug() << "Value:" << p;
        qDebug() << p.canConvert<CuteEntityManager::Entity*>();
        qDebug() << qvariant_cast<CuteEntityManager::Entity*>(p);
        //p.type().canConvert(1);


//        if (QString(p.typeName()).contains("QList")) {
//            auto n = static_cast<QList<CuteEntityManager::Entity *>*>(p.data());
//            qDebug() << "Size:" << n->size();
//            for (int var = 0; var < n->size(); ++var) {
//                CuteEntityManager::Entity *entity = n->at(var);
//                qDebug() << entity->toString();
//            }
//        }
    }
    return 0;
}
