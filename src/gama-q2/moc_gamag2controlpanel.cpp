/****************************************************************************
** Meta object code from reading C++ file 'gamag2controlpanel.h'
**
** Created: Wed Nov 7 11:02:41 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gamag2controlpanel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamag2controlpanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GamaQ2ControlPanel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
      38,   19,   19,   19, 0x08,
      65,   19,   19,   19, 0x08,
     107,   19,   19,   19, 0x08,
     132,   19,   19,   19, 0x08,
     180,   19,   19,   19, 0x08,
     221,   19,   19,   19, 0x08,
     262,   19,   19,   19, 0x08,
     315,   19,   19,   19, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GamaQ2ControlPanel[] = {
    "GamaQ2ControlPanel\0\0gamaCloseSignal()\0"
    "on_action_Exit_triggered()\0"
    "on_action_Connect_to_database_triggered()\0"
    "disable_input_data(bool)\0"
    "on_action_Import_configuration_file_triggered()\0"
    "on_action_Network_adjustment_triggered()\0"
    "on_action_Drop_schema_Tables_triggered()\0"
    "on_actionDelete_all_Data_from_the_Schema_triggered()\0"
    "on_actionDelete_Network_Configuration_triggered()\0"
};

void GamaQ2ControlPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GamaQ2ControlPanel *_t = static_cast<GamaQ2ControlPanel *>(_o);
        switch (_id) {
        case 0: _t->gamaCloseSignal(); break;
        case 1: _t->on_action_Exit_triggered(); break;
        case 2: _t->on_action_Connect_to_database_triggered(); break;
        case 3: _t->disable_input_data((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->on_action_Import_configuration_file_triggered(); break;
        case 5: _t->on_action_Network_adjustment_triggered(); break;
        case 6: _t->on_action_Drop_schema_Tables_triggered(); break;
        case 7: _t->on_actionDelete_all_Data_from_the_Schema_triggered(); break;
        case 8: _t->on_actionDelete_Network_Configuration_triggered(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GamaQ2ControlPanel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GamaQ2ControlPanel::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_GamaQ2ControlPanel,
      qt_meta_data_GamaQ2ControlPanel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GamaQ2ControlPanel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GamaQ2ControlPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GamaQ2ControlPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GamaQ2ControlPanel))
        return static_cast<void*>(const_cast< GamaQ2ControlPanel*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int GamaQ2ControlPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void GamaQ2ControlPanel::gamaCloseSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
