/****************************************************************************
** Meta object code from reading C++ file 'lregister.h'
**
** Created: Fri Jul 8 15:15:34 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "lregister.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lregister.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Lregister[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      25,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Lregister[] = {
    "Lregister\0\0pB2_clicked()\0pB1_clicked()\0"
};

void Lregister::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Lregister *_t = static_cast<Lregister *>(_o);
        switch (_id) {
        case 0: _t->pB2_clicked(); break;
        case 1: _t->pB1_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Lregister::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Lregister::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Lregister,
      qt_meta_data_Lregister, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Lregister::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Lregister::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Lregister::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Lregister))
        return static_cast<void*>(const_cast< Lregister*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Lregister::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
