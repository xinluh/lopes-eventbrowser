#include "GraphInfos.h"
#include "Canvas.h"

#ifdef DEBUG
#include <iostream>
#endif

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
	//todo release resources
};

void Canvas::setGraphType (graphTypes graphType)
{
	// no need to change if old and new are the same
	if ((graphInfo) &&  getGraphType() == graphType) return;
	
	if (graphInfo)
	{
		// delete the old infoGraph struct
		switch (getGraphType())
		{
			case GRAPH_2D:      delete (infoGraph2D*) graphInfo;     break;
			case GRAPH_POLAR:   delete (infoGraphPolar*) graphInfo;  break;
			case SHOWER_ANGLE:  delete (infoShowerAngle*) graphInfo; break;
			// ## to add new graph type: case ... see above for example
		}

		graphInfo = 0;
	}
	
	switch (graphType)
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
		// ## to add new graph type: case ... see above for example
	}

	type = graphType;
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
