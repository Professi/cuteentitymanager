/****************************************************************************
** Meta object code from reading C++ file 'address.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "models/address.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QSharedPointer>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'address.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Address_t {
    QByteArrayData data[10];
    char stringdata0[112];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Address_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Address_t qt_meta_stringdata_Address = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Address"
QT_MOC_LITERAL(1, 8, 0), // ""
QT_MOC_LITERAL(2, 9, 5), // "label"
QT_MOC_LITERAL(3, 15, 6), // "street"
QT_MOC_LITERAL(4, 22, 8), // "postcode"
QT_MOC_LITERAL(5, 31, 4), // "city"
QT_MOC_LITERAL(6, 36, 7), // "persons"
QT_MOC_LITERAL(7, 44, 30), // "QList<QSharedPointer<Person> >"
QT_MOC_LITERAL(8, 75, 6), // "pupils"
QT_MOC_LITERAL(9, 82, 29) // "QList<QSharedPointer<Pupil> >"

    },
    "Address\0\0label\0street\0postcode\0city\0"
    "persons\0QList<QSharedPointer<Person> >\0"
    "pupils\0QList<QSharedPointer<Pupil> >"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Address[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       6,   15, // properties
       0,    0, // enums/sets
       1,   33, // constructors
       0,       // flags
       0,       // signalCount

 // constructors: parameters
    0x80000000 | 1,

 // properties: name, type, flags
       2, QMetaType::QString, 0x00095103,
       3, QMetaType::QString, 0x00095103,
       4, QMetaType::QString, 0x00095103,
       5, QMetaType::QString, 0x00095103,
       6, 0x80000000 | 7, 0x0009510b,
       8, 0x80000000 | 9, 0x0009510b,

 // constructors: name, argc, parameters, tag, flags
       0,    0,   14,    1, 0x0e /* Public */,

       0        // eod
};

void Address::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { Address *_r = new Address();
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        default: break;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        Address *_t = static_cast<Address *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->getLabel(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->getStreet(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->getPostcode(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->getCity(); break;
        case 4: *reinterpret_cast< QList<QSharedPointer<Person> >*>(_v) = _t->getPersons(); break;
        case 5: *reinterpret_cast< QList<QSharedPointer<Pupil> >*>(_v) = _t->getPupils(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        Address *_t = static_cast<Address *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setLabel(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setStreet(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setPostcode(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setCity(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setPersons(*reinterpret_cast< QList<QSharedPointer<Person> >*>(_v)); break;
        case 5: _t->setPupils(*reinterpret_cast< QList<QSharedPointer<Pupil> >*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_o);
}

const QMetaObject Address::staticMetaObject = {
    { &CuteEntityManager::Entity::staticMetaObject, qt_meta_stringdata_Address.data,
      qt_meta_data_Address,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Address::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Address::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Address.stringdata0))
        return static_cast<void*>(const_cast< Address*>(this));
    return CuteEntityManager::Entity::qt_metacast(_clname);
}

int Address::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CuteEntityManager::Entity::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
   if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 6;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
