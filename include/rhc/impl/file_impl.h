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
#include <SDL2/SDL.h>
#endif


#ifdef OPTION_SDL
typedef struct {
    SDL_RWops *file;
} SdlFile;
_Static_assert(sizeof (SdlFile) <= RHC_FILE_STORAGE_SIZE, "storage not big enough");

static size_t file_stream_read(Stream_i stream, void *msg, size_t size) {
    RhcFile *self = stream.user_data;
    if(!rhc_file_valid(self))
        return 0;

    SdlFile *impl = (SdlFile*) self->impl_storage;

    size_t n = SDL_RWread(impl->file,msg, 1, size);
    if(n <= 0) {
        log_error("rhc_file_read failed, killing file...");
        SDL_RWclose(impl->file);
        impl->file = NULL;
        return 0;
    }
    assert(n <= size);
    return (size_t) n;
}

static size_t file_stream_write(Stream_i stream, void *msg, size_t size) {
    RhcFile *self = stream.user_data;
    if(!rhc_file_valid(self))
        return 0;

    SdlFile *impl = (SdlFile*) self->impl_storage;

    size_t n = SDL_RWwrite(impl->file, msg, 1, size);
    if(n <= 0) {
        log_error("rhc_file_write failed, killing file...");
        SDL_RWclose(impl->file);
        impl->file = NULL;
        return 0;
    }
    assert(n <= size);
    return (size_t) n;
}

bool rhc_file_valid(const RhcFile *self) {
    if(!self)
        return false;
    SdlFile *impl = (SdlFile*) self->impl_storage;
    return impl->file;
}

RhcFile *rhc_file_open_read_a(const char *file, bool ascii, Allocator_i a) {
    RhcFile *self = a.calloc(a, sizeof *self);
    SdlFile *impl = (SdlFile*) self->impl_storage;
    self->stream = (Stream_i) {self, file_stream_read, NULL};
    self->allocator = a;
    impl->file = SDL_RWFromFile(file, ascii ? "r" : "rb");
    if (!impl->file) {
        rhc_error = "rhc_file_open_read_a failed";
        log_warn("rhc_file_open_read_a failed: %s", file);
        a.free(a, self);
        return NULL;
    }
    return self;
}
RhcFile *rhc_file_open_write_a(const char *file, bool ascii, Allocator_i a) {
    RhcFile *self = a.calloc(a, sizeof *self);
    SdlFile *impl = (SdlFile*) self->impl_storage;
    self->stream = (Stream_i) {self, file_stream_read, NULL};
    self->allocator = a;
    impl->file = SDL_RWFromFile(file, ascii ? "w" : "wb");
    if (!impl->file) {
        rhc_error = "rhc_file_open_write_a failed";
        log_warn("rhc_file_open_write_a failed: %s", file);
        a.free(a, self);
        return NULL;
    }
    return self;
}
RhcFile *rhc_file_open_append_a(const char *file, bool ascii, Allocator_i a) {
    RhcFile *self = a.calloc(a, sizeof *self);
    SdlFile *impl = (SdlFile*) self->impl_storage;
    self->stream = (Stream_i) {self, file_stream_read, NULL};
    self->allocator = a;
    impl->file = SDL_RWFromFile(file, ascii ? "a" : "ab");
    if (!impl->file) {
        rhc_error = "rhc_file_open_append_a failed";
        log_warn("rhc_file_open_append_a failed: %s", file);
        a.free(a, self);
        return NULL;
    }
    return self;
}

void rhc_file_kill(RhcFile **self_ptr) {
    RhcFile *self = *self_ptr;
    if(!self)
        return;
    SdlFile *impl = (SdlFile*) self->impl_storage;
    SDL_RWclose(impl->file);
    self->allocator.free(self->allocator, self);
    *self_ptr = NULL;
}
String rhc_file_read_a(const char *file, bool ascii, Allocator_i a) {
    if(!allocator_valid(a)) {
        rhc_error = "file read failed, allocator invalid";
        log_error("rhc_file_read_a failed, allocator invalid: %s", file);
        return string_new_invalid_a(a);
    }

    SDL_RWops *f = SDL_RWFromFile(file, ascii ? "r" : "rb");
    if (!f) {
        rhc_error = "file read failed";
        log_warn("rhc_file_read_a failed: %s", file);
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
        //  CRLF will be converted to LF on windows in ascii and will be a byte smaller
        if (!ascii && res.size != length) {
            log_error("rhc_file_read_a failed: %s %d/%d bytes read", file, res.size, length);
            string_kill(&res);
        } else {
            res.data[length] = '\0';  // should have been set in String, just to be sure
        }
    }
    SDL_RWclose(f);
    return res;
}

bool rhc_file_write(const char *file, Str_s content, bool ascii) {
    if(!str_valid(content)) {
        rhc_error = "file write failed, content invalid";
        log_error("rhc_file_write failed, content invalid: %s", file);
        return false;
    }

    SDL_RWops *f = SDL_RWFromFile(file, ascii ? "w" : "wb");
    if (!f) {
        rhc_error = "file write failed";
        log_warn("rhc_file_write failed: %s", file);
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
        log_error("rhc_file_write failed: %s %d/%d bytes written", file, chars_written, content.size);
        return false;
    }
    return true;
}

bool rhc_file_append(const char *file, Str_s content, bool ascii) {
    if(!str_valid(content)) {
        rhc_error = "file append failed, content invalid";
        log_error("rhc_file_append failed, content invalid: %s", file);
        return false;
    }

    SDL_RWops *f = SDL_RWFromFile(file, ascii ? "a" : "ab");
    if (!f) {
        rhc_error = "file append failed";
        log_warn("rhc_file_append failed: %s", file);
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
        log_error("rhc_file_append failed: %s %d/%d bytes written", file, chars_written, content.size);
        return false;
    }
    return true;
}


