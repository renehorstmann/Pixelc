#ifndef UTILC_STRVIUPARSE_H
#define UTILC_STRVIUPARSE_H

#include "strviu.h"

/**
 * eats the next (with leading spaces) int_x_t and returns the strviu without it.
 * If eaten is not NULL, the eaten int_x_t will be set into it.
 * If an error occurs, the resulting viu is {NULL, "error message"}.
 */
#define SV__HELPER_EAT_INTX_ASCII_PROTOTYPE_(x)\
static strviu sv_eat_int ## x ## _ascii(strviu viu, int ## x ## _t *eaten) {\
    if(!viu.begin)\
        return viu;\
    char *end;\
    long long int res = strtoll(viu.begin, &end, 0);\
    if(end == viu.begin)\
        return (strviu) {NULL, "sv_eat_int" #x "_ascii failed"};\
    if(eaten)\
        *eaten = (int ## x ##_t) res;\
    return (strviu) {end, viu.end};\
}

SV__HELPER_EAT_INTX_ASCII_PROTOTYPE_(8)
SV__HELPER_EAT_INTX_ASCII_PROTOTYPE_(16)
SV__HELPER_EAT_INTX_ASCII_PROTOTYPE_(32)
SV__HELPER_EAT_INTX_ASCII_PROTOTYPE_(64)

/**
 * eats the next (with leading spaces) uint_x_t and returns the strviu without it.
 * If eaten is not NULL, the eaten uint_x_t will be set into it.
 * If an error occurs, the resulting viu is {NULL, "error message"}.
 */
#define SV__HELPER_EAT_UINTX_ASCII_PROTOTYPE_(x)\
static strviu sv_eat_uint ## x ## _ascii(strviu viu, uint ## x ## _t *eaten) {\
    if(!viu.begin)\
        return viu;\
    char *end;\
    unsigned long long int res = strtoull(viu.begin, &end, 0);\
    if(end == viu.begin)\
        return (strviu) {NULL, "sv_eat_uint" #x "_ascii failed"};\
    if(eaten)\
        *eaten = (uint ## x ##_t) res;\
    return (strviu) {end, viu.end};\
}

SV__HELPER_EAT_UINTX_ASCII_PROTOTYPE_(8)
SV__HELPER_EAT_UINTX_ASCII_PROTOTYPE_(16)
SV__HELPER_EAT_UINTX_ASCII_PROTOTYPE_(32)
SV__HELPER_EAT_UINTX_ASCII_PROTOTYPE_(64)

/**
 * eats the next (with leading spaces) float and returns the strviu without it.
 * If eaten is not NULL, the eaten float will be set into it.
 * If an error occurs, the resulting viu is {NULL, "error message"}.
 */
static strviu sv_eat_float_ascii(strviu viu, float *eaten) {
    if(!viu.begin)
        return viu;
    char *end;
    double res = strtod(viu.begin, &end);
    if(end == viu.begin)
        return (strviu) {NULL, "sv_eat_float_ascii failed"};
    if(eaten)
        *eaten = (float) res;
    return (strviu) {end, viu.end};
}

/**
 * eats the next (with leading spaces) double and returns the strviu without it.
 * If eaten is not NULL, the eaten double will be set into it.
 * If an error occurs, the resulting viu is {NULL, "error message"}.
 */
static strviu sv_eat_double_ascii(strviu viu, double *eaten) {
    if(!viu.begin)
        return viu;
    char *end;
    double res = strtod(viu.begin, &end);
    if(end == viu.begin)
        return (strviu) {NULL, "sv_eat_double_ascii failed"};
    if(eaten)
        *eaten = (double) res;
    return (strviu) {end, viu.end};
}

//
// parsing binary eat's
//

/**
 * eats the next intx_t as binary little endian and returns the strviu without it.
 * If eaten is not NULL, the eaten intx_t will be set into it.
 * If an error occurs, the resulting viu is {NULL, "error message"}.
 */
#define SV__HELPER_EAT_INTX_BINARY_LE_PROTOTPYE_(x)\
static strviu sv_eat_int ## x ## _binary_le(strviu viu, int ## x ## _t *eaten) {\
    if(!viu.begin)\
        return viu;\
    if(sv_length(viu) < (x)/8)\
        return (strviu) {NULL, "sv_eat_int" #x "_binary_le failed"};\
    if(eaten){\
        memcpy(eaten, viu.begin, (x)/8);\
        if(!sv__helper_system_is_binary_little_endian_())\
            sv__helper_swap_endian_(eaten, (x)/8);\
    }\
    viu.begin += (x)/8;\
    return viu;\
}

SV__HELPER_EAT_INTX_BINARY_LE_PROTOTPYE_(8)
SV__HELPER_EAT_INTX_BINARY_LE_PROTOTPYE_(16)
SV__HELPER_EAT_INTX_BINARY_LE_PROTOTPYE_(32)
SV__HELPER_EAT_INTX_BINARY_LE_PROTOTPYE_(64)

/**
 * eats the next intx_t as binary big endian and returns the strviu without it.
 * If eaten is not NULL, the eaten intx_t will be set into it.
 * If an error occurs, the resulting viu is {NULL, "error message"}.
 */
#define SV__HELPER_EAT_INTX_BINARY_BE_PROTOTPYE_(x)\
static strviu sv_eat_int ## x ## _binary_be(strviu viu, int ## x ## _t *eaten) {\
    if(!viu.begin)\
        return viu;\
    if(sv_length(viu) < (x)/8)\
        return (strviu) {NULL, "sv_eat_int" #x "_binary_be failed"};\
    if(eaten){\
        memcpy(eaten, viu.begin, (x)/8);\
        if(sv__helper_system_is_binary_little_endian_())\
            sv__helper_swap_endian_(eaten, (x)/8);\
    }\
    viu.begin += (x)/8;\
    return viu;\
}

SV__HELPER_EAT_INTX_BINARY_BE_PROTOTPYE_(8)
SV__HELPER_EAT_INTX_BINARY_BE_PROTOTPYE_(16)
SV__HELPER_EAT_INTX_BINARY_BE_PROTOTPYE_(32)
SV__HELPER_EAT_INTX_BINARY_BE_PROTOTPYE_(64)

/**
 * eats the next uintx_t as binary little endian and returns the strviu without it.
 * If eaten is not NULL, the eaten uintx_t will be set into it.
 * If an error occurs, the resulting viu is {NULL, "error message"}.
 */
#define SV__HELPER_EAT_UINTX_BINARY_LE_PROTOTPYE_(x)\
static strviu sv_eat_uint ## x ## _binary_le(strviu viu, uint ## x ## _t *eaten) {\
    if(!viu.begin)\
        return viu;\
    if(sv_length(viu) < (x)/8)\
        return (strviu) {NULL, "sv_eat_uint" #x "_binary_le failed"};\
    if(eaten){\
        memcpy(eaten, viu.begin, (x)/8);\
        if(!sv__helper_system_is_binary_little_endian_())\
            sv__helper_swap_endian_(eaten, (x)/8);\
    }\
    viu.begin += (x)/8;\
    return viu;\
}

SV__HELPER_EAT_UINTX_BINARY_LE_PROTOTPYE_(8)
SV__HELPER_EAT_UINTX_BINARY_LE_PROTOTPYE_(16)
SV__HELPER_EAT_UINTX_BINARY_LE_PROTOTPYE_(32)
SV__HELPER_EAT_UINTX_BINARY_LE_PROTOTPYE_(64)

/**
 * eats the next uintx_t as binary big endian and returns the strviu without it.
 * If eaten is not NULL, the eaten uintx_t will be set into it.
 * If an error occurs, the resulting viu is {NULL, "error message"}.
 */
#define SV__HELPER_EAT_UINTX_BINARY_BE_PROTOTPYE_(x)\
static strviu sv_eat_uint ## x ## _binary_be(strviu viu, uint ## x ## _t *eaten) {\
    if(!viu.begin)\
        return viu;\
    if(sv_length(viu) < (x)/8)\
        return (strviu) {NULL, "sv_eat_uint" #x "_binary_be failed"};\
    if(eaten){\
        memcpy(eaten, viu.begin, (x)/8);\
        if(sv__helper_system_is_binary_little_endian_())\
            sv__helper_swap_endian_(eaten, (x)/8);\
    }\
    viu.begin += (x)/8;\
    return viu;\
}

SV__HELPER_EAT_UINTX_BINARY_BE_PROTOTPYE_(8)
SV__HELPER_EAT_UINTX_BINARY_BE_PROTOTPYE_(16)
SV__HELPER_EAT_UINTX_BINARY_BE_PROTOTPYE_(32)
SV__HELPER_EAT_UINTX_BINARY_BE_PROTOTPYE_(64)


/**
 * eats the next float as binary little endian and returns the strviu without it.
 * If eaten is not NULL, the eaten float will be set into it.
 * If an error occurs, the resulting viu is {NULL, "error message"}.
 */
static strviu sv_eat_float_binary_le(strviu viu, float *eaten) {
    if(!viu.begin)
        return viu;
    if(sv_length(viu) < 4)
        return (strviu) {NULL, "sv_eat_float_binary_le failed"};
    if(eaten) {
        memcpy(eaten, viu.begin, 4);
        if (!sv__helper_system_is_binary_little_endian_())
            sv__helper_swap_endian_(eaten, 4);
    }
    viu.begin += 4;
    return viu;
}

/**
 * eats the next float as binary big endian and returns the strviu without it.
 * If eaten is not NULL, the eaten float will be set into it.
 * If an error occurs, the resulting viu is {NULL, "error message"}.
 */
static strviu sv_eat_float_binary_be(strviu viu, float *eaten) {
    if(!viu.begin)
        return viu;
    if(sv_length(viu) < 4)
        return (strviu) {NULL, "sv_eat_float_binary_be failed"};
    if(eaten) {
        memcpy(eaten, viu.begin, 4);
        if (sv__helper_system_is_binary_little_endian_())
            sv__helper_swap_endian_(eaten, 4);
    }
    viu.begin += 4;
    return viu;
}

/**
 * eats the next double as binary little endian and returns the strviu without it.
 * If eaten is not NULL, the eaten double will be set into it.
 * If an error occurs, the resulting viu is {NULL, "error message"}.
 */
static strviu sv_eat_double_binary_le(strviu viu, double *eaten) {
    if(!viu.begin)
        return viu;
    if(sv_length(viu) < 8)
        return (strviu) {NULL, "sv_eat_double_binary_le failed"};
    if(eaten) {
        memcpy(eaten, viu.begin, 8);
        if (!sv__helper_system_is_binary_little_endian_())
            sv__helper_swap_endian_(eaten, 8);
    }
    viu.begin += 8;
    return viu;
}

/**
 * eats the next double as binary big endian and returns the strviu without it.
 * If eaten is not NULL, the eaten double will be set into it.
 * If an error occurs, the resulting viu is {NULL, "error message"}.
 */
static strviu sv_eat_double_binary_be(strviu viu, double *eaten) {
    if(!viu.begin)
        return viu;
    if(sv_length(viu) < 8)
        return (strviu) {NULL, "sv_eat_double_binary_be failed"};
    if(eaten) {
        memcpy(eaten, viu.begin, 8);
        if (sv__helper_system_is_binary_little_endian_())
            sv__helper_swap_endian_(eaten, 8);
    }
    viu.begin += 8;
    return viu;
}

#endif //UTILC_STRVIUPARSE_H

