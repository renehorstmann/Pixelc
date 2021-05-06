#ifndef RHC_ALLOC_IMPL_H
#define RHC_ALLOC_IMPL_H

#include <stdlib.h>
#include "../error.h"
#include "../log.h"
#include "../allocator.h"

#ifdef OPTION_SDL
#include <SDL.h>
#endif

void *rhc_malloc(size_t size) {
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


void *rhc_realloc(void *memory, size_t size) {
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


void *rhc_malloc_raising(size_t size) {
#ifdef OPTION_SDL
    void *data = SDL_malloc(size);
#else
    void *data = malloc(size);
#endif
    assume(data, "allocation failed for a size of: %zu", size);
    return data;
}


void *rhc_realloc_raising(void *memory, size_t size) {
#ifdef OPTION_SDL
    void *data = SDL_realloc(memory, size);
#else
    void *data = realloc(memory, size);
#endif
    assume(data, "reallocation failed for a size of: %zu", size);
    return data;
}


static void *rhc_allocator_default_malloc_impl_(Allocator_s self, size_t size) {
    return rhc_malloc(size);
}

static void *rhc_allocator_default_realloc_impl_(Allocator_s self, void *memory, size_t size) {
    return rhc_realloc(memory, size);
}

static void rhc_allocator_default_free_impl_(Allocator_s self, void *memory) {
    rhc_free(memory);
}

static void *rhc_allocator_raising_malloc_impl_(Allocator_s self, size_t size) {
    return rhc_malloc_raising(size);
}

static void *rhc_allocator_raising_realloc_impl_(Allocator_s self, void *memory, size_t size) {
    return rhc_realloc_raising(memory, size);
}

static void *rhc_allocator_empty_malloc_impl_(Allocator_s self, size_t size) {
    return NULL;
}

static void *rhc_allocator_empty_realloc_impl_(Allocator_s self, void *memory, size_t size) {
    return NULL;
}

static void rhc_allocator_empty_free_impl_(Allocator_s self, void *memory) {
}

static void *rhc_allocator_empty_raising_malloc_impl_(Allocator_s self, size_t size) {
    assume(false, "allocator empty raising malloc called");
    return NULL;
}

static void *rhc_allocator_empty_raising_realloc_impl_(Allocator_s self, void *memory, size_t size) {
    assume(false, "allocator empty raising realloc called");
    return NULL;
}

static void rhc_allocator_empty_raising_free_impl_(Allocator_s self, void *memory) {
    assume(false, "allocator empty raising free called");
}


Allocator_s allocator_new_default() {
    return (Allocator_s) {
        NULL,
        rhc_allocator_default_malloc_impl_,
        rhc_allocator_default_realloc_impl_,
        rhc_allocator_default_free_impl_
    };
}


Allocator_s allocator_new_raising() {
    return (Allocator_s) {
        NULL,
        rhc_allocator_raising_malloc_impl_,
        rhc_allocator_raising_realloc_impl_,
        rhc_allocator_default_free_impl_
    };
}

Allocator_s allocator_new_empty() {
    return (Allocator_s) {
        NULL,
        rhc_allocator_empty_malloc_impl_,
        rhc_allocator_empty_realloc_impl_,
        rhc_allocator_empty_free_impl_,
    };
}

Allocator_s allocator_new_empty_raising() {
    return (Allocator_s) {
        NULL,
        rhc_allocator_empty_raising_malloc_impl_,
        rhc_allocator_empty_raising_realloc_impl_,
        rhc_allocator_empty_raising_free_impl_,
    };
}

#endif //RHC_ALLOC_IMPL_H
