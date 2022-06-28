#ifndef S_STR_PARSE_H
#define S_STR_PARSE_H

//
// special str functions to read and write to little or big endian
//

#include "endian.h"
#include "str.h"

//
// ascii
//

// eats the next (with leading spaces) int_x_t and returns the str without it.
#define S__STR_PARSE_HELPER_EAT_IX_ASCII_PROTOTYPE_(x)\
static sStr_s str_eat_i ## x ## _ascii(sStr_s s, si ## x *opt_eaten) {\
    if(s_str_empty(s))\
        return s;\
    char *end;\
    long long int res = strtoll(s.data, &end, 0);\
    ssize ate_size = end - s.data;\
    if(ate_size <= 0 || ate_size > s.size) {\
        s_error_set("str_eat_int_ascii failed");\
        s_log_warn("str_eat_i" #x "_ascii: failed");\
        return s_str_new_invalid();\
    }\
    if(opt_eaten)\
        *opt_eaten = (si ## x) res;\
    return (sStr_s) {s.data+ate_size, s.size-ate_size};\
}

S__STR_PARSE_HELPER_EAT_IX_ASCII_PROTOTYPE_(8)

S__STR_PARSE_HELPER_EAT_IX_ASCII_PROTOTYPE_(16)

S__STR_PARSE_HELPER_EAT_IX_ASCII_PROTOTYPE_(32)

S__STR_PARSE_HELPER_EAT_IX_ASCII_PROTOTYPE_(64)


// eats the next (with leading spaces) uint_x_t and returns the str without it.
#define S__STR_PARSE_HELPER_EAT_UX_ASCII_PROTOTYPE_(x)\
static sStr_s str_eat_u ## x ## _ascii(sStr_s s, su ## x *opt_eaten) {\
    if(s_str_empty(s))\
        return s;\
    char *end;\
    unsigned long long int res = strtoull(s.data, &end, 0);\
    ssize ate_size = end - s.data;\
    if(ate_size <= 0 || ate_size > s.size) {\
        s_error_set("str_eat_uint_ascii failed");\
        s_log_warn("str_eat_u" #x "_ascii: failed");\
        return s_str_new_invalid();\
    }\
    if(opt_eaten)\
        *opt_eaten = (su ## x ) res;\
    return (sStr_s) {s.data+ate_size, s.size-ate_size};\
}

S__STR_PARSE_HELPER_EAT_UX_ASCII_PROTOTYPE_(8)

S__STR_PARSE_HELPER_EAT_UX_ASCII_PROTOTYPE_(16)

S__STR_PARSE_HELPER_EAT_UX_ASCII_PROTOTYPE_(32)

S__STR_PARSE_HELPER_EAT_UX_ASCII_PROTOTYPE_(64)


// eats the next (with leading spaces) f32 and returns the str without it.
static sStr_s str_eat_f32_ascii(sStr_s s, sf32 *opt_eaten) {
    if (s_str_empty(s))
        return s;
    char *end;
    sf64 res = strtod(s.data, &end);
    ssize ate_size = end - s.data;
    if (ate_size <= 0 || ate_size > s.size) {
        s_error_set("str_eat_f32_ascii failed");
        s_log_warn("str_eat_f32_ascii: failed");
        return s_str_new_invalid();
    }
    if (opt_eaten)
        *opt_eaten = (sf32) res;
    return (sStr_s) {s.data + ate_size, s.size - ate_size};
}

// eats the next (with leading spaces) f64 and returns the str without it.
static sStr_s str_eat_f64_ascii(sStr_s s, sf64 *opt_eaten) {
    if (s_str_empty(s))
        return s;
    char *end;
    sf64 res = strtod(s.data, &end);
    ssize ate_size = end - s.data;
    if (ate_size <= 0 || ate_size > s.size) {
        s_error_set("str_eat_f64_ascii failed");
        s_log_warn("str_eat_f64_ascii: failed");
        return s_str_new_invalid();
    }
    if (opt_eaten)
        *opt_eaten = (sf64) res;
    return (sStr_s) {s.data + ate_size, s.size - ate_size};
}


//
// binary
//

// eats the next intx_t as binary little endian and returns the str without it.
#define S__STR_PARSE_HELPER_EAT_IX_BINARY_LE_PROTOTPYE_(x)\
static sStr_s str_eat_i ## x ## _binary_le(sStr_s s, si ## x *opt_eaten) {\
    if(s_str_empty(s))\
        return s;\
    if(s.size < (x)/8) {\
        s_error_set("str_eat_int_binary_le failed");\
        s_log_warn("str_eat_i" #x "_binary_le: failed");\
        return s_str_new_invalid();\
    }\
    if(opt_eaten){\
        memcpy(opt_eaten, s.data, (x)/8);\
        if(!s_endian_system_is_binary_little_endian())\
            s_endian_swap(opt_eaten, (x)/8);\
    }\
    s.data += (x)/8;\
    s.size -= (x)/8;\
    return s;\
}

S__STR_PARSE_HELPER_EAT_IX_BINARY_LE_PROTOTPYE_(8)

S__STR_PARSE_HELPER_EAT_IX_BINARY_LE_PROTOTPYE_(16)

S__STR_PARSE_HELPER_EAT_IX_BINARY_LE_PROTOTPYE_(32)

S__STR_PARSE_HELPER_EAT_IX_BINARY_LE_PROTOTPYE_(64)

// eats the next intx_t as binary big endian and returns the str without it.
#define S__STR_PARSE_HELPER_EAT_IX_BINARY_BE_PROTOTPYE_(x)\
static sStr_s str_eat_i ## x ## _binary_be(sStr_s s, si ## x *opt_eaten) {\
    if(s_str_empty(s))\
        return s;\
    if(s.size < (x)/8) {\
        s_error_set("str_eat_int_binary_be failed");\
        s_log_warn("str_eat_i" #x "_binary_be: failed");\
        return s_str_new_invalid();\
    }\
    if(opt_eaten){\
        memcpy(opt_eaten, s.data, (x)/8);\
        if(s_endian_system_is_binary_little_endian())\
            s_endian_swap(opt_eaten, (x)/8);\
    }\
    s.data += (x)/8;\
    s.size -= (x)/8;\
    return s;\
}

S__STR_PARSE_HELPER_EAT_IX_BINARY_BE_PROTOTPYE_(8)

S__STR_PARSE_HELPER_EAT_IX_BINARY_BE_PROTOTPYE_(16)

S__STR_PARSE_HELPER_EAT_IX_BINARY_BE_PROTOTPYE_(32)

S__STR_PARSE_HELPER_EAT_IX_BINARY_BE_PROTOTPYE_(64)

// eats the next uintx_t as binary little endian and returns the str without it.
#define S__STR_PARSE_HELPER_EAT_UX_BINARY_LE_PROTOTPYE_(x)\
static sStr_s str_eat_u ## x ## _binary_le(sStr_s s, su ## x *opt_eaten) {\
    if(s_str_empty(s))\
        return s;\
    if(s.size < (x)/8) {\
        s_error_set("str_eat_uint_binary_le failed");\
        s_log_warn("str_eat_u" #x "_binary_le: failed");\
        return s_str_new_invalid();\
    }\
    if(opt_eaten){\
        memcpy(opt_eaten, s.data, (x)/8);\
        if(!s_endian_system_is_binary_little_endian())\
            s_endian_swap(opt_eaten, (x)/8);\
    }\
    s.data += (x)/8;\
    s.size -= (x)/8;\
    return s;\
}

S__STR_PARSE_HELPER_EAT_UX_BINARY_LE_PROTOTPYE_(8)

S__STR_PARSE_HELPER_EAT_UX_BINARY_LE_PROTOTPYE_(16)

S__STR_PARSE_HELPER_EAT_UX_BINARY_LE_PROTOTPYE_(32)

S__STR_PARSE_HELPER_EAT_UX_BINARY_LE_PROTOTPYE_(64)

// eats the next uintx_t as binary big endian and returns the str without it.
#define S__STR_PARSE_HELPER_EAT_UX_BINARY_BE_PROTOTPYE_(x)\
static sStr_s str_eat_u ## x ## _binary_be(sStr_s s, su ## x *opt_eaten) {\
    if(s_str_empty(s))\
        return s;\
    if(s.size < (x)/8) {\
        s_error_set("str_eat_uint_binary_be failed");\
        s_log_warn("str_eat_u" #x "_binary_be: failed");\
        return s_str_new_invalid();\
    }\
    if(opt_eaten){\
        memcpy(opt_eaten, s.data, (x)/8);\
        if(s_endian_system_is_binary_little_endian())\
            s_endian_swap(opt_eaten, (x)/8);\
    }\
    s.data += (x)/8;\
    s.size -= (x)/8;\
    return s;\
}

S__STR_PARSE_HELPER_EAT_UX_BINARY_BE_PROTOTPYE_(8)

S__STR_PARSE_HELPER_EAT_UX_BINARY_BE_PROTOTPYE_(16)

S__STR_PARSE_HELPER_EAT_UX_BINARY_BE_PROTOTPYE_(32)

S__STR_PARSE_HELPER_EAT_UX_BINARY_BE_PROTOTPYE_(64)


// eats the next f32 as binary little endian and returns the str without it.
static sStr_s str_eat_f32_binary_le(sStr_s s, sf32 *opt_eaten) {
    if (s_str_empty(s))
        return s;
    if (s.size < 4) {
        s_error_set("str_eat_f32_binary_le failed");
        s_log_warn("str_eat_f32_binary_le: failed");
        return s_str_new_invalid();
    }
    if (opt_eaten) {
        memcpy(opt_eaten, s.data, 4);
        if (!s_endian_system_is_binary_little_endian())
            s_endian_swap(opt_eaten, 4);
    }
    s.data += 4;
    s.size -= 4;
    return s;
}

// eats the next f32 as binary big endian and returns the str without it.
static sStr_s str_eat_f32_binary_be(sStr_s s, sf32 *opt_eaten) {
    if (s_str_empty(s))
        return s;
    if (s.size < 4) {
        s_error_set("str_eat_f32_binary_be failed");
        s_log_warn("str_eat_f32_binary_be: failed");
        return s_str_new_invalid();
    }
    if (opt_eaten) {
        memcpy(opt_eaten, s.data, 4);
        if (s_endian_system_is_binary_little_endian())
            s_endian_swap(opt_eaten, 4);
    }
    s.data += 4;
    s.size -= 4;
    return s;
}


// eats the next f64 as binary little endian and returns the str without it.
static sStr_s str_eat_f64_binary_le(sStr_s s, sf64 *opt_eaten) {
    if (s_str_empty(s))
        return s;
    if (s.size < 8) {
        s_error_set("str_eat_f64_binary_le failed");
        s_log_warn("str_eat_f64_binary_le: failed");
        return s_str_new_invalid();
    }
    if (opt_eaten) {
        memcpy(opt_eaten, s.data, 8);
        if (!s_endian_system_is_binary_little_endian())
            s_endian_swap(opt_eaten, 8);
    }
    s.data += 8;
    s.size -= 8;
    return s;
}

// eats the next f64 as binary big endian and returns the str without it.
static sStr_s str_eat_f64_binary_be(sStr_s s, sf64 *opt_eaten) {
    if (s_str_empty(s))
        return s;
    if (s.size < 8) {
        s_error_set("str_eat_f64_binary_be failed");
        s_log_warn("str_eat_f64_binary_be: failed");
        return s_str_new_invalid();
    }
    if (opt_eaten) {
        memcpy(opt_eaten, s.data, 8);
        if (s_endian_system_is_binary_little_endian())
            s_endian_swap(opt_eaten, 8);
    }
    s.data += 8;
    s.size -= 8;
    return s;
}

//
// feed binary
//

// feeds an intx_t as binary little endian and returns the str without it (behind it).
#define S__STR_PARSE_HELPER_FEED_IX_BINARY_LE_PROTOTPYE_(x)\
static sStr_s str_feed_int ## x ## _binary_le(sStr_s s, si ## x feed) {\
    if(s_str_empty(s))\
        return s;\
    if(s.size < (x)/8) {\
        s_error_set("str_feed_int_binary_le failed");\
        s_log_warn("str_feed_i" #x "_binary_le: failed");\
        return s_str_new_invalid();\
    }\
    if(!s_endian_system_is_binary_little_endian())\
        s_endian_swap(&feed, (x)/8);\
    memcpy(s.data, &feed, (x)/8);\
    s.data += (x)/8;\
    s.size -= (x)/8;\
    return s;\
}

S__STR_PARSE_HELPER_FEED_IX_BINARY_LE_PROTOTPYE_(8)

S__STR_PARSE_HELPER_FEED_IX_BINARY_LE_PROTOTPYE_(16)

S__STR_PARSE_HELPER_FEED_IX_BINARY_LE_PROTOTPYE_(32)

S__STR_PARSE_HELPER_FEED_IX_BINARY_LE_PROTOTPYE_(64)

// feeds an intx_t as binary bigb endian and returns the str without it (behind it).
#define S__STR_PARSE_HELPER_FEED_IX_BINARY_BE_PROTOTPYE_(x)\
static sStr_s str_feed_int ## x ## _binary_be(sStr_s s, si ## x feed) {\
    if(s_str_empty(s))\
        return s;\
    if(s.size < (x)/8) {\
        s_error_set("str_feed_int_binary_be failed");\
        s_log_warn("str_feed_i" #x "_binary_be: failed");\
        return s_str_new_invalid();\
    }\
    if(s_endian_system_is_binary_little_endian())\
        s_endian_swap(&feed, (x)/8);\
    memcpy(s.data, &feed, (x)/8);\
    s.data += (x)/8;\
    s.size -= (x)/8;\
    return s;\
}

S__STR_PARSE_HELPER_FEED_IX_BINARY_BE_PROTOTPYE_(8)

S__STR_PARSE_HELPER_FEED_IX_BINARY_BE_PROTOTPYE_(16)

S__STR_PARSE_HELPER_FEED_IX_BINARY_BE_PROTOTPYE_(32)

S__STR_PARSE_HELPER_FEED_IX_BINARY_BE_PROTOTPYE_(64)

// feeds an uintx_t as binary little endian and returns the str without it (behind it).
#define S__STR_PARSE_HELPER_FEED_UX_BINARY_LE_PROTOTPYE_(x)\
static sStr_s str_feed_uint ## x ## _binary_le(sStr_s s, su ## x feed) {\
    if(s_str_empty(s))\
        return s;\
    if(s.size < (x)/8) {\
        s_error_set("str_feed_uint_binary_le failed");\
        s_log_warn("str_feed_u" #x "_binary_le: failed");\
        return s_str_new_invalid();\
    }\
    if(!s_endian_system_is_binary_little_endian())\
        s_endian_swap(&feed, (x)/8);\
    memcpy(s.data, &feed, (x)/8);\
    s.data += (x)/8;\
    s.size -= (x)/8;\
    return s;\
}

S__STR_PARSE_HELPER_FEED_UX_BINARY_LE_PROTOTPYE_(8)

S__STR_PARSE_HELPER_FEED_UX_BINARY_LE_PROTOTPYE_(16)

S__STR_PARSE_HELPER_FEED_UX_BINARY_LE_PROTOTPYE_(32)

S__STR_PARSE_HELPER_FEED_UX_BINARY_LE_PROTOTPYE_(64)

// feeds an uintx_t as binary bigb endian and returns the str without it (behind it).
#define S__STR_PARSE_HELPER_FEED_UX_BINARY_BE_PROTOTPYE_(x)\
static sStr_s str_feed_uint ## x ## _binary_be(sStr_s s, su ## x  feed) {\
    if(s_str_empty(s))\
        return s;\
    if(s.size < (x)/8) {\
        s_error_set("str_feed_uint_binary_be failed");\
        s_log_warn("str_feed_u" #x "_binary_be: failed");\
        return s_str_new_invalid();\
    }\
    if(s_endian_system_is_binary_little_endian())\
        s_endian_swap(&feed, (x)/8);\
    memcpy(s.data, &feed, (x)/8);\
    s.data += (x)/8;\
    s.size -= (x)/8;\
    return s;\
}

S__STR_PARSE_HELPER_FEED_UX_BINARY_BE_PROTOTPYE_(8)

S__STR_PARSE_HELPER_FEED_UX_BINARY_BE_PROTOTPYE_(16)

S__STR_PARSE_HELPER_FEED_UX_BINARY_BE_PROTOTPYE_(32)

S__STR_PARSE_HELPER_FEED_UX_BINARY_BE_PROTOTPYE_(64)


// feeds a f32 as binary little endian and returns the str without it (behind it).
static sStr_s str_feed_f32_binary_le(sStr_s s, sf32 feed) {
    if (s_str_empty(s))
        return s;
    if (s.size < 4) {
        s_error_set("str_feed_f32_binary_le failed");
        s_log_warn("str_feed_f32_binary_le: failed");
        return s_str_new_invalid();
    }
    if (!s_endian_system_is_binary_little_endian())
        s_endian_swap(&feed, 4);
    memcpy(s.data, &feed, 4);
    s.data += 4;
    s.size -= 4;
    return s;
}

// feeds a f32 as binary little endian and returns the str without it (behind it).
static sStr_s str_feed_f32_binary_be(sStr_s s, sf32 feed) {
    if (s_str_empty(s))
        return s;
    if (s.size < 4) {
        s_error_set("str_feed_f32_binary_be failed");
        s_log_warn("str_feed_f32_binary_be: failed");
        return s_str_new_invalid();
    }
    if (s_endian_system_is_binary_little_endian())
        s_endian_swap(&feed, 4);
    memcpy(s.data, &feed, 4);
    s.data += 4;
    s.size -= 4;
    return s;
}

// feeds a f64 as binary little endian and returns the str without it (behind it).
static sStr_s str_feed_f64_binary_le(sStr_s s, sf64 feed) {
    if (s_str_empty(s))
        return s;
    if (s.size < 8) {
        s_error_set("str_feed_f64_binary_le failed");
        s_log_warn("str_feed_f64_binary_le: failed");
        return s_str_new_invalid();
    }
    if (!s_endian_system_is_binary_little_endian())
        s_endian_swap(&feed, 8);
    memcpy(s.data, &feed, 8);
    s.data += 8;
    s.size -= 8;
    return s;
}

// feeds a f64 as binary little endian and returns the str without it (behind it).
static sStr_s str_feed_f64_binary_be(sStr_s s, sf64 feed) {
    if (s_str_empty(s))
        return s;
    if (s.size < 8) {
        s_error_set("str_feed_f64_binary_be failed");
        s_log_warn("str_feed_f64_binary_be: failed");
        return s_str_new_invalid();
    }
    if (s_endian_system_is_binary_little_endian())
        s_endian_swap(&feed, 8);
    memcpy(s.data, &feed, 8);
    s.data += 8;
    s.size -= 8;
    return s;
}

#endif //S_STR_PARSE_H
