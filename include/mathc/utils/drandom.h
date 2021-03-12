#ifndef MAHTC_UTILS_DRANDOM
#define MAHTC_UTILS_DRANDOM

#include <float.h>
#include <math.h>

#ifndef MATHC_RANDOM_FUNCTION
#include <stdlib.h>
#define MATHC_RANDOM_FUNCTION rand
#endif

#ifndef MATHC_RANDOM_FUNCTION_MAX
#define MATHC_RANDOM_FUNCTION_MAX RAND_MAX
#endif

#include "../types/double.h"

/** dst = rand() [0:1] */
static double dsca_random() {
    return 1.0 * MATHC_RANDOM_FUNCTION() / MATHC_RANDOM_FUNCTION_MAX;
}

/** dst = rand() [a:b] */
static double dsca_random_range(double a, double b) {
    return a + (b-a) * dsca_random();
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
    } while (u1 <= DBL_EPSILON);
    u2 = dsca_random();

    double mag = sigma * sqrt(-2.0 * log(u1));
    return mean + mag * cos(2 * M_PI * u2);
}

//
// dvecN
//

/** dst = rand() [0:1] */
static void dvecN_random(double *dst, int n) {
    for(int i=0; i<n; i++) {
        dst[i] = dsca_random();
    }
}

/** dst = rand() [a:b] */
static void dvecN_random_range(double *dst, double a, double b, int n) {
    for(int i=0; i<n; i++) {
        dst[i] = dsca_random_range(a, b);
    }
}

/** dst = rand() [a:b] */
static void dvecN_random_range_dvec(double *dst, const double *a, const double *b, int n) {
    for(int i=0; i<n; i++) {
        dst[i] = dsca_random_range(a[i], b[i]);
    }
}

/** dst = mean +- amplitude * rand() */
static void dvecN_random_noise(double *dst, double mean, double amplitude, int n) {
    for(int i=0; i<n; i++) {
        dst[i] = dsca_random_noise(mean, amplitude);
    }
}

/** dst = mean +- amplitude * rand() */
static void dvecN_random_noise_dvec(double *dst, const double *mean, const double *amplitude, int n) {
    for(int i=0; i<n; i++) {
        dst[i] = dsca_random_noise(mean[i], amplitude[i]);
    }
}

/** dst = mean +- sigma * normalized_rand() */
static void dvecN_random_normal(double *dst, double mean, double sigma, int n) {
    for(int i=0; i<n; i++) {
        dst[i] = dsca_random_normal(mean, sigma);
    }
}

