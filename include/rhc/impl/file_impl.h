#ifndef RHC_FILE_IMPL_H
#define RHC_FILE_IMPL_H
#ifdef RHC_IMPL

#include <stdio.h>
#include "../error.h"
#include "../str.h"
#include "../string.h"
#include "../log.h"
#include "../file.h"

#ifdef OPTION_SDL
#include <SDL.h>
#endif


#ifdef OPTION_SDL
String file_read_a(const char *file, bool ascii, Allocator_s a) {
    if(!allocator_valid(a)) {
        rhc_error = "file read failed, allocator invalid";
        log_error("file_read_a failed, allocator invalid: %s", file);
        return string_new_invalid_a(a);
    }

    SDL_RWops *f = SDL_RWFromFile(file, ascii ? "r" : "rb");
    if (!f) {
        rhc_error = "file read failed";
        log_warn("file_read_a failed: %s", file);
        return string_new_invalid_a(a);
    }

    Sint64 length = SDL_RWsize(f);
    String res = string_new_a(length, a);

    if (string_valid(res)) {
        Sint64 buf_appended = 1;
        char *buf = res.data;
        while (res.size < length && buf_appended != 0) {
            buf_appended = SDL_RWread(f, buf, 1, length - res.size);
            res.size += buf_appended;
            buf += buf_appended;
        }
        if (res.size != length) {
            log_error("file_read_a failed: %s %d/%d bytes read", file, res.size, length);
            string_kill(&res);
        } else {
            res.data[length] = '\0';  // should have been set in String, just to be sure
        }
    }
    SDL_RWclose(f);
    return res;
}

bool file_write(const char *file, Str_s content, bool ascii) {
    if(!str_valid(content)) {
        rhc_error = "file write failed, content invalid";
        log_error("file_write failed, content invalid: %s", file);
        return false;
    }

    SDL_RWops *f = SDL_RWFromFile(file, ascii ? "w" : "wb");
    if (!f) {
        rhc_error = "file write failed";
        log_warn("file_write failed: %s", file);
        return false;
    }

    Sint64 chars_written = 0, buf_appended = 1;
    char *buf = content.data;
    while(chars_written < content.size && buf_appended != 0) {
        buf_appended = SDL_RWwrite(f, buf, 1, content.size - chars_written);
        chars_written += buf_appended;
        buf += buf_appended;
    }

    SDL_RWclose(f);

    if (chars_written != content.size) {
        log_error("file_write failed: %s %d/%d bytes written", file, chars_written, content.size);
        return false;
    }
    return true;
}

bool file_append(const char *file, Str_s content, bool ascii) {
    if(!str_valid(content)) {
        rhc_error = "file append failed, content invalid";
        log_error("file_append failed, content invalid: %s", file);
        return false;
    }

    SDL_RWops *f = SDL_RWFromFile(file, ascii ? "a" : "ab");
    if (!f) {
        rhc_error = "file append failed";
        log_warn("file_append failed: %s", file);
        return false;
    }

    Sint64 chars_written = 0, buf_appended = 1;
    char *buf = content.data;
    while(chars_written < content.size && buf_appended != 0) {
        buf_appended = SDL_RWwrite(f, buf, 1, content.size - chars_written);
        chars_written += buf_appended;
        buf += buf_appended;
    }

    SDL_RWclose(f);

    if (chars_written != content.size) {
        log_error("file_append failed: %s %d/%d bytes written", file, chars_written, content.size);
        return false;
    }
    return true;
}


#else
// unix file implementation

String file_read_a(const char *file, bool ascii, Allocator_s a) {
    if(!allocator_valid(a)) {
        rhc_error = "file read failed, allocator invalid";
        log_error("file_read_a failed, allocator invalid: %s", file);
        return string_new_invalid_a(a);
    }

    FILE *f = fopen(file, ascii ? "r" : "rb");
    if (!f) {
        rhc_error = "file read failed";
        log_warn("file_read_a failed: %s", file);
        return string_new_invalid_a(a);
    }

    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);
    String res = string_new_a(length, a);

    if (string_valid(res)) {
        size_t buf_appended = 1;
        char *buf = res.data;
        while(res.size < length && buf_appended != 0) {
            buf_appended = fread(buf, 1, (length - res.size), f);
            res.size += buf_appended;
            buf += buf_appended;
        }
        if (res.size != length) {
            log_error("file_read_a failed: %s %d/%d bytes read", file, res.size, length);
            string_kill(&res);
        } else {
            res.data[length] = '\0';  // should have been set in String, just to be sure
        }
    }
    fclose(f);
    return res;
}

bool file_write(const char *file, Str_s content, bool ascii) {
    if(!str_valid(content)) {
        rhc_error = "file write failed, content invalid";
        log_error("file_write failed, content invalid: %s", file);
        return false;
    }

    FILE *f = fopen(file, ascii ? "w" : "wb");
    if (!f) {
        rhc_error = "file write failed";
        log_warn("file_write failed: %s", file);
        return false;
    }

    size_t chars_written = 0, buf_appended = 1;
    char *buf = content.data;
    while(chars_written < content.size && buf_appended != 0) {
        buf_appended = fwrite(buf, 1, content.size - chars_written, f);
        chars_written += buf_appended;
        buf += buf_appended;
    }

    fclose(f);

    if (chars_written != content.size) {
        log_error("file_write failed: %s %d/%d bytes written", file, chars_written, content.size);
        return false;
    }
    return true;
}

bool file_append(const char *file, Str_s content, bool ascii) {
    if(!str_valid(content)) {
        rhc_error = "file append failed, content invalid";
        log_error("file_append failed, content invalid: %s", file);
        return false;
    }

    FILE *f = fopen(file, ascii ? "a" : "ab");
    if (!f) {
        rhc_error = "file append failed";
        log_warn("file_append failed: %s", file);
        return false;
    }

    size_t chars_written = 0, buf_appended = 1;
    char *buf = content.data;
    while(chars_written < content.size && buf_appended != 0) {
        buf_appended = fwrite(buf, 1, content.size - chars_written, f);
        chars_written += buf_appended;
        buf += buf_appended;
    }

    fclose(f);

    if (chars_written != content.size) {
        log_error("file_append failed: %s %d/%d bytes written", file, chars_written, content.size);
        return false;
    }
    return true;
}
#endif



#endif //RHC_IMPL
#endif //RHC_FILE_IMPL_H
