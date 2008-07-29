#ifndef _CANVASCOLLECTION_H_
#define _CANVASCOLLECTION_H_

#include <string>
#include <fstream>
#include <iostream>


#include "Canvas.h"
#include "global.h"


class CanvasCollection
{
private:
 	

public:
 	CanvasCollection();
 	~CanvasCollection();

	std::vector<Canvas*> canvases;
	
	long size () { return canvases.size(); }
	Canvas* at(int index) { return canvases[index]; }
	void push_back(Canvas* c) { canvases.push_back(c); }
	void removeCanvas (int index);
	
	void print();
	void saveToFile();
	static CanvasCollection* readFromFile();
//	CanvasCollection* clone();
	 
};


#endif /* _CANVASCOLLECTION_H_ */
