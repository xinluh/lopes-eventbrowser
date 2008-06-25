/****************************************************************************
** MainForm meta object code from reading C++ file 'mainform.h'
**
** Created: Tue Jun 24 15:55:46 2008
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "mainform.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MainForm::className() const
{
    return "MainForm";
}

QMetaObject *MainForm::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MainForm( "MainForm", &MainForm::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MainForm::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MainForm", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MainForm::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MainForm", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MainForm::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QMainWindow::staticMetaObject();
    static const QUMethod slot_0 = {"fileOpen", 0, 0 };
    static const QUMethod slot_1 = {"fileSave", 0, 0 };
    static const QUMethod slot_2 = {"fileSaveAllSingle", 0, 0 };
    static const QUMethod slot_3 = {"fileSaveAllMultiple", 0, 0 };
    static const QUMethod slot_4 = {"filePrint", 0, 0 };
    static const QUMethod slot_5 = {"editUndo", 0, 0 };
    static const QUMethod slot_6 = {"editRedo", 0, 0 };
    static const QUMethod slot_7 = {"fileExit", 0, 0 };
    static const QUMethod slot_8 = {"editCut", 0, 0 };
    static const QUMethod slot_9 = {"editCopy", 0, 0 };
    static const QUMethod slot_10 = {"editPaste", 0, 0 };
    static const QUMethod slot_11 = {"helpIndex", 0, 0 };
    static const QUMethod slot_12 = {"helpContents", 0, 0 };
    static const QUMethod slot_13 = {"helpAbout", 0, 0 };
    static const QUMethod slot_14 = {"enableDrawButton", 0, 0 };
    static const QUMethod slot_15 = {"Draw", 0, 0 };
    static const QUMethod slot_16 = {"applyRootCut", 0, 0 };
    static const QUMethod slot_17 = {"txtEventCut_changed", 0, 0 };
    static const QUMethod slot_18 = {"addNewTab", 0, 0 };
    static const QUMethod slot_19 = {"enableTabActionButtons", 0, 0 };
    static const QUParameter param_slot_20[] = {
	{ "qw", &static_QUType_ptr, "QWidget", QUParameter::In }
    };
    static const QUMethod slot_20 = {"setTabAsCanvas", 1, param_slot_20 };
    static const QUParameter param_slot_21[] = {
	{ 0, &static_QUType_int, 0, QUParameter::Out }
    };
    static const QUMethod slot_21 = {"getTabIndex", 1, param_slot_21 };
    static const QUParameter param_slot_22[] = {
	{ 0, &static_QUType_int, 0, QUParameter::Out },
	{ "widgetID", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_22 = {"getTabIndex", 2, param_slot_22 };
    static const QUParameter param_slot_23[] = {
	{ 0, &static_QUType_int, 0, QUParameter::Out },
	{ "item", &static_QUType_ptr, "QListViewItem", QUParameter::In }
    };
    static const QUMethod slot_23 = {"getTabIndex", 2, param_slot_23 };
    static const QUParameter param_slot_24[] = {
	{ "sel", &static_QUType_ptr, "QListViewItem", QUParameter::In }
    };
    static const QUMethod slot_24 = {"selectTab", 1, param_slot_24 };
    static const QUMethod slot_25 = {"removeTab", 0, 0 };
    static const QUParameter param_slot_26[] = {
	{ "index", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_26 = {"removeTab", 1, param_slot_26 };
    static const QUMethod slot_27 = {"renameTab", 0, 0 };
    static const QUParameter param_slot_28[] = {
	{ "index", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_28 = {"renameTab", 1, param_slot_28 };
    static const QUParameter param_slot_29[] = {
	{ "name", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_29 = {"renameTab", 1, param_slot_29 };
    static const QUParameter param_slot_30[] = {
	{ "index", &static_QUType_int, 0, QUParameter::In },
	{ "name", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_30 = {"renameTab", 2, param_slot_30 };
    static const QUMethod slot_31 = {"divideCanvas", 0, 0 };
    static const QUParameter param_slot_32[] = {
	{ "n_columns", &static_QUType_int, 0, QUParameter::In },
	{ "n_rows", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_32 = {"divideCanvas", 2, param_slot_32 };
    static const QUParameter param_slot_33[] = {
	{ "n_subpad", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_33 = {"addNewSubPad", 1, param_slot_33 };
    static const QUMethod slot_34 = {"clearGraph", 0, 0 };
    static const QUParameter param_slot_35[] = {
	{ "state", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_35 = {"setMultigraphStatus", 1, param_slot_35 };
    static const QUMethod slot_36 = {"saveEventCut", 0, 0 };
    static const QUParameter param_slot_37[] = {
	{ "status", &static_QUType_QString, 0, QUParameter::In }
    };
    static const QUMethod slot_37 = {"changeStatus", 1, param_slot_37 };
    static const QUParameter param_slot_38[] = {
	{ "index", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_38 = {"selectGraphType", 1, param_slot_38 };
    static const QUMethod slot_39 = {"viewData", 0, 0 };
    static const QUMethod slot_40 = {"fillBranchNames", 0, 0 };
    static const QUMethod slot_41 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "fileOpen()", &slot_0, QMetaData::Public },
	{ "fileSave()", &slot_1, QMetaData::Public },
	{ "fileSaveAllSingle()", &slot_2, QMetaData::Public },
	{ "fileSaveAllMultiple()", &slot_3, QMetaData::Public },
	{ "filePrint()", &slot_4, QMetaData::Public },
	{ "editUndo()", &slot_5, QMetaData::Public },
	{ "editRedo()", &slot_6, QMetaData::Public },
	{ "fileExit()", &slot_7, QMetaData::Public },
	{ "editCut()", &slot_8, QMetaData::Public },
	{ "editCopy()", &slot_9, QMetaData::Public },
	{ "editPaste()", &slot_10, QMetaData::Public },
	{ "helpIndex()", &slot_11, QMetaData::Public },
	{ "helpContents()", &slot_12, QMetaData::Public },
	{ "helpAbout()", &slot_13, QMetaData::Public },
	{ "enableDrawButton()", &slot_14, QMetaData::Public },
	{ "Draw()", &slot_15, QMetaData::Public },
	{ "applyRootCut()", &slot_16, QMetaData::Public },
	{ "txtEventCut_changed()", &slot_17, QMetaData::Public },
	{ "addNewTab()", &slot_18, QMetaData::Public },
	{ "enableTabActionButtons()", &slot_19, QMetaData::Public },
	{ "setTabAsCanvas(QWidget*)", &slot_20, QMetaData::Public },
	{ "getTabIndex()", &slot_21, QMetaData::Public },
	{ "getTabIndex(int)", &slot_22, QMetaData::Public },
	{ "getTabIndex(QListViewItem*)", &slot_23, QMetaData::Public },
	{ "selectTab(QListViewItem*)", &slot_24, QMetaData::Public },
	{ "removeTab()", &slot_25, QMetaData::Public },
	{ "removeTab(int)", &slot_26, QMetaData::Public },
	{ "renameTab()", &slot_27, QMetaData::Public },
	{ "renameTab(int)", &slot_28, QMetaData::Public },
	{ "renameTab(QString)", &slot_29, QMetaData::Public },
	{ "renameTab(int,QString)", &slot_30, QMetaData::Public },
	{ "divideCanvas()", &slot_31, QMetaData::Public },
	{ "divideCanvas(int,int)", &slot_32, QMetaData::Public },
	{ "addNewSubPad(int)", &slot_33, QMetaData::Public },
	{ "clearGraph()", &slot_34, QMetaData::Public },
	{ "setMultigraphStatus(bool)", &slot_35, QMetaData::Public },
	{ "saveEventCut()", &slot_36, QMetaData::Public },
	{ "changeStatus(QString)", &slot_37, QMetaData::Public },
	{ "selectGraphType(int)", &slot_38, QMetaData::Public },
	{ "viewData()", &slot_39, QMetaData::Public },
	{ "fillBranchNames()", &slot_40, QMetaData::Public },
	{ "languageChange()", &slot_41, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"MainForm", parentObject,
	slot_tbl, 42,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MainForm.setMetaObject( metaObj );
    return metaObj;
}

void* MainForm::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MainForm" ) )
	return this;
    return QMainWindow::qt_cast( clname );
}

bool MainForm::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: fileOpen(); break;
    case 1: fileSave(); break;
    case 2: fileSaveAllSingle(); break;
    case 3: fileSaveAllMultiple(); break;
    case 4: filePrint(); break;
    case 5: editUndo(); break;
    case 6: editRedo(); break;
    case 7: fileExit(); break;
    case 8: editCut(); break;
    case 9: editCopy(); break;
    case 10: editPaste(); break;
    case 11: helpIndex(); break;
    case 12: helpContents(); break;
    case 13: helpAbout(); break;
    case 14: enableDrawButton(); break;
    case 15: Draw(); break;
    case 16: applyRootCut(); break;
    case 17: txtEventCut_changed(); break;
    case 18: addNewTab(); break;
    case 19: enableTabActionButtons(); break;
    case 20: setTabAsCanvas((QWidget*)static_QUType_ptr.get(_o+1)); break;
    case 21: static_QUType_int.set(_o,getTabIndex()); break;
    case 22: static_QUType_int.set(_o,getTabIndex((int)static_QUType_int.get(_o+1))); break;
    case 23: static_QUType_int.set(_o,getTabIndex((QListViewItem*)static_QUType_ptr.get(_o+1))); break;
    case 24: selectTab((QListViewItem*)static_QUType_ptr.get(_o+1)); break;
    case 25: removeTab(); break;
    case 26: removeTab((int)static_QUType_int.get(_o+1)); break;
    case 27: renameTab(); break;
    case 28: renameTab((int)static_QUType_int.get(_o+1)); break;
    case 29: renameTab((QString)static_QUType_QString.get(_o+1)); break;
    case 30: renameTab((int)static_QUType_int.get(_o+1),(QString)static_QUType_QString.get(_o+2)); break;
    case 31: divideCanvas(); break;
    case 32: divideCanvas((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 33: addNewSubPad((int)static_QUType_int.get(_o+1)); break;
    case 34: clearGraph(); break;
    case 35: setMultigraphStatus((bool)static_QUType_bool.get(_o+1)); break;
    case 36: saveEventCut(); break;
    case 37: changeStatus((QString)static_QUType_QString.get(_o+1)); break;
    case 38: selectGraphType((int)static_QUType_int.get(_o+1)); break;
    case 39: viewData(); break;
    case 40: fillBranchNames(); break;
    case 41: languageChange(); break;
    default:
	return QMainWindow::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool MainForm::qt_emit( int _id, QUObject* _o )
{
    return QMainWindow::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool MainForm::qt_property( int id, int f, QVariant* v)
{
    return QMainWindow::qt_property( id, f, v);
}

bool MainForm::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
