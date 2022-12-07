#ifndef S_FILE_IMPL_H
#define S_FILE_IMPL_H
#ifdef S_IMPL

#include "../error.h"
#include "../file.h"

#ifdef OPTION_SDL
#include <SDL2/SDL.h>
#endif

struct sFile {
#ifdef OPTION_SDL
    SDL_RWops *file;
#else
    FILE *file;
#endif
};


bool s_file_valid(sFile *self) {
    return self && self->file;
}

static void s__file_close(sFile *self) {
    if (!self || !self->file)
        return;
#ifdef OPTION_SDL
    SDL_RWclose(self->file);
#else
    fclose(self->file);
#endif
    self->file = NULL;
}


sFile *s_file_new_read(const char *file, bool ascii) {
    sFile self_stack;
#ifdef OPTION_SDL
    self_stack.file = SDL_RWFromFile(file, ascii ? "r" : "rb");
#else
    self_stack.file = fopen(file, ascii ? "r" : "rb");
#endif
    if (!s_file_valid(&self_stack)) {
        s_error_set("s_file_new_read failed");
        s_log_warn("s_file_new_read failed: %s", file);
        return NULL;
    }
    sFile *self = s_new(sFile, 1);
    *self = self_stack;
    return self;
}

sFile *s_file_new_write(const char *file, bool ascii) {
    sFile self_stack;
#ifdef OPTION_SDL
    self_stack.file = SDL_RWFromFile(file, ascii ? "w" : "wb");
#else
    self_stack.file = fopen(file, ascii ? "w" : "wb");
#endif
    if (!s_file_valid(&self_stack)) {
        s_error_set("s_file_new_write failed");
        s_log_warn("s_file_new_write failed: %s", file);
        return NULL;
    }
    sFile *self = s_new(sFile, 1);
    *self = self_stack;
    return self;
}

sFile *s_file_new_append(const char *file, bool ascii) {
    sFile self_stack;
#ifdef OPTION_SDL
    self_stack.file = SDL_RWFromFile(file, ascii ? "a" : "ab");
#else
    self_stack.file = fopen(file, ascii ? "a" : "ab");
#endif
    if (!s_file_valid(&self_stack)) {
        s_error_set("s_file_new_append failed");
        s_log_warn("s_file_new_append failed: %s", file);
        return NULL;
    }
    sFile *self = s_new(sFile, 1);
    *self = self_stack;
    return self;
}

void s_file_kill(sFile **self_ptr) {
    sFile *self = *self_ptr;
    s__file_close(self);
    s_free(self);
    *self_ptr = NULL;
}

ssize s_file_size(sFile *self) {
    if(!s_file_valid(self))
        return 0;
#ifdef OPTION_SDL
    Sint64 rwsize = SDL_RWsize(self->file);
    if(rwsize <=0) {
        s_error_set("file read failed");
        s_log_warn("s_file_size failed: (unknown size)");
    }

    return (ssize) s_max(rwsize, 0);
#else
    fseek(self->file, 0, SEEK_END);
    ssize length = (ssize) ftell(self->file);
    fseek(self->file, 0, SEEK_SET);
    return s_max(length, 0);
#endif
}

static ssize s__file_stream_read(struct sStream_i *stream, void *memory, ssize n) {
    sFile *self = stream->impl;
    if (!s_file_valid(self)) {
        return 0;
    }
    ssize read;
#ifdef OPTION_SDL
    read = (ssize) SDL_RWread(self->file, memory, 1, n);
#else
    read = (ssize) fread(memory, 1, n, self->file);
#endif
    if (read <= 0) {
        s__file_close(self);
    }
    return read;
}

static ssize s__file_stream_write(struct sStream_i *stream, const void *memory, ssize n) {
    sFile *self = stream->impl;
    if (!s_file_valid(self)) {
        return 0;
    }
    ssize written;
#ifdef OPTION_SDL
    written = (ssize) SDL_RWwrite(self->file, memory, 1, n);
#else
    written = (ssize) fwrite(memory, 1, n, self->file);
#endif
    if (written <= 0) {
        s__file_close(self);
    }
    return written;
}

static void s__file_stream_flush(struct sStream_i *stream) {
    sFile *self = stream->impl;
    if (!s_file_valid(self)) {
        return;
    }
    // sdl not seems to have a flush function
#ifndef OPTION_SDL
    fflush(self->file);
#endif
}

static bool s__file_stream_valid(struct sStream_i *stream) {
    sFile *self = stream->impl;
    return s_file_valid(self);
}


sStream_i s_file_stream(sFile *self) {
    return (sStream_i) {
            .impl = self,
            .opt_read_try = s__file_stream_read,
            .opt_write_try = s__file_stream_write,
            .opt_flush = s__file_stream_flush,
            .valid = s__file_stream_valid};
}


sStream_i s_file_stream_from_cfile(FILE *cfile, bool read, bool write) {
    static sFile f = {0};
#ifdef OPTION_SDL
    f.file = SDL_RWFromFP(cfile, SDL_FALSE);
#else
    f.file = cfile;
#endif
    sStream_i stream = s_file_stream(&f);
    if(!read)
        stream.opt_read_try = NULL;
    if(!write)
        stream.opt_write_try = NULL;
    return stream;
}

sString *s_file_read_a(const char *file, bool ascii, sAllocator_i a) {
    if (!s_allocator_valid(a)) {
        s_error_set("file read failed, allocator invalid");
        s_log_error("s_file_read_a failed, allocator invalid: %s", file);
        return s_string_new_invalid();
    }
    sFile *f = s_file_new_read(file, ascii);

    // will return an empty (allocated) string else
    if(!s_file_valid(f))
        return s_string_new_invalid();

    ssize length = s_file_size(f);
    sString *res = s_string_new_a(length, a);
    res->size = s_stream_read_as_long_as_valid(s_file_stream_in(f), res->data, length);
    s_file_kill(&f);
    return res;
}

bool s_file_write(const char *file, sStr_s content, bool ascii) {
    sFile *f = s_file_new_write(file, ascii);
    ssize s = s_stream_write(s_file_stream_out(f), content.data, content.size);
    s_file_kill(&f);
    return s > 0;
}

bool s_file_append(const char *file, sStr_s content, bool ascii) {
    sFile *f = s_file_new_append(file, ascii);
    ssize s = s_stream_write(s_file_stream_out(f), content.data, content.size);
    s_file_kill(&f);
    return s > 0;
}

#endif //S_IMPL
#endif //S_FILE_IMPL_H
