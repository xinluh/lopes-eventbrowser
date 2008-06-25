/****************************************************************************
** Draw meta object code from reading C++ file 'Draw.h'
**
** Created: Tue Jun 17 13:30:57 2008
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../Draw.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *Draw::className() const
{
    return "Draw";
}

QMetaObject *Draw::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Draw( "Draw", &Draw::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString Draw::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Draw", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Draw::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Draw", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Draw::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QObject::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"Draw", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_Draw.setMetaObject( metaObj );
    return metaObj;
}

void* Draw::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "Draw" ) )
	return this;
    return QObject::qt_cast( clname );
}

bool Draw::qt_invoke( int _id, QUObject* _o )
{
    return QObject::qt_invoke(_id,_o);
}

bool Draw::qt_emit( int _id, QUObject* _o )
{
    return QObject::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool Draw::qt_property( int id, int f, QVariant* v)
{
    return QObject::qt_property( id, f, v);
}

bool Draw::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
