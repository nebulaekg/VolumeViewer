/****************************************************************************
** Meta object code from reading C++ file 'dialog_bg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dialog_bg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog_bg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Dialog_Bg_t {
    QByteArrayData data[10];
    char stringdata[155];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dialog_Bg_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dialog_Bg_t qt_meta_stringdata_Dialog_Bg = {
    {
QT_MOC_LITERAL(0, 0, 9), // "Dialog_Bg"
QT_MOC_LITERAL(1, 10, 12), // "sendbgparams"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 19), // "on_reset_bg_clicked"
QT_MOC_LITERAL(4, 44, 17), // "on_set_bg_clicked"
QT_MOC_LITERAL(5, 62, 24), // "on_bg_col_r_valueChanged"
QT_MOC_LITERAL(6, 87, 4), // "arg1"
QT_MOC_LITERAL(7, 92, 24), // "on_bg_col_g_valueChanged"
QT_MOC_LITERAL(8, 117, 24), // "on_bg_col_b_valueChanged"
QT_MOC_LITERAL(9, 142, 12) // "canvasupdate"

    },
    "Dialog_Bg\0sendbgparams\0\0on_reset_bg_clicked\0"
    "on_set_bg_clicked\0on_bg_col_r_valueChanged\0"
    "arg1\0on_bg_col_g_valueChanged\0"
    "on_bg_col_b_valueChanged\0canvasupdate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dialog_Bg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   56,    2, 0x08 /* Private */,
       4,    0,   57,    2, 0x08 /* Private */,
       5,    1,   58,    2, 0x08 /* Private */,
       7,    1,   61,    2, 0x08 /* Private */,
       8,    1,   64,    2, 0x08 /* Private */,
       9,    0,   67,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,    2,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,

       0        // eod
};

void Dialog_Bg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Dialog_Bg *_t = static_cast<Dialog_Bg *>(_o);
        switch (_id) {
        case 0: _t->sendbgparams((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 1: _t->on_reset_bg_clicked(); break;
        case 2: _t->on_set_bg_clicked(); break;
        case 3: _t->on_bg_col_r_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_bg_col_g_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_bg_col_b_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->canvasupdate(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Dialog_Bg::*_t)(double , double , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dialog_Bg::sendbgparams)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Dialog_Bg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Dialog_Bg.data,
      qt_meta_data_Dialog_Bg,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Dialog_Bg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dialog_Bg::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Dialog_Bg.stringdata))
        return static_cast<void*>(const_cast< Dialog_Bg*>(this));
    return QDialog::qt_metacast(_clname);
}

int Dialog_Bg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Dialog_Bg::sendbgparams(double _t1, double _t2, double _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
