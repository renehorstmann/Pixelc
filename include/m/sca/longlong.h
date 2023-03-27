#ifndef M_SCA_LONGLONG_H
#define M_SCA_LONGLONG_H

#include <stdlib.h>  // abs
#include <limits.h>  // LLONG_MAX
#include <math.h>
#include "../common.h"

/** maximum possible value */
#define LLSCA_MAX LLONG_MAX

/** minimum possible value */
#define LLSCA_MIN LLONG_MIN

/** for printing in IO */
#define LLSCA_PRINT_FORMAT_SPECIFIER "lli"

/** dst = pow(x, y) */
static long long llsca_pow(long long x, long long y) {
    return (long long) pow(x, y);
}

/** dst = exp(x) */
static long long llsca_exp(long long x) {
    return (long long) exp(x);
}

/** dst = log(x) */
static long long llsca_log(long long x) {
    return (long long) log(x);
}

/** dst = exp2(x) */
static long long llsca_exp2(long long x) {
    return (long long) exp2(x);
}

/** dst = log2(x) */
static long long llsca_log2(long long x) {
    return (long long) log2(x);
}

/** dst = sqrt(x) */
static long long llsca_sqrt(long long x) {
    return (long long) sqrt(x);
}

/** dst = abs(x) */
static long long llsca_abs(long long x) {
    return llabs(x);
}

/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static long long llsca_sign(long long x) {
    return x > 0 ? 1 : (x < 0 ? -1 : 0);
}

/** dst = (x % y + y) % y (always positive, if y>0) **/
static int llsca_mod(long long x, long long y) {
    return (x % y + y) % y;
}

/** dst = a < b ? a : b */
static long long llsca_min(long long a, long long b) {
    return a < b ? a : b;
}

/** dst = a > b ? a : b */
static long long llsca_max(long long a, long long b) {
    return a > b ? a : b;
}

/** dst = x < min ? min : (x > max ? max : x) */
static long long llsca_clamp(long long x, long long min, long long max) {
    return x < min ? min : (x > max ? max : x);
}

/** dst = a * (1-t) + b * t */
static long long llsca_mix(long long a, long long b, float t) {
    return (long long) (a * (1.0f - t) + b * t);
}

/** dst = x < edge ? 0 : 1 */
static long long llsca_step(long long x, long long edge) {
    return x < edge ? 0 : 1;
}

#endif //M_SCA_LONGLONG_H
