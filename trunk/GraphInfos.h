#ifndef _GRAPHINFOS_H_
#define _GRAPHINFOS_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "global.h"
#include "Helper.h"
#include "Draw.h"
#include "Canvas.h"



using namespace std;


struct infoGraph
{
	Canvas* parentCanvas;
		
	virtual ~infoGraph() {};
	
	void virtual print(ostream* s = NULL)
	{
		if (!s)
			s = &cout;
		*s << "don't know about how to describe myself...; "
		   << "overwrite my print() method please ;)" << endl;
	}

	void virtual enterValue(const string&, const string&) {};
	void virtual draw(Draw*) {};
	bool virtual readyToDraw() { return false; }
	
};

struct infoGraph2D : infoGraph
{
	bool    useErrors    ;
	string  xAxis        ;
	string  xAxis_err    ;
	string  yAxis        ;
	string  yAxis_err    ;

	void print(ostream* s = NULL)
	{
		if (!s)
			s = &cout;

		*s << "useErrors"  <<  " = "  << useErrors << endl;
		*s << "xAxis    "  <<  " = "  << xAxis     << endl;
		*s << "xAxis_err"  <<  " = "  << xAxis_err << endl;
		*s << "yAxis    "  <<  " = "  << yAxis     << endl;
		*s << "yAxis_err"  <<  " = "  << yAxis_err << endl;
	}


	void enterValue(const string& name, const string& value)
	{
		if      (name == "useErrors") useErrors = atob(value);
		else if (name == "xAxis"    ) xAxis = value;
		else if (name == "yAxis"    ) yAxis = value;
		else if (name == "xAxis_err") xAxis_err = value;
		else if (name == "yAxis_err") yAxis_err = value;
	}

 	bool virtual readyToDraw()
 	{
		print();
		
 		return (xAxis.length() > 0 && yAxis.length() > 0 && (!useErrors ||
			(useErrors && !xAxis_err.empty() && !yAxis_err.empty())));
 	}

	void virtual draw(Draw* d)
	{
		string x_err = (useErrors)? xAxis_err : "";
		string y_err = (useErrors)? yAxis_err : "";
		
		d->draw2DGraph(xAxis,yAxis, x_err,y_err);

		parentCanvas->setName(xAxis + " - " + yAxis);
	}

};

struct infoShowerAngle : infoGraph
{
	string rAxis          ;
	string thetaAxis      ;
	string colorCodeBy    ;

	void print(ostream* s)
	{
		if (!s)
			s = &cout;

		*s << "rAxis      "  <<  " = "  << rAxis       << endl;
		*s << "thetaAxis  "  <<  " = "  << thetaAxis   << endl;
		*s << "colorCodeBy"  <<  " = "  << colorCodeBy << endl;
	}

	void enterValue(const string& name, const string& value)
	{
		if      (name == "rAxis")       rAxis = value;
		else if (name == "thetaAxis" )  thetaAxis = value;
		else if (name == "colorCodeBy") colorCodeBy = value;
	}

	bool virtual readyToDraw()
	{
		return (!rAxis.empty() && !thetaAxis.empty() && !colorCodeBy.empty());
	}

	void virtual draw(Draw* d)
	{
		d->drawShowerAngles(rAxis,thetaAxis,colorCodeBy);		
        parentCanvas->setName("Shower Angles");
	}			
};

struct infoGraphPolar : infoGraph
{
	bool         useErrors      ;
	string  rAxis          ;
	string  rAxis_err      ;
	string  thetaAxis      ;
	string  thetaAxis_err  ;

	void print(ostream* s)
	{
		if (!s)
			s = &cout;

		*s << "useErrors    "  <<  " = "  << useErrors     << endl;
		*s << "rAxis        "  <<  " = "  << rAxis         << endl;
		*s << "rAxis_err    "  <<  " = "  << rAxis_err     << endl;
		*s << "thetaAxis    "  <<  " = "  << thetaAxis     << endl;
		*s << "thetaAxis_err"  <<  " = "  << thetaAxis_err << endl;
				
	}

	void enterValue(const string& name, const string& value)
	{
		if      (name == "useErrors") useErrors 		= atob(value);
		else if (name == "rAxis"    ) rAxis 			= value;
		else if (name == "thetaAxis" ) thetaAxis 		= value;
		else if (name == "rAxis_err") rAxis_err 		= value;
		else if (name == "thetaAxis_err") thetaAxis_err = value;
	}

	bool virtual readyToDraw()
	{
		return (!rAxis.empty() && !thetaAxis.empty() && (!useErrors ||
			 (useErrors && !thetaAxis_err.empty() && !rAxis_err.empty())));
	}
};

struct infoGraphPosition : infoGraph
{
    enum positionTypes {GRANDE_COORD = 0,ANTENNA_POS};

    positionTypes positionType;
    
    void print(ostream* s)
    {
        if (!s)
            s = &cout;

        *s << "positionType  "  <<  " = "  << positionType  << endl;
    }

    void enterValue(const string& name, const string& value)
    {
        if   (name == "positionType")
            positionType = (positionTypes) atoi(value.c_str());
    }
    
    bool virtual readyToDraw() { return true; }

    void virtual draw(Draw* d)
    {
        if (positionType == GRANDE_COORD)
        {
            d->drawGrandeCoordinates();
            parentCanvas->setName("Grande Coordinates");
        }
        else if (positionType == ANTENNA_POS)
        {
            d->drawAntennaPosition();
            parentCanvas->setName("Antenna Position");
        }
    }
};


// ## uncomment below to add another graph type ## 
//struct infoGraphBlahBlah : infoGraph
//{
//	all information for graphing go here; see above for example
//  void print(ostream* s)
//	{
//  }
//
//  void enterValue(const string& name, const string& value)
//  {
//      if (!s)
//          s = &cout;
//
//      *s << "_name-of-param_"  <<  " = "  << _param_  << endl;
//
//  }
//  bool virtual readyToDraw()
//  {
//       return _true if ready; false if not_;
//}
//  void virtual draw(Draw* d)
//  {
//       d->_drawSomething_();
//       parentCanvas->setName(_an appropriate name for the canvas_);
//  }
//};


#endif /* _GRAPHINFOS_H_ */