/** dst = mean +- sigma * normalized_rand() */
static void dvecN_random_normal_dvec(double *dst, const double *mean, const double *sigma, int n) {
    for(int i=0; i<n; i++) {
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
static dvec2 dvec2_random_range_dvec(dvec2 a, dvec2 b) {
    dvec2 res;
    dvecN_random_range_dvec(res.v, a.v, b.v, 2);
    return res;
}

/** dst = rand() [a:b] */
static dvec2 dvec2_random_range_dvec_v(const double *a, const double *b) {
    return dvec2_random_range_dvec(DVec2(a), DVec2(b));
}

/** dst = mean +- amplitude * rand() */
static dvec2 dvec2_random_noise(double mean, double amplitude) {
    dvec2 res;
    dvecN_random_noise(res.v, mean, amplitude, 2);
    return res;
}

/** dst = mean +- amplitude * rand() */
static dvec2 dvec2_random_noise_dvec(dvec2 mean, dvec2 amplitude) {
    dvec2 res;
    dvecN_random_noise_dvec(res.v, mean.v, amplitude.v, 2);
    return res;
}

/** dst = mean +- amplitude * rand() */
static dvec2 dvec2_random_noise_dvec_v(const double *mean, const double *amplitude) {
    return dvec2_random_noise_dvec(DVec2(mean), DVec2(amplitude));
}

/** dst = mean +- sigma * normalized_rand() */
static dvec2 dvec2_random_normal(double mean, double sigma) {
    dvec2 res;
    dvecN_random_normal(res.v, mean, sigma, 2);
    return res;
}

/** dst = mean +- sigma * normalized_rand() */
static dvec2 dvec2_random_normal_dvec(dvec2 mean, dvec2 sigma) {
    dvec2 res;
    dvecN_random_normal_dvec(res.v, mean.v, sigma.v, 2);
    return res;
}

/** dst = mean +- sigma * normalized_rand() */
static dvec2 dvec2_random_normal_dvec_v(const double *mean, const double *sigma) {
    return dvec2_random_normal_dvec(DVec2(mean), DVec2(sigma));
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
static dvec3 dvec3_random_range_dvec(dvec3 a, dvec3 b) {
    dvec3 res;
    dvecN_random_range_dvec(res.v, a.v, b.v, 3);
    return res;
}

/** dst = rand() [a:b] */
static dvec3 dvec3_random_range_dvec_v(const double *a, const double *b) {
    return dvec3_random_range_dvec(DVec3(a), DVec3(b));
}

/** dst = mean +- amplitude * rand() */
static dvec3 dvec3_random_noise(double mean, double amplitude) {
    dvec3 res;
    dvecN_random_noise(res.v, mean, amplitude, 3);
    return res;
}

/** dst = mean +- amplitude * rand() */
static dvec3 dvec3_random_noise_dvec(dvec3 mean, dvec3 amplitude) {
    dvec3 res;
    dvecN_random_noise_dvec(res.v, mean.v, amplitude.v, 3);
    return res;
}

/** dst = mean +- amplitude * rand() */
static dvec3 dvec3_random_noise_dvec_v(const double *mean, const double *amplitude) {
    return dvec3_random_noise_dvec(DVec3(mean), DVec3(amplitude));
}

/** dst = mean +- sigma * normalized_rand() */
static dvec3 dvec3_random_normal(double mean, double sigma) {
    dvec3 res;
    dvecN_random_normal(res.v, mean, sigma, 3);
    return res;
}

/** dst = mean +- sigma * normalized_rand() */
static dvec3 dvec3_random_normal_dvec(dvec3 mean, dvec3 sigma) {
    dvec3 res;
    dvecN_random_normal_dvec(res.v, mean.v, sigma.v, 3);
    return res;
}

/** dst = mean +- sigma * normalized_rand() */
static dvec3 dvec3_random_normal_dvec_v(const double *mean, const double *sigma) {
    return dvec3_random_normal_dvec(DVec3(mean), DVec3(sigma));
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
static dvec4 dvec4_random_range_dvec(dvec4 a, dvec4 b) {
    dvec4 res;
    dvecN_random_range_dvec(res.v, a.v, b.v, 4);
    return res;
}

/** dst = rand() [a:b] */
static dvec4 dvec4_random_range_dvec_v(const double *a, const double *b) {
    return dvec4_random_range_dvec(DVec4(a), DVec4(b));
}

/** dst = mean +- amplitude * rand() */
static dvec4 dvec4_random_noise(double mean, double amplitude) {
    dvec4 res;
    dvecN_random_noise(res.v, mean, amplitude, 4);
    return res;
}

/** dst = mean +- amplitude * rand() */
static dvec4 dvec4_random_noise_dvec(dvec4 mean, dvec4 amplitude) {
    dvec4 res;
    dvecN_random_noise_dvec(res.v, mean.v, amplitude.v, 4);
    return res;
}

/** dst = mean +- amplitude * rand() */
static dvec4 dvec4_random_noise_dvec_v(const double *mean, const double *amplitude) {
    return dvec4_random_noise_dvec(DVec4(mean), DVec4(amplitude));
}

/** dst = mean +- sigma * normalized_rand() */
static dvec4 dvec4_random_normal(double mean, double sigma) {
    dvec4 res;
    dvecN_random_normal(res.v, mean, sigma, 4);
    return res;
}

/** dst = mean +- sigma * normalized_rand() */
static dvec4 dvec4_random_normal_dvec(dvec4 mean, dvec4 sigma) {
    dvec4 res;
    dvecN_random_normal_dvec(res.v, mean.v, sigma.v, 4);
    return res;
}

/** dst = mean +- sigma * normalized_rand() */
static dvec4 dvec4_random_normal_dvec_v(const double *mean, const double *sigma) {
    return dvec4_random_normal_dvec(DVec4(mean), DVec4(sigma));
}


#endif // MAHTC_UTILS_DRANDOM
