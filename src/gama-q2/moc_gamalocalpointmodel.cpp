/****************************************************************************
** Meta object code from reading C++ file 'gamalocalpointmodel.h'
**
** Created: Wed Nov 7 11:02:44 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gamalocalpointmodel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamalocalpointmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GamaLocalPointModel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_GamaLocalPointModel[] = {
    "GamaLocalPointModel\0\0warning(QString)\0"
};

void GamaLocalPointModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GamaLocalPointModel *_t = static_cast<GamaLocalPointModel *>(_o);
        switch (_id) {
        case 0: _t->warning((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GamaLocalPointModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GamaLocalPointModel::staticMetaObject = {
    { &QAbstractTableModel::staticMetaObject, qt_meta_stringdata_GamaLocalPointModel,
      qt_meta_data_GamaLocalPointModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GamaLocalPointModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GamaLocalPointModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GamaLocalPointModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GamaLocalPointModel))
        return static_cast<void*>(const_cast< GamaLocalPointModel*>(this));
    return QAbstractTableModel::qt_metacast(_clname);
}

int GamaLocalPointModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void GamaLocalPointModel::warning(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
