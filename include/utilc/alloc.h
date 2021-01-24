#ifndef UTILC_ALLOC_H
#define UTILC_ALLOC_H

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#ifndef ALLOC_SIGNAL
#define ALLOC_SIGNAL SIGABRT
#endif

/** calls malloc and raises sig if it fails */
static void *raising_malloc(int n, int size, int sig) {
    void *mem = malloc(n * size);
    if(!mem) {
        fprintf(stderr, "malloc failed with n: %d size: %d\n", n, size);
        raise(sig);
    }
    return mem;
}

/** calls calloc and raises sig if it fails */
static void *raising_calloc(int n, int size, int sig) {
    void *mem = calloc(n, size);
    if(!mem) {
        fprintf(stderr, "calloc failed with n: %d size: %d\n", n, size);
        raise(sig);
    }
    return mem;
}

/** calls realloc and raises sig if it fails */
static void *raising_realloc(void *mem, int n, int size, int sig) {
    mem = realloc(mem, n * size);
    if(!mem) {
        fprintf(stderr, "realloc failed with n: %d size: %d\n", n, size);
        raise(sig);
    }
    return mem;
}

/** calls free and sets the pointer NULL (must be a pointer to the address) */
static void free0(void **mem) {
    free(*mem);
    *mem = NULL;
}

/** calls raising_malloc and casts to the given type */
#define New(type, n) (type *) raising_malloc((n), sizeof(type), ALLOC_SIGNAL)

/** calls raising_calloc and casts to the given type */
#define New0(type, n) (type *) raising_calloc((n), sizeof(type), ALLOC_SIGNAL)

/** calls raising_realloc and casts to the given type */
#define ReNew(type, mem, n) (type *) raising_realloc((mem), (n), sizeof(type), ALLOC_SIGNAL)


/** calls malloc and casts to the given type */
#define TryNew(type, n) (type *) malloc((n) * sizeof(type))

/** calls calloc and casts to the given type */
#define TryNew0(type, n) (type *) calloc((n), sizeof(type))

/** calls realloc and casts to the given type */
#define TryReNew(type, mem, n) (type *) realloc((mem), (n) * sizeof(type))

/** wrappper for free0 */
#define Free0(mem) free0((void **)&(mem))

#endif //UTILC_ALLOC_H

