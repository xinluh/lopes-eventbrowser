#ifndef _READROOTTREE_H_
#define _READROOTTREE_H_
#include "TFile.h"
#include "TTree.h"
#include "TEventList.h"
#include "TChain.h"
#include "TMath.h"

#include "muParser.h"
#include "Helper.h"

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
	std::vector<mu::Parser> parsers;
	std::string message;
	long entries;
	std::string * eventCut;
	enum callback_type {CALLBACK_FLOAT,CALLBACK_STR};

    //keep the indices of the events; the TEventList seems to be always sorted,
	//which is an undesired behavior
	std::vector<long> eventlist;
	
	void getBranches(const char * filename);
	void initParsers(int n);
	
	// this is the function that do all the hard work; both fillValues and
	// fillValues_str call this function
	int fillValues_all(void* callback_func,callback_type type,
					   void* obj,std::vector<std::string> expressions);
	
	// keepting track of the root tree branches;
	// these are filled by getBranches();
	std::vector<void*> branch_address;
	std::vector<std::string> branches;
	std::vector<char> branch_types;
	std::vector<float> * values; //keeping the address to the memory
	 
 public:
	ReadRootTree(std::vector<std::string> root_files, const char * tree_name,
				 const char* branchNamees_file);
	~ReadRootTree(); //todo: destroy used memory...

	// apply eventcut; if filter is null, then the previous cut is re-applied
	void setEventCut(const char * filter = NULL,const char * sort_by = NULL,
					 bool sort_desc = false);
	
	// for each event in the root tree, this function will call the callback
	// function as given in parameter; obj will be pass unmodified to the
	// callback function;
	int fillValues(int (*callback)(void* obj,int index,
								   std::vector<float> values,
								   long total_n),
				   void* obj, std::vector<std::string> expressions);
	
	// same as fillValues except it gives strings as output for display
	// purposes also can handle int (hopefully!) unlike fillValues, which
	// handels only float
	int fillValues_str(int (*callback_str) (void* obj,int index,
					                        std::vector<std::string> values,
											long total_n),
					   void* obj, std::vector<std::string> expressions);
	
	int getNumberEntries() {return entries;}
	std::string getLastMessage() {return message; }
	std::vector<std::string> getBranchNames() {return branches;}
	const std::string getEventCut() {return *eventCut;}
};

#endif //define _READROOTFILE_H_
