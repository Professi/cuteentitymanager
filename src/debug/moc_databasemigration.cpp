/****************************************************************************
** Meta object code from reading C++ file 'databasemigration.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../databasemigration.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'databasemigration.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CuteEntityManager__DatabaseMigration_t {
    QByteArrayData data[5];
    char stringdata0[74];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CuteEntityManager__DatabaseMigration_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CuteEntityManager__DatabaseMigration_t qt_meta_stringdata_CuteEntityManager__DatabaseMigration = {
    {
QT_MOC_LITERAL(0, 0, 36), // "CuteEntityManager::DatabaseMi..."
QT_MOC_LITERAL(1, 37, 17), // "DatabaseMigration"
QT_MOC_LITERAL(2, 55, 0), // ""
QT_MOC_LITERAL(3, 56, 7), // "version"
QT_MOC_LITERAL(4, 64, 9) // "applyTime"

    },
    "CuteEntityManager::DatabaseMigration\0"
    "DatabaseMigration\0\0version\0applyTime"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CuteEntityManager__DatabaseMigration[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       2,   15, // properties
       0,    0, // enums/sets
       1,   21, // constructors
       0,       // flags
       0,       // signalCount

 // constructors: parameters
    0x80000000 | 2,

 // properties: name, type, flags
       3, QMetaType::QString, 0x00095103,
       4, QMetaType::QDateTime, 0x00095103,

 // constructors: name, argc, parameters, tag, flags
       1,    0,   14,    2, 0x0e /* Public */,

       0        // eod
};

void CuteEntityManager::DatabaseMigration::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { DatabaseMigration *_r = new DatabaseMigration();
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        default: break;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        DatabaseMigration *_t = static_cast<DatabaseMigration *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->getVersion(); break;
        case 1: *reinterpret_cast< QDateTime*>(_v) = _t->getApplyTime(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        DatabaseMigration *_t = static_cast<DatabaseMigration *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setVersion(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setApplyTime(*reinterpret_cast< QDateTime*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_o);
}

const QMetaObject CuteEntityManager::DatabaseMigration::staticMetaObject = {
    { &Entity::staticMetaObject, qt_meta_stringdata_CuteEntityManager__DatabaseMigration.data,
      qt_meta_data_CuteEntityManager__DatabaseMigration,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CuteEntityManager::DatabaseMigration::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CuteEntityManager::DatabaseMigration::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CuteEntityManager__DatabaseMigration.stringdata0))
        return static_cast<void*>(const_cast< DatabaseMigration*>(this));
    return Entity::qt_metacast(_clname);
}

int CuteEntityManager::DatabaseMigration::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Entity::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
   if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
