/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VitalSignsRadar_Demo/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[26];
    char stringdata0[396];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 17), // "gui_statusChanged"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 14), // "serialRecieved"
QT_MOC_LITERAL(4, 45, 10), // "nextPower2"
QT_MOC_LITERAL(5, 56, 3), // "num"
QT_MOC_LITERAL(6, 60, 15), // "parseValueFloat"
QT_MOC_LITERAL(7, 76, 4), // "data"
QT_MOC_LITERAL(8, 81, 8), // "valuePos"
QT_MOC_LITERAL(9, 90, 9), // "valueSize"
QT_MOC_LITERAL(10, 100, 16), // "parseValueUint32"
QT_MOC_LITERAL(11, 117, 16), // "parseValueUint16"
QT_MOC_LITERAL(12, 134, 15), // "parseValueInt16"
QT_MOC_LITERAL(13, 150, 14), // "serialPortFind"
QT_MOC_LITERAL(14, 165, 16), // "serialPortConfig"
QT_MOC_LITERAL(15, 182, 12), // "QSerialPort*"
QT_MOC_LITERAL(16, 195, 6), // "serial"
QT_MOC_LITERAL(17, 202, 8), // "baudrate"
QT_MOC_LITERAL(18, 211, 11), // "dataPortNum"
QT_MOC_LITERAL(19, 223, 11), // "processData"
QT_MOC_LITERAL(20, 235, 27), // "on_pushButton_start_clicked"
QT_MOC_LITERAL(21, 263, 26), // "on_pushButton_stop_clicked"
QT_MOC_LITERAL(22, 290, 27), // "on_pushButton_pause_clicked"
QT_MOC_LITERAL(23, 318, 29), // "on_pushButton_Refresh_clicked"
QT_MOC_LITERAL(24, 348, 30), // "on_pushButton_settings_clicked"
QT_MOC_LITERAL(25, 379, 16) // "gui_statusUpdate"

    },
    "MainWindow\0gui_statusChanged\0\0"
    "serialRecieved\0nextPower2\0num\0"
    "parseValueFloat\0data\0valuePos\0valueSize\0"
    "parseValueUint32\0parseValueUint16\0"
    "parseValueInt16\0serialPortFind\0"
    "serialPortConfig\0QSerialPort*\0serial\0"
    "baudrate\0dataPortNum\0processData\0"
    "on_pushButton_start_clicked\0"
    "on_pushButton_stop_clicked\0"
    "on_pushButton_pause_clicked\0"
    "on_pushButton_Refresh_clicked\0"
    "on_pushButton_settings_clicked\0"
    "gui_statusUpdate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   95,    2, 0x08 /* Private */,
       4,    1,   96,    2, 0x08 /* Private */,
       6,    3,   99,    2, 0x08 /* Private */,
      10,    3,  106,    2, 0x08 /* Private */,
      11,    3,  113,    2, 0x08 /* Private */,
      12,    3,  120,    2, 0x08 /* Private */,
      13,    0,  127,    2, 0x08 /* Private */,
      14,    3,  128,    2, 0x08 /* Private */,
      19,    0,  135,    2, 0x08 /* Private */,
      20,    0,  136,    2, 0x08 /* Private */,
      21,    0,  137,    2, 0x08 /* Private */,
      22,    0,  138,    2, 0x08 /* Private */,
      23,    0,  139,    2, 0x08 /* Private */,
      24,    0,  140,    2, 0x08 /* Private */,
      25,    0,  141,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Int, QMetaType::Int,    5,
    QMetaType::Float, QMetaType::QByteArray, QMetaType::Int, QMetaType::Int,    7,    8,    9,
    QMetaType::UInt, QMetaType::QByteArray, QMetaType::Int, QMetaType::Int,    7,    8,    9,
    QMetaType::UShort, QMetaType::QByteArray, QMetaType::Int, QMetaType::Int,    7,    8,    9,
    QMetaType::Short, QMetaType::QByteArray, QMetaType::Int, QMetaType::Int,    7,    8,    9,
    QMetaType::Bool,
    QMetaType::Bool, 0x80000000 | 15, QMetaType::Int, QMetaType::QString,   16,   17,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->gui_statusChanged(); break;
        case 1: _t->serialRecieved(); break;
        case 2: { int _r = _t->nextPower2((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { float _r = _t->parseValueFloat((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = _r; }  break;
        case 4: { quint32 _r = _t->parseValueUint32((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< quint32*>(_a[0]) = _r; }  break;
        case 5: { quint16 _r = _t->parseValueUint16((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = _r; }  break;
        case 6: { qint16 _r = _t->parseValueInt16((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< qint16*>(_a[0]) = _r; }  break;
        case 7: { bool _r = _t->serialPortFind();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: { bool _r = _t->serialPortConfig((*reinterpret_cast< QSerialPort*(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 9: _t->processData(); break;
        case 10: _t->on_pushButton_start_clicked(); break;
        case 11: _t->on_pushButton_stop_clicked(); break;
        case 12: _t->on_pushButton_pause_clicked(); break;
        case 13: _t->on_pushButton_Refresh_clicked(); break;
        case 14: _t->on_pushButton_settings_clicked(); break;
        case 15: _t->gui_statusUpdate(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QSerialPort* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::gui_statusChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::gui_statusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
