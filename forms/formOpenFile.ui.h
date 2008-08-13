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
#include <string>
#include <vector>
#include <qfiledialog.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qmessagebox.h>

#include "Helper.h"
#include "ReadRootTree.h"

#ifdef DEBUG
#include <iostream>
#endif


using namespace std;

ReadRootTree * tree;


void formOpenFile::init()
{

}

void formOpenFile::initialize(ReadRootTree *t )
{
    vector<string> files;
    tree = t;

    if (!tree)
    {
        // must have valid root files; thus if ReadRootTree is null, user
        // cannot click cancel in this dialog
        buttonCancel->setEnabled(false);
        
        // get a list of files ending with .root in the current working
        // directory
        vector<string> files;
        getFileList("",files,"root");
        openFiles(files);
    }
    else
        openFiles(t->getListOfFiles());

    

}

// prompt with a open file dialog then call openFiles(vector<string> files)
void formOpenFile::openFiles()
{
    vector<string> files;
    
    QStringList vfiles = QFileDialog::getOpenFileNames(
                            "Root File (*.root)",
                            "",
                            this,
                            "Open files dialog",
                            "Select one or more root files to open" );

    if (vfiles.size() == 0) return;
    
    for ( QStringList::Iterator it = vfiles.begin(); it != vfiles.end(); ++it )
            files.push_back(*it);
    
    openFiles(files);
}

void formOpenFile::openFiles(vector<string> files)
{
    //todo: do some checking for multiple root files since they might contain
    //different TTrees which can be a problem when making a
    //TChain... currently the list of availabe TTrees comes from only the
    //first root files in the list

    bool hasFiles = (files.size() > 0);

    // first clean up the previous files if any
    if (hasFiles)
        lsbFiles->clear();

    // then add the new files to the listbox
    for (int i = 0; i < (int) files.size(); ++i)
        lsbFiles->insertItem(files[i]);

    if (hasFiles)
    {
        vector<string> trees;
        trees = ReadRootTree::getRootTreeNames(files[0]);

        cmbRootTree->clear();

        if (trees.size() == 0) // no ROOT tree found in file
        {
            QMessageBox::warning(this,"Error",
                   "No ROOT tree is found in " + files[0] + 
                   "; are you sure that you have a valid ROOT file? ");
            buttonOk->setEnabled(false);
            return;
        }

        // enable the other group boxes when there are files selected
        gbTree->setEnabled(hasFiles);
        gbBranch->setEnabled(hasFiles);
        buttonOk->setEnabled(true);
        
        // fill the root tree combobox with the trees from the root file
        for (int i = 0; i < (int) trees.size(); ++i)
        {
            cmbRootTree->insertItem(trees[i]);

            // select the tree currently selected in the ReadRootTree 
            if (tree && (trees[i] == tree->getTreeName()))
                cmbRootTree->setCurrentItem(cmbRootTree->count() - 1);
        }
            
        if (tree && (tree->getBranchFile()))
        {
            rbBranchFile->setChecked(true);
            txtBranchFile->setText(*(tree->getBranchFile()));
        }
        else
            rbBranchDefault->setChecked(true);
       
    }
}

void formOpenFile::openBranchFile()
{
    QString s = QFileDialog::getOpenFileName(
                    "",
                    "Config files (*.cfg *.txt *.*)",
                    this,
                    "Open file dialog",
                    "Choose a files containing branch definitions" );

    if (!s.isEmpty())
        txtBranchFile->setText(s);
}

void formOpenFile::okClicked()
{
    if (tree)
        delete tree;

    vector<string> files;

    for (int i = 0; i < (int) lsbFiles->count(); ++i)
        files.push_back(lsbFiles->item(i)->text());
    
    tree = new ReadRootTree(files,cmbRootTree->currentText(),
                            ((rbBranchDefault->isChecked() &&
                             !(txtBranchFile->text().isEmpty())) ?
                             txtBranchFile->text() : NULL));

    accept();
    
}


ReadRootTree* formOpenFile::getReadRootTree()
{
    return tree;
}
