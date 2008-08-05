#include "GraphInfos.h"
#include "Canvas.h"
#include <iostream>

using namespace std;

char * Canvas::graphTypeDescriptions[] =
    {
        "2D Graph",
        "Shower Angles",
        "Antenna Positions",
        "Polar Graph"
        // ## add the description for the new graph type in the same order as
        // in the enum graphTypes
    };

Canvas::Canvas()
{
    graphInfo = 0;
}

Canvas::~Canvas()
{
    delete graphInfo;
}

void Canvas::setGraphType (graphTypes graphType)
{
    // no need to change if old and new are the same
    if ((graphInfo) &&  getGraphType() == graphType) return;
    
    if (graphInfo)
    {
        delete graphInfo;
        graphInfo = NULL;
    }

    type = graphType;
    
    switch (type)
    {
        case GRAPH_2D:
            graphInfo = new infoGraph2D();
            break;
        case SHOWER_ANGLE:
            graphInfo = new infoShowerAngle();
            break;
        case GRAPH_POLAR:
            graphInfo = new infoGraphPolar();
            break;
        case ANTENNA_POSITION:
            graphInfo = new infoGraphPosition();
        // ## to add new graph type: case ... see above for example
        default:
            graphInfo = new infoGraph();
    }

    if (graphInfo)
    graphInfo->parentCanvas = this;
}
    
void Canvas::streamToFile(ofstream & s)
{
    // output header in format: [Canvas:_type]
    s << "[Canvas:"; s << type; s << "]\n";
    s << "Name = " << getName() << "\n";
    s << "EventCut = " << getEventCut() << endl;
    
    if (graphInfo)
        graphInfo->print(&s);
    s << endl;
}

bool Canvas::parseFromFile(ifstream & s)
{
    if (!s) return false;

    bool isSectionStarted = false;
    string line, name, value;
    int type;

    while (getline(s,line,END_OF_LINE))
    {
        // stop parsing when encountered '[', since that's the start of the
        // next canvas
        if (isSectionStarted && s.peek() == '[') return true;

        
        // skip blank and comment line
        if (line.size() < 1 || line[0] == CFG_COMMENT_CHAR) continue;
        
        if (line[0] == '[') // then parse header line
        {
            if (sscanf(line.c_str(),"[Canvas:%i]",&type) > 0)
            {
                isSectionStarted = true;
                setGraphType((graphTypes) type);
            }
            else
            {
                cerr << "malformatted header line; parse aborted" << endl;
                return false;
            }
        }
            
        if (isSectionStarted && parseNameValuePair(line,name,value))
        {
            if (name == "Name") setName(value);
            else if (name == "EventCut") setEventCut(value);
            else getGraphInfo()->enterValue(name,value);
        }

        
        if (s.eof()) return false;
    }

    return true;
}

bool Canvas::readyToDraw()
{
    bool ret;

    if (!getGraphInfo())
        ret = false;
    else
        ret = getGraphInfo()->readyToDraw();

    return ret;
}

void Canvas::draw(Draw* d)
{
    if (graphInfo) graphInfo->draw(d);
}


void Canvas::print()
{
    getGraphInfo()->print();
}
