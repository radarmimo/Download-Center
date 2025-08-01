/****************************************************************************
** Meta object code from reading C++ file 'qcustomplot.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "qcustomplot.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCore/qmetatype.h>
#include <QtCore/QSharedPointer>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qcustomplot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_QCPPainter_t {
    uint offsetsAndSizes[14];
    char stringdata0[11];
    char stringdata1[12];
    char stringdata2[10];
    char stringdata3[13];
    char stringdata4[12];
    char stringdata5[14];
    char stringdata6[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPPainter_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPPainter_t qt_meta_stringdata_QCPPainter = {
    {
        QT_MOC_LITERAL(0, 10),  // "QCPPainter"
        QT_MOC_LITERAL(11, 11),  // "PainterMode"
        QT_MOC_LITERAL(23, 9),  // "pmDefault"
        QT_MOC_LITERAL(33, 12),  // "pmVectorized"
        QT_MOC_LITERAL(46, 11),  // "pmNoCaching"
        QT_MOC_LITERAL(58, 13),  // "pmNonCosmetic"
        QT_MOC_LITERAL(72, 12)   // "PainterModes"
    },
    "QCPPainter",
    "PainterMode",
    "pmDefault",
    "pmVectorized",
    "pmNoCaching",
    "pmNonCosmetic",
    "PainterModes"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPPainter[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       2,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    4,   24,
       6,    1, 0x1,    4,   32,

 // enum data: key, value
       2, uint(QCPPainter::pmDefault),
       3, uint(QCPPainter::pmVectorized),
       4, uint(QCPPainter::pmNoCaching),
       5, uint(QCPPainter::pmNonCosmetic),
       2, uint(QCPPainter::pmDefault),
       3, uint(QCPPainter::pmVectorized),
       4, uint(QCPPainter::pmNoCaching),
       5, uint(QCPPainter::pmNonCosmetic),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPPainter::staticMetaObject = { {
    QtPrivate::MetaObjectForType<QPainter>::value,
    qt_meta_stringdata_QCPPainter.offsetsAndSizes,
    qt_meta_data_QCPPainter,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPPainter_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPPainter, std::true_type>
    >,
    nullptr
} };

namespace {
struct qt_meta_stringdata_QCPLayer_t {
    uint offsetsAndSizes[24];
    char stringdata0[9];
    char stringdata1[11];
    char stringdata2[13];
    char stringdata3[5];
    char stringdata4[6];
    char stringdata5[9];
    char stringdata6[21];
    char stringdata7[8];
    char stringdata8[5];
    char stringdata9[10];
    char stringdata10[10];
    char stringdata11[11];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPLayer_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPLayer_t qt_meta_stringdata_QCPLayer = {
    {
        QT_MOC_LITERAL(0, 8),  // "QCPLayer"
        QT_MOC_LITERAL(9, 10),  // "parentPlot"
        QT_MOC_LITERAL(20, 12),  // "QCustomPlot*"
        QT_MOC_LITERAL(33, 4),  // "name"
        QT_MOC_LITERAL(38, 5),  // "index"
        QT_MOC_LITERAL(44, 8),  // "children"
        QT_MOC_LITERAL(53, 20),  // "QList<QCPLayerable*>"
        QT_MOC_LITERAL(74, 7),  // "visible"
        QT_MOC_LITERAL(82, 4),  // "mode"
        QT_MOC_LITERAL(87, 9),  // "LayerMode"
        QT_MOC_LITERAL(97, 9),  // "lmLogical"
        QT_MOC_LITERAL(107, 10)   // "lmBuffered"
    },
    "QCPLayer",
    "parentPlot",
    "QCustomPlot*",
    "name",
    "index",
    "children",
    "QList<QCPLayerable*>",
    "visible",
    "mode",
    "LayerMode",
    "lmLogical",
    "lmBuffered"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPLayer[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       6,   14, // properties
       1,   44, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, 0x80000000 | 2, 0x00015009, uint(-1), 0,
       3, QMetaType::QString, 0x00015001, uint(-1), 0,
       4, QMetaType::Int, 0x00015001, uint(-1), 0,
       5, 0x80000000 | 6, 0x00015009, uint(-1), 0,
       7, QMetaType::Bool, 0x00015103, uint(-1), 0,
       8, 0x80000000 | 9, 0x0001510b, uint(-1), 0,

 // enums: name, alias, flags, count, data
       9,    9, 0x0,    2,   49,

 // enum data: key, value
      10, uint(QCPLayer::lmLogical),
      11, uint(QCPLayer::lmBuffered),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPLayer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_QCPLayer.offsetsAndSizes,
    qt_meta_data_QCPLayer,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPLayer_t,
        // property 'parentPlot'
        QtPrivate::TypeAndForceComplete<QCustomPlot*, std::true_type>,
        // property 'name'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'index'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'children'
        QtPrivate::TypeAndForceComplete<QList<QCPLayerable*>, std::true_type>,
        // property 'visible'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'mode'
        QtPrivate::TypeAndForceComplete<LayerMode, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPLayer, std::true_type>
    >,
    nullptr
} };

void QCPLayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCustomPlot* >(); break;
        case 3:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QCPLayerable*> >(); break;
        }
    }
else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPLayer *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QCustomPlot**>(_v) = _t->parentPlot(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->name(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->index(); break;
        case 3: *reinterpret_cast< QList<QCPLayerable*>*>(_v) = _t->children(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->visible(); break;
        case 5: *reinterpret_cast< LayerMode*>(_v) = _t->mode(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPLayer *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 4: _t->setVisible(*reinterpret_cast< bool*>(_v)); break;
        case 5: _t->setMode(*reinterpret_cast< LayerMode*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_o;
}

const QMetaObject *QCPLayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPLayer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPLayer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QCPLayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
namespace {
struct qt_meta_stringdata_QCPLayerable_t {
    uint offsetsAndSizes[26];
    char stringdata0[13];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[10];
    char stringdata4[9];
    char stringdata5[9];
    char stringdata6[6];
    char stringdata7[8];
    char stringdata8[11];
    char stringdata9[13];
    char stringdata10[16];
    char stringdata11[14];
    char stringdata12[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPLayerable_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPLayerable_t qt_meta_stringdata_QCPLayerable = {
    {
        QT_MOC_LITERAL(0, 12),  // "QCPLayerable"
        QT_MOC_LITERAL(13, 12),  // "layerChanged"
        QT_MOC_LITERAL(26, 0),  // ""
        QT_MOC_LITERAL(27, 9),  // "QCPLayer*"
        QT_MOC_LITERAL(37, 8),  // "newLayer"
        QT_MOC_LITERAL(46, 8),  // "setLayer"
        QT_MOC_LITERAL(55, 5),  // "layer"
        QT_MOC_LITERAL(61, 7),  // "visible"
        QT_MOC_LITERAL(69, 10),  // "parentPlot"
        QT_MOC_LITERAL(80, 12),  // "QCustomPlot*"
        QT_MOC_LITERAL(93, 15),  // "parentLayerable"
        QT_MOC_LITERAL(109, 13),  // "QCPLayerable*"
        QT_MOC_LITERAL(123, 11)   // "antialiased"
    },
    "QCPLayerable",
    "layerChanged",
    "",
    "QCPLayer*",
    "newLayer",
    "setLayer",
    "layer",
    "visible",
    "parentPlot",
    "QCustomPlot*",
    "parentLayerable",
    "QCPLayerable*",
    "antialiased"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPLayerable[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       5,   32, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   26,    2, 0x06,    6 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    1,   29,    2, 0x0a,    8 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Bool, 0x80000000 | 3,    6,

 // properties: name, type, flags
       7, QMetaType::Bool, 0x00015103, uint(-1), 0,
       8, 0x80000000 | 9, 0x00015009, uint(-1), 0,
      10, 0x80000000 | 11, 0x00015009, uint(-1), 0,
       6, 0x80000000 | 3, 0x0001510b, uint(0), 0,
      12, QMetaType::Bool, 0x00015103, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPLayerable::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_QCPLayerable.offsetsAndSizes,
    qt_meta_data_QCPLayerable,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPLayerable_t,
        // property 'visible'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'parentPlot'
        QtPrivate::TypeAndForceComplete<QCustomPlot*, std::true_type>,
        // property 'parentLayerable'
        QtPrivate::TypeAndForceComplete<QCPLayerable*, std::true_type>,
        // property 'layer'
        QtPrivate::TypeAndForceComplete<QCPLayer*, std::true_type>,
        // property 'antialiased'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPLayerable, std::true_type>,
        // method 'layerChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPLayer *, std::false_type>,
        // method 'setLayer'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPLayer *, std::false_type>
    >,
    nullptr
} };

void QCPLayerable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCPLayerable *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->layerChanged((*reinterpret_cast< std::add_pointer_t<QCPLayer*>>(_a[1]))); break;
        case 1: { bool _r = _t->setLayer((*reinterpret_cast< std::add_pointer_t<QCPLayer*>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPLayer* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPLayer* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QCPLayerable::*)(QCPLayer * );
            if (_t _q_method = &QCPLayerable::layerChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPLayer* >(); break;
        case 2:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPLayerable* >(); break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCustomPlot* >(); break;
        }
    }
else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPLayerable *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->visible(); break;
        case 1: *reinterpret_cast< QCustomPlot**>(_v) = _t->parentPlot(); break;
        case 2: *reinterpret_cast< QCPLayerable**>(_v) = _t->parentLayerable(); break;
        case 3: *reinterpret_cast< QCPLayer**>(_v) = _t->layer(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->antialiased(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPLayerable *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setVisible(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->setLayer(*reinterpret_cast< QCPLayer**>(_v)); break;
        case 4: _t->setAntialiased(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *QCPLayerable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPLayerable::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPLayerable.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QCPLayerable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void QCPLayerable::layerChanged(QCPLayer * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
namespace {
struct qt_meta_stringdata_QCPSelectionRect_t {
    uint offsetsAndSizes[22];
    char stringdata0[17];
    char stringdata1[8];
    char stringdata2[1];
    char stringdata3[13];
    char stringdata4[6];
    char stringdata5[8];
    char stringdata6[5];
    char stringdata7[9];
    char stringdata8[13];
    char stringdata9[9];
    char stringdata10[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPSelectionRect_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPSelectionRect_t qt_meta_stringdata_QCPSelectionRect = {
    {
        QT_MOC_LITERAL(0, 16),  // "QCPSelectionRect"
        QT_MOC_LITERAL(17, 7),  // "started"
        QT_MOC_LITERAL(25, 0),  // ""
        QT_MOC_LITERAL(26, 12),  // "QMouseEvent*"
        QT_MOC_LITERAL(39, 5),  // "event"
        QT_MOC_LITERAL(45, 7),  // "changed"
        QT_MOC_LITERAL(53, 4),  // "rect"
        QT_MOC_LITERAL(58, 8),  // "canceled"
        QT_MOC_LITERAL(67, 12),  // "QInputEvent*"
        QT_MOC_LITERAL(80, 8),  // "accepted"
        QT_MOC_LITERAL(89, 6)   // "cancel"
    },
    "QCPSelectionRect",
    "started",
    "",
    "QMouseEvent*",
    "event",
    "changed",
    "rect",
    "canceled",
    "QInputEvent*",
    "accepted",
    "cancel"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPSelectionRect[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   44,    2, 0x06,    1 /* Public */,
       5,    2,   47,    2, 0x06,    3 /* Public */,
       7,    2,   52,    2, 0x06,    6 /* Public */,
       9,    2,   57,    2, 0x06,    9 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      10,    0,   62,    2, 0x0a,   12 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QRect, 0x80000000 | 3,    6,    4,
    QMetaType::Void, QMetaType::QRect, 0x80000000 | 8,    6,    4,
    QMetaType::Void, QMetaType::QRect, 0x80000000 | 3,    6,    4,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPSelectionRect::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayerable::staticMetaObject>(),
    qt_meta_stringdata_QCPSelectionRect.offsetsAndSizes,
    qt_meta_data_QCPSelectionRect,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPSelectionRect_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPSelectionRect, std::true_type>,
        // method 'started'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QRect &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'canceled'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QRect &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QInputEvent *, std::false_type>,
        // method 'accepted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QRect &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'cancel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QCPSelectionRect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCPSelectionRect *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->started((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 1: _t->changed((*reinterpret_cast< std::add_pointer_t<QRect>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[2]))); break;
        case 2: _t->canceled((*reinterpret_cast< std::add_pointer_t<QRect>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QInputEvent*>>(_a[2]))); break;
        case 3: _t->accepted((*reinterpret_cast< std::add_pointer_t<QRect>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[2]))); break;
        case 4: _t->cancel(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QCPSelectionRect::*)(QMouseEvent * );
            if (_t _q_method = &QCPSelectionRect::started; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QCPSelectionRect::*)(const QRect & , QMouseEvent * );
            if (_t _q_method = &QCPSelectionRect::changed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QCPSelectionRect::*)(const QRect & , QInputEvent * );
            if (_t _q_method = &QCPSelectionRect::canceled; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (QCPSelectionRect::*)(const QRect & , QMouseEvent * );
            if (_t _q_method = &QCPSelectionRect::accepted; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *QCPSelectionRect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPSelectionRect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPSelectionRect.stringdata0))
        return static_cast<void*>(this);
    return QCPLayerable::qt_metacast(_clname);
}

