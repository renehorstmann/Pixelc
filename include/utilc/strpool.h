#ifndef UTILC_STRPOOL_H
#define UTILC_STRPOOL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>


#define SP_THREAD_LOCAL __thread
#define SP_CAPACITY_STEPS 8


//
// None pool functions
//

/**
 * Concatenates multiple strings into dst
 * @param dst: buffer that will be filled with the concatenated strings
 * @param strings: A list of strings, that ends with NULL
 * @return: dst
 */
static char *strcat_into_v(char *dst, const char **strings) {
    if(*strings)
        strcpy(dst, *strings++);
    while(*strings)
        strcat(dst, *strings++);
    return dst;
}
/** Concatenates all strings behind dst into dst */
#define strcat_into(dst, ...) strcat_into_v((dst), (const char*[]) {__VA_ARGS__, NULL})

/**
 * Concatenates multiple strings into a new allocated string on the heap
 * @param strings: A list of strings, that ends with NULL
 * @return: The new allocated string on heap
 */
static char *strcat_into_heap_v(const char **strings) {
    const char **it = strings;
    int size = 1;
    while(*it)
        size += strlen(*it++);
    char *res = (char *) malloc(size);
    strcat_into_v(res, strings);
    return res;
}
/** Concatenates all strings into a new allocated string on heap */
#define strcat_into_heap(...) strcat_into_heap_v((const char*[]) {__VA_ARGS__, NULL})

/**
 * Pool member that stores all created strings in a dynamic list.
 * if used, set malloc and free.
 */
struct sp_pool {
    char **data;
    int data_size;
    int data_capacity;
    void *(*malloc)(int size);
    void (*free)(void *data);
};

/** Default pool member for each file and thread (always uses stdlib malloc and free) */
static SP_THREAD_LOCAL struct sp_pool sp_pool_member_;

/** If set, another pool instead the one above will be used */
static struct sp_pool *sp_pool_used;

/** Appends an string to the pool, so that sp_free will free it */
static void sp_pool_append(char *str) {
    struct sp_pool *pool = sp_pool_used ? sp_pool_used : &sp_pool_member_;
    if(++pool->data_size > pool->data_capacity) {
        pool->data_capacity += SP_CAPACITY_STEPS;
        pool->data = (char **) realloc(pool->data, pool->data_capacity * sizeof(char *));
    }
    if(!pool->data) {
        fprintf(stderr, "sp_pool_append failed, alloc error\n");
        raise(SIGABRT);
    }
    pool->data[pool->data_size-1] = str;
}

/** Frees all strings in the pool */
static void sp_free() {
    void (*vfree)(void *) = sp_pool_used ? sp_pool_used->free : free;
    struct sp_pool *pool = sp_pool_used ? sp_pool_used : &sp_pool_member_;
    for(int i=0; i<pool->data_size; i++)
        vfree(pool->data[i]);
    free(pool->data);
    pool->data = NULL;
    pool->data_size = 0;
}

/** Allocates an string and appends it to the pool */
static char *sp_malloc(int size) {
    char *res = (char *) (sp_pool_used ? sp_pool_used->malloc(size) : malloc(size));
    if(!res) {
        fprintf(stderr, "sp_malloc(%d) failed in file %s\n", size, __FILE__);
        raise(SIGABRT);
    }
    sp_pool_append(res);
    return res;
}

/**
 * Removes a string from the pool, without freeing it.
 * @param str: the string to search in the pool
 * @return: The given string if found and removed, NULL if not found.
 */
static char *sp_get_ownership(const char *str) {
    struct sp_pool *pool = sp_pool_used ? sp_pool_used : &sp_pool_member_;
    for(int i=0; i<pool->data_size; i++) {
        if(pool->data[i] == str) {
            pool->data[i] = NULL;
            return (char *) str;
        }
    }
    return NULL;
}

/** Clones a string */
static char *sp_clone(const char *src) {
    char *res = sp_malloc(strlen(src));
    strcpy(res, src);
    return res;
}

/** Clones a string and allocates added_length more bytes */
static char *sp_clone_n(int added_length, const char *src) {
    char *res = sp_malloc(strlen(src) + added_length + 1);
    strcpy(res, src);
    return res;
}

/** Concatenates the strings together (strings must end with a NULL) */
static char *sp_cat_v(const char **strings) {
    int size = 1;
    const char **it = strings;
    while(*it)
        size += strlen(*it++);
    char *res = sp_malloc(size);
    strcat_into_v(res, strings);
    return res;
}

/** Concatenates all given strings together */
#define sp_cat(...) sp_cat_v((const char*[]) {__VA_ARGS__, NULL})

/**
 * Concatenates all given strings together (strings must end with a NULL).
 * added_length more bytes will be allocated
 */
static char *sp_cat_n_v(int added_length, const char **strings) {
    int size = 0;
    const char **it = strings;
    while(*it)
        size += strlen(*it++);
    char *res = sp_malloc(size + added_length + 1);
    strcat_into_v(res, strings);
    return res;
}

/** Concatenates all given strings together. added_length more bytes will be allocated */
#define sp_cat_n(added_length, ...) sp_cat_n_v((added_length), (const char*[]) {__VA_ARGS__, NULL})

/** Iterates and copies src, end can be larger than the string, also all parameters can be negativ */
static char *sp_iter(const char *src, int begin, int end, int step) {
    assert(step != 0 && "sp_iter failed, step must not be 0");
    if(begin < 0)
        begin += (int) strlen(src);
    if(end <= 0)
        end += (int) strlen(src);
    assert(begin < end && "sp_iter failed");
    int range_len = strlen(src+begin);
    if(end-begin < range_len)
        range_len = end-begin;

    int size = (int) range_len / abs(step);
    char *res = sp_malloc(size+1);
    if(step > 0) {
        char *it = res;
        for(int i=0; i<range_len; i+=step)
            *it++ = src[begin+i];
    } else if(step < 0) {
        char *it = res;
        for(int i= (int) range_len-1; i>=0; i+=step)
            *it++ = src[begin+i];
    }
    return res;
}

/** Returns the reversed string of src (calls sp_iter(src, 0, 0, -1)) */
static char *sp_reverse(const char *src) {
    return sp_iter(src, 0, 0, -1);
}

static char *sp_replace(const char *src, const char *from, const char *to) {
    int cnt = 0;
    const char *it_src = src;
    while(*it_src) {
        if(strncmp(it_src, from, strlen(from)) == 0) {
            cnt++;
            it_src+=strlen(from);
        } else
            it_src++;
    }
    int size = strlen(src) - cnt * strlen(from) + cnt * strlen(to) + 1;
    char *res = sp_malloc(size);
    it_src = src;
    char *it_res = res;
    while(*it_src) {
        if(strncmp(it_src, from, strlen(from)) == 0) {
            strcpy(it_res, to);
            it_src += strlen(from);
            it_res += strlen(to);
        } else
            *it_res++ = *it_src++;
    }
    *it_res = '\0';
    return res;
}

/** Sets all characters in the string to lower chars */
static char *sp_tolower(const char *src) {
    char *res = sp_clone(src);
    char *it = res;
    while (*it) {
        *it = (char) tolower(*it);
        it++;
    }
    return res;
}

/** Sets all characters in the string to upper chars */
static char *sp_toupper(const char *src) {
    char *res = sp_clone(src);
    char *it = res;
    while (*it) {
        *it = (char) toupper(*it);
        it++;
    }
    return res;
}


#endif //UTILC_STRPOOL_H
