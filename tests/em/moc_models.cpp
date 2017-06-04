/****************************************************************************
** Meta object code from reading C++ file 'models.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../models.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QSharedPointer>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'models.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Person_t {
    QByteArrayData data[15];
    char stringdata0[148];
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
QT_MOC_LITERAL(5, 36, 8), // "nickName"
QT_MOC_LITERAL(6, 45, 8), // "birthday"
QT_MOC_LITERAL(7, 54, 6), // "gender"
QT_MOC_LITERAL(8, 61, 6), // "Gender"
QT_MOC_LITERAL(9, 68, 6), // "groups"
QT_MOC_LITERAL(10, 75, 29), // "QList<QSharedPointer<Group> >"
QT_MOC_LITERAL(11, 105, 16), // "maintainedGroups"
QT_MOC_LITERAL(12, 122, 4), // "MALE"
QT_MOC_LITERAL(13, 127, 6), // "FEMALE"
QT_MOC_LITERAL(14, 134, 13) // "UNKNOWNGENDER"

    },
    "Person\0\0parent\0firstName\0familyName\0"
    "nickName\0birthday\0gender\0Gender\0groups\0"
    "QList<QSharedPointer<Group> >\0"
    "maintainedGroups\0MALE\0FEMALE\0UNKNOWNGENDER"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Person[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       7,   18, // properties
       1,   39, // enums/sets
       2,   49, // constructors
       0,       // flags
       0,       // signalCount

 // constructors: parameters
    0x80000000 | 1, QMetaType::QObjectStar,    2,
    0x80000000 | 1,

 // properties: name, type, flags
       3, QMetaType::QString, 0x00095103,
       4, QMetaType::QString, 0x00095103,
       5, QMetaType::QString, 0x00095103,
       6, QMetaType::QDate, 0x00095103,
       7, 0x80000000 | 8, 0x0009510b,
       9, 0x80000000 | 10, 0x0009510b,
      11, 0x80000000 | 10, 0x0009510b,

 // enums: name, flags, count, data
       8, 0x2,    3,   43,

 // enum data: key, value
      12, uint(Person::Gender::MALE),
      13, uint(Person::Gender::FEMALE),
      14, uint(Person::Gender::UNKNOWNGENDER),

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
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
        case 5:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSharedPointer<Group> > >(); break;
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
        case 2: *reinterpret_cast< QString*>(_v) = _t->getNickName(); break;
        case 3: *reinterpret_cast< QDate*>(_v) = _t->getBirthday(); break;
        case 4: *reinterpret_cast< Gender*>(_v) = _t->getGender(); break;
        case 5: *reinterpret_cast< QList<QSharedPointer<Group> >*>(_v) = _t->getGroups(); break;
        case 6: *reinterpret_cast< QList<QSharedPointer<Group> >*>(_v) = _t->getMaintainedGroups(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        Person *_t = static_cast<Person *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setFirstName(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setFamilyName(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setNickName(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setBirthday(*reinterpret_cast< QDate*>(_v)); break;
        case 4: _t->setGender(*reinterpret_cast< Gender*>(_v)); break;
        case 5: _t->setGroups(*reinterpret_cast< QList<QSharedPointer<Group> >*>(_v)); break;
        case 6: _t->setMaintainedGroups(*reinterpret_cast< QList<QSharedPointer<Group> >*>(_v)); break;
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
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 7;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
struct qt_meta_stringdata_Employee_t {
    QByteArrayData data[4];
    char stringdata0[39];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Employee_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Employee_t qt_meta_stringdata_Employee = {
    {
QT_MOC_LITERAL(0, 0, 8), // "Employee"
QT_MOC_LITERAL(1, 9, 10), // "department"
QT_MOC_LITERAL(2, 20, 10), // "persNumber"
QT_MOC_LITERAL(3, 31, 7) // "manager"

    },
    "Employee\0department\0persNumber\0manager"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Employee[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       3,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QString, 0x00095103,
       2, QMetaType::ULongLong, 0x00095103,
       3, QMetaType::Bool, 0x00095103,

       0        // eod
};

void Employee::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{

#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty) {
        Employee *_t = static_cast<Employee *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->getDepartment(); break;
        case 1: *reinterpret_cast< quint64*>(_v) = _t->getPersNumber(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->isManager(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        Employee *_t = static_cast<Employee *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setDepartment(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setPersNumber(*reinterpret_cast< quint64*>(_v)); break;
        case 2: _t->setManager(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject Employee::staticMetaObject = {
    { &Person::staticMetaObject, qt_meta_stringdata_Employee.data,
      qt_meta_data_Employee,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Employee::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Employee::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Employee.stringdata0))
        return static_cast<void*>(const_cast< Employee*>(this));
    return Person::qt_metacast(_clname);
}

int Employee::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Person::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
   if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
struct qt_meta_stringdata_WorkerGroup_t {
    QByteArrayData data[6];
    char stringdata0[76];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WorkerGroup_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WorkerGroup_t qt_meta_stringdata_WorkerGroup = {
    {
QT_MOC_LITERAL(0, 0, 11), // "WorkerGroup"
QT_MOC_LITERAL(1, 12, 4), // "name"
QT_MOC_LITERAL(2, 17, 10), // "efficiency"
QT_MOC_LITERAL(3, 28, 6), // "active"
QT_MOC_LITERAL(4, 35, 7), // "workers"
QT_MOC_LITERAL(5, 43, 32) // "QList<QSharedPointer<Employee> >"

    },
    "WorkerGroup\0name\0efficiency\0active\0"
    "workers\0QList<QSharedPointer<Employee> >"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WorkerGroup[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       4,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QString, 0x00095103,
       2, QMetaType::UInt, 0x00095103,
       3, QMetaType::Bool, 0x00095103,
       4, 0x80000000 | 5, 0x0009510b,

       0        // eod
};

void WorkerGroup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSharedPointer<Employee> > >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        WorkerGroup *_t = static_cast<WorkerGroup *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->getName(); break;
        case 1: *reinterpret_cast< quint32*>(_v) = _t->getEfficiency(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->isActive(); break;
        case 3: *reinterpret_cast< QList<QSharedPointer<Employee> >*>(_v) = _t->getWorkers(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        WorkerGroup *_t = static_cast<WorkerGroup *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setName(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setEfficiency(*reinterpret_cast< quint32*>(_v)); break;
        case 2: _t->setActive(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->setWorkers(*reinterpret_cast< QList<QSharedPointer<Employee> >*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_o);
}

const QMetaObject WorkerGroup::staticMetaObject = {
    { &Entity::staticMetaObject, qt_meta_stringdata_WorkerGroup.data,
      qt_meta_data_WorkerGroup,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *WorkerGroup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WorkerGroup::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_WorkerGroup.stringdata0))
        return static_cast<void*>(const_cast< WorkerGroup*>(this));
    return Entity::qt_metacast(_clname);
}

int WorkerGroup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Entity::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_Group_t {
    QByteArrayData data[7];
    char stringdata0[81];
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
QT_MOC_LITERAL(2, 7, 7), // "persons"
QT_MOC_LITERAL(3, 15, 30), // "QList<QSharedPointer<Person> >"
QT_MOC_LITERAL(4, 46, 4), // "name"
QT_MOC_LITERAL(5, 51, 6), // "leader"
QT_MOC_LITERAL(6, 58, 22) // "QSharedPointer<Person>"

    },
    "Group\0\0persons\0QList<QSharedPointer<Person> >\0"
    "name\0leader\0QSharedPointer<Person>"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Group[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       3,   15, // properties
       0,    0, // enums/sets
       1,   24, // constructors
       0,       // flags
       0,       // signalCount

 // constructors: parameters
    0x80000000 | 1,

 // properties: name, type, flags
       2, 0x80000000 | 3, 0x0009510b,
       4, QMetaType::QString, 0x00095103,
       5, 0x80000000 | 6, 0x0009510b,

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
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSharedPointer<Person> > >(); break;
        case 2:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QSharedPointer<Person> >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        Group *_t = static_cast<Group *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QList<QSharedPointer<Person> >*>(_v) = _t->getPersons(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->getName(); break;
        case 2: *reinterpret_cast< QSharedPointer<Person>*>(_v) = _t->getLeader(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        Group *_t = static_cast<Group *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPersons(*reinterpret_cast< QList<QSharedPointer<Person> >*>(_v)); break;
        case 1: _t->setName(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setLeader(*reinterpret_cast< QSharedPointer<Person>*>(_v)); break;
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
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
struct qt_meta_stringdata_Article_t {
    QByteArrayData data[4];
    char stringdata0[20];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Article_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Article_t qt_meta_stringdata_Article = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Article"
QT_MOC_LITERAL(1, 8, 0), // ""
QT_MOC_LITERAL(2, 9, 5), // "price"
QT_MOC_LITERAL(3, 15, 4) // "name"

    },
    "Article\0\0price\0name"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Article[] = {

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
    0x80000000 | 1,

 // properties: name, type, flags
       2, QMetaType::Double, 0x00095103,
       3, QMetaType::QString, 0x00095103,

 // constructors: name, argc, parameters, tag, flags
       0,    0,   14,    1, 0x0e /* Public */,

       0        // eod
};

void Article::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { Article *_r = new Article();
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        default: break;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        Article *_t = static_cast<Article *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< double*>(_v) = _t->getPrice(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->getName(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        Article *_t = static_cast<Article *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPrice(*reinterpret_cast< double*>(_v)); break;
        case 1: _t->setName(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_o);
}

const QMetaObject Article::staticMetaObject = {
    { &CuteEntityManager::Entity::staticMetaObject, qt_meta_stringdata_Article.data,
      qt_meta_data_Article,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Article::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Article::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Article.stringdata0))
        return static_cast<void*>(const_cast< Article*>(this));
    return CuteEntityManager::Entity::qt_metacast(_clname);
}

int Article::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CuteEntityManager::Entity::qt_metacall(_c, _id, _a);
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
