#ifndef MATHC_PUBLICTYPES_UCVEC4_H
#define MATHC_PUBLICTYPES_UCVEC4_H

#include <assert.h>     // for static_assert


#include "ucvec2.h"
#include "ucvec3.h"

typedef union {
    unsigned char v[4];
    struct {
        unsigned char v0, v1, v2, v3;
    };
    mathc_ucvec2 xy;
    mathc_ucvec3 xyz;
    struct {
        unsigned char x;
        union {
            struct {
                unsigned char y;
                union {
                    struct {
                        unsigned char z, w;
                    };
                    mathc_ucvec2 zw;
                };
            };
            mathc_ucvec2 yz;
            mathc_ucvec3 yzw;
        };
    };
    mathc_ucvec2 rg;
    mathc_ucvec3 rgb;
    struct {
        unsigned char r;
        union {
            struct {
                unsigned char g;
                union {
                    struct {
                        unsigned char b, a;
                    };
                    mathc_ucvec2 ba;
                };
            };
            mathc_ucvec2 gb;
            mathc_ucvec3 gba;
        };
    };
} mathc_ucvec4;


static_assert(sizeof(mathc_ucvec4) == sizeof(unsigned char) * 4, "[Mathc] wrong expected size");

/** casts a unsigned char * to a dereferenced ucvec4 */
#define MATHC_AS_UCVEC4(vec) (*(mathc_ucvec4 *) (vec))

#endif //MATHC_PUBLICTYPES_UCVEC4_H
