/****************************************************************************
** Meta object code from reading C++ file 'MeshSubWindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MeshSubWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MeshSubWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MeshSubWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      42,   30,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      80,   77,   14,   14, 0x08,
     110,  107,   14,   14, 0x08,
     138,  135,   14,   14, 0x08,
     169,  135,   14,   14, 0x08,
     196,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MeshSubWindow[] = {
    "MeshSubWindow\0\0window_close()\0surfacedata\0"
    "surfacedata_changed(CSurfaceData*)\0"
    "ov\0set_origin_mesh_view(bool)\0cv\0"
    "set_curvature_show(bool)\0av\0"
    "set_adjustpoints_enabled(bool)\0"
    "set_adjusted_enabled(bool)\0updateStatusBar()\0"
};

void MeshSubWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MeshSubWindow *_t = static_cast<MeshSubWindow *>(_o);
        switch (_id) {
        case 0: _t->window_close(); break;
        case 1: _t->surfacedata_changed((*reinterpret_cast< CSurfaceData*(*)>(_a[1]))); break;
        case 2: _t->set_origin_mesh_view((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->set_curvature_show((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->set_adjustpoints_enabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->set_adjusted_enabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->updateStatusBar(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MeshSubWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MeshSubWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MeshSubWindow,
      qt_meta_data_MeshSubWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MeshSubWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MeshSubWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MeshSubWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MeshSubWindow))
        return static_cast<void*>(const_cast< MeshSubWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MeshSubWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void MeshSubWindow::window_close()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MeshSubWindow::surfacedata_changed(CSurfaceData * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
