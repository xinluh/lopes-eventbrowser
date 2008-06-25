#include "Draw.h"

#ifdef DEBUG
#include <iostream>

#endif

using namespace std;

Draw::Draw(){};
Draw::~Draw(){};

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

	tg->SetFillColor(1);
	tg->SetMarkerStyle(22);
	tg->SetMarkerColor(4);
	tg->SetTitle("Antenna positions in geographic coordinates");

	tg->GetXaxis()->SetTitle("W-E (m)");
	tg->GetYaxis()->SetTitle("S-N (m)");

	tg->Draw("AP");
	canvas->Update();

}

//callback function for ReadRootTree class
int getValue_2DTGraphErrors(void* obj,int index,vector<float> values,
							long total_n)
{
	total_n++; 					// make the compiler shut up about unused param
	TGraphErrors * g = (TGraphErrors  * ) obj;
	cout << index << " " << values[0] << " " << values[1] << endl;

	g->SetPoint(index,values[0],values[1]);
	g->SetPointError(index,values[2],values[3]);
	return 0;
}

void Draw::draw2DGraph(const char * x,const char* y,
			const char * x_err, const char* y_err)
{
//	if (!x || !y || !rootTree) return;
	if (!canvas) return;

	TGraphErrors* g = new TGraphErrors();

	vector<string> arg; 
	arg.push_back(x);
	arg.push_back(y);
	arg.push_back((x_err) ? x_err : "");
	arg.push_back((y_err) ? y_err : "");

	rootTree->fillValues(&getValue_2DTGraphErrors, g, arg);
	
	canvas->SetBorderSize(0);
	canvas->SetFrameFillColor(0);

	g->SetFillColor(1);

	ostringstream s;
	s << x << " vs. " << y ;
		
	g->SetTitle(s.str().c_str());
	g->GetXaxis()->SetTitle(x);
	g->GetYaxis()->SetTitle(y);
	g->SetMarkerColor(2);
	g->SetMarkerStyle(20);
	g->SetMarkerSize(1);

	
		
	g->Draw("AP");
	canvas->Update();
}

int getValue_PolarGraphErrors(void* obj,int index,vector<float> values,
							long total_n)
{
	total_n++; // make compiler shut up about unused param
	TGraphPolar * g = (TGraphPolar  * ) obj;

//	cout << index << " r = " << values[0] << "; theta = " << values[1] << endl;
	cout << "g->SetPoint(" << index << "," << values[0] << "," << values[1]
		 << ");" << endl;

	// SetPoint(index,theta-value,r-value)
	g->SetPoint(index,values[1],values[0]);
	g->SetPointError(index,values[3],values[2]);
	return 0;
}

void Draw::drawPolarGraph(const char * r, const char* theta,
						  const char * r_err,const char * theta_err)
{
	if (!canvas) return;
	
	TGraphPolar* g = new TGraphPolar();

	vector<string> arg;
	arg.push_back(r);
	arg.push_back(theta);
	arg.push_back((r_err) ? r_err : "");
	arg.push_back((theta_err) ? theta_err : "");
	
	rootTree->fillValues(&getValue_PolarGraphErrors, g, arg);
	
	//g.SetLogy();
	canvas->SetBorderSize(0);
	canvas->SetFrameFillColor(0);

	g->SetFillColor(10);
	
	ostringstream s;
	s << r << " vs. " << theta ;
		
//	g->SetTitle(s.str().c_str());
//	g->GetXaxis()->SetTitle(r);
//	g->GetYaxis()->SetTitle(theta);

	if (multiStatus == MULTI_START)
	{
		g->Draw("AOP");
		multiStatus = MULTI_CONT;
	}
	else if (multiStatus == MULTI_CONT)
		g->Draw("P");
	else if (multiStatus == MULTI_NORMAL)
		g->Draw("AOP");

	
	canvas->Update();

	// set the axis division; has to be done after Draw() and Update()
	g->GetPolargram()->SetNdivRadial(105);
	g->GetPolargram()->SetNdivPolar(104);
	g->GetPolargram()->SetToDegree();

	if (multiStatus == MULTI_START)
	{
		g->SetMarkerColor(1);
		colorMultiGraph = 1;
	}
	else if (multiStatus == MULTI_CONT)
	{
		colorMultiGraph = (colorMultiGraph == 9)? 1: colorMultiGraph +1;
		g->SetMarkerColor(colorMultiGraph);
	}
	else if (multiStatus == MULTI_NORMAL)
		g->SetMarkerColor(4);
	
	g->SetMarkerStyle(21);
	g->SetMarkerSize(0.8);

	g->SetMinRadial(0);
	g->GetPolargram()->SetRadialLabelSize(0.05);

	g->GetPolargram()->SetPolarLabel(0,"E");
	g->GetPolargram()->SetPolarLabel(1,"N");
	g->GetPolargram()->SetPolarLabel(2,"W");
	g->GetPolargram()->SetPolarLabel(3,"S");
	
	canvas->Update();
}

int getValue_ShowerAngles(void* obj,int index,vector<float> values,
							long total_n)
{
	total_n++; // make compiler shut up about unused param!
	TGraphPolar * g = (TGraphPolar*) obj;
	g->SetPoint(index,values[1],values[0]);
	return 0;
}

int getValue_ShowerAngles2(void* obj,int index,vector<float> values,
							long total_n)
{
	float theta = values[1],
		  r = values[0]/50,  //need to scale the r value
		  colorcode_by = values[2]; 
 	TMarker* m = new TMarker(r*cos(theta),r*sin(theta),kFullSquare);
	TMarker* m2= new TMarker(0,0,kFullSquare); // for legend
	TLegend* lg = (TLegend*)obj;
	int color = (int) ((float)50 / (float)total_n * (float)index) +51 ;
 
	cout << "color " << color << endl;
	
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

void Draw::drawShowerAngles(const char * r, const char* theta,
						  const char * colorcode_by)
{
	if (!canvas) return;

	// set the so called pretty palette with rainbow colors
	gStyle->SetPalette(1);
	
	TGraphPolar* g = new TGraphPolar();
	vector<string> arg;
	arg.push_back(r);
	arg.push_back(theta);
	arg.push_back(colorcode_by);
	
	TLegend * lg = new TLegend(.92,0.15,.999,0.80,colorcode_by);
	vector<TMarker> lgBox(50); // for the legend spectrum

	// re-apply the eventcut and sort the event by colorcode_by
	rootTree->setEventCut(NULL,colorcode_by);

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

void Draw::setSourceRootTree(vector<string> root_files, const char * treeName)
{
	rootTree = new ReadRootTree(root_files,treeName);
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

void Draw::beginMultigraph()
{
	multiStatus = MULTI_START;
}

void Draw::endMultigraph()
{
	multiStatus = MULTI_NORMAL;
}
