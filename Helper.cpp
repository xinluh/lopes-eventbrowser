#include "Helper.h"

#ifdef DEBUG
#include <iostream>
#endif

using namespace std;


string validateFilename(string s)
{
	if (s.empty()) return s;

	for (int i = 0; i < (int) invalidFilenameCharacters.length(); i++)
	{
		replace(s.begin(),s.end(),invalidFilenameCharacters.c_str()[i],
				REPLACEMENT_CHAR);
	}

	if (s.length() > MAX_LENGTH_FILENAME)
		s.erase(MAX_LENGTH_FILENAME); //truncate the name if too long
	
	//  cout << s << endl;

	return s;
} 
