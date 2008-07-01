/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/
//#include "ColumnCollection.h"
#include <qlistview.h>
#include <vector>

#ifdef DEBUG
#include <iostream>
#endif


using namespace std;

ColumnCollection * cc;
vector<QCheckListItem*> items;
int currentItem = -1; // keep track of which item had been selected


void formChooseDisplayColumns::init()
{
    //don't auto sort the listview
	lv->setSorting(-1);
}

void formChooseDisplayColumns::initialize( ColumnCollection * c )
{
	cc = c;
	populate();
}

void formChooseDisplayColumns::populate()
{
	lv->clear();
	items.clear();

	for (int i = 0; i < (int) cc->columns.size(); ++i)
	    addItem(&(cc->columns[i]));
}

void formChooseDisplayColumns::addItem(singleColumn * c)
{
	if (!c) return;

	QCheckListItem * q = new QCheckListItem(lv,lv->lastItem(),
											"",QCheckListItem::CheckBox);

	q->setText(1,c->expression);
	q->setText(2,c->alias);
	q->setTristate(false);
	q->setState(c->shown? QCheckListItem::On:QCheckListItem::Off);

	items.push_back(q);
}


void formChooseDisplayColumns::editSingleItem( QListViewItem * item )
{
    // save previous changes if any
	saveChanges();

	// keep track of the index being selected so that when user reselects the
	// previous index is knonw
	currentItem = getIndex(item);

	txtAlias->setText(cc->columns[currentItem].alias);
	cmbExpression->setCurrentText(cc->columns[currentItem].expression);
}


int formChooseDisplayColumns::getIndex( QListViewItem *item )
{
	for (int i = 0; i < (int) items.size(); ++i)
	{
	    if (items[i] == (QCheckListItem*) item)
			return i;
	}

	return -1;
	
}


void formChooseDisplayColumns::saveChanges()
{
	if (currentItem != -1)
	{
		cout << "item " << currentItem <<  endl;
		
		cc->columns[currentItem].shown = items[currentItem]->isOn();
		cc->columns[currentItem].expression = cmbExpression->
			                                  currentText().ascii();
		cc->columns[currentItem].alias = txtAlias->text().ascii();
	}
}


void formChooseDisplayColumns::okClicked()
{
	saveChanges();
	accept();
}


void formChooseDisplayColumns::cancelClicked()
{
	reject();
}
