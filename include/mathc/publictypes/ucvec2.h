#ifndef MATHC_PUBLICTYPES_UCVEC2_H
#define MATHC_PUBLICTYPES_UCVEC2_H

#include <assert.h>     // for static_assert


typedef union {
    unsigned char v[2];
    struct {
        unsigned char v0, v1;
    };
    struct {
        unsigned char x, y;
    };
    struct {
        unsigned char r, g;
    };
} mathc_ucvec2;


static_assert(sizeof(mathc_ucvec2) == sizeof(unsigned char) * 2, "[Mathc] wrong expected size");

/** casts a unsigned char * to a dereferenced ucvec2 */
#define MATHC_AS_UCVEC2(vec) (*(mathc_ucvec2 *) (vec))

#endif //MATHC_PUBLICTYPES_UCVEC2_H
