#ifndef MATHC_PUBLICTYPES_BVEC4_H
#define MATHC_PUBLICTYPES_BVEC4_H

#include <assert.h>     // for static_assert


#include <stdbool.h>


#include "bvec2.h"
#include "bvec3.h"

typedef union {
    bool v[4];
    struct {
        bool v0, v1, v2, v3;
    };
    mathc_bvec2 xy;
    mathc_bvec3 xyz;
    struct {
        bool x;
        union {
            struct {
                bool y;
                union {
                    struct {
                        bool z, w;
                    };
                    mathc_bvec2 zw;
                };
            };
            mathc_bvec2 yz;
            mathc_bvec3 yzw;
        };
    };
    mathc_bvec2 rg;
    mathc_bvec3 rgb;
    struct {
        bool r;
        union {
            struct {
                bool g;
                union {
                    struct {
                        bool b, a;
                    };
                    mathc_bvec2 ba;
                };
            };
            mathc_bvec2 gb;
            mathc_bvec3 gba;
        };
    };
} mathc_bvec4;


static_assert(sizeof(mathc_bvec4) == sizeof(bool) * 4, "[Mathc] wrong expected size");

/** casts a bool * to a dereferenced bvec4 */
#define MATHC_AS_BVEC4(vec) (*(mathc_bvec4 *) (vec))

#endif //MATHC_PUBLICTYPES_BVEC4_H
