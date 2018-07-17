/****************************************************************************
** Meta object code from reading C++ file 'proteinview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../proteinview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'proteinview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ProteinView_t {
    QByteArrayData data[6];
    char stringdata[70];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ProteinView_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ProteinView_t qt_meta_stringdata_ProteinView = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 8),
QT_MOC_LITERAL(2, 21, 0),
QT_MOC_LITERAL(3, 22, 16),
QT_MOC_LITERAL(4, 39, 14),
QT_MOC_LITERAL(5, 54, 14)
    },
    "ProteinView\0released\0\0activeAccessions\0"
    "QList<QString>\0selectionEvent\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProteinView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06,
       3,    1,   30,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       5,    0,   33,    2, 0x08,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void ProteinView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ProteinView *_t = static_cast<ProteinView *>(_o);
        switch (_id) {
        case 0: _t->released(); break;
        case 1: _t->activeAccessions((*reinterpret_cast< QList<QString>(*)>(_a[1]))); break;
        case 2: _t->selectionEvent(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QString> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ProteinView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ProteinView::released)) {
                *result = 0;
            }
        }
        {
            typedef void (ProteinView::*_t)(QList<QString> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ProteinView::activeAccessions)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject ProteinView::staticMetaObject = {
    { &QTableView::staticMetaObject, qt_meta_stringdata_ProteinView.data,
      qt_meta_data_ProteinView,  qt_static_metacall, 0, 0}
};


const QMetaObject *ProteinView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProteinView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ProteinView.stringdata))
        return static_cast<void*>(const_cast< ProteinView*>(this));
    return QTableView::qt_metacast(_clname);
}

int ProteinView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ProteinView::released()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ProteinView::activeAccessions(QList<QString> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
