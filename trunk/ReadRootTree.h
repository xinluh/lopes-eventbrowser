#ifndef _READROOTTREE_H_
#define _READROOTTREE_H_
#include "TFile.h"
#include "TTree.h"
#include "TKey.h"
#include "TLeaf.h"
#include "TEventList.h"
#include "TChain.h"
#include "TMath.h"

#include "muParser.h"
#include "Helper.h"
#include "global.h"


#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>


class ReadRootTree
{
 private:
    TChain * chain;
    std::vector<mu::Parser> parsers;
    std::vector<std::string> listOfFiles;
    std::string message;
    long entries;
    std::string * eventCut;
    std::string * branchNameFile;
    enum callback_type {CALLBACK_FLOAT,CALLBACK_STR};
    // keepting track of the root tree branches;
    // these are filled by getBranches() and initBranches()
    std::vector<void*> branch_address;
    std::vector<std::string> branches;
    std::vector<char> branch_types;
    //keep the indices of the events; the TEventList seems to be always sorted,
    //which is an undesired behavior
    std::vector<long> eventlist;
    // read branch information from a file
    void getBranches(const char * filename);
    // read branch information from  the root file
    void getBranches();
    // initialize the various vectors relating to branches using the branch
    // names from branches
    void initBranches();
    void initParsers(int n);
    // this is the function that does all the hard work; both fillValues and
    // fillValues_str call this function
    int fillValues_all(void* callback_func,callback_type type,
                       void* obj,std::vector<std::string> expressions);
    // get a list of branches from the TTree
    static const void getBranchNames(TTree * t,
                                     std::vector<std::string>& names,
                                     std::vector<char>& types);
     
 public:
    // constructor. If tree_name is NULL, then the first tree available will
    // be loaded; if branchNamees_file is NULL, then all branches existing in
    // the tree will be read
    ReadRootTree(std::vector<std::string> root_files,
                 const char * tree_name = NULL,
                 const char* branchNamees_file = NULL);
    ~ReadRootTree(); //todo: destroy used memory...

    // apply eventcut; if filter is null, then the previous cut is re-applied
    void setEventCut(const char * filter = NULL,const char * sort_by = NULL,
                     bool sort_desc = false);

    //save the entries after event cut in a new file; only the branches
    //already set will be read into the new file; that is, the unsupported
    //branch types like string, etc. will NOT be saved to the new file
    void saveToNewFile(std::string filename);
    
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
    const std::string getLastMessage() {return message; }
    const std::vector<std::string> getBranchNames() {return branches;}
    const std::string getEventCut() {return *eventCut;}
    const std::string getTreeName() {return chain->GetName();}
    const std::string* getBranchFile() {return branchNameFile;}
    const std::vector<std::string> getListOfFiles () {return listOfFiles; }

    // get names of all root trees saved under a root file
    static const std::vector<std::string> getRootTreeNames
                                          (std::string rootFile);
    // get names of the available branches in a TTree
    static void getRootBranchNames (std::string rootFile,
                                    std::string treeName,
                                    std::vector<std::string>& names,
                                    std::vector<char>& types);
};

#endif //define _READROOTFILE_H_

