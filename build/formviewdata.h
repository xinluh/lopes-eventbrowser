/****************************************************************************
** Form interface generated from reading ui file 'forms/formviewdata.ui'
**
** Created: Mon Jun 23 17:26:22 2008
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.7   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FORMVIEWDATA_H
#define FORMVIEWDATA_H

#include <qvariant.h>
#include <qdialog.h>
#include <string>
#include <vector>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QTable;
class ReadRootTree;

class formViewData : public QDialog
{
    Q_OBJECT

public:
    formViewData( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~formViewData();

    QTable* table;

public slots:
    virtual void initialize( ReadRootTree * rootTree );
    virtual void setColumnNames( std::vector<std::string> );

protected:
    QHBoxLayout* formViewDataLayout;

protected slots:
    virtual void languageChange();

};

#endif // FORMVIEWDATA_H
