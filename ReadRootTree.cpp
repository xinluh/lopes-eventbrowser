#include "ReadRootTree.h"

#ifdef DEBUG
#include <iostream>
#endif

#undef DEBUG

//uncomment the following line if it is desirable to use integer
//for computation; currently only float can be used in expressions which are
//evaluated using mu::Parser. Be careful with defining the following symbol,
//however, as converting from float to int will result in losts in precision
//
//#define TREAT_INTEGER_AS_FLOAT

using namespace std;
using namespace mu;

const vector<string> ReadRootTree::getRootTreeNames(string rootFile)
{
	TFile f(rootFile.c_str());
	vector<string> names;

	TIter next(f.GetListOfKeys());
	TKey *key;
	while ((key = (TKey*) next()))
	{

		if (string(key->GetClassName()) == "TTree")
			names.push_back(key->GetName());
	}

	return names;
}

void ReadRootTree::getRootBranchNames (std::string rootFile,
									std::string treeName,
									std::vector<std::string>& names,
									std::vector<char>& types)
{
	TFile f(rootFile.c_str());
	TTree * t = (TTree*) f.Get(treeName.c_str());

	getBranchNames(t,names,types);
}
	

ReadRootTree::ReadRootTree(vector<string> root_files, const char * tree_name,
						   const char* branchNamees_file)
{
	if (root_files.empty())
	{
		cerr <<  "Fatal error! cannot initialize without valid rootfile(s)"
			 << endl;
		return;
	}

	if (!tree_name)
    // then find and read the first TTree found in the first root file
	{
		vector<string> treeNames =  getRootTreeNames(root_files[0]);

		if (!treeNames.empty())
			tree_name = treeNames[0].c_str();
		else
		{
			cerr << "Fatal error! there is no TTree existing in"
				"the given root file: " << root_files[0] << endl;
			return;
		}
	}	
	
	chain = new TChain(tree_name);

	// copy root_files into listOfFiles for later reference
	listOfFiles.clear();
	listOfFiles.assign(root_files.begin(),root_files.end());

	// adding the root files into the TChain
	for (int i = 0; i < (int) root_files.size(); i++)
		chain->Add(root_files[i].c_str());

	// get the initial count of events
	entries = (int)chain->GetEntries();

	// get the branch names either from file or from TTree/TChain
	if ((branchNamees_file) && fileExists(branchNamees_file))
	{
		branchNameFile = new string(branchNamees_file);
		getBranches(branchNamees_file);
	}
	else
	{
		branchNameFile = NULL;
		getBranches();
	}
	
	initBranches();

	setEventCut("");
}

ReadRootTree::~ReadRootTree()
{
	delete chain;
	delete eventCut;
	
	branch_address.clear();
}

const void ReadRootTree::getBranchNames(TTree * t,
										std::vector<std::string>& names,
										std::vector<char>& types)
{
	TIter next(t->GetListOfBranches());
	TBranch * branch;
	TLeaf * leaf;

	// read each branch; if the branch has type float (TLeafF) or int (TLeafI)
	// then process the branch into the vectors names and types
	while ((branch = (TBranch*) next()))
	{
		leaf = (TLeaf*) branch->GetListOfLeaves()->At(0);
		
		if (string(leaf->ClassName()) == "TLeafF")
		{
			names.push_back(branch->GetName());
			types.push_back('F');
		}
		else if (string(leaf->ClassName()) == "TLeafI")
		{
			names.push_back(branch->GetName());
			types.push_back('I');
		}			
	}

}

void ReadRootTree::getBranches()
{
	getBranchNames((TTree*) chain,branches,branch_types);
}

void ReadRootTree::getBranches(const char *filename)
 {
	ifstream infile (filename);
	string s;

    while (getline(infile, s, '\n'))
    {
		if (s.at(0) != CFG_COMMENT_CHAR) //don't read the comment line
		{
			//each line is formated as: T/branch_name
			//where T is the type, only support F=float and I=integer for now
			branch_types.push_back(s.at(0));
			branches.push_back (s.substr(2));
		}
    }
 }
	

