#ifndef MATHC_PUBLICTYPES_IMAT3_H
#define MATHC_PUBLICTYPES_IMAT3_H

#include <assert.h>     // for static_assert





#include "ivec3.h"
typedef union {
    int v[3*3];
    int m[3][3];
    mathc_ivec3 col[3];
    struct {
        int v0, v1, v2;
        int v3, v4, v5;
        int v6, v7, v8;
    };
    struct {
        int m00, m01, m02;
        int m10, m11, m12;
        int m20, m21, m22;
    };
} mathc_imat3;






static_assert(sizeof(mathc_imat3) == sizeof(int) * 3 * 3, "[Mathc] wrong expected size");

/** casts a int * to a dereferenced imat3 */
#define MATHC_AS_IMAT3(mat) (*(mathc_imat3 *) (mat))

#endif //MATHC_PUBLICTYPES_IMAT3_H
