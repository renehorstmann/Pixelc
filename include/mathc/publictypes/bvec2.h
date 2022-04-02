#ifndef MATHC_PUBLICTYPES_BVEC2_H
#define MATHC_PUBLICTYPES_BVEC2_H

#include <assert.h>     // for static_assert


#include <stdbool.h>



typedef union {
    bool v[2];
    struct {
        bool v0, v1;
    };
    struct {
        bool x, y;
    };
    struct {
        bool r, g;
    };
} mathc_bvec2;








static_assert(sizeof(mathc_bvec2) == sizeof(bool) * 2, "[Mathc] wrong expected size");

/** casts a bool * to a dereferenced bvec2 */
#define MATHC_AS_BVEC2(vec) (*(mathc_bvec2 *) (vec))

#endif //MATHC_PUBLICTYPES_BVEC2_H
