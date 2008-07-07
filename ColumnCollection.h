#ifndef _COLUMNCOLLECTION_H_
#define _COLUMNCOLLECTION_H_
#include <string>
#include <vector>

#include "Helper.h"


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
};

//typedef std::vector<singleColumn> ColumnCollection;

class ColumnCollection
 {
 private:
 	

  public:
 	ColumnCollection();
 	ColumnCollection(std::vector<std::string> columns);
 	~ColumnCollection();

	std::vector<singleColumn> columns;
	
	// when considerShown is true, the expression/alias from the column marked
	// as not shown is not included
	std::vector<std::string> getExpressions(bool considerShown = false);
	std::vector<std::string> getAliases(bool considerShown = false);
	int size(bool considerShown = false);

	void print();
//	ColumnCollection* clone();
	 
 };



#endif /* _COLUMNCOLLECTION_H_ */
