/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtCharts/qlineseries.h>
#include <QtCharts/qabstractbarseries.h>
#include <QtCharts/qvbarmodelmapper.h>
#include <QtCharts/qboxplotseries.h>
#include <QtCharts/qcandlestickseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qpieseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qboxplotseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qpieseries.h>
#include <QtCharts/qpieseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qxyseries.h>
#include <QtCharts/qxyseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qboxplotseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qpieseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qxyseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "on_btnAjouter_clicked",
    "",
    "on_btnModifier_clicked",
    "on_btnSupprimer_clicked",
    "on_btnRechercher_clicked",
    "on_btnReinitialiser_clicked",
    "on_tableViewAppareils_2_clicked",
    "QModelIndex",
    "index",
    "on_btnAjouterClient_clicked",
    "on_btnModifierClient_clicked",
    "on_btnSupprimerClient_clicked",
    "on_btnRechercherClient_clicked",
    "on_btnReinitialiserClient_clicked",
    "on_tableViewClients_clicked",
    "on_btnAjouterAppareil_clicked",
    "on_btnModifierAppareil_clicked",
    "on_btnSupprimerAppareil_clicked",
    "on_btnRechercherAppareil_clicked",
    "on_btnReinitialiserAppareil_clicked",
    "on_btnVieAppareil_clicked",
    "on_tableViewAppareils_clicked",
    "on_btnAjouterReparation_clicked",
    "on_btnModifierReparation_clicked",
    "on_btnSupprimerReparation_clicked",
    "on_btnRechercherReparation_clicked",
    "on_btnReinitialiserReparation_clicked",
    "on_tableViewReparationsListe_clicked",
    "on_btnGenererRapport_clicked",
    "on_btnStatistiquesAppareil_clicked",
    "on_btnCalendrier_clicked",
    "onTextChanged",
    "text",
    "onHeaderReparationClicked",
    "logicalIndex",
    "on_btnAnalyserFidelite_clicked",
    "on_btnMaintenancePreventive_clicked",
    "on_btnShowStatistics_clicked",
    "on_btnExportPDF_clicked"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      34,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  218,    2, 0x08,    1 /* Private */,
       3,    0,  219,    2, 0x08,    2 /* Private */,
       4,    0,  220,    2, 0x08,    3 /* Private */,
       5,    0,  221,    2, 0x08,    4 /* Private */,
       6,    0,  222,    2, 0x08,    5 /* Private */,
       7,    1,  223,    2, 0x08,    6 /* Private */,
      10,    0,  226,    2, 0x08,    8 /* Private */,
      11,    0,  227,    2, 0x08,    9 /* Private */,
      12,    0,  228,    2, 0x08,   10 /* Private */,
      13,    0,  229,    2, 0x08,   11 /* Private */,
      14,    0,  230,    2, 0x08,   12 /* Private */,
      15,    1,  231,    2, 0x08,   13 /* Private */,
      16,    0,  234,    2, 0x08,   15 /* Private */,
      17,    0,  235,    2, 0x08,   16 /* Private */,
      18,    0,  236,    2, 0x08,   17 /* Private */,
      19,    0,  237,    2, 0x08,   18 /* Private */,
      20,    0,  238,    2, 0x08,   19 /* Private */,
      21,    0,  239,    2, 0x08,   20 /* Private */,
      22,    1,  240,    2, 0x08,   21 /* Private */,
      23,    0,  243,    2, 0x08,   23 /* Private */,
      24,    0,  244,    2, 0x08,   24 /* Private */,
      25,    0,  245,    2, 0x08,   25 /* Private */,
      26,    0,  246,    2, 0x08,   26 /* Private */,
      27,    0,  247,    2, 0x08,   27 /* Private */,
      28,    1,  248,    2, 0x08,   28 /* Private */,
      29,    0,  251,    2, 0x08,   30 /* Private */,
      30,    0,  252,    2, 0x08,   31 /* Private */,
      31,    0,  253,    2, 0x08,   32 /* Private */,
      32,    1,  254,    2, 0x08,   33 /* Private */,
      34,    1,  257,    2, 0x08,   35 /* Private */,
      36,    0,  260,    2, 0x08,   37 /* Private */,
      37,    0,  261,    2, 0x08,   38 /* Private */,
      38,    0,  262,    2, 0x08,   39 /* Private */,
      39,    0,  263,    2, 0x08,   40 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   33,
    QMetaType::Void, QMetaType::Int,   35,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'on_btnAjouter_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnModifier_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnSupprimer_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnRechercher_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnReinitialiser_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_tableViewAppareils_2_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'on_btnAjouterClient_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnModifierClient_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnSupprimerClient_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnRechercherClient_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnReinitialiserClient_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_tableViewClients_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'on_btnAjouterAppareil_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnModifierAppareil_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnSupprimerAppareil_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnRechercherAppareil_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnReinitialiserAppareil_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnVieAppareil_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_tableViewAppareils_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'on_btnAjouterReparation_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnModifierReparation_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnSupprimerReparation_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnRechercherReparation_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnReinitialiserReparation_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_tableViewReparationsListe_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'on_btnGenererRapport_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnStatistiquesAppareil_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnCalendrier_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onTextChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onHeaderReparationClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_btnAnalyserFidelite_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnMaintenancePreventive_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnShowStatistics_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnExportPDF_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_btnAjouter_clicked(); break;
        case 1: _t->on_btnModifier_clicked(); break;
        case 2: _t->on_btnSupprimer_clicked(); break;
        case 3: _t->on_btnRechercher_clicked(); break;
        case 4: _t->on_btnReinitialiser_clicked(); break;
        case 5: _t->on_tableViewAppareils_2_clicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 6: _t->on_btnAjouterClient_clicked(); break;
        case 7: _t->on_btnModifierClient_clicked(); break;
        case 8: _t->on_btnSupprimerClient_clicked(); break;
        case 9: _t->on_btnRechercherClient_clicked(); break;
        case 10: _t->on_btnReinitialiserClient_clicked(); break;
        case 11: _t->on_tableViewClients_clicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 12: _t->on_btnAjouterAppareil_clicked(); break;
        case 13: _t->on_btnModifierAppareil_clicked(); break;
        case 14: _t->on_btnSupprimerAppareil_clicked(); break;
        case 15: _t->on_btnRechercherAppareil_clicked(); break;
        case 16: _t->on_btnReinitialiserAppareil_clicked(); break;
        case 17: _t->on_btnVieAppareil_clicked(); break;
        case 18: _t->on_tableViewAppareils_clicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 19: _t->on_btnAjouterReparation_clicked(); break;
        case 20: _t->on_btnModifierReparation_clicked(); break;
        case 21: _t->on_btnSupprimerReparation_clicked(); break;
        case 22: _t->on_btnRechercherReparation_clicked(); break;
        case 23: _t->on_btnReinitialiserReparation_clicked(); break;
        case 24: _t->on_tableViewReparationsListe_clicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 25: _t->on_btnGenererRapport_clicked(); break;
        case 26: _t->on_btnStatistiquesAppareil_clicked(); break;
        case 27: _t->on_btnCalendrier_clicked(); break;
        case 28: _t->onTextChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 29: _t->onHeaderReparationClicked((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 30: _t->on_btnAnalyserFidelite_clicked(); break;
        case 31: _t->on_btnMaintenancePreventive_clicked(); break;
        case 32: _t->on_btnShowStatistics_clicked(); break;
        case 33: _t->on_btnExportPDF_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 34)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 34;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 34)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 34;
    }
    return _id;
}
QT_WARNING_POP
