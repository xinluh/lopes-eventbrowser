#include "Canvas.h"


Canvas::Canvas() {};
Canvas::~Canvas() {};

void Canvas::setGraphType (graphTypes graphType)
{
	if (graphInfo)
	{
		// todo cast void before deleting; otherwise won't work!
		delete graphInfo;
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
	}			
}
	
