/****************************************************************************
** Meta object code from reading C++ file 'dialogsave.h'
**
** Created: Thu 23. Sep 09:54:15 2021
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dialogsave.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogsave.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DialogSave[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   12,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      39,   11,   11,   11, 0x08,
      60,   11,   11,   11, 0x08,
      83,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DialogSave[] = {
    "DialogSave\0\0fileName\0sendData(QString)\0"
    "on_btnSave_clicked()\0on_btnCancel_clicked()\0"
    "showEvent(QShowEvent*)\0"
};

const QMetaObject DialogSave::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogSave,
      qt_meta_data_DialogSave, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DialogSave::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DialogSave::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DialogSave::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DialogSave))
        return static_cast<void*>(const_cast< DialogSave*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogSave::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sendData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: on_btnSave_clicked(); break;
        case 2: on_btnCancel_clicked(); break;
        case 3: showEvent((*reinterpret_cast< QShowEvent*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void DialogSave::sendData(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
