#ifndef RHC_STR_H
#define RHC_STR_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "alloc.h"
#include "error.h"
#include "log.h"

//
// Options
//

// creates an invalid str
static Str_s str_new_invalid() {
    return (Str_s) {NULL, 0};
}

// Str_s from a c string
static Str_s strc(const char *cstring) {
    return (Str_s) {(char *) cstring, strlen(cstring)};
}

// returns true if the str is empty
static bool str_empty(Str_s s) {
    return !s.data || s.size == 0;
}

// prints a str to stdout
static void sv_fprint(Str_s s, FILE *file) {
    if(!str_valid(s))
        return;
    fprintf(file, "(Str_s) {\"%.*s\", %zu}\n", (int) s.size, s.data, s.size);
}

static void sv_print(Str_s s) {
    sv_fprint(s, stdout);
}

// copies from into cpy. cpy and from must have the same size
static void str_cpy(Str_s cpy, Str_s from) {
    if(!str_valid(cpy) || !str_valid(from) || cpy.size != from.size) {
        rhc_error = "str_cpy failed";
        log_error("str_cpy failed: invalid or wrong sizes");
        return;
    }
    memcpy(cpy.data, from.data, cpy.size);
}

// copies from into cpy_buffer. cpy_buffer must have at least the size of from
// returns cpy_buffer with the copied size of from
static Str_s str_cpy_into(Str_s cpy_buffer, Str_s from) {
    if(!str_valid(cpy_buffer) || !str_valid(from) || cpy_buffer.size < from.size) {
        rhc_error = "str_cpy_info failed";
        log_error("str_cpy_into failed: invalid or wrong sizes");
        return (Str_s) {cpy_buffer.data, 0};
    }
    cpy_buffer.size = from.size;
    str_cpy(cpy_buffer, from);
    return cpy_buffer;
}

static bool str_equals(Str_s a, Str_s b) {
    if(str_empty(a) && str_empty(b))
        return true;
    if(!str_valid(a) || !str_valid(b) || a.size != b.size)
        return false;
    return memcmp(a.data, b.data, a.size) == 0;
}

// out_c_string needs to be a buffer of at least str.size+1
static void str_as_c(char *out_c_string, Str_s s) {
    if(!str_valid(s)) {
        out_c_string[0] = '\0';
        return;
    }
    memcpy(out_c_string, s.data, s.size);
    out_c_string[s.size] = '\0';
}

// returns a new allocated buffer with str as cstring
static char *str_as_new_c_a(Str_s s, Allocator_i a) {
    assume(allocator_valid(a), "allocator needs to be valid");
    if(!str_valid(s))
        return NULL;
    char *buffer = a.malloc(a, s.size+1);
    if(!buffer)
        return NULL;
    str_as_c(buffer, s);
    return buffer;
}


// returns a new allocated buffer with str as cstring
static char *str_as_new_c(Str_s s) {
    return str_as_new_c_a(s, RHC_DEFAULT_ALLOCATOR);
}



// returns true if str begins with cmp
static bool str_begins_with(Str_s s, Str_s cmp) {
    if(!str_valid(s) || str_empty(cmp) || s.size < cmp.size)
        return false;
    return str_equals(cmp, (Str_s) {s.data, cmp.size});
}

// returns true if str ends with cmp
static bool str_ends_with(Str_s s, Str_s cmp) {
    if(!str_valid(s) || str_empty(cmp) || s.size < cmp.size)
        return false;
    return str_equals(cmp, (Str_s) {s.data+s.size-cmp.size, cmp.size});
}

// returns a new str, based on s, but without the leading chars of strip (space -> isspace())
static Str_s str_lstrip(Str_s s, char strip) {
    // invalid safe
    if(strip==' ') {
        while (!str_empty(s) && isspace(*s.data)) {
            s.data++;
            s.size--;
        }
    } else {
        while (!str_empty(s) && *s.data == strip) {
            s.data++;
            s.size--;
        }
    }
    return s;
}

