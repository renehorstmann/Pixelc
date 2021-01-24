#ifndef UTILC_STRVIU_H
#define UTILC_STRVIU_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

// helper functions:
static bool sv__helper_system_is_binary_little_endian_() {
    int n = 1;
    // little endian if true
    return *(char *) &n == 1;
}

static void sv__helper_swap_endian_(void *buf, int n) {
    char *buf_data = (char *) buf;
    char tmp[n];
    for (int i = 0; i < n; i++)
        tmp[i] = buf_data[n - i - 1];
    memcpy(buf_data, tmp, n);
}

/** Macro to create a StrViu from a cstring */
#define ToStrViu(string) ((strviu){(char*)(string), (char*)(string)+strlen((string))})

/** Data type for a string view instead of null termination, it uses an pointer to end (e. g. pointing to the 0) */
typedef struct {
    char *begin;
    char *end;
} strviu;

#define STRVIUARRAY_SIZE 128
/** Data type to store multiple StrViu's, limited to STRVIUARRAY_SIZE */
typedef struct {
    strviu array[128];
    int size;
} strviuarray;

/** Data type to store multiple StrViu's */
typedef struct {
    strviu *array;
    int size;
} StrViuArray;

/** StrViuArray destructor frees the array and sets to 0 */
static void StrViuArray_kill(StrViuArray *self) {
    free(self->array);
    self->array = NULL;
    self->size = 0;
}

/** Prints a strviu to stdout and returns its length */
static int sv_print(strviu viu) {
    int size = (viu.end > viu.begin) ? (viu.end - viu.begin) : 0;
    printf("(strviu) {%.*s}\n", size, viu.begin);
    return size;
}

/** @returns: true if the StrViu is empty (length==0) */
static bool sv_empty(strviu viu) {
    return viu.begin >= viu.end;
}

/** @returns: the length of the StrViu */
static int sv_length(strviu viu) {
    return (viu.end > viu.begin) ? (viu.end - viu.begin) : 0;
}

/** @returns: A new StrViu, based on viu, but without the leading chars of strip (space -> isspace()) */
static strviu sv_lstrip(strviu viu, char strip) {
    if (strip == ' ') {
        while (viu.begin < viu.end && isspace(*viu.begin))
            viu.begin++;
    } else {
        while (viu.begin < viu.end && *viu.begin == strip)
            viu.begin++;
    }
    return viu;
}

/** @returns: A new StrViu, based on viu, but without the least chars of strip (space -> isspace()) */
static strviu sv_rstrip(strviu viu, char strip) {
    if (strip == ' ') {
        while (viu.begin < viu.end && isspace(*(viu.end - 1)))
            viu.end--;
    } else {
        while (viu.begin < viu.end && *(viu.end - 1) == strip)
            viu.end--;
    }
    return viu;
}

/** @returns: A new StrViu, based on viu, but without the leading and least chars of strip (space -> isspace()) */
static strviu sv_strip(strviu viu, char strip) {
    return sv_lstrip(sv_rstrip(viu, strip), strip);
}

/** @returns: A new StrViu, based on viu, from the beginning until the first split, or the end*/
static strviu sv_next_split(strviu viu, char split) {
    strviu res = {viu.begin, viu.begin + 1};
    if (split == ' ') {
        while (res.end < viu.end && !isspace(*res.end))
            res.end++;
    } else {
        while (res.end < viu.end && *res.end != split)
            res.end++;
    }
    return res;
}

/** @returns: An StrViuArray, based on viu, containing all non empty splits between each split (limited autotype version) */
static strviuarray sv_split(strviu viu, char split) {
    strviuarray res = {0};
    for (;;) {
        viu = sv_lstrip(viu, split);
        if (sv_empty(viu))
            return res;
        strviu item = sv_next_split(viu, split);
        viu.begin = item.end;
        res.size++;
        if (res.size > STRVIUARRAY_SIZE) {
            res.size = -1;
            return res;
        }
        res.array[res.size - 1] = item;
    }
}

