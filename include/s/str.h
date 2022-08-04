#ifndef S_STR_H
#define S_STR_H

//
// functions working on a data view
//

#include "export.h"
#include "error.h"
#include "log.h"
#include "str_type.h"

struct sStream_i;

//
// Functions
//


// sStr_s from a c string
static sStr_s s_strc(const char *cstring) {
    return (sStr_s) {(char *) cstring, strlen(cstring)};
}

// returns true if the str is empty
static bool s_str_empty(sStr_s s) {
    return !s.data || s.size <= 0;
}

// prints the str to a stream
// as f.e.: "(sStr_s) {"hello world", 11}\n"
// returns the amount of printed characters
S_EXPORT
ssize s_str_stream_print(sStr_s str, struct sStream_i stream);

// prints the str to stdoud
// as f.e.: "(sStr_s) {"hello world", 11}\n"
// returns the amount of printed characters
S_EXPORT
ssize s_str_print(sStr_s s);

// copies from into cpy. cpy and from must have the same size
static void s_str_cpy(sStr_s cpy, sStr_s from) {
    if(!s_str_valid(cpy) || !s_str_valid(from) || cpy.size != from.size) {
        s_error_set("s_str_cpy failed");
        s_log_error("s_str_cpy failed: invalid or wrong sizes");
        return;
    }
    memcpy(cpy.data, from.data, cpy.size);
}

// copies from into cpy_buffer. cpy_buffer must have at least the size of from
// returns cpy_buffer with the copied size of from
static sStr_s s_str_cpy_into(sStr_s cpy_buffer, sStr_s from) {
    if(!s_str_valid(cpy_buffer) || !s_str_valid(from) || cpy_buffer.size < from.size) {
        s_error_set("s_str_cpy_info failed");
        s_log_error("s_str_cpy_into failed: invalid or wrong sizes");
        return (sStr_s) {cpy_buffer.data, 0};
    }
    cpy_buffer.size = from.size;
    s_str_cpy(cpy_buffer, from);
    return cpy_buffer;
}

// returns true if the strs are equal
static bool s_str_equals(sStr_s a, sStr_s b) {
    if(!s_str_valid(a) || !s_str_valid(b) || a.size != b.size)
        return false;
    if(s_str_empty(a) && s_str_empty(b))
        return true;
    return memcmp(a.data, b.data, a.size) == 0;
}

// out_c_string needs to be a buffer of at least str.size+1
static void s_str_as_c(char *out_c_string, sStr_s s) {
    if(!s_str_valid(s)) {
        out_c_string[0] = '\0';
        return;
    }
    memcpy(out_c_string, s.data, s.size);
    out_c_string[s.size] = '\0';
}

// returns a new allocated buffer with str as cstring
static char *s_str_as_new_c_a(sStr_s s, sAllocator_i a) {
    s_assume(s_allocator_valid(a), "a needs to be valid");
    if(!s_str_valid(s))
        return NULL;
    char *buffer = s_a_malloc(a, s.size + 1);
    if(!buffer)
        return NULL;
    s_str_as_c(buffer, s);
    return buffer;
}


// returns a new allocated buffer with str as cstring
static char *s_str_as_new_c(sStr_s s) {
    return s_str_as_new_c_a(s, S_ALLOCATOR_DEFAULT);
}


// returns true if str begins with cmp
static bool s_str_begins_with(sStr_s s, sStr_s cmp) {
    if(!s_str_valid(s) || s_str_empty(cmp) || s.size < cmp.size)
        return false;
    return s_str_equals(cmp, (sStr_s) {s.data, cmp.size});
}

// returns true if str ends with cmp
static bool s_str_ends_with(sStr_s s, sStr_s cmp) {
    if(!s_str_valid(s) || s_str_empty(cmp) || s.size < cmp.size)
        return false;
    return s_str_equals(cmp, (sStr_s) {s.data + s.size - cmp.size, cmp.size});
}

// returns a new str, based on s, but without the leading chars of strip (space -> isspace())
static sStr_s s_str_lstrip(sStr_s s, char strip) {
    // invalid safe
    if(strip==' ') {
        while (!s_str_empty(s) && isspace(*s.data)) {
            s.data++;
            s.size--;
        }
    } else {
        while (!s_str_empty(s) && *s.data == strip) {
            s.data++;
            s.size--;
        }
    }
    return s;
}

// returns a new str, based on s, but without the least chars of strip (space -> isspace())
static sStr_s s_str_rstrip(sStr_s s, char strip) {
    // invalid safe
    if(strip==' ') {
        while (!s_str_empty(s) && isspace(s.data[s.size-1])) {
            s.size--;
        }
    } else {
        while (!s_str_empty(s) && s.data[s.size-1] == strip) {
            s.size--;
        }
    }
    return s;
}

