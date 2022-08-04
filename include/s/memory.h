#ifndef S_MEMORY_H
#define S_MEMORY_H

//
// safe malloc and co
//

#include "common.h"
#include "export.h"
#include "assume.h"

//
// Functions
//

// realloc (see impl/memory_impl.h)
S_EXPORT
void *s_realloc_try(void *memory, ssize n);


// malloc
static void *s_malloc_try(ssize n) {
    return s_realloc_try(NULL, n);
}

// calloc
static void *s_malloc0_try(ssize n) {
    void *mem = s_malloc_try(n);
    if(!mem)
        return NULL;
    memset(mem, 0, n);
    return mem;
}

// free
static void s_free(void *memory) {
    s_realloc_try(memory, 0);
}

// malloc + s_assume
static void *s_malloc(ssize n) {
    s_assume(n > 0, "at least 1 byte (could also be an overflow)");
    void *mem = s_malloc_try(n);
    s_assume(mem, "s_malloc failed");
    return mem;
}

// calloc + s_assume
static void *s_malloc0(ssize n) {
    s_assume(n > 0, "at least 1 byte (could also be an overflow)");
    void *mem = s_malloc0_try(n);
    s_assume(mem, "s_malloc0 failed");
    return mem;
}

// realloc + s_assume
static void *s_realloc(void *memory, ssize n) {
    s_assume(n >= 0, "overflow?");
    void *mem = s_realloc_try(memory, n);
    s_assume(n==0||mem, "s_realloc failed");
    return mem;
}


//
// Macro functions
//

// calls s_free and sets the pointer to NULL
#define s_clear(mem) \
do { \
    s_free((mem)); \
    (mem) = NULL; \
} while(0)

// calls s_malloc with the ssize of the struct
#define s_new(struct_type, n_structs) \
        ((struct_type *) s_malloc ((n_structs) * sizeof (struct_type)))

// calls s_malloc0 with the ssize of the struct
#define s_new0(struct_type, n_structs) \
        ((struct_type *) s_malloc0 ((n_structs) * sizeof (struct_type)))

// calls s_relloc0 with the ssize of the struct
#define s_renew(struct_type, mem, n_structs) \
        ((struct_type *) s_realloc (mem, (n_structs) * sizeof (struct_type)))

// calls s_malloc_try with the ssize of the struct
#define s_new_try(struct_type, n_structs) \
        ((struct_type *) s_malloc_try ((n_structs) * sizeof (struct_type)))

// calls s_malloc0_try with the ssize of the struct
#define s_new0_try(struct_type, n_structs) \
        ((struct_type *) s_malloc0_try ((n_structs) * sizeof (struct_type)))

// calls s_realloc_try with the ssize of the struct
#define s_renew_try(struct_type, mem, n_structs) \
        ((struct_type *) s_realloc_try (mem, (n_structs) * sizeof (struct_type)))
        

#endif //S_MEMORY_H