/** @returns: An StrViuArray, based on viu, containing all non empty splits between each split */
static StrViuArray sv_split_heap(strviu viu, char split) {
    StrViuArray res = {0};
    for (;;) {
        viu = sv_lstrip(viu, split);
        if (sv_empty(viu))
            return res;
        strviu item = sv_next_split(viu, split);
        viu.begin = item.end;
        res.array = (strviu *) realloc(res.array, ++res.size * sizeof(strviu));
        res.array[res.size - 1] = item;
    }
}

/** @returns: The index of the first found char find in viu, or -1 if nothing found */
static int sv_find_first(strviu viu, char find) {
    int n = 0;
    if (find == ' ') {
        while (viu.begin < viu.end) {
            if (isspace(*viu.begin++))
                return n;
            n++;
        }
    } else {
        while (viu.begin < viu.end) {
            if (*viu.begin++ == find)
                return n;
            n++;
        }
    }
    return -1;
}

/** @returns: The index of the last found char find in viu, or -1 if nothing found */
static int sv_find_last(strviu viu, char find) {
    int n = (int) sv_length(viu) - 1;
    if (find == ' ') {
        while (--viu.end >= viu.begin) {
            if (isspace(*viu.end))
                return n;
            n--;
        }
    } else {
        while (--viu.end >= viu.begin) {
            if (*viu.end == find)
                return n;
            n--;
        }
    }
    return -1;
}

/** @returns: The index of the first found StrViu find in viu, or -1 if nothing found */
static int sv_find_first_sv(strviu viu, strviu find) {
    int n = 0;
    int find_len = sv_length(find);
    while (viu.begin <= viu.end - find_len) {
        if (strncmp(viu.begin++, find.begin, find_len) == 0)
            return n;
        n++;
    }
    return -1;
}

/** @returns: The index of the last found StrViu find in viu, or -1 if nothing found */
static int sv_find_last_sv(strviu viu, strviu find) {
    int find_len = sv_length(find);
    viu.end -= find_len;
    int n = (int) sv_length(viu);
    while (viu.end >= viu.begin) {
        if (strncmp(viu.end--, find.begin, find_len) == 0)
            return n;
        n--;
    }
    return -1;
}

/** @returns: The index of the first found cstring find in viu, or -1 if nothing found */
static int sv_find_first_cstring(strviu viu, const char *find) {
    return sv_find_first_sv(viu, ToStrViu(find));
}

/** @returns: The index of the last found cstring find in viu, or -1 if nothing found */
static int sv_find_last_cstring(strviu viu, const char *find) {
    return sv_find_last_sv(viu, ToStrViu(find));
}

/** @returns: The index of the first found char of multiple_chars in viu, or -1 if nothing found */
static int sv_find_first_multiple(strviu viu, const char *multiple_chars) {
    int n = 0;
    while (viu.begin < viu.end) {
        for (const char *c = multiple_chars; *c != 0; c++) {
            if ((*c == ' ' && isspace(*viu.begin)) || *c == *viu.begin)
                return n;
        }
        viu.begin++;
        n++;
    }
    return -1;
}

/** @returns: The index of the last found char of multiple_chars in viu, or -1 if nothing found */
static int sv_find_last_multiple(strviu viu, const char *multiple_chars) {
    int n = (int) sv_length(viu) - 1;
    while (--viu.end >= viu.begin) {
        for (const char *c = multiple_chars; *c != 0; c++) {
            if ((*c == ' ' && isspace(*viu.end)) || *c == *viu.end)
                return n;
        }
        n--;
    }
    return -1;
}


/** @returns: A new StrViu, based on viu, without every leading char until the char until */
static strviu sv_eat_until(strviu viu, char until) {
    int pos = sv_find_first(viu, until);
    if (pos >= 0)
        viu.begin += pos;
    else
        viu.begin = viu.end;
    return viu;
}

/**
 * @returns: A new StrViu, based on viu, without every leading char until the char until. The cut is set into get
 */
static strviu sv_eat_get_until(strviu viu, char until, strviu *get) {
    get->begin = viu.begin;
    int pos = sv_find_first(viu, until);
    if (pos >= 0)
        viu.begin += pos;
    else
        viu.begin = viu.end;
    get->end = viu.begin;
    return viu;
}