// returns a new str, based on s, but without the least chars of strip (space -> isspace())
static Str_s str_rstrip(Str_s s, char strip) {
    // invalid safe
    if(strip==' ') {
        while (!str_empty(s) && isspace(s.data[s.size-1])) {
            s.size--;
        }
    } else {
        while (!str_empty(s) && s.data[s.size-1] == strip) {
            s.size--;
        }
    }
    return s;
}

// returns a new str, based on s, but without the leading and least chars of strip (space -> isspace())
static Str_s str_strip(Str_s s, char strip) {
    return str_lstrip(str_rstrip(s, strip), strip);
}

// a new str, based on s, from the beginning until the first split, or the end
static Str_s str_next_split(Str_s s, char split) {
    if(str_empty(s))
        return str_new_invalid();
    Str_s res = {s.data, 0};
    if (split==' ') {
        while (res.size < s.size && !isspace(res.data[res.size]))
            res.size++;
    } else {
        while (res.size < s.size && res.data[res.size] != split)
            res.size++;
    }
    return res;
}


// returns a str array, based on s, containing all non empty splits between each split (limited autotype version)
static int str_split(Str_s *splits, int max, Str_s s, char split) {
    // invalid safe
    int n = 0;
    for (;;) {
        s = str_lstrip(s, split);
        if (str_empty(s))
            return n;
        Str_s item = str_next_split(s, split);
        s.data += item.size;
        s.size -= item.size;
        splits[n++] = item;
        if (n >= max) {
            log_warn("str_split: reached max: %d/%d", n, max);
            return n;
        }
    }
}

// returns a str array, based on s, containing all non empty splits between each split (allocated version)
static StrArray str_split_allocated(Str_s s, char split, Allocator_i a) {
    StrArray res = {.allocator = a};
    assume(allocator_valid(a), "allocator needs to be valid");
    for (;;) {
        s = str_lstrip(s, split);
        if (str_empty(s))
            return res;
        Str_s item = str_next_split(s, split);
        s.data += item.size;
        s.size -= item.size;
        Str_s *array = a.realloc(a, res.array, sizeof(Str_s) * (res.size+1));
        if(!array) {
            log_warn("str_split_allocated failed: to realloc");
            return res;
        }
        res.array = array;
        res.array[res.size++] = item;
    }
}

// returns the index of the first found char find in str, or -1 if nothing found
static ssize_t str_find_first(Str_s s, char find) {
    if(str_empty(s))
        return -1;
    if (find==' ') {
        for(ssize_t i=0; i<s.size; i++) {
            if(isspace(s.data[i]))
                return i;
        }
    } else {
        for(ssize_t i=0; i<s.size; i++) {
            if(s.data[i] == find)
                return i;
        }
    }
    return -1;
}


// returns the index of the last found char find in str, or -1 if nothing found
static ssize_t str_find_last(Str_s s, char find) {
    if(str_empty(s))
        return -1;
    if (find==' ') {
        for(ssize_t i=s.size-1; i>=0; i--) {
            if(isspace(s.data[i]))
                return i;
        }
    } else {
        for(ssize_t i=s.size-1; i>=0; i--) {
            if(s.data[i] == find)
                return i;
        }
    }
    return -1;
}

// returns the index of the first found str found in s, or -1 if nothing found
static ssize_t str_find_first_str(Str_s s, Str_s find) {
    // invalid safe
    if(find.size > s.size)
        return -1;
    for(size_t i=0; i<s.size-find.size; i++) {
        if(str_equals(find, (Str_s) {s.data+i, find.size}))
            return i;
    }
    return -1;
}

// returns the index of the last found str found in s, or -1 if nothing found
static ssize_t str_find_last_str(Str_s s, Str_s find) {
    // invalid safe
    if(find.size > s.size)
        return -1;
    for(ssize_t i=(ssize_t) s.size-find.size-1; i>=0; i--) {
        if(str_equals(find, (Str_s) {s.data+i, find.size}))
            return i;
    }
    return -1;
}