#else
// unix file implementation

typedef struct {
    FILE *file;
} UnixFile;
_Static_assert(sizeof (UnixFile) <= RHC_FILE_STORAGE_SIZE, "storage not big enough");

static size_t file_stream_read(Stream_i stream, void *msg, size_t size) {
    RhcFile *self = stream.user_data;
    if(!rhc_file_valid(self))
        return 0;

    UnixFile *impl = (UnixFile*) self->impl_storage;

    size_t n = fread(msg, 1, size, impl->file);
    if(n <= 0) {
        log_error("rhc_file_read failed, killing file...");
        fclose(impl->file);
        impl->file = NULL;
        return 0;
    }
    assert(n <= size);
    return (size_t) n;
}

static size_t file_stream_write(Stream_i stream, const void *msg, size_t size) {
    RhcFile *self = stream.user_data;
    if(!rhc_file_valid(self))
        return 0;

    UnixFile *impl = (UnixFile*) self->impl_storage;

    size_t n = fwrite(msg, 1, size, impl->file);
    if(n <= 0) {
        log_error("rhc_file_write failed, killing file...");
        fclose(impl->file);
        impl->file = NULL;
        return 0;
    }
    assert(n <= size);
    return (size_t) n;
}

bool rhc_file_valid(const RhcFile *self) {
    if(!self)
        return false;
    UnixFile *impl = (UnixFile*) self->impl_storage;
    return impl->file;
}

RhcFile *rhc_file_open_read_a(const char *file, bool ascii, Allocator_i a) {
    RhcFile *self = a.calloc(a, sizeof *self);
    UnixFile *impl = (UnixFile*) self->impl_storage;
    self->stream = (Stream_i) {self, file_stream_read, NULL};
    self->allocator = a;
    impl->file = fopen(file, ascii ? "r" : "rb");
    if (!impl->file) {
        rhc_error = "rhc_file_open_read_a failed";
        log_warn("rhc_file_open_read_a failed: %s", file);
        a.free(a, self);
        return NULL;
    }
    return self;
}
RhcFile *rhc_file_open_write_a(const char *file, bool ascii, Allocator_i a) {
    RhcFile *self = a.calloc(a, sizeof *self);
    UnixFile *impl = (UnixFile*) self->impl_storage;
    self->stream = (Stream_i) {self, NULL, file_stream_write};
    self->allocator = a;
    impl->file = fopen(file, ascii ? "w" : "wb");
    if (!impl->file) {
        rhc_error = "rhc_file_open_write_a failed";
        log_warn("rhc_file_open_write_a failed: %s", file);
        a.free(a, self);
        return NULL;
    }
    return self;
}
RhcFile *rhc_file_open_append_a(const char *file, bool ascii, Allocator_i a) {
    RhcFile *self = a.calloc(a, sizeof *self);
    UnixFile *impl = (UnixFile*) self->impl_storage;
    self->stream = (Stream_i) {self, NULL, file_stream_write};
    self->allocator = a;
    impl->file = fopen(file, ascii ? "a" : "ab");
    if (!impl->file) {
        rhc_error = "rhc_file_open_append_a failed";
        log_warn("rhc_file_open_append_a failed: %s", file);
        a.free(a, self);
        return NULL;
    }
    return self;
}

void rhc_file_kill(RhcFile **self_ptr) {
    RhcFile *self = *self_ptr;
    if(!self)
        return;
    UnixFile *impl = (UnixFile*) self->impl_storage;
    fclose(impl->file);
    self->allocator.free(self->allocator, self);
    *self_ptr = NULL;
}

String rhc_file_read_a(const char *file, bool ascii, Allocator_i a) {
    if(!allocator_valid(a)) {
        rhc_error = "file read failed, allocator invalid";
        log_error("rhc_file_read_a failed, allocator invalid: %s", file);
        return string_new_invalid_a(a);
    }

    FILE *f = fopen(file, ascii ? "r" : "rb");
    if (!f) {
        rhc_error = "file read failed";
        log_warn("rhc_file_read_a failed: %s", file);
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
        //  CRLF will be converted to LF on windows in ascii and will be a byte smaller
        if (!ascii && res.size != length) {
            log_error("rhc_file_read_a failed: %s %d/%d bytes read", file, res.size, length);
            string_kill(&res);
        } else {
            res.data[length] = '\0';  // should have been set in String, just to be sure
        }
    }
    fclose(f);
    return res;
}

bool rhc_file_write(const char *file, Str_s content, bool ascii) {
    if(!str_valid(content)) {
        rhc_error = "file write failed, content invalid";
        log_error("rhc_file_write failed, content invalid: %s", file);
        return false;
    }

    FILE *f = fopen(file, ascii ? "w" : "wb");
    if (!f) {
        rhc_error = "file write failed";
        log_warn("rhc_file_write failed: %s", file);
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
        log_error("rhc_file_write failed: %s %d/%d bytes written", file, chars_written, content.size);
        return false;
    }
    return true;
}

bool rhc_file_append(const char *file, Str_s content, bool ascii) {
    if(!str_valid(content)) {
        rhc_error = "file append failed, content invalid";
        log_error("rhc_file_append failed, content invalid: %s", file);
        return false;
    }

    FILE *f = fopen(file, ascii ? "a" : "ab");
    if (!f) {
        rhc_error = "file append failed";
        log_warn("rhc_file_append failed: %s", file);
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
        log_error("rhc_file_append failed: %s %d/%d bytes written", file, chars_written, content.size);
        return false;
    }
    return true;
}
#endif



#endif //RHC_IMPL
#endif //RHC_FILE_IMPL_H
