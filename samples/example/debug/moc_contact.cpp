/****************************************************************************
** Meta object code from reading C++ file 'contact.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../models/contact.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QSharedPointer>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'contact.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Contact_t {
    QByteArrayData data[10];
    char stringdata0[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Contact_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Contact_t qt_meta_stringdata_Contact = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Contact"
QT_MOC_LITERAL(1, 8, 0), // ""
QT_MOC_LITERAL(2, 9, 7), // "content"
QT_MOC_LITERAL(3, 17, 8), // "category"
QT_MOC_LITERAL(4, 26, 8), // "Category"
QT_MOC_LITERAL(5, 35, 5), // "label"
QT_MOC_LITERAL(6, 41, 7), // "persons"
QT_MOC_LITERAL(7, 49, 30), // "QList<QSharedPointer<Person> >"
QT_MOC_LITERAL(8, 80, 6), // "pupils"
QT_MOC_LITERAL(9, 87, 29) // "QList<QSharedPointer<Pupil> >"

    },
    "Contact\0\0content\0category\0Category\0"
    "label\0persons\0QList<QSharedPointer<Person> >\0"
    "pupils\0QList<QSharedPointer<Pupil> >"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Contact[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       5,   15, // properties
       0,    0, // enums/sets
       1,   30, // constructors
       0,       // flags
       0,       // signalCount

 // constructors: parameters
    0x80000000 | 1,

 // properties: name, type, flags
       2, QMetaType::QString, 0x00095103,
       3, 0x80000000 | 4, 0x0009510b,
       5, QMetaType::QString, 0x00095103,
       6, 0x80000000 | 7, 0x0009510b,
       8, 0x80000000 | 9, 0x0009510b,

 // constructors: name, argc, parameters, tag, flags
       0,    0,   14,    1, 0x0e /* Public */,

       0        // eod
};

void Contact::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { Contact *_r = new Contact();
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        default: break;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        Contact *_t = static_cast<Contact *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->getContent(); break;
        case 1: *reinterpret_cast< Category*>(_v) = _t->getCategory(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->getLabel(); break;
        case 3: *reinterpret_cast< QList<QSharedPointer<Person> >*>(_v) = _t->getPersons(); break;
        case 4: *reinterpret_cast< QList<QSharedPointer<Pupil> >*>(_v) = _t->getPupils(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        Contact *_t = static_cast<Contact *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setContent(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setCategory(*reinterpret_cast< Category*>(_v)); break;
        case 2: _t->setLabel(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setPersons(*reinterpret_cast< QList<QSharedPointer<Person> >*>(_v)); break;
        case 4: _t->setPupils(*reinterpret_cast< QList<QSharedPointer<Pupil> >*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_o);
}

const QMetaObject Contact::staticMetaObject = {
    { &CuteEntityManager::Entity::staticMetaObject, qt_meta_stringdata_Contact.data,
      qt_meta_data_Contact,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Contact::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Contact::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Contact.stringdata0))
        return static_cast<void*>(const_cast< Contact*>(this));
    return CuteEntityManager::Entity::qt_metacast(_clname);
}

int Contact::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CuteEntityManager::Entity::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
   if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
