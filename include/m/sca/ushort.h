#ifndef M_SCA_USHORT_H
#define M_SCA_USHORT_H

#include <stdlib.h>  // abs
#include <limits.h>  // USHRT_MAX
#include <math.h>

/** maximum possible value */
#define USSCA_MAX USHRT_MAX

/** minimum possible value */
#define USSCA_MIN 0

/** for printing in IO */
#define USSCA_PRINT_FORMAT_SPECIFIER "hu"

/** dst = pow(x, y) */
static unsigned short ussca_pow(unsigned short x, unsigned short y) {
    return (unsigned short) pow(x, y);
}

/** dst = exp(x) */
static unsigned short ussca_exp(unsigned short x) {
    return (unsigned short) exp(x);
}

/** dst = log(x) */
static unsigned short ussca_log(unsigned short x) {
    return (unsigned short) log(x);
}

/** dst = exp2(x) */
static unsigned short ussca_exp2(unsigned short x) {
    return (unsigned short) exp2(x);
}

/** dst = log2(x) */
static unsigned short ussca_log2(unsigned short x) {
    return (unsigned short) log2(x);
}

/** dst = sqrt(x) */
static unsigned short ussca_sqrt(unsigned short x) {
    return (unsigned short) sqrt(x);
}

/** dst =  x % y  **/
static unsigned short ussca_mod(unsigned short x, unsigned short y) {
    return x % y;
}

/** dst = a < b ? a : b */
static unsigned short ussca_min(unsigned short a, unsigned short b) {
    return a < b ? a : b;
}

/** dst = a > b ? a : b */
static unsigned short ussca_max(unsigned short a, unsigned short b) {
    return a > b ? a : b;
}

/** dst = x < min ? min : (x > max ? max : x) */
static unsigned short ussca_clamp(unsigned short x, unsigned short min, unsigned short max) {
    return x < min ? min : (x > max ? max : x);
}

/** dst = a * (1-t) + b * t */
static unsigned short ussca_mix(unsigned short a, unsigned short b, float t) {
    return (unsigned short) (a * (1.0f - t) + b * t);
}

/** dst = x < edge ? 0 : 1 */
static unsigned short ussca_step(unsigned short x, unsigned short edge) {
    return x < edge ? 0 : 1;
}

#endif //M_SCA_USHORT_H
