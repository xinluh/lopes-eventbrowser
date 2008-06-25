#include "ReadRootTree.h"

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

//#undef DEBUG

//uncomment the following line if it is desirable to use integer
//for computation; currently only float can be used in expressions which are
//evaluated using mu::Parser. Be careful with defining the following symbol,
//however, as converting from float to int will result in losts in precision
//
//#define TREAT_INTEGER_AS_FLOAT

using namespace std;
using namespace mu;

ReadRootTree::ReadRootTree(vector<string> root_files, const char * tree_name)
{
	chain = new TChain(tree_name);

	for (int i = 0; i < (int) root_files.size(); i++)
		chain->Add(root_files[i].c_str());

	entries = (int)chain->GetEntries();

	getBranches("branches.txt");

	setEventCut("");
}

void ReadRootTree::getBranches(char *filename)
{
	ifstream infile (filename);
	string s;

    while (getline(infile, s, '\n'))
    {
		if (s.at(0) != COMMENT_CHAR) //don't read the comment line
		{
			//each line is like: T/branch_name
			//where T is the type, only F=float and I=integer for now
			
			branch_types.push_back(s.at(0));
			branches.push_back (s.substr(2));
		}
    }

	//allot memory for the branch values;
	//todo using float for the largest size for now
	// important: do not delete this vector<float>; "static" is important!
	// take care with multi-threading of multiple ReadRootTree objects!
	static vector<float> f (branches.size()); 
	for (int i = 0; i<(int) branches.size() ; i++)
		branch_address.push_back(&f[i]);


	setAddresses();
}

void ReadRootTree::initParsers(int n)
{
	Parser *p;
	while (n > (int) parsers.size())
	{
		p = new Parser();
		parsers.push_back(*p);
	}

	cout << parsers.size() << endl;
	for (int j = 0; j < n; j++)
	{

		for (int i = 0; i<(int) branches.size() ; i++)
		{
			// Warning! only add variable of type float since the rest of the
			// code is designed only for float; for other types garbages
			// values might occur!
#ifndef TREAT_INTEGER_AS_FLOAT
			if (branch_types[i] == 'F')
#endif
				parsers[j].DefineVar(branches[i].c_str(),
							 (float*) branch_address[i]);
		}
	}
}

void ReadRootTree::setAddresses()
{
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

void ReadRootTree::setEventCut(const char * filter,const char * sort_by,
					 bool sort_desc)
{
	chain->SetEventList(NULL);
	eventlist.clear();
	if (filter)
		eventCut = new string(filter);
	
	entries =  chain->Draw(">>eventlist",eventCut->c_str());
	
	if (entries == -1) return; 
	TEventList *  teventlist = (TEventList*)gDirectory->Get("eventlist");
	Long64_t* tmplist = teventlist->GetList();

			
	if (sort_by) // also sort the events
	{
		cout << "Sorting by: " << sort_by << endl;

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
	else
	{
		for (int i = 0; i < entries ; i++)
			eventlist.push_back(tmplist[i]);
	}
	
#ifdef DEBUG
	for (int i = 0; i < entries ; i++)
		cout << eventlist[i] << " ";
	cout << endl;
	cout << entries << endl;
#endif
	
}

int ReadRootTree::fillValues(int (*callback)(void*,int,vector<float>,
											 long total_n ),
							 void* obj,
							 vector<string> expressions)
{
	if (!callback) return 0;
		
	vector<float> values(expressions.size());

	initParsers(expressions.size());

	for (int j = 0; j < (int) expressions.size(); j++)
	{
		if (expressions[j] != "")
			parsers[j].SetExpr(expressions[j]);
	}

	for (int i = 0;i < getNumberEntries() ; i++)
	{
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
		// evaluate each of the expressions given and stored the result
		for (int j =0; j< (int) expressions.size(); j++)
		{
			if (expressions[j] != "")
			{
				try
				{
					values[j] = parsers[j].Eval();
				}
				catch (mu::Parser::exception_type e)
				{
					cerr << e.GetMsg() << endl;
					return 1;
                    // todo:  don't go on when the expression can't be parsed
				}
#ifdef DEBUG
				cout << expressions[j] << " = " <<  values [j] << endl;
#endif
			}
			else
				values[j] = 0;

		}
	
		if (callback(obj,i,values,entries) != 0) return 1; // aborted
	}

	return 0;
}


int ReadRootTree::fillValues_all(void* callback_func,callback_type type,
								 void* obj, 
								 vector<string> expressions)
{
	if (!callback_func) return 0;

	vector<float> values_f(expressions.size());
	vector<string> values_s(expressions.size());

	initParsers(expressions.size());

	for (int j = 0; j < (int) expressions.size(); j++)
	{
		// snap up the expression corresponding to type int and
		// convert them to string
	    for (int i = 0; i < (int) branches.size(); i++)
		{
		  
		}
		
		if (expressions[j] != "")
			parsers[j].SetExpr(expressions[j]);
	}

	for (int i = 0;i < getNumberEntries() ; i++)
	{
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
		// evaluate each of the expressions given and stored the result
		for (int j =0; j< (int) expressions.size(); j++)
		{
			if (expressions[j] != "")
			{
				try
				{
					values_f[j] = parsers[j].Eval();
				}
				catch (mu::Parser::exception_type e)
				{
					cerr << e.GetMsg() << endl;
					return 1;
                    // todo:  don't go on when the expression can't be parsed
				}
#ifdef DEBUG
				cout << expressions[j] << " = " <<  values_f [j] << endl;
#endif
			}
			else
				values_f[j] = 0;

		}
	
		if (callback(obj,i,values_f,entries) != 0) return 1; // aborted
	}

	return 0;
}
