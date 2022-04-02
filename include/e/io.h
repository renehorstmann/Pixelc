#ifndef E_IO_H
#define E_IO_H

//
// write and load files under specific directories
//

#include "rhc/types.h"


#define E_IO_SAVESTATE_MAX_FILENAME_LENGTH 128

// callback for file uploads, only called on success
// file and ascii must not be checked and are the same as for e_io_ask_for_file_upload
typedef void (*eIoFileUploadCallback)(const char *file, bool ascii, const char *user_file_name, void *user_data);


// web: offer the given file as download
void e_io_offer_file_as_download(const char *file);

// web: opens a file dialog to upload a file
//      on success, callback is called
//      should be called after a pointer event, or the browser may discard the file dialog
void e_io_ask_for_file_upload(const char *file, bool ascii, eIoFileUploadCallback callback, void *user_data);


// web: save files saved with e_io_savestate_file_path to IndexedDB
void e_io_savestate_save();


struct eIoSavestateString {
    // Additional 64 bytes for the path (+title for web)
    char s[64 + E_IO_SAVESTATE_MAX_FILENAME_LENGTH];
};

// creates a savestate file path to load and save with default FILE's
// filename must not include directories (/)
// returns an empty / cleared string, if not valid
struct eIoSavestateString e_io_savestate_file_path(const char *filename);



// read a savestate file
// web will read a IndexedDB file (like a cookie)
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
//     calls e_io_savestate_save
// others create savestate_<filename>
// filename must not include directories (/)
// returns false on error
bool e_io_savestate_append(const char *filename, Str_s content, bool ascii);


#endif //E_IO_H
