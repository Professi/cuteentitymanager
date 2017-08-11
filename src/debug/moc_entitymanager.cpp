/****************************************************************************
** Meta object code from reading C++ file 'entitymanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../entitymanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QSharedPointer>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'entitymanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CuteEntityManager__EntityManager_t {
    QByteArrayData data[50];
    char stringdata0[665];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CuteEntityManager__EntityManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CuteEntityManager__EntityManager_t qt_meta_stringdata_CuteEntityManager__EntityManager = {
    {
QT_MOC_LITERAL(0, 0, 32), // "CuteEntityManager::EntityManager"
QT_MOC_LITERAL(1, 33, 7), // "startup"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 7), // "version"
QT_MOC_LITERAL(4, 50, 12), // "toInitialize"
QT_MOC_LITERAL(5, 63, 13), // "createIndices"
QT_MOC_LITERAL(6, 77, 12), // "executeQuery"
QT_MOC_LITERAL(7, 90, 5), // "query"
QT_MOC_LITERAL(8, 96, 8), // "findById"
QT_MOC_LITERAL(9, 105, 22), // "QSharedPointer<Entity>"
QT_MOC_LITERAL(10, 128, 2), // "id"
QT_MOC_LITERAL(11, 131, 9), // "classname"
QT_MOC_LITERAL(12, 141, 7), // "refresh"
QT_MOC_LITERAL(13, 149, 22), // "findEntityByAttributes"
QT_MOC_LITERAL(14, 172, 30), // "QList<QSharedPointer<Entity> >"
QT_MOC_LITERAL(15, 203, 6), // "entity"
QT_MOC_LITERAL(16, 210, 8), // "ignoreID"
QT_MOC_LITERAL(17, 219, 16), // "resolveRelations"
QT_MOC_LITERAL(18, 236, 6), // "findId"
QT_MOC_LITERAL(19, 243, 23), // "QSharedPointer<Entity>&"
QT_MOC_LITERAL(20, 267, 6), // "create"
QT_MOC_LITERAL(21, 274, 31), // "QList<QSharedPointer<Entity> >&"
QT_MOC_LITERAL(22, 306, 8), // "entities"
QT_MOC_LITERAL(23, 315, 16), // "persistRelations"
QT_MOC_LITERAL(24, 332, 14), // "checkDuplicate"
QT_MOC_LITERAL(25, 347, 8), // "validate"
QT_MOC_LITERAL(26, 356, 25), // "relationsIgnoreHasChanged"
QT_MOC_LITERAL(27, 382, 4), // "save"
QT_MOC_LITERAL(28, 387, 16), // "ignoreHasChanged"
QT_MOC_LITERAL(29, 404, 9), // "removeAll"
QT_MOC_LITERAL(30, 414, 7), // "tblname"
QT_MOC_LITERAL(31, 422, 11), // "createTable"
QT_MOC_LITERAL(32, 434, 20), // "createRelationTables"
QT_MOC_LITERAL(33, 455, 9), // "className"
QT_MOC_LITERAL(34, 465, 11), // "removeTable"
QT_MOC_LITERAL(35, 477, 5), // "count"
QT_MOC_LITERAL(36, 483, 15), // "joinBaseClasses"
QT_MOC_LITERAL(37, 499, 9), // "tableName"
QT_MOC_LITERAL(38, 509, 5), // "getDb"
QT_MOC_LITERAL(39, 515, 24), // "QSharedPointer<Database>"
QT_MOC_LITERAL(40, 540, 5), // "setDb"
QT_MOC_LITERAL(41, 546, 5), // "value"
QT_MOC_LITERAL(42, 552, 9), // "getSchema"
QT_MOC_LITERAL(43, 562, 22), // "QSharedPointer<Schema>"
QT_MOC_LITERAL(44, 585, 13), // "selectByQuery"
QT_MOC_LITERAL(45, 599, 31), // "QList<QHash<QString,QVariant> >"
QT_MOC_LITERAL(46, 631, 6), // "Query&"
QT_MOC_LITERAL(47, 638, 11), // "selectBySql"
QT_MOC_LITERAL(48, 650, 3), // "sql"
QT_MOC_LITERAL(49, 654, 10) // "hasChanged"

    },
    "CuteEntityManager::EntityManager\0"
    "startup\0\0version\0toInitialize\0"
    "createIndices\0executeQuery\0query\0"
    "findById\0QSharedPointer<Entity>\0id\0"
    "classname\0refresh\0findEntityByAttributes\0"
    "QList<QSharedPointer<Entity> >\0entity\0"
    "ignoreID\0resolveRelations\0findId\0"
    "QSharedPointer<Entity>&\0create\0"
    "QList<QSharedPointer<Entity> >&\0"
    "entities\0persistRelations\0checkDuplicate\0"
    "validate\0relationsIgnoreHasChanged\0"
    "save\0ignoreHasChanged\0removeAll\0tblname\0"
    "createTable\0createRelationTables\0"
    "className\0removeTable\0count\0joinBaseClasses\0"
    "tableName\0getDb\0QSharedPointer<Database>\0"
    "setDb\0value\0getSchema\0QSharedPointer<Schema>\0"
    "selectByQuery\0QList<QHash<QString,QVariant> >\0"
    "Query&\0selectBySql\0sql\0hasChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CuteEntityManager__EntityManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      37,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,  199,    2, 0x0a /* Public */,
       1,    2,  206,    2, 0x2a /* Public | MethodCloned */,
       6,    1,  211,    2, 0x0a /* Public */,
       8,    3,  214,    2, 0x0a /* Public */,
       8,    2,  221,    2, 0x2a /* Public | MethodCloned */,
      13,    3,  226,    2, 0x0a /* Public */,
      13,    2,  233,    2, 0x2a /* Public | MethodCloned */,
      13,    1,  238,    2, 0x2a /* Public | MethodCloned */,
      18,    1,  241,    2, 0x0a /* Public */,
      20,    5,  244,    2, 0x0a /* Public */,
      20,    4,  255,    2, 0x2a /* Public | MethodCloned */,
      20,    3,  264,    2, 0x2a /* Public | MethodCloned */,
      20,    2,  271,    2, 0x2a /* Public | MethodCloned */,
      20,    1,  276,    2, 0x2a /* Public | MethodCloned */,
      27,    5,  279,    2, 0x0a /* Public */,
      27,    4,  290,    2, 0x2a /* Public | MethodCloned */,
      27,    3,  299,    2, 0x2a /* Public | MethodCloned */,
      27,    2,  306,    2, 0x2a /* Public | MethodCloned */,
      27,    1,  311,    2, 0x2a /* Public | MethodCloned */,
      29,    1,  314,    2, 0x0a /* Public */,
      31,    2,  317,    2, 0x0a /* Public */,
      31,    1,  322,    2, 0x2a /* Public | MethodCloned */,
      31,    2,  325,    2, 0x0a /* Public */,
      31,    1,  330,    2, 0x2a /* Public | MethodCloned */,
      34,    1,  333,    2, 0x0a /* Public */,
      35,    3,  336,    2, 0x0a /* Public */,
      35,    2,  343,    2, 0x2a /* Public | MethodCloned */,
      35,    1,  348,    2, 0x2a /* Public | MethodCloned */,
      35,    1,  351,    2, 0x0a /* Public */,
      38,    0,  354,    2, 0x0a /* Public */,
      40,    1,  355,    2, 0x0a /* Public */,
      42,    0,  358,    2, 0x0a /* Public */,
      44,    1,  359,    2, 0x0a /* Public */,
      47,    1,  362,    2, 0x0a /* Public */,
      35,    1,  365,    2, 0x0a /* Public */,
      25,    1,  368,    2, 0x0a /* Public */,
      49,    1,  371,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Bool, QMetaType::QString, QMetaType::QStringList, QMetaType::Bool,    3,    4,    5,
    QMetaType::Bool, QMetaType::QString, QMetaType::QStringList,    3,    4,
    QMetaType::Bool, QMetaType::QString,    7,
    0x80000000 | 9, QMetaType::LongLong, QMetaType::QString, QMetaType::Bool,   10,   11,   12,
    0x80000000 | 9, QMetaType::LongLong, QMetaType::QString,   10,   11,
    0x80000000 | 14, 0x80000000 | 9, QMetaType::Bool, QMetaType::Bool,   15,   16,   17,
    0x80000000 | 14, 0x80000000 | 9, QMetaType::Bool,   15,   16,
    0x80000000 | 14, 0x80000000 | 9,   15,
    QMetaType::LongLong, 0x80000000 | 19,   15,
    QMetaType::Bool, 0x80000000 | 21, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,   22,   23,   24,   25,   26,
    QMetaType::Bool, 0x80000000 | 21, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,   22,   23,   24,   25,
    QMetaType::Bool, 0x80000000 | 21, QMetaType::Bool, QMetaType::Bool,   22,   23,   24,
    QMetaType::Bool, 0x80000000 | 21, QMetaType::Bool,   22,   23,
    QMetaType::Bool, 0x80000000 | 21,   22,
    QMetaType::Bool, 0x80000000 | 21, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,   22,   23,   28,   25,   26,
    QMetaType::Bool, 0x80000000 | 21, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,   22,   23,   28,   25,
    QMetaType::Bool, 0x80000000 | 21, QMetaType::Bool, QMetaType::Bool,   22,   23,   28,
    QMetaType::Bool, 0x80000000 | 21, QMetaType::Bool,   22,   23,
    QMetaType::Bool, 0x80000000 | 21,   22,
    QMetaType::Bool, QMetaType::QString,   30,
    QMetaType::Bool, 0x80000000 | 9, QMetaType::Bool,   15,   32,
    QMetaType::Bool, 0x80000000 | 9,   15,
    QMetaType::Bool, QMetaType::QString, QMetaType::Bool,   33,   32,
    QMetaType::Bool, QMetaType::QString,   33,
    QMetaType::Bool, QMetaType::QString,   33,
    QMetaType::UInt, 0x80000000 | 9, QMetaType::Bool, QMetaType::Bool,   15,   16,   36,
    QMetaType::UInt, 0x80000000 | 9, QMetaType::Bool,   15,   16,
    QMetaType::UInt, 0x80000000 | 9,   15,
    QMetaType::UInt, QMetaType::QString,   37,
    0x80000000 | 39,
    QMetaType::Void, 0x80000000 | 39,   41,
    0x80000000 | 43,
    0x80000000 | 45, 0x80000000 | 46,    7,
    0x80000000 | 45, QMetaType::QString,   48,
    QMetaType::UInt, 0x80000000 | 46,    7,
    QMetaType::Bool, 0x80000000 | 19,   15,
    QMetaType::Bool, 0x80000000 | 19,   15,

       0        // eod
};

