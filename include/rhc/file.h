#ifndef RHC_FILE_H
#define RHC_FILE_H

#include "types.h"
#include "alloc.h"

#define RHC_FILE_STORAGE_SIZE 8

typedef struct {
    Stream_i stream;
    Allocator_i a;
    char impl_storage[RHC_FILE_STORAGE_SIZE];
} RhcFile;

// safe way to use the Stream interface
static Stream_i rhc_file_get_stream(RhcFile *self) {
    if (!self)
        return stream_new_invalid();
    return self->stream;
}

// returns true, if the rhc file is valid to use
bool rhc_file_valid(const RhcFile *self);

// opens a file as rhc stream to read
RhcFile *rhc_file_open_read_a(const char *file, bool ascii, Allocator_i a);

// opens a file as rhc stream to write
RhcFile *rhc_file_open_write_a(const char *file, bool ascii, Allocator_i a);

// opens a file as rhc stream to append
RhcFile *rhc_file_open_append_a(const char *file, bool ascii, Allocator_i a);

// closes the rhc stream file
void rhc_file_kill(RhcFile **self_ptr);


// reads in a full file into the returned String
String rhc_file_read_a(const char *file, bool ascii, Allocator_i a);
// writes a file and returns false on error
bool rhc_file_write(const char *file, Str_s content, bool ascii);
// appends to a file and returns false on error
bool rhc_file_append(const char *file, Str_s content, bool ascii);


//
// wrapper
//

// opens a file as rhc stream to read
static RhcFile *rhc_file_open_read(const char *file, bool ascii) {
    return rhc_file_open_read_a(file, ascii, RHC_DEFAULT_ALLOCATOR);
}

// opens a file as rhc stream to write
static RhcFile *rhc_file_open_write(const char *file, bool ascii) {
    return rhc_file_open_write_a(file, ascii, RHC_DEFAULT_ALLOCATOR);
}

// opens a file as rhc stream to append
static RhcFile *rhc_file_open_append(const char *file, bool ascii) {
    return rhc_file_open_append_a(file, ascii, RHC_DEFAULT_ALLOCATOR);
}

// reads in a full file into the returned String
static String file_read(const char *file, bool ascii) {
    return rhc_file_read_a(file, ascii, RHC_DEFAULT_ALLOCATOR);
}

//
// wrapper without _rhc
//

// reads in a full file into the returned String
static String file_read_a(const char *file, bool ascii, Allocator_i a) {
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