void ReadRootTree::initBranches()
{
	// allot memory for the branch values;  todo using float for the largest
	// size for now. IMPORTANT: do not delete this vector<float>; "static"
	// is important!  take care with multi-threading of multiple ReadRootTree
	// objects, as each call to TTree.GetEntry will mess up the values
	// pointing by branch_address
	static vector<float> f (branches.size()); 
	for (int i = 0; i<(int) branches.size() ; i++)
		branch_address.push_back(&f[i]);

	for (int i = 0; i<(int) branches.size() ; i++)
		chain->SetBranchAddress(branches[i].c_str(),branch_address[i]);

#ifdef DEBUG //print the first entry for debugging purpose
	chain->GetEntry(0);

	cout << "First entry from root file:" << endl;
	
	for (int i = 0; i<(int) branches.size() ; i++)
	{
		cout << branches[i] << "(" << branch_types[i] << ") \t\t\t = ";
		if (branch_types[i] == 'F') // read as float
			cout << *((float*) branch_address[i]) << endl;
		else if (branch_types[i] == 'I') // read as int
			cout << *((int*) branch_address[i]) << endl;
	}
#endif
}

void ReadRootTree::initParsers(int n)
{
	Parser *p;

	// substantiate parser as needed and set variable addresses for the new
	// parsers
	while (n > (int) parsers.size())
	{
		p = new Parser();

		for (int i = 0; i<(int) branches.size() ; i++)
		{
			// Warning! only add variable of type float for expression
			// evaluation since mu::parser is designed only for float; for
			// other types garbages values might occur!
#ifndef TREAT_INTEGER_AS_FLOAT
			if (branch_types[i] == 'F')
#endif
				p->DefineVar(branches[i].c_str(),
							 (float*) branch_address[i]);
		}

		parsers.push_back(*p);

	}
}

void ReadRootTree::setEventCut(const char * filter,const char * sort_by,
					 bool sort_desc)
{
	// reset the previous eventcut
	chain->SetEventList(NULL);
	eventlist.clear();
	
	if (filter)
		eventCut = new string(filter);
	
	entries =  chain->Draw(">>eventlist",eventCut->c_str());
	
	if (entries == -1) return; // somehow Draw() fails; run away...
	TEventList *  teventlist = (TEventList*)gDirectory->Get("eventlist");
	Long64_t* tmplist = teventlist->GetList();
			
	if (sort_by) // also sort the events
	{
		teventlist->SetReapplyCut(true);
		chain->SetEventList(teventlist);
		
		// drawing with variable sort_by with no graphic
		entries = chain->Draw(sort_by,"","goff");
		if (entries == -1) return; // somehow Draw() fails; run away...

		// to hold the event indices that will be sorted using sort_by
		int * indices = new int[entries];
		
		// and then sort...
		TMath::Sort(entries,chain->GetV1(),indices,sort_desc? kTRUE : kFALSE);
		
		for (int i = 0; i < entries ; i++)
			eventlist.push_back( tmplist[indices[i]]);
		
		delete [] indices;
	}
	else // no need to sort, just add the event numbers to eventlist
	{
		for (int i = 0; i < entries ; i++)
			eventlist.push_back(tmplist[i]);
	}
	
// #ifdef DEBUG
// 	cout << "Selected Events after cut: "  << endl;
// 	for (int i = 0; i < entries ; i++)
// 		cout << eventlist[i] << " ";
// 	cout << endl;
// 	cout << entries << endl;
// #endif
	
}

int ReadRootTree::fillValues(int (*callback)(void*,int,vector<float>,
											 long total_n ),
							 void* obj,
							 vector<string> expressions)
{
	if (!callback) return 0;

	return fillValues_all((void*)callback,CALLBACK_FLOAT,obj,expressions);
}

int ReadRootTree::fillValues_str(int (*callback)(void*,int,vector<string>,
											 long total_n ),
							 void* obj,
							 vector<string> expressions)
{
	if (!callback) return 0;

	return fillValues_all((void*)callback,CALLBACK_STR,obj,expressions);
}


