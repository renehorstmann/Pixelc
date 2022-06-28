#ifndef S_ALLOCATOR_IMPL_H
#define S_ALLOCATOR_IMPL_H
#ifdef S_IMPL

#include "../allocator.h"

//
// AllocatorArena
//

struct s__Arena {
    sAllocator_i a;

    ssize stack_size;
    ssize used;
    su8 *last_allocation;

    // empty last array -> arena is located behind s__Arena struct in memory
    su8 stack[];
};

static void *s__allocator_arena_realloc_impl(sAllocator_i allocator, void *memory, ssize n) {
    struct s__Arena *self = allocator.impl;

    // free
    if(n == 0) {
        if(!memory)
            return NULL;
        // only possible if it was the last allocation
        if(self->last_allocation == memory) {
            self->used = self->last_allocation - self->stack;
            self->last_allocation = NULL;
        }
        return NULL;
    }

    // realloc
    if(memory) {
        // actual realloc
        if(self->last_allocation == memory) {
            ssize new_used = self->last_allocation - self->stack + n;
            if(new_used > self->stack_size)
                return NULL;
            self->used = new_used;
            return self->last_allocation;
        }

        // fall to malloc
    }

    // malloc
    if(self->used + n > self->stack_size) {
        return NULL;
    }
    self->last_allocation = self->stack + self->used;
    self->used += n;
    return self->last_allocation;
}

sAllocator_i s_allocator_arena_new_a(ssize arena_size, sAllocator_i arena_stack_allocator) {
    struct s__Arena *self = s_a_malloc0(arena_stack_allocator, sizeof *self + arena_size);
    self->a = arena_stack_allocator;
    self->stack_size = arena_size;

    return (sAllocator_i) {
            .impl = self,
            .realloc = s__allocator_arena_realloc_impl
    };
}

void s_allocator_arena_kill(sAllocator_i *self_arena) {
    struct s__Arena *self = self_arena->impl;
    s_a_free(self->a, self);
    *self_arena = s_allocator_new_invalid();
}

// clears / frees all allocations
void s_allocator_arena_clear(sAllocator_i self_arena) {
    struct s__Arena *self = self_arena.impl;
    self->used = 0;
    self->last_allocation = NULL;
}

// returns the ssize the arena was created with
ssize s_allocator_arena_full_size(sAllocator_i self_arena) {
    struct s__Arena *self = self_arena.impl;
    return self->stack_size;
}

// returns the current remaining ssize of the arena
ssize s_allocator_arena_remaining_size(sAllocator_i self_arena) {
    struct s__Arena *self = self_arena.impl;
    return self->stack_size-self->used;
}


#endif //S_IMPL
#endif //S_ALLOCATOR_IMPL_H
