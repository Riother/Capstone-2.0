/****************************************************************************
** Meta object code from reading C++ file 'LabeledCheckBox.h'
**
** Created: Thu Apr 23 11:28:26 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "LabeledCheckBox.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LabeledCheckBox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LabeledCheckBox[] = {

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
      17,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      32,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_LabeledCheckBox[] = {
    "LabeledCheckBox\0\0stateChanged()\0"
    "checkedUnchecked()\0"
};

void LabeledCheckBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LabeledCheckBox *_t = static_cast<LabeledCheckBox *>(_o);
        switch (_id) {
        case 0: _t->stateChanged(); break;
        case 1: _t->checkedUnchecked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData LabeledCheckBox::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LabeledCheckBox::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LabeledCheckBox,
      qt_meta_data_LabeledCheckBox, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LabeledCheckBox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LabeledCheckBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LabeledCheckBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LabeledCheckBox))
        return static_cast<void*>(const_cast< LabeledCheckBox*>(this));
    return QWidget::qt_metacast(_clname);
}

int LabeledCheckBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void LabeledCheckBox::stateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
