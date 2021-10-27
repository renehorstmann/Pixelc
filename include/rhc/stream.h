#ifndef RHC_STREAM_H
#define RHC_STREAM_H

#include "types.h"

// reads up to n bytes from the stream into memory
// returns bytes read or 0 on error
// if self.read is NULL, 0 is returned
size_t rhc_stream_read(struct Stream_i self, void *memory, size_t n);
    
// writes up to n bytes into the stream from memory
// returns bytes written or 0 on error
// if self.write is NULL, 0 is returned
size_t rhc_stream_write(struct Stream_i self, const void *memory, size_t n);

// reads exactly n bytes from the stream into memory
// returns bytes read or 0 on error
// if self.read is NULL, 0 is returned
size_t rhc_stream_read_msg(struct Stream_i self, void *memory, size_t n);
    
// writes exactly n bytes into the stream from memory
// returns bytes written or 0 on error
// if self.write is NULL, 0 is returned
size_t rhc_stream_write_msg(struct Stream_i self, const void *memory, size_t n);


//
// wrapper
//

// reads up to n bytes from the stream into memory
// returns bytes read or 0 on error
// if self.read is NULL, 0 is returned
#define stream_read rhc_stream_read
    
// writes up to n bytes into the stream from memory
// returns bytes written or 0 on error
// if self.write is NULL, 0 is returned
#define stream_write rhc_stream_write

// reads exactly n bytes from the stream into memory
// returns bytes read or 0 on error
// if self.read is NULL, 0 is returned
#define stream_read_msg rhc_stream_read_msg
    
// writes exactly n bytes into the stream from memory
// returns bytes written or 0 on error
// if self.write is NULL, 0 is returned
#define stream_write_msg rhc_stream_write_msg


#endif //RHC_STREAM_H
