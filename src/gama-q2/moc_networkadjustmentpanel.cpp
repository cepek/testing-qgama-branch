/****************************************************************************
** Meta object code from reading C++ file 'networkadjustmentpanel.h'
**
** Created: Wed Nov 7 11:02:42 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "networkadjustmentpanel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'networkadjustmentpanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_NetworkAdjustmentPanel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      29,   24,   23,   23, 0x08,
      66,   59,   23,   23, 0x08,
      99,   23,   23,   23, 0x28,
     128,   23,   23,   23, 0x08,
     156,   59,   23,   23, 0x08,
     188,   23,   23,   23, 0x28,
     221,  216,   23,   23, 0x08,
     241,   23,   23,   23, 0x08,
     290,   23,   23,   23, 0x08,
     349,   23,   23,   23, 0x08,
     377,   23,   23,   23, 0x08,
     415,   23,   23,   23, 0x08,
     441,   23,   23,   23, 0x08,
     497,   23,   23,   23, 0x08,
     537,  531,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_NetworkAdjustmentPanel[] = {
    "NetworkAdjustmentPanel\0\0conf\0"
    "getConfigurationName(QString)\0solved\0"
    "draw_network_configuration(bool)\0"
    "draw_network_configuration()\0"
    "update_point_editor_table()\0"
    "update_adjustment_results(bool)\0"
    "update_adjustment_results()\0text\0"
    "status_bar(QString)\0"
    "on_actionSave_XML_adjustment_results_triggered()\0"
    "on_actionSave_adjustment_results_as_plain_text_triggered()\0"
    "on_action_Close_triggered()\0"
    "on_actionSave_as_SQL_file_triggered()\0"
    "on_action_Run_triggered()\0"
    "on_actionSave_network_configuration_outline_triggered()\0"
    "on_actionOutline_draw_triggered()\0"
    "event\0closeEvent(QCloseEvent*)\0"
};

void NetworkAdjustmentPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        NetworkAdjustmentPanel *_t = static_cast<NetworkAdjustmentPanel *>(_o);
        switch (_id) {
        case 0: _t->getConfigurationName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->draw_network_configuration((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->draw_network_configuration(); break;
        case 3: _t->update_point_editor_table(); break;
        case 4: _t->update_adjustment_results((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->update_adjustment_results(); break;
        case 6: _t->status_bar((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->on_actionSave_XML_adjustment_results_triggered(); break;
        case 8: _t->on_actionSave_adjustment_results_as_plain_text_triggered(); break;
        case 9: _t->on_action_Close_triggered(); break;
        case 10: _t->on_actionSave_as_SQL_file_triggered(); break;
        case 11: _t->on_action_Run_triggered(); break;
        case 12: _t->on_actionSave_network_configuration_outline_triggered(); break;
        case 13: _t->on_actionOutline_draw_triggered(); break;
        case 14: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData NetworkAdjustmentPanel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject NetworkAdjustmentPanel::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_NetworkAdjustmentPanel,
      qt_meta_data_NetworkAdjustmentPanel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &NetworkAdjustmentPanel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *NetworkAdjustmentPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *NetworkAdjustmentPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_NetworkAdjustmentPanel))
        return static_cast<void*>(const_cast< NetworkAdjustmentPanel*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int NetworkAdjustmentPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
