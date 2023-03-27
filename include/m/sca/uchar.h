#ifndef M_SCA_UCHAR_H
#define M_SCA_UCHAR_H

#include <stdlib.h>  // abs
#include <limits.h>  // UCHAR_MAX
#include <math.h>
#include "../common.h"

/** maximum possible value */
#define UCSCA_MAX UCHAR_MAX

/** minimum possible value */
#define UCSCA_MIN 0

/** for printing in IO */
#define UCSCA_PRINT_FORMAT_SPECIFIER "hhu"

/** dst = pow(x, y) */
static unsigned char ucsca_pow(unsigned char x, unsigned char y) {
    return (unsigned char) pow(x, y);
}

/** dst = exp(x) */
static unsigned char ucsca_exp(unsigned char x) {
    return (unsigned char) exp(x);
}

/** dst = log(x) */
static unsigned char ucsca_log(unsigned char x) {
    return (unsigned char) log(x);
}

/** dst = exp2(x) */
static unsigned char ucsca_exp2(unsigned char x) {
    return (unsigned char) exp2(x);
}

/** dst = log2(x) */
static unsigned char ucsca_log2(unsigned char x) {
    return (unsigned char) log2(x);
}

/** dst = sqrt(x) */
static unsigned char ucsca_sqrt(unsigned char x) {
    return (unsigned char) sqrt(x);
}

/** dst =  x % y  **/
static unsigned char ucsca_mod(unsigned char x, unsigned char y) {
    return x % y;
}

/** dst = a < b ? a : b */
static unsigned char ucsca_min(unsigned char a, unsigned char b) {
    return a < b ? a : b;
}

/** dst = a > b ? a : b */
static unsigned char ucsca_max(unsigned char a, unsigned char b) {
    return a > b ? a : b;
}

/** dst = x < min ? min : (x > max ? max : x) */
static unsigned char ucsca_clamp(unsigned char x, unsigned char min, unsigned char max) {
    return x < min ? min : (x > max ? max : x);
}

/** dst = a * (1-t) + b * t */
static unsigned char ucsca_mix(unsigned char a, unsigned char b, float t) {
    return (unsigned char) (a * (1.0f - t) + b * t);
}

/** dst = x < edge ? 0 : 1 */
static unsigned char ucsca_step(unsigned char x, unsigned char edge) {
    return x < edge ? 0 : 1;
}

#endif //M_SCA_UCHAR_H
