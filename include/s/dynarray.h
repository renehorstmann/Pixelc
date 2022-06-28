// this header file does not have an include guard!
// can be used multiple times, with different types

//
// dynamic array like a std::vector
//

#include "error.h"
#include "memory.h"
#include "log.h"


#define S_NAME_CONCAT(a, b) a ## b
#define S_NAME_CONCAT2(a, b) S_NAME_CONCAT(a, b)
#define S_TO_STRING(a) #a
#define S_TO_STRING2(a) S_TO_STRING(a)

//
// Options:
//

// array type, for example int
#ifndef TYPE
#error dynarray.h needs a type (e.g.: #define TYPE int)
#endif

// array class name, for example Foo
#ifndef CLASS
#define CLASS S_NAME_CONCAT2(DynArray_, TYPE)
#endif

// array function names, for example foo
#ifndef FN_NAME
#define FN_NAME S_NAME_CONCAT2(dynarray_, TYPE)
#endif

// remove copying functions (push)
//#define NO_COPY



// so the example would be:
// #define TYPE int
// #define CLASS Foo
// #define FN_NAME foo
// #include "s/dynarray.h"
//
// Foo foo = foo_new(&foo, 32);   // start_capacity
// foo_push(&foo, 7);             // push the int 7 into the array
// printf("foo.array[0]=%d ; foo.size=%d", foo.array[0], foo.size);
// foo_kill(&foo);


typedef struct CLASS {
    TYPE *array;
    ssize size;

    ssize capacity;
    sAllocator_i allocator;
} CLASS;


// bool foo_valid(Foo self)
static bool S_NAME_CONCAT2(FN_NAME, _valid)(CLASS self) {
    return self.array != NULL && s_allocator_valid(self.allocator);
}


// Foo foo_new_a(ssize start_capacity, sAllocator_i a)
static CLASS S_NAME_CONCAT2(FN_NAME, _new_a)(ssize start_capacity, sAllocator_i a) {
    s_assume(s_allocator_valid(a), "a needs to be valid");
    CLASS self = {
            s_a_new(a, TYPE, start_capacity),
            0,
            start_capacity,
            a
    };
    if (!self.array) {
        s_error_set("dynarray_new failed");
        s_log_error(S_TO_STRING2(FN_NAME) "_new failed: for capacity: %zu", start_capacity);
        return (CLASS) {.allocator = a};
    }
    return self;
}

// Foo foo_new(ssize start_capacity)
static CLASS S_NAME_CONCAT2(FN_NAME, _new)(ssize start_capacity) {
    // new_a
    return S_NAME_CONCAT2(FN_NAME, _new_a)(start_capacity, S_ALLOCATOR_DEFAULT);
}

// Foo foo_new_invalid_a(sAllocator_i a)
static CLASS S_NAME_CONCAT2(FN_NAME, _new_invalid_a)(sAllocator_i a) {
    return (CLASS) {.allocator = a};
}

// Foo foo_new_invalid_a()
static CLASS S_NAME_CONCAT2(FN_NAME, _new_invalid)() {
    // new_invalid_a
    return S_NAME_CONCAT2(FN_NAME, _new_invalid_a)(S_ALLOCATOR_DEFAULT);
}

// Foo foo_new_clone_a(int *to_clone, ssize n, sAllocator_i a)
static CLASS S_NAME_CONCAT2(FN_NAME, _new_clone_a)(TYPE *to_clone, ssize n, sAllocator_i a) {
    // new_a
    CLASS self = S_NAME_CONCAT2(FN_NAME, _new_a)(n, a);

    // valid
    if(!S_NAME_CONCAT2(FN_NAME, _valid)(self))
        return self;

    memcpy(self.array, to_clone, n * sizeof(TYPE));
    self.size = n;
    return self;
}

// Foo foo_new_clone(int *to_clone, ssize n)
static CLASS S_NAME_CONCAT2(FN_NAME, _new_clone)(TYPE *to_clone, ssize n) {
    // new_clone_a
    return S_NAME_CONCAT2(FN_NAME, _new_clone_a)(to_clone, n, S_ALLOCATOR_DEFAULT);
}

// void foo_kill(Foo *self)
static void S_NAME_CONCAT2(FN_NAME, _kill)(CLASS *self) {
    // valid
    if(S_NAME_CONCAT2(FN_NAME, _valid)(*self)) {
        s_a_free(self->allocator, self->array);
    }
    // new_invalid_a
    *self = S_NAME_CONCAT2(FN_NAME, _new_invalid_a)(self->allocator);
}

// void foo_set_capacity(Foo *self, ssize capacity)
static void S_NAME_CONCAT2(FN_NAME, _set_capacity)(CLASS *self, ssize capacity) {
    // !valid
    if(!S_NAME_CONCAT2(FN_NAME, _valid)(*self))
        return;

    void *array = s_a_renew(self->allocator, TYPE, self->array, capacity);
    if(!array) {
        // kill
        s_error_set("dynarray_set_capacity failed");
        s_log_error(S_TO_STRING2(FN_NAME) "_set_capacity failed: for capacity: %zu", capacity);
        S_NAME_CONCAT2(FN_NAME, _kill)(self);
        return;
    }
    self->array = array;
    self->capacity = capacity;
    if(capacity < self->size)
        self->size = capacity;
}

// void foo_resize(Foo *self, ssize size)
static void S_NAME_CONCAT2(FN_NAME, _resize)(CLASS *self, ssize size) {
    if(size > self->capacity) {
        // _set_capacity
        S_NAME_CONCAT2(FN_NAME, _set_capacity)(self, size * 2);
    }

    // valid
    if(S_NAME_CONCAT2(FN_NAME, _valid)(*self)) {
        self->size = size;
    }
}

// int *foo_append_array(Foo *self, int *opt_init_array, ssize array_size)
static TYPE *S_NAME_CONCAT2(FN_NAME, _append_array)(CLASS *self, TYPE *opt_init_array, ssize array_size) {
    // resize
    S_NAME_CONCAT2(FN_NAME, _resize)(self, self->size+array_size);

    TYPE *ret = &self->array[self->size-array_size];
    if(opt_init_array)
        memcpy(ret, opt_init_array, sizeof(TYPE) * array_size);
    return ret;
}

// int *foo_append(Foo *self, int *opt_init)
static TYPE *S_NAME_CONCAT2(FN_NAME, _append)(CLASS *self, TYPE *opt_init) {
    // append_array
    return S_NAME_CONCAT2(FN_NAME, _append_array)(self, opt_init, 1);
}


#ifndef NO_COPY
// void foo_push(Foo *self, int push)
static void S_NAME_CONCAT2(FN_NAME, _push)(CLASS *self, TYPE push) {
    // append
    S_NAME_CONCAT2(FN_NAME, _append)(self, &push);
}

// TYPE foo_pop(Foo *self)
static TYPE S_NAME_CONCAT2(FN_NAME, _pop)(CLASS *self) {
    // !valid || self->size <= 0
    if(!S_NAME_CONCAT2(FN_NAME, _valid)(*self) || self->size <= 0) {
        s_log_error(S_TO_STRING2(FN_NAME) "_pop failed: invalid or size = 0");
        return (TYPE) {0};
    }
    TYPE ret = self->array[self->size-1];

    // resize
    S_NAME_CONCAT2(FN_NAME, _resize)(self, self->size-1);

    return ret;
}

#endif



#undef TYPE
#undef CLASS
#undef FN_NAME
#undef NO_COPY
