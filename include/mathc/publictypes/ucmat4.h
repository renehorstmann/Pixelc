#ifndef MATHC_PUBLICTYPES_UCMAT4_H
#define MATHC_PUBLICTYPES_UCMAT4_H

#include <assert.h>     // for static_assert







#include "ucvec4.h"
typedef union {
    unsigned char v[4*4];
    unsigned char m[4][4];
    mathc_ucvec4 col[4];
    struct {
        unsigned char v0, v1, v2, v3;
        unsigned char v4, v5, v6, v7;
        unsigned char v8, v9, v10, v11;
        unsigned char v12, v13, v14, v15;
    };
    struct {
        unsigned char m00, m01, m02, m03;
        unsigned char m10, m11, m12, m13;
        unsigned char m20, m21, m22, m23;
        unsigned char m30, m31, m32, m33;
    };
} mathc_ucmat4;




static_assert(sizeof(mathc_ucmat4) == sizeof(unsigned char) * 4 * 4, "[Mathc] wrong expected size");

/** casts a unsigned char * to a dereferenced ucmat4 */
#define MATHC_AS_UCMAT4(mat) (*(mathc_ucmat4 *) (mat))

#endif //MATHC_PUBLICTYPES_UCMAT4_H
