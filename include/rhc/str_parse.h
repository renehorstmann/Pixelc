#ifndef RHC_STR_PARSE_H
#define RHC_STR_PARSE_H

#include <stdlib.h>  // strto*
#include <stdint.h>  // int*_t
#include "str.h"

// helper functions:
static bool rhc_str__helper_system_is_binary_little_endian_() {
    int n = 1;
    // little endian if true
    return *(char *) &n == 1;
}
static void rhc_str__helper_swap_endian_(void *buf, int n) {
    char *buf_data = (char *) buf;
    char tmp[n];
    for (int i = 0; i < n; i++)
        tmp[i] = buf_data[n - i - 1];
    memcpy(buf_data, tmp, n);
}

//
// ascii
//

// eats the next (with leading spaces) int_x_t and returns the str without it.
#define RHC_STR__HELPER_EAT_INTX_ASCII_PROTOTYPE_(x)\
static Str_s str_eat_int ## x ## _ascii(Str_s s, int ## x ## _t *opt_eaten) {\
    if(str_empty(s))\
        return s;\
    char *end;\
    long long int res = strtoll(s.data, &end, 0);\
    size_t ate_size = end - s.data;\
    if(ate_size <= 0 || ate_size > s.size) {\
        rhc_error = "str_eat_int_ascii failed";\
        log_warn("str_eat_int" #x "_ascii: failed");\
        return (Str_s) {s.data, 0};\
    }\
    if(opt_eaten)\
        *opt_eaten = (int ## x ##_t) res;\
    return (Str_s) {s.data+ate_size, s.size-ate_size};\
}

RHC_STR__HELPER_EAT_INTX_ASCII_PROTOTYPE_(8)
RHC_STR__HELPER_EAT_INTX_ASCII_PROTOTYPE_(16)
RHC_STR__HELPER_EAT_INTX_ASCII_PROTOTYPE_(32)
RHC_STR__HELPER_EAT_INTX_ASCII_PROTOTYPE_(64)


// eats the next (with leading spaces) uint_x_t and returns the str without it.
#define RHC_STR__HELPER_EAT_UINTX_ASCII_PROTOTYPE_(x)\
static Str_s str_eat_uint ## x ## _ascii(Str_s s, uint ## x ## _t *opt_eaten) {\
    if(str_empty(s))\
        return s;\
    char *end;\
    unsigned long long int res = strtoull(s.data, &end, 0);\
    size_t ate_size = end - s.data;\
    if(ate_size <= 0 || ate_size > s.size) {\
        rhc_error = "str_eat_uint_ascii failed";\
        log_warn("str_eat_uint" #x "_ascii: failed");\
        return (Str_s) {s.data, 0};\
    }\
    if(opt_eaten)\
        *opt_eaten = (int ## x ##_t) res;\
    return (Str_s) {s.data+ate_size, s.size-ate_size};\
}

RHC_STR__HELPER_EAT_UINTX_ASCII_PROTOTYPE_(8)
RHC_STR__HELPER_EAT_UINTX_ASCII_PROTOTYPE_(16)
RHC_STR__HELPER_EAT_UINTX_ASCII_PROTOTYPE_(32)
RHC_STR__HELPER_EAT_UINTX_ASCII_PROTOTYPE_(64)


// eats the next (with leading spaces) float and returns the str without it.
static Str_s str_eat_float_ascii(Str_s s, float *opt_eaten) {
    if(str_empty(s))
        return s;
    char *end;
    double res = strtod(s.data, &end);
    size_t ate_size = end - s.data;
    if(ate_size <= 0 || ate_size > s.size) {
        rhc_error = "str_eat_float_ascii failed";
        log_warn("str_eat_float_ascii: failed");
        return (Str_s) {s.data, 0};
    }
    if(opt_eaten)
        *opt_eaten = (float) res;
    return (Str_s) {s.data+ate_size, s.size-ate_size};
}

// eats the next (with leading spaces) double and returns the str without it.
static Str_s str_eat_double_ascii(Str_s s, double *opt_eaten) {
    if(str_empty(s))
        return s;
    char *end;
    double res = strtod(s.data, &end);
    size_t ate_size = end - s.data;
    if(ate_size <= 0 || ate_size > s.size) {
        rhc_error = "str_eat_double_ascii failed";
        log_warn("str_eat_double_ascii: failed");
        return (Str_s) {s.data, 0};
    }
    if(opt_eaten)
        *opt_eaten = (double) res;
    return (Str_s) {s.data+ate_size, s.size-ate_size};
}


//
// binary
//

// eats the next intx_t as binary little endian and returns the str without it.
#define RHC_STR__HELPER_EAT_INTX_BINARY_LE_PROTOTPYE_(x)\
static Str_s str_eat_int ## x ## _binary_le(Str_s s, int ## x ## _t *opt_eaten) {\
    if(str_empty(s))\
        return s;\
    if(s.size < (x)/8) {\
        rhc_error = "str_eat_int_binary_le failed";\
        log_warn("str_eat_int" #x "_binary_le: failed");\
        return (Str_s) {s.data, 0};\
    }\
    if(opt_eaten){\
        memcpy(opt_eaten, s.data, (x)/8);\
        if(!rhc_str__helper_system_is_binary_little_endian_())\
            rhc_str__helper_swap_endian_(opt_eaten, (x)/8);\
    }\
    s.data += (x)/8;\
    s.size -= (x)/8;\
    return s;\
}

RHC_STR__HELPER_EAT_INTX_BINARY_LE_PROTOTPYE_(8)
RHC_STR__HELPER_EAT_INTX_BINARY_LE_PROTOTPYE_(16)
RHC_STR__HELPER_EAT_INTX_BINARY_LE_PROTOTPYE_(32)
RHC_STR__HELPER_EAT_INTX_BINARY_LE_PROTOTPYE_(64)

// eats the next intx_t as binary big endian and returns the str without it.
#define RHC_STR__HELPER_EAT_INTX_BINARY_BE_PROTOTPYE_(x)\
static Str_s str_eat_int ## x ## _binary_be(Str_s s, int ## x ## _t *opt_eaten) {\
    if(str_empty(s))\
        return s;\
    if(s.size < (x)/8) {\
        rhc_error = "str_eat_int_binary_be failed";\
        log_warn("str_eat_int" #x "_binary_be: failed");\
        return (Str_s) {s.data, 0};\
    }\
    if(opt_eaten){\
        memcpy(opt_eaten, s.data, (x)/8);\
        if(rhc_str__helper_system_is_binary_little_endian_())\
            rhc_str__helper_swap_endian_(opt_eaten, (x)/8);\
    }\
    s.data += (x)/8;\
    s.size -= (x)/8;\
    return s;\
}

RHC_STR__HELPER_EAT_INTX_BINARY_BE_PROTOTPYE_(8)
RHC_STR__HELPER_EAT_INTX_BINARY_BE_PROTOTPYE_(16)
RHC_STR__HELPER_EAT_INTX_BINARY_BE_PROTOTPYE_(32)
RHC_STR__HELPER_EAT_INTX_BINARY_BE_PROTOTPYE_(64)

// eats the next uintx_t as binary little endian and returns the str without it.
#define RHC_STR__HELPER_EAT_UINTX_BINARY_LE_PROTOTPYE_(x)\
static Str_s str_eat_uint ## x ## _binary_le(Str_s s, uint ## x ## _t *opt_eaten) {\
    if(str_empty(s))\
        return s;\
    if(s.size < (x)/8) {\
        rhc_error = "str_eat_uint_binary_le failed";\
        log_warn("str_eat_uint" #x "_binary_le: failed");\
        return (Str_s) {s.data, 0};\
    }\
    if(opt_eaten){\
        memcpy(opt_eaten, s.data, (x)/8);\
        if(!rhc_str__helper_system_is_binary_little_endian_())\
            rhc_str__helper_swap_endian_(opt_eaten, (x)/8);\
    }\
    s.data += (x)/8;\
    s.size -= (x)/8;\
    return s;\
}

RHC_STR__HELPER_EAT_UINTX_BINARY_LE_PROTOTPYE_(8)
RHC_STR__HELPER_EAT_UINTX_BINARY_LE_PROTOTPYE_(16)
RHC_STR__HELPER_EAT_UINTX_BINARY_LE_PROTOTPYE_(32)
RHC_STR__HELPER_EAT_UINTX_BINARY_LE_PROTOTPYE_(64)

// eats the next uintx_t as binary big endian and returns the str without it.
#define RHC_STR__HELPER_EAT_UINTX_BINARY_BE_PROTOTPYE_(x)\
static Str_s str_eat_uint ## x ## _binary_be(Str_s s, uint ## x ## _t *opt_eaten) {\
    if(str_empty(s))\
        return s;\
    if(s.size < (x)/8) {\
        rhc_error = "str_eat_uint_binary_be failed";\
        log_warn("str_eat_uint" #x "_binary_be: failed");\
        return (Str_s) {s.data, 0};\
    }\
    if(opt_eaten){\
        memcpy(opt_eaten, s.data, (x)/8);\
        if(rhc_str__helper_system_is_binary_little_endian_())\
            rhc_str__helper_swap_endian_(opt_eaten, (x)/8);\
    }\
    s.data += (x)/8;\
    s.size -= (x)/8;\
    return s;\
}

RHC_STR__HELPER_EAT_UINTX_BINARY_BE_PROTOTPYE_(8)
RHC_STR__HELPER_EAT_UINTX_BINARY_BE_PROTOTPYE_(16)
RHC_STR__HELPER_EAT_UINTX_BINARY_BE_PROTOTPYE_(32)
RHC_STR__HELPER_EAT_UINTX_BINARY_BE_PROTOTPYE_(64)


// eats the next float as binary little endian and returns the str without it.
static Str_s str_eat_float_binary_le(Str_s s, float *opt_eaten) {
    if(str_empty(s))
        return s;
    if(s.size < 4) {
        rhc_error = "str_eat_float_binary_le failed";
        log_warn("str_eat_float_binary_le: failed");
        return (Str_s) {s.data, 0};
    }
    if(opt_eaten) {
        memcpy(opt_eaten, s.data, 4);
        if (!rhc_str__helper_system_is_binary_little_endian_())
            rhc_str__helper_swap_endian_(opt_eaten, 4);
    }
    s.data += 4;
    s.size -= 4;
    return s;
}

// eats the next float as binary big endian and returns the str without it.
static Str_s str_eat_float_binary_be(Str_s s, float *opt_eaten) {
    if(str_empty(s))
        return s;
    if(s.size < 4) {
        rhc_error = "str_eat_float_binary_be failed";
        log_warn("str_eat_float_binary_be: failed");
        return (Str_s) {s.data, 0};
    }
    if(opt_eaten) {
        memcpy(opt_eaten, s.data, 4);
        if (rhc_str__helper_system_is_binary_little_endian_())
            rhc_str__helper_swap_endian_(opt_eaten, 4);
    }
    s.data += 4;
    s.size -= 4;
    return s;
}


// eats the next double as binary little endian and returns the str without it.
static Str_s str_eat_double_binary_le(Str_s s, double *opt_eaten) {
    if(str_empty(s))
        return s;
    if(s.size < 8) {
        rhc_error = "str_eat_double_binary_le failed";
        log_warn("str_eat_double_binary_le: failed");
        return (Str_s) {s.data, 0};
    }
    if(opt_eaten) {
        memcpy(opt_eaten, s.data, 8);
        if (!rhc_str__helper_system_is_binary_little_endian_())
            rhc_str__helper_swap_endian_(opt_eaten, 8);
    }
    s.data += 8;
    s.size -= 8;
    return s;
}

// eats the next double as binary big endian and returns the str without it.
static Str_s str_eat_double_binary_be(Str_s s, double *opt_eaten) {
    if(str_empty(s))
        return s;
    if(s.size < 8) {
        rhc_error = "str_eat_double_binary_be failed";
        log_warn("str_eat_double_binary_be: failed");
        return (Str_s) {s.data, 0};
    }
    if(opt_eaten) {
        memcpy(opt_eaten, s.data, 8);
        if (rhc_str__helper_system_is_binary_little_endian_())
            rhc_str__helper_swap_endian_(opt_eaten, 8);
    }
    s.data += 8;
    s.size -= 8;
    return s;
}

#endif //RHC_STR_PARSE_H
