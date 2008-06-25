/****************************************************************************
** Form implementation generated from reading ui file 'forms/formviewdata.ui'
**
** Created: Tue Jun 24 15:19:25 2008
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "formviewdata.h"

#include <qvariant.h>
#include <qtable.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "../forms/formviewdata.ui.h"

/*
 *  Constructs a formViewData as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
formViewData::formViewData( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "formViewData" );
    setEnabled( FALSE );
    setSizeGripEnabled( TRUE );
    formViewDataLayout = new QHBoxLayout( this, 11, 6, "formViewDataLayout"); 

    table = new QTable( this, "table" );
    table->setNumRows( 3 );
    table->setNumCols( 3 );
    formViewDataLayout->addWidget( table );
    languageChange();
    resize( QSize(745, 684).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
}

/*
 *  Destroys the object and frees any allocated resources
 */
formViewData::~formViewData()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void formViewData::languageChange()
{
    setCaption( tr( "View Tree Data" ) );
}