int ReadRootTree::fillValues_all(void* callback_func,callback_type type,
								 void* obj, 
								 vector<string> expressions)
{
	if (!callback_func) return 0;

	vector<float> values_f(expressions.size());
	vector<string> values_s(expressions.size());

	// keep track of whether the expression corresponds to an integer type;
	// positive values corresponds to index of the corresponding branch, -1
	// signify that the expression should be evaluated (instead of simple
	// substitution)
	vector<int> iexp(expressions.size());
	
	ostringstream ss;
	int ret_code;
	int (*callback)(void*,int,std::vector<float>,long) = 0;
	int (*callback_str) (void*,int,std::vector<std::string>,long) = 0;

	// cast the callback function to the correct type
	if (type == CALLBACK_STR)
		callback_str = (int (*) (void*,int,std::vector<std::string>,long))
            			callback_func;
	else
		callback = (int (*)(void*,int,std::vector<float>,long)) callback_func;

	// init parsers based on how many needed
	initParsers(expressions.size());

	// loop through the expressions and prepare the parsers 
	for (int j = 0; j < (int) expressions.size(); j++)
	{
		if (type == CALLBACK_STR)
		{
			for (int i = 0; i < (int) branches.size(); i++)
			{
				// if a expression corresponds to an integer branch type then
				// mark the expression to be substituted (not evaluated)
				if (branch_types[i] == 'I' &&  expressions[j] == branches[i])
				{
					iexp[j] = i;
					break;
				}
				else
					iexp[j] = -1;
			}
		}
		else
			iexp[j] = -1; //the expression is to be evaluated
		 		
		if (expressions[j] != "")
			parsers[j].SetExpr(expressions[j]);
	}

	// time to loop through the events and call the callback func!
	for (int i = 0;i < getNumberEntries() ; i++)
	{
		// will fill values into the addresses in branch_address
		chain->GetEntry(eventlist[i]); 
		
#ifdef TREAT_INTEGER_AS_FLOAT
		for (int k = 0; k < (int) branches.size(); k++)
		{

			if (branch_types[k] == 'I')
			{
				cout << branches[k] << " ";
				cout << *((int*) branch_address[k]) << endl;				
				*(float*) branch_address[k] =
					(float) *((int*) branch_address[k]);
				cout << *((float*) branch_address[k]) << endl;
			}
		}
#endif
		
#ifdef DEBUG	
		cout << i << " (Event #" << eventlist[i]
			 << "): -------------------------------" <<endl;
#endif
		
		for (int j =0; j <(int) expressions.size(); j++)
		{
			if (expressions[j] != "" && iexp[j] == -1) //evaluate expression
			{
				try
				{ 
					if (type == CALLBACK_STR)
					{
						ss.str("");
						ss << parsers[j].Eval();
						values_s[j] = ss.str();
					}
					else
						values_f[j] = parsers[j].Eval();
				}
				catch (mu::Parser::exception_type e)
				{
					cerr << e.GetMsg() << endl;
					message = e.GetMsg();
					return 1;
                    // todo:  don't go on when the expression can't be parsed
				}
			}
			else if (expressions[j] != "") // substitution (for integer)
			{
				ss.str("");	// clean up the stringstream
				ss << *((int*) branch_address[iexp[j]]);
				values_s[j]=ss.str();
			}
			else if (i == 0) // if it's the first, clean up the previous data
			{
				if (type == CALLBACK_STR)
					values_s[j] = "#ERROR#";
				else
					values_f[j] = 0;
			}
			// else - do nothing

#ifdef DEBUG
			   if (type == CALLBACK_STR)
				   cout << expressions[j] << " = " <<  values_s [j] << endl;
			   else
				   cout << expressions[j] << " = " <<  values_f [j] << endl;
#endif
		}

		// call the appropriate callback function
		ret_code = (type == CALLBACK_STR)?
			        callback_str(obj,i,values_s,entries):
       				callback(obj,i,values_f,entries);
			
		if  (ret_code != 0) return ret_code; // aborted by callback
	}

	return 0;
}

void ReadRootTree::saveToNewFile(string filename)
{
	TFile *file = new TFile(filename.c_str(),"recreate");
	TTree *newtree = chain->CloneTree(0);

	for (long i = 0; i < entries; ++i)
	{
	    chain->GetEntry(eventlist[i]);
		newtree->Fill();
	}

	newtree->Print();
	newtree->AutoSave();
	delete file;
}
