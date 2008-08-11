#ifndef _HELPER_H_
#define _HELPER_H_
#include <string>
#include <sys/stat.h>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h> // need to use <direct.h> if under windows

#include "global.h"

// This file contains some small utility functions

// remove illegal characters like \, ?, etc. from string intended for filename
std::string validateFilename(std::string s);
// whether file exists
bool fileExists(std::string filename);
// get a lists of string of files (optionally with a certain extension) in a
// directory
int getFileList(std::string dir, std::vector<std::string> &files,
                std::string extension);
// get the directory where the program starts from
std::string getCurrentDir();
// concat a list of strings into one, separated by "separator"
std::string joinStrings(std::vector<std::string> strings,
                       std::string separator);
// remove white spaces from beginning and end of a string
std::string trimString(std::string& s);
// take a string a separator it into two parts, name and value
bool parseNameValuePair(const std::string& s,
                        std::string& name, std::string& value,
                        std::string separator = "=");
// convert string to bool
bool atob(const std::string& s);
// convert string to int; wrapper around the standard atoi() for convenience
int atoi(const std::string& s);
// convert string to float; wrapper around the standard atof() for convenience
float atof(const std::string& s);
// convert int to string
std::string itos(const int i);
// convert float to string
std::string ftos(const float);
// get all lines from a file into a vector of strings
void getLines(const std::string& filename, std::vector<std::string>& lines);
// append a line to a file (will be created if not existent)
void appendLine(const std::string& filename, const std::string& line);

#endif 


