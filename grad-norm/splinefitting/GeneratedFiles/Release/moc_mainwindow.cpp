/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_mainwindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      22,   11,   11,   11, 0x08,
      29,   11,   11,   11, 0x08,
      37,   11,   11,   11, 0x08,
      46,   11,   11,   11, 0x08,
      72,   63,   11,   11, 0x08,
      97,   11,   11,   11, 0x08,
     116,   11,   11,   11, 0x08,
     136,   11,   11,   11, 0x08,
     154,   11,   11,   11, 0x08,
     177,   11,   11,   11, 0x08,
     192,   11,   11,   11, 0x08,
     207,   11,   11,   11, 0x08,
     225,   11,   11,   11, 0x08,
     242,   11,   11,   11, 0x08,
     257,   11,   11,   11, 0x08,
     289,   11,   11,   11, 0x08,
     301,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_mainwindow[] = {
    "mainwindow\0\0newFile()\0open()\0about()\0"
    "saveAs()\0openRecentFile()\0bVisible\0"
    "set_window_visible(bool)\0meshwindow_close()\0"
    "knotswindow_close()\0fitwindow_close()\0"
    "mesh_parametrization()\0mesh_fitting()\0"
    "adjust_upper()\0input_parameter()\0"
    "load_curvature()\0adjust_knots()\0"
    "adjust_knots_by_fitting_error()\0"
    "add_knots()\0add_horizon_knots()\0"
};

void mainwindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        mainwindow *_t = static_cast<mainwindow *>(_o);
        switch (_id) {
        case 0: _t->newFile(); break;
        case 1: _t->open(); break;
        case 2: _t->about(); break;
        case 3: _t->saveAs(); break;
        case 4: _t->openRecentFile(); break;
        case 5: _t->set_window_visible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->meshwindow_close(); break;
        case 7: _t->knotswindow_close(); break;
        case 8: _t->fitwindow_close(); break;
        case 9: _t->mesh_parametrization(); break;
        case 10: _t->mesh_fitting(); break;
        case 11: _t->adjust_upper(); break;
        case 12: _t->input_parameter(); break;
        case 13: _t->load_curvature(); break;
        case 14: _t->adjust_knots(); break;
        case 15: _t->adjust_knots_by_fitting_error(); break;
        case 16: _t->add_knots(); break;
        case 17: _t->add_horizon_knots(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData mainwindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject mainwindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_mainwindow,
      qt_meta_data_mainwindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &mainwindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *mainwindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *mainwindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_mainwindow))
        return static_cast<void*>(const_cast< mainwindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int mainwindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
