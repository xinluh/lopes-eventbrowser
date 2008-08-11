#include "Draw.h"
#include "TGraph.h"
#include "TH1F.h"
#include "TTree.h"
#include "TGraphErrors.h"
#include "TGraphPolar.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TMarker.h"
#include "TStyle.h"
#include "TLegend.h"

#include "ReadRootTree.h"
#include "global.h"

#include <sstream>


#ifdef DEBUG
#include <iostream>

#endif

using namespace std;

Draw::Draw()
{
    colorMultiGraph = 1;
    rootTree = NULL;
}

Draw::~Draw(){}; //todo: release resources!

int Draw::getDrawColor()
{
    if (isMultiGraph()) colorMultiGraph++;
    return colorMultiGraph;
}


void Draw::setCanvas(TCanvas *tc)
{
    canvas = tc;
    canvas->cd();
}

void Draw::drawAntennaPosition()
{
    
    if (!canvas) return;

    float x_ant[30]={79.61,111.425,36.12,54.621,22.68,40.841,
        2.114,34.345,72.799,91.021,-64.335,-45.981,-84.665,-52.069,
        -91.563,-73.138,-112.217,-80.264,-34.721,-2.713,-13.861,4.335,
        -41.354,-23.045,-61.694,-29.84,-21.85,-7.826,16.846,2.626};
    float y_ant[30]={-45.96,-64.297,-84.724,-52.915,-34.593,-2.652,
        40.762,22.469,-21.039,10.966,-112.265,-80.043,-36.799,-54.61,
        -11.622,20.123,63.405,45.138,-23.298,-41.538,-98.158,-66.264,
        1.876,33.919,77.362,58.835,-152.552,-127.937,-141.969,-166.636};

    TGraph *tg = new TGraph();
    for (int j=0;j<30;j++) tg->SetPoint(j,y_ant[j],x_ant[j]);

    canvas->SetBorderSize(0);
    canvas->SetGridx();
    canvas->SetGridy();
    canvas->SetFrameFillColor(0);

    tg->SetMarkerStyle(22);
    tg->SetMarkerColor(getDrawColor());
    tg->SetTitle("Antenna positions in geographic coordinates");

    tg->GetXaxis()->SetTitle("W-E (m)");
    tg->GetYaxis()->SetTitle("S-N (m)");

    tg->Draw(isMultiGraph()? "P" : "AP");
    canvas->Update();

}

void Draw::drawGrandeCoordinates()
{
    float x_G[37]={-0.14,-131.26,-257.02,-384.85,-499.64, 64.48,
                   -64.99,-211.23,-328.97,-426.06,-569.81, 24.21,
                   -140.10,-260.88,-377.53,-481.52,  44.09, -95.83,
                   -195.43,-319.85,-481.54,-608.26,  24.79,-112.86,
                   -249.76,-386.09,-533.71, 101.22, -24.72,-196.54,
                   -317.87,-443.33,-565.96,-111.90,-275.03,-389.06, -517.91};
    float y_G[37]={65.33, 70.87, 101.73, 96.12, 95.51, -42.03,-41.42,
                   -40.54, -49.29,  -7.66,  46.42,-156.62, -143.78,
                   -136.19,-144.97,-155.46,-276.64,-276.04, -272.58,
                   -267.57,-234.93,-281.77,-391.27,-383.64, -392.04,
                   -382.12,-409.11,-507.57,-507.58,-504.10, -529.16,
                   -525.89,-526.39,-654.86,-645.43,-653.28, -620.77};

    TGraph *tg = new TGraph();
    for (int j=0;j<30;j++) tg->SetPoint(j,x_G[j],y_G[j]);

    canvas->SetBorderSize(0);
    canvas->SetGridx();
    canvas->SetGridy();
    canvas->SetFrameFillColor(0);

    tg->SetMarkerStyle(22);
    tg->SetMarkerColor(getDrawColor());
    tg->SetTitle("Grande coordinates");

    tg->GetXaxis()->SetTitle("W-E (m)");
    tg->GetYaxis()->SetTitle("S-N (m)");

    tg->Draw(isMultiGraph()? "P" : "AP");
    canvas->Update();

}


