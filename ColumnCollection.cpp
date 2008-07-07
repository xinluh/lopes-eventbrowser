#include "ColumnCollection.h"

#ifdef DEBUG
#include <iostream>
#endif



using namespace std;

 ColumnCollection::ColumnCollection(vector<string> columnNames)
 {
 	singleColumn *c;
 	for (int i = 0; i < (int) columnNames.size(); ++i)
 	{
 	    c = new singleColumn(columnNames[i]);
		columns.push_back(*c);
		
 	}
 }

vector<string> ColumnCollection::getExpressions( bool considerShown)
{
	vector<string> s;
	for (int i = 0; i <(int) columns.size(); ++i)
	{
		if (!considerShown || (considerShown && columns[i].shown))
			s.push_back(columns[i].expression);

	}
	return s;
}
					
	
vector<string> ColumnCollection::getAliases( bool considerShown)
{
	vector<string> s;
	for (int i = 0; i <(int) columns.size(); ++i)
	{
		if (!considerShown || (considerShown && columns[i].shown))
			s.push_back(columns[i].alias);
	}
	return s;
}

int ColumnCollection::size( bool considerShown)
{
	int n = 0;
	for (int i = 0; i <(int) columns.size(); ++i)
	{
		if (!considerShown || (considerShown && columns[i].shown))
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
	
		cout << columns[i].shown << " " << columns[i].expression << " " << columns[i].alias << endl;
	}
		
}
