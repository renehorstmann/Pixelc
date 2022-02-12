#ifndef RHC_ALLOCATOR_H
#define RHC_ALLOCATOR_H

#include <string.h> // memset
#include "types.h"

//
// Options
//
#ifndef RHC_DEFAULT_ALLOCATOR
#define RHC_DEFAULT_ALLOCATOR allocator_new()
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
Allocator_i allocator_new_try();

// uses rhc_malloc_raising, rhc_realloc_raising, rhc_free
Allocator_i allocator_new();

// does nothing, but is valid
// malloc, realloc will return NULL
Allocator_i allocator_new_empty_try();

// will always raise a signal, but is valid
// if the signal is catched and ignored, NULL is returned
Allocator_i allocator_new_empty();

// An arena a allocates everythin on the a fixed stack
// If realloc is called, the new object is either copied to the end,
//      or if it was the last element, its size is just updates
// the arena can be cleared with allocator_arena_clear to free all allocations
// the arena must also be killed with allocator_arena_kill (which will also free all allocations)
// Stack a version
Allocator_i allocator_arena_new_a(size_t arena_size, Allocator_i arena_stack_allocator);

// An arena a allocates everythin on the a fixed stack
// If realloc is called, the new object is either copied to the end,
//      or if it was the last element, its size is just updates
// the arena can be cleared with allocator_arena_clear to free all allocations
// the arena must also be killed with allocator_arena_kill (which will also free all allocations)
static Allocator_i allocator_arena_new(size_t arena_size) {
    return allocator_arena_new_a(arena_size, RHC_DEFAULT_ALLOCATOR);
}

void allocator_arena_kill(Allocator_i *self_arena);

// clears / frees all allocations
void allocator_arena_clear(Allocator_i self_arena);

// returns the size the arena was created with
size_t allocator_arena_full_size(Allocator_i self_arena);

// returns the current remaining size of the arena
size_t allocator_arena_remaining_size(Allocator_i self_arena);


// allocates empty memory from the a
static void *allocator_malloc(Allocator_i self, size_t size) {
    return self.realloc(NULL, size, self.user_data);
}

// allocates zero set memory from the a
static void *allocator_calloc(Allocator_i self, size_t size) {
    void *data = self.realloc(NULL, size, self.user_data);
    memset(data, 0, size);
    return data;
}

// reallocates memory from the a
static void *allocator_realloc(Allocator_i self, void *memory, size_t size) {
    return self.realloc(memory, size, self.user_data);
}

// frees memory from the a
static void allocator_free(Allocator_i self, void *memory) {
    self.realloc(memory, 0, self.user_data);
}


#endif //RHC_ALLOCATOR_H
