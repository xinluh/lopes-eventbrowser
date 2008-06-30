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

using namespace std;

ColumnCollection * cc;
vector<QCheckListItem*> items;
int currentItem; // keep track of which item had been selected


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
	if (currentItem != -1) // commit the change
	{
		cc->columns[currentItem].shown = items[currentItem]->isOn();
		cc->columns[currentItem].expression = items[currentItem]->
			text(1).ascii();
		cc->columns[currentItem].alias = items[currentItem]->text(2).ascii();
	}

	currentItem = getIndex(item);	
	QCheckListItem *q = (QCheckListItem*) item;

	ckbShown->setChecked(q->isOn());
	txtAlias->setText(q->text(2));
	cmbExpression->setCurrentText(q->text(1));
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
