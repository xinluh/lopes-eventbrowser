#ifndef _DRAW_H_
#define _DRAW_H_

class TCanvas;
class ReadRootTree;
class TGraphErrors;
class TGraphPolar;
class TH1F;

#include <string>
#include <vector>

class Draw
{

public:
	Draw();
	~Draw();

//	enum multiGraphStatus {MULTI_START,MULTI_CONT,MULTI_NORMAL};
	enum saveAsOptions { DEFAULT, OPEN_ONLY, CLOSE_ONLY };
	
	ReadRootTree *  rootTree;

	// "multiGraph" interface: when isMultiGraph() is set to true, any
	// subsequent draw will be drawn in a different color on top of the
	// previous graphs and the exisint axises without erasing the previous
	// graph
	bool isMultiGraph() { return multiGraph; }
	void setMultiGraph(bool isMultiGraph);
	void setCanvas(TCanvas * tc); // set the current TCanvas to draw on
	void setCanvas(TCanvas * tc, int subpadnumber);
	void setSourceRootTree(std::vector<std::string> root_files,
						   const char * treeName);
	void divideCanvas(int n_columns, int n_rows);
	void clearCanvas();
	void saveAs(TCanvas *tc, const char * filename,
				saveAsOptions options = DEFAULT);

	// a bunch of drawing functions; add your own, if you want!
	void drawAntennaPosition();
	void drawGrandeCoordinates();
	TGraphErrors* draw2DGraph(const std::string& x, const std::string& y,
					 const std::string& x_err, const std::string& y_err);
    TGraphPolar* drawPolarGraph(const std::string& r, const std::string& theta,
                       const std::string& r_err, const std::string& theta_err);
	TGraphPolar* drawShowerAngles(const std::string& r,
                                 const std::string& theta,
								const std::string& colorcode_by);
    TH1F* draw1DHist(const std::string& content, bool useDefault = true,
                    float min = 0, float max = 0, int nbins = 0);

    
 private:
	TCanvas *canvas; //the curent canva to draw on
	int padn; //the subpad number
	int colorMultiGraph; // keeping track of the colors used by previous graph
	bool multiGraph;
	int getDrawColor(); //detect whether is multiGraph and auto increment the
						//color as needed
};


#endif //_DRAW_H_
