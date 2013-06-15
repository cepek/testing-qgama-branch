/****************************************************************************
** Meta object code from reading C++ file 'drawsettings.h'
**
** Created: Wed Nov 7 11:02:44 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "drawsettings.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'drawsettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DrawSettings[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      23,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DrawSettings[] = {
    "DrawSettings\0\0redraw()\0"
    "on_pushButtonRedraw_clicked()\0"
};

void DrawSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DrawSettings *_t = static_cast<DrawSettings *>(_o);
        switch (_id) {
        case 0: _t->redraw(); break;
        case 1: _t->on_pushButtonRedraw_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData DrawSettings::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DrawSettings::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DrawSettings,
      qt_meta_data_DrawSettings, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DrawSettings::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DrawSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DrawSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DrawSettings))
        return static_cast<void*>(const_cast< DrawSettings*>(this));
    return QWidget::qt_metacast(_clname);
}

int DrawSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void DrawSettings::redraw()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
