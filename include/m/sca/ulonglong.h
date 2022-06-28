#ifndef M_SCA_ULONGLONG_H
#define M_SCA_ULONGLONG_H

#include <stdlib.h>  // abs
#include <limits.h>  // ULLONG_MAX
#include <math.h>

/** maximum possible value */
#define ULLSCA_MAX ULLONG_MAX

/** minimum possible value */
#define ULLSCA_MIN 0

/** for printing in IO */
#define ULLSCA_PRINT_FORMAT_SPECIFIER "llu"

/** dst = pow(x, y) */
static unsigned long long ullsca_pow(unsigned long long x, unsigned long long y) {
    return (unsigned long long) pow(x, y);
}

/** dst = exp(x) */
static unsigned long long ullsca_exp(unsigned long long x) {
    return (unsigned long long) exp(x);
}

/** dst = log(x) */
static unsigned long long ullsca_log(unsigned long long x) {
    return (unsigned long long) log(x);
}

/** dst = exp2(x) */
static unsigned long long ullsca_exp2(unsigned long long x) {
    return (unsigned long long) exp2(x);
}

/** dst = log2(x) */
static unsigned long long ullsca_log2(unsigned long long x) {
    return (unsigned long long) log2(x);
}

/** dst = sqrt(x) */
static unsigned long long ullsca_sqrt(unsigned long long x) {
    return (unsigned long long) sqrt(x);
}

/** dst =  x % y  **/
static unsigned long long ullsca_mod(unsigned long long x, unsigned long long y) {
    return x % y;
}

/** dst = a < b ? a : b */
static unsigned long long ullsca_min(unsigned long long a, unsigned long long b) {
    return a < b ? a : b;
}

/** dst = a > b ? a : b */
static unsigned long long ullsca_max(unsigned long long a, unsigned long long b) {
    return a > b ? a : b;
}

/** dst = x < min ? min : (x > max ? max : x) */
static unsigned long long ullsca_clamp(unsigned long long x, unsigned long long min, unsigned long long max) {
    return x < min ? min : (x > max ? max : x);
}

/** dst = a * (1-t) + b * t */
static unsigned long long ullsca_mix(unsigned long long a, unsigned long long b, float t) {
    return (unsigned long long) (a * (1.0f - t) + b * t);
}

/** dst = x < edge ? 0 : 1 */
static unsigned long long ullsca_step(unsigned long long x, unsigned long long edge) {
    return x < edge ? 0 : 1;
}

#endif //M_SCA_ULONGLONG_H
