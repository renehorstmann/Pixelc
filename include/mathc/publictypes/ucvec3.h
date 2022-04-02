#ifndef MATHC_PUBLICTYPES_UCVEC3_H
#define MATHC_PUBLICTYPES_UCVEC3_H

#include <assert.h>     // for static_assert







#include "ucvec2.h"
typedef union {
    unsigned char v[3];
    struct {
        unsigned char v0, v1, v2;
    };
    mathc_ucvec2 xy;
    struct {
        unsigned char x;
        union {
            struct {
                unsigned char y, z;
            };
            mathc_ucvec2 yz;
        };
    };
    mathc_ucvec2 rg;
    struct {
        unsigned char r;
        union {
            struct {
                unsigned char g, b;
            };
            mathc_ucvec2 gb;
        };
    };
} mathc_ucvec3;






static_assert(sizeof(mathc_ucvec3) == sizeof(unsigned char) * 3, "[Mathc] wrong expected size");

/** casts a unsigned char * to a dereferenced ucvec3 */
#define MATHC_AS_UCVEC3(vec) (*(mathc_ucvec3 *) (vec))

#endif //MATHC_PUBLICTYPES_UCVEC3_H
