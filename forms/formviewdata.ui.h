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

#ifdef DEBUG
#include <iostream>
#endif

//#include <string>
//#include <vector>

using namespace std;

// max num of events to be fetched for display purpose
#define MAX_NUM_EVENTS 500

ReadRootTree * rootTree;


void formViewData::initialize( ReadRootTree * root_Tree )
{
	if (!root_Tree) throw "Must give a valid ReadRootTree object when init!";

	rootTree = root_Tree;
		
	setColumnNames(rootTree->getBranchNames());
	//table->setNumRows(6);
	fetchData(rootTree->getBranchNames());
	
	
    setEnabled(true);
}


void formViewData::setColumnNames( vector<string> names )
{
	table->setNumCols(names.size());
	for (int i = 0; i < (int) names.size(); i++)
			table->horizontalHeader()->setLabel(i,names[i]);
}

int callback_fetchData(void* obj,int index, vector<string> values,
					   long total_n)
{
	QTable* table = (QTable*) obj;
	int row = table->numRows();
	// insert new row
	table->setNumRows(table->numRows() + 1);

	for (int i = 0; i < ((table->numCols() < (int) values.size())?
			             table->numCols(): (int) values.size()); ++i)
	{
	    table->setText(row,i,values[i]);
		
	}

	if (index > MAX_NUM_EVENTS)
		return 2; // time to abort; don't need anymore data
	else
		return 0;
	
}

void formViewData::fetchData(vector<string> column_expressions)
{
	rootTree->fillValues_str(&callback_fetchData,table,column_expressions);
}
