#ifndef S_ALLOCATOR_H
#define S_ALLOCATOR_H

//
// This module contains a second namespace apart from allocator
//      allocator methods just use 'a' as namespace as s_a_malloc
//          so s_a_new (calls malloc on the allocator) does not collide with s_allocator_new (constructor)
//      The postfix *_a is also just for functions taking an allocator...
//

#include "memory.h"

//
// Options
//

#ifndef S_ALLOCATOR_DEFAULT
#define S_ALLOCATOR_DEFAULT s_allocator_new()
#endif

//
// Interface
//

struct sAllocator_i;

typedef void *(*s_allocator_realloc_fn)(struct sAllocator_i allocator, void *memory, ssize n);

typedef struct sAllocator_i {
    void *impl;

    // vtable
    // if memory is NULL -> malloc
    // if ssize is NULL -> free
    // should be ok to pass NULL, 0, *
    s_allocator_realloc_fn realloc;
} sAllocator_i;

//
// Functions
//

static bool s_allocator_valid(sAllocator_i self) {
    return self.realloc != NULL;
}

static sAllocator_i s_allocator_new_invalid() {
    return (sAllocator_i) {0};
}

// interface function for s_allocator_new_try
static void *s__allocator_new_try_realloc(sAllocator_i allocator, void *memory, ssize n) {
    return s_realloc_try(memory, n);
}

// interface function for s_allocator_new_try
static void *s__allocator_new_realloc(sAllocator_i allocator, void *memory, ssize n) {
    return s_realloc(memory, n);
}

// uses realloc_try
static sAllocator_i s_allocator_new_try() {
    return (sAllocator_i) {.realloc = s__allocator_new_try_realloc};
}

// uses realloc
static sAllocator_i s_allocator_new() {
    return (sAllocator_i) {.realloc = s__allocator_new_realloc};
}

//
// FUnctions (with smaller name to not callide with s_allocator_new)
//

// realloc
static void *s_a_realloc_try(sAllocator_i self, void *memory, ssize n) {
    return self.realloc(self, memory, n);
}

// malloc
static void *s_a_malloc_try(sAllocator_i self, ssize n) {
    return s_a_realloc_try(self, NULL, n);
}

// calloc
static void *s_a_malloc0_try(sAllocator_i self, ssize n) {
    void *mem = s_a_malloc_try(self, n);
    if(!mem)
        return NULL;
    memset(mem, 0, n);
    return mem;
}

// free
static void s_a_free(sAllocator_i self, void *memory) {
    s_a_realloc_try(self, memory, 0);
}

// malloc + s_assume
static void *s_a_malloc(sAllocator_i self, ssize n) {
    s_assume(n > 0, "at least 1 byte (could also be an overflow)");
    void *mem = s_a_malloc_try(self, n);
    s_assume(mem, "s_a_malloc failed");
    return mem;
}

// calloc + s_assume
static void *s_a_malloc0(sAllocator_i self, ssize n) {
    s_assume(n > 0, "at least 1 byte (could also be an overflow)");
    void *mem = s_a_malloc0_try(self, n);
    s_assume(mem, "s_a_malloc0 failed");
    return mem;
}

// realloc + s_assume
static void *s_a_realloc(sAllocator_i self, void *memory, ssize n) {
    s_assume(n >= 0, "overflow?");
    void *mem = s_a_realloc_try(self, memory, n);
    s_assume(mem, "s_a_realloc failed");
    return mem;
}


//
// Macro functions (with smaller name to not callide with s_allocator_new)
//

// calls allocator_free and sets the pointer to NULL
#define s_a_clear(self, mem) \
do { \
    a_free((self), (mem)); \
    (mem) = NULL; \
} while(0)

// calls s_a_malloc with the ssize of the struct
#define s_a_new(self, struct_type, n_structs) \
        ((struct_type *) s_a_malloc ((self), (n_structs) * sizeof (struct_type)))

// calls s_a_malloc0 with the ssize of the struct
#define s_a_new0(self, struct_type, n_structs) \
        ((struct_type *) s_a_malloc0 ((self), (n_structs) * sizeof (struct_type)))

// calls s_a_realloc with the ssize of the struct
#define s_a_renew(self, struct_type, mem, n_structs) \
        ((struct_type *) s_a_realloc ((self), mem, (n_structs) * sizeof (struct_type)))

// calls s_a_malloc_try with the ssize of the struct
#define s_a_try_new(self, struct_type, n_structs) \
        ((struct_type *) s_a_malloc_try ((self), (n_structs) * sizeof (struct_type)))

// calls s_a_malloc0_try with the ssize of the struct
#define s_a_try_new0(self, struct_type, n_structs) \
        ((struct_type *) s_a_malloc0_try ((self), (n_structs) * sizeof (struct_type)))

// calls s_a_realloc_try with the ssize of the struct
#define s_a_try_renew(self, struct_type, mem, n_structs) \
        ((struct_type *) s_a_realloc_try ((self), mem, (n_structs) * sizeof (struct_type)))
        
        
//
// AllocatorArena
//

// An arena allocates everything on a fixed stack
// If realloc is called, the new object is either copied to the end,
//      or if it was the last element, its ssize is just updates
// the arena can be cleared with s_allocator_arena_clear to free all allocations
// the arena must also be killed with s_allocator_arena_kill (which will also free all allocations)
// Stack a version
sAllocator_i s_allocator_arena_new_a(ssize arena_size, sAllocator_i arena_stack_allocator);

// An arena allocates everything on a fixed stack
// If realloc is called, the new object is either copied to the end,
//      or if it was the last element, its ssize is just updates
// the arena can be cleared with s_allocator_arena_clear to free all allocations
// the arena must also be killed with s_allocator_arena_kill (which will also free all allocations)
static sAllocator_i s_allocator_arena_new(ssize arena_size) {
    return s_allocator_arena_new_a(arena_size, S_ALLOCATOR_DEFAULT);
}

void s_allocator_arena_kill(sAllocator_i *self_arena);

// clears / frees all allocations
void s_allocator_arena_clear(sAllocator_i self_arena);

// returns the ssize the arena was created with
ssize s_allocator_arena_full_size(sAllocator_i self_arena);

// returns the current remaining ssize of the arena
ssize s_allocator_arena_remaining_size(sAllocator_i self_arena);


#endif //S_ALLOCATOR_H
