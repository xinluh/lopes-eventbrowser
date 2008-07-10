#include "ColumnCollection.h"

#ifdef DEBUG
#endif

using namespace std;

ColumnCollection::ColumnCollection() {};

ColumnCollection::ColumnCollection(vector<string> columnNames)
{
 	singleColumn *c;
 	for (int i = 0; i < (int) columnNames.size(); ++i)
 	{
 	    c = new singleColumn(columnNames[i]);
		columns.push_back(c);
		
 	}
}

ColumnCollection::~ColumnCollection()
{
	for (int i = 0; i < (int) columns.size(); ++i)
	{
	    delete columns[i];
	}
}

void ColumnCollection::addColumn(singleColumn *c)
{
	columns.push_back(c);
}

void ColumnCollection::removeColumn(int index)
{
	cout << "removing " << columns[index]->expression << endl;

	// todo:don't know what in the world is happening here - the item erased
	// is always the one before, but shifting the index will result in index
	// out of bound...

	delete columns[index];
	columns.erase(columns.begin() + index);
}

vector<string> ColumnCollection::getExpressions( bool considerShown)
{
	vector<string> s;
	for (int i = 0; i <(int) columns.size(); ++i)
	{
		if (!considerShown || (considerShown && columns[i]->shown))
			s.push_back(columns[i]->expression);

	}
	return s;
}
					
	
vector<string> ColumnCollection::getAliases( bool considerShown)
{
	vector<string> s;
	for (int i = 0; i <(int) columns.size(); ++i)
	{
		if (!considerShown || (considerShown && columns[i]->shown))
			s.push_back(columns[i]->alias);
	}
	return s;
}

int ColumnCollection::size( bool considerShown)
{
	int n = 0;
	for (int i = 0; i <(int) columns.size(); ++i)
	{
		if (!considerShown || (considerShown && columns[i]->shown))
			n++;
	}
		
	return n;
}
// ColumnCollection* ColumnCollection::clone()
// {
// 	ColumnCollection *c = new ColumnCollection();
// 	c->columns.resize(columns.size());
// 	for (int i = 0; i < (int) columns.size(); ++i)
// 	{
// 	    c->columns[i] = columns[i];
// 	}
// 	return c;
// }

void ColumnCollection::print()
{
	cout << "-----------------------------------" << endl;
	for (int i = 0; i <(int) columns.size(); ++i)
	{
	
		cout << columns[i]->shown << " " << columns[i]->expression
			 << " " << columns[i]->alias << endl;
	}
		
}

void ColumnCollection::saveToFile()
{
	ofstream file;
	file.open (COLUMN_FILE, ios::trunc);
	if (file.is_open())
	{
		for (int i = 0; i < (int) columns.size(); ++i)
		{
		    file << ((columns[i]->shown)? 1 : 0);
			file << CFG_SEPARATOR;
			file << columns[i]->expression;
			file << CFG_SEPARATOR;
			file << columns[i]->alias;
			file << "\n";
		}
		file.close();
	}
}

ColumnCollection* ColumnCollection::readFromFile()
{
	ifstream f(COLUMN_FILE);

	string shown,exp,alias;

	ColumnCollection* cc = new ColumnCollection;
	singleColumn *c;

	while (!getline(f,shown,CFG_SEPARATOR).eof())
	{
		getline(f,exp,CFG_SEPARATOR);
		getline(f,alias);

		c = new singleColumn((shown == "1")? true : false, exp, alias);
		cc->addColumn(c);
	}

	return cc;
}
