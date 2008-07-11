#include <qapplication.h>
#include <iostream>
#include "qstring.h"
#include "mainform.h"



using namespace std;

int main( int argc, char *argv[] ) 
{
	QApplication *app = new QApplication(argc, argv);
	app->connect( app, SIGNAL( lastWindowClosed() ), app, SLOT( quit() ) );

	cout << "Application starting..." << endl;
	
	
	MainForm f;
	
	
	f.show();

	app->exec();
	return 0;
}
