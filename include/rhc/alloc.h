#ifndef RHC_ALLOCATOR_H
#define RHC_ALLOCATOR_H

#include "types.h"

//
// Options
//
#ifndef RHC_DEFAULT_ALLOCATOR
#define RHC_DEFAULT_ALLOCATOR rhc_allocator_new()
#endif

//
// Functions
//

// malloc
void *rhc_malloc_try(size_t size);

// calloc
void *rhc_calloc_try(size_t size);

// realloc
void *rhc_realloc_try(void *memory, size_t size);

// free
void rhc_free(void *memory);

// malloc + assume
void *rhc_malloc(size_t size);

// calloc + assume
void *rhc_calloc(size_t size);

// realloc + assume
void *rhc_realloc(void *memory, size_t size);


// uses rhc_malloc, rhc_realloc, rhc_free
Allocator_i rhc_allocator_new_try();

// uses rhc_malloc_raising, rhc_realloc_raising, rhc_free
Allocator_i rhc_allocator_new();

// does nothing, but is valid
// malloc, realloc will return NULL
Allocator_i rhc_allocator_new_empty_try();

// will always raise a signal, but is valid
// if the signal is catched and ignored, NULL is returned
Allocator_i rhc_allocator_new_empty();


#endif //RHC_ALLOCATOR_H
