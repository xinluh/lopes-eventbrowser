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
#include "ReadRootTree.h"
#include "ColumnCollection.h"
#include "formChooseDisplayColumns.h"
#include "Helper.h"

#include <qfiledialog.h>
#include <qstatusbar.h>

#ifdef DEBUG
#include <iostream>
#endif

//#include <string>
//#include <vector>

using namespace std;

// max num of events to be fetched for display purpose
#define MAX_NUM_EVENTS 500

ReadRootTree * rootTree;
ColumnCollection * cols;


void formViewData::initialize( ReadRootTree * root_Tree )
{
	if (!root_Tree) throw "Must give a valid ReadRootTree object when init!";

	rootTree = root_Tree;

	txtEventCut->setCurrentText(rootTree->getEventCut());
	if (fileExists(COLUMN_FILE))
		cols = ColumnCollection::readFromFile();
	else
		cols = new ColumnCollection(rootTree->getBranchNames());
		
	setColumnNames();
	applyCut();
		
    setEnabled(true);
}


void formViewData::applyCut()
{
	rootTree->setEventCut(txtEventCut->currentText().ascii());
//	btnApplyCut->setEnabled(false);

	fetchData();


	
}

void formViewData::setColumnNames()
{
	vector<string> aliases = cols->getAliases(true);
	table->setNumCols(aliases.size());
	
	for (int i = 0; i < (int)aliases.size(); i++)
			table->horizontalHeader()->setLabel(i,aliases[i]);
}


int callback_fetchData(void* obj,int index, vector<string> values,
					   long total_n)
{
	index++;total_n++; // make compiler shut up about unused param
	 
	QTable* table = (QTable*) obj;
	int row = table->numRows();
	// insert new row
	table->setNumRows(table->numRows() + 1);

	for (int i = 0; i < ((table->numCols() < (int) values.size())?
			             table->numCols(): (int) values.size()); ++i)
	{
	    table->setText(row,i,values[i]);
		
	}

	if (index >= MAX_NUM_EVENTS)
		return 2; // time to abort; don't need anymore data
	else
		return 0;
	
}

void formViewData::fetchData()
{
	int retCode;
	// clear the table first
	table->setNumRows(0);

	// don't starting fetching if nothing is needed for display
	if (cols->size(true) == 0) return; 

	// make the table enabled/disabled to indicate visually whether the
	// data-fetching is still going on
	table->setEnabled(false);
	retCode = rootTree->fillValues_str(&callback_fetchData,
							 table,
							 cols->getExpressions(true));

	QString status  = QString("Current number of events: %1")
		.arg(rootTree->getNumberEntries());

	if (retCode == 2)
		status += QString("; NOTE: only the first %1 events are displayed!")
			.arg(MAX_NUM_EVENTS);

	cout << status << endl;
	
	
	//lblEventCutStatus->setText(status);
	statusBar()->message(status);
	table->setEnabled(true);
}


void formViewData::editColumns()
{
	// todo: important: make a copy of the ColumnCollection class before
	// sending it off for editing; otherwise after user canceled the result
	// could be bad...
    formChooseDisplayColumns f(this);
    f.initialize(cols);

	if (f.exec())
	{
		setColumnNames();
		fetchData();
	}
}

void formViewData::saveAsNewRoot()
{
	QString file = QFileDialog::getSaveFileName(
		            "newroot.root",
					"Root file (*.root)",
                    this,
                    tr("save file dialog"),
                    tr("Choose a filename to save under"));

	if (file) rootTree->saveToNewFile(file.ascii());
}
	
