#ifndef MATHC_PUBLICTYPES_BVEC3_H
#define MATHC_PUBLICTYPES_BVEC3_H

#include <assert.h>     // for static_assert


#include <stdbool.h>


#include "bvec2.h"

typedef union {
    bool v[3];
    struct {
        bool v0, v1, v2;
    };
    mathc_bvec2 xy;
    struct {
        bool x;
        union {
            struct {
                bool y, z;
            };
            mathc_bvec2 yz;
        };
    };
    mathc_bvec2 rg;
    struct {
        bool r;
        union {
            struct {
                bool g, b;
            };
            mathc_bvec2 gb;
        };
    };
} mathc_bvec3;


static_assert(sizeof(mathc_bvec3) == sizeof(bool) * 3, "[Mathc] wrong expected size");

/** casts a bool * to a dereferenced bvec3 */
#define MATHC_AS_BVEC3(vec) (*(mathc_bvec3 *) (vec))

#endif //MATHC_PUBLICTYPES_BVEC3_H
