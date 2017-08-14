/****************************************************************************
** Meta object code from reading C++ file 'tst_em.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../tst_em.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tst_em.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EmTest_t {
    QByteArrayData data[18];
    char stringdata0[281];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EmTest_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EmTest_t qt_meta_stringdata_EmTest = {
    {
QT_MOC_LITERAL(0, 0, 6), // "EmTest"
QT_MOC_LITERAL(1, 7, 19), // "testCheckDuplicates"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 10), // "testBasics"
QT_MOC_LITERAL(4, 39, 4), // "init"
QT_MOC_LITERAL(5, 44, 7), // "cleanup"
QT_MOC_LITERAL(6, 52, 12), // "testFindById"
QT_MOC_LITERAL(7, 65, 18), // "testFindByIdOnNull"
QT_MOC_LITERAL(8, 84, 10), // "testFindId"
QT_MOC_LITERAL(9, 95, 14), // "testHasChanged"
QT_MOC_LITERAL(10, 110, 12), // "testValidate"
QT_MOC_LITERAL(11, 123, 13), // "testRelations"
QT_MOC_LITERAL(12, 137, 25), // "testRelationTableCreation"
QT_MOC_LITERAL(13, 163, 22), // "testInheritedRelations"
QT_MOC_LITERAL(14, 186, 31), // "testNonCachedInheritedRelations"
QT_MOC_LITERAL(15, 218, 26), // "testDatabaseMigrationTable"
QT_MOC_LITERAL(16, 245, 17), // "testCountEntities"
QT_MOC_LITERAL(17, 263, 17) // "testTableCreation"

    },
    "EmTest\0testCheckDuplicates\0\0testBasics\0"
    "init\0cleanup\0testFindById\0testFindByIdOnNull\0"
    "testFindId\0testHasChanged\0testValidate\0"
    "testRelations\0testRelationTableCreation\0"
    "testInheritedRelations\0"
    "testNonCachedInheritedRelations\0"
    "testDatabaseMigrationTable\0testCountEntities\0"
    "testTableCreation"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EmTest[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    0,   97,    2, 0x08 /* Private */,
       6,    0,   98,    2, 0x08 /* Private */,
       7,    0,   99,    2, 0x08 /* Private */,
       8,    0,  100,    2, 0x08 /* Private */,
       9,    0,  101,    2, 0x08 /* Private */,
      10,    0,  102,    2, 0x08 /* Private */,
      11,    0,  103,    2, 0x08 /* Private */,
      12,    0,  104,    2, 0x08 /* Private */,
      13,    0,  105,    2, 0x08 /* Private */,
      14,    0,  106,    2, 0x08 /* Private */,
      15,    0,  107,    2, 0x08 /* Private */,
      16,    0,  108,    2, 0x08 /* Private */,
      17,    0,  109,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void EmTest::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EmTest *_t = static_cast<EmTest *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->testCheckDuplicates(); break;
        case 1: _t->testBasics(); break;
        case 2: _t->init(); break;
        case 3: _t->cleanup(); break;
        case 4: _t->testFindById(); break;
        case 5: _t->testFindByIdOnNull(); break;
        case 6: _t->testFindId(); break;
        case 7: _t->testHasChanged(); break;
        case 8: _t->testValidate(); break;
        case 9: _t->testRelations(); break;
        case 10: _t->testRelationTableCreation(); break;
        case 11: _t->testInheritedRelations(); break;
        case 12: _t->testNonCachedInheritedRelations(); break;
        case 13: _t->testDatabaseMigrationTable(); break;
        case 14: _t->testCountEntities(); break;
        case 15: _t->testTableCreation(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject EmTest::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_EmTest.data,
      qt_meta_data_EmTest,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *EmTest::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EmTest::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_EmTest.stringdata0))
        return static_cast<void*>(const_cast< EmTest*>(this));
    return QObject::qt_metacast(_clname);
}

int EmTest::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
