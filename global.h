#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <string>


// contains some global definitions

#define COLUMN_FILE "columns.cfg"
#define CFG_SEPARATOR '|'
#define CFG_COMMENT_CHAR ';'

#define INVALID_CHAR_REPLACEMENT_CHAR '_'
#define MAX_LENGTH_SAVE_FILENAME 100

#define MAX_LINE 2048
#define END_OF_LINE '\n'

const std::string invalidFilenameCharacters = "`~#%&*{}\\:?/|;";



#endif // _GLOBAL_H_ 
