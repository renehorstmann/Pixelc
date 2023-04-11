#ifndef M_SCA_LONGDOUBLE_H
#define M_SCA_LONGDOUBLE_H

#include <stdbool.h>
#include <float.h>  // for LDBL_MAX, ...
#include <math.h>
#include "../common.h"

/** maximum possible value */
#define LDSCA_MAX LDBL_MAX

/** minimum possible value */
#define LDSCA_MIN (-LDBL_MAX)

/** smallest positive value */
#define LDSCA_SMALL LDBL_MIN

/** smallest positive value change */
#define LDSCA_EPS LDBL_EPSILON

/* clone of some math.h constants */
#define LDSCA_E 2.718281828459045235360287471352662498L /* e */
#define LDSCA_LOG2E 1.442695040888963407359924681001892137L /* log_2 e */
#define LDSCA_LOG10E 0.434294481903251827651128918916605082L /* log_10 e */
#define LDSCA_LN2 0.693147180559945309417232121458176568L /* log_e 2 */
#define LDSCA_LN10 2.302585092994045684017991454684364208L /* log_e 10 */
#define LDSCA_PI 3.141592653589793238462643383279502884L /* pi */
#define LDSCA_PI_2 1.570796326794896619231321691639751442L /* pi/2 */
#define LDSCA_PI_4 0.785398163397448309615660845819875721L /* pi/4 */
#define LDSCA_1_PI 0.318309886183790671537767526745028724L /* 1/pi */
#define LDSCA_2_PI 0.636619772367581343075535053490057448L /* 2/pi */
#define LDSCA_2_SQRTPI 1.128379167095512573896158903121545172L /* 2/sqrt(pi) */
#define LDSCA_SQRT2 1.414213562373095048801688724209698079L /* sqrt(2) */
#define LDSCA_SQRT1_2 0.707106781186547524400844362104849039L /* 1/sqrt(2) */

/** for printing in IO */
#define LDSCA_PRINT_FORMAT_SPECIFIER "g"

/** dst = a * M_PI / 180 */
static long double ldsca_radians(long double deg) {
    return deg * LDSCA_PI / 180.0L;
}

/** dst = a * 180 / M_PI */
static long double ldsca_degrees(long double rad) {
    return rad * 180.0L / LDSCA_PI;
}

/** dst = sin(angle_rad) */
static long double ldsca_sin(long double angle_rad) {
    return sinl(angle_rad);
}

/** dst = cos(angle_rad) */
static long double ldsca_cos(long double angle_rad) {
    return cosl(angle_rad);
}

/** dst = tan(angle_rad) */
static long double ldsca_tan(long double angle_rad) {
    return tanl(angle_rad);
}

/** dst = asin(x) */
static long double ldsca_asin(long double x) {
    return asinl(x);
}

/** dst = acos(x) */
static long double ldsca_acos(long double x) {
    return acosl(x);
}

/** dst = atan(x) */
static long double ldsca_atan(long double x) {
    return atanl(x);
}

/** dst = atan2(y, x) */
static long double ldsca_atan2(long double y, long double x) {
    return atan2l(y, x);
}

/** dst = pow(x, y) */
static long double ldsca_pow(long double x, long double y) {
    return powl(x, y);
}

/** dst = exp(x) */
static long double ldsca_exp(long double x) {
    return expl(x);
}

/** dst = log(x) */
static long double ldsca_log(long double x) {
    return logl(x);
}

/** dst = exp2(x) */
static long double ldsca_exp2(long double x) {
    return exp2l(x);
}

/** dst = log2(x) */
static long double ldsca_log2(long double x) {
    return log2l(x);
}

/** dst = sqrt(x) */
static long double ldsca_sqrt(long double x) {
    return sqrtl(x);
}

/** dst = 1 / sqrt(x) */
static long double ldsca_inversesqrt(long double x) {
    return 1.0L / sqrtl(x);
}

/** dst = abs(x) */
static long double ldsca_abs(long double x) {
    return fabsl(x);
}

/** dst = x > 0 ? 1 : (x < 0 ? -1 : 0) */
static long double ldsca_sign(long double x) {
    return x > 0.0L ? 1.0L : (x < 0.0L ? -1.0L : 0.0L);
}

/** dst = floor(x) */
static long double ldsca_floor(long double x) {
    return floorl(x);
}

/** dst = ceil(x) */
static long double ldsca_ceil(long double x) {
    return ceill(x);
}

/** dst = 1 - floor(x) */
static long double ldsca_fract(long double x) {
    return 1.0L - floorl(x);
}

/** dst = x - y * floor(x/y) */
static long double ldsca_mod(long double x, long double y) {
    return x - y * floorl(x / y);
}

/** dst = a < b ? a : b */
static long double ldsca_min(long double a, long double b) {
    return a < b ? a : b;
}

/** dst = a > b ? a : b */
static long double ldsca_max(long double a, long double b) {
    return a > b ? a : b;
}

