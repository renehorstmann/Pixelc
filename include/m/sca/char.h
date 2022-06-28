#ifndef M_SCA_CHAR_H
#define M_SCA_CHAR_H

#include <stdlib.h>  // abs
#include <limits.h>  // SCHAR_MAX
#include <math.h>

/** maximum possible value */
#define CSCA_MAX SCHAR_MAX

/** minimum possible value */
#define CSCA_MIN (-SCHAR_MIN)

/** for printing in IO */
#define CSCA_PRINT_FORMAT_SPECIFIER "hhi"

/** dst = pow(x, y) */
static signed char csca_pow(signed char x, signed char y) {
    return (signed char) pow(x, y);
}

/** dst = exp(x) */
static signed char csca_exp(signed char x) {
    return (signed char) exp(x);
}

/** dst = log(x) */
static signed char csca_log(signed char x) {
    return (signed char) log(x);
}

/** dst = exp2(x) */
static signed char csca_exp2(signed char x) {
    return (signed char) exp2(x);
}

/** dst = log2(x) */
static signed char csca_log2(signed char x) {
    return (signed char) log2(x);
}

/** dst = sqrt(x) */
static signed char csca_sqrt(signed char x) {
    return (signed char) sqrt(x);
}

/** dst = abs(x) */
static signed char csca_abs(signed char x) {
    return abs(x);
}

/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static signed char csca_sign(signed char x) {
    return x > 0 ? 1 : (x < 0 ? -1 : 0);
}

/** dst = (x % y + y) % y (always positive, if y>0) **/
static signed char csca_mod(signed char x, signed char y) {
    return (x % y + y) % y;
}

/** dst = a < b ? a : b */
static signed char csca_min(signed char a, signed char b) {
    return a < b ? a : b;
}

/** dst = a > b ? a : b */
static signed char csca_max(signed char a, signed char b) {
    return a > b ? a : b;
}

/** dst = x < min ? min : (x > max ? max : x) */
static signed char csca_clamp(signed char x, signed char min, signed char max) {
    return x < min ? min : (x > max ? max : x);
}

/** dst = a * (1-t) + b * t */
static signed char csca_mix(signed char a, signed char b, float t) {
    return (signed char) (a * (1.0f - t) + b * t);
}

/** dst = x < edge ? 0 : 1 */
static signed char csca_step(signed char x, signed char edge) {
    return x < edge ? 0 : 1;
}

#endif //M_SCA_CHAR_H
