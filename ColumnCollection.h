#ifndef _COLUMNCOLLECTION_H_
#define _COLUMNCOLLECTION_H_
#include <string>
#include <vector>
#include <fstream>
#include <iostream>


#include "Helper.h"
#include "global.h"

#define COLUMN_FILE "columns.cfg"
#define CFG_SEPARATOR '|'

struct singleColumn
{
	std::string alias;
	std::string expression;
	bool shown;

	singleColumn();
	singleColumn(std::string exp)
	{
		alias = validateFilename(exp);
		expression = exp;
		shown = true;
	}
	singleColumn(bool _shown, std::string exp, std::string _alias)
	{
		shown = _shown;
		expression = exp;
		alias = _alias;
	}
			
};

class ColumnCollection
 {
 private:
 	

  public:
 	ColumnCollection();
 	ColumnCollection(std::vector<std::string> columns);
 	~ColumnCollection();

	std::vector<singleColumn*> columns;
	
	// when considerShown is true, the expression/alias from the column marked
	// as not shown is not included
	std::vector<std::string> getExpressions(bool considerShown = false);
	std::vector<std::string> getAliases(bool considerShown = false);
	int size(bool considerShown = false);
	void addColumn (singleColumn * c);
	void removeColumn (int index);
	
	void print();
	void saveToFile();
	static ColumnCollection* readFromFile();
//	ColumnCollection* clone();
	 
 };



#endif /* _COLUMNCOLLECTION_H_ */
