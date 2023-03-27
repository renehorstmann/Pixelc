#ifndef M_UTILS_DRANDOM
#define M_UTILS_DRANDOM


#ifndef M_RANDOM_FUNCTION
#include <stdlib.h>
#define M_RANDOM_FUNCTION rand
#endif

#ifndef M_RANDOM_FUNCTION_MAX
#define M_RANDOM_FUNCTION_MAX RAND_MAX
#endif

#include "../types/dvec2.h"
#include "../types/dvec3.h"
#include "../types/dvec4.h"
#include "../sca/double.h"

/** dst = rand() [0:1] */
static double dsca_random() {
    return (double) 1 * M_RANDOM_FUNCTION() / (double) M_RANDOM_FUNCTION_MAX;
}

/** dst = rand() [a:b] */
static double dsca_random_range(double a, double b) {
    return a + (b - a) * dsca_random();
}

/** dst = mean +- amplitude * rand() */
static double dsca_random_noise(double mean, double amplitude) {
    return mean - amplitude + 2 * amplitude * dsca_random();
}

/** dst = mean +- sigma * normalized_rand() */
static double dsca_random_normal(double mean, double sigma) {
    double u1, u2;
    do {
        u1 = dsca_random();
    } while (u1 <= (double) 0.00000001);
    u2 = dsca_random();

    double mag = sigma * dsca_sqrt((double) -2 * log(u1));
    return mean + mag * dsca_cos(2 * DSCA_PI * u2);
}

//
// vecN
//

/** dst = rand() [0:1] */
static void dvecN_random(double *dst, int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = dsca_random();
    }
}

/** dst = rand() [a:b] */
static void dvecN_random_range(double *dst, double a, double b, int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = dsca_random_range(a, b);
    }
}

/** dst = rand() [a:b] */
static void dvecN_random_range_vec(double *dst, const double *a, const double *b, int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = dsca_random_range(a[i], b[i]);
    }
}

/** dst = mean +- amplitude * rand() */
static void dvecN_random_noise(double *dst, double mean, double amplitude, int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = dsca_random_noise(mean, amplitude);
    }
}

/** dst = mean +- amplitude * rand() */
static void dvecN_random_noise_vec(double *dst, const double *mean, const double *amplitude, int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = dsca_random_noise(mean[i], amplitude[i]);
    }
}

/** dst = mean +- sigma * normalized_rand() */
static void dvecN_random_normal(double *dst, double mean, double sigma, int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = dsca_random_normal(mean, sigma);
    }
}

/** dst = mean +- sigma * normalized_rand() */
static void dvecN_random_normal_vec(double *dst, const double *mean, const double *sigma, int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = dsca_random_normal(mean[i], sigma[i]);
    }
}

//
// dvec2
//

/** dst = rand() [0:1] */
static dvec2 dvec2_random() {
    dvec2 res;
    dvecN_random(res.v, 2);
    return res;
}

/** dst = rand() [a:b] */
static dvec2 dvec2_random_range(double a, double b) {
    dvec2 res;
    dvecN_random_range(res.v, a, b, 2);
    return res;
}

/** dst = rand() [a:b] */
static dvec2 dvec2_random_range_vec(dvec2 a, dvec2 b) {
    dvec2 res;
    dvecN_random_range_vec(res.v, a.v, b.v, 2);
    return res;
}

/** dst = mean +- amplitude * rand() */
static dvec2 dvec2_random_noise(double mean, double amplitude) {
    dvec2 res;
    dvecN_random_noise(res.v, mean, amplitude, 2);
    return res;
}

/** dst = mean +- amplitude * rand() */
static dvec2 dvec2_random_noise_vec(dvec2 mean, dvec2 amplitude) {
    dvec2 res;
    dvecN_random_noise_vec(res.v, mean.v, amplitude.v, 2);
    return res;
}

/** dst = mean +- sigma * normalized_rand() */
static dvec2 dvec2_random_normal(double mean, double sigma) {
    dvec2 res;
    dvecN_random_normal(res.v, mean, sigma, 2);
    return res;
}

/** dst = mean +- sigma * normalized_rand() */
static dvec2 dvec2_random_normal_vec(dvec2 mean, dvec2 sigma) {
    dvec2 res;
    dvecN_random_normal_vec(res.v, mean.v, sigma.v, 2);
    return res;
}

//
// dvec3
//

/** dst = rand() [0:1] */
static dvec3 dvec3_random() {
    dvec3 res;
    dvecN_random(res.v, 3);
    return res;
}

/** dst = rand() [a:b] */
static dvec3 dvec3_random_range(double a, double b) {
    dvec3 res;
    dvecN_random_range(res.v, a, b, 3);
    return res;
}

/** dst = rand() [a:b] */
static dvec3 dvec3_random_range_vec(dvec3 a, dvec3 b) {
    dvec3 res;
    dvecN_random_range_vec(res.v, a.v, b.v, 3);
    return res;
}

/** dst = mean +- amplitude * rand() */
static dvec3 dvec3_random_noise(double mean, double amplitude) {
    dvec3 res;
    dvecN_random_noise(res.v, mean, amplitude, 3);
    return res;
}

/** dst = mean +- amplitude * rand() */
static dvec3 dvec3_random_noise_vec(dvec3 mean, dvec3 amplitude) {
    dvec3 res;
    dvecN_random_noise_vec(res.v, mean.v, amplitude.v, 3);
    return res;
}

/** dst = mean +- sigma * normalized_rand() */
static dvec3 dvec3_random_normal(double mean, double sigma) {
    dvec3 res;
    dvecN_random_normal(res.v, mean, sigma, 3);
    return res;
}

/** dst = mean +- sigma * normalized_rand() */
static dvec3 dvec3_random_normal_vec(dvec3 mean, dvec3 sigma) {
    dvec3 res;
    dvecN_random_normal_vec(res.v, mean.v, sigma.v, 3);
    return res;
}


//
// dvec4
//

/** dst = rand() [0:1] */
static dvec4 dvec4_random() {
    dvec4 res;
    dvecN_random(res.v, 4);
    return res;
}

/** dst = rand() [a:b] */
static dvec4 dvec4_random_range(double a, double b) {
    dvec4 res;
    dvecN_random_range(res.v, a, b, 4);
    return res;
}

/** dst = rand() [a:b] */
static dvec4 dvec4_random_range_vec(dvec4 a, dvec4 b) {
    dvec4 res;
    dvecN_random_range_vec(res.v, a.v, b.v, 4);
    return res;
}

/** dst = mean +- amplitude * rand() */
static dvec4 dvec4_random_noise(double mean, double amplitude) {
    dvec4 res;
    dvecN_random_noise(res.v, mean, amplitude, 4);
    return res;
}

/** dst = mean +- amplitude * rand() */
static dvec4 dvec4_random_noise_vec(dvec4 mean, dvec4 amplitude) {
    dvec4 res;
    dvecN_random_noise_vec(res.v, mean.v, amplitude.v, 4);
    return res;
}

/** dst = mean +- sigma * normalized_rand() */
static dvec4 dvec4_random_normal(double mean, double sigma) {
    dvec4 res;
    dvecN_random_normal(res.v, mean, sigma, 4);
    return res;
}

/** dst = mean +- sigma * normalized_rand() */
static dvec4 dvec4_random_normal_vec(dvec4 mean, dvec4 sigma) {
    dvec4 res;
    dvecN_random_normal_vec(res.v, mean.v, sigma.v, 4);
    return res;
}

#endif // M_UTILS_DRANDOM
