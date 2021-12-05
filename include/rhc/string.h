#ifndef RHC_STRING_H
#define RHC_STRING_H

#include "str.h"


//
// Functions
//

static String string_new_invalid_a(Allocator_i a);


// allocated start_capacity + 1 (null)
static String string_new_a(size_t start_capacity, Allocator_i a) {
    assume(allocator_valid(a), "allocator needs to be valid");
    String self = {
            .str.data = a.malloc(a, start_capacity + 1),
            .str.size = 0,
            .capacity = start_capacity,
            .allocator = a
    };
    if(!self.data)
        return string_new_invalid_a(a);
    memset(self.data, 0, start_capacity + 1);
    return self;
}

// allocated start_capacity + 1 (null)
static String string_new(size_t start_capacity) {
    return string_new_a(start_capacity, RHC_DEFAULT_ALLOCATOR);
}

// new empty invalid string
static String string_new_invalid_a(Allocator_i a) {
    String self = {0};
    self.allocator = a;
    return self;
}

// new empty invalid string with the default allocator
static String string_new_invalid() {
    String self = {0};
    self.allocator = RHC_DEFAULT_ALLOCATOR;
    return self;
}

// clones Str_s and appends null
static String string_new_clone_a(Str_s to_clone, Allocator_i a) {
    String sb = string_new_a(to_clone.size, a);
    if(!string_valid(sb))
        return sb;
    memcpy(sb.data, to_clone.data, to_clone.size);
    sb.size = to_clone.size;
    return sb;
}

// clones Str_s and appends null
static String string_new_clone(Str_s to_clone) {
    return string_new_clone_a(to_clone, RHC_DEFAULT_ALLOCATOR);
}

// copies str s into a new string, with old -> replacement.
static String string_new_replace_a(Str_s to_replace, Str_s old, Str_s replacement, Allocator_i a) {
    if(str_empty(to_replace) || str_empty(old) || !str_valid(replacement)) {
        return string_new_invalid_a(a);
    }
    size_t cnt = str_count_str(to_replace, old);
    if(cnt <= 0) {
        return string_new_clone_a(to_replace, a);
    }
    size_t size = to_replace.size - cnt*old.size + cnt*replacement.size;
    String res = string_new_a(size, a);
    res.size = size;
    res.str = str_replace_str_into(res.str, to_replace, old, replacement);
    return res;
}

// copies str s into a new string, with old -> replacement.

static String string_new_replace(Str_s to_replace, Str_s old, Str_s replacement) {
    return string_new_replace_a(to_replace, old, replacement, RHC_DEFAULT_ALLOCATOR);
}

// concatenates all strs
static String string_new_cat_a(Str_s *strs, int n, Allocator_i a) {
    size_t size = 0;
    for(size_t i=0; i<n; i++) {
        size += str_empty(strs[i])? 0 : strs[i].size;
    }
    String res = string_new_a(size, a);
    if(!string_valid(res))
        return res;

    for(size_t i=0; i<n; i++) {
        if(!str_empty(strs[i])) {
            str_cpy(strs[i], (Str_s) {res.data + res.size, strs[i].size});
            res.size += strs[i].size;
        }
    }
    return res;
}

// concatenates all strs
static String string_new_cat(Str_s *strs, int n) {
    return string_new_cat_a(strs, n, RHC_DEFAULT_ALLOCATOR);
}

// size is the sum of characters, not including termination null (as strlen)
static void string_set_capacity(String *self, size_t capacity) {
    if(!string_valid(*self))
        return;

    void *data = self->allocator.realloc(self->allocator, self->data, capacity + 1);
    if(!data) {
        string_kill(self);
        return;
    }
    self->data = data;
    self->capacity = capacity;
    memset(&self->data[self->size], 0, self->capacity + 1 - self->size);
}

// size is the sum of characters, not including termination null (as strlen)
static void string_resize(String *self, size_t size) {
    if(size > self->capacity) {
        string_set_capacity(self, size * 2);
    }
    if(!string_valid(*self))
        return;
    self->size = size;
    self->data[self->size] = '\0';  //just to be sure
}

// appends a char
static void string_push(String *self, char push) {
    if(!string_valid(*self))
        return;
    string_resize(self, self->size + 1);
    self->data[self->size-1] = push;
    self->data[self->size] = '\0';  //just to be sure
}

// appends a string
static void string_append(String *self, Str_s append) {
    if(!string_valid(*self))
        return;
    size_t prev_size = self->size;
    string_resize(self, self->size + append.size);
    memcpy(self->data + prev_size, append.data, append.size);
    self->data[self->size] = '\0';  //just to be sure
}



#endif //RHC_STRING_H
