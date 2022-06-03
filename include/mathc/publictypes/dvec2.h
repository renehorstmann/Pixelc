#ifndef MATHC_PUBLICTYPES_DVEC2_H
#define MATHC_PUBLICTYPES_DVEC2_H

#include <assert.h>     // for static_assert


typedef union {
    double v[2];
    struct {
        double v0, v1;
    };
    struct {
        double x, y;
    };
    struct {
        double r, g;
    };
} mathc_dvec2;


static_assert(sizeof(mathc_dvec2) == sizeof(double) * 2, "[Mathc] wrong expected size");

/** casts a double * to a dereferenced dvec2 */
#define MATHC_AS_DVEC2(vec) (*(mathc_dvec2 *) (vec))

#endif //MATHC_PUBLICTYPES_DVEC2_H
