#ifndef MATHC_PUBLICTYPES_IMAT2_H
#define MATHC_PUBLICTYPES_IMAT2_H

#include <assert.h>     // for static_assert


#include "ivec2.h"

typedef union {
    int v[2 * 2];
    int m[2][2];
    mathc_ivec2 col[2];
    struct {
        int v0, v1;
        int v2, v3;
    };
    struct {
        int m00, m01;
        int m10, m11;
    };
} mathc_imat2;


static_assert(sizeof(mathc_imat2) == sizeof(int) * 2 * 2, "[Mathc] wrong expected size");

/** casts a int * to a dereferenced imat2 */
#define MATHC_AS_IMAT2(mat) (*(mathc_imat2 *) (mat))

#endif //MATHC_PUBLICTYPES_IMAT2_H
