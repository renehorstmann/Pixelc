#ifndef M_SCA_SHORT_H
#define M_SCA_SHORT_H

#include <stdlib.h>  // abs
#include <limits.h>  // SHRT_MAX
#include <math.h>

/** maximum possible value */
#define SSCA_MAX SHRT_MAX

/** minimum possible value */
#define SSCA_MIN SHRT_MIN

/** for printing in IO */
#define SSCA_PRINT_FORMAT_SPECIFIER "hi"

/** dst = pow(x, y) */
static short ssca_pow(short x, short y) {
    return (short) pow(x, y);
}

/** dst = exp(x) */
static short ssca_exp(short x) {
    return (short) exp(x);
}

/** dst = log(x) */
static short ssca_log(short x) {
    return (short) log(x);
}

/** dst = exp2(x) */
static short ssca_exp2(short x) {
    return (short) exp2(x);
}

/** dst = log2(x) */
static short ssca_log2(short x) {
    return (short) log2(x);
}

/** dst = sqrt(x) */
static short ssca_sqrt(short x) {
    return (short) sqrt(x);
}

/** dst = abs(x) */
static short ssca_abs(short x) {
    return abs(x);
}

/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static short ssca_sign(short x) {
    return x > 0 ? 1 : (x < 0 ? -1 : 0);
}

/** dst = (x % y + y) % y (always positive, if y>0) **/
static short ssca_mod(short x, short y) {
    return (x % y + y) % y;
}

/** dst = a < b ? a : b */
static short ssca_min(short a, short b) {
    return a < b ? a : b;
}

/** dst = a > b ? a : b */
static short ssca_max(short a, short b) {
    return a > b ? a : b;
}

/** dst = x < min ? min : (x > max ? max : x) */
static short ssca_clamp(short x, short min, short max) {
    return x < min ? min : (x > max ? max : x);
}

/** dst = a * (1-t) + b * t */
static short ssca_mix(short a, short b, float t) {
    return (short) (a * (1.0f - t) + b * t);
}

/** dst = x < edge ? 0 : 1 */
static short ssca_step(short x, short edge) {
    return x < edge ? 0 : 1;
}

#endif //M_SCA_SHORT_H