/** @returns: A new StrViu, based on viu, without every tailing char until the char until */
static strviu sv_eat_back_until(strviu viu, char until) {
    int pos = sv_find_last(viu, until);
    if (pos >= 0)
        viu.end = viu.begin + pos + 1;
    else
        viu.end = viu.begin;
    return viu;
}

/** @returns: A new StrViu, based on viu, without every tailing char until the char until. The cut is set into get */
static strviu sv_eat_get_back_until(strviu viu, char until, strviu *get) {
    get->begin = viu.begin;
    int pos = sv_find_last(viu, until);
    if (pos >= 0)
        viu.end = viu.begin + pos + 1;
    else
        viu.end = viu.begin;
    get->end = viu.begin;
    return viu;
}

/** @returns: A new StrViu, based on viu, without every leading char until the StrViu until */
static strviu sv_eat_until_sv(strviu viu, strviu until) {
    int pos = sv_find_first_sv(viu, until);
    if (pos >= 0)
        viu.begin += pos;
    else
        viu.begin = viu.end;
    return viu;
}

/** @returns: A new StrViu, based on viu, without every leading char until the StrViu until. The cut is set into get */
static strviu sv_eat_get_until_sv(strviu viu, strviu until, strviu *get) {
    get->begin = viu.begin;
    int pos = sv_find_first_sv(viu, until);
    if (pos >= 0)
        viu.begin += pos;
    else
        viu.begin = viu.end;
    get->end = viu.begin;
    return viu;
}

/** @returns: A new StrViu, based on viu, without every tailing char until the StrViu until */
static strviu sv_eat_back_until_sv(strviu viu, strviu until) {
    int pos = sv_find_last_sv(viu, until);
    if (pos >= 0)
        viu.end = viu.begin + pos + sv_length(until);
    else
        viu.end = viu.begin;
    return viu;
}

/** @returns: A new StrViu, based on viu, without every tailing char until the StrViu until. The cut is set into get */
static strviu sv_eat_get_back_until_sv(strviu viu, strviu until, strviu *get) {
    get->begin = viu.begin;
    int pos = sv_find_last_sv(viu, until);
    if (pos >= 0)
        viu.end = viu.begin + pos + sv_length(until);
    else
        viu.end = viu.begin;
    get->end = viu.begin;
    return viu;
}

/** @returns: A new StrViu, based on viu, without every leading char until the cstring until */
static strviu sv_eat_until_cstring(strviu viu, const char *until) {
    return sv_eat_until_sv(viu, ToStrViu(until));
}

/** @returns: A new StrViu, based on viu, without every leading char until the cstring until. The cut is set into get */
static strviu sv_eat_get_until_cstring(strviu viu, const char *until, strviu *get) {
    return sv_eat_get_until_sv(viu, ToStrViu(until), get);
}

/** @returns: A new StrViu, based on viu, without every tailing char until the cstring until */
static strviu sv_eat_back_until_cstring(strviu viu, const char *until) {
    return sv_eat_back_until_sv(viu, ToStrViu(until));
}

/** @returns: A new StrViu, based on viu, without every tailing char until the cstring until. The cut is set into get */
static strviu sv_eat_get_back_until_cstring(strviu viu, const char *until, strviu *get) {
    return sv_eat_get_back_until_sv(viu, ToStrViu(until), get);
}

/** @returns: A new StrViu, based on viu, without every leading char until one of the chars in multiple_chars */
static strviu sv_eat_until_multiple(strviu viu, const char *multiple_chars) {
    int pos = sv_find_first_multiple(viu, multiple_chars);
    if (pos >= 0)
        viu.begin += pos;
    else
        viu.begin = viu.end;
    return viu;
}

/** @returns: A new StrViu, based on viu, without every leading char until one of the chars in multiple_chars. The cut is set into get */
static strviu sv_eat_get_until_multiple(strviu viu, const char *multiple_chars, strviu *get) {
    get->begin = viu.begin;
    int pos = sv_find_first_multiple(viu, multiple_chars);
    if (pos >= 0)
        viu.begin += pos;
    else
        viu.begin = viu.end;
    get->end = viu.begin;
    return viu;
}

