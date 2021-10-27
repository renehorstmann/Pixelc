#ifndef RHC_STREAM_IMPL_H
#define RHC_STREAM_IMPL_H

#include <assert.h>
#include "../stream.h"


size_t rhc_stream_read(struct Stream_i self, void *memory, size_t n) {
    if(!self.opt_read)
        return 0;
    return self.opt_read(self, memory, n);
}
    

size_t rhc_stream_write(struct Stream_i self, const void *memory, size_t n) {
    if(!self.opt_write)
        return 0;
    return self.opt_write(self, memory, n);
}


size_t rhc_stream_read_msg(struct Stream_i self, void *memory, size_t n) {
    if(!self.opt_read)
        return 0;
    char *buf = memory;
    size_t rem = n;
    while(rem > 0) {
        size_t cnt = self.opt_read(self, buf, rem);
        if(cnt == 0)
            return 0;
        assert(cnt <= rem);
        buf += cnt;
        rem -= cnt;
    }
    return n;
}
    

size_t rhc_stream_write_msg(struct Stream_i self, const void *memory, size_t n) {
    if(!self.opt_write)
        return 0;
    const char *buf = memory;
    size_t rem = n;
    while(rem > 0) {
        size_t cnt = self.opt_write(self, buf, rem);
        if(cnt == 0)
            return 0;
        assert(cnt <= rem);
        buf += cnt;
        rem -= cnt;
    }
    return n;
}



#endif //RHC_STREAM_IMPL_H
