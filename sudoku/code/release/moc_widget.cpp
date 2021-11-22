/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created: Tue 21. Sep 21:51:53 2021
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../widget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Widget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      32,   23,    7,    7, 0x0a,
      58,   52,    7,    7, 0x0a,
      79,    7,    7,    7, 0x08,
      96,    7,   92,    7, 0x08,
     110,    7,   92,    7, 0x08,
     121,    7,   92,    7, 0x08,
     132,    7,    7,    7, 0x08,
     151,    7,    7,    7, 0x08,
     166,    7,    7,    7, 0x08,
     183,    7,    7,    7, 0x08,
     198,    7,    7,    7, 0x08,
     217,    7,    7,    7, 0x08,
     245,  239,    7,    7, 0x08,
     270,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Widget[] = {
    "Widget\0\0refreshTable()\0fileName\0"
    "savingGame(QString)\0table\0"
    "openingGame(QString)\0cleanTable()\0int\0"
    "saveGameHow()\0saveGame()\0loadGame()\0"
    "newGame_VeryEasy()\0newGame_Easy()\0"
    "newGame_Normal()\0newGame_Hard()\0"
    "newGame_VeryHard()\0gameModeHelpChanged()\0"
    "event\0closeEvent(QCloseEvent*)\0"
    "tableChanged()\0"
};

const QMetaObject Widget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Widget,
      qt_meta_data_Widget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Widget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Widget))
        return static_cast<void*>(const_cast< Widget*>(this));
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: refreshTable(); break;
        case 1: savingGame((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: openingGame((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: cleanTable(); break;
        case 4: { int _r = saveGameHow();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 5: { int _r = saveGame();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 6: { int _r = loadGame();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 7: newGame_VeryEasy(); break;
        case 8: newGame_Easy(); break;
        case 9: newGame_Normal(); break;
        case 10: newGame_Hard(); break;
        case 11: newGame_VeryHard(); break;
        case 12: gameModeHelpChanged(); break;
        case 13: closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 14: tableChanged(); break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void Widget::refreshTable()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
