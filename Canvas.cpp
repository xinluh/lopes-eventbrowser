#include "Canvas.h"

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

Canvas::Canvas()
{
	graphInfo = 0;
}
Canvas::~Canvas() {};

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
		// ## to add new graph type: case ... see above for example

	}

	type = graphType;
}
	
