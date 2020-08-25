/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Harry_Plotter/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[21];
    char stringdata0[343];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 21), // "on_selectFile_clicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 23), // "on_gridBox_stateChanged"
QT_MOC_LITERAL(4, 58, 22), // "on_addFunction_clicked"
QT_MOC_LITERAL(5, 81, 22), // "on_resetButton_clicked"
QT_MOC_LITERAL(6, 104, 22), // "on_rangeButton_clicked"
QT_MOC_LITERAL(7, 127, 31), // "on_styleBox_currentIndexChanged"
QT_MOC_LITERAL(8, 159, 21), // "on_xFrom_valueChanged"
QT_MOC_LITERAL(9, 181, 19), // "on_xTo_valueChanged"
QT_MOC_LITERAL(10, 201, 21), // "on_yFrom_valueChanged"
QT_MOC_LITERAL(11, 223, 19), // "on_yTo_valueChanged"
QT_MOC_LITERAL(12, 243, 28), // "on_pointsNumber_valueChanged"
QT_MOC_LITERAL(13, 272, 14), // "deleteFunction"
QT_MOC_LITERAL(14, 287, 9), // "Function*"
QT_MOC_LITERAL(15, 297, 8), // "function"
QT_MOC_LITERAL(16, 306, 10), // "deleteFile"
QT_MOC_LITERAL(17, 317, 5), // "File*"
QT_MOC_LITERAL(18, 323, 4), // "file"
QT_MOC_LITERAL(19, 328, 4), // "plot"
QT_MOC_LITERAL(20, 333, 9) // "automatic"

    },
    "MainWindow\0on_selectFile_clicked\0\0"
    "on_gridBox_stateChanged\0on_addFunction_clicked\0"
    "on_resetButton_clicked\0on_rangeButton_clicked\0"
    "on_styleBox_currentIndexChanged\0"
    "on_xFrom_valueChanged\0on_xTo_valueChanged\0"
    "on_yFrom_valueChanged\0on_yTo_valueChanged\0"
    "on_pointsNumber_valueChanged\0"
    "deleteFunction\0Function*\0function\0"
    "deleteFile\0File*\0file\0plot\0automatic"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    1,   85,    2, 0x08 /* Private */,
       4,    0,   88,    2, 0x08 /* Private */,
       5,    0,   89,    2, 0x08 /* Private */,
       6,    0,   90,    2, 0x08 /* Private */,
       7,    1,   91,    2, 0x08 /* Private */,
       8,    1,   94,    2, 0x08 /* Private */,
       9,    1,   97,    2, 0x08 /* Private */,
      10,    1,  100,    2, 0x08 /* Private */,
      11,    1,  103,    2, 0x08 /* Private */,
      12,    1,  106,    2, 0x08 /* Private */,
      13,    1,  109,    2, 0x08 /* Private */,
      16,    1,  112,    2, 0x08 /* Private */,
      19,    1,  115,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, QMetaType::Bool,   20,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_selectFile_clicked(); break;
        case 1: _t->on_gridBox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_addFunction_clicked(); break;
        case 3: _t->on_resetButton_clicked(); break;
        case 4: _t->on_rangeButton_clicked(); break;
        case 5: _t->on_styleBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_xFrom_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->on_xTo_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->on_yFrom_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->on_yTo_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->on_pointsNumber_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->deleteFunction((*reinterpret_cast< Function*(*)>(_a[1]))); break;
        case 12: _t->deleteFile((*reinterpret_cast< File*(*)>(_a[1]))); break;
        case 13: _t->plot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
