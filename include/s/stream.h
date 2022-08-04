#ifndef S_STREAM_H
#define S_STREAM_H

//
// Stream interface and functions
//    Implementations are in string.h, file.h and socket.h
//

#include "export.h"
#include "common.h"

struct sString;

//
// Interface
//

struct sStream_i;

typedef ssize (*s_stream_read_try_fn)(struct sStream_i stream, void *memory, ssize n);
typedef ssize (*s_stream_write_try_fn)(struct sStream_i stream, const void *memory, ssize n);
typedef void (*s_stream_flush_fn)(struct sStream_i stream);
typedef bool (*s_stream_valid_fn)(struct sStream_i stream);

typedef struct sStream_i {
    void *impl;

    // vtable
    s_stream_read_try_fn opt_read_try;
    s_stream_write_try_fn opt_write_try;
    s_stream_flush_fn opt_flush;
    s_stream_valid_fn valid;
} sStream_i;


//
// Functions
//

static sStream_i s_stream_new_invalid() {
    return (sStream_i) {0};
}

// trys to reads up to n bytes from the stream into memory
// returns bytes read or <=0 on error
static ssize s_stream_read_try(sStream_i self, void *memory, ssize n) {
    assert(self.opt_read_try);
    return self.opt_read_try(self, memory, n);
}
    
// trys writes up to n bytes into the stream from memory
// returns bytes written or <=0 on error
static ssize s_stream_write_try(sStream_i self, const void *memory, ssize n) {
    assert(self.opt_write_try);
    return self.opt_write_try(self, memory, n);
}

// flushes the stream, if opt_flush is available
static void s_stream_flush(sStream_i self) {
    if(self.opt_flush)
        self.opt_flush(self);
}

// returns true, if the stream (implementation) is in a valid state
static bool s_stream_valid(sStream_i self) {
    if(!self.valid)
        return false;
    return self.valid(self);
}

// reads exactly n bytes from the stream into memory
// returns bytes read or <=0 on error
S_EXPORT
ssize s_stream_read(sStream_i self, void *memory, ssize n);

// reads exactly n bytes, if the stream stays valid
// returns bytes read or <=0 on error
S_EXPORT
ssize s_stream_read_as_long_as_valid(sStream_i self, void *memory, ssize n);

// writes exactly n bytes into the stream into memory
// returns bytes written or <=0 on error
S_EXPORT
ssize s_stream_write(sStream_i self, const void *memory, ssize n);

// print formatted on the stream
S_EXPORT
ssize s_stream_printf_v(sStream_i self, const char *format, va_list args);

// print formatted on the stream
S_EXPORT
ssize s_stream_printf(sStream_i self, const char *format, ...);

// print a line of text on the stream
S_EXPORT
ssize s_stream_puts(sStream_i self, const char *text);

// reads a single byte from the stream
// returns -1 on error
static int s_stream_getchar(sStream_i self) {
    char c;
    if(s_stream_read_try(self, &c, 1) <= 0)
        return -1;
    return (int) c;
}

// writes a single byte into the stream
// returns false on error
static bool s_stream_putchar(sStream_i self, char c) {
    return s_stream_write_try(self, &c, 1) == 1;
}

// reads from the string into memory, until the given char "until" (which will be included)
// stops on max characters. To check if there are more characters before "until", simple check:
//      if(returned_line_len==max && memory[returned_line_len-1]!=until)
//          // more characters in the line
// returns 0 on error
S_EXPORT
ssize s_stream_read_until_into(sStream_i self, void *memory, ssize max, char until);

// reads into the returned String, until the given char "until" (which will be included)
// returns an invalid string on error
S_EXPORT
struct sString *s_stream_read_until(sStream_i self, char until);


// reads from the string into memory, until newline (which will be included)
// stops on max characters. To check if there are more characters in the line, simple check:
//      if(returned_line_len==max && memory[returned_line_len-1]!='\n')
//          // more characters in the line
// returns 0 on error
static ssize s_stream_read_line_into(sStream_i self, void *memory, ssize max) {
    return s_stream_read_until_into(self, memory, max, '\n');
}

// reads into the returned String, until newline (which will be included)
// returns an invalid string on error
static struct sString *s_stream_read_line(sStream_i self) {
    return s_stream_read_until(self, '\n');
}



#endif //S_STREAM_H
