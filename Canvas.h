#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <vector>
#include <string>
#include "global.h"

class Canvas
{
public:
	Canvas();
	~Canvas();

	enum graphTypes
	{
		GRAPH_2D,
		GRAPH_POLAR,
		ANTENNA_POSITION,
		SHOWER_ANGLE
	};
	
	graphTypes getGraphType() {return type;}
	std::string getEventCut() {return eventCut;}
	std::string getName() {return name;}
	int getNumEvents() {return n_events;}

	void setName (std::string _name) {name = _name;}
	void setEventCut (std::string cut) {eventCut = cut;}
	void setGraphType(graphTypes graphType);
	
	
 private:
	graphTypes type;
	void * graphInfo;
	std::string name;
	std::string eventCut;
	int n_events;
	std::vector<Canvas*> childPads;
};

struct infoGraph2D
{
	std::string xAxis;
	std::string xAxis_err;
	std::string yAxis;
	std::string yAxis_err;
};

struct infoShowerAngle
{
	std::string rAxis;
	std::string thetaAxis;
	std::string colorCodeBy;
};



#endif //_CANVAS_H_
