/****************************************************************************
** Meta object code from reading C++ file 'selectconfiguration.h'
**
** Created: Wed Nov 7 11:02:42 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "selectconfiguration.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'selectconfiguration.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SelectConfiguration[] = {

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
      26,   21,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
      60,   55,   20,   20, 0x08,
     122,  111,   20,   20, 0x08,
     185,   20,   20,   20, 0x08,
     216,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SelectConfiguration[] = {
    "SelectConfiguration\0\0conf\0"
    "selectConfiguration(QString)\0arg1\0"
    "on_lineEdit_ConfigurationName_textChanged(QString)\0"
    "row,column\0"
    "on_tableWidget_ExistingConfigurationNames_cellClicked(int,int)\0"
    "on_pushButton_Cancel_clicked()\0"
    "on_pushButton_Select_clicked()\0"
};

void SelectConfiguration::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SelectConfiguration *_t = static_cast<SelectConfiguration *>(_o);
        switch (_id) {
        case 0: _t->selectConfiguration((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->on_lineEdit_ConfigurationName_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_tableWidget_ExistingConfigurationNames_cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->on_pushButton_Cancel_clicked(); break;
        case 4: _t->on_pushButton_Select_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SelectConfiguration::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SelectConfiguration::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SelectConfiguration,
      qt_meta_data_SelectConfiguration, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SelectConfiguration::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SelectConfiguration::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SelectConfiguration::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SelectConfiguration))
        return static_cast<void*>(const_cast< SelectConfiguration*>(this));
    return QWidget::qt_metacast(_clname);
}

int SelectConfiguration::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void SelectConfiguration::selectConfiguration(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
