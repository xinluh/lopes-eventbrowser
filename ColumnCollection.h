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
		alias = ValidateFilename(exp);
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
	std::vector<std::string> getExpressions();
	std::vector<std::string> getAliases();

//	ColumnCollection* clone();
	 
 };



#endif /* _COLUMNCOLLECTION_H_ */
