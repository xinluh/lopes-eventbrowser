#include "CanvasCollection.h"

#ifdef DEBUG
#include <iostream>

#endif

using namespace std;

CanvasCollection::CanvasCollection() {};

CanvasCollection::~CanvasCollection()
{
	for (int i = 0; i < (int) canvases.size(); ++i)
	{
	    delete canvases[i];
	}
}

void CanvasCollection::removeCanvas(int index)
{
	delete canvases[index];
	canvases.erase(canvases.begin() + index);
}

// CanvasCollection* CanvasCollection::clone()
// {
// 	CanvasCollection *c = new CanvasCollection();
// 	c->canvases.resize(canvases.size());
// 	for (int i = 0; i < (int) canvases.size(); ++i)
// 	{
// 	    c->canvases[i] = canvases[i];
// 	}
// 	return c;
// }

void CanvasCollection::print()
{
	cout << "-----------------------------------" << endl;
	for (int i = 0; i <(int) canvases.size(); ++i)
	{
	
		cout << canvases[i]->getName() << endl;
	}
		
}

void CanvasCollection::saveToFile()
{
// 	ofstream file;
// 	file.open (COLUMN_FILE, ios::trunc);
// 	if (file.is_open())
// 	{
// 		for (int i = 0; i < (int) canvases.size(); ++i)
// 		{
// 		    file << ((canvases[i]->shown)? 1 : 0);
// 			file << CFG_SEPARATOR;
// 			file << canvases[i]->expression;
// 			file << CFG_SEPARATOR;
// 			file << canvases[i]->alias;
// 			file << "\n";
// 		}
// 		file.close();
// 	}
}

CanvasCollection* CanvasCollection::readFromFile()
{
// 	ifstream f(COLUMN_FILE);

// 	string shown,exp,alias;

// 	CanvasCollection* cc = new CanvasCollection;
// 	Canvas *c;

// 	while (!getline(f,shown,CFG_SEPARATOR).eof())
// 	{
// 		getline(f,exp,CFG_SEPARATOR);
// 		getline(f,alias);

// 		c = new Canvas((shown == "1")? true : false, exp, alias);
// 		cc->addCanvas(c);
// 	}

// 	return cc;
}
