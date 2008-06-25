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

#define MAX_NUM_EVENTS 500

void formViewData::initialize( ReadRootTree * rootTree )
{
	if (!rootTree) return;

	setColumnNames(rootTree->getBranchNames());
	table->setNumRows(6);
	
    setEnabled(true);
}


void formViewData::setColumnNames( vector<string> names )
{
	table->setNumCols(names.size());
	for (int i = 0; i < (int) names.size(); i++)
			table->horizontalHeader()->setLabel(i,names[i]);
}
