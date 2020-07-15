/****************************************************************************
** Meta object code from reading C++ file 'dialogsettings.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VitalSignsRadar_Demo/dialogsettings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogsettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DialogSettings_t {
    QByteArrayData data[11];
    char stringdata0[186];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DialogSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DialogSettings_t qt_meta_stringdata_DialogSettings = {
    {
QT_MOC_LITERAL(0, 0, 14), // "DialogSettings"
QT_MOC_LITERAL(1, 15, 21), // "on_buttonBox_accepted"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 24), // "on_pushButton_Ok_clicked"
QT_MOC_LITERAL(4, 63, 17), // "getUserComPortNum"
QT_MOC_LITERAL(5, 81, 17), // "getDataComPortNum"
QT_MOC_LITERAL(6, 99, 17), // "setUserComPortNum"
QT_MOC_LITERAL(7, 117, 7), // "portNum"
QT_MOC_LITERAL(8, 125, 17), // "setDataComPortNum"
QT_MOC_LITERAL(9, 143, 20), // "getHeartWfm_yAxisMax"
QT_MOC_LITERAL(10, 164, 21) // "getBreathWfm_yAxisMax"

    },
    "DialogSettings\0on_buttonBox_accepted\0"
    "\0on_pushButton_Ok_clicked\0getUserComPortNum\0"
    "getDataComPortNum\0setUserComPortNum\0"
    "portNum\0setDataComPortNum\0"
    "getHeartWfm_yAxisMax\0getBreathWfm_yAxisMax"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DialogSettings[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    1,   58,    2, 0x0a /* Public */,
       8,    1,   61,    2, 0x0a /* Public */,
       9,    0,   64,    2, 0x0a /* Public */,
      10,    0,   65,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString, QMetaType::QString,    7,
    QMetaType::QString, QMetaType::QString,    7,
    QMetaType::Double,
    QMetaType::Double,

       0        // eod
};

void DialogSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DialogSettings *_t = static_cast<DialogSettings *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_buttonBox_accepted(); break;
        case 1: _t->on_pushButton_Ok_clicked(); break;
        case 2: { QString _r = _t->getUserComPortNum();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 3: { QString _r = _t->getDataComPortNum();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 4: { QString _r = _t->setUserComPortNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 5: { QString _r = _t->setDataComPortNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 6: { double _r = _t->getHeartWfm_yAxisMax();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        case 7: { double _r = _t->getBreathWfm_yAxisMax();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject DialogSettings::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogSettings.data,
      qt_meta_data_DialogSettings,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DialogSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DialogSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DialogSettings.stringdata0))
        return static_cast<void*>(const_cast< DialogSettings*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
