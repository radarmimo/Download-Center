/****************************************************************************
** Meta object code from reading C++ file 'usrprx.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "usrprx.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'usrprx.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_usrpRx_t {
    uint offsetsAndSizes[18];
    char stringdata0[7];
    char stringdata1[10];
    char stringdata2[1];
    char stringdata3[14];
    char stringdata4[6];
    char stringdata5[6];
    char stringdata6[11];
    char stringdata7[7];
    char stringdata8[14];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_usrpRx_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_usrpRx_t qt_meta_stringdata_usrpRx = {
    {
        QT_MOC_LITERAL(0, 6),  // "usrpRx"
        QT_MOC_LITERAL(7, 9),  // "dataReady"
        QT_MOC_LITERAL(17, 0),  // ""
        QT_MOC_LITERAL(18, 13),  // "QList<double>"
        QT_MOC_LITERAL(32, 5),  // "dataI"
        QT_MOC_LITERAL(38, 5),  // "dataQ"
        QT_MOC_LITERAL(44, 10),  // "usrpStatus"
        QT_MOC_LITERAL(55, 6),  // "status"
        QT_MOC_LITERAL(62, 13)   // "deviceAddress"
    },
    "usrpRx",
    "dataReady",
    "",
    "QList<double>",
    "dataI",
    "dataQ",
    "usrpStatus",
    "status",
    "deviceAddress"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_usrpRx[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   26,    2, 0x06,    1 /* Public */,
       6,    2,   31,    2, 0x06,    4 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    7,    8,

       0        // eod
};

Q_CONSTINIT const QMetaObject usrpRx::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_usrpRx.offsetsAndSizes,
    qt_meta_data_usrpRx,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_usrpRx_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<usrpRx, std::true_type>,
        // method 'dataReady'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QVector<double>, std::false_type>,
        QtPrivate::TypeAndForceComplete<QVector<double>, std::false_type>,
        // method 'usrpStatus'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>
    >,
    nullptr
} };

void usrpRx::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<usrpRx *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->dataReady((*reinterpret_cast< std::add_pointer_t<QList<double>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QList<double>>>(_a[2]))); break;
        case 1: _t->usrpStatus((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<double> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (usrpRx::*)(QVector<double> , QVector<double> );
            if (_t _q_method = &usrpRx::dataReady; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (usrpRx::*)(bool , QString );
            if (_t _q_method = &usrpRx::usrpStatus; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *usrpRx::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *usrpRx::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_usrpRx.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int usrpRx::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
    }
    return _id;
}

// SIGNAL 0
void usrpRx::dataReady(QVector<double> _t1, QVector<double> _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void usrpRx::usrpStatus(bool _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
