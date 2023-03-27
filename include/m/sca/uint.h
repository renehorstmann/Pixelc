#ifndef M_SCA_UINT_H
#define M_SCA_UINT_H

#include <stdlib.h>  // abs
#include <limits.h>  // UINT_MAX
#include <math.h>
#include "../common.h"

/** maximum possible value */
#define UISCA_MAX UINT_MAX

/** minimum possible value */
#define UISCA_MIN 0

/** for printing in IO */
#define UISCA_PRINT_FORMAT_SPECIFIER "u"

/** dst = pow(x, y) */
static unsigned int uisca_pow(unsigned int x, unsigned int y) {
    return (unsigned int) pow(x, y);
}

/** dst = exp(x) */
static unsigned int uisca_exp(unsigned int x) {
    return (unsigned int) exp(x);
}

/** dst = log(x) */
static unsigned int uisca_log(unsigned int x) {
    return (unsigned int) log(x);
}

/** dst = exp2(x) */
static unsigned int uisca_exp2(unsigned int x) {
    return (unsigned int) exp2(x);
}

/** dst = log2(x) */
static unsigned int uisca_log2(unsigned int x) {
    return (unsigned int) log2(x);
}

/** dst = sqrt(x) */
static unsigned int uisca_sqrt(unsigned int x) {
    return (unsigned int) sqrt(x);
}

/** dst =  x % y  **/
static unsigned int uisca_mod(unsigned int x, unsigned int y) {
    return x % y;
}

/** dst = a < b ? a : b */
static unsigned int uisca_min(unsigned int a, unsigned int b) {
    return a < b ? a : b;
}

/** dst = a > b ? a : b */
static unsigned int uisca_max(unsigned int a, unsigned int b) {
    return a > b ? a : b;
}

/** dst = x < min ? min : (x > max ? max : x) */
static unsigned int uisca_clamp(unsigned int x, unsigned int min, unsigned int max) {
    return x < min ? min : (x > max ? max : x);
}

/** dst = a * (1-t) + b * t */
static unsigned int uisca_mix(unsigned int a, unsigned int b, float t) {
    return (unsigned int) (a * (1.0f - t) + b * t);
}

/** dst = x < edge ? 0 : 1 */
static unsigned int uisca_step(unsigned int x, unsigned int edge) {
    return x < edge ? 0 : 1;
}

#endif //M_SCA_UINT_H
