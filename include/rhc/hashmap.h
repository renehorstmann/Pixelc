// this header file does not have an include guard!
// can be used multiple times, with different types

#include <string.h>     // memcpy
#include "allocator.h"
#include "log.h"

#define RHC_NAME_CONCAT(a, b) a ## b
#define RHC_NAME_CONCAT2(a, b) RHC_NAME_CONCAT(a, b)
#define RHC_TO_STRING(a) #a
#define RHC_TO_STRING2(a) RHC_TO_STRING(a)

//
// Options:
//

#ifndef TYPE
#error hashmap.h needs a type (value type) (e.g.: #define TYPE int)
#endif

#ifndef KEY
#error hashmap.h needs a type (value type) (e.g.: #define TYPE int)
#endif

// array class name, for example Foo
#ifndef CLASS
#define CLASS RHC_NAME_CONCAT2(HashMap_, TYPE)
#endif

// array function names, for example foo
#ifndef FN_NAME
#define FN_NAME RHC_NAME_CONCAT2(hashmap_, TYPE)
#endif

#ifndef KEY_CLONE_FN
#error hashmap.h needs a function to clone a key(key key_clone_fn(key to_clone, Allocator_s a))
#endif

#ifndef KEY_KILL_FN
#error hashmap.h needs a function to kill a key(key key_clone_fn(key to_clone, Allocator_s a))
#endif

#ifndef KEY_EQUALS_FN
#error hashmap.h needs a function to compare two keys (bool key_equals_fn(key a, key b))
#endif

#ifndef KEY_HASH_FN
#error hashmap.h needs a function to hash a key (unsigned key_hash_fn(key k))
#endif


// so the example would be:
// #define TYPE int
// #define CLASS Foo
// #define FN_NAME foo
// #include "rhc/hashmap_string.h"
//
// Foo foo = foo_new(&foo, 32);   // approx_size
// *foo_get(&foo, "a") = 7;       // set 7 to key "a"
// *foo_get(&foo, "b") = 8;       // set 8 to key "a"
// *foo_get(&foo, "a") = 77;      // overwrite 77 to key "a"
// printf("foo["a"]=%d, *foo_get(&foo, "a"));
// FooIter_s iter = foo_iter_new(&foo);
// int *item;
// while(item=foo_iter_next(&iter)) {
//      printf("item: %i\n", *item);
// }
// foo_kill(&foo);

//
// auto definitions
//
#define ITEM RHC_NAME_CONCAT2(CLASS, Item_s)
#define ITER RHC_NAME_CONCAT2(CLASS, Iter_s)

typedef struct ITEM {
    TYPE value;
    KEY key;
    struct ITEM *next;
} ITEM;

typedef struct {
    ITEM **map;
    int size;
    Allocator_s allocator;
} CLASS;

typedef struct {
    CLASS *hashmap;
    int map_index;
    ITEM *next;
} ITER;


// bool foo_valid(Foo self)
static bool RHC_NAME_CONCAT2(FN_NAME, _valid)(CLASS self) {
    return self.map != NULL && self.size >= 1 && allocator_valid(self.allocator);
}

// Foo foo_new_a(size_t approx_size, Allocator_s a)
static CLASS RHC_NAME_CONCAT2(FN_NAME, _new_a)(int approx_size, Allocator_s a) {
    assume(allocator_valid(a), "allocator needs to be valid");
    CLASS self = {
            a.malloc(a, approx_size * sizeof(ITEM *)),
            approx_size,
            a
    };
    if (!self.map) {
        rhc_error = "hashmap_new failed";
        log_error(RHC_TO_STRING2(FN_NAME) "_new failed: for approx_size: %zu", approx_size);
        return (CLASS) {.allocator = a};
    } else {
        memset(self.map, 0, approx_size * sizeof(ITEM *));
    }
    return self;
}

// Foo foo_new(size_t approx_size)
static CLASS RHC_NAME_CONCAT2(FN_NAME, _new)(int approx_size) {
    // new_a
    return RHC_NAME_CONCAT2(FN_NAME, _new_a)(approx_size, RHC_HASHMAP_DEFAULT_ALLOCATOR);
}

