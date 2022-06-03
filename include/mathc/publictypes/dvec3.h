#ifndef MATHC_PUBLICTYPES_DVEC3_H
#define MATHC_PUBLICTYPES_DVEC3_H

#include <assert.h>     // for static_assert


#include "dvec2.h"

typedef union {
    double v[3];
    struct {
        double v0, v1, v2;
    };
    mathc_dvec2 xy;
    struct {
        double x;
        union {
            struct {
                double y, z;
            };
            mathc_dvec2 yz;
        };
    };
    mathc_dvec2 rg;
    struct {
        double r;
        union {
            struct {
                double g, b;
            };
            mathc_dvec2 gb;
        };
    };
} mathc_dvec3;


static_assert(sizeof(mathc_dvec3) == sizeof(double) * 3, "[Mathc] wrong expected size");

/** casts a double * to a dereferenced dvec3 */
#define MATHC_AS_DVEC3(vec) (*(mathc_dvec3 *) (vec))

#endif //MATHC_PUBLICTYPES_DVEC3_H
