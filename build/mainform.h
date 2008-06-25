/****************************************************************************
** Form interface generated from reading ui file 'forms/mainform.ui'
**
** Created: Tue Jun 24 15:55:29 2008
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef MAINFORM_H
#define MAINFORM_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qmainwindow.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QAction;
class QActionGroup;
class QToolBar;
class QPopupMenu;
class QSplitter;
class QToolButton;
class QListView;
class QListViewItem;
class QWidgetStack;
class QWidget;
class QLabel;
class QTabWidget;
class QLineEdit;
class QGroupBox;
class QTextEdit;
class QComboBox;
class QPushButton;
class QCheckBox;

class MainForm : public QMainWindow
{
    Q_OBJECT

public:
    MainForm( QWidget* parent = 0, const char* name = 0, WFlags fl = WType_TopLevel );
    ~MainForm();

    QSplitter* splitter1;
    QToolButton* btnAddNewTab;
    QToolButton* btnRemoveTab;
    QToolButton* btnRenameTab;
    QListView* lvGraphs;
    QWidgetStack* wgStack;
    QWidget* wgEmtpyPage;
    QLabel* textLabel1_4;
    QWidget* qt_dead_widget_WStackPage;
    QTabWidget* tabsAction;
    QWidget* tabRootTree;
    QLabel* textLabel2_2;
    QLineEdit* txtNumberEvents;
    QGroupBox* groupBox3;
    QTextEdit* txtEventCut;
    QLabel* textLabel1_3_2;
    QComboBox* cmbEventCuts;
    QLabel* textLabel1_3_2_2;
    QComboBox* cmbBranchNames;
    QPushButton* btnApplyCut;
    QPushButton* btnSaveCut;
    QPushButton* btnViewData;
    QLabel* textLabel1;
    QComboBox* cmbGraphType;
    QWidgetStack* wgsAction;
    QWidget* tabGraph2D;
    QLabel* textLabel3;
    QLineEdit* txt2DXAxis;
    QLabel* textLabel4;
    QLineEdit* txt2DYAxis;
    QCheckBox* ckb2DErrors;
    QGroupBox* gb2DErrors;
    QLabel* textLabel3_2;
    QLineEdit* txt2DXAxisError;
    QLabel* textLabel4_2;
    QLineEdit* txt2DYAxisError;
    QWidget* tabShowerAngles;
    QLineEdit* txtPolarRAxis;
    QLabel* textLabel4_3;
    QLabel* textLabel3_3;
    QLabel* textLabel1_5;
    QLineEdit* txtPolarThetaAxis;
    QLineEdit* txtColorCode;
    QCheckBox* ckbPolarErrors;
    QGroupBox* gbPolarErrors;
    QLabel* textLabel3_2_2;
    QLineEdit* txtPolarRAxisError;
    QLabel* textLabel4_2_2;
    QLineEdit* txtPolarThetaAxisError;
    QWidget* tabPosition;
    QComboBox* comboBox1;
    QCheckBox* ckbNewTab;
    QCheckBox* ckbMultiGraph;
    QPushButton* btnClear;
    QPushButton* btnDraw;
    QMenuBar *MenuBar;
    QPopupMenu *fileMenu;
    QPopupMenu *popupMenu_4;
    QPopupMenu *Edit;
    QPopupMenu *helpMenu;
    QAction* fileNewAction;
    QAction* fileOpenAction;
    QAction* fileSaveAction;
    QAction* fileSaveAsAction;
    QAction* filePrintAction;
    QAction* fileExitAction;
    QAction* editUndoAction;
    QAction* editRedoAction;
    QAction* editCutAction;
    QAction* editCopyAction;
    QAction* editPasteAction;
    QAction* editFindAction;
    QAction* helpContentsAction;
    QAction* helpIndexAction;
    QAction* helpAboutAction;
    QAction* fileSave_AllAction;
    QAction* fileSave_AllSingle_PostscriptAction;
    QAction* fileSave_AllSeparate_PostscritpsAction;
    QAction* editDivide_CanvasAction;
    QAction* editDivide_Canvas2_x_2Action;
    QAction* editDivide_Canvas3_x_2Action;
    QAction* editDivide_Canvas4_x_2Action;

public slots:
    virtual void fileOpen();
    virtual void fileSave();
    virtual void fileSaveAllSingle();
    virtual void fileSaveAllMultiple();
    virtual void filePrint();
    virtual void editUndo();
    virtual void editRedo();
    virtual void fileExit();
    virtual void editCut();
    virtual void editCopy();
    virtual void editPaste();
    virtual void helpIndex();
    virtual void helpContents();
    virtual void helpAbout();
    virtual void enableDrawButton();
    virtual void Draw();
    virtual void applyRootCut();
    virtual void txtEventCut_changed();
    virtual void addNewTab();
    virtual void enableTabActionButtons();
    virtual void setTabAsCanvas( QWidget * qw );
    virtual int getTabIndex();
    virtual int getTabIndex( int widgetID );
    virtual int getTabIndex( QListViewItem * item );
    virtual void selectTab( QListViewItem * sel );
    virtual void removeTab();
    virtual void removeTab( int index );
    virtual void renameTab();
    virtual void renameTab( int index );
    virtual void renameTab( QString name );
    virtual void renameTab( int index, QString name );
    virtual void divideCanvas();
    virtual void divideCanvas( int n_columns, int n_rows );
    virtual void addNewSubPad( int n_subpad );
    virtual void clearGraph();
    virtual void setMultigraphStatus( bool state );
    virtual void saveEventCut();
    virtual void changeStatus( QString status );
    virtual void selectGraphType( int index );
    virtual void viewData();
    virtual void fillBranchNames();

protected:
    QVBoxLayout* MainFormLayout;
    QVBoxLayout* layout26;
    QHBoxLayout* layout25;
    QSpacerItem* spacer5;
    QHBoxLayout* wgEmtpyPageLayout;
    QHBoxLayout* layout15;
    QHBoxLayout* layout13;
    QHBoxLayout* layout11;
    QSpacerItem* spacer4;
    QHBoxLayout* layout22;
    QVBoxLayout* groupBox3Layout;
    QHBoxLayout* layout29;
    QHBoxLayout* layout21;
    QHBoxLayout* layout40;
    QVBoxLayout* layout25_2;
    QHBoxLayout* layout24;
    QSpacerItem* spacer7;
    QHBoxLayout* tabGraph2DLayout;
    QVBoxLayout* layout12;
    QSpacerItem* spacer2;
    QHBoxLayout* layout5;
    QHBoxLayout* layout6;
    QVBoxLayout* gb2DErrorsLayout;
    QHBoxLayout* layout8;
    QHBoxLayout* layout9;
    QVBoxLayout* tabShowerAnglesLayout;
    QGridLayout* layout23;
    QVBoxLayout* gbPolarErrorsLayout;
    QHBoxLayout* layout8_2;
    QHBoxLayout* layout9_2;
    QHBoxLayout* layout24_2;
    QSpacerItem* spacer1;

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;
    QPixmap image1;
    QPixmap image2;
    QPixmap image3;
    QPixmap image4;
    QPixmap image5;
    QPixmap image6;
    QPixmap image7;
    QPixmap image8;
    QPixmap image9;
    QPixmap image10;
    QPixmap image11;
    QPixmap image12;

    void init();

};

#endif // MAINFORM_H