// returns the index of the first found char of multiple_chars in str, or -1 if nothing found
static ssize_t str_find_first_set(Str_s s, const char *char_set) {
    for(size_t i=0; i<s.size; i++) {
        for (const char *c = char_set; *c != 0; c++) {
            if ((*c == ' ' && isspace(s.data[i])) || *c == s.data[i])
                return i;
        }
    }
    return -1;
}
// returns the index of the first found char of multiple_chars in str, or -1 if nothing found
static ssize_t str_find_last_set(Str_s s, const char *char_set) {
    for(ssize_t i=(ssize_t) s.size-1; i>=0; i--) {
        for (const char *c = char_set; *c != 0; c++) {
            if ((*c == ' ' && isspace(s.data[i])) || *c == s.data[i])
                return i;
        }
    }
    return -1;
}

// returns new str, based on s, but missing the first n characters
static Str_s str_eat(Str_s s, size_t n) {
    if(n>=s.size) {
        s.data += s.size;
        s.size = 0;
    } else {
        s.data += n;
        s.size -= n;
    }
    return s;
}

// returns new str, based on s, but missing the last n characters
static Str_s str_eat_back(Str_s s, size_t n) {
    if(n>=s.size) {
        s.size = 0;
    } else {
        s.size -= n;
    }
    return s;
}

// checks if s begins with eat_begin and returns a new str, based on s, without eat_begin at the beginning
// if s does not begin with eat_begin, an invalid str is returned
static Str_s str_eat_str(Str_s s, Str_s eat_begin) {
    if(!str_begins_with(s, eat_begin))
        return str_new_invalid();
    s.data+=eat_begin.size;
    s.size-=eat_begin.size;
    return s;
}

// checks if s ends with eat_back and returns a new str, based on s, without eat_back at the end
// if s does not end with eat_back, an invalid str is returned
static Str_s str_eat_back_str(Str_s s, Str_s eat_back) {
    if(!str_ends_with(s, eat_back))
        return str_new_invalid();
    s.size-=eat_back.size;
    return s;
}

// returns new str, based on s, without every leading char until the char until.
// The cut is set into opt_get
static Str_s str_eat_until(Str_s s, char until, Str_s *opt_get) {
    Str_s get = s;
    ssize_t pos = str_find_first(s, until);
    if (pos >= 0) {
        s.data+=pos;
        s.size-=pos;
        get.size=pos;
    } else {
        s.data+=s.size;
        s.size = 0;
    }
    if(opt_get)
        *opt_get = get;
    return s;
}

// returns new str, based on s, without every least char until the char until.
// The cut is set into opt_get
static Str_s str_eat_back_until(Str_s s, char until, Str_s *opt_get) {
    Str_s get = s;
    ssize_t pos = str_find_last(s, until);
    if (pos >= 0) {
        s.size=pos;
        get.data+=pos;
        get.size-=pos;
    } else {
        s.size = 0;
    }
    if(opt_get)
        *opt_get = get;
    return s;
}

// returns new str, based on s, without every leading char until the str until.
// The cut is set into opt_get
static Str_s str_eat_until_str(Str_s s, Str_s until, Str_s *opt_get) {
    Str_s get = s;
    ssize_t pos = str_find_first_str(s, until);
    if (pos >= 0) {
        s.data+=pos;
        s.size-=pos;
        get.size=pos;
    } else {
        s.data+=s.size;
        s.size = 0;
    }
    if(opt_get)
        *opt_get = get;
    return s;
}

// returns new str, based on s, without every least char until the str until.
// The cut is set into opt_get
static Str_s str_eat_back_until_str(Str_s s, Str_s until, Str_s *opt_get) {
    Str_s get = s;
    ssize_t pos = str_find_last_str(s, until);
    if (pos >= 0) {
        s.size=pos;
        get.data+=pos;
        get.size-=pos;
    } else {
        s.size = 0;
    }
    if(opt_get)
        *opt_get = get;
    return s;
}

