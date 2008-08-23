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
    std::vector<Canvas*> canvases;
     
public:
     CanvasCollection();
     ~CanvasCollection();
    
    long size () { return canvases.size(); }
    Canvas* at(int index) { return canvases[index]; }
    void push_back(Canvas* c) { canvases.push_back(c); }
    void removeCanvas (int index);
    
    void print();
    void saveToFile(std::string filename);
    static CanvasCollection* readFromFile(std::string filename);
//    CanvasCollection* clone();
     
};


#endif /* _CANVASCOLLECTION_H_ */
