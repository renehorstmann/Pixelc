#ifndef MATHC_TYPES_BOOL_H
#define MATHC_TYPES_BOOL_H

#ifndef __cplusplus
#define static_assert _Static_assert
#endif

#include "stdbool.h"


typedef union bvec2 {
    bool v[2];
    struct {
        bool v0, v1;
    };
    struct {
        bool x, y;
    };
} bvec2;
static_assert(sizeof(bvec2) == sizeof(bool) * 2, "[Mathc] wrong expected size");

/** casts a bool * to a dereferenced bvec2 */
#define BVec2(bvec) (*(bvec2 *) (bvec))

/** casts a bool * to a dereferenced const bvec2 */
#define ConstBVec2(bvec) (*(const bvec2 *) (bvec))

typedef union bvec3 {
    bool v[3];
    struct {
        bool v0, v1, v2;
    };
    bvec2 xy;
    struct {
        bool x;
        union {
            struct {
                bool y, z;
            };
            bvec2 yz;
        };
    };
} bvec3;
static_assert(sizeof(bvec3) == sizeof(bool) * 3, "[Mathc] wrong expected size");

/** casts a bool * to a dereferenced bvec3 */
#define BVec3(bvec) (*(bvec3 *) (bvec))

/** casts a bool * to a dereferenced const bvec3 */
#define ConstBVec3(bvec) (*(const bvec3 *) (bvec))


typedef union bvec4 {
    bool v[4];
    struct {
        bool v0, v1, v2, v3;
    };
    bvec2 xy;
    bvec3 xyz;
    struct {
        bool x;
        union {
            struct {
                bool y;
                union {
                    struct {
                        bool z, w;
                    };
                    bvec2 zw;
                };
            };
            bvec2 yz;
            bvec3 yzw;
        };
    };
} bvec4;
static_assert(sizeof(bvec4) == sizeof(bool) * 4, "[Mathc] wrong expected size");

/** casts a bool * to a dereferenced bvec4 */
#define BVec4(bvec) (*(bvec4 *) (bvec))

/** casts a bool * to a dereferenced const bvec4 */
#define ConstBVec4(bvec) (*(const bvec4 *) (bvec))


#endif //MATHC_TYPES_BOOL_H
