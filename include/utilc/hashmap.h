#ifndef UTILC_HASHMAP_H
#define UTILC_HASHMAP_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 * Creates a HashMap with the name (class_name) and the types for key and value (key_type) (value_type).
 * The function hashfunction should take a key and return an unsigned hash number.
 * The function keycmp_function should return true, if both key parameters are equal.
 * The function keycpy_function should copy the input key into the return value.
 * The function keykill_function should free the given key.
 * 
 * Construct a Map with <class_name> map; <fn_name>_new(&map, approx_size);.
 * Kill it with <fn_name>_kill.
 * <fn_name>_get returns an pointer to a value for the given key (if not available yet, it will create a new entry).
 * <fn_name>_remove removes the value under the given key, if available.
 *
 * Get a map iterator with <fn_name>_get_iter(&map);
 */
#define HashMap(key_type, value_type, class_name, fn_name, hash_function, keycmp_function, keycpy_function, keykill_function)\
typedef struct class_name ## _Item {\
    key_type key;\
    value_type value;\
    struct class_name ## _Item *next;\
} class_name ## _Item;\
typedef struct {\
    class_name ## _Item **map;\
    int map_size;\
} class_name;\
typedef struct {\
    class_name *hashmap;\
    int hash_row;\
    class_name ## _Item *next;\
} class_name ## _Iter;\
void fn_name ## _new(class_name *self, int approx_size) {\
    self->map = (class_name ## _Item **) calloc(approx_size, sizeof(class_name ## _Item *));\
    self->map_size = approx_size;\
}\
void fn_name ## _kill(class_name  *self) {\
    for (int i = 0; i < self->map_size; i++) {\
        class_name ## _Item *item = self->map[i];\
        while (item) {\
            class_name ## _Item *next = item->next;\
            keykill_function(item->key);\
            free(item);\
            item = next;\
        }\
    }\
    free(self->map);\
    self->map = NULL;\
    self->map_size = 0;\
}\
value_type *fn_name ## _get(const class_name *self, key_type key) {\
    unsigned hash = hash_function(key) % self->map_size;\
    class_name ## _Item **item = &self->map[hash];\
    while (*item && !keycmp_function(key, (*item)->key))\
        item = &(*item)->next;\
    if (!*item) {\
        *item = (class_name ## _Item *) malloc(sizeof(class_name ## _Item));\
        (*item)->key = keycpy_function(key);\
        (*item)->next = NULL;\
    }\
    return &(*item)->value;\
}\
void fn_name ## _remove(const class_name *self, key_type key) {\
    unsigned hash = hash_function(key) % self->map_size;\
    class_name ## _Item **item = &self->map[hash];\
    while (*item && !keycmp_function(key, (*item)->key))\
        item = &(*item)->next;\
    if (*item) {\
        class_name ## _Item *kill = *item;\
        *item = (*item)->next;\
        keykill_function(kill->key);\
        free(kill);\
    }\
}\
class_name ## _Iter fn_name ## _get_iter(class_name *self) {\
    return (class_name ## _Iter) {self, -1, NULL};\
}\
class_name ## _Item *fn_name ## _Iter_next(class_name ## _Iter *it) {\
    class_name ## _Item *ret;\
    if(it->next) {\
        ret = it->next;\
        it->next = ret->next;\
        return ret;\
    }\
    do {\
        it->hash_row++;\
        if(it->hash_row >= it->hashmap->map_size)\
            return NULL;\
        ret = it->hashmap->map[it->hash_row];\
    } while(ret == NULL);\
    it->next = ret->next;\
    return ret;\
}

/** impl function for StrHashMap */
static unsigned StrHashMap_impl_hash(const char *key) {
    unsigned hash = 5381;
    int c;
    while ((c = *key++))
        hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */
    return hash;
}

/** impl function for StrHashMap */
static bool StrHashMap_impl_keycmp(const char *a, const char *b) {
    return strcmp(a, b) == 0;
}

/** impl function for StrHashMap */
static const char *StrHashMap_impl_keycpy(const char *cpy) {
    char *result = (char *) malloc(strlen(cpy) + 1);
    strcpy(result, cpy);
    return result;
}

/** impl function for StrHashMap */
static void StrHashMap_impl_keykill(const char *key) {
    free((void *) key);
}


/**
 * Creates a string HashMap with the name (class_name) and the type for value (value_type).
 * 
 * Construct a Map with <class_name> map; <fn_name>_new(&map, approx_size);.
 * Kill it with <fn_name>_kill.
 * <fn_name>_get returns an pointer to a value for the given string key (if not available yet, it will create a new entry).
 * <fn_name>_remove removes the value under the given string key, if available.
 */
#define StrHashMap(value_type, class_name, fn_name) HashMap(const char *, value_type, class_name, fn_name,\
StrHashMap_impl_hash, StrHashMap_impl_keycmp, StrHashMap_impl_keycpy, StrHashMap_impl_keykill)


#endif //UTILC_HASHMAP_H

