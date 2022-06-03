#ifndef MATHC_PUBLICTYPES_IVEC4_H
#define MATHC_PUBLICTYPES_IVEC4_H

#include <assert.h>     // for static_assert


#include "ivec2.h"
#include "ivec3.h"

typedef union {
    int v[4];
    struct {
        int v0, v1, v2, v3;
    };
    mathc_ivec2 xy;
    mathc_ivec3 xyz;
    struct {
        int x;
        union {
            struct {
                int y;
                union {
                    struct {
                        int z, w;
                    };
                    mathc_ivec2 zw;
                };
            };
            mathc_ivec2 yz;
            mathc_ivec3 yzw;
        };
    };
    mathc_ivec2 rg;
    mathc_ivec3 rgb;
    struct {
        int r;
        union {
            struct {
                int g;
                union {
                    struct {
                        int b, a;
                    };
                    mathc_ivec2 ba;
                };
            };
            mathc_ivec2 gb;
            mathc_ivec3 gba;
        };
    };
} mathc_ivec4;


static_assert(sizeof(mathc_ivec4) == sizeof(int) * 4, "[Mathc] wrong expected size");

/** casts a int * to a dereferenced ivec4 */
#define MATHC_AS_IVEC4(vec) (*(mathc_ivec4 *) (vec))

#endif //MATHC_PUBLICTYPES_IVEC4_H