// returns a new str, based on s, but without the leading and least chars of strip (space -> isspace())
static sStr_s s_str_strip(sStr_s s, char strip) {
    return s_str_lstrip(s_str_rstrip(s, strip), strip);
}

// a new str, based on s, from the beginning until the first split, or the end
static sStr_s s_str_next_split(sStr_s s, char split) {
    if(s_str_empty(s))
        return s_str_new_invalid();
    sStr_s res = {s.data, 0};
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
static int s_str_split(sStr_s *splits, int max, sStr_s s, char split) {
    // invalid safe
    int n = 0;
    for (;;) {
        s = s_str_lstrip(s, split);
        if (s_str_empty(s))
            return n;
        sStr_s item = s_str_next_split(s, split);
        s.data += item.size;
        s.size -= item.size;
        splits[n++] = item;
        if (n >= max) {
            s_log_warn("s_str_split: reached max: %d/%d", n, max);
            return n;
        }
    }
}

// returns a str array, based on s, containing all non empty splits between each split (allocated version)
static sStrArray s_str_split_allocated(sStr_s s, char split, sAllocator_i a) {
    sStrArray res = {.allocator = a};
    s_assume(s_allocator_valid(a), "a needs to be valid");
    for (;;) {
        s = s_str_lstrip(s, split);
        if (s_str_empty(s))
            return res;
        sStr_s item = s_str_next_split(s, split);
        s.data += item.size;
        s.size -= item.size;
        sStr_s *array = s_a_renew(a, sStr_s, res.array, res.size + 1);
        if(!array) {
            s_log_warn("s_str_split_allocated failed: to realloc");
            return res;
        }
        res.array = array;
        res.array[res.size++] = item;
    }
}

// returns the index of the first found char find in str, or -1 if nothing found
static ssize s_str_find_first(sStr_s s, char find) {
    if(s_str_empty(s))
        return -1;
    if (find==' ') {
        for(ssize i=0; i < s.size; i++) {
            if(isspace(s.data[i]))
                return (ssize) i;
        }
    } else {
        for(ssize i=0; i < s.size; i++) {
            if(s.data[i] == find)
                return (ssize) i;
        }
    }
    return -1;
}


// returns the index of the last found char find in str, or -1 if nothing found
static ssize s_str_find_last(sStr_s s, char find) {
    if(s_str_empty(s))
        return -1;
    if (find==' ') {
        for(ssize i=s.size; i > 0; i--) {
            if(isspace(s.data[i-1]))
                return (ssize) i - 1;
        }
    } else {
        for(ssize i=s.size; i > 0; i--) {
            if(s.data[i-1] == find)
                return (ssize) i - 1;
        }
    }
    return -1;
}

// returns the index of the first found str found in s, or -1 if nothing found
static ssize s_str_find_first_str(sStr_s s, sStr_s find) {
    // invalid safe
    if(find.size > s.size)
        return -1;
    for(ssize i=0; i < s.size - find.size; i++) {
        if(s_str_equals(find, (sStr_s) {s.data + i, find.size}))
            return (ssize) i;
    }
    return -1;
}

// returns the index of the last found str found in s, or -1 if nothing found
static ssize s_str_find_last_str(sStr_s s, sStr_s find) {
    // invalid safe
    if(find.size > s.size)
        return -1;
    for(ssize i= s.size - find.size; i > 0; i--) {
        if(s_str_equals(find, (sStr_s) {s.data + i - 1, find.size}))
            return (ssize) i;
    }
    return -1;
}

// returns the index of the first found char of multiple_chars in str, or -1 if nothing found
static ssize s_str_find_first_set(sStr_s s, const char *char_set) {
    for(ssize i=0; i < s.size; i++) {
        for (const char *c = char_set; *c != 0; c++) {
            if ((*c == ' ' && isspace(s.data[i])) || *c == s.data[i])
                return (ssize) i;
        }
    }
    return -1;
}
// returns the index of the first found char of multiple_chars in str, or -1 if nothing found
static ssize s_str_find_last_set(sStr_s s, const char *char_set) {
    for(ssize i=s.size; i > 0; i--) {
        for (const char *c = char_set; *c != 0; c++) {
            if ((*c == ' ' && isspace(s.data[i-1])) || *c == s.data[i-1])
                return (ssize) i - 1;
        }
    }
    return -1;
}

// returns new str, based on s, but missing the first n characters
static sStr_s s_str_eat(sStr_s s, ssize n) {
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
static sStr_s s_str_eat_back(sStr_s s, ssize n) {
    if(n>=s.size) {
        s.size = 0;
    } else {
        s.size -= n;
    }
    return s;
}

// checks if s begins with eat_begin and returns a new str, based on s, without eat_begin at the beginning
// if s does not begin with eat_begin, an invalid str is returned
static sStr_s s_str_eat_str(sStr_s s, sStr_s eat_begin) {
    if(!s_str_begins_with(s, eat_begin))
        return s_str_new_invalid();
    s.data+=eat_begin.size;
    s.size-=eat_begin.size;
    return s;
}

// checks if s ends with eat_back and returns a new str, based on s, without eat_back at the end
// if s does not end with eat_back, an invalid str is returned
static sStr_s s_str_eat_back_str(sStr_s s, sStr_s eat_back) {
    if(!s_str_ends_with(s, eat_back))
        return s_str_new_invalid();
    s.size-=eat_back.size;
    return s;
}

// returns new str, based on s, without every leading char until the char until.
// The cut is set into opt_get
static sStr_s s_str_eat_until(sStr_s s, char until, sStr_s *opt_get) {
    sStr_s get = s;
    ssize pos = s_str_find_first(s, until);
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
static sStr_s s_str_eat_back_until(sStr_s s, char until, sStr_s *opt_get) {
    sStr_s get = s;
    ssize pos = s_str_find_last(s, until);
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
static sStr_s s_str_eat_until_str(sStr_s s, sStr_s until, sStr_s *opt_get) {
    sStr_s get = s;
    ssize pos = s_str_find_first_str(s, until);
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
static sStr_s s_str_eat_back_until_str(sStr_s s, sStr_s until, sStr_s *opt_get) {
    sStr_s get = s;
    ssize pos = s_str_find_last_str(s, until);
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
static sStr_s s_str_eat_until_set(sStr_s s, const char *set_until, sStr_s *opt_get) {
    sStr_s get = s;
    ssize pos = s_str_find_first_set(s, set_until);
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
static sStr_s s_str_eat_back_until_set(sStr_s s, const char *set_until, sStr_s *opt_get) {
    sStr_s get = s;
    ssize pos = s_str_find_last_set(s, set_until);
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
static ssize s_str_count(sStr_s s, char search) {
    if(s_str_empty(s))
        return 0;
    ssize cnt = 0;
    if(search==' ') {
        for(ssize i=0; i < s.size; i++) {
            if(isspace(s.data[i]))
                cnt++;
        }
    } else {
        for(ssize i=0; i < s.size; i++) {
            if(s.data[i] == search)
                cnt++;
        }
    }
    return cnt;
}

// returns the number of str search, found in s
static ssize s_str_count_str(sStr_s s, sStr_s search) {
    if(s.size < search.size)
        return 0;
    ssize cnt = 0;
    for(ssize i=0; i < s.size - search.size; i++) {
        if(s_str_equals(search, (sStr_s) {s.data + i, search.size}))
            cnt++;
    }
    return cnt;
}

// returns the number of a char in set_search, found in s
static ssize s_str_count_set(sStr_s s, const char *set_search) {
    ssize cnt = 0;
    while(*set_search) {
        cnt += s_str_count(s, *set_search++);
    }
    return cnt;
}

// replaces each char old with replacement in the str s
static void s_str_replace(sStr_s s, char old, char replacement) {
    if(s_str_empty(s))
        return;
    if(old==' ') {
        for(ssize i=0; i < s.size; i++) {
            if(isspace(s.data[i]))
                s.data[i] = replacement;
        }
    } else {
        for(ssize i=0; i < s.size; i++) {
            if(s.data[i] == old)
                s.data[i] = replacement;
        }
    }
}

// copies str s into buffer, with old -> replacement.
// the resulting str will be truncated to buffer.size
// returns the buffer with its new size
// have a look at string.h::s_string_new_replace_a for an allocated version
static sStr_s s_str_replace_str_into(sStr_s buffer, sStr_s s, sStr_s old, sStr_s replacement) {
    if(s_str_empty(buffer) || s_str_empty(s) || s_str_empty(old) || !s_str_valid(replacement))
        return (sStr_s) {buffer.data, 0};

    ssize b = 0;
    for(ssize i=0; i < s.size; i++) {
        if(s.size-i>=old.size && s_str_equals(old, (sStr_s) {s.data + i, old.size})) {
            ssize cpy_size = buffer.size - b >= replacement.size ? replacement.size : buffer.size - b;
            s_str_cpy((sStr_s) {buffer.data + b, cpy_size}, (sStr_s) {replacement.data, cpy_size});
            b += cpy_size;
        } else {
            if(b<buffer.size) {
                buffer.data[b] =s.data[i];
            }
            b++;
        }
    }
    return (sStr_s) {buffer.data, b};
}

// runs tolower on each char in s and returns s
static sStr_s s_str_tolower(sStr_s s) {
    if(s_str_empty(s)) return s;
    for(ssize i=0; i < s.size; i++) {
        s.data[i] = (char) tolower(s.data[i]);
    }
    return s;
}

// runs toupper on each char in s and returns s
static sStr_s s_str_toupper(sStr_s s) {
    if(s_str_empty(s)) return s;
    for(ssize i=0; i < s.size; i++) {
        s.data[i] = (char) toupper(s.data[i]);
    }
    return s;
}

#endif //S_STR_H
