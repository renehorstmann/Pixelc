#ifndef UTILC_ITERATOR_H
#define UTILC_ITERATOR_H

#include <stdlib.h>

typedef struct intiterator {
    char impl[32]; // impl max size = 32 bytes
    int *end;
    const int *(*get)(struct intiterator *self);
    const int *(*next)(struct intiterator *self);
} intiterator;


struct intiterator_range_s_ {
    int i;
    int step;
    int end;
};

static const int *intiterator_range_get_(intiterator *self) {
    struct intiterator_range_s_ *impl = (struct intiterator_range_s_ *) self->impl;
    return impl->i < impl->end ? &impl->i : NULL;
}

static const int *intiterator_range_reverse_get_(intiterator *self) {
    struct intiterator_range_s_ *impl = (struct intiterator_range_s_ *) self->impl;
    return impl->i > impl->end ? &impl->i : NULL;
}

static const int *intiterator_range_next_(intiterator *self) {
    struct intiterator_range_s_ *impl = (struct intiterator_range_s_ *) self->impl;
    impl->i+=impl->step;
    return self->get(self);
}

/**
 * Creates an intiterator from a range of [start:end) : step
 * @returns the pointer to the first value
 */
static const int *intiterator_full_range_begin(intiterator *self, int start, int end, int step) {
    struct intiterator_range_s_ *impl = (struct intiterator_range_s_ *) self->impl;
    impl->i = start;
    impl->step = step;
    impl->end = end;
    self->end = NULL;
    if(impl->step >=0)
        self->get = &intiterator_range_get_;
    else
        self->get = &intiterator_range_reverse_get_;
    self->next = &intiterator_range_next_;
    return self->get(self);
}

/**
 * Creates an intiterator from a range of [0:end) : 1
 * @returns the pointer to the first value
 */
static const int *intiterator_range_begin(intiterator *self, int end) {
    return intiterator_full_range_begin(self, 0, end, 1);
}



static const int *intiterator_indices_get_(intiterator *self) {
    int **index = (int **) self->impl;
    return *index;
}

static const int *intiterator_indices_next_(intiterator *self) {
    int **index = (int **) self->impl;
    (*index)++;
    return *index;
}

/**
 * Creates an intiterator from indices
 * @returns the pointer to the first value
 */
static const int *intiterator_indices_begin(intiterator *self, int *indices, int size) {
    int **index = (int **) self->impl;
    *index = indices;
    self->end = indices + size;
    self->get = &intiterator_indices_get_;
    self->next = &intiterator_indices_next_;
    return *index;
}

#endif //UTILC_ITERATOR_H

