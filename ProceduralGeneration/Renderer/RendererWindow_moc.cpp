/****************************************************************************
** Meta object code from reading C++ file 'RendererWindow.h'
**
** Created: Wed Apr 8 14:23:15 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "RendererWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RendererWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RendererWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,
      36,   15,   15,   15, 0x05,
      47,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      58,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RendererWindow[] = {
    "RendererWindow\0\0characterSelected()\0"
    "moveMade()\0attacked()\0Update()\0"
};

void RendererWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RendererWindow *_t = static_cast<RendererWindow *>(_o);
        switch (_id) {
        case 0: _t->characterSelected(); break;
        case 1: _t->moveMade(); break;
        case 2: _t->attacked(); break;
        case 3: _t->Update(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData RendererWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RendererWindow::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_RendererWindow,
      qt_meta_data_RendererWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RendererWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RendererWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RendererWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RendererWindow))
        return static_cast<void*>(const_cast< RendererWindow*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int RendererWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void RendererWindow::characterSelected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void RendererWindow::moveMade()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void RendererWindow::attacked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