/** dst = x < min ? min : (x > max ? max : x) */
static long double ldsca_clamp(long double x, long double min, long double max) {
    return x < min ? min : (x > max ? max : x);
}

/** dst = a * (1-t) + b * t */
static long double ldsca_mix(long double a, long double b, long double t) {
    return a * (1.0L - t) + b * t;
}

/** dst = x < edge ? 0 : 1 */
static long double ldsca_step(long double x, long double edge) {
    return x < edge ? 0.0L : 1.0L;
}

/** dst = x < edge1 ? 0 : (x > edge2 ? 1 : x * x * (3 - 2 * x)) Hermite polynomials */
static long double ldsca_smoothstep(long double x, long double edge1, long double edge2) {
    x = ldsca_clamp((x - edge1) / (edge2 - edge1), 0.0L, 1.0L);
    return x * x * (3.0L - 2.0L * x);
}


// dst = sin(x*2pi)
//  X   ->   Y
// 0.00 ->  0.0
// 0.25 -> +1.0
// 0.50 ->  0.0
// 0.75 -> -1.0
static long double ldsca_signal_wave(long double x) {
    return ldsca_sin(x * 2.0L * LDSCA_PI);
}

// dst = -1 or 1, x: [0:1] (0-0.5 is -1)
//  X   ->   Y
// 0.25 -> -1.0
// 0.75 -> +1.0
static long double ldsca_signal_block(long double x) {
    return 2.0L * (ldsca_mod(x, 1.0L) > 0.5f) - 1.0L;
}

// dst = saw like signal, linear up, step down, x: [0:1] -> dst [-1:1]
//  X   ->   Y
// 0.00 -> -1.0
// 0.50 ->  0.0
static long double ldsca_signal_saw(long double x) {
    return 2.0L * ldsca_mod(x, 1.0L) - 1.0L;
}

// dst = linear up and down signal, x: [0:1] -> dst [-1:1]
//  X   ->   Y
// 0.00 -> -1.0
// 0.25 ->  0.0
// 0.50 -> +1.0
// 0.75 ->  0.0
static long double ldsca_signal_ramp(long double x) {
    x = ldsca_mod(x + 0.5f, 1.0L);
    return 4.0L * ldsca_abs(x - 0.5f) - 1.0L;
}

// dst = saw like signal, linear up, step down, x: [0:1] -> dst [-1:1]
// smoothed edge at [1-edge:1]
//  X   ->   Y
// 0.00 -> -1.0
// 1.00 -> +1.0
static long double ldsca_signal_smoothsaw_single(long double x, long double edge) {
    x = ldsca_mod(x, 1.0L);

    // linear: y = a*x
    // smooth: y = 1-b*(x-1)^2
    // equations solved, so that f==(1-edge) -> y and derivate are equal
    long double f = 1.0L - edge;
    long double b = -1.0L / (2.0L * (f - 1.0L));
    long double a = (1.0L - b * ldsca_pow(f - 1.0L, 2.0L)) / f;

    long double signal;
    // linear up
    if (x < f) {
        signal = a * x;
    } else {
        // smooth end
        signal = 1.0L - b * ldsca_pow(x - 1.0L, 2.0L);
    }
    return -1.0L + 2.0L * signal;
}

// dst = saw like signal, linear up, step down, x: [0:1] -> dst [-1:1]
// smoothed edges between [0:edge] , [1-edge:1]
//  X   ->   Y
// 0.00 -> -1.0
// 0.50 ->  0.0
static long double ldsca_signal_smoothsaw(long double x, long double edge) {
    x = ldsca_mod(x, 1.0L);
    if (x < 0.5L) {
        // 0.5*2 is exactly 1.0f, which will mod to 0, which will result in 1.0 instead of -1.0
        return -0.5L - ldsca_signal_smoothsaw_single((0.5L - x) * 1.99999L, edge * 2.0L) / 2.0L;
    }
    return 0.5L + ldsca_signal_smoothsaw_single((x - 0.5L) * 2.0L, edge * 2.0L) / 2.0L;
}

// dst = ramp like signal, linear up, linear down, x: [0:1] -> dst [-1:1]
// smoothed edges between [0:edge] , [0.5-edge:0.5+edge] , [1-edge:1]
//  X   ->   Y
// 0.00 -> -1.0
// 0.25 ->  0.0
// 0.50 -> +1.0
// 0.75 ->  0.0
static long double ldsca_signal_smoothramp(long double x, long double edge) {
    x = ldsca_mod(x, 1.0L);
    if (x < 0.5L) {
        return ldsca_signal_smoothsaw(x * 2.0L, edge * 2.0L);
    }
    return -ldsca_signal_smoothsaw((x - 0.5L) * 2.0L, edge * 2.0L);
}

/** dst = isnan(x) */
static bool ldsca_isnan(long double x) {
    return isnan(x);
}

/** dst = isinf(x) */
static bool ldsca_isinf(long double x) {
    return isinf(x);
}

#endif //M_SCA_LONGDOUBLE_H
