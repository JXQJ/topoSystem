/****************************************************************************
** Meta object code from reading C++ file 'AddNode.h'
**
** Created: Mon Jul 9 09:43:29 2018
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../AddNode.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AddNode.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AddNode[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AddNode[] = {
    "AddNode\0\0addNodeConfirm()\0"
};

const QMetaObject AddNode::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AddNode,
      qt_meta_data_AddNode, 0 }
};

const QMetaObject *AddNode::metaObject() const
{
    return &staticMetaObject;
}

void *AddNode::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AddNode))
	return static_cast<void*>(const_cast< AddNode*>(this));
    return QDialog::qt_metacast(_clname);
}

int AddNode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addNodeConfirm(); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
