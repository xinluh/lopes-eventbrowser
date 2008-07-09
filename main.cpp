#include <qapplication.h>
/*#include "TGraph.h"
#include "TQtWidget.h"
#include "TCanvas.h"
#include "qstring.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>*/
#include <iostream>
#include "qstring.h"
#include "mainform.h"
#include "ReadRootTree.h"
#include "muParser.h"
#include <vector>
#include <string>
#include "Helper.h"

using namespace std;

const char * datafile = "tree-ka104ev.root";

int main( int argc, char *argv[] ) 
{
	QApplication *app = new QApplication(argc, argv);
	app->connect( app, SIGNAL( lastWindowClosed() ), app, SLOT( quit() ) );

/*	mu::Parser p;
	float f1 = 2 ;
	p.DefineVar("a",&f1);
	p.SetExpr("a + a");
	cout << p.Eval()<< endl;*/
	
//	datafile = new QString("doo1");

//	cout << ValidateFilename("askgjakjdf##g_f,gkja") << endl;
	
	cout << "---------------------------" << endl << endl << endl;
	cout << datafile << endl;
	cout << "---------------------------" << endl << endl << endl;

	
	
//	ReadRootTree * r = new ReadRootTree("tree-ka104ev.root","T");
	
	MainForm f;
	
	
	f.show();

/*
	cout <<"dd" << endl; 
//	r->setEventFilter("CCheight_EW>1.8 && CCheight_EW<30 && CCheight_NS>1.8 && CCheight_NS<30 && Gt>0 && CurvR_EW>0 && Mean_daxis_EW>0 && AzL_ew>0  && ElL_ew>0 && Size>0 && Nmu>0 && CCheight_error_EW>0 && CCheight_error_NS>0 && CCheight_error_EW<5 && CCheight_error_NS<5");

	string a[] = {"Size","Size*2","Size","Size","Size","Size"};
	
	cout << r->branches[0] << endl;


r->fillValues(NULL,NULL,a);

 cout << "heee" << endl; 
*/
	
	app->exec();
	return 0;
}

