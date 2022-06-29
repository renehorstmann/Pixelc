#ifndef S_STRING_H
#define S_STRING_H

//
// Dynamic string that may grow
//      Can be used as a stream (see stream.h)
// When a function returns a string, you have to kill it
//

#include "str_type.h"
#include "stream.h"

//
// Class
//

typedef struct sString {
    // sStr_s
    char *data;
    ssize size;

    // buf
    ssize capacity;
    sAllocator_i allocator;

    // read and write the string with a stream
    sStream_i stream;
    ssize stream_pos;
} sString;

//
// Functions
//

static bool s_string_valid(const sString *self) {
    return self
           && self->data && self->size>=0
           && self->capacity > 0
           && s_allocator_valid(self->allocator)
           && self->stream_pos >= 0 && self->stream_pos <= self->size;
}

static sString *s_string_new_invalid() {
    return NULL;
}

// returns a Str from the data
static sStr_s s_string_get_str(sString *self) {
    if(!s_string_valid(self))
        return s_str_new_invalid();
    return (sStr_s) {self->data, self->size};
}

// safe way to get the stream from the string
static sStream_i s_string_get_stream(sString *self) {
    if(!self)
        return s_stream_new_invalid();
    return self->stream;
}


// allocated start_capacity + 1 (null)
// start_capacity will be set to a minimum of 7
sString *s_string_new_a(ssize start_capacity, sAllocator_i a);

// allocated start_capacity + 1 (null)
static sString *s_string_new(ssize start_capacity) {
    return s_string_new_a(start_capacity, S_ALLOCATOR_DEFAULT);
}

// clones sStr_s and appends null
sString *s_string_new_clone_a(sStr_s to_clone, sAllocator_i a);


// clones sStr_s and appends null
static sString *s_string_new_clone(sStr_s to_clone) {
    return s_string_new_clone_a(to_clone, S_ALLOCATOR_DEFAULT);
}

// copies str s into a new string, with old -> replacement.
sString *s_string_new_replace_a(sStr_s to_replace, sStr_s old, sStr_s replacement, sAllocator_i a);


// copies str s into a new string, with old -> replacement.
static sString *s_string_new_replace(sStr_s to_replace, sStr_s old, sStr_s replacement) {
    return s_string_new_replace_a(to_replace, old, replacement, S_ALLOCATOR_DEFAULT);
}

// concatenates all strs
sString *s_string_new_cat_a(sStr_s *strs, int n, sAllocator_i a);

// concatenates all strs
static sString *s_string_new_cat(sStr_s *strs, int n) {
    return s_string_new_cat_a(strs, n, S_ALLOCATOR_DEFAULT);
}

void s_string_kill(sString **self_ptr);

// size is the sum of characters, not including termination null (as strlen)
void s_string_set_capacity(sString *self, ssize capacity);

// size is the sum of characters, not including termination null (as strlen)
void s_string_resize(sString *self, ssize size);

// appends a char
void s_string_push(sString *self, char push);

// appends a string
void s_string_append(sString *self, sStr_s append);

#endif //S_STRING_H
