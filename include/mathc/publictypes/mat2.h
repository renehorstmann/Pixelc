#ifndef MATHC_PUBLICTYPES_MAT2_H
#define MATHC_PUBLICTYPES_MAT2_H

#include <assert.h>     // for static_assert



#include "vec2.h"
typedef union {
    float v[2*2];
    float m[2][2];
    mathc_vec2 col[2];
    struct {
        float v0, v1;
        float v2, v3;
    };
    struct {
        float m00, m01;
        float m10, m11;
    };
} mathc_mat2;








static_assert(sizeof(mathc_mat2) == sizeof(float) * 2 * 2, "[Mathc] wrong expected size");

/** casts a float * to a dereferenced mat2 */
#define MATHC_AS_MAT2(mat) (*(mathc_mat2 *) (mat))

#endif //MATHC_PUBLICTYPES_MAT2_H
