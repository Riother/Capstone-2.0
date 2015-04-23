/****************************************************************************
** Meta object code from reading C++ file 'LabeledSpinbox.h'
**
** Created: Wed Apr 15 14:23:56 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "LabeledSpinbox.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LabeledSpinbox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LabeledSpinbox[] = {

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
      16,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      31,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_LabeledSpinbox[] = {
    "LabeledSpinbox\0\0valueChanged()\0"
    "spinboxValueChanged()\0"
};

void LabeledSpinbox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LabeledSpinbox *_t = static_cast<LabeledSpinbox *>(_o);
        switch (_id) {
        case 0: _t->valueChanged(); break;
        case 1: _t->spinboxValueChanged(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData LabeledSpinbox::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LabeledSpinbox::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LabeledSpinbox,
      qt_meta_data_LabeledSpinbox, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LabeledSpinbox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LabeledSpinbox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LabeledSpinbox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LabeledSpinbox))
        return static_cast<void*>(const_cast< LabeledSpinbox*>(this));
    return QWidget::qt_metacast(_clname);
}

int LabeledSpinbox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void LabeledSpinbox::valueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
