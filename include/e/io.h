#ifndef E_IO_H
#define E_IO_H

//
// write and load files under specific directories
//

#include "rhc/types.h"


#define E_IO_SAVESTATE_MAX_FILENAME_LENGTH 128


// read a savestate file
// web will read a IndexedDB file (like a cookie)
// others read savestate_<filename>
// filename must not include directories (/)
String e_io_savestate_read(const char *filename, bool ascii);


// write a savestate file
// web will create a IndexedDB file (like a cookie)
// others create savestate_<filename>
// filename must not include directories (/)
// returns false on error
bool e_io_savestate_write(const char *filename, Str_s content, bool ascii);


// appends to a savestate file
// web will create a IndexedDB file (like a cookie)
// others create savestate_<filename>
// filename must not include directories (/)
// returns false on error
bool e_io_savestate_append(const char *filename, Str_s content, bool ascii);



#endif //E_IO_H
