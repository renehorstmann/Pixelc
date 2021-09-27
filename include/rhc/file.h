#ifndef RHC_FILE_H
#define RHC_FILE_H

#include "types.h"
#include "alloc.h"



// reads in a full file into the returned String
String rhc_file_read_a(const char *file, bool ascii, Allocator_s a);
// writes a file and returns false on error
bool rhc_file_write(const char *file, Str_s content, bool ascii);
// appends to a file and returns false on error
bool rhc_file_append(const char *file, Str_s content, bool ascii);



// reads in a full file into the returned String
static String file_read(const char *file, bool ascii) {
    return rhc_file_read_a(file, ascii, RHC_STRING_DEFAULT_ALLOCATOR);
}

// wrapper without _rhc

// reads in a full file into the returned String
static String file_read_a(const char *file, bool ascii, Allocator_s a) {
    return rhc_file_read_a(file, ascii, a);
}

// writes a file and returns false on error
static bool file_write(const char *file, Str_s content, bool ascii) {
    return rhc_file_write(file, content, ascii);
}

// appends to a file and returns false on error
static bool file_append(const char *file, Str_s content, bool ascii) {
    return rhc_file_append(file, content, ascii);
}


#endif //RHC_FILE_H