int QCPSelectionRect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayerable::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void QCPSelectionRect::started(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCPSelectionRect::changed(const QRect & _t1, QMouseEvent * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QCPSelectionRect::canceled(const QRect & _t1, QInputEvent * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QCPSelectionRect::accepted(const QRect & _t1, QMouseEvent * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
namespace {
struct qt_meta_stringdata_QCPMarginGroup_t {
    uint offsetsAndSizes[2];
    char stringdata0[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPMarginGroup_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPMarginGroup_t qt_meta_stringdata_QCPMarginGroup = {
    {
        QT_MOC_LITERAL(0, 14)   // "QCPMarginGroup"
    },
    "QCPMarginGroup"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPMarginGroup[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPMarginGroup::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_QCPMarginGroup.offsetsAndSizes,
    qt_meta_data_QCPMarginGroup,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPMarginGroup_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPMarginGroup, std::true_type>
    >,
    nullptr
} };

void QCPMarginGroup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *QCPMarginGroup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPMarginGroup::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPMarginGroup.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QCPMarginGroup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_stringdata_QCPLayoutElement_t {
    uint offsetsAndSizes[36];
    char stringdata0[17];
    char stringdata1[7];
    char stringdata2[11];
    char stringdata3[5];
    char stringdata4[10];
    char stringdata5[8];
    char stringdata6[9];
    char stringdata7[15];
    char stringdata8[12];
    char stringdata9[12];
    char stringdata10[19];
    char stringdata11[19];
    char stringdata12[12];
    char stringdata13[14];
    char stringdata14[10];
    char stringdata15[9];
    char stringdata16[13];
    char stringdata17[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPLayoutElement_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPLayoutElement_t qt_meta_stringdata_QCPLayoutElement = {
    {
        QT_MOC_LITERAL(0, 16),  // "QCPLayoutElement"
        QT_MOC_LITERAL(17, 6),  // "layout"
        QT_MOC_LITERAL(24, 10),  // "QCPLayout*"
        QT_MOC_LITERAL(35, 4),  // "rect"
        QT_MOC_LITERAL(40, 9),  // "outerRect"
        QT_MOC_LITERAL(50, 7),  // "margins"
        QT_MOC_LITERAL(58, 8),  // "QMargins"
        QT_MOC_LITERAL(67, 14),  // "minimumMargins"
        QT_MOC_LITERAL(82, 11),  // "minimumSize"
        QT_MOC_LITERAL(94, 11),  // "maximumSize"
        QT_MOC_LITERAL(106, 18),  // "sizeConstraintRect"
        QT_MOC_LITERAL(125, 18),  // "SizeConstraintRect"
        QT_MOC_LITERAL(144, 11),  // "UpdatePhase"
        QT_MOC_LITERAL(156, 13),  // "upPreparation"
        QT_MOC_LITERAL(170, 9),  // "upMargins"
        QT_MOC_LITERAL(180, 8),  // "upLayout"
        QT_MOC_LITERAL(189, 12),  // "scrInnerRect"
        QT_MOC_LITERAL(202, 12)   // "scrOuterRect"
    },
    "QCPLayoutElement",
    "layout",
    "QCPLayout*",
    "rect",
    "outerRect",
    "margins",
    "QMargins",
    "minimumMargins",
    "minimumSize",
    "maximumSize",
    "sizeConstraintRect",
    "SizeConstraintRect",
    "UpdatePhase",
    "upPreparation",
    "upMargins",
    "upLayout",
    "scrInnerRect",
    "scrOuterRect"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPLayoutElement[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       8,   14, // properties
       2,   54, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, 0x80000000 | 2, 0x00015009, uint(-1), 0,
       3, QMetaType::QRect, 0x00015001, uint(-1), 0,
       4, QMetaType::QRect, 0x00015103, uint(-1), 0,
       5, 0x80000000 | 6, 0x0001510b, uint(-1), 0,
       7, 0x80000000 | 6, 0x0001510b, uint(-1), 0,
       8, QMetaType::QSize, 0x00015103, uint(-1), 0,
       9, QMetaType::QSize, 0x00015103, uint(-1), 0,
      10, 0x80000000 | 11, 0x0001510b, uint(-1), 0,

 // enums: name, alias, flags, count, data
      12,   12, 0x0,    3,   64,
      11,   11, 0x0,    2,   70,

 // enum data: key, value
      13, uint(QCPLayoutElement::upPreparation),
      14, uint(QCPLayoutElement::upMargins),
      15, uint(QCPLayoutElement::upLayout),
      16, uint(QCPLayoutElement::scrInnerRect),
      17, uint(QCPLayoutElement::scrOuterRect),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPLayoutElement::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayerable::staticMetaObject>(),
    qt_meta_stringdata_QCPLayoutElement.offsetsAndSizes,
    qt_meta_data_QCPLayoutElement,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPLayoutElement_t,
        // property 'layout'
        QtPrivate::TypeAndForceComplete<QCPLayout*, std::true_type>,
        // property 'rect'
        QtPrivate::TypeAndForceComplete<QRect, std::true_type>,
        // property 'outerRect'
        QtPrivate::TypeAndForceComplete<QRect, std::true_type>,
        // property 'margins'
        QtPrivate::TypeAndForceComplete<QMargins, std::true_type>,
        // property 'minimumMargins'
        QtPrivate::TypeAndForceComplete<QMargins, std::true_type>,
        // property 'minimumSize'
        QtPrivate::TypeAndForceComplete<QSize, std::true_type>,
        // property 'maximumSize'
        QtPrivate::TypeAndForceComplete<QSize, std::true_type>,
        // property 'sizeConstraintRect'
        QtPrivate::TypeAndForceComplete<SizeConstraintRect, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPLayoutElement, std::true_type>
    >,
    nullptr
} };

void QCPLayoutElement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPLayout* >(); break;
        }
    }
else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPLayoutElement *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QCPLayout**>(_v) = _t->layout(); break;
        case 1: *reinterpret_cast< QRect*>(_v) = _t->rect(); break;
        case 2: *reinterpret_cast< QRect*>(_v) = _t->outerRect(); break;
        case 3: *reinterpret_cast< QMargins*>(_v) = _t->margins(); break;
        case 4: *reinterpret_cast< QMargins*>(_v) = _t->minimumMargins(); break;
        case 5: *reinterpret_cast< QSize*>(_v) = _t->minimumSize(); break;
        case 6: *reinterpret_cast< QSize*>(_v) = _t->maximumSize(); break;
        case 7: *reinterpret_cast< SizeConstraintRect*>(_v) = _t->sizeConstraintRect(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPLayoutElement *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 2: _t->setOuterRect(*reinterpret_cast< QRect*>(_v)); break;
        case 3: _t->setMargins(*reinterpret_cast< QMargins*>(_v)); break;
        case 4: _t->setMinimumMargins(*reinterpret_cast< QMargins*>(_v)); break;
        case 5: _t->setMinimumSize(*reinterpret_cast< QSize*>(_v)); break;
        case 6: _t->setMaximumSize(*reinterpret_cast< QSize*>(_v)); break;
        case 7: _t->setSizeConstraintRect(*reinterpret_cast< SizeConstraintRect*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_o;
}

const QMetaObject *QCPLayoutElement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPLayoutElement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPLayoutElement.stringdata0))
        return static_cast<void*>(this);
    return QCPLayerable::qt_metacast(_clname);
}

int QCPLayoutElement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayerable::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
namespace {
struct qt_meta_stringdata_QCPLayout_t {
    uint offsetsAndSizes[2];
    char stringdata0[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPLayout_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPLayout_t qt_meta_stringdata_QCPLayout = {
    {
        QT_MOC_LITERAL(0, 9)   // "QCPLayout"
    },
    "QCPLayout"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPLayout[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPLayout::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayoutElement::staticMetaObject>(),
    qt_meta_stringdata_QCPLayout.offsetsAndSizes,
    qt_meta_data_QCPLayout,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPLayout_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPLayout, std::true_type>
    >,
    nullptr
} };

void QCPLayout::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *QCPLayout::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPLayout::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPLayout.stringdata0))
        return static_cast<void*>(this);
    return QCPLayoutElement::qt_metacast(_clname);
}

int QCPLayout::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayoutElement::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_stringdata_QCPLayoutGrid_t {
    uint offsetsAndSizes[26];
    char stringdata0[14];
    char stringdata1[9];
    char stringdata2[12];
    char stringdata3[21];
    char stringdata4[14];
    char stringdata5[18];
    char stringdata6[14];
    char stringdata7[11];
    char stringdata8[10];
    char stringdata9[10];
    char stringdata10[5];
    char stringdata11[12];
    char stringdata12[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPLayoutGrid_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPLayoutGrid_t qt_meta_stringdata_QCPLayoutGrid = {
    {
        QT_MOC_LITERAL(0, 13),  // "QCPLayoutGrid"
        QT_MOC_LITERAL(14, 8),  // "rowCount"
        QT_MOC_LITERAL(23, 11),  // "columnCount"
        QT_MOC_LITERAL(35, 20),  // "columnStretchFactors"
        QT_MOC_LITERAL(56, 13),  // "QList<double>"
        QT_MOC_LITERAL(70, 17),  // "rowStretchFactors"
        QT_MOC_LITERAL(88, 13),  // "columnSpacing"
        QT_MOC_LITERAL(102, 10),  // "rowSpacing"
        QT_MOC_LITERAL(113, 9),  // "fillOrder"
        QT_MOC_LITERAL(123, 9),  // "FillOrder"
        QT_MOC_LITERAL(133, 4),  // "wrap"
        QT_MOC_LITERAL(138, 11),  // "foRowsFirst"
        QT_MOC_LITERAL(150, 14)   // "foColumnsFirst"
    },
    "QCPLayoutGrid",
    "rowCount",
    "columnCount",
    "columnStretchFactors",
    "QList<double>",
    "rowStretchFactors",
    "columnSpacing",
    "rowSpacing",
    "fillOrder",
    "FillOrder",
    "wrap",
    "foRowsFirst",
    "foColumnsFirst"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPLayoutGrid[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       8,   14, // properties
       1,   54, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::Int, 0x00015001, uint(-1), 0,
       2, QMetaType::Int, 0x00015001, uint(-1), 0,
       3, 0x80000000 | 4, 0x0001510b, uint(-1), 0,
       5, 0x80000000 | 4, 0x0001510b, uint(-1), 0,
       6, QMetaType::Int, 0x00015103, uint(-1), 0,
       7, QMetaType::Int, 0x00015103, uint(-1), 0,
       8, 0x80000000 | 9, 0x0001510b, uint(-1), 0,
      10, QMetaType::Int, 0x00015103, uint(-1), 0,

 // enums: name, alias, flags, count, data
       9,    9, 0x0,    2,   59,

 // enum data: key, value
      11, uint(QCPLayoutGrid::foRowsFirst),
      12, uint(QCPLayoutGrid::foColumnsFirst),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPLayoutGrid::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayout::staticMetaObject>(),
    qt_meta_stringdata_QCPLayoutGrid.offsetsAndSizes,
    qt_meta_data_QCPLayoutGrid,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPLayoutGrid_t,
        // property 'rowCount'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'columnCount'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'columnStretchFactors'
        QtPrivate::TypeAndForceComplete<QList<double>, std::true_type>,
        // property 'rowStretchFactors'
        QtPrivate::TypeAndForceComplete<QList<double>, std::true_type>,
        // property 'columnSpacing'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'rowSpacing'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'fillOrder'
        QtPrivate::TypeAndForceComplete<FillOrder, std::true_type>,
        // property 'wrap'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPLayoutGrid, std::true_type>
    >,
    nullptr
} };

void QCPLayoutGrid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
        case 2:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<double> >(); break;
        }
    }
else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPLayoutGrid *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->rowCount(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->columnCount(); break;
        case 2: *reinterpret_cast< QList<double>*>(_v) = _t->columnStretchFactors(); break;
        case 3: *reinterpret_cast< QList<double>*>(_v) = _t->rowStretchFactors(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->columnSpacing(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->rowSpacing(); break;
        case 6: *reinterpret_cast< FillOrder*>(_v) = _t->fillOrder(); break;
        case 7: *reinterpret_cast< int*>(_v) = _t->wrap(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPLayoutGrid *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 2: _t->setColumnStretchFactors(*reinterpret_cast< QList<double>*>(_v)); break;
        case 3: _t->setRowStretchFactors(*reinterpret_cast< QList<double>*>(_v)); break;
        case 4: _t->setColumnSpacing(*reinterpret_cast< int*>(_v)); break;
        case 5: _t->setRowSpacing(*reinterpret_cast< int*>(_v)); break;
        case 6: _t->setFillOrder(*reinterpret_cast< FillOrder*>(_v)); break;
        case 7: _t->setWrap(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_o;
}

const QMetaObject *QCPLayoutGrid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPLayoutGrid::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPLayoutGrid.stringdata0))
        return static_cast<void*>(this);
    return QCPLayout::qt_metacast(_clname);
}

int QCPLayoutGrid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayout::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
namespace {
struct qt_meta_stringdata_QCPLayoutInset_t {
    uint offsetsAndSizes[8];
    char stringdata0[15];
    char stringdata1[15];
    char stringdata2[7];
    char stringdata3[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPLayoutInset_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPLayoutInset_t qt_meta_stringdata_QCPLayoutInset = {
    {
        QT_MOC_LITERAL(0, 14),  // "QCPLayoutInset"
        QT_MOC_LITERAL(15, 14),  // "InsetPlacement"
        QT_MOC_LITERAL(30, 6),  // "ipFree"
        QT_MOC_LITERAL(37, 15)   // "ipBorderAligned"
    },
    "QCPLayoutInset",
    "InsetPlacement",
    "ipFree",
    "ipBorderAligned"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPLayoutInset[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    2,   19,

 // enum data: key, value
       2, uint(QCPLayoutInset::ipFree),
       3, uint(QCPLayoutInset::ipBorderAligned),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPLayoutInset::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayout::staticMetaObject>(),
    qt_meta_stringdata_QCPLayoutInset.offsetsAndSizes,
    qt_meta_data_QCPLayoutInset,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPLayoutInset_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPLayoutInset, std::true_type>
    >,
    nullptr
} };

void QCPLayoutInset::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *QCPLayoutInset::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPLayoutInset::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPLayoutInset.stringdata0))
        return static_cast<void*>(this);
    return QCPLayout::qt_metacast(_clname);
}

int QCPLayoutInset::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayout::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_stringdata_QCPLineEnding_t {
    uint offsetsAndSizes[24];
    char stringdata0[14];
    char stringdata1[12];
    char stringdata2[7];
    char stringdata3[12];
    char stringdata4[13];
    char stringdata5[12];
    char stringdata6[7];
    char stringdata7[9];
    char stringdata8[10];
    char stringdata9[6];
    char stringdata10[10];
    char stringdata11[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPLineEnding_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPLineEnding_t qt_meta_stringdata_QCPLineEnding = {
    {
        QT_MOC_LITERAL(0, 13),  // "QCPLineEnding"
        QT_MOC_LITERAL(14, 11),  // "EndingStyle"
        QT_MOC_LITERAL(26, 6),  // "esNone"
        QT_MOC_LITERAL(33, 11),  // "esFlatArrow"
        QT_MOC_LITERAL(45, 12),  // "esSpikeArrow"
        QT_MOC_LITERAL(58, 11),  // "esLineArrow"
        QT_MOC_LITERAL(70, 6),  // "esDisc"
        QT_MOC_LITERAL(77, 8),  // "esSquare"
        QT_MOC_LITERAL(86, 9),  // "esDiamond"
        QT_MOC_LITERAL(96, 5),  // "esBar"
        QT_MOC_LITERAL(102, 9),  // "esHalfBar"
        QT_MOC_LITERAL(112, 11)   // "esSkewedBar"
    },
    "QCPLineEnding",
    "EndingStyle",
    "esNone",
    "esFlatArrow",
    "esSpikeArrow",
    "esLineArrow",
    "esDisc",
    "esSquare",
    "esDiamond",
    "esBar",
    "esHalfBar",
    "esSkewedBar"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPLineEnding[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,   10,   19,

 // enum data: key, value
       2, uint(QCPLineEnding::esNone),
       3, uint(QCPLineEnding::esFlatArrow),
       4, uint(QCPLineEnding::esSpikeArrow),
       5, uint(QCPLineEnding::esLineArrow),
       6, uint(QCPLineEnding::esDisc),
       7, uint(QCPLineEnding::esSquare),
       8, uint(QCPLineEnding::esDiamond),
       9, uint(QCPLineEnding::esBar),
      10, uint(QCPLineEnding::esHalfBar),
      11, uint(QCPLineEnding::esSkewedBar),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPLineEnding::staticMetaObject = { {
    nullptr,
    qt_meta_stringdata_QCPLineEnding.offsetsAndSizes,
    qt_meta_data_QCPLineEnding,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPLineEnding_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPLineEnding, std::true_type>
    >,
    nullptr
} };

namespace {
struct qt_meta_stringdata_QCPLabelPainterPrivate_t {
    uint offsetsAndSizes[34];
    char stringdata0[23];
    char stringdata1[11];
    char stringdata2[14];
    char stringdata3[16];
    char stringdata4[16];
    char stringdata5[20];
    char stringdata6[10];
    char stringdata7[11];
    char stringdata8[11];
    char stringdata9[7];
    char stringdata10[8];
    char stringdata11[6];
    char stringdata12[9];
    char stringdata13[10];
    char stringdata14[11];
    char stringdata15[14];
    char stringdata16[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPLabelPainterPrivate_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPLabelPainterPrivate_t qt_meta_stringdata_QCPLabelPainterPrivate = {
    {
        QT_MOC_LITERAL(0, 22),  // "QCPLabelPainterPrivate"
        QT_MOC_LITERAL(23, 10),  // "AnchorMode"
        QT_MOC_LITERAL(34, 13),  // "amRectangular"
        QT_MOC_LITERAL(48, 15),  // "amSkewedUpright"
        QT_MOC_LITERAL(64, 15),  // "amSkewedRotated"
        QT_MOC_LITERAL(80, 19),  // "AnchorReferenceType"
        QT_MOC_LITERAL(100, 9),  // "artNormal"
        QT_MOC_LITERAL(110, 10),  // "artTangent"
        QT_MOC_LITERAL(121, 10),  // "AnchorSide"
        QT_MOC_LITERAL(132, 6),  // "asLeft"
        QT_MOC_LITERAL(139, 7),  // "asRight"
        QT_MOC_LITERAL(147, 5),  // "asTop"
        QT_MOC_LITERAL(153, 8),  // "asBottom"
        QT_MOC_LITERAL(162, 9),  // "asTopLeft"
        QT_MOC_LITERAL(172, 10),  // "asTopRight"
        QT_MOC_LITERAL(183, 13),  // "asBottomRight"
        QT_MOC_LITERAL(197, 12)   // "asBottomLeft"
    },
    "QCPLabelPainterPrivate",
    "AnchorMode",
    "amRectangular",
    "amSkewedUpright",
    "amSkewedRotated",
    "AnchorReferenceType",
    "artNormal",
    "artTangent",
    "AnchorSide",
    "asLeft",
    "asRight",
    "asTop",
    "asBottom",
    "asTopLeft",
    "asTopRight",
    "asBottomRight",
    "asBottomLeft"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPLabelPainterPrivate[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       3,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    3,   29,
       5,    5, 0x0,    2,   35,
       8,    8, 0x0,    8,   39,

 // enum data: key, value
       2, uint(QCPLabelPainterPrivate::amRectangular),
       3, uint(QCPLabelPainterPrivate::amSkewedUpright),
       4, uint(QCPLabelPainterPrivate::amSkewedRotated),
       6, uint(QCPLabelPainterPrivate::artNormal),
       7, uint(QCPLabelPainterPrivate::artTangent),
       9, uint(QCPLabelPainterPrivate::asLeft),
      10, uint(QCPLabelPainterPrivate::asRight),
      11, uint(QCPLabelPainterPrivate::asTop),
      12, uint(QCPLabelPainterPrivate::asBottom),
      13, uint(QCPLabelPainterPrivate::asTopLeft),
      14, uint(QCPLabelPainterPrivate::asTopRight),
      15, uint(QCPLabelPainterPrivate::asBottomRight),
      16, uint(QCPLabelPainterPrivate::asBottomLeft),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPLabelPainterPrivate::staticMetaObject = { {
    nullptr,
    qt_meta_stringdata_QCPLabelPainterPrivate.offsetsAndSizes,
    qt_meta_data_QCPLabelPainterPrivate,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPLabelPainterPrivate_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPLabelPainterPrivate, std::true_type>
    >,
    nullptr
} };

namespace {
struct qt_meta_stringdata_QCPAxisTicker_t {
    uint offsetsAndSizes[8];
    char stringdata0[14];
    char stringdata1[17];
    char stringdata2[15];
    char stringdata3[17];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPAxisTicker_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPAxisTicker_t qt_meta_stringdata_QCPAxisTicker = {
    {
        QT_MOC_LITERAL(0, 13),  // "QCPAxisTicker"
        QT_MOC_LITERAL(14, 16),  // "TickStepStrategy"
        QT_MOC_LITERAL(31, 14),  // "tssReadability"
        QT_MOC_LITERAL(46, 16)   // "tssMeetTickCount"
    },
    "QCPAxisTicker",
    "TickStepStrategy",
    "tssReadability",
    "tssMeetTickCount"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPAxisTicker[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    2,   19,

 // enum data: key, value
       2, uint(QCPAxisTicker::tssReadability),
       3, uint(QCPAxisTicker::tssMeetTickCount),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPAxisTicker::staticMetaObject = { {
    nullptr,
    qt_meta_stringdata_QCPAxisTicker.offsetsAndSizes,
    qt_meta_data_QCPAxisTicker,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPAxisTicker_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPAxisTicker, std::true_type>
    >,
    nullptr
} };

namespace {
struct qt_meta_stringdata_QCPAxisTickerTime_t {
    uint offsetsAndSizes[14];
    char stringdata0[18];
    char stringdata1[9];
    char stringdata2[15];
    char stringdata3[10];
    char stringdata4[10];
    char stringdata5[8];
    char stringdata6[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPAxisTickerTime_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPAxisTickerTime_t qt_meta_stringdata_QCPAxisTickerTime = {
    {
        QT_MOC_LITERAL(0, 17),  // "QCPAxisTickerTime"
        QT_MOC_LITERAL(18, 8),  // "TimeUnit"
        QT_MOC_LITERAL(27, 14),  // "tuMilliseconds"
        QT_MOC_LITERAL(42, 9),  // "tuSeconds"
        QT_MOC_LITERAL(52, 9),  // "tuMinutes"
        QT_MOC_LITERAL(62, 7),  // "tuHours"
        QT_MOC_LITERAL(70, 6)   // "tuDays"
    },
    "QCPAxisTickerTime",
    "TimeUnit",
    "tuMilliseconds",
    "tuSeconds",
    "tuMinutes",
    "tuHours",
    "tuDays"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPAxisTickerTime[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    5,   19,

 // enum data: key, value
       2, uint(QCPAxisTickerTime::tuMilliseconds),
       3, uint(QCPAxisTickerTime::tuSeconds),
       4, uint(QCPAxisTickerTime::tuMinutes),
       5, uint(QCPAxisTickerTime::tuHours),
       6, uint(QCPAxisTickerTime::tuDays),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPAxisTickerTime::staticMetaObject = { {
    QtPrivate::MetaObjectForType<QCPAxisTicker>::value,
    qt_meta_stringdata_QCPAxisTickerTime.offsetsAndSizes,
    qt_meta_data_QCPAxisTickerTime,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPAxisTickerTime_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPAxisTickerTime, std::true_type>
    >,
    nullptr
} };

namespace {
struct qt_meta_stringdata_QCPAxisTickerFixed_t {
    uint offsetsAndSizes[10];
    char stringdata0[19];
    char stringdata1[14];
    char stringdata2[7];
    char stringdata3[12];
    char stringdata4[9];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPAxisTickerFixed_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPAxisTickerFixed_t qt_meta_stringdata_QCPAxisTickerFixed = {
    {
        QT_MOC_LITERAL(0, 18),  // "QCPAxisTickerFixed"
        QT_MOC_LITERAL(19, 13),  // "ScaleStrategy"
        QT_MOC_LITERAL(33, 6),  // "ssNone"
        QT_MOC_LITERAL(40, 11),  // "ssMultiples"
        QT_MOC_LITERAL(52, 8)   // "ssPowers"
    },
    "QCPAxisTickerFixed",
    "ScaleStrategy",
    "ssNone",
    "ssMultiples",
    "ssPowers"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPAxisTickerFixed[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    3,   19,

 // enum data: key, value
       2, uint(QCPAxisTickerFixed::ssNone),
       3, uint(QCPAxisTickerFixed::ssMultiples),
       4, uint(QCPAxisTickerFixed::ssPowers),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPAxisTickerFixed::staticMetaObject = { {
    QtPrivate::MetaObjectForType<QCPAxisTicker>::value,
    qt_meta_stringdata_QCPAxisTickerFixed.offsetsAndSizes,
    qt_meta_data_QCPAxisTickerFixed,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPAxisTickerFixed_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPAxisTickerFixed, std::true_type>
    >,
    nullptr
} };

namespace {
struct qt_meta_stringdata_QCPAxisTickerPi_t {
    uint offsetsAndSizes[10];
    char stringdata0[16];
    char stringdata1[14];
    char stringdata2[16];
    char stringdata3[17];
    char stringdata4[19];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPAxisTickerPi_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPAxisTickerPi_t qt_meta_stringdata_QCPAxisTickerPi = {
    {
        QT_MOC_LITERAL(0, 15),  // "QCPAxisTickerPi"
        QT_MOC_LITERAL(16, 13),  // "FractionStyle"
        QT_MOC_LITERAL(30, 15),  // "fsFloatingPoint"
        QT_MOC_LITERAL(46, 16),  // "fsAsciiFractions"
        QT_MOC_LITERAL(63, 18)   // "fsUnicodeFractions"
    },
    "QCPAxisTickerPi",
    "FractionStyle",
    "fsFloatingPoint",
    "fsAsciiFractions",
    "fsUnicodeFractions"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPAxisTickerPi[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    3,   19,

 // enum data: key, value
       2, uint(QCPAxisTickerPi::fsFloatingPoint),
       3, uint(QCPAxisTickerPi::fsAsciiFractions),
       4, uint(QCPAxisTickerPi::fsUnicodeFractions),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPAxisTickerPi::staticMetaObject = { {
    QtPrivate::MetaObjectForType<QCPAxisTicker>::value,
    qt_meta_stringdata_QCPAxisTickerPi.offsetsAndSizes,
    qt_meta_data_QCPAxisTickerPi,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPAxisTickerPi_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPAxisTickerPi, std::true_type>
    >,
    nullptr
} };

namespace {
struct qt_meta_stringdata_QCPGrid_t {
    uint offsetsAndSizes[14];
    char stringdata0[8];
    char stringdata1[15];
    char stringdata2[19];
    char stringdata3[20];
    char stringdata4[4];
    char stringdata5[11];
    char stringdata6[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPGrid_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPGrid_t qt_meta_stringdata_QCPGrid = {
    {
        QT_MOC_LITERAL(0, 7),  // "QCPGrid"
        QT_MOC_LITERAL(8, 14),  // "subGridVisible"
        QT_MOC_LITERAL(23, 18),  // "antialiasedSubGrid"
        QT_MOC_LITERAL(42, 19),  // "antialiasedZeroLine"
        QT_MOC_LITERAL(62, 3),  // "pen"
        QT_MOC_LITERAL(66, 10),  // "subGridPen"
        QT_MOC_LITERAL(77, 11)   // "zeroLinePen"
    },
    "QCPGrid",
    "subGridVisible",
    "antialiasedSubGrid",
    "antialiasedZeroLine",
    "pen",
    "subGridPen",
    "zeroLinePen"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPGrid[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       6,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::Bool, 0x00015103, uint(-1), 0,
       2, QMetaType::Bool, 0x00015103, uint(-1), 0,
       3, QMetaType::Bool, 0x00015103, uint(-1), 0,
       4, QMetaType::QPen, 0x00015103, uint(-1), 0,
       5, QMetaType::QPen, 0x00015103, uint(-1), 0,
       6, QMetaType::QPen, 0x00015103, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPGrid::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayerable::staticMetaObject>(),
    qt_meta_stringdata_QCPGrid.offsetsAndSizes,
    qt_meta_data_QCPGrid,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPGrid_t,
        // property 'subGridVisible'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'antialiasedSubGrid'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'antialiasedZeroLine'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'pen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'subGridPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'zeroLinePen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPGrid, std::true_type>
    >,
    nullptr
} };

void QCPGrid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPGrid *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->subGridVisible(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->antialiasedSubGrid(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->antialiasedZeroLine(); break;
        case 3: *reinterpret_cast< QPen*>(_v) = _t->pen(); break;
        case 4: *reinterpret_cast< QPen*>(_v) = _t->subGridPen(); break;
        case 5: *reinterpret_cast< QPen*>(_v) = _t->zeroLinePen(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPGrid *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setSubGridVisible(*reinterpret_cast< bool*>(_v)); break;
        case 1: _t->setAntialiasedSubGrid(*reinterpret_cast< bool*>(_v)); break;
        case 2: _t->setAntialiasedZeroLine(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->setPen(*reinterpret_cast< QPen*>(_v)); break;
        case 4: _t->setSubGridPen(*reinterpret_cast< QPen*>(_v)); break;
        case 5: _t->setZeroLinePen(*reinterpret_cast< QPen*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *QCPGrid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPGrid::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPGrid.stringdata0))
        return static_cast<void*>(this);
    return QCPLayerable::qt_metacast(_clname);
}

int QCPGrid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayerable::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
namespace {
struct qt_meta_stringdata_QCPAxis_t {
    uint offsetsAndSizes[166];
    char stringdata0[8];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[9];
    char stringdata5[9];
    char stringdata6[17];
    char stringdata7[19];
    char stringdata8[10];
    char stringdata9[17];
    char stringdata10[25];
    char stringdata11[6];
    char stringdata12[18];
    char stringdata13[13];
    char stringdata14[5];
    char stringdata15[9];
    char stringdata16[6];
    char stringdata17[19];
    char stringdata18[16];
    char stringdata19[17];
    char stringdata20[14];
    char stringdata21[9];
    char stringdata22[9];
    char stringdata23[9];
    char stringdata24[13];
    char stringdata25[10];
    char stringdata26[14];
    char stringdata27[7];
    char stringdata28[30];
    char stringdata29[6];
    char stringdata30[11];
    char stringdata31[17];
    char stringdata32[14];
    char stringdata33[15];
    char stringdata34[18];
    char stringdata35[14];
    char stringdata36[10];
    char stringdata37[13];
    char stringdata38[16];
    char stringdata39[11];
    char stringdata40[14];
    char stringdata41[17];
    char stringdata42[13];
    char stringdata43[14];
    char stringdata44[9];
    char stringdata45[16];
    char stringdata46[17];
    char stringdata47[8];
    char stringdata48[8];
    char stringdata49[11];
    char stringdata50[10];
    char stringdata51[11];
    char stringdata52[6];
    char stringdata53[13];
    char stringdata54[8];
    char stringdata55[7];
    char stringdata56[16];
    char stringdata57[22];
    char stringdata58[18];
    char stringdata59[23];
    char stringdata60[19];
    char stringdata61[16];
    char stringdata62[16];
    char stringdata63[19];
    char stringdata64[12];
    char stringdata65[14];
    char stringdata66[12];
    char stringdata67[5];
    char stringdata68[9];
    char stringdata69[7];
    char stringdata70[8];
    char stringdata71[6];
    char stringdata72[9];
    char stringdata73[10];
    char stringdata74[9];
    char stringdata75[10];
    char stringdata76[9];
    char stringdata77[14];
    char stringdata78[15];
    char stringdata79[7];
    char stringdata80[7];
    char stringdata81[13];
    char stringdata82[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPAxis_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPAxis_t qt_meta_stringdata_QCPAxis = {
    {
        QT_MOC_LITERAL(0, 7),  // "QCPAxis"
        QT_MOC_LITERAL(8, 12),  // "rangeChanged"
        QT_MOC_LITERAL(21, 0),  // ""
        QT_MOC_LITERAL(22, 8),  // "QCPRange"
        QT_MOC_LITERAL(31, 8),  // "newRange"
        QT_MOC_LITERAL(40, 8),  // "oldRange"
        QT_MOC_LITERAL(49, 16),  // "scaleTypeChanged"
        QT_MOC_LITERAL(66, 18),  // "QCPAxis::ScaleType"
        QT_MOC_LITERAL(85, 9),  // "scaleType"
        QT_MOC_LITERAL(95, 16),  // "selectionChanged"
        QT_MOC_LITERAL(112, 24),  // "QCPAxis::SelectableParts"
        QT_MOC_LITERAL(137, 5),  // "parts"
        QT_MOC_LITERAL(143, 17),  // "selectableChanged"
        QT_MOC_LITERAL(161, 12),  // "setScaleType"
        QT_MOC_LITERAL(174, 4),  // "type"
        QT_MOC_LITERAL(179, 8),  // "setRange"
        QT_MOC_LITERAL(188, 5),  // "range"
        QT_MOC_LITERAL(194, 18),  // "setSelectableParts"
        QT_MOC_LITERAL(213, 15),  // "selectableParts"
        QT_MOC_LITERAL(229, 16),  // "setSelectedParts"
        QT_MOC_LITERAL(246, 13),  // "selectedParts"
        QT_MOC_LITERAL(260, 8),  // "axisType"
        QT_MOC_LITERAL(269, 8),  // "AxisType"
        QT_MOC_LITERAL(278, 8),  // "axisRect"
        QT_MOC_LITERAL(287, 12),  // "QCPAxisRect*"
        QT_MOC_LITERAL(300, 9),  // "ScaleType"
        QT_MOC_LITERAL(310, 13),  // "rangeReversed"
        QT_MOC_LITERAL(324, 6),  // "ticker"
        QT_MOC_LITERAL(331, 29),  // "QSharedPointer<QCPAxisTicker>"
        QT_MOC_LITERAL(361, 5),  // "ticks"
        QT_MOC_LITERAL(367, 10),  // "tickLabels"
        QT_MOC_LITERAL(378, 16),  // "tickLabelPadding"
        QT_MOC_LITERAL(395, 13),  // "tickLabelFont"
        QT_MOC_LITERAL(409, 14),  // "tickLabelColor"
        QT_MOC_LITERAL(424, 17),  // "tickLabelRotation"
        QT_MOC_LITERAL(442, 13),  // "tickLabelSide"
        QT_MOC_LITERAL(456, 9),  // "LabelSide"
        QT_MOC_LITERAL(466, 12),  // "numberFormat"
        QT_MOC_LITERAL(479, 15),  // "numberPrecision"
        QT_MOC_LITERAL(495, 10),  // "tickVector"
        QT_MOC_LITERAL(506, 13),  // "QList<double>"
        QT_MOC_LITERAL(520, 16),  // "tickVectorLabels"
        QT_MOC_LITERAL(537, 12),  // "tickLengthIn"
        QT_MOC_LITERAL(550, 13),  // "tickLengthOut"
        QT_MOC_LITERAL(564, 8),  // "subTicks"
        QT_MOC_LITERAL(573, 15),  // "subTickLengthIn"
        QT_MOC_LITERAL(589, 16),  // "subTickLengthOut"
        QT_MOC_LITERAL(606, 7),  // "basePen"
        QT_MOC_LITERAL(614, 7),  // "tickPen"
        QT_MOC_LITERAL(622, 10),  // "subTickPen"
        QT_MOC_LITERAL(633, 9),  // "labelFont"
        QT_MOC_LITERAL(643, 10),  // "labelColor"
        QT_MOC_LITERAL(654, 5),  // "label"
        QT_MOC_LITERAL(660, 12),  // "labelPadding"
        QT_MOC_LITERAL(673, 7),  // "padding"
        QT_MOC_LITERAL(681, 6),  // "offset"
        QT_MOC_LITERAL(688, 15),  // "SelectableParts"
        QT_MOC_LITERAL(704, 21),  // "selectedTickLabelFont"
        QT_MOC_LITERAL(726, 17),  // "selectedLabelFont"
        QT_MOC_LITERAL(744, 22),  // "selectedTickLabelColor"
        QT_MOC_LITERAL(767, 18),  // "selectedLabelColor"
        QT_MOC_LITERAL(786, 15),  // "selectedBasePen"
        QT_MOC_LITERAL(802, 15),  // "selectedTickPen"
        QT_MOC_LITERAL(818, 18),  // "selectedSubTickPen"
        QT_MOC_LITERAL(837, 11),  // "lowerEnding"
        QT_MOC_LITERAL(849, 13),  // "QCPLineEnding"
        QT_MOC_LITERAL(863, 11),  // "upperEnding"
        QT_MOC_LITERAL(875, 4),  // "grid"
        QT_MOC_LITERAL(880, 8),  // "QCPGrid*"
        QT_MOC_LITERAL(889, 6),  // "atLeft"
        QT_MOC_LITERAL(896, 7),  // "atRight"
        QT_MOC_LITERAL(904, 5),  // "atTop"
        QT_MOC_LITERAL(910, 8),  // "atBottom"
        QT_MOC_LITERAL(919, 9),  // "AxisTypes"
        QT_MOC_LITERAL(929, 8),  // "lsInside"
        QT_MOC_LITERAL(938, 9),  // "lsOutside"
        QT_MOC_LITERAL(948, 8),  // "stLinear"
        QT_MOC_LITERAL(957, 13),  // "stLogarithmic"
        QT_MOC_LITERAL(971, 14),  // "SelectablePart"
        QT_MOC_LITERAL(986, 6),  // "spNone"
        QT_MOC_LITERAL(993, 6),  // "spAxis"
        QT_MOC_LITERAL(1000, 12),  // "spTickLabels"
        QT_MOC_LITERAL(1013, 11)   // "spAxisLabel"
    },
    "QCPAxis",
    "rangeChanged",
    "",
    "QCPRange",
    "newRange",
    "oldRange",
    "scaleTypeChanged",
    "QCPAxis::ScaleType",
    "scaleType",
    "selectionChanged",
    "QCPAxis::SelectableParts",
    "parts",
    "selectableChanged",
    "setScaleType",
    "type",
    "setRange",
    "range",
    "setSelectableParts",
    "selectableParts",
    "setSelectedParts",
    "selectedParts",
    "axisType",
    "AxisType",
    "axisRect",
    "QCPAxisRect*",
    "ScaleType",
    "rangeReversed",
    "ticker",
    "QSharedPointer<QCPAxisTicker>",
    "ticks",
    "tickLabels",
    "tickLabelPadding",
    "tickLabelFont",
    "tickLabelColor",
    "tickLabelRotation",
    "tickLabelSide",
    "LabelSide",
    "numberFormat",
    "numberPrecision",
    "tickVector",
    "QList<double>",
    "tickVectorLabels",
    "tickLengthIn",
    "tickLengthOut",
    "subTicks",
    "subTickLengthIn",
    "subTickLengthOut",
    "basePen",
    "tickPen",
    "subTickPen",
    "labelFont",
    "labelColor",
    "label",
    "labelPadding",
    "padding",
    "offset",
    "SelectableParts",
    "selectedTickLabelFont",
    "selectedLabelFont",
    "selectedTickLabelColor",
    "selectedLabelColor",
    "selectedBasePen",
    "selectedTickPen",
    "selectedSubTickPen",
    "lowerEnding",
    "QCPLineEnding",
    "upperEnding",
    "grid",
    "QCPGrid*",
    "atLeft",
    "atRight",
    "atTop",
    "atBottom",
    "AxisTypes",
    "lsInside",
    "lsOutside",
    "stLinear",
    "stLogarithmic",
    "SelectablePart",
    "spNone",
    "spAxis",
    "spTickLabels",
    "spAxisLabel"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPAxis[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
      43,   97, // properties
       6,  312, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   68,    2, 0x06,   44 /* Public */,
       1,    2,   71,    2, 0x06,   46 /* Public */,
       6,    1,   76,    2, 0x06,   49 /* Public */,
       9,    1,   79,    2, 0x06,   51 /* Public */,
      12,    1,   82,    2, 0x06,   53 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      13,    1,   85,    2, 0x0a,   55 /* Public */,
      15,    1,   88,    2, 0x0a,   57 /* Public */,
      17,    1,   91,    2, 0x0a,   59 /* Public */,
      19,    1,   94,    2, 0x0a,   61 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,   14,
    QMetaType::Void, 0x80000000 | 3,   16,
    QMetaType::Void, 0x80000000 | 10,   18,
    QMetaType::Void, 0x80000000 | 10,   20,

 // properties: name, type, flags
      21, 0x80000000 | 22, 0x00015009, uint(-1), 0,
      23, 0x80000000 | 24, 0x00015009, uint(-1), 0,
       8, 0x80000000 | 25, 0x0001510b, uint(2), 0,
      16, 0x80000000 | 3, 0x0001510b, uint(0), 0,
      26, QMetaType::Bool, 0x00015103, uint(-1), 0,
      27, 0x80000000 | 28, 0x0001510b, uint(-1), 0,
      29, QMetaType::Bool, 0x00015103, uint(-1), 0,
      30, QMetaType::Bool, 0x00015103, uint(-1), 0,
      31, QMetaType::Int, 0x00015103, uint(-1), 0,
      32, QMetaType::QFont, 0x00015103, uint(-1), 0,
      33, QMetaType::QColor, 0x00015103, uint(-1), 0,
      34, QMetaType::Double, 0x00015103, uint(-1), 0,
      35, 0x80000000 | 36, 0x0001510b, uint(-1), 0,
      37, QMetaType::QString, 0x00015103, uint(-1), 0,
      38, QMetaType::Int, 0x00015103, uint(-1), 0,
      39, 0x80000000 | 40, 0x00015009, uint(-1), 0,
      41, QMetaType::QStringList, 0x00015001, uint(-1), 0,
      42, QMetaType::Int, 0x00015103, uint(-1), 0,
      43, QMetaType::Int, 0x00015103, uint(-1), 0,
      44, QMetaType::Bool, 0x00015103, uint(-1), 0,
      45, QMetaType::Int, 0x00015103, uint(-1), 0,
      46, QMetaType::Int, 0x00015103, uint(-1), 0,
      47, QMetaType::QPen, 0x00015103, uint(-1), 0,
      48, QMetaType::QPen, 0x00015103, uint(-1), 0,
      49, QMetaType::QPen, 0x00015103, uint(-1), 0,
      50, QMetaType::QFont, 0x00015103, uint(-1), 0,
      51, QMetaType::QColor, 0x00015103, uint(-1), 0,
      52, QMetaType::QString, 0x00015103, uint(-1), 0,
      53, QMetaType::Int, 0x00015103, uint(-1), 0,
      54, QMetaType::Int, 0x00015103, uint(-1), 0,
      55, QMetaType::Int, 0x00015103, uint(-1), 0,
      20, 0x80000000 | 56, 0x0001510b, uint(3), 0,
      18, 0x80000000 | 56, 0x0001510b, uint(4), 0,
      57, QMetaType::QFont, 0x00015103, uint(-1), 0,
      58, QMetaType::QFont, 0x00015103, uint(-1), 0,
      59, QMetaType::QColor, 0x00015103, uint(-1), 0,
      60, QMetaType::QColor, 0x00015103, uint(-1), 0,
      61, QMetaType::QPen, 0x00015103, uint(-1), 0,
      62, QMetaType::QPen, 0x00015103, uint(-1), 0,
      63, QMetaType::QPen, 0x00015103, uint(-1), 0,
      64, 0x80000000 | 65, 0x0001510b, uint(-1), 0,
      66, 0x80000000 | 65, 0x0001510b, uint(-1), 0,
      67, 0x80000000 | 68, 0x00015009, uint(-1), 0,

 // enums: name, alias, flags, count, data
      22,   22, 0x0,    4,  342,
      73,   22, 0x1,    4,  350,
      36,   36, 0x0,    2,  358,
      25,   25, 0x0,    2,  362,
      78,   78, 0x0,    4,  366,
      56,   78, 0x1,    4,  374,

 // enum data: key, value
      69, uint(QCPAxis::atLeft),
      70, uint(QCPAxis::atRight),
      71, uint(QCPAxis::atTop),
      72, uint(QCPAxis::atBottom),
      69, uint(QCPAxis::atLeft),
      70, uint(QCPAxis::atRight),
      71, uint(QCPAxis::atTop),
      72, uint(QCPAxis::atBottom),
      74, uint(QCPAxis::lsInside),
      75, uint(QCPAxis::lsOutside),
      76, uint(QCPAxis::stLinear),
      77, uint(QCPAxis::stLogarithmic),
      79, uint(QCPAxis::spNone),
      80, uint(QCPAxis::spAxis),
      81, uint(QCPAxis::spTickLabels),
      82, uint(QCPAxis::spAxisLabel),
      79, uint(QCPAxis::spNone),
      80, uint(QCPAxis::spAxis),
      81, uint(QCPAxis::spTickLabels),
      82, uint(QCPAxis::spAxisLabel),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPAxis::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayerable::staticMetaObject>(),
    qt_meta_stringdata_QCPAxis.offsetsAndSizes,
    qt_meta_data_QCPAxis,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPAxis_t,
        // property 'axisType'
        QtPrivate::TypeAndForceComplete<AxisType, std::true_type>,
        // property 'axisRect'
        QtPrivate::TypeAndForceComplete<QCPAxisRect*, std::true_type>,
        // property 'scaleType'
        QtPrivate::TypeAndForceComplete<ScaleType, std::true_type>,
        // property 'range'
        QtPrivate::TypeAndForceComplete<QCPRange, std::true_type>,
        // property 'rangeReversed'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'ticker'
        QtPrivate::TypeAndForceComplete<QSharedPointer<QCPAxisTicker>, std::true_type>,
        // property 'ticks'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'tickLabels'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'tickLabelPadding'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'tickLabelFont'
        QtPrivate::TypeAndForceComplete<QFont, std::true_type>,
        // property 'tickLabelColor'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'tickLabelRotation'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'tickLabelSide'
        QtPrivate::TypeAndForceComplete<LabelSide, std::true_type>,
        // property 'numberFormat'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'numberPrecision'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'tickVector'
        QtPrivate::TypeAndForceComplete<QList<double>, std::true_type>,
        // property 'tickVectorLabels'
        QtPrivate::TypeAndForceComplete<QList<QString>, std::true_type>,
        // property 'tickLengthIn'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'tickLengthOut'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'subTicks'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'subTickLengthIn'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'subTickLengthOut'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'basePen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'tickPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'subTickPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'labelFont'
        QtPrivate::TypeAndForceComplete<QFont, std::true_type>,
        // property 'labelColor'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'label'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'labelPadding'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'padding'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'offset'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'selectedParts'
        QtPrivate::TypeAndForceComplete<SelectableParts, std::true_type>,
        // property 'selectableParts'
        QtPrivate::TypeAndForceComplete<SelectableParts, std::true_type>,
        // property 'selectedTickLabelFont'
        QtPrivate::TypeAndForceComplete<QFont, std::true_type>,
        // property 'selectedLabelFont'
        QtPrivate::TypeAndForceComplete<QFont, std::true_type>,
        // property 'selectedTickLabelColor'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'selectedLabelColor'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'selectedBasePen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'selectedTickPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'selectedSubTickPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'lowerEnding'
        QtPrivate::TypeAndForceComplete<QCPLineEnding, std::true_type>,
        // property 'upperEnding'
        QtPrivate::TypeAndForceComplete<QCPLineEnding, std::true_type>,
        // property 'grid'
        QtPrivate::TypeAndForceComplete<QCPGrid*, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPAxis, std::true_type>,
        // method 'rangeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        // method 'rangeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        // method 'scaleTypeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAxis::ScaleType, std::false_type>,
        // method 'selectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPAxis::SelectableParts &, std::false_type>,
        // method 'selectableChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPAxis::SelectableParts &, std::false_type>,
        // method 'setScaleType'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAxis::ScaleType, std::false_type>,
        // method 'setRange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        // method 'setSelectableParts'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPAxis::SelectableParts &, std::false_type>,
        // method 'setSelectedParts'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPAxis::SelectableParts &, std::false_type>
    >,
    nullptr
} };

void QCPAxis::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCPAxis *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->rangeChanged((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1]))); break;
        case 1: _t->rangeChanged((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[2]))); break;
        case 2: _t->scaleTypeChanged((*reinterpret_cast< std::add_pointer_t<QCPAxis::ScaleType>>(_a[1]))); break;
        case 3: _t->selectionChanged((*reinterpret_cast< std::add_pointer_t<QCPAxis::SelectableParts>>(_a[1]))); break;
        case 4: _t->selectableChanged((*reinterpret_cast< std::add_pointer_t<QCPAxis::SelectableParts>>(_a[1]))); break;
        case 5: _t->setScaleType((*reinterpret_cast< std::add_pointer_t<QCPAxis::ScaleType>>(_a[1]))); break;
        case 6: _t->setRange((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1]))); break;
        case 7: _t->setSelectableParts((*reinterpret_cast< std::add_pointer_t<QCPAxis::SelectableParts>>(_a[1]))); break;
        case 8: _t->setSelectedParts((*reinterpret_cast< std::add_pointer_t<QCPAxis::SelectableParts>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAxis::ScaleType >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAxis::ScaleType >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QCPAxis::*)(const QCPRange & );
            if (_t _q_method = &QCPAxis::rangeChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QCPAxis::*)(const QCPRange & , const QCPRange & );
            if (_t _q_method = &QCPAxis::rangeChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QCPAxis::*)(QCPAxis::ScaleType );
            if (_t _q_method = &QCPAxis::scaleTypeChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (QCPAxis::*)(const QCPAxis::SelectableParts & );
            if (_t _q_method = &QCPAxis::selectionChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (QCPAxis::*)(const QCPAxis::SelectableParts & );
            if (_t _q_method = &QCPAxis::selectableChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxisRect* >(); break;
        case 42:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPGrid* >(); break;
        case 15:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<double> >(); break;
        case 5:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QSharedPointer<QCPAxisTicker> >(); break;
        }
    }
else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPAxis *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< AxisType*>(_v) = _t->axisType(); break;
        case 1: *reinterpret_cast< QCPAxisRect**>(_v) = _t->axisRect(); break;
        case 2: *reinterpret_cast< ScaleType*>(_v) = _t->scaleType(); break;
        case 3: *reinterpret_cast< QCPRange*>(_v) = _t->range(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->rangeReversed(); break;
        case 5: *reinterpret_cast< QSharedPointer<QCPAxisTicker>*>(_v) = _t->ticker(); break;
        case 6: *reinterpret_cast< bool*>(_v) = _t->ticks(); break;
        case 7: *reinterpret_cast< bool*>(_v) = _t->tickLabels(); break;
        case 8: *reinterpret_cast< int*>(_v) = _t->tickLabelPadding(); break;
        case 9: *reinterpret_cast< QFont*>(_v) = _t->tickLabelFont(); break;
        case 10: *reinterpret_cast< QColor*>(_v) = _t->tickLabelColor(); break;
        case 11: *reinterpret_cast< double*>(_v) = _t->tickLabelRotation(); break;
        case 12: *reinterpret_cast< LabelSide*>(_v) = _t->tickLabelSide(); break;
        case 13: *reinterpret_cast< QString*>(_v) = _t->numberFormat(); break;
        case 14: *reinterpret_cast< int*>(_v) = _t->numberPrecision(); break;
        case 15: *reinterpret_cast< QList<double>*>(_v) = _t->tickVector(); break;
        case 16: *reinterpret_cast< QList<QString>*>(_v) = _t->tickVectorLabels(); break;
        case 17: *reinterpret_cast< int*>(_v) = _t->tickLengthIn(); break;
        case 18: *reinterpret_cast< int*>(_v) = _t->tickLengthOut(); break;
        case 19: *reinterpret_cast< bool*>(_v) = _t->subTicks(); break;
        case 20: *reinterpret_cast< int*>(_v) = _t->subTickLengthIn(); break;
        case 21: *reinterpret_cast< int*>(_v) = _t->subTickLengthOut(); break;
        case 22: *reinterpret_cast< QPen*>(_v) = _t->basePen(); break;
        case 23: *reinterpret_cast< QPen*>(_v) = _t->tickPen(); break;
        case 24: *reinterpret_cast< QPen*>(_v) = _t->subTickPen(); break;
        case 25: *reinterpret_cast< QFont*>(_v) = _t->labelFont(); break;
        case 26: *reinterpret_cast< QColor*>(_v) = _t->labelColor(); break;
        case 27: *reinterpret_cast< QString*>(_v) = _t->label(); break;
        case 28: *reinterpret_cast< int*>(_v) = _t->labelPadding(); break;
        case 29: *reinterpret_cast< int*>(_v) = _t->padding(); break;
        case 30: *reinterpret_cast< int*>(_v) = _t->offset(); break;
        case 31: *reinterpret_cast<int*>(_v) = QFlag(_t->selectedParts()); break;
        case 32: *reinterpret_cast<int*>(_v) = QFlag(_t->selectableParts()); break;
        case 33: *reinterpret_cast< QFont*>(_v) = _t->selectedTickLabelFont(); break;
        case 34: *reinterpret_cast< QFont*>(_v) = _t->selectedLabelFont(); break;
        case 35: *reinterpret_cast< QColor*>(_v) = _t->selectedTickLabelColor(); break;
        case 36: *reinterpret_cast< QColor*>(_v) = _t->selectedLabelColor(); break;
        case 37: *reinterpret_cast< QPen*>(_v) = _t->selectedBasePen(); break;
        case 38: *reinterpret_cast< QPen*>(_v) = _t->selectedTickPen(); break;
        case 39: *reinterpret_cast< QPen*>(_v) = _t->selectedSubTickPen(); break;
        case 40: *reinterpret_cast< QCPLineEnding*>(_v) = _t->lowerEnding(); break;
        case 41: *reinterpret_cast< QCPLineEnding*>(_v) = _t->upperEnding(); break;
        case 42: *reinterpret_cast< QCPGrid**>(_v) = _t->grid(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPAxis *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 2: _t->setScaleType(*reinterpret_cast< ScaleType*>(_v)); break;
        case 3: _t->setRange(*reinterpret_cast< QCPRange*>(_v)); break;
        case 4: _t->setRangeReversed(*reinterpret_cast< bool*>(_v)); break;
        case 5: _t->setTicker(*reinterpret_cast< QSharedPointer<QCPAxisTicker>*>(_v)); break;
        case 6: _t->setTicks(*reinterpret_cast< bool*>(_v)); break;
        case 7: _t->setTickLabels(*reinterpret_cast< bool*>(_v)); break;
        case 8: _t->setTickLabelPadding(*reinterpret_cast< int*>(_v)); break;
        case 9: _t->setTickLabelFont(*reinterpret_cast< QFont*>(_v)); break;
        case 10: _t->setTickLabelColor(*reinterpret_cast< QColor*>(_v)); break;
        case 11: _t->setTickLabelRotation(*reinterpret_cast< double*>(_v)); break;
        case 12: _t->setTickLabelSide(*reinterpret_cast< LabelSide*>(_v)); break;
        case 13: _t->setNumberFormat(*reinterpret_cast< QString*>(_v)); break;
        case 14: _t->setNumberPrecision(*reinterpret_cast< int*>(_v)); break;
        case 17: _t->setTickLengthIn(*reinterpret_cast< int*>(_v)); break;
        case 18: _t->setTickLengthOut(*reinterpret_cast< int*>(_v)); break;
        case 19: _t->setSubTicks(*reinterpret_cast< bool*>(_v)); break;
        case 20: _t->setSubTickLengthIn(*reinterpret_cast< int*>(_v)); break;
        case 21: _t->setSubTickLengthOut(*reinterpret_cast< int*>(_v)); break;
        case 22: _t->setBasePen(*reinterpret_cast< QPen*>(_v)); break;
        case 23: _t->setTickPen(*reinterpret_cast< QPen*>(_v)); break;
        case 24: _t->setSubTickPen(*reinterpret_cast< QPen*>(_v)); break;
        case 25: _t->setLabelFont(*reinterpret_cast< QFont*>(_v)); break;
        case 26: _t->setLabelColor(*reinterpret_cast< QColor*>(_v)); break;
        case 27: _t->setLabel(*reinterpret_cast< QString*>(_v)); break;
        case 28: _t->setLabelPadding(*reinterpret_cast< int*>(_v)); break;
        case 29: _t->setPadding(*reinterpret_cast< int*>(_v)); break;
        case 30: _t->setOffset(*reinterpret_cast< int*>(_v)); break;
        case 31: _t->setSelectedParts(QFlag(*reinterpret_cast<int*>(_v))); break;
        case 32: _t->setSelectableParts(QFlag(*reinterpret_cast<int*>(_v))); break;
        case 33: _t->setSelectedTickLabelFont(*reinterpret_cast< QFont*>(_v)); break;
        case 34: _t->setSelectedLabelFont(*reinterpret_cast< QFont*>(_v)); break;
        case 35: _t->setSelectedTickLabelColor(*reinterpret_cast< QColor*>(_v)); break;
        case 36: _t->setSelectedLabelColor(*reinterpret_cast< QColor*>(_v)); break;
        case 37: _t->setSelectedBasePen(*reinterpret_cast< QPen*>(_v)); break;
        case 38: _t->setSelectedTickPen(*reinterpret_cast< QPen*>(_v)); break;
        case 39: _t->setSelectedSubTickPen(*reinterpret_cast< QPen*>(_v)); break;
        case 40: _t->setLowerEnding(*reinterpret_cast< QCPLineEnding*>(_v)); break;
        case 41: _t->setUpperEnding(*reinterpret_cast< QCPLineEnding*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *QCPAxis::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPAxis::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPAxis.stringdata0))
        return static_cast<void*>(this);
    return QCPLayerable::qt_metacast(_clname);
}

int QCPAxis::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayerable::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 43;
    }
    return _id;
}

// SIGNAL 0
void QCPAxis::rangeChanged(const QCPRange & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCPAxis::rangeChanged(const QCPRange & _t1, const QCPRange & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QCPAxis::scaleTypeChanged(QCPAxis::ScaleType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QCPAxis::selectionChanged(const QCPAxis::SelectableParts & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QCPAxis::selectableChanged(const QCPAxis::SelectableParts & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
namespace {
struct qt_meta_stringdata_QCPScatterStyle_t {
    uint offsetsAndSizes[56];
    char stringdata0[16];
    char stringdata1[16];
    char stringdata2[7];
    char stringdata3[6];
    char stringdata4[8];
    char stringdata5[7];
    char stringdata6[8];
    char stringdata7[6];
    char stringdata8[18];
    char stringdata9[13];
    char stringdata10[7];
    char stringdata11[6];
    char stringdata12[8];
    char stringdata13[7];
    char stringdata14[9];
    char stringdata15[7];
    char stringdata16[9];
    char stringdata17[10];
    char stringdata18[7];
    char stringdata19[11];
    char stringdata20[19];
    char stringdata21[14];
    char stringdata22[13];
    char stringdata23[14];
    char stringdata24[13];
    char stringdata25[8];
    char stringdata26[9];
    char stringdata27[9];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPScatterStyle_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPScatterStyle_t qt_meta_stringdata_QCPScatterStyle = {
    {
        QT_MOC_LITERAL(0, 15),  // "QCPScatterStyle"
        QT_MOC_LITERAL(16, 15),  // "ScatterProperty"
        QT_MOC_LITERAL(32, 6),  // "spNone"
        QT_MOC_LITERAL(39, 5),  // "spPen"
        QT_MOC_LITERAL(45, 7),  // "spBrush"
        QT_MOC_LITERAL(53, 6),  // "spSize"
        QT_MOC_LITERAL(60, 7),  // "spShape"
        QT_MOC_LITERAL(68, 5),  // "spAll"
        QT_MOC_LITERAL(74, 17),  // "ScatterProperties"
        QT_MOC_LITERAL(92, 12),  // "ScatterShape"
        QT_MOC_LITERAL(105, 6),  // "ssNone"
        QT_MOC_LITERAL(112, 5),  // "ssDot"
        QT_MOC_LITERAL(118, 7),  // "ssCross"
        QT_MOC_LITERAL(126, 6),  // "ssPlus"
        QT_MOC_LITERAL(133, 8),  // "ssCircle"
        QT_MOC_LITERAL(142, 6),  // "ssDisc"
        QT_MOC_LITERAL(149, 8),  // "ssSquare"
        QT_MOC_LITERAL(158, 9),  // "ssDiamond"
        QT_MOC_LITERAL(168, 6),  // "ssStar"
        QT_MOC_LITERAL(175, 10),  // "ssTriangle"
        QT_MOC_LITERAL(186, 18),  // "ssTriangleInverted"
        QT_MOC_LITERAL(205, 13),  // "ssCrossSquare"
        QT_MOC_LITERAL(219, 12),  // "ssPlusSquare"
        QT_MOC_LITERAL(232, 13),  // "ssCrossCircle"
        QT_MOC_LITERAL(246, 12),  // "ssPlusCircle"
        QT_MOC_LITERAL(259, 7),  // "ssPeace"
        QT_MOC_LITERAL(267, 8),  // "ssPixmap"
        QT_MOC_LITERAL(276, 8)   // "ssCustom"
    },
    "QCPScatterStyle",
    "ScatterProperty",
    "spNone",
    "spPen",
    "spBrush",
    "spSize",
    "spShape",
    "spAll",
    "ScatterProperties",
    "ScatterShape",
    "ssNone",
    "ssDot",
    "ssCross",
    "ssPlus",
    "ssCircle",
    "ssDisc",
    "ssSquare",
    "ssDiamond",
    "ssStar",
    "ssTriangle",
    "ssTriangleInverted",
    "ssCrossSquare",
    "ssPlusSquare",
    "ssCrossCircle",
    "ssPlusCircle",
    "ssPeace",
    "ssPixmap",
    "ssCustom"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPScatterStyle[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       3,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    6,   29,
       8,    1, 0x1,    6,   41,
       9,    9, 0x0,   18,   53,

 // enum data: key, value
       2, uint(QCPScatterStyle::spNone),
       3, uint(QCPScatterStyle::spPen),
       4, uint(QCPScatterStyle::spBrush),
       5, uint(QCPScatterStyle::spSize),
       6, uint(QCPScatterStyle::spShape),
       7, uint(QCPScatterStyle::spAll),
       2, uint(QCPScatterStyle::spNone),
       3, uint(QCPScatterStyle::spPen),
       4, uint(QCPScatterStyle::spBrush),
       5, uint(QCPScatterStyle::spSize),
       6, uint(QCPScatterStyle::spShape),
       7, uint(QCPScatterStyle::spAll),
      10, uint(QCPScatterStyle::ssNone),
      11, uint(QCPScatterStyle::ssDot),
      12, uint(QCPScatterStyle::ssCross),
      13, uint(QCPScatterStyle::ssPlus),
      14, uint(QCPScatterStyle::ssCircle),
      15, uint(QCPScatterStyle::ssDisc),
      16, uint(QCPScatterStyle::ssSquare),
      17, uint(QCPScatterStyle::ssDiamond),
      18, uint(QCPScatterStyle::ssStar),
      19, uint(QCPScatterStyle::ssTriangle),
      20, uint(QCPScatterStyle::ssTriangleInverted),
      21, uint(QCPScatterStyle::ssCrossSquare),
      22, uint(QCPScatterStyle::ssPlusSquare),
      23, uint(QCPScatterStyle::ssCrossCircle),
      24, uint(QCPScatterStyle::ssPlusCircle),
      25, uint(QCPScatterStyle::ssPeace),
      26, uint(QCPScatterStyle::ssPixmap),
      27, uint(QCPScatterStyle::ssCustom),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPScatterStyle::staticMetaObject = { {
    nullptr,
    qt_meta_stringdata_QCPScatterStyle.offsetsAndSizes,
    qt_meta_data_QCPScatterStyle,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPScatterStyle_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPScatterStyle, std::true_type>
    >,
    nullptr
} };

namespace {
struct qt_meta_stringdata_QCPSelectionDecorator_t {
    uint offsetsAndSizes[2];
    char stringdata0[22];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPSelectionDecorator_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPSelectionDecorator_t qt_meta_stringdata_QCPSelectionDecorator = {
    {
        QT_MOC_LITERAL(0, 21)   // "QCPSelectionDecorator"
    },
    "QCPSelectionDecorator"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPSelectionDecorator[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPSelectionDecorator::staticMetaObject = { {
    nullptr,
    qt_meta_stringdata_QCPSelectionDecorator.offsetsAndSizes,
    qt_meta_data_QCPSelectionDecorator,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPSelectionDecorator_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPSelectionDecorator, std::true_type>
    >,
    nullptr
} };

namespace {
struct qt_meta_stringdata_QCPAbstractPlottable_t {
    uint offsetsAndSizes[42];
    char stringdata0[21];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[17];
    char stringdata5[10];
    char stringdata6[18];
    char stringdata7[19];
    char stringdata8[11];
    char stringdata9[14];
    char stringdata10[13];
    char stringdata11[5];
    char stringdata12[16];
    char stringdata13[20];
    char stringdata14[4];
    char stringdata15[6];
    char stringdata16[8];
    char stringdata17[9];
    char stringdata18[10];
    char stringdata19[19];
    char stringdata20[23];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPAbstractPlottable_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPAbstractPlottable_t qt_meta_stringdata_QCPAbstractPlottable = {
    {
        QT_MOC_LITERAL(0, 20),  // "QCPAbstractPlottable"
        QT_MOC_LITERAL(21, 16),  // "selectionChanged"
        QT_MOC_LITERAL(38, 0),  // ""
        QT_MOC_LITERAL(39, 8),  // "selected"
        QT_MOC_LITERAL(48, 16),  // "QCPDataSelection"
        QT_MOC_LITERAL(65, 9),  // "selection"
        QT_MOC_LITERAL(75, 17),  // "selectableChanged"
        QT_MOC_LITERAL(93, 18),  // "QCP::SelectionType"
        QT_MOC_LITERAL(112, 10),  // "selectable"
        QT_MOC_LITERAL(123, 13),  // "setSelectable"
        QT_MOC_LITERAL(137, 12),  // "setSelection"
        QT_MOC_LITERAL(150, 4),  // "name"
        QT_MOC_LITERAL(155, 15),  // "antialiasedFill"
        QT_MOC_LITERAL(171, 19),  // "antialiasedScatters"
        QT_MOC_LITERAL(191, 3),  // "pen"
        QT_MOC_LITERAL(195, 5),  // "brush"
        QT_MOC_LITERAL(201, 7),  // "keyAxis"
        QT_MOC_LITERAL(209, 8),  // "QCPAxis*"
        QT_MOC_LITERAL(218, 9),  // "valueAxis"
        QT_MOC_LITERAL(228, 18),  // "selectionDecorator"
        QT_MOC_LITERAL(247, 22)   // "QCPSelectionDecorator*"
    },
    "QCPAbstractPlottable",
    "selectionChanged",
    "",
    "selected",
    "QCPDataSelection",
    "selection",
    "selectableChanged",
    "QCP::SelectionType",
    "selectable",
    "setSelectable",
    "setSelection",
    "name",
    "antialiasedFill",
    "antialiasedScatters",
    "pen",
    "brush",
    "keyAxis",
    "QCPAxis*",
    "valueAxis",
    "selectionDecorator",
    "QCPSelectionDecorator*"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPAbstractPlottable[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
      10,   59, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   44,    2, 0x06,   11 /* Public */,
       1,    1,   47,    2, 0x06,   13 /* Public */,
       6,    1,   50,    2, 0x06,   15 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    1,   53,    2, 0x0a,   17 /* Public */,
      10,    1,   56,    2, 0x0a,   19 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 4,    5,

 // properties: name, type, flags
      11, QMetaType::QString, 0x00015103, uint(-1), 0,
      12, QMetaType::Bool, 0x00015103, uint(-1), 0,
      13, QMetaType::Bool, 0x00015103, uint(-1), 0,
      14, QMetaType::QPen, 0x00015103, uint(-1), 0,
      15, QMetaType::QBrush, 0x00015103, uint(-1), 0,
      16, 0x80000000 | 17, 0x0001510b, uint(-1), 0,
      18, 0x80000000 | 17, 0x0001510b, uint(-1), 0,
       8, 0x80000000 | 7, 0x0001510b, uint(2), 0,
       5, 0x80000000 | 4, 0x0001510b, uint(0), 0,
      19, 0x80000000 | 20, 0x0001510b, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT static const QMetaObject::SuperData qt_meta_extradata_QCPAbstractPlottable[] = {
    QMetaObject::SuperData::link<QCP::staticMetaObject>(),
    nullptr
};

Q_CONSTINIT const QMetaObject QCPAbstractPlottable::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayerable::staticMetaObject>(),
    qt_meta_stringdata_QCPAbstractPlottable.offsetsAndSizes,
    qt_meta_data_QCPAbstractPlottable,
    qt_static_metacall,
    qt_meta_extradata_QCPAbstractPlottable,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPAbstractPlottable_t,
        // property 'name'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'antialiasedFill'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'antialiasedScatters'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'pen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'brush'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // property 'keyAxis'
        QtPrivate::TypeAndForceComplete<QCPAxis*, std::true_type>,
        // property 'valueAxis'
        QtPrivate::TypeAndForceComplete<QCPAxis*, std::true_type>,
        // property 'selectable'
        QtPrivate::TypeAndForceComplete<QCP::SelectionType, std::true_type>,
        // property 'selection'
        QtPrivate::TypeAndForceComplete<QCPDataSelection, std::true_type>,
        // property 'selectionDecorator'
        QtPrivate::TypeAndForceComplete<QCPSelectionDecorator*, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPAbstractPlottable, std::true_type>,
        // method 'selectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'selectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPDataSelection &, std::false_type>,
        // method 'selectableChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCP::SelectionType, std::false_type>,
        // method 'setSelectable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCP::SelectionType, std::false_type>,
        // method 'setSelection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPDataSelection, std::false_type>
    >,
    nullptr
} };

void QCPAbstractPlottable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCPAbstractPlottable *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->selectionChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->selectionChanged((*reinterpret_cast< std::add_pointer_t<QCPDataSelection>>(_a[1]))); break;
        case 2: _t->selectableChanged((*reinterpret_cast< std::add_pointer_t<QCP::SelectionType>>(_a[1]))); break;
        case 3: _t->setSelectable((*reinterpret_cast< std::add_pointer_t<QCP::SelectionType>>(_a[1]))); break;
        case 4: _t->setSelection((*reinterpret_cast< std::add_pointer_t<QCPDataSelection>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPDataSelection >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPDataSelection >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QCPAbstractPlottable::*)(bool );
            if (_t _q_method = &QCPAbstractPlottable::selectionChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QCPAbstractPlottable::*)(const QCPDataSelection & );
            if (_t _q_method = &QCPAbstractPlottable::selectionChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QCPAbstractPlottable::*)(QCP::SelectionType );
            if (_t _q_method = &QCPAbstractPlottable::selectableChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
        case 5:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxis* >(); break;
        case 8:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPDataSelection >(); break;
        case 9:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPSelectionDecorator* >(); break;
        }
    }
else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPAbstractPlottable *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->name(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->antialiasedFill(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->antialiasedScatters(); break;
        case 3: *reinterpret_cast< QPen*>(_v) = _t->pen(); break;
        case 4: *reinterpret_cast< QBrush*>(_v) = _t->brush(); break;
        case 5: *reinterpret_cast< QCPAxis**>(_v) = _t->keyAxis(); break;
        case 6: *reinterpret_cast< QCPAxis**>(_v) = _t->valueAxis(); break;
        case 7: *reinterpret_cast< QCP::SelectionType*>(_v) = _t->selectable(); break;
        case 8: *reinterpret_cast< QCPDataSelection*>(_v) = _t->selection(); break;
        case 9: *reinterpret_cast< QCPSelectionDecorator**>(_v) = _t->selectionDecorator(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPAbstractPlottable *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setName(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setAntialiasedFill(*reinterpret_cast< bool*>(_v)); break;
        case 2: _t->setAntialiasedScatters(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->setPen(*reinterpret_cast< QPen*>(_v)); break;
        case 4: _t->setBrush(*reinterpret_cast< QBrush*>(_v)); break;
        case 5: _t->setKeyAxis(*reinterpret_cast< QCPAxis**>(_v)); break;
        case 6: _t->setValueAxis(*reinterpret_cast< QCPAxis**>(_v)); break;
        case 7: _t->setSelectable(*reinterpret_cast< QCP::SelectionType*>(_v)); break;
        case 8: _t->setSelection(*reinterpret_cast< QCPDataSelection*>(_v)); break;
        case 9: _t->setSelectionDecorator(*reinterpret_cast< QCPSelectionDecorator**>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *QCPAbstractPlottable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPAbstractPlottable::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPAbstractPlottable.stringdata0))
        return static_cast<void*>(this);
    return QCPLayerable::qt_metacast(_clname);
}

int QCPAbstractPlottable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayerable::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void QCPAbstractPlottable::selectionChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCPAbstractPlottable::selectionChanged(const QCPDataSelection & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QCPAbstractPlottable::selectableChanged(QCP::SelectionType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
namespace {
struct qt_meta_stringdata_QCPItemAnchor_t {
    uint offsetsAndSizes[2];
    char stringdata0[14];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPItemAnchor_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPItemAnchor_t qt_meta_stringdata_QCPItemAnchor = {
    {
        QT_MOC_LITERAL(0, 13)   // "QCPItemAnchor"
    },
    "QCPItemAnchor"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPItemAnchor[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPItemAnchor::staticMetaObject = { {
    nullptr,
    qt_meta_stringdata_QCPItemAnchor.offsetsAndSizes,
    qt_meta_data_QCPItemAnchor,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPItemAnchor_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPItemAnchor, std::true_type>
    >,
    nullptr
} };

namespace {
struct qt_meta_stringdata_QCPItemPosition_t {
    uint offsetsAndSizes[12];
    char stringdata0[16];
    char stringdata1[13];
    char stringdata2[11];
    char stringdata3[16];
    char stringdata4[16];
    char stringdata5[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPItemPosition_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPItemPosition_t qt_meta_stringdata_QCPItemPosition = {
    {
        QT_MOC_LITERAL(0, 15),  // "QCPItemPosition"
        QT_MOC_LITERAL(16, 12),  // "PositionType"
        QT_MOC_LITERAL(29, 10),  // "ptAbsolute"
        QT_MOC_LITERAL(40, 15),  // "ptViewportRatio"
        QT_MOC_LITERAL(56, 15),  // "ptAxisRectRatio"
        QT_MOC_LITERAL(72, 12)   // "ptPlotCoords"
    },
    "QCPItemPosition",
    "PositionType",
    "ptAbsolute",
    "ptViewportRatio",
    "ptAxisRectRatio",
    "ptPlotCoords"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPItemPosition[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    4,   19,

 // enum data: key, value
       2, uint(QCPItemPosition::ptAbsolute),
       3, uint(QCPItemPosition::ptViewportRatio),
       4, uint(QCPItemPosition::ptAxisRectRatio),
       5, uint(QCPItemPosition::ptPlotCoords),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPItemPosition::staticMetaObject = { {
    QtPrivate::MetaObjectForType<QCPItemAnchor>::value,
    qt_meta_stringdata_QCPItemPosition.offsetsAndSizes,
    qt_meta_data_QCPItemPosition,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPItemPosition_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPItemPosition, std::true_type>
    >,
    nullptr
} };

namespace {
struct qt_meta_stringdata_QCPAbstractItem_t {
    uint offsetsAndSizes[22];
    char stringdata0[16];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[18];
    char stringdata5[11];
    char stringdata6[14];
    char stringdata7[12];
    char stringdata8[15];
    char stringdata9[13];
    char stringdata10[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPAbstractItem_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPAbstractItem_t qt_meta_stringdata_QCPAbstractItem = {
    {
        QT_MOC_LITERAL(0, 15),  // "QCPAbstractItem"
        QT_MOC_LITERAL(16, 16),  // "selectionChanged"
        QT_MOC_LITERAL(33, 0),  // ""
        QT_MOC_LITERAL(34, 8),  // "selected"
        QT_MOC_LITERAL(43, 17),  // "selectableChanged"
        QT_MOC_LITERAL(61, 10),  // "selectable"
        QT_MOC_LITERAL(72, 13),  // "setSelectable"
        QT_MOC_LITERAL(86, 11),  // "setSelected"
        QT_MOC_LITERAL(98, 14),  // "clipToAxisRect"
        QT_MOC_LITERAL(113, 12),  // "clipAxisRect"
        QT_MOC_LITERAL(126, 12)   // "QCPAxisRect*"
    },
    "QCPAbstractItem",
    "selectionChanged",
    "",
    "selected",
    "selectableChanged",
    "selectable",
    "setSelectable",
    "setSelected",
    "clipToAxisRect",
    "clipAxisRect",
    "QCPAxisRect*"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPAbstractItem[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       4,   50, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   38,    2, 0x06,    5 /* Public */,
       4,    1,   41,    2, 0x06,    7 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    1,   44,    2, 0x0a,    9 /* Public */,
       7,    1,   47,    2, 0x0a,   11 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    3,

 // properties: name, type, flags
       8, QMetaType::Bool, 0x00015103, uint(-1), 0,
       9, 0x80000000 | 10, 0x0001510b, uint(-1), 0,
       5, QMetaType::Bool, 0x00015103, uint(1), 0,
       3, QMetaType::Bool, 0x00015103, uint(0), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPAbstractItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayerable::staticMetaObject>(),
    qt_meta_stringdata_QCPAbstractItem.offsetsAndSizes,
    qt_meta_data_QCPAbstractItem,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPAbstractItem_t,
        // property 'clipToAxisRect'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'clipAxisRect'
        QtPrivate::TypeAndForceComplete<QCPAxisRect*, std::true_type>,
        // property 'selectable'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'selected'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPAbstractItem, std::true_type>,
        // method 'selectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'selectableChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setSelectable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void QCPAbstractItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCPAbstractItem *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->selectionChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->selectableChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->setSelectable((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->setSelected((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QCPAbstractItem::*)(bool );
            if (_t _q_method = &QCPAbstractItem::selectionChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QCPAbstractItem::*)(bool );
            if (_t _q_method = &QCPAbstractItem::selectableChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxisRect* >(); break;
        }
    }
else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPAbstractItem *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->clipToAxisRect(); break;
        case 1: *reinterpret_cast< QCPAxisRect**>(_v) = _t->clipAxisRect(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->selectable(); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->selected(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPAbstractItem *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setClipToAxisRect(*reinterpret_cast< bool*>(_v)); break;
        case 1: _t->setClipAxisRect(*reinterpret_cast< QCPAxisRect**>(_v)); break;
        case 2: _t->setSelectable(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->setSelected(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *QCPAbstractItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPAbstractItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPAbstractItem.stringdata0))
        return static_cast<void*>(this);
    return QCPLayerable::qt_metacast(_clname);
}

int QCPAbstractItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayerable::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void QCPAbstractItem::selectionChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCPAbstractItem::selectableChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
namespace {
struct qt_meta_stringdata_QCustomPlot_t {
    uint offsetsAndSizes[130];
    char stringdata0[12];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[13];
    char stringdata4[6];
    char stringdata5[11];
    char stringdata6[10];
    char stringdata7[13];
    char stringdata8[11];
    char stringdata9[13];
    char stringdata10[15];
    char stringdata11[22];
    char stringdata12[10];
    char stringdata13[10];
    char stringdata14[21];
    char stringdata15[10];
    char stringdata16[17];
    char stringdata17[5];
    char stringdata18[16];
    char stringdata19[10];
    char stringdata20[9];
    char stringdata21[5];
    char stringdata22[24];
    char stringdata23[5];
    char stringdata24[16];
    char stringdata25[12];
    char stringdata26[11];
    char stringdata27[7];
    char stringdata28[23];
    char stringdata29[18];
    char stringdata30[23];
    char stringdata31[13];
    char stringdata32[12];
    char stringdata33[12];
    char stringdata34[12];
    char stringdata35[22];
    char stringdata36[12];
    char stringdata37[7];
    char stringdata38[29];
    char stringdata39[16];
    char stringdata40[21];
    char stringdata41[5];
    char stringdata42[16];
    char stringdata43[22];
    char stringdata44[9];
    char stringdata45[11];
    char stringdata46[17];
    char stringdata47[21];
    char stringdata48[20];
    char stringdata49[11];
    char stringdata50[15];
    char stringdata51[25];
    char stringdata52[19];
    char stringdata53[21];
    char stringdata54[20];
    char stringdata55[21];
    char stringdata56[7];
    char stringdata57[16];
    char stringdata58[9];
    char stringdata59[9];
    char stringdata60[16];
    char stringdata61[19];
    char stringdata62[16];
    char stringdata63[14];
    char stringdata64[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCustomPlot_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCustomPlot_t qt_meta_stringdata_QCustomPlot = {
    {
        QT_MOC_LITERAL(0, 11),  // "QCustomPlot"
        QT_MOC_LITERAL(12, 16),  // "mouseDoubleClick"
        QT_MOC_LITERAL(29, 0),  // ""
        QT_MOC_LITERAL(30, 12),  // "QMouseEvent*"
        QT_MOC_LITERAL(43, 5),  // "event"
        QT_MOC_LITERAL(49, 10),  // "mousePress"
        QT_MOC_LITERAL(60, 9),  // "mouseMove"
        QT_MOC_LITERAL(70, 12),  // "mouseRelease"
        QT_MOC_LITERAL(83, 10),  // "mouseWheel"
        QT_MOC_LITERAL(94, 12),  // "QWheelEvent*"
        QT_MOC_LITERAL(107, 14),  // "plottableClick"
        QT_MOC_LITERAL(122, 21),  // "QCPAbstractPlottable*"
        QT_MOC_LITERAL(144, 9),  // "plottable"
        QT_MOC_LITERAL(154, 9),  // "dataIndex"
        QT_MOC_LITERAL(164, 20),  // "plottableDoubleClick"
        QT_MOC_LITERAL(185, 9),  // "itemClick"
        QT_MOC_LITERAL(195, 16),  // "QCPAbstractItem*"
        QT_MOC_LITERAL(212, 4),  // "item"
        QT_MOC_LITERAL(217, 15),  // "itemDoubleClick"
        QT_MOC_LITERAL(233, 9),  // "axisClick"
        QT_MOC_LITERAL(243, 8),  // "QCPAxis*"
        QT_MOC_LITERAL(252, 4),  // "axis"
        QT_MOC_LITERAL(257, 23),  // "QCPAxis::SelectablePart"
        QT_MOC_LITERAL(281, 4),  // "part"
        QT_MOC_LITERAL(286, 15),  // "axisDoubleClick"
        QT_MOC_LITERAL(302, 11),  // "legendClick"
        QT_MOC_LITERAL(314, 10),  // "QCPLegend*"
        QT_MOC_LITERAL(325, 6),  // "legend"
        QT_MOC_LITERAL(332, 22),  // "QCPAbstractLegendItem*"
        QT_MOC_LITERAL(355, 17),  // "legendDoubleClick"
        QT_MOC_LITERAL(373, 22),  // "selectionChangedByUser"
        QT_MOC_LITERAL(396, 12),  // "beforeReplot"
        QT_MOC_LITERAL(409, 11),  // "afterLayout"
        QT_MOC_LITERAL(421, 11),  // "afterReplot"
        QT_MOC_LITERAL(433, 11),  // "rescaleAxes"
        QT_MOC_LITERAL(445, 21),  // "onlyVisiblePlottables"
        QT_MOC_LITERAL(467, 11),  // "deselectAll"
        QT_MOC_LITERAL(479, 6),  // "replot"
        QT_MOC_LITERAL(486, 28),  // "QCustomPlot::RefreshPriority"
        QT_MOC_LITERAL(515, 15),  // "refreshPriority"
        QT_MOC_LITERAL(531, 20),  // "processRectSelection"
        QT_MOC_LITERAL(552, 4),  // "rect"
        QT_MOC_LITERAL(557, 15),  // "processRectZoom"
        QT_MOC_LITERAL(573, 21),  // "processPointSelection"
        QT_MOC_LITERAL(595, 8),  // "viewport"
        QT_MOC_LITERAL(604, 10),  // "background"
        QT_MOC_LITERAL(615, 16),  // "backgroundScaled"
        QT_MOC_LITERAL(632, 20),  // "backgroundScaledMode"
        QT_MOC_LITERAL(653, 19),  // "Qt::AspectRatioMode"
        QT_MOC_LITERAL(673, 10),  // "plotLayout"
        QT_MOC_LITERAL(684, 14),  // "QCPLayoutGrid*"
        QT_MOC_LITERAL(699, 24),  // "autoAddPlottableToLegend"
        QT_MOC_LITERAL(724, 18),  // "selectionTolerance"
        QT_MOC_LITERAL(743, 20),  // "noAntialiasingOnDrag"
        QT_MOC_LITERAL(764, 19),  // "multiSelectModifier"
        QT_MOC_LITERAL(784, 20),  // "Qt::KeyboardModifier"
        QT_MOC_LITERAL(805, 6),  // "openGl"
        QT_MOC_LITERAL(812, 15),  // "LayerInsertMode"
        QT_MOC_LITERAL(828, 8),  // "limBelow"
        QT_MOC_LITERAL(837, 8),  // "limAbove"
        QT_MOC_LITERAL(846, 15),  // "RefreshPriority"
        QT_MOC_LITERAL(862, 18),  // "rpImmediateRefresh"
        QT_MOC_LITERAL(881, 15),  // "rpQueuedRefresh"
        QT_MOC_LITERAL(897, 13),  // "rpRefreshHint"
        QT_MOC_LITERAL(911, 14)   // "rpQueuedReplot"
    },
    "QCustomPlot",
    "mouseDoubleClick",
    "",
    "QMouseEvent*",
    "event",
    "mousePress",
    "mouseMove",
    "mouseRelease",
    "mouseWheel",
    "QWheelEvent*",
    "plottableClick",
    "QCPAbstractPlottable*",
    "plottable",
    "dataIndex",
    "plottableDoubleClick",
    "itemClick",
    "QCPAbstractItem*",
    "item",
    "itemDoubleClick",
    "axisClick",
    "QCPAxis*",
    "axis",
    "QCPAxis::SelectablePart",
    "part",
    "axisDoubleClick",
    "legendClick",
    "QCPLegend*",
    "legend",
    "QCPAbstractLegendItem*",
    "legendDoubleClick",
    "selectionChangedByUser",
    "beforeReplot",
    "afterLayout",
    "afterReplot",
    "rescaleAxes",
    "onlyVisiblePlottables",
    "deselectAll",
    "replot",
    "QCustomPlot::RefreshPriority",
    "refreshPriority",
    "processRectSelection",
    "rect",
    "processRectZoom",
    "processPointSelection",
    "viewport",
    "background",
    "backgroundScaled",
    "backgroundScaledMode",
    "Qt::AspectRatioMode",
    "plotLayout",
    "QCPLayoutGrid*",
    "autoAddPlottableToLegend",
    "selectionTolerance",
    "noAntialiasingOnDrag",
    "multiSelectModifier",
    "Qt::KeyboardModifier",
    "openGl",
    "LayerInsertMode",
    "limBelow",
    "limAbove",
    "RefreshPriority",
    "rpImmediateRefresh",
    "rpQueuedRefresh",
    "rpRefreshHint",
    "rpQueuedReplot"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCustomPlot[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
      10,  257, // properties
       2,  307, // enums/sets
       0,    0, // constructors
       0,       // flags
      17,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  164,    2, 0x06,   11 /* Public */,
       5,    1,  167,    2, 0x06,   13 /* Public */,
       6,    1,  170,    2, 0x06,   15 /* Public */,
       7,    1,  173,    2, 0x06,   17 /* Public */,
       8,    1,  176,    2, 0x06,   19 /* Public */,
      10,    3,  179,    2, 0x06,   21 /* Public */,
      14,    3,  186,    2, 0x06,   25 /* Public */,
      15,    2,  193,    2, 0x06,   29 /* Public */,
      18,    2,  198,    2, 0x06,   32 /* Public */,
      19,    3,  203,    2, 0x06,   35 /* Public */,
      24,    3,  210,    2, 0x06,   39 /* Public */,
      25,    3,  217,    2, 0x06,   43 /* Public */,
      29,    3,  224,    2, 0x06,   47 /* Public */,
      30,    0,  231,    2, 0x06,   51 /* Public */,
      31,    0,  232,    2, 0x06,   52 /* Public */,
      32,    0,  233,    2, 0x06,   53 /* Public */,
      33,    0,  234,    2, 0x06,   54 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      34,    1,  235,    2, 0x0a,   55 /* Public */,
      34,    0,  238,    2, 0x2a,   57 /* Public | MethodCloned */,
      36,    0,  239,    2, 0x0a,   58 /* Public */,
      37,    1,  240,    2, 0x0a,   59 /* Public */,
      37,    0,  243,    2, 0x2a,   61 /* Public | MethodCloned */,
      40,    2,  244,    2, 0x09,   62 /* Protected */,
      42,    2,  249,    2, 0x09,   65 /* Protected */,
      43,    1,  254,    2, 0x09,   68 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 9,    4,
    QMetaType::Void, 0x80000000 | 11, QMetaType::Int, 0x80000000 | 3,   12,   13,    4,
    QMetaType::Void, 0x80000000 | 11, QMetaType::Int, 0x80000000 | 3,   12,   13,    4,
    QMetaType::Void, 0x80000000 | 16, 0x80000000 | 3,   17,    4,
    QMetaType::Void, 0x80000000 | 16, 0x80000000 | 3,   17,    4,
    QMetaType::Void, 0x80000000 | 20, 0x80000000 | 22, 0x80000000 | 3,   21,   23,    4,
    QMetaType::Void, 0x80000000 | 20, 0x80000000 | 22, 0x80000000 | 3,   21,   23,    4,
    QMetaType::Void, 0x80000000 | 26, 0x80000000 | 28, 0x80000000 | 3,   27,   17,    4,
    QMetaType::Void, 0x80000000 | 26, 0x80000000 | 28, 0x80000000 | 3,   27,   17,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,   35,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 38,   39,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QRect, 0x80000000 | 3,   41,    4,
    QMetaType::Void, QMetaType::QRect, 0x80000000 | 3,   41,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // properties: name, type, flags
      44, QMetaType::QRect, 0x00015103, uint(-1), 0,
      45, QMetaType::QPixmap, 0x00015103, uint(-1), 0,
      46, QMetaType::Bool, 0x00015103, uint(-1), 0,
      47, 0x80000000 | 48, 0x0001510b, uint(-1), 0,
      49, 0x80000000 | 50, 0x00015009, uint(-1), 0,
      51, QMetaType::Bool, 0x00015103, uint(-1), 0,
      52, QMetaType::Int, 0x00015103, uint(-1), 0,
      53, QMetaType::Bool, 0x00015103, uint(-1), 0,
      54, 0x80000000 | 55, 0x0001510b, uint(-1), 0,
      56, QMetaType::Bool, 0x00015103, uint(-1), 0,

 // enums: name, alias, flags, count, data
      57,   57, 0x0,    2,  317,
      60,   60, 0x0,    4,  321,

 // enum data: key, value
      58, uint(QCustomPlot::limBelow),
      59, uint(QCustomPlot::limAbove),
      61, uint(QCustomPlot::rpImmediateRefresh),
      62, uint(QCustomPlot::rpQueuedRefresh),
      63, uint(QCustomPlot::rpRefreshHint),
      64, uint(QCustomPlot::rpQueuedReplot),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCustomPlot::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_QCustomPlot.offsetsAndSizes,
    qt_meta_data_QCustomPlot,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCustomPlot_t,
        // property 'viewport'
        QtPrivate::TypeAndForceComplete<QRect, std::true_type>,
        // property 'background'
        QtPrivate::TypeAndForceComplete<QPixmap, std::true_type>,
        // property 'backgroundScaled'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'backgroundScaledMode'
        QtPrivate::TypeAndForceComplete<Qt::AspectRatioMode, std::true_type>,
        // property 'plotLayout'
        QtPrivate::TypeAndForceComplete<QCPLayoutGrid*, std::true_type>,
        // property 'autoAddPlottableToLegend'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'selectionTolerance'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'noAntialiasingOnDrag'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'multiSelectModifier'
        QtPrivate::TypeAndForceComplete<Qt::KeyboardModifier, std::true_type>,
        // property 'openGl'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCustomPlot, std::true_type>,
        // method 'mouseDoubleClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'mousePress'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'mouseMove'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'mouseRelease'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'mouseWheel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QWheelEvent *, std::false_type>,
        // method 'plottableClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAbstractPlottable *, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'plottableDoubleClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAbstractPlottable *, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'itemClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAbstractItem *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'itemDoubleClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAbstractItem *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'axisClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAxis *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAxis::SelectablePart, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'axisDoubleClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAxis *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAxis::SelectablePart, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'legendClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPLegend *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAbstractLegendItem *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'legendDoubleClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPLegend *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAbstractLegendItem *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'selectionChangedByUser'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'beforeReplot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'afterLayout'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'afterReplot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'rescaleAxes'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'rescaleAxes'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deselectAll'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'replot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCustomPlot::RefreshPriority, std::false_type>,
        // method 'replot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'processRectSelection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QRect, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'processRectZoom'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QRect, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'processPointSelection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>
    >,
    nullptr
} };

void QCustomPlot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCustomPlot *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->mouseDoubleClick((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 1: _t->mousePress((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 2: _t->mouseMove((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 3: _t->mouseRelease((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 4: _t->mouseWheel((*reinterpret_cast< std::add_pointer_t<QWheelEvent*>>(_a[1]))); break;
        case 5: _t->plottableClick((*reinterpret_cast< std::add_pointer_t<QCPAbstractPlottable*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[3]))); break;
        case 6: _t->plottableDoubleClick((*reinterpret_cast< std::add_pointer_t<QCPAbstractPlottable*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[3]))); break;
        case 7: _t->itemClick((*reinterpret_cast< std::add_pointer_t<QCPAbstractItem*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[2]))); break;
        case 8: _t->itemDoubleClick((*reinterpret_cast< std::add_pointer_t<QCPAbstractItem*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[2]))); break;
        case 9: _t->axisClick((*reinterpret_cast< std::add_pointer_t<QCPAxis*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QCPAxis::SelectablePart>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[3]))); break;
        case 10: _t->axisDoubleClick((*reinterpret_cast< std::add_pointer_t<QCPAxis*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QCPAxis::SelectablePart>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[3]))); break;
        case 11: _t->legendClick((*reinterpret_cast< std::add_pointer_t<QCPLegend*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QCPAbstractLegendItem*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[3]))); break;
        case 12: _t->legendDoubleClick((*reinterpret_cast< std::add_pointer_t<QCPLegend*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QCPAbstractLegendItem*>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[3]))); break;
        case 13: _t->selectionChangedByUser(); break;
        case 14: _t->beforeReplot(); break;
        case 15: _t->afterLayout(); break;
        case 16: _t->afterReplot(); break;
        case 17: _t->rescaleAxes((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 18: _t->rescaleAxes(); break;
        case 19: _t->deselectAll(); break;
        case 20: _t->replot((*reinterpret_cast< std::add_pointer_t<QCustomPlot::RefreshPriority>>(_a[1]))); break;
        case 21: _t->replot(); break;
        case 22: _t->processRectSelection((*reinterpret_cast< std::add_pointer_t<QRect>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[2]))); break;
        case 23: _t->processRectZoom((*reinterpret_cast< std::add_pointer_t<QRect>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[2]))); break;
        case 24: _t->processPointSelection((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAbstractPlottable* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAbstractPlottable* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAbstractItem* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAbstractItem* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAxis* >(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAxis::SelectablePart >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAxis* >(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAxis::SelectablePart >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAbstractLegendItem* >(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPLegend* >(); break;
            }
            break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAbstractLegendItem* >(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPLegend* >(); break;
            }
            break;
        case 20:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCustomPlot::RefreshPriority >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QCustomPlot::*)(QMouseEvent * );
            if (_t _q_method = &QCustomPlot::mouseDoubleClick; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QCustomPlot::*)(QMouseEvent * );
            if (_t _q_method = &QCustomPlot::mousePress; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QCustomPlot::*)(QMouseEvent * );
            if (_t _q_method = &QCustomPlot::mouseMove; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (QCustomPlot::*)(QMouseEvent * );
            if (_t _q_method = &QCustomPlot::mouseRelease; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (QCustomPlot::*)(QWheelEvent * );
            if (_t _q_method = &QCustomPlot::mouseWheel; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (QCustomPlot::*)(QCPAbstractPlottable * , int , QMouseEvent * );
            if (_t _q_method = &QCustomPlot::plottableClick; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (QCustomPlot::*)(QCPAbstractPlottable * , int , QMouseEvent * );
            if (_t _q_method = &QCustomPlot::plottableDoubleClick; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (QCustomPlot::*)(QCPAbstractItem * , QMouseEvent * );
            if (_t _q_method = &QCustomPlot::itemClick; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (QCustomPlot::*)(QCPAbstractItem * , QMouseEvent * );
            if (_t _q_method = &QCustomPlot::itemDoubleClick; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (QCustomPlot::*)(QCPAxis * , QCPAxis::SelectablePart , QMouseEvent * );
            if (_t _q_method = &QCustomPlot::axisClick; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (QCustomPlot::*)(QCPAxis * , QCPAxis::SelectablePart , QMouseEvent * );
            if (_t _q_method = &QCustomPlot::axisDoubleClick; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (QCustomPlot::*)(QCPLegend * , QCPAbstractLegendItem * , QMouseEvent * );
            if (_t _q_method = &QCustomPlot::legendClick; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (QCustomPlot::*)(QCPLegend * , QCPAbstractLegendItem * , QMouseEvent * );
            if (_t _q_method = &QCustomPlot::legendDoubleClick; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (QCustomPlot::*)();
            if (_t _q_method = &QCustomPlot::selectionChangedByUser; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (QCustomPlot::*)();
            if (_t _q_method = &QCustomPlot::beforeReplot; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (QCustomPlot::*)();
            if (_t _q_method = &QCustomPlot::afterLayout; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (QCustomPlot::*)();
            if (_t _q_method = &QCustomPlot::afterReplot; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 16;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPLayoutGrid* >(); break;
        }
    }
else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCustomPlot *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QRect*>(_v) = _t->viewport(); break;
        case 1: *reinterpret_cast< QPixmap*>(_v) = _t->background(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->backgroundScaled(); break;
        case 3: *reinterpret_cast< Qt::AspectRatioMode*>(_v) = _t->backgroundScaledMode(); break;
        case 4: *reinterpret_cast< QCPLayoutGrid**>(_v) = _t->plotLayout(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->autoAddPlottableToLegend(); break;
        case 6: *reinterpret_cast< int*>(_v) = _t->selectionTolerance(); break;
        case 7: *reinterpret_cast< bool*>(_v) = _t->noAntialiasingOnDrag(); break;
        case 8: *reinterpret_cast< Qt::KeyboardModifier*>(_v) = _t->multiSelectModifier(); break;
        case 9: *reinterpret_cast< bool*>(_v) = _t->openGl(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCustomPlot *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setViewport(*reinterpret_cast< QRect*>(_v)); break;
        case 1: _t->setBackground(*reinterpret_cast< QPixmap*>(_v)); break;
        case 2: _t->setBackgroundScaled(*reinterpret_cast< bool*>(_v)); break;
        case 3: _t->setBackgroundScaledMode(*reinterpret_cast< Qt::AspectRatioMode*>(_v)); break;
        case 5: _t->setAutoAddPlottableToLegend(*reinterpret_cast< bool*>(_v)); break;
        case 6: _t->setSelectionTolerance(*reinterpret_cast< int*>(_v)); break;
        case 7: _t->setNoAntialiasingOnDrag(*reinterpret_cast< bool*>(_v)); break;
        case 8: _t->setMultiSelectModifier(*reinterpret_cast< Qt::KeyboardModifier*>(_v)); break;
        case 9: _t->setOpenGl(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *QCustomPlot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCustomPlot::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCustomPlot.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int QCustomPlot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void QCustomPlot::mouseDoubleClick(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCustomPlot::mousePress(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QCustomPlot::mouseMove(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QCustomPlot::mouseRelease(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QCustomPlot::mouseWheel(QWheelEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QCustomPlot::plottableClick(QCPAbstractPlottable * _t1, int _t2, QMouseEvent * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QCustomPlot::plottableDoubleClick(QCPAbstractPlottable * _t1, int _t2, QMouseEvent * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void QCustomPlot::itemClick(QCPAbstractItem * _t1, QMouseEvent * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void QCustomPlot::itemDoubleClick(QCPAbstractItem * _t1, QMouseEvent * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void QCustomPlot::axisClick(QCPAxis * _t1, QCPAxis::SelectablePart _t2, QMouseEvent * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void QCustomPlot::axisDoubleClick(QCPAxis * _t1, QCPAxis::SelectablePart _t2, QMouseEvent * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void QCustomPlot::legendClick(QCPLegend * _t1, QCPAbstractLegendItem * _t2, QMouseEvent * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void QCustomPlot::legendDoubleClick(QCPLegend * _t1, QCPAbstractLegendItem * _t2, QMouseEvent * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void QCustomPlot::selectionChangedByUser()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void QCustomPlot::beforeReplot()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}

// SIGNAL 15
void QCustomPlot::afterLayout()
{
    QMetaObject::activate(this, &staticMetaObject, 15, nullptr);
}

// SIGNAL 16
void QCustomPlot::afterReplot()
{
    QMetaObject::activate(this, &staticMetaObject, 16, nullptr);
}
namespace {
struct qt_meta_stringdata_QCPColorGradient_t {
    uint offsetsAndSizes[46];
    char stringdata0[17];
    char stringdata1[19];
    char stringdata2[6];
    char stringdata3[6];
    char stringdata4[12];
    char stringdata5[7];
    char stringdata6[14];
    char stringdata7[15];
    char stringdata8[14];
    char stringdata9[11];
    char stringdata10[15];
    char stringdata11[12];
    char stringdata12[6];
    char stringdata13[7];
    char stringdata14[8];
    char stringdata15[8];
    char stringdata16[12];
    char stringdata17[6];
    char stringdata18[10];
    char stringdata19[8];
    char stringdata20[11];
    char stringdata21[6];
    char stringdata22[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPColorGradient_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPColorGradient_t qt_meta_stringdata_QCPColorGradient = {
    {
        QT_MOC_LITERAL(0, 16),  // "QCPColorGradient"
        QT_MOC_LITERAL(17, 18),  // "ColorInterpolation"
        QT_MOC_LITERAL(36, 5),  // "ciRGB"
        QT_MOC_LITERAL(42, 5),  // "ciHSV"
        QT_MOC_LITERAL(48, 11),  // "NanHandling"
        QT_MOC_LITERAL(60, 6),  // "nhNone"
        QT_MOC_LITERAL(67, 13),  // "nhLowestColor"
        QT_MOC_LITERAL(81, 14),  // "nhHighestColor"
        QT_MOC_LITERAL(96, 13),  // "nhTransparent"
        QT_MOC_LITERAL(110, 10),  // "nhNanColor"
        QT_MOC_LITERAL(121, 14),  // "GradientPreset"
        QT_MOC_LITERAL(136, 11),  // "gpGrayscale"
        QT_MOC_LITERAL(148, 5),  // "gpHot"
        QT_MOC_LITERAL(154, 6),  // "gpCold"
        QT_MOC_LITERAL(161, 7),  // "gpNight"
        QT_MOC_LITERAL(169, 7),  // "gpCandy"
        QT_MOC_LITERAL(177, 11),  // "gpGeography"
        QT_MOC_LITERAL(189, 5),  // "gpIon"
        QT_MOC_LITERAL(195, 9),  // "gpThermal"
        QT_MOC_LITERAL(205, 7),  // "gpPolar"
        QT_MOC_LITERAL(213, 10),  // "gpSpectrum"
        QT_MOC_LITERAL(224, 5),  // "gpJet"
        QT_MOC_LITERAL(230, 6)   // "gpHues"
    },
    "QCPColorGradient",
    "ColorInterpolation",
    "ciRGB",
    "ciHSV",
    "NanHandling",
    "nhNone",
    "nhLowestColor",
    "nhHighestColor",
    "nhTransparent",
    "nhNanColor",
    "GradientPreset",
    "gpGrayscale",
    "gpHot",
    "gpCold",
    "gpNight",
    "gpCandy",
    "gpGeography",
    "gpIon",
    "gpThermal",
    "gpPolar",
    "gpSpectrum",
    "gpJet",
    "gpHues"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPColorGradient[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       3,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    2,   29,
       4,    4, 0x0,    5,   33,
      10,   10, 0x0,   12,   43,

 // enum data: key, value
       2, uint(QCPColorGradient::ciRGB),
       3, uint(QCPColorGradient::ciHSV),
       5, uint(QCPColorGradient::nhNone),
       6, uint(QCPColorGradient::nhLowestColor),
       7, uint(QCPColorGradient::nhHighestColor),
       8, uint(QCPColorGradient::nhTransparent),
       9, uint(QCPColorGradient::nhNanColor),
      11, uint(QCPColorGradient::gpGrayscale),
      12, uint(QCPColorGradient::gpHot),
      13, uint(QCPColorGradient::gpCold),
      14, uint(QCPColorGradient::gpNight),
      15, uint(QCPColorGradient::gpCandy),
      16, uint(QCPColorGradient::gpGeography),
      17, uint(QCPColorGradient::gpIon),
      18, uint(QCPColorGradient::gpThermal),
      19, uint(QCPColorGradient::gpPolar),
      20, uint(QCPColorGradient::gpSpectrum),
      21, uint(QCPColorGradient::gpJet),
      22, uint(QCPColorGradient::gpHues),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPColorGradient::staticMetaObject = { {
    nullptr,
    qt_meta_stringdata_QCPColorGradient.offsetsAndSizes,
    qt_meta_data_QCPColorGradient,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPColorGradient_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPColorGradient, std::true_type>
    >,
    nullptr
} };

namespace {
struct qt_meta_stringdata_QCPSelectionDecoratorBracket_t {
    uint offsetsAndSizes[14];
    char stringdata0[29];
    char stringdata1[13];
    char stringdata2[16];
    char stringdata3[14];
    char stringdata4[10];
    char stringdata5[7];
    char stringdata6[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPSelectionDecoratorBracket_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPSelectionDecoratorBracket_t qt_meta_stringdata_QCPSelectionDecoratorBracket = {
    {
        QT_MOC_LITERAL(0, 28),  // "QCPSelectionDecoratorBracket"
        QT_MOC_LITERAL(29, 12),  // "BracketStyle"
        QT_MOC_LITERAL(42, 15),  // "bsSquareBracket"
        QT_MOC_LITERAL(58, 13),  // "bsHalfEllipse"
        QT_MOC_LITERAL(72, 9),  // "bsEllipse"
        QT_MOC_LITERAL(82, 6),  // "bsPlus"
        QT_MOC_LITERAL(89, 11)   // "bsUserStyle"
    },
    "QCPSelectionDecoratorBracket",
    "BracketStyle",
    "bsSquareBracket",
    "bsHalfEllipse",
    "bsEllipse",
    "bsPlus",
    "bsUserStyle"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPSelectionDecoratorBracket[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    5,   19,

 // enum data: key, value
       2, uint(QCPSelectionDecoratorBracket::bsSquareBracket),
       3, uint(QCPSelectionDecoratorBracket::bsHalfEllipse),
       4, uint(QCPSelectionDecoratorBracket::bsEllipse),
       5, uint(QCPSelectionDecoratorBracket::bsPlus),
       6, uint(QCPSelectionDecoratorBracket::bsUserStyle),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPSelectionDecoratorBracket::staticMetaObject = { {
    QtPrivate::MetaObjectForType<QCPSelectionDecorator>::value,
    qt_meta_stringdata_QCPSelectionDecoratorBracket.offsetsAndSizes,
    qt_meta_data_QCPSelectionDecoratorBracket,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPSelectionDecoratorBracket_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPSelectionDecoratorBracket, std::true_type>
    >,
    nullptr
} };

namespace {
struct qt_meta_stringdata_QCPAxisRect_t {
    uint offsetsAndSizes[16];
    char stringdata0[12];
    char stringdata1[11];
    char stringdata2[17];
    char stringdata3[21];
    char stringdata4[20];
    char stringdata5[10];
    char stringdata6[17];
    char stringdata7[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPAxisRect_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPAxisRect_t qt_meta_stringdata_QCPAxisRect = {
    {
        QT_MOC_LITERAL(0, 11),  // "QCPAxisRect"
        QT_MOC_LITERAL(12, 10),  // "background"
        QT_MOC_LITERAL(23, 16),  // "backgroundScaled"
        QT_MOC_LITERAL(40, 20),  // "backgroundScaledMode"
        QT_MOC_LITERAL(61, 19),  // "Qt::AspectRatioMode"
        QT_MOC_LITERAL(81, 9),  // "rangeDrag"
        QT_MOC_LITERAL(91, 16),  // "Qt::Orientations"
        QT_MOC_LITERAL(108, 9)   // "rangeZoom"
    },
    "QCPAxisRect",
    "background",
    "backgroundScaled",
    "backgroundScaledMode",
    "Qt::AspectRatioMode",
    "rangeDrag",
    "Qt::Orientations",
    "rangeZoom"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPAxisRect[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       5,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QPixmap, 0x00015103, uint(-1), 0,
       2, QMetaType::Bool, 0x00015103, uint(-1), 0,
       3, 0x80000000 | 4, 0x0001510b, uint(-1), 0,
       5, 0x80000000 | 6, 0x0001510b, uint(-1), 0,
       7, 0x80000000 | 6, 0x0001510b, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPAxisRect::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayoutElement::staticMetaObject>(),
    qt_meta_stringdata_QCPAxisRect.offsetsAndSizes,
    qt_meta_data_QCPAxisRect,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPAxisRect_t,
        // property 'background'
        QtPrivate::TypeAndForceComplete<QPixmap, std::true_type>,
        // property 'backgroundScaled'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'backgroundScaledMode'
        QtPrivate::TypeAndForceComplete<Qt::AspectRatioMode, std::true_type>,
        // property 'rangeDrag'
        QtPrivate::TypeAndForceComplete<Qt::Orientations, std::true_type>,
        // property 'rangeZoom'
        QtPrivate::TypeAndForceComplete<Qt::Orientations, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPAxisRect, std::true_type>
    >,
    nullptr
} };

void QCPAxisRect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPAxisRect *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QPixmap*>(_v) = _t->background(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->backgroundScaled(); break;
        case 2: *reinterpret_cast< Qt::AspectRatioMode*>(_v) = _t->backgroundScaledMode(); break;
        case 3: *reinterpret_cast< Qt::Orientations*>(_v) = _t->rangeDrag(); break;
        case 4: *reinterpret_cast< Qt::Orientations*>(_v) = _t->rangeZoom(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPAxisRect *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setBackground(*reinterpret_cast< QPixmap*>(_v)); break;
        case 1: _t->setBackgroundScaled(*reinterpret_cast< bool*>(_v)); break;
        case 2: _t->setBackgroundScaledMode(*reinterpret_cast< Qt::AspectRatioMode*>(_v)); break;
        case 3: _t->setRangeDrag(*reinterpret_cast< Qt::Orientations*>(_v)); break;
        case 4: _t->setRangeZoom(*reinterpret_cast< Qt::Orientations*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *QCPAxisRect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPAxisRect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPAxisRect.stringdata0))
        return static_cast<void*>(this);
    return QCPLayoutElement::qt_metacast(_clname);
}

int QCPAxisRect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayoutElement::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
namespace {
struct qt_meta_stringdata_QCPAbstractLegendItem_t {
    uint offsetsAndSizes[28];
    char stringdata0[22];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[18];
    char stringdata5[11];
    char stringdata6[14];
    char stringdata7[12];
    char stringdata8[13];
    char stringdata9[11];
    char stringdata10[5];
    char stringdata11[10];
    char stringdata12[13];
    char stringdata13[18];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPAbstractLegendItem_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPAbstractLegendItem_t qt_meta_stringdata_QCPAbstractLegendItem = {
    {
        QT_MOC_LITERAL(0, 21),  // "QCPAbstractLegendItem"
        QT_MOC_LITERAL(22, 16),  // "selectionChanged"
        QT_MOC_LITERAL(39, 0),  // ""
        QT_MOC_LITERAL(40, 8),  // "selected"
        QT_MOC_LITERAL(49, 17),  // "selectableChanged"
        QT_MOC_LITERAL(67, 10),  // "selectable"
        QT_MOC_LITERAL(78, 13),  // "setSelectable"
        QT_MOC_LITERAL(92, 11),  // "setSelected"
        QT_MOC_LITERAL(104, 12),  // "parentLegend"
        QT_MOC_LITERAL(117, 10),  // "QCPLegend*"
        QT_MOC_LITERAL(128, 4),  // "font"
        QT_MOC_LITERAL(133, 9),  // "textColor"
        QT_MOC_LITERAL(143, 12),  // "selectedFont"
        QT_MOC_LITERAL(156, 17)   // "selectedTextColor"
    },
    "QCPAbstractLegendItem",
    "selectionChanged",
    "",
    "selected",
    "selectableChanged",
    "selectable",
    "setSelectable",
    "setSelected",
    "parentLegend",
    "QCPLegend*",
    "font",
    "textColor",
    "selectedFont",
    "selectedTextColor"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPAbstractLegendItem[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       7,   50, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   38,    2, 0x06,    8 /* Public */,
       4,    1,   41,    2, 0x06,   10 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    1,   44,    2, 0x0a,   12 /* Public */,
       7,    1,   47,    2, 0x0a,   14 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    3,

 // properties: name, type, flags
       8, 0x80000000 | 9, 0x00015009, uint(-1), 0,
      10, QMetaType::QFont, 0x00015103, uint(-1), 0,
      11, QMetaType::QColor, 0x00015103, uint(-1), 0,
      12, QMetaType::QFont, 0x00015103, uint(-1), 0,
      13, QMetaType::QColor, 0x00015103, uint(-1), 0,
       5, QMetaType::Bool, 0x00015103, uint(0), 0,
       3, QMetaType::Bool, 0x00015103, uint(1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPAbstractLegendItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayoutElement::staticMetaObject>(),
    qt_meta_stringdata_QCPAbstractLegendItem.offsetsAndSizes,
    qt_meta_data_QCPAbstractLegendItem,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPAbstractLegendItem_t,
        // property 'parentLegend'
        QtPrivate::TypeAndForceComplete<QCPLegend*, std::true_type>,
        // property 'font'
        QtPrivate::TypeAndForceComplete<QFont, std::true_type>,
        // property 'textColor'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'selectedFont'
        QtPrivate::TypeAndForceComplete<QFont, std::true_type>,
        // property 'selectedTextColor'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'selectable'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'selected'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPAbstractLegendItem, std::true_type>,
        // method 'selectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'selectableChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setSelectable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void QCPAbstractLegendItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCPAbstractLegendItem *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->selectionChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->selectableChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->setSelectable((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 3: _t->setSelected((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QCPAbstractLegendItem::*)(bool );
            if (_t _q_method = &QCPAbstractLegendItem::selectionChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QCPAbstractLegendItem::*)(bool );
            if (_t _q_method = &QCPAbstractLegendItem::selectableChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPLegend* >(); break;
        }
    }
else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPAbstractLegendItem *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QCPLegend**>(_v) = _t->parentLegend(); break;
        case 1: *reinterpret_cast< QFont*>(_v) = _t->font(); break;
        case 2: *reinterpret_cast< QColor*>(_v) = _t->textColor(); break;
        case 3: *reinterpret_cast< QFont*>(_v) = _t->selectedFont(); break;
        case 4: *reinterpret_cast< QColor*>(_v) = _t->selectedTextColor(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->selectable(); break;
        case 6: *reinterpret_cast< bool*>(_v) = _t->selected(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPAbstractLegendItem *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 1: _t->setFont(*reinterpret_cast< QFont*>(_v)); break;
        case 2: _t->setTextColor(*reinterpret_cast< QColor*>(_v)); break;
        case 3: _t->setSelectedFont(*reinterpret_cast< QFont*>(_v)); break;
        case 4: _t->setSelectedTextColor(*reinterpret_cast< QColor*>(_v)); break;
        case 5: _t->setSelectable(*reinterpret_cast< bool*>(_v)); break;
        case 6: _t->setSelected(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *QCPAbstractLegendItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPAbstractLegendItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPAbstractLegendItem.stringdata0))
        return static_cast<void*>(this);
    return QCPLayoutElement::qt_metacast(_clname);
}

int QCPAbstractLegendItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayoutElement::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void QCPAbstractLegendItem::selectionChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCPAbstractLegendItem::selectableChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
namespace {
struct qt_meta_stringdata_QCPPlottableLegendItem_t {
    uint offsetsAndSizes[2];
    char stringdata0[23];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPPlottableLegendItem_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPPlottableLegendItem_t qt_meta_stringdata_QCPPlottableLegendItem = {
    {
        QT_MOC_LITERAL(0, 22)   // "QCPPlottableLegendItem"
    },
    "QCPPlottableLegendItem"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPPlottableLegendItem[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPPlottableLegendItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractLegendItem::staticMetaObject>(),
    qt_meta_stringdata_QCPPlottableLegendItem.offsetsAndSizes,
    qt_meta_data_QCPPlottableLegendItem,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPPlottableLegendItem_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPPlottableLegendItem, std::true_type>
    >,
    nullptr
} };

void QCPPlottableLegendItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *QCPPlottableLegendItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPPlottableLegendItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPPlottableLegendItem.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractLegendItem::qt_metacast(_clname);
}

int QCPPlottableLegendItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractLegendItem::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_stringdata_QCPLegend_t {
    uint offsetsAndSizes[54];
    char stringdata0[10];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[27];
    char stringdata4[6];
    char stringdata5[18];
    char stringdata6[19];
    char stringdata7[16];
    char stringdata8[16];
    char stringdata9[17];
    char stringdata10[14];
    char stringdata11[10];
    char stringdata12[6];
    char stringdata13[5];
    char stringdata14[10];
    char stringdata15[9];
    char stringdata16[16];
    char stringdata17[14];
    char stringdata18[18];
    char stringdata19[22];
    char stringdata20[14];
    char stringdata21[13];
    char stringdata22[18];
    char stringdata23[15];
    char stringdata24[7];
    char stringdata25[12];
    char stringdata26[8];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPLegend_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPLegend_t qt_meta_stringdata_QCPLegend = {
    {
        QT_MOC_LITERAL(0, 9),  // "QCPLegend"
        QT_MOC_LITERAL(10, 16),  // "selectionChanged"
        QT_MOC_LITERAL(27, 0),  // ""
        QT_MOC_LITERAL(28, 26),  // "QCPLegend::SelectableParts"
        QT_MOC_LITERAL(55, 5),  // "parts"
        QT_MOC_LITERAL(61, 17),  // "selectableChanged"
        QT_MOC_LITERAL(79, 18),  // "setSelectableParts"
        QT_MOC_LITERAL(98, 15),  // "SelectableParts"
        QT_MOC_LITERAL(114, 15),  // "selectableParts"
        QT_MOC_LITERAL(130, 16),  // "setSelectedParts"
        QT_MOC_LITERAL(147, 13),  // "selectedParts"
        QT_MOC_LITERAL(161, 9),  // "borderPen"
        QT_MOC_LITERAL(171, 5),  // "brush"
        QT_MOC_LITERAL(177, 4),  // "font"
        QT_MOC_LITERAL(182, 9),  // "textColor"
        QT_MOC_LITERAL(192, 8),  // "iconSize"
        QT_MOC_LITERAL(201, 15),  // "iconTextPadding"
        QT_MOC_LITERAL(217, 13),  // "iconBorderPen"
        QT_MOC_LITERAL(231, 17),  // "selectedBorderPen"
        QT_MOC_LITERAL(249, 21),  // "selectedIconBorderPen"
        QT_MOC_LITERAL(271, 13),  // "selectedBrush"
        QT_MOC_LITERAL(285, 12),  // "selectedFont"
        QT_MOC_LITERAL(298, 17),  // "selectedTextColor"
        QT_MOC_LITERAL(316, 14),  // "SelectablePart"
        QT_MOC_LITERAL(331, 6),  // "spNone"
        QT_MOC_LITERAL(338, 11),  // "spLegendBox"
        QT_MOC_LITERAL(350, 7)   // "spItems"
    },
    "QCPLegend",
    "selectionChanged",
    "",
    "QCPLegend::SelectableParts",
    "parts",
    "selectableChanged",
    "setSelectableParts",
    "SelectableParts",
    "selectableParts",
    "setSelectedParts",
    "selectedParts",
    "borderPen",
    "brush",
    "font",
    "textColor",
    "iconSize",
    "iconTextPadding",
    "iconBorderPen",
    "selectedBorderPen",
    "selectedIconBorderPen",
    "selectedBrush",
    "selectedFont",
    "selectedTextColor",
    "SelectablePart",
    "spNone",
    "spLegendBox",
    "spItems"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPLegend[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
      14,   50, // properties
       2,  120, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   38,    2, 0x06,   15 /* Public */,
       5,    1,   41,    2, 0x06,   17 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    1,   44,    2, 0x0a,   19 /* Public */,
       9,    1,   47,    2, 0x0a,   21 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,   10,

 // properties: name, type, flags
      11, QMetaType::QPen, 0x00015103, uint(-1), 0,
      12, QMetaType::QBrush, 0x00015103, uint(-1), 0,
      13, QMetaType::QFont, 0x00015103, uint(-1), 0,
      14, QMetaType::QColor, 0x00015103, uint(-1), 0,
      15, QMetaType::QSize, 0x00015103, uint(-1), 0,
      16, QMetaType::Int, 0x00015103, uint(-1), 0,
      17, QMetaType::QPen, 0x00015103, uint(-1), 0,
       8, 0x80000000 | 7, 0x0001510b, uint(0), 0,
      10, 0x80000000 | 7, 0x0001510b, uint(1), 0,
      18, QMetaType::QPen, 0x00015103, uint(-1), 0,
      19, QMetaType::QPen, 0x00015103, uint(-1), 0,
      20, QMetaType::QBrush, 0x00015103, uint(-1), 0,
      21, QMetaType::QFont, 0x00015103, uint(-1), 0,
      22, QMetaType::QColor, 0x00015103, uint(-1), 0,

 // enums: name, alias, flags, count, data
      23,   23, 0x0,    3,  130,
       7,   23, 0x1,    3,  136,

 // enum data: key, value
      24, uint(QCPLegend::spNone),
      25, uint(QCPLegend::spLegendBox),
      26, uint(QCPLegend::spItems),
      24, uint(QCPLegend::spNone),
      25, uint(QCPLegend::spLegendBox),
      26, uint(QCPLegend::spItems),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPLegend::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayoutGrid::staticMetaObject>(),
    qt_meta_stringdata_QCPLegend.offsetsAndSizes,
    qt_meta_data_QCPLegend,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPLegend_t,
        // property 'borderPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'brush'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // property 'font'
        QtPrivate::TypeAndForceComplete<QFont, std::true_type>,
        // property 'textColor'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'iconSize'
        QtPrivate::TypeAndForceComplete<QSize, std::true_type>,
        // property 'iconTextPadding'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'iconBorderPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'selectableParts'
        QtPrivate::TypeAndForceComplete<SelectableParts, std::true_type>,
        // property 'selectedParts'
        QtPrivate::TypeAndForceComplete<SelectableParts, std::true_type>,
        // property 'selectedBorderPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'selectedIconBorderPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'selectedBrush'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // property 'selectedFont'
        QtPrivate::TypeAndForceComplete<QFont, std::true_type>,
        // property 'selectedTextColor'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPLegend, std::true_type>,
        // method 'selectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPLegend::SelectableParts, std::false_type>,
        // method 'selectableChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPLegend::SelectableParts, std::false_type>,
        // method 'setSelectableParts'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const SelectableParts &, std::false_type>,
        // method 'setSelectedParts'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const SelectableParts &, std::false_type>
    >,
    nullptr
} };

void QCPLegend::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCPLegend *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->selectionChanged((*reinterpret_cast< std::add_pointer_t<QCPLegend::SelectableParts>>(_a[1]))); break;
        case 1: _t->selectableChanged((*reinterpret_cast< std::add_pointer_t<QCPLegend::SelectableParts>>(_a[1]))); break;
        case 2: _t->setSelectableParts((*reinterpret_cast< std::add_pointer_t<SelectableParts>>(_a[1]))); break;
        case 3: _t->setSelectedParts((*reinterpret_cast< std::add_pointer_t<SelectableParts>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QCPLegend::*)(QCPLegend::SelectableParts );
            if (_t _q_method = &QCPLegend::selectionChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QCPLegend::*)(QCPLegend::SelectableParts );
            if (_t _q_method = &QCPLegend::selectableChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPLegend *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QPen*>(_v) = _t->borderPen(); break;
        case 1: *reinterpret_cast< QBrush*>(_v) = _t->brush(); break;
        case 2: *reinterpret_cast< QFont*>(_v) = _t->font(); break;
        case 3: *reinterpret_cast< QColor*>(_v) = _t->textColor(); break;
        case 4: *reinterpret_cast< QSize*>(_v) = _t->iconSize(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->iconTextPadding(); break;
        case 6: *reinterpret_cast< QPen*>(_v) = _t->iconBorderPen(); break;
        case 7: *reinterpret_cast<int*>(_v) = QFlag(_t->selectableParts()); break;
        case 8: *reinterpret_cast<int*>(_v) = QFlag(_t->selectedParts()); break;
        case 9: *reinterpret_cast< QPen*>(_v) = _t->selectedBorderPen(); break;
        case 10: *reinterpret_cast< QPen*>(_v) = _t->selectedIconBorderPen(); break;
        case 11: *reinterpret_cast< QBrush*>(_v) = _t->selectedBrush(); break;
        case 12: *reinterpret_cast< QFont*>(_v) = _t->selectedFont(); break;
        case 13: *reinterpret_cast< QColor*>(_v) = _t->selectedTextColor(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPLegend *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setBorderPen(*reinterpret_cast< QPen*>(_v)); break;
        case 1: _t->setBrush(*reinterpret_cast< QBrush*>(_v)); break;
        case 2: _t->setFont(*reinterpret_cast< QFont*>(_v)); break;
        case 3: _t->setTextColor(*reinterpret_cast< QColor*>(_v)); break;
        case 4: _t->setIconSize(*reinterpret_cast< QSize*>(_v)); break;
        case 5: _t->setIconTextPadding(*reinterpret_cast< int*>(_v)); break;
        case 6: _t->setIconBorderPen(*reinterpret_cast< QPen*>(_v)); break;
        case 7: _t->setSelectableParts(QFlag(*reinterpret_cast<int*>(_v))); break;
        case 8: _t->setSelectedParts(QFlag(*reinterpret_cast<int*>(_v))); break;
        case 9: _t->setSelectedBorderPen(*reinterpret_cast< QPen*>(_v)); break;
        case 10: _t->setSelectedIconBorderPen(*reinterpret_cast< QPen*>(_v)); break;
        case 11: _t->setSelectedBrush(*reinterpret_cast< QBrush*>(_v)); break;
        case 12: _t->setSelectedFont(*reinterpret_cast< QFont*>(_v)); break;
        case 13: _t->setSelectedTextColor(*reinterpret_cast< QColor*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *QCPLegend::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPLegend::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPLegend.stringdata0))
        return static_cast<void*>(this);
    return QCPLayoutGrid::qt_metacast(_clname);
}

int QCPLegend::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayoutGrid::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void QCPLegend::selectionChanged(QCPLegend::SelectableParts _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCPLegend::selectableChanged(QCPLegend::SelectableParts _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
namespace {
struct qt_meta_stringdata_QCPTextElement_t {
    uint offsetsAndSizes[34];
    char stringdata0[15];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[18];
    char stringdata5[11];
    char stringdata6[8];
    char stringdata7[13];
    char stringdata8[6];
    char stringdata9[14];
    char stringdata10[14];
    char stringdata11[12];
    char stringdata12[5];
    char stringdata13[5];
    char stringdata14[10];
    char stringdata15[13];
    char stringdata16[18];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPTextElement_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPTextElement_t qt_meta_stringdata_QCPTextElement = {
    {
        QT_MOC_LITERAL(0, 14),  // "QCPTextElement"
        QT_MOC_LITERAL(15, 16),  // "selectionChanged"
        QT_MOC_LITERAL(32, 0),  // ""
        QT_MOC_LITERAL(33, 8),  // "selected"
        QT_MOC_LITERAL(42, 17),  // "selectableChanged"
        QT_MOC_LITERAL(60, 10),  // "selectable"
        QT_MOC_LITERAL(71, 7),  // "clicked"
        QT_MOC_LITERAL(79, 12),  // "QMouseEvent*"
        QT_MOC_LITERAL(92, 5),  // "event"
        QT_MOC_LITERAL(98, 13),  // "doubleClicked"
        QT_MOC_LITERAL(112, 13),  // "setSelectable"
        QT_MOC_LITERAL(126, 11),  // "setSelected"
        QT_MOC_LITERAL(138, 4),  // "text"
        QT_MOC_LITERAL(143, 4),  // "font"
        QT_MOC_LITERAL(148, 9),  // "textColor"
        QT_MOC_LITERAL(158, 12),  // "selectedFont"
        QT_MOC_LITERAL(171, 17)   // "selectedTextColor"
    },
    "QCPTextElement",
    "selectionChanged",
    "",
    "selected",
    "selectableChanged",
    "selectable",
    "clicked",
    "QMouseEvent*",
    "event",
    "doubleClicked",
    "setSelectable",
    "setSelected",
    "text",
    "font",
    "textColor",
    "selectedFont",
    "selectedTextColor"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPTextElement[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       7,   68, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   50,    2, 0x06,    8 /* Public */,
       4,    1,   53,    2, 0x06,   10 /* Public */,
       6,    1,   56,    2, 0x06,   12 /* Public */,
       9,    1,   59,    2, 0x06,   14 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      10,    1,   62,    2, 0x0a,   16 /* Public */,
      11,    1,   65,    2, 0x0a,   18 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    3,

 // properties: name, type, flags
      12, QMetaType::QString, 0x00015103, uint(-1), 0,
      13, QMetaType::QFont, 0x00015103, uint(-1), 0,
      14, QMetaType::QColor, 0x00015103, uint(-1), 0,
      15, QMetaType::QFont, 0x00015103, uint(-1), 0,
      16, QMetaType::QColor, 0x00015103, uint(-1), 0,
       5, QMetaType::Bool, 0x00015103, uint(1), 0,
       3, QMetaType::Bool, 0x00015103, uint(0), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPTextElement::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayoutElement::staticMetaObject>(),
    qt_meta_stringdata_QCPTextElement.offsetsAndSizes,
    qt_meta_data_QCPTextElement,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPTextElement_t,
        // property 'text'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'font'
        QtPrivate::TypeAndForceComplete<QFont, std::true_type>,
        // property 'textColor'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'selectedFont'
        QtPrivate::TypeAndForceComplete<QFont, std::true_type>,
        // property 'selectedTextColor'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'selectable'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'selected'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPTextElement, std::true_type>,
        // method 'selectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'selectableChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'doubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'setSelectable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'setSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void QCPTextElement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCPTextElement *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->selectionChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->selectableChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 2: _t->clicked((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 3: _t->doubleClicked((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 4: _t->setSelectable((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 5: _t->setSelected((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QCPTextElement::*)(bool );
            if (_t _q_method = &QCPTextElement::selectionChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QCPTextElement::*)(bool );
            if (_t _q_method = &QCPTextElement::selectableChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QCPTextElement::*)(QMouseEvent * );
            if (_t _q_method = &QCPTextElement::clicked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (QCPTextElement::*)(QMouseEvent * );
            if (_t _q_method = &QCPTextElement::doubleClicked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPTextElement *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->text(); break;
        case 1: *reinterpret_cast< QFont*>(_v) = _t->font(); break;
        case 2: *reinterpret_cast< QColor*>(_v) = _t->textColor(); break;
        case 3: *reinterpret_cast< QFont*>(_v) = _t->selectedFont(); break;
        case 4: *reinterpret_cast< QColor*>(_v) = _t->selectedTextColor(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->selectable(); break;
        case 6: *reinterpret_cast< bool*>(_v) = _t->selected(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPTextElement *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setText(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setFont(*reinterpret_cast< QFont*>(_v)); break;
        case 2: _t->setTextColor(*reinterpret_cast< QColor*>(_v)); break;
        case 3: _t->setSelectedFont(*reinterpret_cast< QFont*>(_v)); break;
        case 4: _t->setSelectedTextColor(*reinterpret_cast< QColor*>(_v)); break;
        case 5: _t->setSelectable(*reinterpret_cast< bool*>(_v)); break;
        case 6: _t->setSelected(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *QCPTextElement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPTextElement::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPTextElement.stringdata0))
        return static_cast<void*>(this);
    return QCPLayoutElement::qt_metacast(_clname);
}

int QCPTextElement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayoutElement::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void QCPTextElement::selectionChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCPTextElement::selectableChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QCPTextElement::clicked(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QCPTextElement::doubleClicked(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
namespace {
struct qt_meta_stringdata_QCPColorScaleAxisRectPrivate_t {
    uint offsetsAndSizes[14];
    char stringdata0[29];
    char stringdata1[21];
    char stringdata2[1];
    char stringdata3[25];
    char stringdata4[14];
    char stringdata5[22];
    char stringdata6[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPColorScaleAxisRectPrivate_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPColorScaleAxisRectPrivate_t qt_meta_stringdata_QCPColorScaleAxisRectPrivate = {
    {
        QT_MOC_LITERAL(0, 28),  // "QCPColorScaleAxisRectPrivate"
        QT_MOC_LITERAL(29, 20),  // "axisSelectionChanged"
        QT_MOC_LITERAL(50, 0),  // ""
        QT_MOC_LITERAL(51, 24),  // "QCPAxis::SelectableParts"
        QT_MOC_LITERAL(76, 13),  // "selectedParts"
        QT_MOC_LITERAL(90, 21),  // "axisSelectableChanged"
        QT_MOC_LITERAL(112, 15)   // "selectableParts"
    },
    "QCPColorScaleAxisRectPrivate",
    "axisSelectionChanged",
    "",
    "QCPAxis::SelectableParts",
    "selectedParts",
    "axisSelectableChanged",
    "selectableParts"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPColorScaleAxisRectPrivate[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   26,    2, 0x09,    1 /* Protected */,
       5,    1,   29,    2, 0x09,    3 /* Protected */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    6,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPColorScaleAxisRectPrivate::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAxisRect::staticMetaObject>(),
    qt_meta_stringdata_QCPColorScaleAxisRectPrivate.offsetsAndSizes,
    qt_meta_data_QCPColorScaleAxisRectPrivate,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPColorScaleAxisRectPrivate_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPColorScaleAxisRectPrivate, std::true_type>,
        // method 'axisSelectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAxis::SelectableParts, std::false_type>,
        // method 'axisSelectableChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAxis::SelectableParts, std::false_type>
    >,
    nullptr
} };

void QCPColorScaleAxisRectPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCPColorScaleAxisRectPrivate *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->axisSelectionChanged((*reinterpret_cast< std::add_pointer_t<QCPAxis::SelectableParts>>(_a[1]))); break;
        case 1: _t->axisSelectableChanged((*reinterpret_cast< std::add_pointer_t<QCPAxis::SelectableParts>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *QCPColorScaleAxisRectPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPColorScaleAxisRectPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPColorScaleAxisRectPrivate.stringdata0))
        return static_cast<void*>(this);
    return QCPAxisRect::qt_metacast(_clname);
}

int QCPColorScaleAxisRectPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAxisRect::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}
namespace {
struct qt_meta_stringdata_QCPColorScale_t {
    uint offsetsAndSizes[46];
    char stringdata0[14];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[9];
    char stringdata5[21];
    char stringdata6[19];
    char stringdata7[10];
    char stringdata8[16];
    char stringdata9[17];
    char stringdata10[12];
    char stringdata11[13];
    char stringdata12[10];
    char stringdata13[17];
    char stringdata14[12];
    char stringdata15[9];
    char stringdata16[5];
    char stringdata17[18];
    char stringdata18[14];
    char stringdata19[6];
    char stringdata20[9];
    char stringdata21[10];
    char stringdata22[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPColorScale_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPColorScale_t qt_meta_stringdata_QCPColorScale = {
    {
        QT_MOC_LITERAL(0, 13),  // "QCPColorScale"
        QT_MOC_LITERAL(14, 16),  // "dataRangeChanged"
        QT_MOC_LITERAL(31, 0),  // ""
        QT_MOC_LITERAL(32, 8),  // "QCPRange"
        QT_MOC_LITERAL(41, 8),  // "newRange"
        QT_MOC_LITERAL(50, 20),  // "dataScaleTypeChanged"
        QT_MOC_LITERAL(71, 18),  // "QCPAxis::ScaleType"
        QT_MOC_LITERAL(90, 9),  // "scaleType"
        QT_MOC_LITERAL(100, 15),  // "gradientChanged"
        QT_MOC_LITERAL(116, 16),  // "QCPColorGradient"
        QT_MOC_LITERAL(133, 11),  // "newGradient"
        QT_MOC_LITERAL(145, 12),  // "setDataRange"
        QT_MOC_LITERAL(158, 9),  // "dataRange"
        QT_MOC_LITERAL(168, 16),  // "setDataScaleType"
        QT_MOC_LITERAL(185, 11),  // "setGradient"
        QT_MOC_LITERAL(197, 8),  // "gradient"
        QT_MOC_LITERAL(206, 4),  // "type"
        QT_MOC_LITERAL(211, 17),  // "QCPAxis::AxisType"
        QT_MOC_LITERAL(229, 13),  // "dataScaleType"
        QT_MOC_LITERAL(243, 5),  // "label"
        QT_MOC_LITERAL(249, 8),  // "barWidth"
        QT_MOC_LITERAL(258, 9),  // "rangeDrag"
        QT_MOC_LITERAL(268, 9)   // "rangeZoom"
    },
    "QCPColorScale",
    "dataRangeChanged",
    "",
    "QCPRange",
    "newRange",
    "dataScaleTypeChanged",
    "QCPAxis::ScaleType",
    "scaleType",
    "gradientChanged",
    "QCPColorGradient",
    "newGradient",
    "setDataRange",
    "dataRange",
    "setDataScaleType",
    "setGradient",
    "gradient",
    "type",
    "QCPAxis::AxisType",
    "dataScaleType",
    "label",
    "barWidth",
    "rangeDrag",
    "rangeZoom"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPColorScale[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       8,   68, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   50,    2, 0x06,    9 /* Public */,
       5,    1,   53,    2, 0x06,   11 /* Public */,
       8,    1,   56,    2, 0x06,   13 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      11,    1,   59,    2, 0x0a,   15 /* Public */,
      13,    1,   62,    2, 0x0a,   17 /* Public */,
      14,    1,   65,    2, 0x0a,   19 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,   12,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   15,

 // properties: name, type, flags
      16, 0x80000000 | 17, 0x0001510b, uint(-1), 0,
      12, 0x80000000 | 3, 0x0001510b, uint(0), 0,
      18, 0x80000000 | 6, 0x0001510b, uint(1), 0,
      15, 0x80000000 | 9, 0x0001510b, uint(2), 0,
      19, QMetaType::QString, 0x00015103, uint(-1), 0,
      20, QMetaType::Int, 0x00015103, uint(-1), 0,
      21, QMetaType::Bool, 0x00015103, uint(-1), 0,
      22, QMetaType::Bool, 0x00015103, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT static const QMetaObject::SuperData qt_meta_extradata_QCPColorScale[] = {
    QMetaObject::SuperData::link<QCPAxis::staticMetaObject>(),
    nullptr
};

Q_CONSTINIT const QMetaObject QCPColorScale::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayoutElement::staticMetaObject>(),
    qt_meta_stringdata_QCPColorScale.offsetsAndSizes,
    qt_meta_data_QCPColorScale,
    qt_static_metacall,
    qt_meta_extradata_QCPColorScale,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPColorScale_t,
        // property 'type'
        QtPrivate::TypeAndForceComplete<QCPAxis::AxisType, std::true_type>,
        // property 'dataRange'
        QtPrivate::TypeAndForceComplete<QCPRange, std::true_type>,
        // property 'dataScaleType'
        QtPrivate::TypeAndForceComplete<QCPAxis::ScaleType, std::true_type>,
        // property 'gradient'
        QtPrivate::TypeAndForceComplete<QCPColorGradient, std::true_type>,
        // property 'label'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'barWidth'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'rangeDrag'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'rangeZoom'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPColorScale, std::true_type>,
        // method 'dataRangeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        // method 'dataScaleTypeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAxis::ScaleType, std::false_type>,
        // method 'gradientChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPColorGradient &, std::false_type>,
        // method 'setDataRange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        // method 'setDataScaleType'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAxis::ScaleType, std::false_type>,
        // method 'setGradient'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPColorGradient &, std::false_type>
    >,
    nullptr
} };

void QCPColorScale::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCPColorScale *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->dataRangeChanged((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1]))); break;
        case 1: _t->dataScaleTypeChanged((*reinterpret_cast< std::add_pointer_t<QCPAxis::ScaleType>>(_a[1]))); break;
        case 2: _t->gradientChanged((*reinterpret_cast< std::add_pointer_t<QCPColorGradient>>(_a[1]))); break;
        case 3: _t->setDataRange((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1]))); break;
        case 4: _t->setDataScaleType((*reinterpret_cast< std::add_pointer_t<QCPAxis::ScaleType>>(_a[1]))); break;
        case 5: _t->setGradient((*reinterpret_cast< std::add_pointer_t<QCPColorGradient>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAxis::ScaleType >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAxis::ScaleType >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QCPColorScale::*)(const QCPRange & );
            if (_t _q_method = &QCPColorScale::dataRangeChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QCPColorScale::*)(QCPAxis::ScaleType );
            if (_t _q_method = &QCPColorScale::dataScaleTypeChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QCPColorScale::*)(const QCPColorGradient & );
            if (_t _q_method = &QCPColorScale::gradientChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxis::AxisType >(); break;
        case 2:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxis::ScaleType >(); break;
        }
    }
else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPColorScale *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QCPAxis::AxisType*>(_v) = _t->type(); break;
        case 1: *reinterpret_cast< QCPRange*>(_v) = _t->dataRange(); break;
        case 2: *reinterpret_cast< QCPAxis::ScaleType*>(_v) = _t->dataScaleType(); break;
        case 3: *reinterpret_cast< QCPColorGradient*>(_v) = _t->gradient(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->label(); break;
        case 5: *reinterpret_cast< int*>(_v) = _t->barWidth(); break;
        case 6: *reinterpret_cast< bool*>(_v) = _t->rangeDrag(); break;
        case 7: *reinterpret_cast< bool*>(_v) = _t->rangeZoom(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPColorScale *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setType(*reinterpret_cast< QCPAxis::AxisType*>(_v)); break;
        case 1: _t->setDataRange(*reinterpret_cast< QCPRange*>(_v)); break;
        case 2: _t->setDataScaleType(*reinterpret_cast< QCPAxis::ScaleType*>(_v)); break;
        case 3: _t->setGradient(*reinterpret_cast< QCPColorGradient*>(_v)); break;
        case 4: _t->setLabel(*reinterpret_cast< QString*>(_v)); break;
        case 5: _t->setBarWidth(*reinterpret_cast< int*>(_v)); break;
        case 6: _t->setRangeDrag(*reinterpret_cast< bool*>(_v)); break;
        case 7: _t->setRangeZoom(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *QCPColorScale::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPColorScale::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPColorScale.stringdata0))
        return static_cast<void*>(this);
    return QCPLayoutElement::qt_metacast(_clname);
}

int QCPColorScale::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayoutElement::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void QCPColorScale::dataRangeChanged(const QCPRange & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCPColorScale::dataScaleTypeChanged(QCPAxis::ScaleType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QCPColorScale::gradientChanged(const QCPColorGradient & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
namespace {
struct qt_meta_stringdata_QCPGraph_t {
    uint offsetsAndSizes[30];
    char stringdata0[9];
    char stringdata1[10];
    char stringdata2[10];
    char stringdata3[13];
    char stringdata4[16];
    char stringdata5[12];
    char stringdata6[17];
    char stringdata7[10];
    char stringdata8[17];
    char stringdata9[7];
    char stringdata10[7];
    char stringdata11[11];
    char stringdata12[12];
    char stringdata13[13];
    char stringdata14[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPGraph_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPGraph_t qt_meta_stringdata_QCPGraph = {
    {
        QT_MOC_LITERAL(0, 8),  // "QCPGraph"
        QT_MOC_LITERAL(9, 9),  // "lineStyle"
        QT_MOC_LITERAL(19, 9),  // "LineStyle"
        QT_MOC_LITERAL(29, 12),  // "scatterStyle"
        QT_MOC_LITERAL(42, 15),  // "QCPScatterStyle"
        QT_MOC_LITERAL(58, 11),  // "scatterSkip"
        QT_MOC_LITERAL(70, 16),  // "channelFillGraph"
        QT_MOC_LITERAL(87, 9),  // "QCPGraph*"
        QT_MOC_LITERAL(97, 16),  // "adaptiveSampling"
        QT_MOC_LITERAL(114, 6),  // "lsNone"
        QT_MOC_LITERAL(121, 6),  // "lsLine"
        QT_MOC_LITERAL(128, 10),  // "lsStepLeft"
        QT_MOC_LITERAL(139, 11),  // "lsStepRight"
        QT_MOC_LITERAL(151, 12),  // "lsStepCenter"
        QT_MOC_LITERAL(164, 9)   // "lsImpulse"
    },
    "QCPGraph",
    "lineStyle",
    "LineStyle",
    "scatterStyle",
    "QCPScatterStyle",
    "scatterSkip",
    "channelFillGraph",
    "QCPGraph*",
    "adaptiveSampling",
    "lsNone",
    "lsLine",
    "lsStepLeft",
    "lsStepRight",
    "lsStepCenter",
    "lsImpulse"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPGraph[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       5,   14, // properties
       1,   39, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, 0x80000000 | 2, 0x0001510b, uint(-1), 0,
       3, 0x80000000 | 4, 0x0001510b, uint(-1), 0,
       5, QMetaType::Int, 0x00015103, uint(-1), 0,
       6, 0x80000000 | 7, 0x0001510b, uint(-1), 0,
       8, QMetaType::Bool, 0x00015103, uint(-1), 0,

 // enums: name, alias, flags, count, data
       2,    2, 0x0,    6,   44,

 // enum data: key, value
       9, uint(QCPGraph::lsNone),
      10, uint(QCPGraph::lsLine),
      11, uint(QCPGraph::lsStepLeft),
      12, uint(QCPGraph::lsStepRight),
      13, uint(QCPGraph::lsStepCenter),
      14, uint(QCPGraph::lsImpulse),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPGraph::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractPlottable1D<QCPGraphData>::staticMetaObject>(),
    qt_meta_stringdata_QCPGraph.offsetsAndSizes,
    qt_meta_data_QCPGraph,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPGraph_t,
        // property 'lineStyle'
        QtPrivate::TypeAndForceComplete<LineStyle, std::true_type>,
        // property 'scatterStyle'
        QtPrivate::TypeAndForceComplete<QCPScatterStyle, std::true_type>,
        // property 'scatterSkip'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'channelFillGraph'
        QtPrivate::TypeAndForceComplete<QCPGraph*, std::true_type>,
        // property 'adaptiveSampling'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPGraph, std::true_type>
    >,
    nullptr
} };

void QCPGraph::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPGraph* >(); break;
        }
    }
else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPGraph *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< LineStyle*>(_v) = _t->lineStyle(); break;
        case 1: *reinterpret_cast< QCPScatterStyle*>(_v) = _t->scatterStyle(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->scatterSkip(); break;
        case 3: *reinterpret_cast< QCPGraph**>(_v) = _t->channelFillGraph(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->adaptiveSampling(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPGraph *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setLineStyle(*reinterpret_cast< LineStyle*>(_v)); break;
        case 1: _t->setScatterStyle(*reinterpret_cast< QCPScatterStyle*>(_v)); break;
        case 2: _t->setScatterSkip(*reinterpret_cast< int*>(_v)); break;
        case 3: _t->setChannelFillGraph(*reinterpret_cast< QCPGraph**>(_v)); break;
        case 4: _t->setAdaptiveSampling(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_o;
}

const QMetaObject *QCPGraph::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPGraph::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPGraph.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractPlottable1D<QCPGraphData>::qt_metacast(_clname);
}

int QCPGraph::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractPlottable1D<QCPGraphData>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
namespace {
struct qt_meta_stringdata_QCPCurve_t {
    uint offsetsAndSizes[16];
    char stringdata0[9];
    char stringdata1[13];
    char stringdata2[16];
    char stringdata3[12];
    char stringdata4[10];
    char stringdata5[10];
    char stringdata6[7];
    char stringdata7[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPCurve_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPCurve_t qt_meta_stringdata_QCPCurve = {
    {
        QT_MOC_LITERAL(0, 8),  // "QCPCurve"
        QT_MOC_LITERAL(9, 12),  // "scatterStyle"
        QT_MOC_LITERAL(22, 15),  // "QCPScatterStyle"
        QT_MOC_LITERAL(38, 11),  // "scatterSkip"
        QT_MOC_LITERAL(50, 9),  // "lineStyle"
        QT_MOC_LITERAL(60, 9),  // "LineStyle"
        QT_MOC_LITERAL(70, 6),  // "lsNone"
        QT_MOC_LITERAL(77, 6)   // "lsLine"
    },
    "QCPCurve",
    "scatterStyle",
    "QCPScatterStyle",
    "scatterSkip",
    "lineStyle",
    "LineStyle",
    "lsNone",
    "lsLine"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPCurve[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       3,   14, // properties
       1,   29, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, 0x80000000 | 2, 0x0001510b, uint(-1), 0,
       3, QMetaType::Int, 0x00015103, uint(-1), 0,
       4, 0x80000000 | 5, 0x0001510b, uint(-1), 0,

 // enums: name, alias, flags, count, data
       5,    5, 0x0,    2,   34,

 // enum data: key, value
       6, uint(QCPCurve::lsNone),
       7, uint(QCPCurve::lsLine),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPCurve::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractPlottable1D<QCPCurveData>::staticMetaObject>(),
    qt_meta_stringdata_QCPCurve.offsetsAndSizes,
    qt_meta_data_QCPCurve,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPCurve_t,
        // property 'scatterStyle'
        QtPrivate::TypeAndForceComplete<QCPScatterStyle, std::true_type>,
        // property 'scatterSkip'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'lineStyle'
        QtPrivate::TypeAndForceComplete<LineStyle, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPCurve, std::true_type>
    >,
    nullptr
} };

void QCPCurve::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPCurve *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QCPScatterStyle*>(_v) = _t->scatterStyle(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->scatterSkip(); break;
        case 2: *reinterpret_cast< LineStyle*>(_v) = _t->lineStyle(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPCurve *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setScatterStyle(*reinterpret_cast< QCPScatterStyle*>(_v)); break;
        case 1: _t->setScatterSkip(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setLineStyle(*reinterpret_cast< LineStyle*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *QCPCurve::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPCurve::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPCurve.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractPlottable1D<QCPCurveData>::qt_metacast(_clname);
}

int QCPCurve::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractPlottable1D<QCPCurveData>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
namespace {
struct qt_meta_stringdata_QCPBarsGroup_t {
    uint offsetsAndSizes[14];
    char stringdata0[13];
    char stringdata1[12];
    char stringdata2[12];
    char stringdata3[8];
    char stringdata4[11];
    char stringdata5[16];
    char stringdata6[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPBarsGroup_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPBarsGroup_t qt_meta_stringdata_QCPBarsGroup = {
    {
        QT_MOC_LITERAL(0, 12),  // "QCPBarsGroup"
        QT_MOC_LITERAL(13, 11),  // "spacingType"
        QT_MOC_LITERAL(25, 11),  // "SpacingType"
        QT_MOC_LITERAL(37, 7),  // "spacing"
        QT_MOC_LITERAL(45, 10),  // "stAbsolute"
        QT_MOC_LITERAL(56, 15),  // "stAxisRectRatio"
        QT_MOC_LITERAL(72, 12)   // "stPlotCoords"
    },
    "QCPBarsGroup",
    "spacingType",
    "SpacingType",
    "spacing",
    "stAbsolute",
    "stAxisRectRatio",
    "stPlotCoords"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPBarsGroup[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       2,   14, // properties
       1,   24, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, 0x80000000 | 2, 0x0001510b, uint(-1), 0,
       3, QMetaType::Double, 0x00015103, uint(-1), 0,

 // enums: name, alias, flags, count, data
       2,    2, 0x0,    3,   29,

 // enum data: key, value
       4, uint(QCPBarsGroup::stAbsolute),
       5, uint(QCPBarsGroup::stAxisRectRatio),
       6, uint(QCPBarsGroup::stPlotCoords),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPBarsGroup::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_QCPBarsGroup.offsetsAndSizes,
    qt_meta_data_QCPBarsGroup,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPBarsGroup_t,
        // property 'spacingType'
        QtPrivate::TypeAndForceComplete<SpacingType, std::true_type>,
        // property 'spacing'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPBarsGroup, std::true_type>
    >,
    nullptr
} };

void QCPBarsGroup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPBarsGroup *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< SpacingType*>(_v) = _t->spacingType(); break;
        case 1: *reinterpret_cast< double*>(_v) = _t->spacing(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPBarsGroup *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setSpacingType(*reinterpret_cast< SpacingType*>(_v)); break;
        case 1: _t->setSpacing(*reinterpret_cast< double*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *QCPBarsGroup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPBarsGroup::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPBarsGroup.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QCPBarsGroup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
namespace {
struct qt_meta_stringdata_QCPBars_t {
    uint offsetsAndSizes[28];
    char stringdata0[8];
    char stringdata1[6];
    char stringdata2[10];
    char stringdata3[10];
    char stringdata4[10];
    char stringdata5[14];
    char stringdata6[10];
    char stringdata7[12];
    char stringdata8[9];
    char stringdata9[9];
    char stringdata10[9];
    char stringdata11[11];
    char stringdata12[16];
    char stringdata13[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPBars_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPBars_t qt_meta_stringdata_QCPBars = {
    {
        QT_MOC_LITERAL(0, 7),  // "QCPBars"
        QT_MOC_LITERAL(8, 5),  // "width"
        QT_MOC_LITERAL(14, 9),  // "widthType"
        QT_MOC_LITERAL(24, 9),  // "WidthType"
        QT_MOC_LITERAL(34, 9),  // "barsGroup"
        QT_MOC_LITERAL(44, 13),  // "QCPBarsGroup*"
        QT_MOC_LITERAL(58, 9),  // "baseValue"
        QT_MOC_LITERAL(68, 11),  // "stackingGap"
        QT_MOC_LITERAL(80, 8),  // "barBelow"
        QT_MOC_LITERAL(89, 8),  // "QCPBars*"
        QT_MOC_LITERAL(98, 8),  // "barAbove"
        QT_MOC_LITERAL(107, 10),  // "wtAbsolute"
        QT_MOC_LITERAL(118, 15),  // "wtAxisRectRatio"
        QT_MOC_LITERAL(134, 12)   // "wtPlotCoords"
    },
    "QCPBars",
    "width",
    "widthType",
    "WidthType",
    "barsGroup",
    "QCPBarsGroup*",
    "baseValue",
    "stackingGap",
    "barBelow",
    "QCPBars*",
    "barAbove",
    "wtAbsolute",
    "wtAxisRectRatio",
    "wtPlotCoords"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPBars[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       7,   14, // properties
       1,   49, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::Double, 0x00015103, uint(-1), 0,
       2, 0x80000000 | 3, 0x0001510b, uint(-1), 0,
       4, 0x80000000 | 5, 0x0001510b, uint(-1), 0,
       6, QMetaType::Double, 0x00015103, uint(-1), 0,
       7, QMetaType::Double, 0x00015103, uint(-1), 0,
       8, 0x80000000 | 9, 0x00015009, uint(-1), 0,
      10, 0x80000000 | 9, 0x00015009, uint(-1), 0,

 // enums: name, alias, flags, count, data
       3,    3, 0x0,    3,   54,

 // enum data: key, value
      11, uint(QCPBars::wtAbsolute),
      12, uint(QCPBars::wtAxisRectRatio),
      13, uint(QCPBars::wtPlotCoords),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPBars::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractPlottable1D<QCPBarsData>::staticMetaObject>(),
    qt_meta_stringdata_QCPBars.offsetsAndSizes,
    qt_meta_data_QCPBars,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPBars_t,
        // property 'width'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'widthType'
        QtPrivate::TypeAndForceComplete<WidthType, std::true_type>,
        // property 'barsGroup'
        QtPrivate::TypeAndForceComplete<QCPBarsGroup*, std::true_type>,
        // property 'baseValue'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'stackingGap'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'barBelow'
        QtPrivate::TypeAndForceComplete<QCPBars*, std::true_type>,
        // property 'barAbove'
        QtPrivate::TypeAndForceComplete<QCPBars*, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPBars, std::true_type>
    >,
    nullptr
} };

void QCPBars::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
        case 5:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPBars* >(); break;
        case 2:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPBarsGroup* >(); break;
        }
    }
else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPBars *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< double*>(_v) = _t->width(); break;
        case 1: *reinterpret_cast< WidthType*>(_v) = _t->widthType(); break;
        case 2: *reinterpret_cast< QCPBarsGroup**>(_v) = _t->barsGroup(); break;
        case 3: *reinterpret_cast< double*>(_v) = _t->baseValue(); break;
        case 4: *reinterpret_cast< double*>(_v) = _t->stackingGap(); break;
        case 5: *reinterpret_cast< QCPBars**>(_v) = _t->barBelow(); break;
        case 6: *reinterpret_cast< QCPBars**>(_v) = _t->barAbove(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPBars *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setWidth(*reinterpret_cast< double*>(_v)); break;
        case 1: _t->setWidthType(*reinterpret_cast< WidthType*>(_v)); break;
        case 2: _t->setBarsGroup(*reinterpret_cast< QCPBarsGroup**>(_v)); break;
        case 3: _t->setBaseValue(*reinterpret_cast< double*>(_v)); break;
        case 4: _t->setStackingGap(*reinterpret_cast< double*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_o;
}

const QMetaObject *QCPBars::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPBars::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPBars.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractPlottable1D<QCPBarsData>::qt_metacast(_clname);
}

int QCPBars::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractPlottable1D<QCPBarsData>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
namespace {
struct qt_meta_stringdata_QCPStatisticalBox_t {
    uint offsetsAndSizes[18];
    char stringdata0[18];
    char stringdata1[6];
    char stringdata2[13];
    char stringdata3[11];
    char stringdata4[14];
    char stringdata5[19];
    char stringdata6[10];
    char stringdata7[13];
    char stringdata8[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPStatisticalBox_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPStatisticalBox_t qt_meta_stringdata_QCPStatisticalBox = {
    {
        QT_MOC_LITERAL(0, 17),  // "QCPStatisticalBox"
        QT_MOC_LITERAL(18, 5),  // "width"
        QT_MOC_LITERAL(24, 12),  // "whiskerWidth"
        QT_MOC_LITERAL(37, 10),  // "whiskerPen"
        QT_MOC_LITERAL(48, 13),  // "whiskerBarPen"
        QT_MOC_LITERAL(62, 18),  // "whiskerAntialiased"
        QT_MOC_LITERAL(81, 9),  // "medianPen"
        QT_MOC_LITERAL(91, 12),  // "outlierStyle"
        QT_MOC_LITERAL(104, 15)   // "QCPScatterStyle"
    },
    "QCPStatisticalBox",
    "width",
    "whiskerWidth",
    "whiskerPen",
    "whiskerBarPen",
    "whiskerAntialiased",
    "medianPen",
    "outlierStyle",
    "QCPScatterStyle"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPStatisticalBox[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       7,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::Double, 0x00015103, uint(-1), 0,
       2, QMetaType::Double, 0x00015103, uint(-1), 0,
       3, QMetaType::QPen, 0x00015103, uint(-1), 0,
       4, QMetaType::QPen, 0x00015103, uint(-1), 0,
       5, QMetaType::Bool, 0x00015103, uint(-1), 0,
       6, QMetaType::QPen, 0x00015103, uint(-1), 0,
       7, 0x80000000 | 8, 0x0001510b, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPStatisticalBox::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractPlottable1D<QCPStatisticalBoxData>::staticMetaObject>(),
    qt_meta_stringdata_QCPStatisticalBox.offsetsAndSizes,
    qt_meta_data_QCPStatisticalBox,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPStatisticalBox_t,
        // property 'width'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'whiskerWidth'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'whiskerPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'whiskerBarPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'whiskerAntialiased'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'medianPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'outlierStyle'
        QtPrivate::TypeAndForceComplete<QCPScatterStyle, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPStatisticalBox, std::true_type>
    >,
    nullptr
} };

void QCPStatisticalBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPStatisticalBox *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< double*>(_v) = _t->width(); break;
        case 1: *reinterpret_cast< double*>(_v) = _t->whiskerWidth(); break;
        case 2: *reinterpret_cast< QPen*>(_v) = _t->whiskerPen(); break;
        case 3: *reinterpret_cast< QPen*>(_v) = _t->whiskerBarPen(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->whiskerAntialiased(); break;
        case 5: *reinterpret_cast< QPen*>(_v) = _t->medianPen(); break;
        case 6: *reinterpret_cast< QCPScatterStyle*>(_v) = _t->outlierStyle(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPStatisticalBox *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setWidth(*reinterpret_cast< double*>(_v)); break;
        case 1: _t->setWhiskerWidth(*reinterpret_cast< double*>(_v)); break;
        case 2: _t->setWhiskerPen(*reinterpret_cast< QPen*>(_v)); break;
        case 3: _t->setWhiskerBarPen(*reinterpret_cast< QPen*>(_v)); break;
        case 4: _t->setWhiskerAntialiased(*reinterpret_cast< bool*>(_v)); break;
        case 5: _t->setMedianPen(*reinterpret_cast< QPen*>(_v)); break;
        case 6: _t->setOutlierStyle(*reinterpret_cast< QCPScatterStyle*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *QCPStatisticalBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPStatisticalBox::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPStatisticalBox.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractPlottable1D<QCPStatisticalBoxData>::qt_metacast(_clname);
}

int QCPStatisticalBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractPlottable1D<QCPStatisticalBoxData>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
namespace {
struct qt_meta_stringdata_QCPColorMap_t {
    uint offsetsAndSizes[50];
    char stringdata0[12];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[9];
    char stringdata5[21];
    char stringdata6[19];
    char stringdata7[10];
    char stringdata8[16];
    char stringdata9[17];
    char stringdata10[12];
    char stringdata11[13];
    char stringdata12[10];
    char stringdata13[17];
    char stringdata14[12];
    char stringdata15[9];
    char stringdata16[17];
    char stringdata17[23];
    char stringdata18[14];
    char stringdata19[10];
    char stringdata20[14];
    char stringdata21[12];
    char stringdata22[14];
    char stringdata23[11];
    char stringdata24[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPColorMap_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPColorMap_t qt_meta_stringdata_QCPColorMap = {
    {
        QT_MOC_LITERAL(0, 11),  // "QCPColorMap"
        QT_MOC_LITERAL(12, 16),  // "dataRangeChanged"
        QT_MOC_LITERAL(29, 0),  // ""
        QT_MOC_LITERAL(30, 8),  // "QCPRange"
        QT_MOC_LITERAL(39, 8),  // "newRange"
        QT_MOC_LITERAL(48, 20),  // "dataScaleTypeChanged"
        QT_MOC_LITERAL(69, 18),  // "QCPAxis::ScaleType"
        QT_MOC_LITERAL(88, 9),  // "scaleType"
        QT_MOC_LITERAL(98, 15),  // "gradientChanged"
        QT_MOC_LITERAL(114, 16),  // "QCPColorGradient"
        QT_MOC_LITERAL(131, 11),  // "newGradient"
        QT_MOC_LITERAL(143, 12),  // "setDataRange"
        QT_MOC_LITERAL(156, 9),  // "dataRange"
        QT_MOC_LITERAL(166, 16),  // "setDataScaleType"
        QT_MOC_LITERAL(183, 11),  // "setGradient"
        QT_MOC_LITERAL(195, 8),  // "gradient"
        QT_MOC_LITERAL(204, 16),  // "updateLegendIcon"
        QT_MOC_LITERAL(221, 22),  // "Qt::TransformationMode"
        QT_MOC_LITERAL(244, 13),  // "transformMode"
        QT_MOC_LITERAL(258, 9),  // "thumbSize"
        QT_MOC_LITERAL(268, 13),  // "dataScaleType"
        QT_MOC_LITERAL(282, 11),  // "interpolate"
        QT_MOC_LITERAL(294, 13),  // "tightBoundary"
        QT_MOC_LITERAL(308, 10),  // "colorScale"
        QT_MOC_LITERAL(319, 14)   // "QCPColorScale*"
    },
    "QCPColorMap",
    "dataRangeChanged",
    "",
    "QCPRange",
    "newRange",
    "dataScaleTypeChanged",
    "QCPAxis::ScaleType",
    "scaleType",
    "gradientChanged",
    "QCPColorGradient",
    "newGradient",
    "setDataRange",
    "dataRange",
    "setDataScaleType",
    "setGradient",
    "gradient",
    "updateLegendIcon",
    "Qt::TransformationMode",
    "transformMode",
    "thumbSize",
    "dataScaleType",
    "interpolate",
    "tightBoundary",
    "colorScale",
    "QCPColorScale*"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPColorMap[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       6,   95, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   68,    2, 0x06,    7 /* Public */,
       5,    1,   71,    2, 0x06,    9 /* Public */,
       8,    1,   74,    2, 0x06,   11 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      11,    1,   77,    2, 0x0a,   13 /* Public */,
      13,    1,   80,    2, 0x0a,   15 /* Public */,
      14,    1,   83,    2, 0x0a,   17 /* Public */,
      16,    2,   86,    2, 0x0a,   19 /* Public */,
      16,    1,   91,    2, 0x2a,   22 /* Public | MethodCloned */,
      16,    0,   94,    2, 0x2a,   24 /* Public | MethodCloned */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,   12,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   15,
    QMetaType::Void, 0x80000000 | 17, QMetaType::QSize,   18,   19,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void,

 // properties: name, type, flags
      12, 0x80000000 | 3, 0x0001510b, uint(0), 0,
      20, 0x80000000 | 6, 0x0001510b, uint(1), 0,
      15, 0x80000000 | 9, 0x0001510b, uint(2), 0,
      21, QMetaType::Bool, 0x00015103, uint(-1), 0,
      22, QMetaType::Bool, 0x00015103, uint(-1), 0,
      23, 0x80000000 | 24, 0x0001510b, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT static const QMetaObject::SuperData qt_meta_extradata_QCPColorMap[] = {
    QMetaObject::SuperData::link<QCPAxis::staticMetaObject>(),
    nullptr
};

Q_CONSTINIT const QMetaObject QCPColorMap::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractPlottable::staticMetaObject>(),
    qt_meta_stringdata_QCPColorMap.offsetsAndSizes,
    qt_meta_data_QCPColorMap,
    qt_static_metacall,
    qt_meta_extradata_QCPColorMap,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPColorMap_t,
        // property 'dataRange'
        QtPrivate::TypeAndForceComplete<QCPRange, std::true_type>,
        // property 'dataScaleType'
        QtPrivate::TypeAndForceComplete<QCPAxis::ScaleType, std::true_type>,
        // property 'gradient'
        QtPrivate::TypeAndForceComplete<QCPColorGradient, std::true_type>,
        // property 'interpolate'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'tightBoundary'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'colorScale'
        QtPrivate::TypeAndForceComplete<QCPColorScale*, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPColorMap, std::true_type>,
        // method 'dataRangeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        // method 'dataScaleTypeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAxis::ScaleType, std::false_type>,
        // method 'gradientChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPColorGradient &, std::false_type>,
        // method 'setDataRange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        // method 'setDataScaleType'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPAxis::ScaleType, std::false_type>,
        // method 'setGradient'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPColorGradient &, std::false_type>,
        // method 'updateLegendIcon'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Qt::TransformationMode, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QSize &, std::false_type>,
        // method 'updateLegendIcon'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Qt::TransformationMode, std::false_type>,
        // method 'updateLegendIcon'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void QCPColorMap::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCPColorMap *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->dataRangeChanged((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1]))); break;
        case 1: _t->dataScaleTypeChanged((*reinterpret_cast< std::add_pointer_t<QCPAxis::ScaleType>>(_a[1]))); break;
        case 2: _t->gradientChanged((*reinterpret_cast< std::add_pointer_t<QCPColorGradient>>(_a[1]))); break;
        case 3: _t->setDataRange((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1]))); break;
        case 4: _t->setDataScaleType((*reinterpret_cast< std::add_pointer_t<QCPAxis::ScaleType>>(_a[1]))); break;
        case 5: _t->setGradient((*reinterpret_cast< std::add_pointer_t<QCPColorGradient>>(_a[1]))); break;
        case 6: _t->updateLegendIcon((*reinterpret_cast< std::add_pointer_t<Qt::TransformationMode>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QSize>>(_a[2]))); break;
        case 7: _t->updateLegendIcon((*reinterpret_cast< std::add_pointer_t<Qt::TransformationMode>>(_a[1]))); break;
        case 8: _t->updateLegendIcon(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAxis::ScaleType >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPAxis::ScaleType >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QCPColorMap::*)(const QCPRange & );
            if (_t _q_method = &QCPColorMap::dataRangeChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QCPColorMap::*)(QCPAxis::ScaleType );
            if (_t _q_method = &QCPColorMap::dataScaleTypeChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QCPColorMap::*)(const QCPColorGradient & );
            if (_t _q_method = &QCPColorMap::gradientChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAxis::ScaleType >(); break;
        case 5:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPColorScale* >(); break;
        }
    }
else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPColorMap *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QCPRange*>(_v) = _t->dataRange(); break;
        case 1: *reinterpret_cast< QCPAxis::ScaleType*>(_v) = _t->dataScaleType(); break;
        case 2: *reinterpret_cast< QCPColorGradient*>(_v) = _t->gradient(); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->interpolate(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->tightBoundary(); break;
        case 5: *reinterpret_cast< QCPColorScale**>(_v) = _t->colorScale(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPColorMap *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setDataRange(*reinterpret_cast< QCPRange*>(_v)); break;
        case 1: _t->setDataScaleType(*reinterpret_cast< QCPAxis::ScaleType*>(_v)); break;
        case 2: _t->setGradient(*reinterpret_cast< QCPColorGradient*>(_v)); break;
        case 3: _t->setInterpolate(*reinterpret_cast< bool*>(_v)); break;
        case 4: _t->setTightBoundary(*reinterpret_cast< bool*>(_v)); break;
        case 5: _t->setColorScale(*reinterpret_cast< QCPColorScale**>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *QCPColorMap::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPColorMap::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPColorMap.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractPlottable::qt_metacast(_clname);
}

int QCPColorMap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractPlottable::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void QCPColorMap::dataRangeChanged(const QCPRange & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCPColorMap::dataScaleTypeChanged(QCPAxis::ScaleType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QCPColorMap::gradientChanged(const QCPColorGradient & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
namespace {
struct qt_meta_stringdata_QCPFinancial_t {
    uint offsetsAndSizes[32];
    char stringdata0[13];
    char stringdata1[11];
    char stringdata2[11];
    char stringdata3[6];
    char stringdata4[10];
    char stringdata5[10];
    char stringdata6[11];
    char stringdata7[14];
    char stringdata8[14];
    char stringdata9[12];
    char stringdata10[12];
    char stringdata11[11];
    char stringdata12[16];
    char stringdata13[13];
    char stringdata14[7];
    char stringdata15[14];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPFinancial_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPFinancial_t qt_meta_stringdata_QCPFinancial = {
    {
        QT_MOC_LITERAL(0, 12),  // "QCPFinancial"
        QT_MOC_LITERAL(13, 10),  // "chartStyle"
        QT_MOC_LITERAL(24, 10),  // "ChartStyle"
        QT_MOC_LITERAL(35, 5),  // "width"
        QT_MOC_LITERAL(41, 9),  // "widthType"
        QT_MOC_LITERAL(51, 9),  // "WidthType"
        QT_MOC_LITERAL(61, 10),  // "twoColored"
        QT_MOC_LITERAL(72, 13),  // "brushPositive"
        QT_MOC_LITERAL(86, 13),  // "brushNegative"
        QT_MOC_LITERAL(100, 11),  // "penPositive"
        QT_MOC_LITERAL(112, 11),  // "penNegative"
        QT_MOC_LITERAL(124, 10),  // "wtAbsolute"
        QT_MOC_LITERAL(135, 15),  // "wtAxisRectRatio"
        QT_MOC_LITERAL(151, 12),  // "wtPlotCoords"
        QT_MOC_LITERAL(164, 6),  // "csOhlc"
        QT_MOC_LITERAL(171, 13)   // "csCandlestick"
    },
    "QCPFinancial",
    "chartStyle",
    "ChartStyle",
    "width",
    "widthType",
    "WidthType",
    "twoColored",
    "brushPositive",
    "brushNegative",
    "penPositive",
    "penNegative",
    "wtAbsolute",
    "wtAxisRectRatio",
    "wtPlotCoords",
    "csOhlc",
    "csCandlestick"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPFinancial[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       8,   14, // properties
       2,   54, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, 0x80000000 | 2, 0x0001510b, uint(-1), 0,
       3, QMetaType::Double, 0x00015103, uint(-1), 0,
       4, 0x80000000 | 5, 0x0001510b, uint(-1), 0,
       6, QMetaType::Bool, 0x00015103, uint(-1), 0,
       7, QMetaType::QBrush, 0x00015103, uint(-1), 0,
       8, QMetaType::QBrush, 0x00015103, uint(-1), 0,
       9, QMetaType::QPen, 0x00015103, uint(-1), 0,
      10, QMetaType::QPen, 0x00015103, uint(-1), 0,

 // enums: name, alias, flags, count, data
       5,    5, 0x0,    3,   64,
       2,    2, 0x0,    2,   70,

 // enum data: key, value
      11, uint(QCPFinancial::wtAbsolute),
      12, uint(QCPFinancial::wtAxisRectRatio),
      13, uint(QCPFinancial::wtPlotCoords),
      14, uint(QCPFinancial::csOhlc),
      15, uint(QCPFinancial::csCandlestick),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPFinancial::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractPlottable1D<QCPFinancialData>::staticMetaObject>(),
    qt_meta_stringdata_QCPFinancial.offsetsAndSizes,
    qt_meta_data_QCPFinancial,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPFinancial_t,
        // property 'chartStyle'
        QtPrivate::TypeAndForceComplete<ChartStyle, std::true_type>,
        // property 'width'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'widthType'
        QtPrivate::TypeAndForceComplete<WidthType, std::true_type>,
        // property 'twoColored'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'brushPositive'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // property 'brushNegative'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // property 'penPositive'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'penNegative'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPFinancial, std::true_type>
    >,
    nullptr
} };

void QCPFinancial::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPFinancial *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< ChartStyle*>(_v) = _t->chartStyle(); break;
        case 1: *reinterpret_cast< double*>(_v) = _t->width(); break;
        case 2: *reinterpret_cast< WidthType*>(_v) = _t->widthType(); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->twoColored(); break;
        case 4: *reinterpret_cast< QBrush*>(_v) = _t->brushPositive(); break;
        case 5: *reinterpret_cast< QBrush*>(_v) = _t->brushNegative(); break;
        case 6: *reinterpret_cast< QPen*>(_v) = _t->penPositive(); break;
        case 7: *reinterpret_cast< QPen*>(_v) = _t->penNegative(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPFinancial *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setChartStyle(*reinterpret_cast< ChartStyle*>(_v)); break;
        case 1: _t->setWidth(*reinterpret_cast< double*>(_v)); break;
        case 2: _t->setWidthType(*reinterpret_cast< WidthType*>(_v)); break;
        case 3: _t->setTwoColored(*reinterpret_cast< bool*>(_v)); break;
        case 4: _t->setBrushPositive(*reinterpret_cast< QBrush*>(_v)); break;
        case 5: _t->setBrushNegative(*reinterpret_cast< QBrush*>(_v)); break;
        case 6: _t->setPenPositive(*reinterpret_cast< QPen*>(_v)); break;
        case 7: _t->setPenNegative(*reinterpret_cast< QPen*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *QCPFinancial::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPFinancial::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPFinancial.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractPlottable1D<QCPFinancialData>::qt_metacast(_clname);
}

int QCPFinancial::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractPlottable1D<QCPFinancialData>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
namespace {
struct qt_meta_stringdata_QCPErrorBars_t {
    uint offsetsAndSizes[22];
    char stringdata0[13];
    char stringdata1[5];
    char stringdata2[42];
    char stringdata3[14];
    char stringdata4[22];
    char stringdata5[10];
    char stringdata6[10];
    char stringdata7[13];
    char stringdata8[10];
    char stringdata9[11];
    char stringdata10[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPErrorBars_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPErrorBars_t qt_meta_stringdata_QCPErrorBars = {
    {
        QT_MOC_LITERAL(0, 12),  // "QCPErrorBars"
        QT_MOC_LITERAL(13, 4),  // "data"
        QT_MOC_LITERAL(18, 41),  // "QSharedPointer<QCPErrorBarsDa..."
        QT_MOC_LITERAL(60, 13),  // "dataPlottable"
        QT_MOC_LITERAL(74, 21),  // "QCPAbstractPlottable*"
        QT_MOC_LITERAL(96, 9),  // "errorType"
        QT_MOC_LITERAL(106, 9),  // "ErrorType"
        QT_MOC_LITERAL(116, 12),  // "whiskerWidth"
        QT_MOC_LITERAL(129, 9),  // "symbolGap"
        QT_MOC_LITERAL(139, 10),  // "etKeyError"
        QT_MOC_LITERAL(150, 12)   // "etValueError"
    },
    "QCPErrorBars",
    "data",
    "QSharedPointer<QCPErrorBarsDataContainer>",
    "dataPlottable",
    "QCPAbstractPlottable*",
    "errorType",
    "ErrorType",
    "whiskerWidth",
    "symbolGap",
    "etKeyError",
    "etValueError"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPErrorBars[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       5,   14, // properties
       1,   39, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, 0x80000000 | 2, 0x0001510b, uint(-1), 0,
       3, 0x80000000 | 4, 0x0001510b, uint(-1), 0,
       5, 0x80000000 | 6, 0x0001510b, uint(-1), 0,
       7, QMetaType::Double, 0x00015103, uint(-1), 0,
       8, QMetaType::Double, 0x00015103, uint(-1), 0,

 // enums: name, alias, flags, count, data
       6,    6, 0x0,    2,   44,

 // enum data: key, value
       9, uint(QCPErrorBars::etKeyError),
      10, uint(QCPErrorBars::etValueError),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPErrorBars::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractPlottable::staticMetaObject>(),
    qt_meta_stringdata_QCPErrorBars.offsetsAndSizes,
    qt_meta_data_QCPErrorBars,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPErrorBars_t,
        // property 'data'
        QtPrivate::TypeAndForceComplete<QSharedPointer<QCPErrorBarsDataContainer>, std::true_type>,
        // property 'dataPlottable'
        QtPrivate::TypeAndForceComplete<QCPAbstractPlottable*, std::true_type>,
        // property 'errorType'
        QtPrivate::TypeAndForceComplete<ErrorType, std::true_type>,
        // property 'whiskerWidth'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'symbolGap'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPErrorBars, std::true_type>
    >,
    nullptr
} };

void QCPErrorBars::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractPlottable* >(); break;
        }
    }
else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPErrorBars *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QSharedPointer<QCPErrorBarsDataContainer>*>(_v) = _t->data(); break;
        case 1: *reinterpret_cast< QCPAbstractPlottable**>(_v) = _t->dataPlottable(); break;
        case 2: *reinterpret_cast< ErrorType*>(_v) = _t->errorType(); break;
        case 3: *reinterpret_cast< double*>(_v) = _t->whiskerWidth(); break;
        case 4: *reinterpret_cast< double*>(_v) = _t->symbolGap(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPErrorBars *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setData(*reinterpret_cast< QSharedPointer<QCPErrorBarsDataContainer>*>(_v)); break;
        case 1: _t->setDataPlottable(*reinterpret_cast< QCPAbstractPlottable**>(_v)); break;
        case 2: _t->setErrorType(*reinterpret_cast< ErrorType*>(_v)); break;
        case 3: _t->setWhiskerWidth(*reinterpret_cast< double*>(_v)); break;
        case 4: _t->setSymbolGap(*reinterpret_cast< double*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_o;
}

const QMetaObject *QCPErrorBars::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPErrorBars::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPErrorBars.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QCPPlottableInterface1D"))
        return static_cast< QCPPlottableInterface1D*>(this);
    return QCPAbstractPlottable::qt_metacast(_clname);
}

int QCPErrorBars::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractPlottable::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
namespace {
struct qt_meta_stringdata_QCPItemStraightLine_t {
    uint offsetsAndSizes[6];
    char stringdata0[20];
    char stringdata1[4];
    char stringdata2[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPItemStraightLine_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPItemStraightLine_t qt_meta_stringdata_QCPItemStraightLine = {
    {
        QT_MOC_LITERAL(0, 19),  // "QCPItemStraightLine"
        QT_MOC_LITERAL(20, 3),  // "pen"
        QT_MOC_LITERAL(24, 11)   // "selectedPen"
    },
    "QCPItemStraightLine",
    "pen",
    "selectedPen"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPItemStraightLine[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       2,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QPen, 0x00015103, uint(-1), 0,
       2, QMetaType::QPen, 0x00015103, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPItemStraightLine::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractItem::staticMetaObject>(),
    qt_meta_stringdata_QCPItemStraightLine.offsetsAndSizes,
    qt_meta_data_QCPItemStraightLine,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPItemStraightLine_t,
        // property 'pen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'selectedPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPItemStraightLine, std::true_type>
    >,
    nullptr
} };

void QCPItemStraightLine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPItemStraightLine *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QPen*>(_v) = _t->pen(); break;
        case 1: *reinterpret_cast< QPen*>(_v) = _t->selectedPen(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPItemStraightLine *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPen(*reinterpret_cast< QPen*>(_v)); break;
        case 1: _t->setSelectedPen(*reinterpret_cast< QPen*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *QCPItemStraightLine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPItemStraightLine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPItemStraightLine.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractItem::qt_metacast(_clname);
}

int QCPItemStraightLine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
namespace {
struct qt_meta_stringdata_QCPItemLine_t {
    uint offsetsAndSizes[12];
    char stringdata0[12];
    char stringdata1[4];
    char stringdata2[12];
    char stringdata3[5];
    char stringdata4[14];
    char stringdata5[5];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPItemLine_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPItemLine_t qt_meta_stringdata_QCPItemLine = {
    {
        QT_MOC_LITERAL(0, 11),  // "QCPItemLine"
        QT_MOC_LITERAL(12, 3),  // "pen"
        QT_MOC_LITERAL(16, 11),  // "selectedPen"
        QT_MOC_LITERAL(28, 4),  // "head"
        QT_MOC_LITERAL(33, 13),  // "QCPLineEnding"
        QT_MOC_LITERAL(47, 4)   // "tail"
    },
    "QCPItemLine",
    "pen",
    "selectedPen",
    "head",
    "QCPLineEnding",
    "tail"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPItemLine[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       4,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QPen, 0x00015103, uint(-1), 0,
       2, QMetaType::QPen, 0x00015103, uint(-1), 0,
       3, 0x80000000 | 4, 0x0001510b, uint(-1), 0,
       5, 0x80000000 | 4, 0x0001510b, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPItemLine::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractItem::staticMetaObject>(),
    qt_meta_stringdata_QCPItemLine.offsetsAndSizes,
    qt_meta_data_QCPItemLine,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPItemLine_t,
        // property 'pen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'selectedPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'head'
        QtPrivate::TypeAndForceComplete<QCPLineEnding, std::true_type>,
        // property 'tail'
        QtPrivate::TypeAndForceComplete<QCPLineEnding, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPItemLine, std::true_type>
    >,
    nullptr
} };

void QCPItemLine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPItemLine *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QPen*>(_v) = _t->pen(); break;
        case 1: *reinterpret_cast< QPen*>(_v) = _t->selectedPen(); break;
        case 2: *reinterpret_cast< QCPLineEnding*>(_v) = _t->head(); break;
        case 3: *reinterpret_cast< QCPLineEnding*>(_v) = _t->tail(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPItemLine *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPen(*reinterpret_cast< QPen*>(_v)); break;
        case 1: _t->setSelectedPen(*reinterpret_cast< QPen*>(_v)); break;
        case 2: _t->setHead(*reinterpret_cast< QCPLineEnding*>(_v)); break;
        case 3: _t->setTail(*reinterpret_cast< QCPLineEnding*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *QCPItemLine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPItemLine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPItemLine.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractItem::qt_metacast(_clname);
}

int QCPItemLine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
namespace {
struct qt_meta_stringdata_QCPItemCurve_t {
    uint offsetsAndSizes[12];
    char stringdata0[13];
    char stringdata1[4];
    char stringdata2[12];
    char stringdata3[5];
    char stringdata4[14];
    char stringdata5[5];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPItemCurve_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPItemCurve_t qt_meta_stringdata_QCPItemCurve = {
    {
        QT_MOC_LITERAL(0, 12),  // "QCPItemCurve"
        QT_MOC_LITERAL(13, 3),  // "pen"
        QT_MOC_LITERAL(17, 11),  // "selectedPen"
        QT_MOC_LITERAL(29, 4),  // "head"
        QT_MOC_LITERAL(34, 13),  // "QCPLineEnding"
        QT_MOC_LITERAL(48, 4)   // "tail"
    },
    "QCPItemCurve",
    "pen",
    "selectedPen",
    "head",
    "QCPLineEnding",
    "tail"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPItemCurve[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       4,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QPen, 0x00015103, uint(-1), 0,
       2, QMetaType::QPen, 0x00015103, uint(-1), 0,
       3, 0x80000000 | 4, 0x0001510b, uint(-1), 0,
       5, 0x80000000 | 4, 0x0001510b, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPItemCurve::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractItem::staticMetaObject>(),
    qt_meta_stringdata_QCPItemCurve.offsetsAndSizes,
    qt_meta_data_QCPItemCurve,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPItemCurve_t,
        // property 'pen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'selectedPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'head'
        QtPrivate::TypeAndForceComplete<QCPLineEnding, std::true_type>,
        // property 'tail'
        QtPrivate::TypeAndForceComplete<QCPLineEnding, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPItemCurve, std::true_type>
    >,
    nullptr
} };

void QCPItemCurve::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPItemCurve *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QPen*>(_v) = _t->pen(); break;
        case 1: *reinterpret_cast< QPen*>(_v) = _t->selectedPen(); break;
        case 2: *reinterpret_cast< QCPLineEnding*>(_v) = _t->head(); break;
        case 3: *reinterpret_cast< QCPLineEnding*>(_v) = _t->tail(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPItemCurve *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPen(*reinterpret_cast< QPen*>(_v)); break;
        case 1: _t->setSelectedPen(*reinterpret_cast< QPen*>(_v)); break;
        case 2: _t->setHead(*reinterpret_cast< QCPLineEnding*>(_v)); break;
        case 3: _t->setTail(*reinterpret_cast< QCPLineEnding*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *QCPItemCurve::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPItemCurve::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPItemCurve.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractItem::qt_metacast(_clname);
}

int QCPItemCurve::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
namespace {
struct qt_meta_stringdata_QCPItemRect_t {
    uint offsetsAndSizes[10];
    char stringdata0[12];
    char stringdata1[4];
    char stringdata2[12];
    char stringdata3[6];
    char stringdata4[14];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPItemRect_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPItemRect_t qt_meta_stringdata_QCPItemRect = {
    {
        QT_MOC_LITERAL(0, 11),  // "QCPItemRect"
        QT_MOC_LITERAL(12, 3),  // "pen"
        QT_MOC_LITERAL(16, 11),  // "selectedPen"
        QT_MOC_LITERAL(28, 5),  // "brush"
        QT_MOC_LITERAL(34, 13)   // "selectedBrush"
    },
    "QCPItemRect",
    "pen",
    "selectedPen",
    "brush",
    "selectedBrush"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPItemRect[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       4,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QPen, 0x00015103, uint(-1), 0,
       2, QMetaType::QPen, 0x00015103, uint(-1), 0,
       3, QMetaType::QBrush, 0x00015103, uint(-1), 0,
       4, QMetaType::QBrush, 0x00015103, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPItemRect::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractItem::staticMetaObject>(),
    qt_meta_stringdata_QCPItemRect.offsetsAndSizes,
    qt_meta_data_QCPItemRect,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPItemRect_t,
        // property 'pen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'selectedPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'brush'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // property 'selectedBrush'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPItemRect, std::true_type>
    >,
    nullptr
} };

void QCPItemRect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPItemRect *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QPen*>(_v) = _t->pen(); break;
        case 1: *reinterpret_cast< QPen*>(_v) = _t->selectedPen(); break;
        case 2: *reinterpret_cast< QBrush*>(_v) = _t->brush(); break;
        case 3: *reinterpret_cast< QBrush*>(_v) = _t->selectedBrush(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPItemRect *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPen(*reinterpret_cast< QPen*>(_v)); break;
        case 1: _t->setSelectedPen(*reinterpret_cast< QPen*>(_v)); break;
        case 2: _t->setBrush(*reinterpret_cast< QBrush*>(_v)); break;
        case 3: _t->setSelectedBrush(*reinterpret_cast< QBrush*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *QCPItemRect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPItemRect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPItemRect.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractItem::qt_metacast(_clname);
}

int QCPItemRect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
namespace {
struct qt_meta_stringdata_QCPItemText_t {
    uint offsetsAndSizes[32];
    char stringdata0[12];
    char stringdata1[6];
    char stringdata2[14];
    char stringdata3[4];
    char stringdata4[12];
    char stringdata5[6];
    char stringdata6[14];
    char stringdata7[5];
    char stringdata8[13];
    char stringdata9[5];
    char stringdata10[18];
    char stringdata11[14];
    char stringdata12[14];
    char stringdata13[9];
    char stringdata14[8];
    char stringdata15[9];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPItemText_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPItemText_t qt_meta_stringdata_QCPItemText = {
    {
        QT_MOC_LITERAL(0, 11),  // "QCPItemText"
        QT_MOC_LITERAL(12, 5),  // "color"
        QT_MOC_LITERAL(18, 13),  // "selectedColor"
        QT_MOC_LITERAL(32, 3),  // "pen"
        QT_MOC_LITERAL(36, 11),  // "selectedPen"
        QT_MOC_LITERAL(48, 5),  // "brush"
        QT_MOC_LITERAL(54, 13),  // "selectedBrush"
        QT_MOC_LITERAL(68, 4),  // "font"
        QT_MOC_LITERAL(73, 12),  // "selectedFont"
        QT_MOC_LITERAL(86, 4),  // "text"
        QT_MOC_LITERAL(91, 17),  // "positionAlignment"
        QT_MOC_LITERAL(109, 13),  // "Qt::Alignment"
        QT_MOC_LITERAL(123, 13),  // "textAlignment"
        QT_MOC_LITERAL(137, 8),  // "rotation"
        QT_MOC_LITERAL(146, 7),  // "padding"
        QT_MOC_LITERAL(154, 8)   // "QMargins"
    },
    "QCPItemText",
    "color",
    "selectedColor",
    "pen",
    "selectedPen",
    "brush",
    "selectedBrush",
    "font",
    "selectedFont",
    "text",
    "positionAlignment",
    "Qt::Alignment",
    "textAlignment",
    "rotation",
    "padding",
    "QMargins"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPItemText[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
      13,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QColor, 0x00015103, uint(-1), 0,
       2, QMetaType::QColor, 0x00015103, uint(-1), 0,
       3, QMetaType::QPen, 0x00015103, uint(-1), 0,
       4, QMetaType::QPen, 0x00015103, uint(-1), 0,
       5, QMetaType::QBrush, 0x00015103, uint(-1), 0,
       6, QMetaType::QBrush, 0x00015103, uint(-1), 0,
       7, QMetaType::QFont, 0x00015103, uint(-1), 0,
       8, QMetaType::QFont, 0x00015103, uint(-1), 0,
       9, QMetaType::QString, 0x00015103, uint(-1), 0,
      10, 0x80000000 | 11, 0x0001510b, uint(-1), 0,
      12, 0x80000000 | 11, 0x0001510b, uint(-1), 0,
      13, QMetaType::Double, 0x00015103, uint(-1), 0,
      14, 0x80000000 | 15, 0x0001510b, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPItemText::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractItem::staticMetaObject>(),
    qt_meta_stringdata_QCPItemText.offsetsAndSizes,
    qt_meta_data_QCPItemText,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPItemText_t,
        // property 'color'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'selectedColor'
        QtPrivate::TypeAndForceComplete<QColor, std::true_type>,
        // property 'pen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'selectedPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'brush'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // property 'selectedBrush'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // property 'font'
        QtPrivate::TypeAndForceComplete<QFont, std::true_type>,
        // property 'selectedFont'
        QtPrivate::TypeAndForceComplete<QFont, std::true_type>,
        // property 'text'
        QtPrivate::TypeAndForceComplete<QString, std::true_type>,
        // property 'positionAlignment'
        QtPrivate::TypeAndForceComplete<Qt::Alignment, std::true_type>,
        // property 'textAlignment'
        QtPrivate::TypeAndForceComplete<Qt::Alignment, std::true_type>,
        // property 'rotation'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'padding'
        QtPrivate::TypeAndForceComplete<QMargins, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPItemText, std::true_type>
    >,
    nullptr
} };

void QCPItemText::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPItemText *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QColor*>(_v) = _t->color(); break;
        case 1: *reinterpret_cast< QColor*>(_v) = _t->selectedColor(); break;
        case 2: *reinterpret_cast< QPen*>(_v) = _t->pen(); break;
        case 3: *reinterpret_cast< QPen*>(_v) = _t->selectedPen(); break;
        case 4: *reinterpret_cast< QBrush*>(_v) = _t->brush(); break;
        case 5: *reinterpret_cast< QBrush*>(_v) = _t->selectedBrush(); break;
        case 6: *reinterpret_cast< QFont*>(_v) = _t->font(); break;
        case 7: *reinterpret_cast< QFont*>(_v) = _t->selectedFont(); break;
        case 8: *reinterpret_cast< QString*>(_v) = _t->text(); break;
        case 9: *reinterpret_cast< Qt::Alignment*>(_v) = _t->positionAlignment(); break;
        case 10: *reinterpret_cast< Qt::Alignment*>(_v) = _t->textAlignment(); break;
        case 11: *reinterpret_cast< double*>(_v) = _t->rotation(); break;
        case 12: *reinterpret_cast< QMargins*>(_v) = _t->padding(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPItemText *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setColor(*reinterpret_cast< QColor*>(_v)); break;
        case 1: _t->setSelectedColor(*reinterpret_cast< QColor*>(_v)); break;
        case 2: _t->setPen(*reinterpret_cast< QPen*>(_v)); break;
        case 3: _t->setSelectedPen(*reinterpret_cast< QPen*>(_v)); break;
        case 4: _t->setBrush(*reinterpret_cast< QBrush*>(_v)); break;
        case 5: _t->setSelectedBrush(*reinterpret_cast< QBrush*>(_v)); break;
        case 6: _t->setFont(*reinterpret_cast< QFont*>(_v)); break;
        case 7: _t->setSelectedFont(*reinterpret_cast< QFont*>(_v)); break;
        case 8: _t->setText(*reinterpret_cast< QString*>(_v)); break;
        case 9: _t->setPositionAlignment(*reinterpret_cast< Qt::Alignment*>(_v)); break;
        case 10: _t->setTextAlignment(*reinterpret_cast< Qt::Alignment*>(_v)); break;
        case 11: _t->setRotation(*reinterpret_cast< double*>(_v)); break;
        case 12: _t->setPadding(*reinterpret_cast< QMargins*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *QCPItemText::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPItemText::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPItemText.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractItem::qt_metacast(_clname);
}

int QCPItemText::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
namespace {
struct qt_meta_stringdata_QCPItemEllipse_t {
    uint offsetsAndSizes[10];
    char stringdata0[15];
    char stringdata1[4];
    char stringdata2[12];
    char stringdata3[6];
    char stringdata4[14];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPItemEllipse_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPItemEllipse_t qt_meta_stringdata_QCPItemEllipse = {
    {
        QT_MOC_LITERAL(0, 14),  // "QCPItemEllipse"
        QT_MOC_LITERAL(15, 3),  // "pen"
        QT_MOC_LITERAL(19, 11),  // "selectedPen"
        QT_MOC_LITERAL(31, 5),  // "brush"
        QT_MOC_LITERAL(37, 13)   // "selectedBrush"
    },
    "QCPItemEllipse",
    "pen",
    "selectedPen",
    "brush",
    "selectedBrush"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPItemEllipse[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       4,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QPen, 0x00015103, uint(-1), 0,
       2, QMetaType::QPen, 0x00015103, uint(-1), 0,
       3, QMetaType::QBrush, 0x00015103, uint(-1), 0,
       4, QMetaType::QBrush, 0x00015103, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPItemEllipse::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractItem::staticMetaObject>(),
    qt_meta_stringdata_QCPItemEllipse.offsetsAndSizes,
    qt_meta_data_QCPItemEllipse,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPItemEllipse_t,
        // property 'pen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'selectedPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'brush'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // property 'selectedBrush'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPItemEllipse, std::true_type>
    >,
    nullptr
} };

void QCPItemEllipse::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPItemEllipse *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QPen*>(_v) = _t->pen(); break;
        case 1: *reinterpret_cast< QPen*>(_v) = _t->selectedPen(); break;
        case 2: *reinterpret_cast< QBrush*>(_v) = _t->brush(); break;
        case 3: *reinterpret_cast< QBrush*>(_v) = _t->selectedBrush(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPItemEllipse *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPen(*reinterpret_cast< QPen*>(_v)); break;
        case 1: _t->setSelectedPen(*reinterpret_cast< QPen*>(_v)); break;
        case 2: _t->setBrush(*reinterpret_cast< QBrush*>(_v)); break;
        case 3: _t->setSelectedBrush(*reinterpret_cast< QBrush*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *QCPItemEllipse::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPItemEllipse::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPItemEllipse.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractItem::qt_metacast(_clname);
}

int QCPItemEllipse::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
namespace {
struct qt_meta_stringdata_QCPItemPixmap_t {
    uint offsetsAndSizes[18];
    char stringdata0[14];
    char stringdata1[7];
    char stringdata2[7];
    char stringdata3[16];
    char stringdata4[20];
    char stringdata5[19];
    char stringdata6[23];
    char stringdata7[4];
    char stringdata8[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPItemPixmap_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPItemPixmap_t qt_meta_stringdata_QCPItemPixmap = {
    {
        QT_MOC_LITERAL(0, 13),  // "QCPItemPixmap"
        QT_MOC_LITERAL(14, 6),  // "pixmap"
        QT_MOC_LITERAL(21, 6),  // "scaled"
        QT_MOC_LITERAL(28, 15),  // "aspectRatioMode"
        QT_MOC_LITERAL(44, 19),  // "Qt::AspectRatioMode"
        QT_MOC_LITERAL(64, 18),  // "transformationMode"
        QT_MOC_LITERAL(83, 22),  // "Qt::TransformationMode"
        QT_MOC_LITERAL(106, 3),  // "pen"
        QT_MOC_LITERAL(110, 11)   // "selectedPen"
    },
    "QCPItemPixmap",
    "pixmap",
    "scaled",
    "aspectRatioMode",
    "Qt::AspectRatioMode",
    "transformationMode",
    "Qt::TransformationMode",
    "pen",
    "selectedPen"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPItemPixmap[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       6,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QPixmap, 0x00015103, uint(-1), 0,
       2, QMetaType::Bool, 0x00015103, uint(-1), 0,
       3, 0x80000000 | 4, 0x00015009, uint(-1), 0,
       5, 0x80000000 | 6, 0x00015009, uint(-1), 0,
       7, QMetaType::QPen, 0x00015103, uint(-1), 0,
       8, QMetaType::QPen, 0x00015103, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPItemPixmap::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractItem::staticMetaObject>(),
    qt_meta_stringdata_QCPItemPixmap.offsetsAndSizes,
    qt_meta_data_QCPItemPixmap,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPItemPixmap_t,
        // property 'pixmap'
        QtPrivate::TypeAndForceComplete<QPixmap, std::true_type>,
        // property 'scaled'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'aspectRatioMode'
        QtPrivate::TypeAndForceComplete<Qt::AspectRatioMode, std::true_type>,
        // property 'transformationMode'
        QtPrivate::TypeAndForceComplete<Qt::TransformationMode, std::true_type>,
        // property 'pen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'selectedPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPItemPixmap, std::true_type>
    >,
    nullptr
} };

void QCPItemPixmap::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPItemPixmap *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QPixmap*>(_v) = _t->pixmap(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->scaled(); break;
        case 2: *reinterpret_cast< Qt::AspectRatioMode*>(_v) = _t->aspectRatioMode(); break;
        case 3: *reinterpret_cast< Qt::TransformationMode*>(_v) = _t->transformationMode(); break;
        case 4: *reinterpret_cast< QPen*>(_v) = _t->pen(); break;
        case 5: *reinterpret_cast< QPen*>(_v) = _t->selectedPen(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPItemPixmap *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPixmap(*reinterpret_cast< QPixmap*>(_v)); break;
        case 1: _t->setScaled(*reinterpret_cast< bool*>(_v)); break;
        case 4: _t->setPen(*reinterpret_cast< QPen*>(_v)); break;
        case 5: _t->setSelectedPen(*reinterpret_cast< QPen*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *QCPItemPixmap::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPItemPixmap::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPItemPixmap.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractItem::qt_metacast(_clname);
}

int QCPItemPixmap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
namespace {
struct qt_meta_stringdata_QCPItemTracer_t {
    uint offsetsAndSizes[34];
    char stringdata0[14];
    char stringdata1[4];
    char stringdata2[12];
    char stringdata3[6];
    char stringdata4[14];
    char stringdata5[5];
    char stringdata6[6];
    char stringdata7[12];
    char stringdata8[6];
    char stringdata9[10];
    char stringdata10[9];
    char stringdata11[14];
    char stringdata12[7];
    char stringdata13[7];
    char stringdata14[12];
    char stringdata15[9];
    char stringdata16[9];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPItemTracer_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPItemTracer_t qt_meta_stringdata_QCPItemTracer = {
    {
        QT_MOC_LITERAL(0, 13),  // "QCPItemTracer"
        QT_MOC_LITERAL(14, 3),  // "pen"
        QT_MOC_LITERAL(18, 11),  // "selectedPen"
        QT_MOC_LITERAL(30, 5),  // "brush"
        QT_MOC_LITERAL(36, 13),  // "selectedBrush"
        QT_MOC_LITERAL(50, 4),  // "size"
        QT_MOC_LITERAL(55, 5),  // "style"
        QT_MOC_LITERAL(61, 11),  // "TracerStyle"
        QT_MOC_LITERAL(73, 5),  // "graph"
        QT_MOC_LITERAL(79, 9),  // "QCPGraph*"
        QT_MOC_LITERAL(89, 8),  // "graphKey"
        QT_MOC_LITERAL(98, 13),  // "interpolating"
        QT_MOC_LITERAL(112, 6),  // "tsNone"
        QT_MOC_LITERAL(119, 6),  // "tsPlus"
        QT_MOC_LITERAL(126, 11),  // "tsCrosshair"
        QT_MOC_LITERAL(138, 8),  // "tsCircle"
        QT_MOC_LITERAL(147, 8)   // "tsSquare"
    },
    "QCPItemTracer",
    "pen",
    "selectedPen",
    "brush",
    "selectedBrush",
    "size",
    "style",
    "TracerStyle",
    "graph",
    "QCPGraph*",
    "graphKey",
    "interpolating",
    "tsNone",
    "tsPlus",
    "tsCrosshair",
    "tsCircle",
    "tsSquare"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPItemTracer[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       9,   14, // properties
       1,   59, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QPen, 0x00015103, uint(-1), 0,
       2, QMetaType::QPen, 0x00015103, uint(-1), 0,
       3, QMetaType::QBrush, 0x00015103, uint(-1), 0,
       4, QMetaType::QBrush, 0x00015103, uint(-1), 0,
       5, QMetaType::Double, 0x00015103, uint(-1), 0,
       6, 0x80000000 | 7, 0x0001510b, uint(-1), 0,
       8, 0x80000000 | 9, 0x0001510b, uint(-1), 0,
      10, QMetaType::Double, 0x00015103, uint(-1), 0,
      11, QMetaType::Bool, 0x00015103, uint(-1), 0,

 // enums: name, alias, flags, count, data
       7,    7, 0x0,    5,   64,

 // enum data: key, value
      12, uint(QCPItemTracer::tsNone),
      13, uint(QCPItemTracer::tsPlus),
      14, uint(QCPItemTracer::tsCrosshair),
      15, uint(QCPItemTracer::tsCircle),
      16, uint(QCPItemTracer::tsSquare),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPItemTracer::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractItem::staticMetaObject>(),
    qt_meta_stringdata_QCPItemTracer.offsetsAndSizes,
    qt_meta_data_QCPItemTracer,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPItemTracer_t,
        // property 'pen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'selectedPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'brush'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // property 'selectedBrush'
        QtPrivate::TypeAndForceComplete<QBrush, std::true_type>,
        // property 'size'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'style'
        QtPrivate::TypeAndForceComplete<TracerStyle, std::true_type>,
        // property 'graph'
        QtPrivate::TypeAndForceComplete<QCPGraph*, std::true_type>,
        // property 'graphKey'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'interpolating'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPItemTracer, std::true_type>
    >,
    nullptr
} };

void QCPItemTracer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPGraph* >(); break;
        }
    }
else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPItemTracer *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QPen*>(_v) = _t->pen(); break;
        case 1: *reinterpret_cast< QPen*>(_v) = _t->selectedPen(); break;
        case 2: *reinterpret_cast< QBrush*>(_v) = _t->brush(); break;
        case 3: *reinterpret_cast< QBrush*>(_v) = _t->selectedBrush(); break;
        case 4: *reinterpret_cast< double*>(_v) = _t->size(); break;
        case 5: *reinterpret_cast< TracerStyle*>(_v) = _t->style(); break;
        case 6: *reinterpret_cast< QCPGraph**>(_v) = _t->graph(); break;
        case 7: *reinterpret_cast< double*>(_v) = _t->graphKey(); break;
        case 8: *reinterpret_cast< bool*>(_v) = _t->interpolating(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPItemTracer *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPen(*reinterpret_cast< QPen*>(_v)); break;
        case 1: _t->setSelectedPen(*reinterpret_cast< QPen*>(_v)); break;
        case 2: _t->setBrush(*reinterpret_cast< QBrush*>(_v)); break;
        case 3: _t->setSelectedBrush(*reinterpret_cast< QBrush*>(_v)); break;
        case 4: _t->setSize(*reinterpret_cast< double*>(_v)); break;
        case 5: _t->setStyle(*reinterpret_cast< TracerStyle*>(_v)); break;
        case 6: _t->setGraph(*reinterpret_cast< QCPGraph**>(_v)); break;
        case 7: _t->setGraphKey(*reinterpret_cast< double*>(_v)); break;
        case 8: _t->setInterpolating(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_o;
}

const QMetaObject *QCPItemTracer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPItemTracer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPItemTracer.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractItem::qt_metacast(_clname);
}

int QCPItemTracer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
namespace {
struct qt_meta_stringdata_QCPItemBracket_t {
    uint offsetsAndSizes[20];
    char stringdata0[15];
    char stringdata1[4];
    char stringdata2[12];
    char stringdata3[7];
    char stringdata4[6];
    char stringdata5[13];
    char stringdata6[9];
    char stringdata7[8];
    char stringdata8[8];
    char stringdata9[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPItemBracket_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPItemBracket_t qt_meta_stringdata_QCPItemBracket = {
    {
        QT_MOC_LITERAL(0, 14),  // "QCPItemBracket"
        QT_MOC_LITERAL(15, 3),  // "pen"
        QT_MOC_LITERAL(19, 11),  // "selectedPen"
        QT_MOC_LITERAL(31, 6),  // "length"
        QT_MOC_LITERAL(38, 5),  // "style"
        QT_MOC_LITERAL(44, 12),  // "BracketStyle"
        QT_MOC_LITERAL(57, 8),  // "bsSquare"
        QT_MOC_LITERAL(66, 7),  // "bsRound"
        QT_MOC_LITERAL(74, 7),  // "bsCurly"
        QT_MOC_LITERAL(82, 14)   // "bsCalligraphic"
    },
    "QCPItemBracket",
    "pen",
    "selectedPen",
    "length",
    "style",
    "BracketStyle",
    "bsSquare",
    "bsRound",
    "bsCurly",
    "bsCalligraphic"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPItemBracket[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       4,   14, // properties
       1,   34, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::QPen, 0x00015103, uint(-1), 0,
       2, QMetaType::QPen, 0x00015103, uint(-1), 0,
       3, QMetaType::Double, 0x00015103, uint(-1), 0,
       4, 0x80000000 | 5, 0x0001510b, uint(-1), 0,

 // enums: name, alias, flags, count, data
       5,    5, 0x0,    4,   39,

 // enum data: key, value
       6, uint(QCPItemBracket::bsSquare),
       7, uint(QCPItemBracket::bsRound),
       8, uint(QCPItemBracket::bsCurly),
       9, uint(QCPItemBracket::bsCalligraphic),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPItemBracket::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractItem::staticMetaObject>(),
    qt_meta_stringdata_QCPItemBracket.offsetsAndSizes,
    qt_meta_data_QCPItemBracket,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPItemBracket_t,
        // property 'pen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'selectedPen'
        QtPrivate::TypeAndForceComplete<QPen, std::true_type>,
        // property 'length'
        QtPrivate::TypeAndForceComplete<double, std::true_type>,
        // property 'style'
        QtPrivate::TypeAndForceComplete<BracketStyle, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPItemBracket, std::true_type>
    >,
    nullptr
} };

void QCPItemBracket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QCPItemBracket *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QPen*>(_v) = _t->pen(); break;
        case 1: *reinterpret_cast< QPen*>(_v) = _t->selectedPen(); break;
        case 2: *reinterpret_cast< double*>(_v) = _t->length(); break;
        case 3: *reinterpret_cast< BracketStyle*>(_v) = _t->style(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<QCPItemBracket *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPen(*reinterpret_cast< QPen*>(_v)); break;
        case 1: _t->setSelectedPen(*reinterpret_cast< QPen*>(_v)); break;
        case 2: _t->setLength(*reinterpret_cast< double*>(_v)); break;
        case 3: _t->setStyle(*reinterpret_cast< BracketStyle*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *QCPItemBracket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPItemBracket::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPItemBracket.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractItem::qt_metacast(_clname);
}

int QCPItemBracket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
namespace {
struct qt_meta_stringdata_QCPPolarAxisRadial_t {
    uint offsetsAndSizes[72];
    char stringdata0[19];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[9];
    char stringdata5[9];
    char stringdata6[17];
    char stringdata7[30];
    char stringdata8[10];
    char stringdata9[17];
    char stringdata10[36];
    char stringdata11[6];
    char stringdata12[18];
    char stringdata13[13];
    char stringdata14[5];
    char stringdata15[9];
    char stringdata16[6];
    char stringdata17[19];
    char stringdata18[16];
    char stringdata19[17];
    char stringdata20[14];
    char stringdata21[15];
    char stringdata22[11];
    char stringdata23[14];
    char stringdata24[10];
    char stringdata25[9];
    char stringdata26[14];
    char stringdata27[15];
    char stringdata28[7];
    char stringdata29[7];
    char stringdata30[13];
    char stringdata31[12];
    char stringdata32[16];
    char stringdata33[10];
    char stringdata34[10];
    char stringdata35[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPPolarAxisRadial_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPPolarAxisRadial_t qt_meta_stringdata_QCPPolarAxisRadial = {
    {
        QT_MOC_LITERAL(0, 18),  // "QCPPolarAxisRadial"
        QT_MOC_LITERAL(19, 12),  // "rangeChanged"
        QT_MOC_LITERAL(32, 0),  // ""
        QT_MOC_LITERAL(33, 8),  // "QCPRange"
        QT_MOC_LITERAL(42, 8),  // "newRange"
        QT_MOC_LITERAL(51, 8),  // "oldRange"
        QT_MOC_LITERAL(60, 16),  // "scaleTypeChanged"
        QT_MOC_LITERAL(77, 29),  // "QCPPolarAxisRadial::ScaleType"
        QT_MOC_LITERAL(107, 9),  // "scaleType"
        QT_MOC_LITERAL(117, 16),  // "selectionChanged"
        QT_MOC_LITERAL(134, 35),  // "QCPPolarAxisRadial::Selectabl..."
        QT_MOC_LITERAL(170, 5),  // "parts"
        QT_MOC_LITERAL(176, 17),  // "selectableChanged"
        QT_MOC_LITERAL(194, 12),  // "setScaleType"
        QT_MOC_LITERAL(207, 4),  // "type"
        QT_MOC_LITERAL(212, 8),  // "setRange"
        QT_MOC_LITERAL(221, 5),  // "range"
        QT_MOC_LITERAL(227, 18),  // "setSelectableParts"
        QT_MOC_LITERAL(246, 15),  // "selectableParts"
        QT_MOC_LITERAL(262, 16),  // "setSelectedParts"
        QT_MOC_LITERAL(279, 13),  // "selectedParts"
        QT_MOC_LITERAL(293, 14),  // "AngleReference"
        QT_MOC_LITERAL(308, 10),  // "arAbsolute"
        QT_MOC_LITERAL(319, 13),  // "arAngularAxis"
        QT_MOC_LITERAL(333, 9),  // "ScaleType"
        QT_MOC_LITERAL(343, 8),  // "stLinear"
        QT_MOC_LITERAL(352, 13),  // "stLogarithmic"
        QT_MOC_LITERAL(366, 14),  // "SelectablePart"
        QT_MOC_LITERAL(381, 6),  // "spNone"
        QT_MOC_LITERAL(388, 6),  // "spAxis"
        QT_MOC_LITERAL(395, 12),  // "spTickLabels"
        QT_MOC_LITERAL(408, 11),  // "spAxisLabel"
        QT_MOC_LITERAL(420, 15),  // "SelectableParts"
        QT_MOC_LITERAL(436, 9),  // "LabelMode"
        QT_MOC_LITERAL(446, 9),  // "lmUpright"
        QT_MOC_LITERAL(456, 9)   // "lmRotated"
    },
    "QCPPolarAxisRadial",
    "rangeChanged",
    "",
    "QCPRange",
    "newRange",
    "oldRange",
    "scaleTypeChanged",
    "QCPPolarAxisRadial::ScaleType",
    "scaleType",
    "selectionChanged",
    "QCPPolarAxisRadial::SelectableParts",
    "parts",
    "selectableChanged",
    "setScaleType",
    "type",
    "setRange",
    "range",
    "setSelectableParts",
    "selectableParts",
    "setSelectedParts",
    "selectedParts",
    "AngleReference",
    "arAbsolute",
    "arAngularAxis",
    "ScaleType",
    "stLinear",
    "stLogarithmic",
    "SelectablePart",
    "spNone",
    "spAxis",
    "spTickLabels",
    "spAxisLabel",
    "SelectableParts",
    "LabelMode",
    "lmUpright",
    "lmRotated"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPPolarAxisRadial[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       5,   97, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   68,    2, 0x06,    1 /* Public */,
       1,    2,   71,    2, 0x06,    3 /* Public */,
       6,    1,   76,    2, 0x06,    6 /* Public */,
       9,    1,   79,    2, 0x06,    8 /* Public */,
      12,    1,   82,    2, 0x06,   10 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      13,    1,   85,    2, 0x0a,   12 /* Public */,
      15,    1,   88,    2, 0x0a,   14 /* Public */,
      17,    1,   91,    2, 0x0a,   16 /* Public */,
      19,    1,   94,    2, 0x0a,   18 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 10,   11,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,   14,
    QMetaType::Void, 0x80000000 | 3,   16,
    QMetaType::Void, 0x80000000 | 10,   18,
    QMetaType::Void, 0x80000000 | 10,   20,

 // enums: name, alias, flags, count, data
      21,   21, 0x0,    2,  122,
      24,   24, 0x0,    2,  126,
      27,   27, 0x0,    4,  130,
      32,   27, 0x1,    4,  138,
      33,   33, 0x0,    2,  146,

 // enum data: key, value
      22, uint(QCPPolarAxisRadial::arAbsolute),
      23, uint(QCPPolarAxisRadial::arAngularAxis),
      25, uint(QCPPolarAxisRadial::stLinear),
      26, uint(QCPPolarAxisRadial::stLogarithmic),
      28, uint(QCPPolarAxisRadial::spNone),
      29, uint(QCPPolarAxisRadial::spAxis),
      30, uint(QCPPolarAxisRadial::spTickLabels),
      31, uint(QCPPolarAxisRadial::spAxisLabel),
      28, uint(QCPPolarAxisRadial::spNone),
      29, uint(QCPPolarAxisRadial::spAxis),
      30, uint(QCPPolarAxisRadial::spTickLabels),
      31, uint(QCPPolarAxisRadial::spAxisLabel),
      34, uint(QCPPolarAxisRadial::lmUpright),
      35, uint(QCPPolarAxisRadial::lmRotated),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPPolarAxisRadial::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayerable::staticMetaObject>(),
    qt_meta_stringdata_QCPPolarAxisRadial.offsetsAndSizes,
    qt_meta_data_QCPPolarAxisRadial,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPPolarAxisRadial_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPPolarAxisRadial, std::true_type>,
        // method 'rangeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        // method 'rangeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        // method 'scaleTypeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPPolarAxisRadial::ScaleType, std::false_type>,
        // method 'selectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPPolarAxisRadial::SelectableParts &, std::false_type>,
        // method 'selectableChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPPolarAxisRadial::SelectableParts &, std::false_type>,
        // method 'setScaleType'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPPolarAxisRadial::ScaleType, std::false_type>,
        // method 'setRange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        // method 'setSelectableParts'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPPolarAxisRadial::SelectableParts &, std::false_type>,
        // method 'setSelectedParts'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPPolarAxisRadial::SelectableParts &, std::false_type>
    >,
    nullptr
} };

void QCPPolarAxisRadial::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCPPolarAxisRadial *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->rangeChanged((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1]))); break;
        case 1: _t->rangeChanged((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[2]))); break;
        case 2: _t->scaleTypeChanged((*reinterpret_cast< std::add_pointer_t<QCPPolarAxisRadial::ScaleType>>(_a[1]))); break;
        case 3: _t->selectionChanged((*reinterpret_cast< std::add_pointer_t<QCPPolarAxisRadial::SelectableParts>>(_a[1]))); break;
        case 4: _t->selectableChanged((*reinterpret_cast< std::add_pointer_t<QCPPolarAxisRadial::SelectableParts>>(_a[1]))); break;
        case 5: _t->setScaleType((*reinterpret_cast< std::add_pointer_t<QCPPolarAxisRadial::ScaleType>>(_a[1]))); break;
        case 6: _t->setRange((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1]))); break;
        case 7: _t->setSelectableParts((*reinterpret_cast< std::add_pointer_t<QCPPolarAxisRadial::SelectableParts>>(_a[1]))); break;
        case 8: _t->setSelectedParts((*reinterpret_cast< std::add_pointer_t<QCPPolarAxisRadial::SelectableParts>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPPolarAxisRadial::ScaleType >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPPolarAxisRadial::ScaleType >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QCPPolarAxisRadial::*)(const QCPRange & );
            if (_t _q_method = &QCPPolarAxisRadial::rangeChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QCPPolarAxisRadial::*)(const QCPRange & , const QCPRange & );
            if (_t _q_method = &QCPPolarAxisRadial::rangeChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QCPPolarAxisRadial::*)(QCPPolarAxisRadial::ScaleType );
            if (_t _q_method = &QCPPolarAxisRadial::scaleTypeChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (QCPPolarAxisRadial::*)(const QCPPolarAxisRadial::SelectableParts & );
            if (_t _q_method = &QCPPolarAxisRadial::selectionChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (QCPPolarAxisRadial::*)(const QCPPolarAxisRadial::SelectableParts & );
            if (_t _q_method = &QCPPolarAxisRadial::selectableChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject *QCPPolarAxisRadial::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPPolarAxisRadial::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPPolarAxisRadial.stringdata0))
        return static_cast<void*>(this);
    return QCPLayerable::qt_metacast(_clname);
}

int QCPPolarAxisRadial::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayerable::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void QCPPolarAxisRadial::rangeChanged(const QCPRange & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCPPolarAxisRadial::rangeChanged(const QCPRange & _t1, const QCPRange & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QCPPolarAxisRadial::scaleTypeChanged(QCPPolarAxisRadial::ScaleType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QCPPolarAxisRadial::selectionChanged(const QCPPolarAxisRadial::SelectableParts & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QCPPolarAxisRadial::selectableChanged(const QCPPolarAxisRadial::SelectableParts & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
namespace {
struct qt_meta_stringdata_QCPPolarAxisAngular_t {
    uint offsetsAndSizes[50];
    char stringdata0[20];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[9];
    char stringdata5[9];
    char stringdata6[17];
    char stringdata7[37];
    char stringdata8[6];
    char stringdata9[18];
    char stringdata10[9];
    char stringdata11[6];
    char stringdata12[19];
    char stringdata13[16];
    char stringdata14[17];
    char stringdata15[14];
    char stringdata16[15];
    char stringdata17[7];
    char stringdata18[7];
    char stringdata19[13];
    char stringdata20[12];
    char stringdata21[16];
    char stringdata22[10];
    char stringdata23[10];
    char stringdata24[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPPolarAxisAngular_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPPolarAxisAngular_t qt_meta_stringdata_QCPPolarAxisAngular = {
    {
        QT_MOC_LITERAL(0, 19),  // "QCPPolarAxisAngular"
        QT_MOC_LITERAL(20, 12),  // "rangeChanged"
        QT_MOC_LITERAL(33, 0),  // ""
        QT_MOC_LITERAL(34, 8),  // "QCPRange"
        QT_MOC_LITERAL(43, 8),  // "newRange"
        QT_MOC_LITERAL(52, 8),  // "oldRange"
        QT_MOC_LITERAL(61, 16),  // "selectionChanged"
        QT_MOC_LITERAL(78, 36),  // "QCPPolarAxisAngular::Selectab..."
        QT_MOC_LITERAL(115, 5),  // "parts"
        QT_MOC_LITERAL(121, 17),  // "selectableChanged"
        QT_MOC_LITERAL(139, 8),  // "setRange"
        QT_MOC_LITERAL(148, 5),  // "range"
        QT_MOC_LITERAL(154, 18),  // "setSelectableParts"
        QT_MOC_LITERAL(173, 15),  // "selectableParts"
        QT_MOC_LITERAL(189, 16),  // "setSelectedParts"
        QT_MOC_LITERAL(206, 13),  // "selectedParts"
        QT_MOC_LITERAL(220, 14),  // "SelectablePart"
        QT_MOC_LITERAL(235, 6),  // "spNone"
        QT_MOC_LITERAL(242, 6),  // "spAxis"
        QT_MOC_LITERAL(249, 12),  // "spTickLabels"
        QT_MOC_LITERAL(262, 11),  // "spAxisLabel"
        QT_MOC_LITERAL(274, 15),  // "SelectableParts"
        QT_MOC_LITERAL(290, 9),  // "LabelMode"
        QT_MOC_LITERAL(300, 9),  // "lmUpright"
        QT_MOC_LITERAL(310, 9)   // "lmRotated"
    },
    "QCPPolarAxisAngular",
    "rangeChanged",
    "",
    "QCPRange",
    "newRange",
    "oldRange",
    "selectionChanged",
    "QCPPolarAxisAngular::SelectableParts",
    "parts",
    "selectableChanged",
    "setRange",
    "range",
    "setSelectableParts",
    "selectableParts",
    "setSelectedParts",
    "selectedParts",
    "SelectablePart",
    "spNone",
    "spAxis",
    "spTickLabels",
    "spAxisLabel",
    "SelectableParts",
    "LabelMode",
    "lmUpright",
    "lmRotated"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPPolarAxisAngular[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       3,   79, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   56,    2, 0x06,    1 /* Public */,
       1,    2,   59,    2, 0x06,    3 /* Public */,
       6,    1,   64,    2, 0x06,    6 /* Public */,
       9,    1,   67,    2, 0x06,    8 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      10,    1,   70,    2, 0x0a,   10 /* Public */,
      12,    1,   73,    2, 0x0a,   12 /* Public */,
      14,    1,   76,    2, 0x0a,   14 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,   11,
    QMetaType::Void, 0x80000000 | 7,   13,
    QMetaType::Void, 0x80000000 | 7,   15,

 // enums: name, alias, flags, count, data
      16,   16, 0x0,    4,   94,
      21,   16, 0x1,    4,  102,
      22,   22, 0x0,    2,  110,

 // enum data: key, value
      17, uint(QCPPolarAxisAngular::spNone),
      18, uint(QCPPolarAxisAngular::spAxis),
      19, uint(QCPPolarAxisAngular::spTickLabels),
      20, uint(QCPPolarAxisAngular::spAxisLabel),
      17, uint(QCPPolarAxisAngular::spNone),
      18, uint(QCPPolarAxisAngular::spAxis),
      19, uint(QCPPolarAxisAngular::spTickLabels),
      20, uint(QCPPolarAxisAngular::spAxisLabel),
      23, uint(QCPPolarAxisAngular::lmUpright),
      24, uint(QCPPolarAxisAngular::lmRotated),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPPolarAxisAngular::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayoutElement::staticMetaObject>(),
    qt_meta_stringdata_QCPPolarAxisAngular.offsetsAndSizes,
    qt_meta_data_QCPPolarAxisAngular,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPPolarAxisAngular_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPPolarAxisAngular, std::true_type>,
        // method 'rangeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        // method 'rangeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        // method 'selectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPPolarAxisAngular::SelectableParts &, std::false_type>,
        // method 'selectableChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPPolarAxisAngular::SelectableParts &, std::false_type>,
        // method 'setRange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPRange &, std::false_type>,
        // method 'setSelectableParts'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPPolarAxisAngular::SelectableParts &, std::false_type>,
        // method 'setSelectedParts'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPPolarAxisAngular::SelectableParts &, std::false_type>
    >,
    nullptr
} };

void QCPPolarAxisAngular::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCPPolarAxisAngular *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->rangeChanged((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1]))); break;
        case 1: _t->rangeChanged((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[2]))); break;
        case 2: _t->selectionChanged((*reinterpret_cast< std::add_pointer_t<QCPPolarAxisAngular::SelectableParts>>(_a[1]))); break;
        case 3: _t->selectableChanged((*reinterpret_cast< std::add_pointer_t<QCPPolarAxisAngular::SelectableParts>>(_a[1]))); break;
        case 4: _t->setRange((*reinterpret_cast< std::add_pointer_t<QCPRange>>(_a[1]))); break;
        case 5: _t->setSelectableParts((*reinterpret_cast< std::add_pointer_t<QCPPolarAxisAngular::SelectableParts>>(_a[1]))); break;
        case 6: _t->setSelectedParts((*reinterpret_cast< std::add_pointer_t<QCPPolarAxisAngular::SelectableParts>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QCPPolarAxisAngular::*)(const QCPRange & );
            if (_t _q_method = &QCPPolarAxisAngular::rangeChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QCPPolarAxisAngular::*)(const QCPRange & , const QCPRange & );
            if (_t _q_method = &QCPPolarAxisAngular::rangeChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QCPPolarAxisAngular::*)(const QCPPolarAxisAngular::SelectableParts & );
            if (_t _q_method = &QCPPolarAxisAngular::selectionChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (QCPPolarAxisAngular::*)(const QCPPolarAxisAngular::SelectableParts & );
            if (_t _q_method = &QCPPolarAxisAngular::selectableChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *QCPPolarAxisAngular::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPPolarAxisAngular::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPPolarAxisAngular.stringdata0))
        return static_cast<void*>(this);
    return QCPLayoutElement::qt_metacast(_clname);
}

int QCPPolarAxisAngular::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayoutElement::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void QCPPolarAxisAngular::rangeChanged(const QCPRange & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCPPolarAxisAngular::rangeChanged(const QCPRange & _t1, const QCPRange & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QCPPolarAxisAngular::selectionChanged(const QCPPolarAxisAngular::SelectableParts & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QCPPolarAxisAngular::selectableChanged(const QCPPolarAxisAngular::SelectableParts & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
namespace {
struct qt_meta_stringdata_QCPPolarGrid_t {
    uint offsetsAndSizes[14];
    char stringdata0[13];
    char stringdata1[9];
    char stringdata2[10];
    char stringdata3[9];
    char stringdata4[6];
    char stringdata5[7];
    char stringdata6[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPPolarGrid_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPPolarGrid_t qt_meta_stringdata_QCPPolarGrid = {
    {
        QT_MOC_LITERAL(0, 12),  // "QCPPolarGrid"
        QT_MOC_LITERAL(13, 8),  // "GridType"
        QT_MOC_LITERAL(22, 9),  // "gtAngular"
        QT_MOC_LITERAL(32, 8),  // "gtRadial"
        QT_MOC_LITERAL(41, 5),  // "gtAll"
        QT_MOC_LITERAL(47, 6),  // "gtNone"
        QT_MOC_LITERAL(54, 9)   // "GridTypes"
    },
    "QCPPolarGrid",
    "GridType",
    "gtAngular",
    "gtRadial",
    "gtAll",
    "gtNone",
    "GridTypes"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPPolarGrid[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       2,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    4,   24,
       6,    1, 0x1,    4,   32,

 // enum data: key, value
       2, uint(QCPPolarGrid::gtAngular),
       3, uint(QCPPolarGrid::gtRadial),
       4, uint(QCPPolarGrid::gtAll),
       5, uint(QCPPolarGrid::gtNone),
       2, uint(QCPPolarGrid::gtAngular),
       3, uint(QCPPolarGrid::gtRadial),
       4, uint(QCPPolarGrid::gtAll),
       5, uint(QCPPolarGrid::gtNone),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPPolarGrid::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayerable::staticMetaObject>(),
    qt_meta_stringdata_QCPPolarGrid.offsetsAndSizes,
    qt_meta_data_QCPPolarGrid,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPPolarGrid_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPPolarGrid, std::true_type>
    >,
    nullptr
} };

void QCPPolarGrid::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *QCPPolarGrid::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPPolarGrid::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPPolarGrid.stringdata0))
        return static_cast<void*>(this);
    return QCPLayerable::qt_metacast(_clname);
}

int QCPPolarGrid::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayerable::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_stringdata_QCPPolarLegendItem_t {
    uint offsetsAndSizes[2];
    char stringdata0[19];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPPolarLegendItem_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPPolarLegendItem_t qt_meta_stringdata_QCPPolarLegendItem = {
    {
        QT_MOC_LITERAL(0, 18)   // "QCPPolarLegendItem"
    },
    "QCPPolarLegendItem"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPPolarLegendItem[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPPolarLegendItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPAbstractLegendItem::staticMetaObject>(),
    qt_meta_stringdata_QCPPolarLegendItem.offsetsAndSizes,
    qt_meta_data_QCPPolarLegendItem,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPPolarLegendItem_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPPolarLegendItem, std::true_type>
    >,
    nullptr
} };

void QCPPolarLegendItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject *QCPPolarLegendItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPPolarLegendItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPPolarLegendItem.stringdata0))
        return static_cast<void*>(this);
    return QCPAbstractLegendItem::qt_metacast(_clname);
}

int QCPPolarLegendItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPAbstractLegendItem::qt_metacall(_c, _id, _a);
    return _id;
}
namespace {
struct qt_meta_stringdata_QCPPolarGraph_t {
    uint offsetsAndSizes[28];
    char stringdata0[14];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[17];
    char stringdata5[10];
    char stringdata6[18];
    char stringdata7[19];
    char stringdata8[11];
    char stringdata9[14];
    char stringdata10[13];
    char stringdata11[10];
    char stringdata12[7];
    char stringdata13[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCPPolarGraph_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCPPolarGraph_t qt_meta_stringdata_QCPPolarGraph = {
    {
        QT_MOC_LITERAL(0, 13),  // "QCPPolarGraph"
        QT_MOC_LITERAL(14, 16),  // "selectionChanged"
        QT_MOC_LITERAL(31, 0),  // ""
        QT_MOC_LITERAL(32, 8),  // "selected"
        QT_MOC_LITERAL(41, 16),  // "QCPDataSelection"
        QT_MOC_LITERAL(58, 9),  // "selection"
        QT_MOC_LITERAL(68, 17),  // "selectableChanged"
        QT_MOC_LITERAL(86, 18),  // "QCP::SelectionType"
        QT_MOC_LITERAL(105, 10),  // "selectable"
        QT_MOC_LITERAL(116, 13),  // "setSelectable"
        QT_MOC_LITERAL(130, 12),  // "setSelection"
        QT_MOC_LITERAL(143, 9),  // "LineStyle"
        QT_MOC_LITERAL(153, 6),  // "lsNone"
        QT_MOC_LITERAL(160, 6)   // "lsLine"
    },
    "QCPPolarGraph",
    "selectionChanged",
    "",
    "selected",
    "QCPDataSelection",
    "selection",
    "selectableChanged",
    "QCP::SelectionType",
    "selectable",
    "setSelectable",
    "setSelection",
    "LineStyle",
    "lsNone",
    "lsLine"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCPPolarGraph[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       1,   59, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   44,    2, 0x06,    1 /* Public */,
       1,    1,   47,    2, 0x06,    3 /* Public */,
       6,    1,   50,    2, 0x06,    5 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    1,   53,    2, 0x0a,    7 /* Public */,
      10,    1,   56,    2, 0x0a,    9 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 4,    5,

 // enums: name, alias, flags, count, data
      11,   11, 0x0,    2,   64,

 // enum data: key, value
      12, uint(QCPPolarGraph::lsNone),
      13, uint(QCPPolarGraph::lsLine),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCPPolarGraph::staticMetaObject = { {
    QMetaObject::SuperData::link<QCPLayerable::staticMetaObject>(),
    qt_meta_stringdata_QCPPolarGraph.offsetsAndSizes,
    qt_meta_data_QCPPolarGraph,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCPPolarGraph_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<QCPPolarGraph, std::true_type>,
        // method 'selectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'selectionChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QCPDataSelection &, std::false_type>,
        // method 'selectableChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCP::SelectionType, std::false_type>,
        // method 'setSelectable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCP::SelectionType, std::false_type>,
        // method 'setSelection'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QCPDataSelection, std::false_type>
    >,
    nullptr
} };

void QCPPolarGraph::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCPPolarGraph *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->selectionChanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 1: _t->selectionChanged((*reinterpret_cast< std::add_pointer_t<QCPDataSelection>>(_a[1]))); break;
        case 2: _t->selectableChanged((*reinterpret_cast< std::add_pointer_t<QCP::SelectionType>>(_a[1]))); break;
        case 3: _t->setSelectable((*reinterpret_cast< std::add_pointer_t<QCP::SelectionType>>(_a[1]))); break;
        case 4: _t->setSelection((*reinterpret_cast< std::add_pointer_t<QCPDataSelection>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPDataSelection >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QCPDataSelection >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QCPPolarGraph::*)(bool );
            if (_t _q_method = &QCPPolarGraph::selectionChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QCPPolarGraph::*)(const QCPDataSelection & );
            if (_t _q_method = &QCPPolarGraph::selectionChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QCPPolarGraph::*)(QCP::SelectionType );
            if (_t _q_method = &QCPPolarGraph::selectableChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *QCPPolarGraph::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPPolarGraph::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPPolarGraph.stringdata0))
        return static_cast<void*>(this);
    return QCPLayerable::qt_metacast(_clname);
}

int QCPPolarGraph::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPLayerable::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void QCPPolarGraph::selectionChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCPPolarGraph::selectionChanged(const QCPDataSelection & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QCPPolarGraph::selectableChanged(QCP::SelectionType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
namespace {
struct qt_meta_stringdata_QCP_t {
    uint offsetsAndSizes[128];
    char stringdata0[4];
    char stringdata1[15];
    char stringdata2[15];
    char stringdata3[20];
    char stringdata4[14];
    char stringdata5[10];
    char stringdata6[13];
    char stringdata7[16];
    char stringdata8[11];
    char stringdata9[11];
    char stringdata10[7];
    char stringdata11[11];
    char stringdata12[11];
    char stringdata13[7];
    char stringdata14[8];
    char stringdata15[6];
    char stringdata16[9];
    char stringdata17[6];
    char stringdata18[7];
    char stringdata19[12];
    char stringdata20[19];
    char stringdata21[7];
    char stringdata22[7];
    char stringdata23[10];
    char stringdata24[9];
    char stringdata25[14];
    char stringdata26[13];
    char stringdata27[8];
    char stringdata28[11];
    char stringdata29[8];
    char stringdata30[11];
    char stringdata31[8];
    char stringdata32[6];
    char stringdata33[7];
    char stringdata34[20];
    char stringdata35[13];
    char stringdata36[7];
    char stringdata37[16];
    char stringdata38[19];
    char stringdata39[14];
    char stringdata40[14];
    char stringdata41[12];
    char stringdata42[6];
    char stringdata43[11];
    char stringdata44[11];
    char stringdata45[13];
    char stringdata46[18];
    char stringdata47[12];
    char stringdata48[14];
    char stringdata49[13];
    char stringdata50[13];
    char stringdata51[32];
    char stringdata52[13];
    char stringdata53[18];
    char stringdata54[8];
    char stringdata55[8];
    char stringdata56[10];
    char stringdata57[10];
    char stringdata58[14];
    char stringdata59[7];
    char stringdata60[8];
    char stringdata61[13];
    char stringdata62[12];
    char stringdata63[21];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_QCP_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_QCP_t qt_meta_stringdata_QCP = {
    {
        QT_MOC_LITERAL(0, 3),  // "QCP"
        QT_MOC_LITERAL(4, 14),  // "ResolutionUnit"
        QT_MOC_LITERAL(19, 14),  // "ruDotsPerMeter"
        QT_MOC_LITERAL(34, 19),  // "ruDotsPerCentimeter"
        QT_MOC_LITERAL(54, 13),  // "ruDotsPerInch"
        QT_MOC_LITERAL(68, 9),  // "ExportPen"
        QT_MOC_LITERAL(78, 12),  // "epNoCosmetic"
        QT_MOC_LITERAL(91, 15),  // "epAllowCosmetic"
        QT_MOC_LITERAL(107, 10),  // "SignDomain"
        QT_MOC_LITERAL(118, 10),  // "sdNegative"
        QT_MOC_LITERAL(129, 6),  // "sdBoth"
        QT_MOC_LITERAL(136, 10),  // "sdPositive"
        QT_MOC_LITERAL(147, 10),  // "MarginSide"
        QT_MOC_LITERAL(158, 6),  // "msLeft"
        QT_MOC_LITERAL(165, 7),  // "msRight"
        QT_MOC_LITERAL(173, 5),  // "msTop"
        QT_MOC_LITERAL(179, 8),  // "msBottom"
        QT_MOC_LITERAL(188, 5),  // "msAll"
        QT_MOC_LITERAL(194, 6),  // "msNone"
        QT_MOC_LITERAL(201, 11),  // "MarginSides"
        QT_MOC_LITERAL(213, 18),  // "AntialiasedElement"
        QT_MOC_LITERAL(232, 6),  // "aeAxes"
        QT_MOC_LITERAL(239, 6),  // "aeGrid"
        QT_MOC_LITERAL(246, 9),  // "aeSubGrid"
        QT_MOC_LITERAL(256, 8),  // "aeLegend"
        QT_MOC_LITERAL(265, 13),  // "aeLegendItems"
        QT_MOC_LITERAL(279, 12),  // "aePlottables"
        QT_MOC_LITERAL(292, 7),  // "aeItems"
        QT_MOC_LITERAL(300, 10),  // "aeScatters"
        QT_MOC_LITERAL(311, 7),  // "aeFills"
        QT_MOC_LITERAL(319, 10),  // "aeZeroLine"
        QT_MOC_LITERAL(330, 7),  // "aeOther"
        QT_MOC_LITERAL(338, 5),  // "aeAll"
        QT_MOC_LITERAL(344, 6),  // "aeNone"
        QT_MOC_LITERAL(351, 19),  // "AntialiasedElements"
        QT_MOC_LITERAL(371, 12),  // "PlottingHint"
        QT_MOC_LITERAL(384, 6),  // "phNone"
        QT_MOC_LITERAL(391, 15),  // "phFastPolylines"
        QT_MOC_LITERAL(407, 18),  // "phImmediateRefresh"
        QT_MOC_LITERAL(426, 13),  // "phCacheLabels"
        QT_MOC_LITERAL(440, 13),  // "PlottingHints"
        QT_MOC_LITERAL(454, 11),  // "Interaction"
        QT_MOC_LITERAL(466, 5),  // "iNone"
        QT_MOC_LITERAL(472, 10),  // "iRangeDrag"
        QT_MOC_LITERAL(483, 10),  // "iRangeZoom"
        QT_MOC_LITERAL(494, 12),  // "iMultiSelect"
        QT_MOC_LITERAL(507, 17),  // "iSelectPlottables"
        QT_MOC_LITERAL(525, 11),  // "iSelectAxes"
        QT_MOC_LITERAL(537, 13),  // "iSelectLegend"
        QT_MOC_LITERAL(551, 12),  // "iSelectItems"
        QT_MOC_LITERAL(564, 12),  // "iSelectOther"
        QT_MOC_LITERAL(577, 31),  // "iSelectPlottablesBeyondAxisRect"
        QT_MOC_LITERAL(609, 12),  // "Interactions"
        QT_MOC_LITERAL(622, 17),  // "SelectionRectMode"
        QT_MOC_LITERAL(640, 7),  // "srmNone"
        QT_MOC_LITERAL(648, 7),  // "srmZoom"
        QT_MOC_LITERAL(656, 9),  // "srmSelect"
        QT_MOC_LITERAL(666, 9),  // "srmCustom"
        QT_MOC_LITERAL(676, 13),  // "SelectionType"
        QT_MOC_LITERAL(690, 6),  // "stNone"
        QT_MOC_LITERAL(697, 7),  // "stWhole"
        QT_MOC_LITERAL(705, 12),  // "stSingleData"
        QT_MOC_LITERAL(718, 11),  // "stDataRange"
        QT_MOC_LITERAL(730, 20)   // "stMultipleDataRanges"
    },
    "QCP",
    "ResolutionUnit",
    "ruDotsPerMeter",
    "ruDotsPerCentimeter",
    "ruDotsPerInch",
    "ExportPen",
    "epNoCosmetic",
    "epAllowCosmetic",
    "SignDomain",
    "sdNegative",
    "sdBoth",
    "sdPositive",
    "MarginSide",
    "msLeft",
    "msRight",
    "msTop",
    "msBottom",
    "msAll",
    "msNone",
    "MarginSides",
    "AntialiasedElement",
    "aeAxes",
    "aeGrid",
    "aeSubGrid",
    "aeLegend",
    "aeLegendItems",
    "aePlottables",
    "aeItems",
    "aeScatters",
    "aeFills",
    "aeZeroLine",
    "aeOther",
    "aeAll",
    "aeNone",
    "AntialiasedElements",
    "PlottingHint",
    "phNone",
    "phFastPolylines",
    "phImmediateRefresh",
    "phCacheLabels",
    "PlottingHints",
    "Interaction",
    "iNone",
    "iRangeDrag",
    "iRangeZoom",
    "iMultiSelect",
    "iSelectPlottables",
    "iSelectAxes",
    "iSelectLegend",
    "iSelectItems",
    "iSelectOther",
    "iSelectPlottablesBeyondAxisRect",
    "Interactions",
    "SelectionRectMode",
    "srmNone",
    "srmZoom",
    "srmSelect",
    "srmCustom",
    "SelectionType",
    "stNone",
    "stWhole",
    "stSingleData",
    "stDataRange",
    "stMultipleDataRanges"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_QCP[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
      13,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    3,   79,
       5,    5, 0x0,    2,   85,
       8,    8, 0x0,    3,   89,
      12,   12, 0x0,    6,   95,
      19,   12, 0x1,    6,  107,
      20,   20, 0x0,   13,  119,
      34,   20, 0x1,   13,  145,
      35,   35, 0x0,    4,  171,
      40,   35, 0x1,    4,  179,
      41,   41, 0x0,   10,  187,
      52,   41, 0x1,   10,  207,
      53,   53, 0x0,    4,  227,
      58,   58, 0x0,    5,  235,

 // enum data: key, value
       2, uint(QCP::ruDotsPerMeter),
       3, uint(QCP::ruDotsPerCentimeter),
       4, uint(QCP::ruDotsPerInch),
       6, uint(QCP::epNoCosmetic),
       7, uint(QCP::epAllowCosmetic),
       9, uint(QCP::sdNegative),
      10, uint(QCP::sdBoth),
      11, uint(QCP::sdPositive),
      13, uint(QCP::msLeft),
      14, uint(QCP::msRight),
      15, uint(QCP::msTop),
      16, uint(QCP::msBottom),
      17, uint(QCP::msAll),
      18, uint(QCP::msNone),
      13, uint(QCP::msLeft),
      14, uint(QCP::msRight),
      15, uint(QCP::msTop),
      16, uint(QCP::msBottom),
      17, uint(QCP::msAll),
      18, uint(QCP::msNone),
      21, uint(QCP::aeAxes),
      22, uint(QCP::aeGrid),
      23, uint(QCP::aeSubGrid),
      24, uint(QCP::aeLegend),
      25, uint(QCP::aeLegendItems),
      26, uint(QCP::aePlottables),
      27, uint(QCP::aeItems),
      28, uint(QCP::aeScatters),
      29, uint(QCP::aeFills),
      30, uint(QCP::aeZeroLine),
      31, uint(QCP::aeOther),
      32, uint(QCP::aeAll),
      33, uint(QCP::aeNone),
      21, uint(QCP::aeAxes),
      22, uint(QCP::aeGrid),
      23, uint(QCP::aeSubGrid),
      24, uint(QCP::aeLegend),
      25, uint(QCP::aeLegendItems),
      26, uint(QCP::aePlottables),
      27, uint(QCP::aeItems),
      28, uint(QCP::aeScatters),
      29, uint(QCP::aeFills),
      30, uint(QCP::aeZeroLine),
      31, uint(QCP::aeOther),
      32, uint(QCP::aeAll),
      33, uint(QCP::aeNone),
      36, uint(QCP::phNone),
      37, uint(QCP::phFastPolylines),
      38, uint(QCP::phImmediateRefresh),
      39, uint(QCP::phCacheLabels),
      36, uint(QCP::phNone),
      37, uint(QCP::phFastPolylines),
      38, uint(QCP::phImmediateRefresh),
      39, uint(QCP::phCacheLabels),
      42, uint(QCP::iNone),
      43, uint(QCP::iRangeDrag),
      44, uint(QCP::iRangeZoom),
      45, uint(QCP::iMultiSelect),
      46, uint(QCP::iSelectPlottables),
      47, uint(QCP::iSelectAxes),
      48, uint(QCP::iSelectLegend),
      49, uint(QCP::iSelectItems),
      50, uint(QCP::iSelectOther),
      51, uint(QCP::iSelectPlottablesBeyondAxisRect),
      42, uint(QCP::iNone),
      43, uint(QCP::iRangeDrag),
      44, uint(QCP::iRangeZoom),
      45, uint(QCP::iMultiSelect),
      46, uint(QCP::iSelectPlottables),
      47, uint(QCP::iSelectAxes),
      48, uint(QCP::iSelectLegend),
      49, uint(QCP::iSelectItems),
      50, uint(QCP::iSelectOther),
      51, uint(QCP::iSelectPlottablesBeyondAxisRect),
      54, uint(QCP::srmNone),
      55, uint(QCP::srmZoom),
      56, uint(QCP::srmSelect),
      57, uint(QCP::srmCustom),
      59, uint(QCP::stNone),
      60, uint(QCP::stWhole),
      61, uint(QCP::stSingleData),
      62, uint(QCP::stDataRange),
      63, uint(QCP::stMultipleDataRanges),

       0        // eod
};

Q_CONSTINIT const QMetaObject QCP::staticMetaObject = { {
    nullptr,
    qt_meta_stringdata_QCP.offsetsAndSizes,
    qt_meta_data_QCP,
    nullptr,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_QCP_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<void, std::true_type>
    >,
    nullptr
} };

QT_WARNING_POP
QT_END_MOC_NAMESPACE
