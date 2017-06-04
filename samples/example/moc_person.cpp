/****************************************************************************
** Meta object code from reading C++ file 'person.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "models/person.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QSharedPointer>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'person.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Person_t {
    QByteArrayData data[18];
    char stringdata0[238];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Person_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Person_t qt_meta_stringdata_Person = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Person"
QT_MOC_LITERAL(1, 7, 0), // ""
QT_MOC_LITERAL(2, 8, 6), // "parent"
QT_MOC_LITERAL(3, 15, 9), // "firstName"
QT_MOC_LITERAL(4, 25, 10), // "familyName"
QT_MOC_LITERAL(5, 36, 10), // "namePrefix"
QT_MOC_LITERAL(6, 47, 8), // "nickName"
QT_MOC_LITERAL(7, 56, 21), // "customPictureFileName"
QT_MOC_LITERAL(8, 78, 8), // "birthday"
QT_MOC_LITERAL(9, 87, 6), // "gender"
QT_MOC_LITERAL(10, 94, 6), // "Gender"
QT_MOC_LITERAL(11, 101, 6), // "groups"
QT_MOC_LITERAL(12, 108, 29), // "QList<QSharedPointer<Group> >"
QT_MOC_LITERAL(13, 138, 16), // "maintainedGroups"
QT_MOC_LITERAL(14, 155, 8), // "contacts"
QT_MOC_LITERAL(15, 164, 31), // "QList<QSharedPointer<Contact> >"
QT_MOC_LITERAL(16, 196, 9), // "addresses"
QT_MOC_LITERAL(17, 206, 31) // "QList<QSharedPointer<Address> >"

    },
    "Person\0\0parent\0firstName\0familyName\0"
    "namePrefix\0nickName\0customPictureFileName\0"
    "birthday\0gender\0Gender\0groups\0"
    "QList<QSharedPointer<Group> >\0"
    "maintainedGroups\0contacts\0"
    "QList<QSharedPointer<Contact> >\0"
    "addresses\0QList<QSharedPointer<Address> >"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Person[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
      11,   18, // properties
       0,    0, // enums/sets
       2,   51, // constructors
       0,       // flags
       0,       // signalCount

 // constructors: parameters
    0x80000000 | 1, QMetaType::QObjectStar,    2,
    0x80000000 | 1,

 // properties: name, type, flags
       3, QMetaType::QString, 0x00095103,
       4, QMetaType::QString, 0x00095103,
       5, QMetaType::QString, 0x00095103,
       6, QMetaType::QString, 0x00095103,
       7, QMetaType::QString, 0x00095103,
       8, QMetaType::QDate, 0x00095103,
       9, 0x80000000 | 10, 0x0009510b,
      11, 0x80000000 | 12, 0x0009510b,
      13, 0x80000000 | 12, 0x0009510b,
      14, 0x80000000 | 15, 0x0009510b,
      16, 0x80000000 | 17, 0x0009510b,

 // constructors: name, argc, parameters, tag, flags
       0,    1,   14,    1, 0x0e /* Public */,
       0,    0,   17,    1, 0x2e /* Public | MethodCloned */,

       0        // eod
};

void Person::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { Person *_r = new Person((*reinterpret_cast< QObject*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        case 1: { Person *_r = new Person();
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        default: break;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        Person *_t = static_cast<Person *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->getFirstName(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->getFamilyName(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->getNamePrefix(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->getNickName(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->getCustomPictureFileName(); break;
        case 5: *reinterpret_cast< QDate*>(_v) = _t->getBirthday(); break;
        case 6: *reinterpret_cast< Gender*>(_v) = _t->getGender(); break;
        case 7: *reinterpret_cast< QList<QSharedPointer<Group> >*>(_v) = _t->getGroups(); break;
        case 8: *reinterpret_cast< QList<QSharedPointer<Group> >*>(_v) = _t->getMaintainedGroups(); break;
        case 9: *reinterpret_cast< QList<QSharedPointer<Contact> >*>(_v) = _t->getContacts(); break;
        case 10: *reinterpret_cast< QList<QSharedPointer<Address> >*>(_v) = _t->getAddresses(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        Person *_t = static_cast<Person *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setFirstName(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setFamilyName(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setNamePrefix(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setNickName(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setCustomPictureFileName(*reinterpret_cast< QString*>(_v)); break;
        case 5: _t->setBirthday(*reinterpret_cast< QDate*>(_v)); break;
        case 6: _t->setGender(*reinterpret_cast< Gender*>(_v)); break;
        case 7: _t->setGroups(*reinterpret_cast< QList<QSharedPointer<Group> >*>(_v)); break;
        case 8: _t->setMaintainedGroups(*reinterpret_cast< QList<QSharedPointer<Group> >*>(_v)); break;
        case 9: _t->setContacts(*reinterpret_cast< QList<QSharedPointer<Contact> >*>(_v)); break;
        case 10: _t->setAddresses(*reinterpret_cast< QList<QSharedPointer<Address> >*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_o);
}

const QMetaObject Person::staticMetaObject = {
    { &Entity::staticMetaObject, qt_meta_stringdata_Person.data,
      qt_meta_data_Person,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Person::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Person::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Person.stringdata0))
        return static_cast<void*>(const_cast< Person*>(this));
    return Entity::qt_metacast(_clname);
}

int Person::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Entity::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
   if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 11;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 11;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