/** @returns: A new StrViu, based on viu, without every tailing char until one of the chars in multiple_chars */
static strviu sv_eat_back_until_multiple(strviu viu, const char *multiple_chars) {
    int pos = sv_find_last_multiple(viu, multiple_chars);
    if (pos >= 0)
        viu.end = viu.begin + pos + 1;
    else
        viu.end = viu.begin;
    return viu;
}

/** @returns: A new StrViu, based on viu, without every tailing char until one of the chars in multiple_chars. The cut is set into get */
static strviu sv_eat_get_back_until_multiple(strviu viu, const char *multiple_chars, strviu *get) {
    get->begin = viu.begin;
    int pos = sv_find_last_multiple(viu, multiple_chars);
    if (pos >= 0)
        viu.end = viu.begin + pos + 1;
    else
        viu.end = viu.begin;
    get->end = viu.begin;
    return viu;
}

/** @returns: The number of the char search, found in viu */
static int sv_count(strviu viu, char search) {
    int cnt = 0;
    if (search == ' ') {
        while (viu.begin < viu.end) {
            if (isspace(*viu.begin++))
                cnt++;
        }
    } else {
        while (viu.begin < viu.end) {
            if (*viu.begin++ == search)
                cnt++;
        }
    }
    return cnt;
}

/** @returns: The number of the StrViu search, found in viu */
static int sv_count_sv(strviu viu, strviu search) {
    int cnt = 0;
    int search_len = sv_length(search);
    while (viu.begin <= viu.end - search_len) {
        if (strncmp(viu.begin++, search.begin, search_len) == 0)
            cnt++;
    }
    return cnt;
}

/** @returns: The number of the cstring search, found in viu */
static int sv_count_cstring(strviu viu, const char *search) {
    return sv_count_sv(viu, ToStrViu(search));
}

/** @returns: The number of each char in multiple_chars, found in viu */
static int sv_count_multiple(strviu viu, const char *multiple_chars) {
    int cnt = 0;
    while (*multiple_chars)
        cnt += sv_count(viu, *multiple_chars++);
    return cnt;
}

/** Replaces each char old with replacement in the StrViu viu */
static void sv_replace(strviu viu, char old, char replacement) {
    while (viu.begin < viu.end) {
        if (*viu.begin == old)
            *viu.begin = replacement;
    }
}

/** Copies the StrViu viu to dst, with each StrViu old replaced to replacement (until the end of one is reached) */
static void sv_replace_into_sv(strviu dst, strviu viu, strviu old, strviu replacement) {
    int old_len = sv_length(old);
    int repl_len = sv_length(replacement);
    while (dst.begin < dst.end && viu.begin < viu.end) {
        if (strncmp(viu.begin, old.begin, old_len) == 0) {
            int n = sv_length(dst) < repl_len ? sv_length(dst) : repl_len;
            strncpy(dst.begin, replacement.begin, n);
            dst.begin += n;
            viu.begin += old_len;
        } else
            *dst.begin++ = *viu.begin++;
    }
    while (dst.begin < dst.end)
        *dst.begin++ = 0;
}

/** Copies the StrViu viu to dst, with each cstring old replaced to replacement (until the end of one is reached) */
static void sv_replace_into_cstring(strviu dst, strviu viu, const char *old, const char *replacement) {
    sv_replace_into_sv(dst, viu, ToStrViu(old), ToStrViu(replacement));
}

/**
 * @returns: A new cstring on the heap, copied from viu to dst,
 * with each StrViu old replaced to replacement
 */
