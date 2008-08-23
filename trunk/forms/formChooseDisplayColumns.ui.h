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
#include <qmessagebox.h>
#include <vector>
#include "Helper.h"

#include <Q3CheckListItem>
#ifdef DEBUG
#include <iostream>
#endif


using namespace std;

ColumnCollection * cc;
vector<Q3CheckListItem*> items;
int currentItem = -1; // keep track of which item had been selected


void formChooseDisplayColumns::init()
{
    //don't auto sort the listview
    lv->setSorting(-1);
}

void formChooseDisplayColumns::initialize( ColumnCollection * collection )
{
    cc = collection;
    populate();
}

void formChooseDisplayColumns::populate()
{
    lv->clear();
    items.clear();

    for (int i = 0; i < (int) cc->columns.size(); ++i)
        addItem(cc->columns[i]);

    lv->setSelected(items[0],true);
}

int formChooseDisplayColumns::addItem(singleColumn * c)
{
    if (!c) return -1;

    Q3CheckListItem * q = new Q3CheckListItem(lv,lv->lastItem(),
                                            "",Q3CheckListItem::CheckBox);

    q->setText(1,s(c->expression));
    q->setText(2,s(c->alias));
    q->setTristate(false);
    q->setState(c->shown? Q3CheckListItem::On : Q3CheckListItem::Off);

    items.push_back(q);
    
    return (int)items.size() - 1;
}


void formChooseDisplayColumns::editSingleItem( Q3ListViewItem * item )
{
    // save previous changes if any
    saveChanges();

//    if (!item) {gbEdit->setEnabled(false); return;}

    // keep track of the index being selected so that when user reselects the
    // previous index is knonw
    currentItem = getIndex(item);

    txtAlias->setText(s(cc->columns[currentItem]->alias));
    cmbExpression->setCurrentText(s(cc->columns[currentItem]->expression));
}


int formChooseDisplayColumns::getIndex( Q3ListViewItem *item )
{
    for (int i = 0; i < (int) items.size(); ++i)
    {
        if (items[i] == (Q3CheckListItem*) item)
            return i;
    }

    return -1;
    
}


void formChooseDisplayColumns::saveChanges()
{
    if (txtAlias->text().isEmpty() && !cmbExpression->currentText().isEmpty())
      txtAlias->setText(s(validateFilename(
                          cmbExpression->currentText().toStdString())));
    
    if (currentItem != -1 && !cmbExpression->currentText().isEmpty() &&
        !txtAlias->text().isEmpty())
    {
        cc->columns[currentItem]->shown = items[currentItem]->isOn();
        cc->columns[currentItem]->expression = cmbExpression->
                                              currentText().ascii();
        cc->columns[currentItem]->alias = txtAlias->text().ascii();
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


void formChooseDisplayColumns::addNewItem()
{
    singleColumn *s  = new singleColumn("new_exp");

    cc->addColumn(s);
    lv->setSelected((Q3ListViewItem*) items[addItem(s)],true);
}


void formChooseDisplayColumns::deleteItem( int index )
{
    cc->print();
    
    cc->removeColumn(index);
    
    delete items[index];
    items.erase(items.begin()+index);

    cc->print();
                          
}


void formChooseDisplayColumns::deleteItem()
{
    cout << "delete item " << currentItem << endl;

    deleteItem(currentItem);
}


void formChooseDisplayColumns::saveColumnsToFile()
{
    cc->saveToFile();
    QMessageBox::information(this,"Columns configuration saved",
                             "The configuration of the columns are saved "
                             "to a file called columns.cfg in the program "
                             "directory. You can delete or edit this file, "
                             "and if this file is found its content  will be "
                             "automatically read.");
}
