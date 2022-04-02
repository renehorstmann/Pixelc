#ifndef MATHC_PUBLICTYPES_VEC3_H
#define MATHC_PUBLICTYPES_VEC3_H

#include <assert.h>     // for static_assert







#include "vec2.h"
typedef union {
    float v[3];
    struct {
        float v0, v1, v2;
    };
    mathc_vec2 xy;
    struct {
        float x;
        union {
            struct {
                float y, z;
            };
            mathc_vec2 yz;
        };
    };
    mathc_vec2 rg;
    struct {
        float r;
        union {
            struct {
                float g, b;
            };
            mathc_vec2 gb;
        };
    };
} mathc_vec3;






static_assert(sizeof(mathc_vec3) == sizeof(float) * 3, "[Mathc] wrong expected size");

/** casts a float * to a dereferenced vec3 */
#define MATHC_AS_VEC3(vec) (*(mathc_vec3 *) (vec))

#endif //MATHC_PUBLICTYPES_VEC3_H