static char *sv_replace_to_heap_sv(strviu viu, strviu old, strviu replacement) {
    int old_len = sv_length(old);
    int repl_len = sv_length(replacement);
    int size = sv_length(viu) + 1;
    int add_size = repl_len > 128 ? repl_len : 128;
    char *res = (char *) malloc(size);
    if (!res)
        return NULL;
    int n = 0;
    while (viu.begin < viu.end) {
        if (strncmp(viu.begin, old.begin, old_len) == 0) {
            if (size <= n + repl_len) {
                size += add_size;
                char *r = (char *) realloc(res, size);
                if (!r) {
                    free(res);
                    return NULL;
                }
                res = r;
            }
            strncpy(res + n, replacement.begin, repl_len);
            viu.begin += old_len;
            n += repl_len;
        } else {
            res[n] = *viu.begin++;
            if (++n >= size) {
                size += add_size;
                char *r = (char *) realloc(res, size);
                if (!r) {
                    free(res);
                    return NULL;
                }
                res = r;
            }
        }
    }
    res[n] = 0; // ?
    return res;
}

/**
 * @returns: A new cstring on the heap, copied from viu to dst,
 * with each cstring old replaced to replacement
 */
static char *sv_replace_to_heap_cstring(strviu viu, const char *old, const char *replacement) {
    return sv_replace_to_heap_sv(viu, ToStrViu(old), ToStrViu(replacement));
}


/** Copies the StrViu viu into the cstring dst */
static void sv_cpy(char *dst, strviu viu) {
    int len = sv_length(viu);
    strncpy(dst, viu.begin, len);
    dst[len] = 0;
}

/** Concatenates viu behind dst */
static void sv_cat(char *dst, strviu viu) {
    sv_cpy(dst + strlen(dst), viu);
}

/** Copies the StrViu viu into the cstring dst, but maximal max_buffer_n wide */
static void sv_ncpy(char *dst, strviu viu, int max_buffer_n) {
    int len = sv_length(viu) < max_buffer_n ? sv_length(viu) : max_buffer_n-1;
    strncpy(dst, viu.begin, len);
    dst[len] = 0;
}

/** Concatenates viu behind dst, but maximal max_buffer_n wide for the whole string */
static void sv_ncat(char *dst, strviu viu, int max_buffer_n) {
    int max_viu = max_buffer_n - strlen(dst);
    sv_ncpy(dst + strlen(dst), viu, max_viu);
}

/** @return: The StrViu viu into a cstring on the heap */
static char *sv_heap_cpy(strviu viu) {
    char *str = (char *) malloc(sv_length(viu) + 1);
    sv_cpy(str, viu);
    return str;
}

/** @return: True if viu contains the same chars as cmp */
static bool sv_equals(strviu viu, strviu cmp) {
    if (sv_length(viu) != sv_length(cmp))
        return false;
    return strncmp(viu.begin, cmp.begin, sv_length(cmp)) == 0;
}

/** @return: True if viu contains the same chars as cmp */
static bool sv_equals_cstring(strviu viu, const char *cmp) {
    return sv_equals(viu, ToStrViu(cmp));
}

/** @return: True if viu begins with the string of cmp */
static bool sv_begins_with(strviu viu, strviu cmp) {
    if (sv_length(viu) < sv_length(cmp))
        return false;
    return strncmp(viu.begin, cmp.begin, sv_length(cmp)) == 0;
}

/** @return: True if viu begins with the string of cmp */
static bool sv_begins_with_cstring(strviu viu, const char *cmp) {
    return sv_begins_with(viu, ToStrViu(cmp));
}

/** @return: True if viu ends with the string of cmp */
static bool sv_ends_with(strviu viu, strviu cmp) {
    if (sv_length(viu) < sv_length(cmp))
        return false;
    int len = sv_length(cmp);
    return strncmp(viu.end - len, cmp.begin, len) == 0;
}

/** @return: True if viu ends with the string of cmp */
static bool sv_ends_with_cstring(strviu viu, const char *cmp) {
    return sv_ends_with(viu, ToStrViu(cmp));
}

/** Sets all characters in the string to lower chars */
static void sv_tolower(strviu viu) {
    while (viu.begin < viu.end) {
        *viu.begin = (char) tolower(*viu.begin);
        viu.begin++;
    }
}

/** Sets all characters in the string to upper chars */
static void sv_toupper(strviu viu) {
    while (viu.begin < viu.end) {
        *viu.begin = (char) toupper(*viu.begin);
        viu.begin++;
    }
}


#endif //UTILC_STRVIU_H

