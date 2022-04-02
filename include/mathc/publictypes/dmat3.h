#ifndef MATHC_PUBLICTYPES_DMAT3_H
#define MATHC_PUBLICTYPES_DMAT3_H

#include <assert.h>     // for static_assert





#include "dvec3.h"
typedef union {
    double v[3*3];
    double m[3][3];
    mathc_dvec3 col[3];
    struct {
        double v0, v1, v2;
        double v3, v4, v5;
        double v6, v7, v8;
    };
    struct {
        double m00, m01, m02;
        double m10, m11, m12;
        double m20, m21, m22;
    };
} mathc_dmat3;






static_assert(sizeof(mathc_dmat3) == sizeof(double) * 3 * 3, "[Mathc] wrong expected size");

/** casts a double * to a dereferenced dmat3 */
#define MATHC_AS_DMAT3(mat) (*(mathc_dmat3 *) (mat))

#endif //MATHC_PUBLICTYPES_DMAT3_H
