/****************************************************************************
** formViewData meta object code from reading C++ file 'formviewdata.h'
**
** Created: Mon Jun 23 17:26:45 2008
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "formviewdata.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *formViewData::className() const
{
    return "formViewData";
}

QMetaObject *formViewData::metaObj = 0;
static QMetaObjectCleanUp cleanUp_formViewData( "formViewData", &formViewData::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString formViewData::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "formViewData", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString formViewData::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "formViewData", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* formViewData::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "rootTree", &static_QUType_ptr, "ReadRootTree", QUParameter::In }
    };
    static const QUMethod slot_0 = {"initialize", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ 0, &static_QUType_ptr, "std::vector<std::string>", QUParameter::In }
    };
    static const QUMethod slot_1 = {"setColumnNames", 1, param_slot_1 };
    static const QUMethod slot_2 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "initialize(ReadRootTree*)", &slot_0, QMetaData::Public },
	{ "setColumnNames(std::vector<std::string>)", &slot_1, QMetaData::Public },
	{ "languageChange()", &slot_2, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"formViewData", parentObject,
	slot_tbl, 3,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_formViewData.setMetaObject( metaObj );
    return metaObj;
}

void* formViewData::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "formViewData" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool formViewData::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: initialize((ReadRootTree*)static_QUType_ptr.get(_o+1)); break;
    case 1: setColumnNames((std::vector<std::string>)(*((std::vector<std::string>*)static_QUType_ptr.get(_o+1)))); break;
    case 2: languageChange(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool formViewData::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool formViewData::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool formViewData::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
