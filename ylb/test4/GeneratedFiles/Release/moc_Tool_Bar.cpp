/****************************************************************************
** Meta object code from reading C++ file 'Tool_Bar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Tool_Bar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Tool_Bar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ToolBar_t {
    QByteArrayData data[12];
    char stringdata0[114];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ToolBar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ToolBar_t qt_meta_stringdata_ToolBar = {
    {
QT_MOC_LITERAL(0, 0, 7), // "ToolBar"
QT_MOC_LITERAL(1, 8, 8), // "judgePic"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 8), // "printPic"
QT_MOC_LITERAL(4, 27, 7), // "savePic"
QT_MOC_LITERAL(5, 35, 7), // "openPic"
QT_MOC_LITERAL(6, 43, 9), // "deletePic"
QT_MOC_LITERAL(7, 53, 10), // "enlargePic"
QT_MOC_LITERAL(8, 64, 9), // "shrinkPic"
QT_MOC_LITERAL(9, 74, 10), // "rotatelPic"
QT_MOC_LITERAL(10, 85, 10), // "rotaterPic"
QT_MOC_LITERAL(11, 96, 17) // "loadImageResource"

    },
    "ToolBar\0judgePic\0\0printPic\0savePic\0"
    "openPic\0deletePic\0enlargePic\0shrinkPic\0"
    "rotatelPic\0rotaterPic\0loadImageResource"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ToolBar[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    0,   72,    2, 0x08 /* Private */,
      11,    0,   73,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ToolBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ToolBar *_t = static_cast<ToolBar *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->judgePic(); break;
        case 1: _t->printPic(); break;
        case 2: _t->savePic(); break;
        case 3: _t->openPic(); break;
        case 4: _t->deletePic(); break;
        case 5: _t->enlargePic(); break;
        case 6: _t->shrinkPic(); break;
        case 7: _t->rotatelPic(); break;
        case 8: _t->rotaterPic(); break;
        case 9: _t->loadImageResource(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ToolBar::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ToolBar.data,
      qt_meta_data_ToolBar,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ToolBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ToolBar::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ToolBar.stringdata0))
        return static_cast<void*>(const_cast< ToolBar*>(this));
    return QWidget::qt_metacast(_clname);
}

int ToolBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
