/****************************************************************************
** Meta object code from reading C++ file 'EditCarWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../untitled/EditCarWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EditCarWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EditCarWindow_t {
    QByteArrayData data[6];
    char stringdata[63];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EditCarWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EditCarWindow_t qt_meta_stringdata_EditCarWindow = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 6),
QT_MOC_LITERAL(2, 21, 0),
QT_MOC_LITERAL(3, 22, 11),
QT_MOC_LITERAL(4, 34, 13),
QT_MOC_LITERAL(5, 48, 14)
    },
    "EditCarWindow\0closed\0\0editClicked\0"
    "cancelClicked\0setEditEnabled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EditCarWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   35,    2, 0x08 /* Private */,
       4,    0,   36,    2, 0x08 /* Private */,
       5,    0,   37,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void EditCarWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EditCarWindow *_t = static_cast<EditCarWindow *>(_o);
        switch (_id) {
        case 0: _t->closed(); break;
        case 1: _t->editClicked(); break;
        case 2: _t->cancelClicked(); break;
        case 3: _t->setEditEnabled(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (EditCarWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EditCarWindow::closed)) {
                *result = 0;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject EditCarWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_EditCarWindow.data,
      qt_meta_data_EditCarWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *EditCarWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EditCarWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EditCarWindow.stringdata))
        return static_cast<void*>(const_cast< EditCarWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int EditCarWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void EditCarWindow::closed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
