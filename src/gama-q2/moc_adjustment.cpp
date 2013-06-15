/****************************************************************************
** Meta object code from reading C++ file 'adjustment.h'
**
** Created: Wed Nov 7 11:02:43 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "adjustment.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'adjustment.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Adjustment[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   12,   11,   11, 0x05,
      43,   11,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_Adjustment[] = {
    "Adjustment\0\0solved\0adjustment_signal(bool)\0"
    "acord_signal()\0"
};

void Adjustment::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Adjustment *_t = static_cast<Adjustment *>(_o);
        switch (_id) {
        case 0: _t->adjustment_signal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->acord_signal(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Adjustment::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Adjustment::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Adjustment,
      qt_meta_data_Adjustment, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Adjustment::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Adjustment::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Adjustment::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Adjustment))
        return static_cast<void*>(const_cast< Adjustment*>(this));
    return QObject::qt_metacast(_clname);
}

int Adjustment::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Adjustment::adjustment_signal(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Adjustment::acord_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
