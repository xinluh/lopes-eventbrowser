#ifndef _CANVAS_H_
#define _CANVAS_H_

#include <vector>
#include <string>



class Canvas
{
 public:
	Canvas();
	~Canvas();

	enum graphTypes { GRAPH_2D,GRAPH_POLAR, ANTENNA_POSITION };
	graphTypes getGraphTypes() {return type;}
	std::string getEventCut() {return eventCut;}
	int getNumEvents() {return n_events;}

	
	
 private:
	graphTypes type;
	void * graphInfo;
	std::string eventCut;
	int n_events;
};

struct iGraph2D
{
	std::string xAxis;
	std::string xAxis_err;
	std::string yAxis;
	std::string yAxis_err;
};




#endif //_CANVAS_H_
