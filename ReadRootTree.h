#ifndef _READROOTTREE_H_
#define _REEDROOTTREE_H_
#include "TFile.h"
#include "TTree.h"
#include "TEventList.h"
#include "TChain.h"
#include "TMath.h"
#include "muParser.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

#define COMMENT_CHAR ';'

class ReadRootTree
{
 private:
	TChain * chain;
//	TFile * file;
	std::vector<mu::Parser> parsers;
	std::string message;
	long entries;
	std::string * eventCut;
	enum callback_type {CALLBACK_FLOAT,CALLBACK_STR};

    //keep the indices of the events; the TEventList seems to be always sorted
	//an undesired behavior
	std::vector<long> eventlist;
	
	void getBranches(char * filename);
	void setAddresses();
	void initParsers(int n);
	int fillValues_all(void* callback_func,callback_type type,
					   void* obj,std::vector<std::string> expressions);

	
	// keepting track of the branches;
	// these are filled by getBranches() and setAddresses(); 
	std::vector<void*> branch_address;
	std::vector<std::string> branches;
	std::vector<char> branch_types;
	std::vector<float> * values; //keeping the address to the memory
	 
 public:
	ReadRootTree(std::vector<std::string> root_files, const char * tree_name);
	~ReadRootTree(); //todo: destroy used memory...

	// apply eventcut; if filter is null, then the previous cut is re-applied
	void setEventCut(const char * filter = NULL,const char * sort_by = NULL,
					 bool sort_desc = false);
	// obj will be pass unmodified to the callback function;
	int fillValues(int (*callback)(void* obj,int index,
								   std::vector<float> values,
								   long total_n),
				   void* obj,
				   std::vector<std::string> expressions);
	// same as fillValues except gives string as output for display purposes
	// also can handle int (hopefully!) unlike fillValues
	int fillValues_str(int (*callback_str) (void* obj,int index,
					                        std::vector<std::string> values,
											long total_n),
					   void* obj,
					   std::vector<std::string> expressions);
	
	int getNumberEntries() {return entries;}
	std::string getLastMessage() {return message; }
	std::vector<std::string> getBranchNames() {return branches;}

	//function pointer for callback
//	int (*callback)(void*,int,std::vector<float>,long);
//	int (*callback_str) (void*,int,std::vector<std::string>,long);
};

//const std::string ReadRootTree::branches[NUM_BRANCHES] = {"Gt","XC","YC","Size","Nmu","Geoang","LogEguess","AzL_ew","ElL_ew","AzL_ns","ElL_ns","CurvR_EW","CurvR_NS","CCheight_EW","CCheight_NS","CCheight_error_EW","CCheight_error_NS","Mean_daxis_EW","Mean_daxis_NS"};


#endif //define _READROOTFILE_H_
