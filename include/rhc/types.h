#ifndef RHC_TYPES_H
#define RHC_TYPES_H

#include <stdbool.h>
#include <stddef.h>



//
// Types
//

// virtual allocator interface, see alloc.h
typedef struct Allocator_i {
    void *user_data;

    // virtual functions
    void *(*malloc)(struct Allocator_i self, size_t size);
    void *(*calloc)(struct Allocator_i self, size_t size);
    void *(*realloc)(struct Allocator_i self, void *memory, size_t size);
    void (*free)(struct Allocator_i self, void *memory);
} Allocator_i;

// virtual stream interface, see stream.h
// stream.h also contains more useful functions, like stream_read/write_msg
typedef struct Stream_i {
    void *user_data;
    
    // virtual functions
    
    // reads up to n bytes from the stream into memory
    // returns bytes read or 0 on error
    // optional, function may be NULL
    size_t (*opt_read)(struct Stream_i self, void *memory, size_t n);
    
    // writes up to n bytes into the stream from memory
    // returns bytes written or 0 on error
    // optional, function may be NULL
    size_t (*opt_write)(struct Stream_i self, const void *memory, size_t n);
} Stream_i;

// string view, data is not null terminated
typedef struct {
    char *data;
    size_t size;
} Str_s;

// array of Str_s, allocated
typedef struct {
    Str_s *array;
    size_t size;

    Allocator_i allocator;
} StrArray;

// dynamic Str_s + always null terminated
typedef struct {
    // Str_s
    union {
        Str_s str;
        struct {
            char *data;
            size_t size;
        };
    };

    // buf
    size_t capacity;
    Allocator_i allocator;
} String;


//
// Autotype / struct  functions
//


// returns true if the allocator seems to be valid
static bool allocator_valid(Allocator_i a) {
    return a.malloc && a.realloc && a.free;  // vfunctions available?
}

static bool stream_valid(Stream_i s) {
    return s.opt_read || s.opt_write;
}

static Stream_i stream_new_invalid() {
    return (Stream_i) {0};
}

// returns true if str is valid
static bool str_valid(Str_s s) {
    return s.data != NULL;
}



//
// Class functions / methods
//

// returns true if str array is valid
static bool strarray_valid(StrArray self) {
    return self.array != NULL && allocator_valid(self.allocator);
}

// kills the str array
static void strarray_kill(StrArray *self) {
    if(strarray_valid(*self))
        self->allocator.free(self->allocator, self->array);
    self->array = NULL;
    self->size = 0;
}

// returns true if the string is valid
static bool string_valid(String self) {
    return str_valid(self.str) && allocator_valid(self.allocator);
}

// kills the string
static void string_kill(String *self) {
    if(string_valid(*self))
        self->allocator.free(self->allocator, self->data);
    self->data = NULL;
    self->size = 0;
    self->capacity = 0;
}

#endif //RHC_TYPES_H
