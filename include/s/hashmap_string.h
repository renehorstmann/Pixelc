// this header file does not have an include guard!
// can be used multiple times, with different types

//
// dynamic hashmap with strings as keys
//      see hashmap.h for the base hashmap class
//

#include <string.h>
#include "memory.h"
#include "error.h"

static const char *s_hashmap_string_key_clone_(const char *key, sAllocator_i a) {
    char *clone = s_a_malloc(a, strlen(key) + 1);
    s_assume(clone, "hashmap_string failed to clone a key");
    memcpy(clone, key, strlen(key)+1);
    return clone;
}

static void s_hashmap_string_key_kill_(const char *key, sAllocator_i a) {
    s_a_free(a, (void *) key);
}

static bool s_hashmap_string_key_equals_(const char *a, const char *b) {
    return strcmp(a, b) == 0;
}

static unsigned s_hashmap_string_key_hash_(const char *key) {
    unsigned hash = 5381;
    int c;
    while ((c = *key++))
        hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */
    return hash;
}


#define KEY const char *
#define KEY_CLONE_FN s_hashmap_string_key_clone_
#define KEY_KILL_FN s_hashmap_string_key_kill_
#define KEY_EQUALS_FN s_hashmap_string_key_equals_
#define KEY_HASH_FN s_hashmap_string_key_hash_
#include "hashmap.h"
