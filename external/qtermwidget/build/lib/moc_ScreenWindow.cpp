/****************************************************************************
** Meta object code from reading C++ file 'ScreenWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../lib/ScreenWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ScreenWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Konsole__ScreenWindow_t {
    QByteArrayData data[7];
    char stringdata[89];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Konsole__ScreenWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Konsole__ScreenWindow_t qt_meta_stringdata_Konsole__ScreenWindow = {
    {
QT_MOC_LITERAL(0, 0, 21),
QT_MOC_LITERAL(1, 22, 13),
QT_MOC_LITERAL(2, 36, 0),
QT_MOC_LITERAL(3, 37, 8),
QT_MOC_LITERAL(4, 46, 4),
QT_MOC_LITERAL(5, 51, 16),
QT_MOC_LITERAL(6, 68, 19)
    },
    "Konsole::ScreenWindow\0outputChanged\0"
    "\0scrolled\0line\0selectionChanged\0"
    "notifyOutputChanged\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Konsole__ScreenWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06,
       3,    1,   35,    2, 0x06,
       5,    0,   38,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       6,    0,   39,    2, 0x0a,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Konsole::ScreenWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ScreenWindow *_t = static_cast<ScreenWindow *>(_o);
        switch (_id) {
        case 0: _t->outputChanged(); break;
        case 1: _t->scrolled((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->selectionChanged(); break;
        case 3: _t->notifyOutputChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ScreenWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScreenWindow::outputChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (ScreenWindow::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScreenWindow::scrolled)) {
                *result = 1;
            }
        }
        {
            typedef void (ScreenWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScreenWindow::selectionChanged)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject Konsole::ScreenWindow::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Konsole__ScreenWindow.data,
      qt_meta_data_Konsole__ScreenWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *Konsole::ScreenWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Konsole::ScreenWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Konsole__ScreenWindow.stringdata))
        return static_cast<void*>(const_cast< ScreenWindow*>(this));
    return QObject::qt_metacast(_clname);
}

int Konsole::ScreenWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Konsole::ScreenWindow::outputChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Konsole::ScreenWindow::scrolled(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Konsole::ScreenWindow::selectionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
