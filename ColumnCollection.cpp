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

vector<string> ColumnCollection::getExpressions()
{
	vector<string> s;
	for (int i = 0; i <(int) columns.size(); ++i)
	{
		cout << columns[i].expression << endl;
		
		s.push_back(columns[i].expression);

	}
	return s;
}
					
	
vector<string> ColumnCollection::getAliases()
{
	vector<string> s;
	for (int i = 0; i <(int) columns.size(); ++i)
		s.push_back(columns[i].alias);
	return s;
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
