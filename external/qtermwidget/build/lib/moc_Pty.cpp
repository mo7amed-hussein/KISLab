/****************************************************************************
** Meta object code from reading C++ file 'Pty.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../lib/Pty.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Pty.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Konsole__Pty_t {
    QByteArrayData data[12];
    char stringdata[104];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Konsole__Pty_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Konsole__Pty_t qt_meta_stringdata_Konsole__Pty = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 12),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 11),
QT_MOC_LITERAL(4, 39, 6),
QT_MOC_LITERAL(5, 46, 6),
QT_MOC_LITERAL(6, 53, 11),
QT_MOC_LITERAL(7, 65, 2),
QT_MOC_LITERAL(8, 68, 7),
QT_MOC_LITERAL(9, 76, 4),
QT_MOC_LITERAL(10, 81, 8),
QT_MOC_LITERAL(11, 90, 12)
    },
    "Konsole::Pty\0receivedData\0\0const char*\0"
    "buffer\0length\0setUtf8Mode\0on\0lockPty\0"
    "lock\0sendData\0dataReceived\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Konsole__Pty[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       6,    1,   44,    2, 0x0a,
       8,    1,   47,    2, 0x0a,
      10,    2,   50,    2, 0x0a,
      11,    0,   55,    2, 0x08,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void,

       0        // eod
};

void Konsole::Pty::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Pty *_t = static_cast<Pty *>(_o);
        switch (_id) {
        case 0: _t->receivedData((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->setUtf8Mode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->lockPty((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->sendData((*reinterpret_cast< const char*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->dataReceived(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Pty::*_t)(const char * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Pty::receivedData)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Konsole::Pty::staticMetaObject = {
    { &KPtyProcess::staticMetaObject, qt_meta_stringdata_Konsole__Pty.data,
      qt_meta_data_Konsole__Pty,  qt_static_metacall, 0, 0}
};


const QMetaObject *Konsole::Pty::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Konsole::Pty::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Konsole__Pty.stringdata))
        return static_cast<void*>(const_cast< Pty*>(this));
    return KPtyProcess::qt_metacast(_clname);
}

int Konsole::Pty::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = KPtyProcess::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Konsole::Pty::receivedData(const char * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
