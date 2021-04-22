#ifndef RHC_FILE_H
#define RHC_FILE_H

#include "types.h"
#include "allocator.h"



// reads in a full file into the returned String
String file_read_a(const char *file, bool ascii, Allocator_s a);

// reads in a full file into the returned String
static String file_read(const char *file, bool ascii) {
    return file_read_a(file, ascii, RHC_STRING_DEFAULT_ALLOCATOR);
}


bool file_write(const char *file, Str_s content, bool ascii);

bool file_append(const char *file, Str_s constent, bool ascii);

#endif //RHC_FILE_H
