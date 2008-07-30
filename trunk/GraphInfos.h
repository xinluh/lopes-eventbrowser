#ifndef _GRAPHINFOS_H_
#define _GRAPHINFOS_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
//#include "global.h"

using namespace std;


struct infoGraph
{
	virtual ~infoGraph() {};
	
	void virtual print(std::ostream* s = NULL)
	{
		if (!s)
			s = &cout;
		*s << "don't know about how to describe myself...; "
		   << "overwrite my print() method please ;)" << endl;
	}
};

struct infoGraph2D : infoGraph
{
	bool         useErrors    ;
	std::string  xAxis        ;
	std::string  xAxis_err    ;
	std::string  yAxis        ;
	std::string  yAxis_err    ;

	void print(std::ostream* s)
	{
		if (!s)
			s = &cout;

		*s << "useErrors"  <<  " = "  << useErrors << endl;
		*s << "xAxis    "  <<  " = "  << xAxis     << endl;
		*s << "xAxis_err"  <<  " = "  << xAxis_err << endl;
		*s << "yAxis    "  <<  " = "  << yAxis     << endl;
		*s << "yAxis_err"  <<  " = "  << yAxis_err << endl;
	}
};

struct infoShowerAngle : infoGraph
{
	std::string rAxis          ;
	std::string thetaAxis      ;
	std::string colorCodeBy    ;

	void print(std::ostream* s)
	{
		if (!s)
			s = &cout;

		*s << "rAxis      "  <<  " = "  << rAxis       << endl;
		*s << "thetaAxis  "  <<  " = "  << thetaAxis   << endl;
		*s << "colorCodeBy"  <<  " = "  << colorCodeBy << endl;
				
	}
};

struct infoGraphPolar : infoGraph
{
	bool         useErrors      ;
	std::string  rAxis          ;
	std::string  rAxis_err      ;
	std::string  thetaAxis      ;
	std::string  thetaAxis_err  ;

	void print(std::ostream* s)
	{
		if (!s)
			s = &cout;

		*s << "useErrors    "  <<  " = "  << useErrors     << endl;
		*s << "rAxis        "  <<  " = "  << rAxis         << endl;
		*s << "rAxis_err    "  <<  " = "  << rAxis_err     << endl;
		*s << "thetaAxis    "  <<  " = "  << thetaAxis     << endl;
		*s << "thetaAxis_err"  <<  " = "  << thetaAxis_err << endl;
				
	}
};

// ## uncomment below to add another graph type ## 
//struct infoGraphBlahBlah : infoGraph
//{
//	all information for graphing go here; see above for example
//  void print(std::ostream* s)
//	{
//		if (!s)
//			s = &cout;
//
//		*s << ""  <<  " = "  <<  << endl;
//				
//  }
//}


#endif /* _GRAPHINFOS_H_ */
