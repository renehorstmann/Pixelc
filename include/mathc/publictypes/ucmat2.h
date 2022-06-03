#ifndef MATHC_PUBLICTYPES_UCMAT2_H
#define MATHC_PUBLICTYPES_UCMAT2_H

#include <assert.h>     // for static_assert


#include "ucvec2.h"

typedef union {
    unsigned char v[2 * 2];
    unsigned char m[2][2];
    mathc_ucvec2 col[2];
    struct {
        unsigned char v0, v1;
        unsigned char v2, v3;
    };
    struct {
        unsigned char m00, m01;
        unsigned char m10, m11;
    };
} mathc_ucmat2;


static_assert(sizeof(mathc_ucmat2) == sizeof(unsigned char) * 2 * 2, "[Mathc] wrong expected size");

/** casts a unsigned char * to a dereferenced ucmat2 */
#define MATHC_AS_UCMAT2(mat) (*(mathc_ucmat2 *) (mat))

#endif //MATHC_PUBLICTYPES_UCMAT2_H
