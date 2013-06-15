/****************************************************************************
** Meta object code from reading C++ file 'importconfigurationfile.h'
**
** Created: Wed Nov 7 11:02:41 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "importconfigurationfile.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'importconfigurationfile.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ImportConfigurationFile[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      25,   24,   24,   24, 0x08,
      61,   56,   24,   24, 0x08,
     112,   24,   24,   24, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ImportConfigurationFile[] = {
    "ImportConfigurationFile\0\0"
    "on_pushButton_Cancel_clicked()\0arg1\0"
    "on_lineEdit_ConfigurationName_textChanged(QString)\0"
    "on_pushButton_Import_clicked()\0"
};

void ImportConfigurationFile::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ImportConfigurationFile *_t = static_cast<ImportConfigurationFile *>(_o);
        switch (_id) {
        case 0: _t->on_pushButton_Cancel_clicked(); break;
        case 1: _t->on_lineEdit_ConfigurationName_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->on_pushButton_Import_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ImportConfigurationFile::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ImportConfigurationFile::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ImportConfigurationFile,
      qt_meta_data_ImportConfigurationFile, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ImportConfigurationFile::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ImportConfigurationFile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ImportConfigurationFile::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImportConfigurationFile))
        return static_cast<void*>(const_cast< ImportConfigurationFile*>(this));
    return QWidget::qt_metacast(_clname);
}

int ImportConfigurationFile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
