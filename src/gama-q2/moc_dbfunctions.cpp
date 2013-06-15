/****************************************************************************
** Meta object code from reading C++ file 'dbfunctions.h'
**
** Created: Wed Nov 7 11:02:44 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dbfunctions.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dbfunctions.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DropDeleteBase[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   16,   15,   15, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_DropDeleteBase[] = {
    "DropDeleteBase\0\0connected\0"
    "drop_or_delete_schema_tables(bool)\0"
};

void DropDeleteBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DropDeleteBase *_t = static_cast<DropDeleteBase *>(_o);
        switch (_id) {
        case 0: _t->drop_or_delete_schema_tables((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DropDeleteBase::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DropDeleteBase::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DropDeleteBase,
      qt_meta_data_DropDeleteBase, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DropDeleteBase::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DropDeleteBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DropDeleteBase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DropDeleteBase))
        return static_cast<void*>(const_cast< DropDeleteBase*>(this));
    return QWidget::qt_metacast(_clname);
}

int DropDeleteBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_DB_DeleteNetworkConfiguration[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      36,   31,   30,   30, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DB_DeleteNetworkConfiguration[] = {
    "DB_DeleteNetworkConfiguration\0\0name\0"
    "getConfigurationName(QString)\0"
};

void DB_DeleteNetworkConfiguration::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DB_DeleteNetworkConfiguration *_t = static_cast<DB_DeleteNetworkConfiguration *>(_o);
        switch (_id) {
        case 0: _t->getConfigurationName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DB_DeleteNetworkConfiguration::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DB_DeleteNetworkConfiguration::staticMetaObject = {
    { &DropDeleteBase::staticMetaObject, qt_meta_stringdata_DB_DeleteNetworkConfiguration,
      qt_meta_data_DB_DeleteNetworkConfiguration, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DB_DeleteNetworkConfiguration::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DB_DeleteNetworkConfiguration::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DB_DeleteNetworkConfiguration::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DB_DeleteNetworkConfiguration))
        return static_cast<void*>(const_cast< DB_DeleteNetworkConfiguration*>(this));
    return DropDeleteBase::qt_metacast(_clname);
}

int DB_DeleteNetworkConfiguration::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DropDeleteBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
