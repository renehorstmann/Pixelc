// this header file does not have an include guard!
// can be used multiple times, with different types

//
// dynamic hashmap
//      see hashmap_string.h for an implementation with strings as keys
//

#include "allocator.h"
#include "log.h"

#define S_NAME_CONCAT(a, b) a ## b
#define S_NAME_CONCAT2(a, b) S_NAME_CONCAT(a, b)
#define S_TO_STRING(a) #a
#define S_TO_STRING2(a) S_TO_STRING(a)

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
#define CLASS S_NAME_CONCAT2(HashMap_, TYPE)
#endif

// array function names, for example foo
#ifndef FN_NAME
#define FN_NAME S_NAME_CONCAT2(hashmap_, TYPE)
#endif

#ifndef KEY_CLONE_FN
#error hashmap.h needs a function to clone a key(key key_clone_fn(key to_clone, sAllocator_i a))
#endif

#ifndef KEY_KILL_FN
#error hashmap.h needs a function to kill a key(void key_kill_fn(key to_kill, sAllocator_i a))
#endif

#ifndef KEY_EQUALS_FN
#error hashmap.h needs a function to compare two keys (bool key_equals_fn(key a, key b))
#endif

#ifndef KEY_HASH_FN
#error hashmap.h needs a function to hash a key (su32 key_hash_fn(key k))
#endif


// so the example would be:
// #define TYPE int
// #define CLASS Foo
// #define FN_NAME foo
// #include "s/hashmap_string.h"
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
#define ITEM S_NAME_CONCAT2(CLASS, Item_s)
#define ITER S_NAME_CONCAT2(CLASS, Iter_s)

typedef struct ITEM {
    TYPE value;
    KEY key;
    struct ITEM *next;
} ITEM;

typedef struct CLASS {
    ITEM **map;
    ssize size;
    sAllocator_i allocator;
} CLASS;

typedef struct ITER {
    CLASS *hashmap;
    ssize map_index;
    ITEM *next;
} ITER;


// bool foo_valid(Foo self)
static bool S_NAME_CONCAT2(FN_NAME, _valid)(CLASS self) {
    return self.map != NULL && self.size >= 1 && s_allocator_valid(self.allocator);
}

// Foo foo_new_a(ssize approx_size, sAllocator_i a)
static CLASS S_NAME_CONCAT2(FN_NAME, _new_a)(ssize approx_size, sAllocator_i a) {
    s_assume(s_allocator_valid(a), "a needs to be valid");
    CLASS self = {
            s_a_new(a, ITEM*, approx_size),
            approx_size,
            a
    };
    if (!self.map) {
        s_error_set("hashmap_new failed");
        s_log_error(S_TO_STRING2(FN_NAME) "_new failed: for approx_size: %zu", approx_size);
        return (CLASS) {.allocator = a};
    } else {
        memset(self.map, 0, approx_size * sizeof(ITEM *));
    }
    return self;
}

// Foo foo_new(ssize approx_size)
static CLASS S_NAME_CONCAT2(FN_NAME, _new)(ssize approx_size) {
    // new_a
    return S_NAME_CONCAT2(FN_NAME, _new_a)(approx_size, S_ALLOCATOR_DEFAULT);
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


// void foo_kill(Foo *self)
static void S_NAME_CONCAT2(FN_NAME, _kill)(CLASS *self) {
    // valid
    if(S_NAME_CONCAT2(FN_NAME, _valid)(*self)) {
        for(int i=0; i<self->size; i++) {
            // first item in hash map array
            ITEM *item = self->map[i];
            while(item) {
                ITEM *next = item->next;
                s_a_free(self->allocator, item);
                item = next;
            }
        }
        s_a_free(self->allocator, self->map);
    }
    // new_invalid_a
    *self = S_NAME_CONCAT2(FN_NAME, _new_invalid_a)(self->allocator);
}

// int *foo_get(Foo *self, const char *key)
static TYPE *S_NAME_CONCAT2(FN_NAME, _get)(CLASS *self, KEY key) {
    // key hash
    su32 hash = KEY_HASH_FN(key) % self->size;
    
    // first item in hash map array
    ITEM **item = &self->map[hash];
    
    // if item is available, get the right item in the linked list
    while(*item && !KEY_EQUALS_FN(key, (*item)->key)) {
        item = &((*item)->next);
    }
    
    // if item not found, create a new one
    if(!(*item)) {
        *item = (ITEM *) s_a_new(self->allocator, ITEM, 1);
        s_assume(*item, "hashmap failed: to allocate a new item");
        memset(*item, 0, sizeof(ITEM));
        (*item)->key = KEY_CLONE_FN(key, self->allocator);
        (*item)->next = NULL;
    }
    
    // return a pointer to the item value
    return &((*item)->value);
}

// void foo_remove(Foo *self, const char *key)
void S_NAME_CONCAT2(FN_NAME, _remove)(CLASS *self, KEY key) {
    // key hash
    su32 hash = KEY_HASH_FN(key) % self->size;

    // first item in hash map array
    ITEM **item = &self->map[hash];

    // if item is available, get the right item in the linked list
    while(*item && !KEY_EQUALS_FN(key, (*item)->key)) {
        item = &((*item)->next);
    }
    
    // item for key not found?
    if(!(*item)) {
        s_log_warn(S_TO_STRING2(FN_NAME), "_remove: failed, key not found");
        return;
    }
    
    ITEM *kill = *item;
    *item = (*item)->next;
    KEY_KILL_FN(kill->key, self->allocator);
    s_a_free(self->allocator, kill);
}

// FooIter_s foo_iter_new(Foo *self)
ITER S_NAME_CONCAT2(FN_NAME, _iter_new)(CLASS *self) {
    return (ITER) {self, -1, NULL};
}

// FooItem_s *foo_iter_next(FooIter_s *self)
ITEM *S_NAME_CONCAT2(FN_NAME, _iter_next)(ITER *self) {
    // test iter valid
    if(!self->hashmap || !S_NAME_CONCAT2(FN_NAME, _valid)(*self->hashmap)
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
