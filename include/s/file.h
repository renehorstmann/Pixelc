#ifndef S_FILE_H
#define S_FILE_H

//
// open, read and write files
// get a sStream_i from the file
//

#include "string.h"

#define S_FILE_STORAGE_SIZE 8

typedef struct sFile sFile;


bool s_file_valid(sFile *self);

// opens a file to read
sFile *s_file_new_read(const char *file, bool ascii);

// opens a file to write
sFile *s_file_new_write(const char *file, bool ascii);

// opens a file to append
sFile *s_file_new_append(const char *file, bool ascii);

// closes the file
void s_file_kill(sFile **self_ptr);

// returns the size of the whole file, returns 0 on error
ssize s_file_size(sFile *self);

// returns a stream from the file (read and write)
sStream_i s_file_stream(sFile *file);

// returns an input/read stream from the file
static sStream_i s_file_stream_in(sFile *self) {
    sStream_i stream = s_file_stream(self);
    stream.opt_write_try = NULL;
    return stream;
}

// returns an output/write stream from the file
static sStream_i s_file_stream_out(sFile *self) {
    sStream_i stream = s_file_stream(self);
    stream.opt_read_try = NULL;
    return stream;
}

// creates a stream from a c FILE*
sStream_i s_file_stream_from_cfile(FILE *cfile, bool read, bool write);

// Returns a stream from the system file
static sStream_i s_file_stream_stdout() {
    return s_file_stream_from_cfile(stdout, false, true);
}

// Returns a stream from the system file
static sStream_i s_file_stream_stderr() {
    return s_file_stream_from_cfile(stderr, false, true);
}

// Returns a stream from the system file
static sStream_i s_file_stream_stdin() {
    return s_file_stream_from_cfile(stdin, true, false);
}


// reads in a full file into the returned sString
sString *s_file_read_a(const char *file, bool ascii, sAllocator_i a);

static sString *s_file_read(const char *file, bool ascii) {
    return s_file_read_a(file, ascii, S_ALLOCATOR_DEFAULT);
}

// writes a file and returns false on error
bool s_file_write(const char *file, sStr_s content, bool ascii);

// appends to a file and returns false on error
bool s_file_append(const char *file, sStr_s content, bool ascii);

#endif //S_FILE_H