//callback function for ReadRootTree class
int getValue_2DTGraphErrors(void* obj,int& index,vector<float>& values, long&)
{
    TGraphErrors * g = (TGraphErrors  * ) obj;

    g->SetPoint(index,values[0],values[1]);
    g->SetPointError(index,values[2],values[3]);
    return 0;
}

void Draw::draw2DGraph(const string& x,const string& y,
                       const string& x_err, const string& y_err)
{
//    if (!x || !y || !rootTree) return;
    if (!canvas) return;

    TGraphErrors* g = new TGraphErrors();

    vector<string> arg; 
    arg.push_back(x);
    arg.push_back(y);
    arg.push_back(x_err);
    arg.push_back(y_err);

    rootTree->fillValues(&getValue_2DTGraphErrors, g, arg);
    
    canvas->SetBorderSize(0);
    canvas->SetFrameFillColor(0);

    g->SetFillColor(1);

    ostringstream s;
    s << x << " vs. " << y ;
        
    g->SetTitle(s.str().c_str());
    g->GetXaxis()->SetTitle(x.c_str());
    g->GetYaxis()->SetTitle(y.c_str());
    g->SetMarkerColor(getDrawColor());
    g->SetMarkerStyle(20);
    g->SetMarkerSize(1);

    g->Draw(isMultiGraph()? "P" : "AP");
    canvas->Update();
}

int getValue_PolarGraphErrors(void* obj,int& index,vector<float>& values, long&)
{
    TGraphPolar* g = (TGraphPolar*) obj;

    // SetPoint(index,theta-value,r-value)
    g->SetPoint(index,values[1],values[0]);
    g->SetPointError(index,values[3],values[2]);
    return 0;
}

void Draw::drawPolarGraph(const string& r, const string& theta,
                          const string& r_err,const string& theta_err)
{
    if (!canvas) return;
    
    TGraphPolar* g = new TGraphPolar();

    vector<string> arg;
    arg.push_back(r);
    arg.push_back(theta);
    arg.push_back(r_err);
    arg.push_back(theta_err);
    
    rootTree->fillValues(&getValue_PolarGraphErrors, g, arg);
    
    canvas->SetBorderSize(0);
    canvas->SetFrameFillColor(0);

    ostringstream s;
    s << r << " vs. " << theta ;
    g->SetTitle(s.str().c_str());
    
    g->Draw((string(isMultiGraph()? "P" : "AOP")
            // and if r_err not empty, paint errors as well (using option "E")
            + string((r_err != "") ? "E" : "")).c_str()); 

    g->SetFillColor(10);
    g->SetMarkerColor(getDrawColor());
    g->SetMarkerStyle(21);
    g->SetMarkerSize(0.8);
    g->SetMinRadial(0);
    
    canvas->Update();
}

int getValue_ShowerAngles(void* obj,int& index,vector<float>& values, long&)
{
    TGraphPolar * g = (TGraphPolar*) obj;
    g->SetPoint(index,values[1],values[0]);
    return 0;
}

int getValue_ShowerAngles2(void* obj,int& index,vector<float>& values,
                            long& total_n)
{
    float theta = values[1],
          r = values[0]/50,  //need to scale the r value; 50 is the max on
                             //r-scale
          colorcode_by = values[2]; 

    TMarker* m = new TMarker(r*cos(theta),r*sin(theta),kFullSquare);
    TMarker* m2= new TMarker(0,0,kFullSquare); // for legend
    TLegend* lg = (TLegend*)obj;
    int color = (int) ((float)50 / (float)total_n * (float)index) +51 ;
 
    m->SetMarkerColor(color);
    m->SetMarkerSize(1);
    m->Draw();

    m2->SetMarkerSize(1);
    m2->SetMarkerColor(color);

    if (index == 0 || index == total_n - 1)
     {
        char label[20];
         sprintf(label,"%G",colorcode_by);
         lg->AddEntry(m2,label,"P");
     }
     else
        lg->AddEntry(m2," ","P");
    
    return 0;
}

