#ifndef _DRAW_H_
#define _DRAW_H_
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphPolar.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TMarker.h"
#include "TStyle.h"
#include "TLegend.h"

#include "ReadRootTree.h"

#include <string>
#include <sstream>
//#include <qobject.h> //not essential for class; just to add slots for 
                     //design convenience

class Draw //: public QObject
{
//	Q_OBJECT // see comment after #include <qobject.h>

public:
	Draw();
	~Draw();

	enum multiGraphStatus {MULTI_START,MULTI_CONT,MULTI_NORMAL};

	ReadRootTree *  rootTree;
	bool isMultiGraph() {return multiGraph;	}
	
	enum saveAsOptions { DEFAULT, OPEN_ONLY, CLOSE_ONLY };

	void setCanvas(TCanvas * tc);
	void setCanvas(TCanvas * tc, int subpadnumber);
	void setMultiGraph(bool isMultiGraph) { colorMultiGraph = 1;
	                                        multiGraph = isMultiGraph;}
	void setSourceRootTree(std::vector<std::string> root_files,
						   const char * treeName);
	void divideCanvas(int n_columns, int n_rows);
	void clearCanvas();
	
	void drawAntennaPosition();
	void drawGrandeCoordinates();
	void draw2DGraph(const char * x,const char* y,
			const char * x_err, const char* y_err);
    void drawPolarGraph(const char * r, const char* theta, const char * r_err,
						const char * theta_err);
	void drawShowerAngles(const char * r, const char* theta,
								const char * colorcode_by);

	void saveAs(TCanvas *tc, const char * filename,
				saveAsOptions options = DEFAULT);

	
 private:
	TCanvas *canvas; //the curent canva to draw on
	int padn; //the subpad number
	multiGraphStatus multiStatus;
	int colorMultiGraph; // keeping track of the colors used by previous graph
	bool multiGraph;
	int getDrawColor(); //detect whether is multiGraph and auto increment the
						//color as needed
	
	

};


#endif //_DRAW_H_
