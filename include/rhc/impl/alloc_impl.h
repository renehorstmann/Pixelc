#ifndef RHC_ALLOC_IMPL_H
#define RHC_ALLOC_IMPL_H

#include <stdlib.h>
#include <string.h>
#include "../error.h"
#include "../log.h"
#include "../alloc.h"

#ifdef OPTION_SDL
#include <SDL2/SDL.h>
#endif

void *rhc_malloc_try(size_t size) {
#ifdef OPTION_SDL
    void *data = SDL_malloc(size);
#else
    void *data = malloc(size);
#endif
    if(!data) {
        log_error("allocation failed for a size of: %zu", size);
        rhc_error = "allocation error";
    }
    return data;
}

void *rhc_calloc_try(size_t size) {
    void *data = rhc_malloc_try(size);
    memset(data, 0, size);
    return data;
}

void *rhc_realloc_try(void *memory, size_t size) {
#ifdef OPTION_SDL
    void *data = SDL_realloc(memory, size);
#else
    void *data = realloc(memory, size);
#endif
    if(!data) {
        log_error("reallocation failed for a size of: %zu", size);
        rhc_error = "allocation error";
        return memory;
    }
    return data;
}


void rhc_free(void *memory) {
#ifdef OPTION_SDL
    SDL_free(memory);
#else
    free(memory);
#endif
}


void *rhc_malloc(size_t size) {
#ifdef OPTION_SDL
    void *data = SDL_malloc(size);
#else
    void *data = malloc(size);
#endif
    assume(data, "allocation failed for a size of: %zu", size);
    return data;
}

void *rhc_calloc(size_t size) {
    void *data = rhc_malloc(size);
    memset(data, 0, size);
    return data;
}

void *rhc_realloc(void *memory, size_t size) {
    // a call to realloc with size=0 should normale free the object, but the sanitizer is angry then
    if(size==0) {
        rhc_free(memory);
        return NULL;
    }
#ifdef OPTION_SDL
    void *data = SDL_realloc(memory, size);
#else
    void *data = realloc(memory, size);
#endif
    assume(data, "reallocation failed for a size of: %zu", size);
    return data;
}

static void *rhc_allocator_try_realloc_impl_(void *memory, size_t size, void *ud) {
    return rhc_realloc_try(memory, size);
}

static void *rhc_allocator_realloc_impl_(void *memory, size_t size, void *ud) {
    return rhc_realloc(memory, size);
}

static void *rhc_allocator_empty_try_realloc_impl_(void *memory, size_t size, void *ud) {
    return NULL;
}
static void *rhc_allocator_empty_realloc_impl_(void *memory, size_t size, void *ud) {
    assume(false, "a empty raising realloc called");
    return NULL;
}



Allocator_i allocator_new_try() {
    return (Allocator_i) {
            NULL,
            rhc_allocator_try_realloc_impl_
    };
}


Allocator_i allocator_new() {
    return (Allocator_i) {
            NULL,
            rhc_allocator_realloc_impl_
    };
}

Allocator_i allocator_new_empty_try() {
    return (Allocator_i) {
            NULL,
            rhc_allocator_empty_try_realloc_impl_
    };
}

Allocator_i allocator_new_empty() {
    return (Allocator_i) {
            NULL,
            rhc_allocator_empty_realloc_impl_
    };
}


struct RhcArena {
    Allocator_i a;

    size_t stack_size;
    size_t used;
    uint8_t *last_allocation;

    // empty last array -> arena is located behind RhcArena struct in memory
    uint8_t stack[];
};

void *rhc_allocator_arena_realloc_impl(void *memory, size_t size, void *user_data) {
    struct RhcArena *self = user_data;

    // free
    if(size == 0) {
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
            size_t new_used = self->last_allocation - self->stack + size;
            if(new_used > self->stack_size)
                return NULL;
            self->used = new_used;
            return self->last_allocation;
        }

        // fall to malloc
    }

    // malloc
    if(self->used + size > self->stack_size) {
        return NULL;
    }
    self->last_allocation = self->stack + self->used;
    self->used += size;
    return self->last_allocation;
}

Allocator_i allocator_arena_new_a(size_t arena_size, Allocator_i arena_stack_allocator) {
    struct RhcArena *self = allocator_calloc(arena_stack_allocator, sizeof*self + arena_size);
    self->a = arena_stack_allocator;
    self->stack_size = arena_size;

    return (Allocator_i) {
            .user_data = self,
            .realloc = rhc_allocator_arena_realloc_impl
    };
}

void allocator_arena_kill(Allocator_i *self_arena) {
    struct RhcArena *self = self_arena->user_data;
    allocator_free(self->a, self);
    *self_arena = allocator_new_invalid();
}

// clears / frees all allocations
void allocator_arena_clear(Allocator_i self_arena) {
    struct RhcArena *self = self_arena.user_data;
    self->used = 0;
    self->last_allocation = NULL;
}

// returns the size the arena was created with
size_t allocator_arena_full_size(Allocator_i self_arena) {
    struct RhcArena *self = self_arena.user_data;
    return self->stack_size;
}

// returns the current remaining size of the arena
size_t allocator_arena_remaining_size(Allocator_i self_arena) {
    struct RhcArena *self = self_arena.user_data;
    return self->stack_size-self->used;
}

#endif //RHC_ALLOC_IMPL_H
