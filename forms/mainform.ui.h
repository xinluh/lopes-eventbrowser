/****************************************************************************
** Ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/
#include "Draw.h"
#include "Canvas.h"
#include "Helper.h"
#include "formviewdata.h"
#include "CanvasCollection.h"
#include "formOpenFile.h"

#include <qstatusbar.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qinputdialog.h>
#include <qobjectlist.h>
#include "TQtWidget.h"

#include <string>
#include <vector>
#include <sstream>

#ifdef DEBUG
#include <iostream>
#endif

#define NOT_IMPLEMENTED QMessageBox::information(this, \
					    "Message","Sorry, not implemented yet." );

using namespace std;


//----------------------------------------------------------------------

Draw * draw = new Draw(); //the Draw object for drawing stuff

//pointers for creating new tab with TQtWidget in it
QWidget * newTab; // pointer to newly created tab
TQtWidget * newTqtw; // pointer to newly created TQtWidget
QVBoxLayout * newLayout; // pointer for laying out TQtWidget properly

// filters for saving to files
static string fileTypeFilterSingle = "Postscript (*.ps);;"
                                     "Root File (*.root);;"
                                     "Encapsulated Postscript (*.eps);;"
                                     "PDF (*.pdf);;"
                                     "JPEG (*.jpg);;"
                                     "GIF (*.gif);;"
                                     "C++ Macro (*.cxx)";
static string fileTypeFilterMultiple = "Postscript (*.ps);;"
                                       "Encapsulated Postscript (*.eps)";


// keeping track of the corresponding tabnames in the listview
// and the widgetstack
vector<int> tabIds;
vector<QListViewItem*> tabNames;
CanvasCollection canvases;

bool multiGraphCont = false;
// statusbar
QLabel* lblStatus;
QLabel* lblEventCutStatus;

//---------------------------------------------------------------------


void MainForm::init()
{
	//don't sort the listview - it messes up the order of inserting tabs
	lvGraphs->setSorting(-1);
	
	addNewTab();	
	
	// set up statusbar; important: don't attempt to write to status bar
	// before this!!!
	lblStatus = new QLabel("Ready",this);
	lblEventCutStatus = new QLabel("Current number of events: 00000",this);
	lblStatus->setMinimumSize(lblStatus->sizeHint());
	statusBar()->addWidget(lblStatus,1);
	statusBar()->addWidget(lblEventCutStatus);

	fileOpen();
	
}

void MainForm::fileOpen()
{
	formOpenFile f(this);
	f.initialize(draw->rootTree);
	
	if (f.exec())
	{
		draw->rootTree = f.getReadRootTree();
	}
	else if (!(draw->rootTree)) // for the first time when program opens
	{
		QMessageBox::critical(this,"Error",
 							  "You must select some root files to"
 							  "start with! The application will exit now.");
 		// todo: this does not work...
 		this->close();
 		return;
	}

	txtEventCut->setText("");
	applyRootCut();
	fillBranchNames();

	this->setCaption("Browser - " +
					 joinStrings(draw->rootTree->getListOfFiles(),"; "));
	//changeStatus("Opened files: " + joinStrings(filenames, ", "));
}

void MainForm::fileSave()
{
	QString file = QFileDialog::getSaveFileName(
		           validateFilename(tabNames[getTabIndex()]->text(0)),
					fileTypeFilterSingle,
                    this,
                    tr("save file dialog"),
                    tr("Choose a filename to save under"));


	if (file) draw->saveAs(NULL,file.ascii());
}


void MainForm::fileSaveAllSingle()
{
	int tabcount = (int) tabIds.size();
	TQtWidget * tqtw;

	if (tabcount < 1) return;

	QString file = QFileDialog::getSaveFileName("",
					fileTypeFilterMultiple,
                    this,
                    tr("save file dialog"),
                    tr("Choose a filename to save under"));

	if (!file) return;

	//open for saving multiple canvas in one file
	draw->saveAs(NULL,file.ascii(),Draw::OPEN_ONLY); 
	
	for (int i = 0; i<tabcount ; i++)
	{
		tqtw = (TQtWidget*) wgStack->widget(tabIds[i])
			    ->child("tqtw","TQtWidget", FALSE);
		if (tqtw)
		{
			draw->saveAs(tqtw->GetCanvas(),file.ascii());
		}
	}

	draw->saveAs(NULL,file.ascii(),Draw::CLOSE_ONLY);
}

void MainForm::fileSaveAllMultiple()
{
	NOT_IMPLEMENTED
}


void MainForm::filePrint()
{
	NOT_IMPLEMENTED
}


void MainForm::editUndo()
{
	NOT_IMPLEMENTED
}

void MainForm::editRedo()
{
	NOT_IMPLEMENTED
}

void MainForm::fileExit()
{
	NOT_IMPLEMENTED
}

void MainForm::editCut()
{
	NOT_IMPLEMENTED
}


void MainForm::editCopy()
{
	NOT_IMPLEMENTED
}


void MainForm::editPaste()
{
	NOT_IMPLEMENTED
}


void MainForm::helpIndex()
{
	NOT_IMPLEMENTED
}


void MainForm::helpContents()
{
	NOT_IMPLEMENTED
}


void MainForm::helpAbout()
{
	NOT_IMPLEMENTED
}


void MainForm::enableDrawButton()
{
	// the draw button should be disabled if not everything neccesary for
	// for drawing the specific graph is present
	
	if (wgsAction->visibleWidget() == tabGraph2D)
	{
		btnDraw->setEnabled(!txt2DXAxis->text().isEmpty() &&
			                !txt2DYAxis->text().isEmpty());
		if (ckb2DErrors->isChecked())
			btnDraw->setEnabled(!txt2DXAxisError->text().isEmpty() &&
								!txt2DYAxisError->text().isEmpty());
	}
	else if (wgsAction->visibleWidget() == tabPosition)
	{
		btnDraw->setEnabled(true);
	}
	else if (wgsAction->visibleWidget() == tabShowerAngles)
	{
		btnDraw->setEnabled(!txtPolarRAxis->text().isEmpty() &&
			                !txtPolarThetaAxis->text().isEmpty());
		if (ckb2DErrors->isChecked())
			btnDraw->setEnabled(!txtPolarRAxisError->text().isEmpty() &&
								!txtPolarThetaAxisError->text().isEmpty());
	}
}



void MainForm::Draw()
{
	if (ckbNewTab->isChecked())
		addNewTab();

// 	if (ckbMultiGraph->isChecked() && multiGraphCont)
// 	{
// 		draw->beginMultigraph();
// 		multiGraphCont = true;
// 	}
	
	if (wgsAction->visibleWidget() == tabPosition)
	{
		switch (cmbPositionType->currentItem())
		{
			case 0:
				draw->drawGrandeCoordinates();
				renameTab("Grande Coordinates");
				break;
			case 1:
				draw->drawAntennaPosition();
				renameTab("Antenna Position");
				break;
		}
	}
	else if (wgsAction->visibleWidget() == tabGraph2D)
	{
		cout << "x" <<txt2DXAxis->text().ascii() << endl;
		cout << "y" << txt2DYAxis->text().ascii() << endl; 

		draw->draw2DGraph(txt2DXAxis->text().ascii(),
						  txt2DYAxis->text().ascii(),
			(ckb2DErrors->isChecked())? txt2DXAxisError->text().ascii() : NULL,
			(ckb2DErrors->isChecked())? txt2DYAxisError->text().ascii() : NULL
			 );

		renameTab(txt2DXAxis->text() + " - " + txt2DYAxis->text());
	}
	else if (wgsAction->visibleWidget() == tabShowerAngles)
	{
		cout << "r=" <<txtPolarRAxis->text().ascii() << endl;
		draw->drawShowerAngles(txtPolarRAxis->text().ascii(),
						       txtPolarThetaAxis->text().ascii(),
							   txtColorCode->text().ascii()	);
		
		renameTab(txtEventCut->text());
	}
}




void MainForm::applyRootCut()
{
	if (!draw->rootTree) return;
	
	draw->rootTree->setEventCut(txtEventCut->text().ascii());
	btnApplyCut->setEnabled(false);

	QString status  = QString("Current number of events: %1")
		.arg(draw->rootTree->getNumberEntries());

	cout << status << endl;

	lblEventCutStatus->setText(status);
}


void MainForm::txtEventCut_changed()
{
	btnApplyCut->setEnabled(true);
}

void MainForm::addNewTab(Canvas* c)
{
	if (!c) return;
	
	int id = -1;
	QListViewItem * item;
	
	newTab = new QWidget(wgStack,"tab_"); //todo add number!
	newTqtw = new TQtWidget(newTab,"tqtw");
	newLayout = new QVBoxLayout(newTab,0,6,"tabLayout");
	newLayout->addWidget(newTqtw);
	
	id = wgStack->addWidget(newTab);

	if (id != -1)
	{
		tabIds.push_back(id);

		//create an item after the last one in the listview
		item = new QListViewItem(lvGraphs,
			  (tabNames.size() == 0)? 0 : tabNames[(int)tabNames.size() - 1],
								 c->getName());
		tabNames.push_back(item);
		
		//focus on the newly created tab
		lvGraphs->setSelected(item,true);

		// make sure that the correct TQtWidget is the current Canvas
		setTabAsCanvas(newTab);
	}

}

void MainForm::addNewTab()
{
	Canvas *c = new Canvas();
	c->setName("Untitled Canvas");

	if (wgsAction->visibleWidget() == tabPosition)
		c->setGraphType(Canvas::ANTENNA_POSITION);
	else if (wgsAction->visibleWidget() == tabGraph2D)
		c->setGraphType(Canvas::GRAPH_2D);
	else if (wgsAction->visibleWidget() == tabShowerAngles)
		c->setGraphType(Canvas::SHOWER_ANGLE);
	
//	int tabcount = tabsGraph->count();
	int id = -1;
	QListViewItem * item;
	
	newTab = new QWidget(wgStack,"tab_"); //todo add number!
	newTqtw = new TQtWidget(newTab,"tqtw");
	newLayout = new QVBoxLayout(newTab,0,6,"tabLayout");
	newLayout->addWidget(newTqtw);
	
	id = wgStack->addWidget(newTab);

	if (id != -1)
	{
		tabIds.push_back(id);

		ostringstream ss;
		ss << "Untitled Canvas " << id;

		//create an item after the last one in the listview
		item = new QListViewItem(lvGraphs,
			  (tabNames.size() == 0)? 0 : tabNames[(int)tabNames.size() - 1],
								 ss.str());
		tabNames.push_back(item);
		
		//focus on the newly created tab
		lvGraphs->setSelected(item,true);

		// make sure that the correct TQtWidget is the current Canvas
		setTabAsCanvas(newTab);
	}
}



void MainForm::enableTabActionButtons()
{
	bool y = (getTabIndex() != -1);
	
	btnRemoveTab->setEnabled(y);
	btnRenameTab->setEnabled(y);
}


void MainForm::setTabAsCanvas( QWidget * qw )
{
	// find the TQtWidget belong to the tab page
	TQtWidget * tqtw = (TQtWidget*) qw->child("tqtw","TQtWidget", FALSE);
	// if found, set it as current canvas for drawing
	if (tqtw) draw->setCanvas(tqtw->GetCanvas());
}


// get the index in the arrays tabIds and tabNames for the currently selected
int MainForm::getTabIndex()
{
	return getTabIndex(lvGraphs->selectedItem());
}



int MainForm::getTabIndex( int widgetID )
{
	int id = (widgetID == 0)? wgStack->id(wgStack->visibleWidget()) : widgetID;

	if (id == 0) return -1;

	for (int i = 0; i < (int)tabIds.size(); i++)
		if (tabIds[i] == id) return i;

	return -1;
}


int MainForm::getTabIndex( QListViewItem * item )
{
	if (!item) return -1;
	
	// find the index for item corresponding to this QListViewItem
	for (int i = 0; i < (int)tabIds.size(); i++)
		if (tabNames[i] == item) return i;

    return -1;
}


void MainForm::selectTab( QListViewItem * sel)
{
	multiGraphCont = false; // make sure that a new graph with axis is started
	
	int index = (sel)? getTabIndex(sel) : getTabIndex();
	int id;
//	int subpad;

	if (index < 0) //not a canvas; select subpad if applicable
	{
		if (!sel || !sel->parent()) return;

		index = getTabIndex(sel->parent());

		if (index < 0) return;

		// todo cd to the subpad
	}

	id = tabIds[index];
	
	//cout << "id = " << id << endl;
	
	if (id == 0)
		wgStack->raiseWidget(wgStack->id(wgEmtpyPage));
	else
		wgStack->raiseWidget(id);
}


void MainForm::removeTab()
{
	int index = getTabIndex();
	if (index > -1)
		removeTab(index);
}


void MainForm::removeTab( int index )
{
	if (index < 0 || index > (int) tabIds.size()) return;

	// the new index to be selected
	int s_index = ((index == (int)tabIds.size() - 1)?
				   (index - 1) : (index + 1));

	cout << "select index " << s_index << endl;
	
 	// select the tab above
	selectTab(tabNames[s_index]); 

	delete tabNames[index];

	tabIds.erase(tabIds.begin() +  index);
	tabNames.erase(tabNames.begin() + index);
}


void MainForm::renameTab()
{
	int index = getTabIndex();
	if (index > -1)
		renameTab(index);
}


void MainForm::renameTab( int index )
{
	if (index < 0 || index > (int) tabIds.size()) return;

	bool ok;
	
	QString name = QInputDialog::getText(tr("Rename Canvas"),
										 tr("Enter a new name:"),
										 QLineEdit::Normal,
										 tabNames[index]->text(0),
										 &ok,
										 this);
	if (ok && !name.isEmpty())
		renameTab(index,name);
}

void MainForm::renameTab(QString name)
{
	int index = getTabIndex();
	if (index > -1)
		renameTab(index,name);
}

void MainForm::renameTab(int index, QString name)
{
	if (index < 0 || index > (int) tabIds.size()) return;


	QListViewItem * item = tabNames[index];
		
	if (item)
		item->setText(0,name);
}


void MainForm::divideCanvas()
{
	bool ok;
	
	QString s = QInputDialog::getText(tr("Divide Canvas"),
									  tr("How to divide? e.g. 3x2"),
									  QLineEdit::Normal,
									  "2x2",
									  &ok,
									  this);
	if (ok && !s.isEmpty())
	{
		// todo: really parse the string instead of dirty ifelse statement ^_^

		if (s == "2x2")
			divideCanvas(2,2);
		else if (s == "3x2")
			divideCanvas(3,2);
		else if (s ==  "4x2")
			divideCanvas(4,2);
		else if (s ==  "3x3")
			divideCanvas(3,3);
		else
			NOT_IMPLEMENTED
	     
	}	
}

void MainForm::divideCanvas(int n_columns, int n_rows)
{
	draw->divideCanvas(n_columns,n_rows);
	addNewSubPad(n_rows * n_columns);
}


void MainForm::addNewSubPad( int n_subpad )
{
	QListViewItem * parent_item = tabNames[getTabIndex()];

	if (!parent_item) return;
	
	QListViewItem * child_item, *after_item;
	ostringstream ss;

	after_item = parent_item->firstChild();
	
	// find the last child under the parent_item
	if (after_item)
	{
		while (after_item->nextSibling() != 0)
			after_item = after_item->nextSibling();
	}
	

	for (int i = 1; i <= n_subpad; i++)
	{
		ss.str("");
		ss << "Pad " << i;
		
		if (after_item)
			child_item = new QListViewItem(parent_item,after_item,ss.str());
		else
			child_item = new QListViewItem(parent_item,ss.str());

		after_item = child_item;
	}

	parent_item->setOpen(true);
}



void MainForm::clearGraph()
{
	draw->clearCanvas();
}


void MainForm::setMultigraphStatus( bool state )
{
	draw->setMultiGraph(state);
}


void MainForm::saveEventCut()
{
	cmbEventCuts->insertItem(txtEventCut->text());
}


void MainForm::changeStatus(QString status)
{
    lblStatus->setText(status);
}

void MainForm::selectGraphType( int index )
{
	switch (index)
	{
		case 0:
			wgsAction->raiseWidget(tabGraph2D);
			break;
		case 1:
			wgsAction->raiseWidget(tabShowerAngles);
			break;
		case 2:
			wgsAction->raiseWidget(tabPosition);
	}
}


void MainForm::viewData()
{
    formViewData* f = new formViewData(this);
    f->initialize(draw->rootTree);
    f->show();
	f->raise();
	f->setActiveWindow();
}


void MainForm::fillBranchNames()
{
	if (!draw->rootTree) return;

	cmbBranchNames->clear();
	
	vector<string> names = draw->rootTree->getBranchNames();
	for (int i = 0; i < (int) names.size(); i++)
		cmbBranchNames->insertItem(names[i]);
}


void MainForm::insertBranchName( const QString& name )
{
	// find the QLineEdit or QTextEdit that has focus and append the branch
	// name to it; the find method relies on the fact that all the textboxes
	// are named with prefix txt
	QObjectList *l = topLevelWidget()->queryList(NULL,"txt*");
    QObjectListIt it( *l );
	QWidget* w;
		
    while ((w = (QWidget*) it.current()) != 0 )
	{
		++it;
		if (w->hasFocus())
		{
			if (dynamic_cast<QLineEdit*>(w) != 0)
			{
				((QLineEdit*)w)->setText(((QLineEdit*)w)->text() + name);
				break;
			}

			if ((QTextEdit*)w != 0)
			{
				((QTextEdit*)w)->setText(((QTextEdit*)w)->text() + name);
				break;
			}
		}
    }

    delete l; 
}

