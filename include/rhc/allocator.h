#ifndef RHC_ALLOCATOR_H
#define RHC_ALLOCATOR_H

#include "types.h"

//
// Options
//
#ifndef RHC_STRING_DEFAULT_ALLOCATOR
#define RHC_STRING_DEFAULT_ALLOCATOR allocator_new_raising()
#endif

#ifndef RHC_DYNARRAY_DEFAULT_ALLOCATOR
#define RHC_DYNARRAY_DEFAULT_ALLOCATOR allocator_new_raising()
#endif

#ifndef RHC_HASHMAP_DEFAULT_ALLOCATOR
#define RHC_HASHMAP_DEFAULT_ALLOCATOR allocator_new_raising()
#endif

//
// Functions
//

// malloc
void *rhc_malloc(size_t size);

// calloc
void *rhc_calloc(size_t size);

// realloc
void *rhc_realloc(void *memory, size_t size);

// free
void rhc_free(void *memory);

// malloc + assume
void *rhc_malloc_raising(size_t size);

// calloc + assume
void *rhc_calloc_raising(size_t size);

// realloc + assume
void *rhc_realloc_raising(void *memory, size_t size);


// uses rhc_malloc, rhc_realloc, rhc_free
Allocator_s allocator_new_default();

// uses rhc_malloc_raising, rhc_realloc_raising, rhc_free
Allocator_s allocator_new_raising();

// does nothing, but is valid
// malloc, realloc will return NULL
Allocator_s allocator_new_empty();

// will always raise a signal, but is valid
// if the signal is catched and ignored, NULL is returned
Allocator_s allocator_new_empty_raising();


#endif //RHC_ALLOCATOR_H