// Foo foo_new_invalid_a(Allocator_s a)
static CLASS RHC_NAME_CONCAT2(FN_NAME, _new_invalid_a)(Allocator_s a) {
    return (CLASS) {.allocator = a};
}

// Foo foo_new_invalid_a()
static CLASS RHC_NAME_CONCAT2(FN_NAME, _new_invalid)() {
    // new_invalid_a
    return RHC_NAME_CONCAT2(FN_NAME, _new_invalid_a)(RHC_HASHMAP_DEFAULT_ALLOCATOR);
}


// void foo_kill(Foo *self)
static void RHC_NAME_CONCAT2(FN_NAME, _kill)(CLASS *self) {
    // valid
    if(!RHC_NAME_CONCAT2(FN_NAME, _valid)(*self)) {
        self->allocator.free(self->allocator, self->map);
    }
    // new_invalid_a
    *self = RHC_NAME_CONCAT2(FN_NAME, _new_invalid_a)(self->allocator);
}

// int *foo_get(Foo *self, const char *key)
static TYPE *RHC_NAME_CONCAT2(FN_NAME, _get)(CLASS *self, KEY key) {
    // key hash
    unsigned hash = KEY_HASH_FN(key) % self->size;
    
    // first item in hash map array
    ITEM **item = &self->map[hash];
    
    // if item is available, get the right item in the linked list
    while(*item && !KEY_EQUALS_FN(key, (*item)->key)) {
        item = &((*item)->next);
    }
    
    // if item not found, create a new one
    if(!(*item)) {
        *item = (ITEM *) self->allocator.alloc(self->allocator, sizeof(ITEM));
        assume(*item, "hashmap failed: to allocate a new item");
        memset(*item, 0, sizeof(ITEM));
        (*item)->key = KEY_CLONE_FN(key, self->allocator);
        (*item)->next = NULL;
    }
    
    // return a pointer to the item value
    return &((*item)->value);
}

// void foo_remove(Foo *self, const char *key)
void RHC_NAME_CONCAT2(FN_NAME, _remove)(CLASS *self, KEY key) {
    // key hash
    unsigned hash = KEY_HASH_FN(key) % self->size;

    // first item in hash map array
    ITEM **item = &self->map[hash];

    // if item is available, get the right item in the linked list
    while(*item && !KEY_EQUALS_FN(key, (*item)->key)) {
        item = &((*item)->next);
    }
    
    // item for key not found?
    if(!(*item)) {
        log_warn(RHC_TO_STRING2(FN_NAME), "_remove: failed, key not found");
        return;
    }
    
    ITEM *kill = *item;
    *item = (*item)->next;
    KEY_KILL_FN(kill->key, self->allocator);
    self->allocator.free(self->allocator, kill);
}

// FooIter_s foo_iter_new(Foo *self)
ITER RHC_NAME_CONCAT2(FN_NAME, _iter_new)(CLASS *self) {
    return (ITER) {self, -1, NULL};
}

// FooItem_s *foo_iter_next(FooIter_s *self)
ITEM *RHC_NAME_CONCAT2(FN_NAME, _iter_next)(ITER *self) {
    // test iter valid
    if(!self->hashmap || !RHC_NAME_CONCAT2(FN_NAME, _valid)(*self->hashmap)
            || self->map_index <= -2 || self->map_index >= self->hashmap->size)
        return NULL;
        
    ITEM *item;
    // next item is available, so just use it
    if(self->next) {
        item = self->next;
        self->next = self->next->next;
        return item;
    }
    
    // find next item in the map array
    do {
        self->map_index++;
        if(self->map_index >= self->hashmap->size) {
            return NULL; // end of hashmap
        }
        item = self->hashmap->map[self->map_index];
    } while(item == NULL);
    
    self->next = item->next;
    return item;
}

#undef TYPE
#undef KEY
#undef CLASS
#undef FN_NAME
#undef KEY_CLONE_FN
#undef KEY_KILL_FN
#undef KEY_EQUALS_FN
#undef KEY_HASH_FN
#undef ITEM
#undef ITER
