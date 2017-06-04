/****************************************************************************
** Meta object code from reading C++ file 'group.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "models/group.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QSharedPointer>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'group.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Group_t {
    QByteArrayData data[9];
    char stringdata0[123];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Group_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Group_t qt_meta_stringdata_Group = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Group"
QT_MOC_LITERAL(1, 6, 0), // ""
QT_MOC_LITERAL(2, 7, 6), // "pupils"
QT_MOC_LITERAL(3, 14, 29), // "QList<QSharedPointer<Pupil> >"
QT_MOC_LITERAL(4, 44, 7), // "persons"
QT_MOC_LITERAL(5, 52, 30), // "QList<QSharedPointer<Person> >"
QT_MOC_LITERAL(6, 83, 4), // "name"
QT_MOC_LITERAL(7, 88, 11), // "mainTeacher"
QT_MOC_LITERAL(8, 100, 22) // "QSharedPointer<Person>"

    },
    "Group\0\0pupils\0QList<QSharedPointer<Pupil> >\0"
    "persons\0QList<QSharedPointer<Person> >\0"
    "name\0mainTeacher\0QSharedPointer<Person>"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Group[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       4,   15, // properties
       0,    0, // enums/sets
       1,   27, // constructors
       0,       // flags
       0,       // signalCount

 // constructors: parameters
    0x80000000 | 1,

 // properties: name, type, flags
       2, 0x80000000 | 3, 0x0009510b,
       4, 0x80000000 | 5, 0x0009510b,
       6, QMetaType::QString, 0x00095103,
       7, 0x80000000 | 8, 0x0009510b,

 // constructors: name, argc, parameters, tag, flags
       0,    0,   14,    1, 0x0e /* Public */,

       0        // eod
};

void Group::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { Group *_r = new Group();
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        default: break;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        Group *_t = static_cast<Group *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QList<QSharedPointer<Pupil> >*>(_v) = _t->getPupils(); break;
        case 1: *reinterpret_cast< QList<QSharedPointer<Person> >*>(_v) = _t->getPersons(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->getName(); break;
        case 3: *reinterpret_cast< QSharedPointer<Person>*>(_v) = _t->getMainTeacher(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        Group *_t = static_cast<Group *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPupils(*reinterpret_cast< QList<QSharedPointer<Pupil> >*>(_v)); break;
        case 1: _t->setPersons(*reinterpret_cast< QList<QSharedPointer<Person> >*>(_v)); break;
        case 2: _t->setName(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setMainTeacher(*reinterpret_cast< QSharedPointer<Person>*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_o);
}

const QMetaObject Group::staticMetaObject = {
    { &CuteEntityManager::Entity::staticMetaObject, qt_meta_stringdata_Group.data,
      qt_meta_data_Group,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Group::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Group::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Group.stringdata0))
        return static_cast<void*>(const_cast< Group*>(this));
    return CuteEntityManager::Entity::qt_metacast(_clname);
}

int Group::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CuteEntityManager::Entity::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
   if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
