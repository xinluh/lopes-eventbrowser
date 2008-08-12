#ifndef _GRAPHINFOS_H_
#define _GRAPHINFOS_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "TH1F.h"

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
        *s << "don't know about how to describe myself..."
           << "(this really should NOT happen!);"
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
         return (xAxis.length() > 0 && yAxis.length() > 0 && (!useErrors ||
            (useErrors && !xAxis_err.empty() && !yAxis_err.empty())));
     }

    void virtual draw(Draw* d)
    {
        string x_err = (useErrors)? xAxis_err : "";
        string y_err = (useErrors)? yAxis_err : "";
        
        d->draw2DGraph(xAxis,yAxis, x_err,y_err);

        parentCanvas->setName("2DGraph: " + xAxis + " - " + yAxis);
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
    bool    useErrors      ;
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
        if      (name == "useErrors") useErrors         = atob(value);
        else if (name == "rAxis"    ) rAxis             = value;
        else if (name == "thetaAxis" ) thetaAxis         = value;
        else if (name == "rAxis_err") rAxis_err         = value;
        else if (name == "thetaAxis_err") thetaAxis_err = value;
    }

    bool virtual readyToDraw()
    {
        return (!rAxis.empty() && !thetaAxis.empty() && (!useErrors ||
             (useErrors && !thetaAxis_err.empty() && !rAxis_err.empty())));
    }

    void draw(Draw* d)
    {
        d->drawPolarGraph(rAxis,thetaAxis,
                           useErrors ? rAxis_err : "",
                           useErrors ? thetaAxis_err : "");
        parentCanvas->setName("Polar: [" + rAxis + "] vs. ["
                              + thetaAxis + "]");
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

struct infoHist1D : infoGraph
{
    bool useDefault;
    string data;
    float min, max;
    int nbins; 
  //  all information for graphing go here; see above for example

  // this function should print information in this struct to a stream;
  // this is used to save the information to a file and for debugging
    void print(ostream* s)
    {
        if (!s) s = &cout;

        *s << "useDefault"  <<  " = "  << useDefault  << endl;
        *s << "data"  <<  " = "  << data  << endl;
        *s << "min"  <<  " = "  << min  << endl;
        *s << "max"  <<  " = "  << max  << endl;
        *s << "nbins"  <<  " = "  << nbins  << endl;
    }

    void enterValue(const string& name, const string& value)
    {
        if      (name == "useDefault") useDefault       = atob(value);
        else if (name == "data"    )   data       = value;
        else if (name == "min" )       min  = atof(value);
        else if (name == "max")        max = atof(value);
        else if (name == "nbins")      nbins = atoi(value);

    }

    bool readyToDraw()
    {
        return (data.length() > 0
                && (useDefault || (!useDefault && max > min && nbins > 0)));
    }
  
    void draw(Draw* d)
    {
        TH1F* hist = d->draw1DHist(data,useDefault,min,max,nbins);
        
        parentCanvas->setName("1DHist: " + data);
        min = (float) hist->GetXaxis()->GetXmin();
        max = (float) hist->GetXaxis()->GetXmax();
        nbins = hist->GetNbinsX();
    }
};

// ## uncomment below to add another graph type ## 
//struct infoGraph_BlahBlah_ : infoGraph
//{
//  //  all information for graphing go here; see above for example
//
//  // this function should print information in this struct to a stream;
//  // this is used to save the information to a file and for debugging
//  void print(ostream* s)
//  {
//      if (!s) s = &cout;
//
//      *s << "_name-of-param_"  <<  " = "  << _param_  << endl;
//
//  }
//
//  // this should read a name-value pair of information into the data member
//  // in this struct; this is used for retrieving previous saved information
//  // in a file back to the memory
//  void enterValue(const string& name, const string& value)
//  {
//  }
//
//  // tell the rest of the program whether all the information necessary for
//  // graphing is already present thus it is ready to draw; must return
//  // something! 
//  bool readyToDraw()
//  {
//       return _true if ready; false if not_;
//  }
//
//  // this is where one will draw something. It is best to define all the
//  // details for drawing in a function in the class Draw, not here; here one
//  // should only call helper functions
//  void draw(Draw* d)
//  {
//       d->_drawSomething_();
//       parentCanvas->setName(_an appropriate name for the canvas_);
//  }
//};


#endif /* _GRAPHINFOS_H_ */
