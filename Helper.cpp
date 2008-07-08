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

// from http://www.techbytes.ca/techbyte103.html
bool fileExists(string strFilename)
{
  struct stat stFileInfo;
  bool blnReturn;
  int intStat;

  // Attempt to get the file attributes
  intStat = stat(strFilename.c_str(),&stFileInfo);
  if(intStat == 0) {
    // We were able to get the file attributes
    // so the file obviously exists.
    blnReturn = true;
  } else {
    // We were not able to get the file attributes.
    // This may mean that we don't have permission to
    // access the folder which contains this file. If you
    // need to do that level of checking, lookup the
    // return values of stat which will give you
    // more details on why stat failed.
    blnReturn = false;
  }
  
  return(blnReturn);
}
