/****************************************************************************
** Meta object code from reading C++ file 'dbconnectdialog.h'
**
** Created: Wed Nov 7 11:02:46 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dbconnectdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dbconnectdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DBConnectDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      39,   16,   16,   16, 0x08,
      62,   16,   16,   16, 0x08,
     101,   16,   16,   16, 0x08,
     125,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DBConnectDialog[] = {
    "DBConnectDialog\0\0input_data_open(bool)\0"
    "switchStackedWidgets()\0"
    "on_pushButton_OpenFileDialog_clicked()\0"
    "on_buttonBox_rejected()\0on_buttonBox_accepted()\0"
};

void DBConnectDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DBConnectDialog *_t = static_cast<DBConnectDialog *>(_o);
        switch (_id) {
        case 0: _t->input_data_open((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->switchStackedWidgets(); break;
        case 2: _t->on_pushButton_OpenFileDialog_clicked(); break;
        case 3: _t->on_buttonBox_rejected(); break;
        case 4: _t->on_buttonBox_accepted(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DBConnectDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DBConnectDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DBConnectDialog,
      qt_meta_data_DBConnectDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DBConnectDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DBConnectDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DBConnectDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DBConnectDialog))
        return static_cast<void*>(const_cast< DBConnectDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int DBConnectDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void DBConnectDialog::input_data_open(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
