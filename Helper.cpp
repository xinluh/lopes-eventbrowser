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
				INVALID_CHAR_REPLACEMENT_CHAR);
	}

	if (s.length() > MAX_LENGTH_SAVE_FILENAME)
		s.erase(MAX_LENGTH_SAVE_FILENAME); //truncate the name if too long
	
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
  if(intStat == 0)
  {
    // We were able to get the file attributes
    // so the file obviously exists.
    blnReturn = true;
  } else
  {
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

int getFileList (string dir, vector<string> &files, string extension)
{
    DIR *dp;
    struct dirent *dirp;

	files.clear();

	if (dir.length() == 0)
		dir = getCurrentDir();

	if((dp  = opendir(dir.c_str())) == NULL)
	{
        cerr << "Error opening " << dir << endl;
        return -1;
    }

    while ((dirp = readdir(dp)) != NULL)
	{
		string s(dirp->d_name);

		if (s.length() > extension.length() &&
		    (s.compare(s.length() - extension.length(),
					   extension.length(),extension) == 0))
			files.push_back(string(dirp->d_name));
    }

	closedir(dp);
    return 0;
}

string getCurrentDir()
{
	char * s = new char[250];
	string *str;
	if (getcwd(s,250))
		str = new string(s);
	else
		str = new string;

	delete s;
	return *str;
}

string joinStrings(vector<string> strings, string separator)
{
	string s;

	for (int i = 0; i < (int) strings.size(); ++i)
	{
		if (s.length() != 0)
			s += separator;

		s += strings[i];
	}

	return s;
}
