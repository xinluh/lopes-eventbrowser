#include "Helper.h"

#include <fstream>
#include <string>
#include <sstream>


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

// from http://www.codeproject.com/KB/stl/stdstringtrim.aspx 
string trimString(string& str)
{
  string::size_type pos = str.find_last_not_of(' ');
  if(pos != string::npos) {
    str.erase(pos + 1);
    pos = str.find_first_not_of(' ');
    if(pos != string::npos) str.erase(0, pos);
  }
  else str.erase(str.begin(), str.end());

  return str;
}

bool parseNameValuePair(const std::string& s,
                        std::string& name, std::string& value,
                        std::string separator)
{
    int pos = s.find_first_of(separator);
    
    if (pos == (int) string::npos) return false; // parse failed

    name = s.substr(0,pos - 1);
    value = ((pos == (int) s.size() - 1)?
             "" : s.substr(pos + 1, string::npos));

    trimString(name);
    trimString(value);

    return true;
}

bool atob(const std::string& s)
{
    int i = atoi(s.c_str());
    return (i == 0)? false : true;
}

int atoi(const std::string& s)
{
    return atoi(s.c_str());
}

float atof(const std::string& s)
{
    return atof(s.c_str());
}

string itos(const int i)
{
   string s;
   stringstream out;
   out << i;
   return out.str();
}

string ftos(const float i)
{
   string s;
   stringstream out;
   out << i;
   return out.str();
}

void getLines(const string& filename, vector<string>& lines)
{
    ifstream file(filename.c_str());
    string line;
    lines.clear();
    
    if (file.is_open())
    {
        
        while (!file.eof())
        {
            getline(file,line);
            if (!line.empty())
                lines.push_back(line);
        }
        file.close();
    }
}

void appendLine(const string& filename, const string& line)
{
    ofstream file;
    file.open(filename.c_str(),ios::app);
    file << line << endl;
    file.close();
}


#ifdef USE_QT
QString s(const string& str)
{
    return QString::fromStdString(str);
}
#endif //USE_QT
