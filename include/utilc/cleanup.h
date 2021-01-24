#ifndef UTILC_CLEANUP_H
#define UTILC_CLEANUP_H

#include <stdlib.h>
#include <assert.h>

/** maximal amount of items to clean in a CleanUp member */
#define CLEAN_UP_MAX_ITEMS 32

/** type of a CleanUp function (void function(void*)) */
typedef void (*CLEAN_UP_FUNCTION_TYPE)(void *);

/** CleanUp class to collect items to clean/ free, and free it e. g. at the end of a function */
typedef struct {
    void *data[CLEAN_UP_MAX_ITEMS];
    CLEAN_UP_FUNCTION_TYPE data_fun[CLEAN_UP_MAX_ITEMS];
    int size;
} CleanUp;

/** macro to automatically call clean at the end of the scope (GNU_C extenstion) */
#define CleanUpAutoClean __attribute__((cleanup (CleanUp_clean))) CleanUp

/** CleanUp clean = CleanUp_INIT; */
#define CleanUp_INIT {0}

/** calls all clean functions with their data */
static void CleanUp_clean(CleanUp *self) {
    for(int i=0; i<self->size; i++)
        self->data_fun[i](self->data[i]);
    self->size = 0;
}

/** adds a clean function and its data to CleanUp */
static void CleanUp_add(CleanUp *self, void *data, CLEAN_UP_FUNCTION_TYPE function) {
    assert(self->size < CLEAN_UP_MAX_ITEMS && "Utilc/cleanup.h got to much items");

    self->data[self->size] = data;
    self->data_fun[self->size] = function;
    self->size++;
}

/** macro to easily call CleanUp_add with the casts to void* and CLEAN_UP_FUNCTION_TYPE */
#define CleanUpAdd(cleanup_ptr, data_ptr, function)\
CleanUp_add((cleanup_ptr), (void *) (data_ptr), (CLEAN_UP_FUNCTION_TYPE) (function))

/** to get the same style as with CleanUpAdd */
#define CleanUpClean(cleanup_ptr)\
CleanUp_clean((cleanup_ptr))


/** Creats a CleanUp member called clean_up_scobe_member__ */
#define CleanUpScopeInit CleanUp clean_up_scobe_member__ = CleanUp_INIT

/** Creats a CleanUp member called clean_up_scobe_member__ with automatic clean at scope end */
#define CleanUpScopeAutoCleanInit __attribute__((cleanup (CleanUp_clean))) CleanUp clean_up_scobe_member__

/** Adds an clean item to the CleanUp member called clean_up_scobe_member__ */
#define CleanUpScopeAdd(data_ptr, function)\
CleanUp_add(&clean_up_scobe_member__,(void *) (data_ptr), (CLEAN_UP_FUNCTION_TYPE) (function))

/** Cleans the CleanUp member called clean_up_scobe_member__ */
#define CleanUpScopeClean CleanUp_clean(&clean_up_scobe_member__)

#endif //UTILC_CLEANUP_H

