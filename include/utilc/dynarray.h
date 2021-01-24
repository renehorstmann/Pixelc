#ifndef UTILC_DYNARRAY_H
#define UTILC_DYNARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#ifndef DYN_ARRAY_SIGNAL
#define DYN_ARRAY_SIGNAL SIGABRT
#endif

#define DYN_ARRAY_INIT {0}

/**
 * Creates an dynamic array of type (type) with the typename class_name.
 * If an allocation error occurs, the signal DYN_ARRAY_SIGNAL (default = SIGABRT) is raised.
 * Construct it as empty struct ( = {};, or calloc).
 * Kill it with <fn_name>_kill;
 * <fn_name>_set_capacity sets the internal capacity. If realloc fails, nothing changes.
 * <fn_name>_resize sets the array size and may set capacity with size*2.
 * <fn_name>_push copies an item to the end of the array (copies to the last element).
 * <fn_name>_append creates an item at the end and returns its pointer (returns the last element).
 * <fn_name>_pop returns a copy of the last item and removes it from the array.
 */
#define DynArray(type, class_name, fn_name) \
typedef struct { \
    type *array; \
    int capacity; \
    int size; \
} class_name; \
static void fn_name ## _kill(class_name *self) { \
    free(self->array); \
    self->array = NULL; \
    self->capacity = 0; \
    self->size = 0; \
} \
static void fn_name ## _set_capacity(class_name *self, int capacity) { \
    type *new_array = (type *) realloc(self->array, capacity * sizeof(type)); \
    if (!new_array) { \
        fprintf(stderr, #fn_name "_set_capacity failed with capacity: %d\n", capacity); \
        raise(DYN_ARRAY_SIGNAL); \
    } \
    self->array = new_array; \
    self->capacity = capacity; \
    if (self->size > capacity) \
    self->size = capacity; \
} \
static void fn_name ## _resize(class_name *self, int size) { \
    if (size > self->capacity) \
        fn_name ## _set_capacity(self, size * 2); \
    self->size = size; \
} \
static void fn_name ## _push(class_name *self, type item) { \
    fn_name ## _resize(self, self->size+1); \
    self->array[self->size-1] = item; \
} \
static void fn_name ## _push_array(class_name *self, const type *item_array, int n) { \
    fn_name ## _resize(self, self->size+n); \
    for(int i=0; i<n; i++)\
        self->array[self->size-n+i] = item_array[i]; \
} \
static type *fn_name ## _append(class_name *self) { \
    fn_name ## _resize(self, self->size+1); \
    return &self->array[self->size-1]; \
} \
static type fn_name ## _pop(class_name *self) { \
    if(self->size > 0) \
        return self->array[--self->size]; \
    return (type) {0}; \
}

/**
 * Creates an dynamic array of type (type) with the typename class_name.
 * Construct it as empty struct ( = {};, or calloc).
 * Kill it with <fn_name>_kill;
 * <fn_name>_set_capacity sets the internal capacity. If realloc fails, nothing changes.
 * <fn_name>_resize sets the array size and may set capacity with size*2.
 * <fn_name>_push copies an item to the end of the array (copies to the last element).
 * <fn_name>_append creates an item at the end and returns its pointer (returns the last element).
 * <fn_name>_pop returns a copy of the last item and removes it from the array.
 */
#define DynArrayTry(type, class_name, fn_name) \
typedef struct { \
    type *array; \
    int capacity; \
    int size; \
} class_name; \
static void fn_name ## _kill(class_name *self) { \
    free(self->array); \
    self->array = NULL; \
    self->capacity = 0; \
    self->size = 0; \
} \
static void fn_name ## _set_capacity(class_name *self, int capacity) { \
    type *new_array = (type *) realloc(self->array, capacity * sizeof(type)); \
    if (new_array) { \
        self->array = new_array; \
        self->capacity = capacity; \
        if (self->size > capacity) \
            self->size = capacity; \
    } \
} \
static void fn_name ## _resize(class_name *self, int size) { \
    if (size > self->capacity) { \
        fn_name ## _set_capacity(self, size * 2); \
        if(size>self->capacity) \
            /* alloc error */ \
            return;\
    } \
    self->size = size; \
} \
static void fn_name ## _push(class_name *self, type item) { \
    fn_name ## _resize(self, self->size+1); \
    self->array[self->size-1] = item; \
} \
static void fn_name ## _push_array(class_name *self, const type *item_array, int n) { \
    fn_name ## _resize(self, self->size+n); \
    for(int i=0; i<n; i++)\
        self->array[self->size-n+i] = item_array[i]; \
} \
static type *fn_name ## _append(class_name *self) { \
    fn_name ## _resize(self, self->size+1); \
    return &self->array[self->size-1]; \
} \
static type fn_name ## _pop(class_name *self) { \
    if(self->size > 0) \
        return self->array[--self->size]; \
    return (type) {0}; \
}




