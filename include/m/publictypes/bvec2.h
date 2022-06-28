#ifndef M_PUBLICTYPES_BVEC2_H
#define M_PUBLICTYPES_BVEC2_H

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
} m_bvec2;


static_assert(sizeof(m_bvec2) == sizeof(bool) * 2, "[Mathc] wrong expected size");

/** casts a bool * to a dereferenced bvec2 */
#define M_AS_BVEC2(vec) (*(m_bvec2 *) (vec))

#endif //M_PUBLICTYPES_BVEC2_H
