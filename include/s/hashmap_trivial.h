// this header file does not have an include guard!
// can be used multiple times, with different types

//
// dynamic hashmap with a trivisl key type (pod structs, int, float, ...)
//      see hashmap.h for the base hashmap class
//

#include <string.h>
#include "memory.h"
#include "error.h"

static KEY s__hashmap_trivial_key_clone(KEY key, sAllocator_i a) {
    return key;
}

static void s__hashmap_trivial_key_kill(KEY key, sAllocator_i a) {
    // noop
}

static bool s__hashmap_trivial_key_equals(KEY a, KEY b) {
    return memcmp(&a, &b, sizeof (KEY)) == 0;
}

static su32 s__hashmap_trivial_key_hash(KEY key) {
    su32 hash = 5381;
    const su8 *it = (su8*) &key;
    int c;
    for(int i=0; i<(int) sizeof (KEY); i++) {
        c = it[i];
        hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

        
#define KEY_CLONE_FN s__hashmap_trivial_key_clone
#define KEY_KILL_FN s__hashmap_trivial_key_kill
#define KEY_EQUALS_FN s__hashmap_trivial_key_equals
#define KEY_HASH_FN s__hashmap_trivial_key_hash
#include "hashmap.h"
