#ifndef E_IO_H
#define E_IO_H

//
// write and load files under specific directories
//

#include "rhc/types.h"


#define E_IO_SAVESTATE_MAX_FILENAME_LENGTH 128


// web: mount and load IndexedDB files
void e_io_savestate_load();

// web: save files to IndexedDB
void e_io_savestate_save();


struct eIoSavestateString {
    // Additional 16 bytes for the path
    char s[16 + E_IO_SAVESTATE_MAX_FILENAME_LENGTH];
};

// creates a savestate file path to load and save with default FILE's
// filename must not include directories (/)
// returns an empty / cleared string, if not valid
struct eIoSavestateString e_io_savestate_file_path(const char *filename);



// read a savestate file
// web will read a IndexedDB file (like a cookie)
//     calls e_io_savestate_load
// others read savestate_<filename>
// filename must not include directories (/)
String e_io_savestate_read(const char *filename, bool ascii);


// write a savestate file
// web will create a IndexedDB file (like a cookie)
//     calls e_io_savestate_save
// others create savestate_<filename>
// filename must not include directories (/)
// returns false on error
bool e_io_savestate_write(const char *filename, Str_s content, bool ascii);


// appends to a savestate file
// web will create a IndexedDB file (like a cookie)
//     calls e_io_savestate_load
//     calls e_io_savestate_save
// others create savestate_<filename>
// filename must not include directories (/)
// returns false on error
bool e_io_savestate_append(const char *filename, Str_s content, bool ascii);



#endif //E_IO_H