// returns new str, based on s, without every leading char until a char in set_until
// The cut is set into opt_get
static Str_s str_eat_until_set(Str_s s, const char *set_until, Str_s *opt_get) {
    Str_s get = s;
    ssize_t pos = str_find_first_set(s, set_until);
    if (pos >= 0) {
        s.data+=pos;
        s.size-=pos;
        get.size=pos;
    } else {
        s.data+=s.size;
        s.size = 0;
    }
    if(opt_get)
        *opt_get = get;
    return s;
}

// returns new str, based on s, without every least char until a char in set_until.
// The cut is set into opt_get
static Str_s str_eat_back_until_set(Str_s s, const char *set_until, Str_s *opt_get) {
    Str_s get = s;
    ssize_t pos = str_find_last_set(s, set_until);
    if (pos >= 0) {
        s.size=pos;
        get.data+=pos;
        get.size-=pos;
    } else {
        s.size = 0;
    }
    if(opt_get)
        *opt_get = get;
    return s;
}

// returns the number of char search, found in str
static size_t str_count(Str_s s, char search) {
    if(str_empty(s))
        return 0;
    size_t cnt = 0;
    if(search==' ') {
        for(size_t i=0; i<s.size; i++) {
            if(isspace(s.data[i]))
                cnt++;
        }
    } else {
        for(size_t i=0; i<s.size; i++) {
            if(s.data[i] == search)
                cnt++;
        }
    }
    return cnt;
}

// returns the number of str search, found in s
static size_t str_count_str(Str_s s, Str_s search) {
    if(s.size < search.size)
        return 0;
    size_t cnt = 0;
    for(size_t i=0; i<s.size-search.size; i++) {
        if(str_equals(search, (Str_s) {s.data+i, search.size}))
            cnt++;
    }
    return cnt;
}

// returns the number of a char in set_search, found in s
static size_t str_count_set(Str_s s, const char *set_search) {
    size_t cnt = 0;
    while(*set_search) {
        cnt += str_count(s, *set_search++);
    }
    return cnt;
}

// replaces each char old with replacement in the str s
static void str_replace(Str_s s, char old, char replacement) {
    if(str_empty(s))
        return;
    if(old==' ') {
        for(size_t i=0; i<s.size; i++) {
            if(isspace(s.data[i]))
                s.data[i] = replacement;
        }
    } else {
        for(size_t i=0; i<s.size; i++) {
            if(s.data[i] == old)
                s.data[i] = replacement;
        }
    }
}

// copies str s into buffer, with old -> replacement.
// the resulting str will be truncated to buffer.size
// returns the buffer with its new size
// have a look at string.h::string_new_replace_a for an allocated version
static Str_s str_replace_str_into(Str_s buffer, Str_s s, Str_s old, Str_s replacement) {
    if(str_empty(buffer) || str_empty(s) || str_empty(old) || !str_valid(replacement))
        return (Str_s) {buffer.data, 0};

    size_t b = 0;
    for(size_t i=0; i<s.size; i++) {
        if(s.size-i>=old.size && str_equals(old, (Str_s) {s.data+i, old.size})) {
            size_t cpy_size = buffer.size-b>=replacement.size? replacement.size : buffer.size-b;
            str_cpy((Str_s) {buffer.data+b, cpy_size}, (Str_s) {replacement.data, cpy_size});
            b += cpy_size;
        } else {
            if(b<buffer.size) {
                buffer.data[b] =s.data[i];
            }
            b++;
        }
    }
    return (Str_s) {buffer.data, b};
}

// runs tolower on each char in s and returns s
static Str_s str_tolower(Str_s s) {
    if(str_empty(s)) return s;
    for(size_t i=0; i<s.size; i++) {
        s.data[i] = (char) tolower(s.data[i]);
    }
    return s;
}

// runs toupper on each char in s and returns s
static Str_s str_toupper(Str_s s) {
    if(str_empty(s)) return s;
    for(size_t i=0; i<s.size; i++) {
        s.data[i] = (char) toupper(s.data[i]);
    }
    return s;
}

#endif //RHC_STR_H
