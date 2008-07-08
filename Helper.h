#ifndef _HELPER_H_
#define _HELPER_H_
#include <string>
#include <sys/stat.h>

#define REPLACEMENT_CHAR '_'
#define MAX_LENGTH_FILENAME 100

const std::string invalidFilenameCharacters = "`~#%&*{}\\:?/|;";

std::string validateFilename(std::string s);

bool fileExists(std::string filename);










#endif 
