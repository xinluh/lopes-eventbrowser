#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "global.h"
#include "Draw.h"


#ifdef DEBUG
using namespace std;
#endif

struct infoGraph;

class Canvas
{
public:
    Canvas();
    ~Canvas();

    enum graphTypes
    {
        GRAPH_2D = 0,
        SHOWER_ANGLE,
        ANTENNA_POSITION,
        GRAPH_POLAR,

        // ## add another graph type here

        // used to find out how many graph types there are
        LAST_ITEM // must be last!
    };


    static int numberOfGraphTypes() {return LAST_ITEM;}
    static std::string getDescription(graphTypes type)
        { return std::string(graphTypeDescriptions[type]); }
    
    graphTypes getGraphType() {return type;}
    std::string getEventCut() {return eventCut;}
    std::string getName() {return name;}
    infoGraph* getGraphInfo() { return graphInfo; }

    void setName (std::string _name) {name = _name;}
    void setEventCut (std::string cut) {eventCut = cut;}
    void setGraphType(graphTypes graphType);

    void streamToFile(std::ofstream & s);
    bool parseFromFile(std::ifstream & s);
    void print();
    bool readyToDraw();
    void draw(Draw* d);
    
 private:
    static char * graphTypeDescriptions[];

    graphTypes type;
    infoGraph* graphInfo;
    std::string name;
    std::string eventCut;
//  std::vector<Canvas*> childPads;
};



#endif //_CANVAS_H_

