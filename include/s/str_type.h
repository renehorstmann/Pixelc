#ifndef S_STR_TYPE_H
#define S_STR_TYPE_H

//
// Just the struct type for Str and StrArray
//

#include "allocator.h"

typedef struct sStr_s {
    char *data;
    ssize size;
} sStr_s;

// array of sStr_s, allocated
typedef struct sStrArray {
    sStr_s *array;
    ssize size;

    sAllocator_i allocator;
} sStrArray;


//
// class functions
//


// returns true if the str is valid
// a valid str has a data ptr, but may have a size==0
static bool s_str_valid(sStr_s str) {
    return str.data && str.size>=0;
}

// returns true if str array is valid
static bool s_strarray_valid(sStrArray self) {
    return self.array != NULL && s_allocator_valid(self.allocator);
}

// kills the str array
static void s_strarray_kill(sStrArray *self) {
    if (s_strarray_valid(*self))
        s_a_free(self->allocator, self->array);
    self->array = NULL;
    self->size = 0;
}

// creates an invalid str
static sStr_s s_str_new_invalid() {
    return (sStr_s) {NULL, 0};
}

#endif //S_STR_TYPE_H
