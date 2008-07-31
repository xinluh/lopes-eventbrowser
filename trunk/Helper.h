#ifndef _HELPER_H_
#define _HELPER_H_
#include <string>
#include <sys/stat.h>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h> // need to use <direct.h> if under windows

#include "global.h"


std::string validateFilename(std::string s);

bool fileExists(std::string filename);

int getFileList(std::string dir, std::vector<std::string> &files,
				std::string extension);

std::string getCurrentDir();

std::string joinStrings(std::vector<std::string> strings,
					   std::string separator);

std::string trimString(std::string& s);

bool parseNameValuePair(const std::string& s,
						std::string& name, std::string& value,
						std::string separator = "=");

// convert string to bool
bool atob(const std::string& s);

#endif 
