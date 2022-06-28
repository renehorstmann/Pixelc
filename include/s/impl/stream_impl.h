#ifndef S_STREAM_IMPL_H
#define S_STREAM_IMPL_H
#ifdef S_IMPL

#include "../memory.h"
#include "../string.h"
#include "../stream.h"

#define S_STREAM_STATIC_BUF_SIZE 128

ssize s_stream_read(sStream_i self, void *memory, ssize n) {
    ssize read = 0;
    do {
        ssize r = s_stream_read_try(self, (su8 *) memory + read, n - read);
        if(r<=0)
            return 0;
        read+=r;
    } while (read < n);
    return read;
}

ssize s_stream_read_as_long_as_valid(sStream_i self, void *memory, ssize n) {
    ssize read = 0;
    do {
        ssize r = s_stream_read_try(self, (su8 *) memory + read, n - read);
        if(r<=0)
            return read;
        read+=r;
    } while (read < n);
    return read;
}

ssize s_stream_write(sStream_i self, const void *memory, ssize n) {
    ssize written = 0;
    do {
        ssize r = s_stream_write_try(self, (su8 *) memory + written, n - written);
        if(r<=0)
            return 0;
        written+=r;
    } while (written < n);
    return written;
}

ssize s_stream_printf_v(sStream_i self, const char *format, va_list args) {
    char static_buf[S_STREAM_STATIC_BUF_SIZE];

    va_list cpy;
    va_copy(cpy, args);
    ssize s = vsnprintf(NULL, 0, format, args);
    char *buf;
    if(s+1<=S_STREAM_STATIC_BUF_SIZE)
        buf = static_buf;
    else
        buf = s_malloc(s+1);

    ssize s2 = vsnprintf(buf, s + 1, format, cpy);
    assert(s==s2 && "different sizes from vsprintf?");
    ssize ret = s_stream_write(self, buf, s);

    if(buf != static_buf)
        s_free(buf);
    va_end(cpy);
    return ret;
}

ssize s_stream_printf(sStream_i self, const char *format, ...) {
    va_list args;
    va_start(args, format);
    ssize ret = s_stream_printf_v(self, format, args);
    va_end(args);
    return ret;
}

ssize s_stream_puts(sStream_i self, const char *text) {
    ssize len = (ssize) strlen(text);
    len = s_stream_write(self, text, len);
    len += s_stream_write(self, "\n", 1);
    s_stream_flush(self);
    return len;
}

ssize s_stream_read_until_into(sStream_i self, void *memory, ssize max, char until) {
    assert(max>0 && "minimum 1 byte for the line");
    ssize len = 0;
    do {
        int r = s_stream_getchar(self);
        if(r<0)
            return 0;
        ((su8*) memory)[len++] = r;
        if(r==until)
            break;
    } while(len<max);
    return len;
}

struct sString *s_stream_read_until(sStream_i self, char until) {
    sString *s = s_string_new(32);
    sStream_i ss = s_string_get_stream(s);
    for(;;) {
        int r = s_stream_getchar(self);
        if(r<0) {
            s_string_kill(&s);
            return s_string_new_invalid();
        }
        s_stream_putchar(ss, (char) r);
        if(r==until)
            break;
    }
    return s;
}


#endif //S_IMPL
#endif //S_STREAM_IMPL_H