/**
 * Creates an dynamic array of type (type) with the typename class_name.
 * This version dont uses copies (push and pop). For use with array types like int[2].
 * If an allocation error occurs, the signal DYN_ARRAY_SIGNAL (default = SIGABRT) is raised.
 *
 * Construct it as empty struct ( = {};, or calloc).
 * Kill it with <fn_name>_kill;
 * <fn_name>_set_capacity sets the internal capacity. If realloc fails, nothing changes.
 * <fn_name>_resize sets the array size and may set capacity with size*2.
 * <fn_name>_append creates an item at the end and returns its pointer (returns the last element).
 */
#define DynArrayWithoutCopy(type, class_name, fn_name) \
typedef struct { \
    type *array; \
    int capacity; \
    int size; \
} class_name; \
static void fn_name ## _kill(class_name *self) { \
    free(self->array); \
    self->array = NULL; \
    self->capacity = 0; \
    self->size = 0; \
} \
static void fn_name ## _set_capacity(class_name *self, int capacity) { \
    type *new_array = (type *) realloc(self->array, capacity * sizeof(type)); \
    if (!new_array) { \
        fprintf(stderr, #fn_name "_set_capacity failed with capacity: %d\n", capacity); \
        raise(DYN_ARRAY_SIGNAL); \
    } \
    self->array = new_array; \
    self->capacity = capacity; \
    if (self->size > capacity) \
    self->size = capacity; \
} \
static void fn_name ## _resize(class_name *self, int size) { \
    if (size > self->capacity) \
        fn_name ## _set_capacity(self, size * 2); \
    self->size = size; \
} \
static type *fn_name ## _append(class_name *self) { \
    fn_name ## _resize(self, self->size+1); \
    return &self->array[self->size-1]; \
}

/**
 * Creates an dynamic array of type (type) with the typename class_name.
 * This version dont uses copies (push and pop). For use with array types like int[2].
 *
 * Construct it as empty struct ( = {};, or calloc).
 * Kill it with <fn_name>_kill;
 * <fn_name>_set_capacity sets the internal capacity. If realloc fails, nothing changes.
 * <fn_name>_resize sets the array size and may set capacity with size*2.
 * <fn_name>_append creates an item at the end and returns its pointer (returns the last element).
 */
#define DynArrayTryWithoutCopy(type, class_name, fn_name) \
typedef struct { \
    type *array; \
    int capacity; \
    int size; \
} class_name; \
static void fn_name ## _kill(class_name *self) { \
    free(self->array); \
    self->array = NULL; \
    self->capacity = 0; \
    self->size = 0; \
} \
static void fn_name ## _set_capacity(class_name *self, int capacity) { \
    type *new_array = (type *) realloc(self->array, capacity * sizeof(type)); \
    if (new_array) { \
        self->array = new_array; \
        self->capacity = capacity; \
        if (self->size > capacity) \
            self->size = capacity; \
    } \
} \
static void fn_name ## _resize(class_name *self, int size) { \
    if (size > self->capacity) { \
        fn_name ## _set_capacity(self, size * 2); \
        if(size>self->capacity) \
            /* alloc error */ \
            return;\
    } \
    self->size = size; \
} \
static type *fn_name ## _append(class_name *self) { \
    fn_name ## _resize(self, self->size+1); \
    return &self->array[self->size-1]; \
}

#endif //UTILC_DYNARRAY_H

