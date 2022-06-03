#ifndef MATHC_PUBLICTYPES_IVEC3_H
#define MATHC_PUBLICTYPES_IVEC3_H

#include <assert.h>     // for static_assert


#include "ivec2.h"

typedef union {
    int v[3];
    struct {
        int v0, v1, v2;
    };
    mathc_ivec2 xy;
    struct {
        int x;
        union {
            struct {
                int y, z;
            };
            mathc_ivec2 yz;
        };
    };
    mathc_ivec2 rg;
    struct {
        int r;
        union {
            struct {
                int g, b;
            };
            mathc_ivec2 gb;
        };
    };
} mathc_ivec3;


static_assert(sizeof(mathc_ivec3) == sizeof(int) * 3, "[Mathc] wrong expected size");

/** casts a int * to a dereferenced ivec3 */
#define MATHC_AS_IVEC3(vec) (*(mathc_ivec3 *) (vec))

#endif //MATHC_PUBLICTYPES_IVEC3_H