void CuteEntityManager::EntityManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EntityManager *_t = static_cast<EntityManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->startup((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: { bool _r = _t->startup((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { bool _r = _t->executeQuery((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { QSharedPointer<Entity> _r = _t->findById((*reinterpret_cast< const qint64(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const bool(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QSharedPointer<Entity>*>(_a[0]) = _r; }  break;
        case 4: { QSharedPointer<Entity> _r = _t->findById((*reinterpret_cast< const qint64(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QSharedPointer<Entity>*>(_a[0]) = _r; }  break;
        case 5: { QList<QSharedPointer<Entity> > _r = _t->findEntityByAttributes((*reinterpret_cast< const QSharedPointer<Entity>(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< const bool(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QList<QSharedPointer<Entity> >*>(_a[0]) = _r; }  break;
        case 6: { QList<QSharedPointer<Entity> > _r = _t->findEntityByAttributes((*reinterpret_cast< const QSharedPointer<Entity>(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QList<QSharedPointer<Entity> >*>(_a[0]) = _r; }  break;
        case 7: { QList<QSharedPointer<Entity> > _r = _t->findEntityByAttributes((*reinterpret_cast< const QSharedPointer<Entity>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QList<QSharedPointer<Entity> >*>(_a[0]) = _r; }  break;
        case 8: { qint64 _r = _t->findId((*reinterpret_cast< QSharedPointer<Entity>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qint64*>(_a[0]) = _r; }  break;
        case 9: { bool _r = _t->create((*reinterpret_cast< QList<QSharedPointer<Entity> >(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2])),(*reinterpret_cast< const bool(*)>(_a[3])),(*reinterpret_cast< const bool(*)>(_a[4])),(*reinterpret_cast< const bool(*)>(_a[5])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 10: { bool _r = _t->create((*reinterpret_cast< QList<QSharedPointer<Entity> >(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2])),(*reinterpret_cast< const bool(*)>(_a[3])),(*reinterpret_cast< const bool(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: { bool _r = _t->create((*reinterpret_cast< QList<QSharedPointer<Entity> >(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2])),(*reinterpret_cast< const bool(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 12: { bool _r = _t->create((*reinterpret_cast< QList<QSharedPointer<Entity> >(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: { bool _r = _t->create((*reinterpret_cast< QList<QSharedPointer<Entity> >(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 14: { bool _r = _t->save((*reinterpret_cast< QList<QSharedPointer<Entity> >(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2])),(*reinterpret_cast< const bool(*)>(_a[3])),(*reinterpret_cast< const bool(*)>(_a[4])),(*reinterpret_cast< const bool(*)>(_a[5])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 15: { bool _r = _t->save((*reinterpret_cast< QList<QSharedPointer<Entity> >(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2])),(*reinterpret_cast< const bool(*)>(_a[3])),(*reinterpret_cast< const bool(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 16: { bool _r = _t->save((*reinterpret_cast< QList<QSharedPointer<Entity> >(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2])),(*reinterpret_cast< const bool(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 17: { bool _r = _t->save((*reinterpret_cast< QList<QSharedPointer<Entity> >(*)>(_a[1])),(*reinterpret_cast< const bool(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 18: { bool _r = _t->save((*reinterpret_cast< QList<QSharedPointer<Entity> >(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 19: { bool _r = _t->removeAll((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 20: { bool _r = _t->createTable((*reinterpret_cast< const QSharedPointer<Entity>(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 21: { bool _r = _t->createTable((*reinterpret_cast< const QSharedPointer<Entity>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 22: { bool _r = _t->createTable((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 23: { bool _r = _t->createTable((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 24: { bool _r = _t->removeTable((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 25: { quint32 _r = _t->count((*reinterpret_cast< const QSharedPointer<Entity>(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = _r; }  break;
        case 26: { quint32 _r = _t->count((*reinterpret_cast< const QSharedPointer<Entity>(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = _r; }  break;
        case 27: { quint32 _r = _t->count((*reinterpret_cast< const QSharedPointer<Entity>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = _r; }  break;
        case 28: { quint32 _r = _t->count((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = _r; }  break;
        case 29: { QSharedPointer<Database> _r = _t->getDb();
            if (_a[0]) *reinterpret_cast< QSharedPointer<Database>*>(_a[0]) = _r; }  break;
        case 30: _t->setDb((*reinterpret_cast< const QSharedPointer<Database>(*)>(_a[1]))); break;
        case 31: { QSharedPointer<Schema> _r = _t->getSchema();
            if (_a[0]) *reinterpret_cast< QSharedPointer<Schema>*>(_a[0]) = _r; }  break;
        case 32: { QList<QHash<QString,QVariant> > _r = _t->selectByQuery((*reinterpret_cast< Query(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QList<QHash<QString,QVariant> >*>(_a[0]) = _r; }  break;
        case 33: { QList<QHash<QString,QVariant> > _r = _t->selectBySql((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QList<QHash<QString,QVariant> >*>(_a[0]) = _r; }  break;
        case 34: { quint32 _r = _t->count((*reinterpret_cast< Query(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = _r; }  break;
        case 35: { bool _r = _t->validate((*reinterpret_cast< QSharedPointer<Entity>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 36: { bool _r = _t->hasChanged((*reinterpret_cast< QSharedPointer<Entity>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QSharedPointer<Entity> >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QSharedPointer<Entity> >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QSharedPointer<Entity> >(); break;
            }
            break;
        case 20:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QSharedPointer<Entity> >(); break;
            }
            break;
        case 21:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QSharedPointer<Entity> >(); break;
            }
            break;
        case 25:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QSharedPointer<Entity> >(); break;
            }
            break;
        case 26:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QSharedPointer<Entity> >(); break;
            }
            break;
        case 27:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QSharedPointer<Entity> >(); break;
            }
            break;
        }
    }
}

const QMetaObject CuteEntityManager::EntityManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CuteEntityManager__EntityManager.data,
      qt_meta_data_CuteEntityManager__EntityManager,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CuteEntityManager::EntityManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CuteEntityManager::EntityManager::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CuteEntityManager__EntityManager.stringdata0))
        return static_cast<void*>(const_cast< EntityManager*>(this));
    return QObject::qt_metacast(_clname);
}

int CuteEntityManager::EntityManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 37)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 37;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 37)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 37;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
