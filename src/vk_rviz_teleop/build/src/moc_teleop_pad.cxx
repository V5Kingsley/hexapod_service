/****************************************************************************
** Meta object code from reading C++ file 'teleop_pad.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/teleop_pad.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'teleop_pad.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_rviz_teleop_commander__TeleopPanel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      42,   36,   35,   35, 0x0a,
      73,   60,   35,   35, 0x0a,
     159,   35,   35,   35, 0x09,
     169,   35,   35,   35, 0x09,
     194,   35,   35,   35, 0x09,
     220,   35,   35,   35, 0x09,
     234,   35,   35,   35, 0x09,
     249,   35,   35,   35, 0x09,
     268,   35,   35,   35, 0x09,
     288,   35,   35,   35, 0x09,
     310,   35,   35,   35, 0x09,
     334,   35,   35,   35, 0x09,
     355,   35,   35,   35, 0x09,
     377,   35,   35,   35, 0x09,
     400,   35,   35,   35, 0x09,
     428,   35,   35,   35, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_rviz_teleop_commander__TeleopPanel[] = {
    "rviz_teleop_commander::TeleopPanel\0\0"
    "topic\0setTopic(QString)\0state,result\0"
    "doneCb(actionlib::SimpleClientGoalState,hexapodservice::hexapodservice"
    "ResultConstPtr)\0"
    "sendVel()\0update_Linear_Velocity()\0"
    "update_Angular_Velocity()\0updateTopic()\0"
    "stopVelocity()\0OPENBUSButtonFuc()\0"
    "CLOSEBUSButtonFuc()\0ENABLEMOTORButonFuc()\0"
    "DISABLEMOTORButtonFuc()\0GETSTATUSButtonFuc()\0"
    "CLEARFAULTButtonFuc()\0ALLLEGRESETButtonFuc()\0"
    "list_msg_show_in_listview()\0"
    "list_msg_show_in_listview_giveup()\0"
};

void rviz_teleop_commander::TeleopPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TeleopPanel *_t = static_cast<TeleopPanel *>(_o);
        switch (_id) {
        case 0: _t->setTopic((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->doneCb((*reinterpret_cast< const actionlib::SimpleClientGoalState(*)>(_a[1])),(*reinterpret_cast< const hexapodservice::hexapodserviceResultConstPtr(*)>(_a[2]))); break;
        case 2: _t->sendVel(); break;
        case 3: _t->update_Linear_Velocity(); break;
        case 4: _t->update_Angular_Velocity(); break;
        case 5: _t->updateTopic(); break;
        case 6: _t->stopVelocity(); break;
        case 7: _t->OPENBUSButtonFuc(); break;
        case 8: _t->CLOSEBUSButtonFuc(); break;
        case 9: _t->ENABLEMOTORButonFuc(); break;
        case 10: _t->DISABLEMOTORButtonFuc(); break;
        case 11: _t->GETSTATUSButtonFuc(); break;
        case 12: _t->CLEARFAULTButtonFuc(); break;
        case 13: _t->ALLLEGRESETButtonFuc(); break;
        case 14: _t->list_msg_show_in_listview(); break;
        case 15: _t->list_msg_show_in_listview_giveup(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData rviz_teleop_commander::TeleopPanel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject rviz_teleop_commander::TeleopPanel::staticMetaObject = {
    { &rviz::Panel::staticMetaObject, qt_meta_stringdata_rviz_teleop_commander__TeleopPanel,
      qt_meta_data_rviz_teleop_commander__TeleopPanel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &rviz_teleop_commander::TeleopPanel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *rviz_teleop_commander::TeleopPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *rviz_teleop_commander::TeleopPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_rviz_teleop_commander__TeleopPanel))
        return static_cast<void*>(const_cast< TeleopPanel*>(this));
    typedef rviz::Panel QMocSuperClass;
    return QMocSuperClass::qt_metacast(_clname);
}

int rviz_teleop_commander::TeleopPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    typedef rviz::Panel QMocSuperClass;
    _id = QMocSuperClass::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