void Draw::drawShowerAngles(const string& r, const string& theta,
                            const string& colorcode_by)
{
    if (!canvas) return;

    // set the so called pretty palette with rainbow colors
    gStyle->SetPalette(1);
    
    TGraphPolar* g = new TGraphPolar();
    vector<string> arg;
    arg.push_back(r);
    arg.push_back(theta);
    arg.push_back(colorcode_by);
    
    TLegend * lg = new TLegend(.92,0.15,.999,0.80,colorcode_by.c_str());
    vector<TMarker> lgBox(50); // for the legend spectrum

    // re-apply the eventcut and sort the event by colorcode_by
    rootTree->setEventCut(NULL,colorcode_by.c_str());

    rootTree->fillValues(&getValue_ShowerAngles, g, arg);

     canvas->SetBorderSize(0);
     canvas->SetFrameFillColor(0);
    canvas->SetFillColor(10);
    
    g->Draw("AOP");

    canvas->Update();

    // set the axis division; has to be done after Draw() and Update()
    g->GetPolargram()->SetNdivRadial(105);
    g->GetPolargram()->SetNdivPolar(104);
    g->GetPolargram()->SetToDegree();

    g->SetMinRadial(0);
    g->SetMaxRadial(50);
    g->GetPolargram()->SetRadialLabelSize(0.05);

    g->GetPolargram()->SetPolarLabel(0,"E");
    g->GetPolargram()->SetPolarLabel(1,"N");
    g->GetPolargram()->SetPolarLabel(2,"W");
    g->GetPolargram()->SetPolarLabel(3,"S");

    lg->SetEntrySeparation(-.01);
    lg->SetFillColor(10);
    lg->SetTextSize(0.030);
    lg->SetTextAlign(12);
    lg->SetTextAngle(70);
    lg->SetBorderSize(0);
    
    //draw the colored markers and the legend
    rootTree->fillValues(&getValue_ShowerAngles2,  lg, arg);

    lg->Draw();
    canvas->Update();
}


int getValue_1DHist(void* obj,int& index,vector<float>& values, long&)
{

    return 0;
}

void Draw::draw1DHist(const string& content, bool useDefault,
                      float min, float max, int nbins)
{
    TH1F* hist = NULL;

    string option = content + ">>hist";
    
    if (!useDefault)
    {
        char buf[1024];
        sprintf(buf,"(%i,%f,%f)",nbins, min, max);
        option += string(buf);
    }

    rootTree->getTTree()->Draw(option.c_str());

    hist = (TH1F*)gPad->GetPrimitive("hist"); 

    if (hist)
        hist->GetXaxis()->SetTitle(content.c_str());
    canvas->Update();

}

void Draw::setSourceRootTree(vector<string> root_files, const char * treeName)
{
    rootTree = new ReadRootTree(root_files,treeName,"branches.cfg");
}

void Draw::saveAs(TCanvas *tc, const char * filename,
                  saveAsOptions options)
{
    TCanvas * c = (tc)? tc : canvas;

    if (!c) return;

    string *s = new string("");
    if (filename)
    {
        s = new string(filename);
        *s += (options == OPEN_ONLY)? "[" : "";
        *s += (options == CLOSE_ONLY)? "]" : "";
    }
    
#ifdef DEBUG
    cout << "Supposely this should save to file: " << s->c_str()  << endl;
#endif

    c->Print(s->c_str()); // print to file

    delete s; //clean up
}

void Draw::divideCanvas(int n_columns, int n_rows)
{
    canvas->Divide(n_columns,n_rows);
    canvas->cd(1);
}

void Draw::clearCanvas()
{
    if (!canvas) return;
    canvas->Clear();
    canvas->Update();
}

void Draw::setMultiGraph(bool isMultiGraph)
{
    colorMultiGraph = 1;
    multiGraph = isMultiGraph;
}	
