#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <vector>
#include <string>
#include "global.h"


#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

struct infoGraph
{
	virtual ~infoGraph() {};
	
	void virtual print()
	{
		cout << "dunno about who I am..." << endl;
	};
};


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
		// ## add another graph type here
	};
	
	graphTypes getGraphType() {return type;}
	std::string getEventCut() {return eventCut;}
	std::string getName() {return name;}
//	int getNumEvents() {return n_events;}
	infoGraph* getGraphInfo() { return graphInfo; }

	void setName (std::string _name) {name = _name;}
	void setEventCut (std::string cut) {eventCut = cut;}
	void setGraphType(graphTypes graphType);
	
	
 private:
	graphTypes type;
	infoGraph* graphInfo;
	std::string name;
	std::string eventCut;
//	int n_events;
	std::vector<Canvas*> childPads;
};


struct infoGraph2D : infoGraph
{
	bool useErrors;
	std::string xAxis;
	std::string xAxis_err;
	std::string yAxis;
	std::string yAxis_err;

	void print()
	{
		cout << "useErrors = " << useErrors << endl;
		cout << "xAxis = " << xAxis << endl;
	}
};

struct infoShowerAngle : infoGraph
{
	std::string rAxis;
	std::string thetaAxis;
	std::string colorCodeBy;
};

struct infoGraphPolar : infoGraph
{
	bool useErrors;
	std::string rAxis;
	std::string rAxis_err;
	std::string thetaAxis;
	std::string thetaAxis_err;
};

// ## uncomment below to add another graph type ## 
//struct infoGraphBlahBlah : infoGraph
//{
//	all information for graphing go here; see above for example
//}


#endif //_CANVAS_H_
