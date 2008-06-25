#ifndef _HELPER_H_
#define _HELPER_H_
#include <string>

#define REPLACEMENT_CHAR '_'
#define MAX_LENGTH_FILENAME 100

const std::string invalidFilenameCharacters = "`~#%&*{}\\:?/|;";

std::string ValidateFilename(std::string s);









#endif 
