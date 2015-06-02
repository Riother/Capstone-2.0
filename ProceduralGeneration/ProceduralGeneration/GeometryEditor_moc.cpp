/****************************************************************************
** Meta object code from reading C++ file 'GeometryEditor.h'
**
** Created: Wed May 20 15:02:58 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "GeometryEditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GeometryEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GeometryEditor[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,
      31,   15,   15,   15, 0x08,
      42,   15,   15,   15, 0x08,
      53,   15,   15,   15, 0x08,
      66,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GeometryEditor[] = {
    "GeometryEditor\0\0updateValues()\0"
    "MakeRoom()\0MakeDome()\0MakeSphere()\0"
    "MakeColumn()\0"
};

void GeometryEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GeometryEditor *_t = static_cast<GeometryEditor *>(_o);
        switch (_id) {
        case 0: _t->updateValues(); break;
        case 1: _t->MakeRoom(); break;
        case 2: _t->MakeDome(); break;
        case 3: _t->MakeSphere(); break;
        case 4: _t->MakeColumn(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData GeometryEditor::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GeometryEditor::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_GeometryEditor,
      qt_meta_data_GeometryEditor, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GeometryEditor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GeometryEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GeometryEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GeometryEditor))
        return static_cast<void*>(const_cast< GeometryEditor*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int GeometryEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
