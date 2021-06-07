#ifndef MATHC_TYPES_UCHAR_H
#define MATHC_TYPES_UCHAR_H

#ifndef __cplusplus
#define static_assert _Static_assert
#endif

#include <stdint.h>

typedef union {
    uint8_t v[2];
    struct {
        uint8_t v0, v1;
    };
    struct {
        uint8_t x, y;
    };
    struct {
        uint8_t r, g;
    };
} ucvec2;
static_assert(sizeof(ucvec2) == sizeof(uint8_t) * 2, "[Mathc] wrong expected size");

/** casts a uint8_t * to a dereferenced ucvec2 */
#define UCVec2(vec) (*(ucvec2 *) (vec))

/** casts a uint8_t * to a dereferenced const ucvec2 */
#define ConstUCVec2(vec) (*(const ucvec2 *) (vec))


typedef union {
    uint8_t v[4];
    uint8_t m[2][2];
    ucvec2 col[2];
    struct {
        uint8_t v0, v1;
        uint8_t v2, v3;
    };
    struct {
        uint8_t m00, m01;
        uint8_t m10, m11;
    };
} ucmat2;
static_assert(sizeof(ucmat2) == sizeof(uint8_t) * 4, "[Mathc] wrong expected size");

/** casts a uint8_t * to a dereferenced ucmat2 */
#define UCMat2(mat) (*(ucmat2 *) (mat))

/** casts a uint8_t * to a dereferenced const ucmat2 */
#define ConstUCMat2(mat) (*(const ucmat2 *) (mat))

typedef union {
    uint8_t v[3];
    struct {
        uint8_t v0, v1, v2;
    };
    ucvec2 xy;
    struct {
        uint8_t x;
        union {
            struct {
                uint8_t y, z;
            };
            ucvec2 yz;
        };
    };
    ucvec2 rg;
    struct {
        uint8_t r;
        union {
            struct {
                uint8_t g, b;
            };
            ucvec2 gb;
        };
    };
} ucvec3;
static_assert(sizeof(ucvec3) == sizeof(uint8_t) * 3, "[Mathc] wrong expected size");

/** casts a uint8_t * to a dereferenced ucvec3 */
#define UCVec3(vec) (*(ucvec3 *) (vec))

/** casts a uint8_t * to a dereferenced const ucvec3 */
#define ConstUCVec3(vec) (*(const ucvec3 *) (vec))


typedef union {
    uint8_t v[9];
    uint8_t m[3][3];
    ucvec3 col[3];
    struct {
        uint8_t v0, v1, v2;
        uint8_t v3, v4, v5;
        uint8_t v6, v7, v8;
    };
    struct {
        uint8_t m00, m01, m02;
        uint8_t m10, m11, m12;
        uint8_t m20, m21, m22;
    };
} ucmat3;
static_assert(sizeof(ucmat3) == sizeof(uint8_t) * 9, "[Mathc] wrong expected size");

/** casts a uint8_t * to a dereferenced ucmat3 */
#define UCMat3(mat) (*(ucmat3 *) (mat))

/** casts a uint8_t * to a dereferenced const ucmat3 */
#define ConstUCMat3(mat) (*(const ucmat3 *) (mat))


typedef union {
    uint8_t v[4];
    struct {
        uint8_t v0, v1, v2, v3;
    };
    ucvec2 xy;
    ucvec3 xyz;
    struct {
        uint8_t x;
        union {
            struct {
                uint8_t y;
                union {
                    struct {
                        uint8_t z, w;
                    };
                    ucvec2 zw;
                };
            };
            ucvec2 yz;
            ucvec3 yzw;
        };
    };
    ucvec2 rg;
    ucvec3 rgb;
    struct {
        uint8_t r;
        union {
            struct {
                uint8_t g;
                union {
                    struct {
                        uint8_t b, a;
                    };
                    ucvec2 ba;
                };
            };
            ucvec2 gb;
            ucvec3 gba;
        };
    };
} ucvec4;
static_assert(sizeof(ucvec4) == sizeof(uint8_t) * 4, "[Mathc] wrong expected size");

/** casts a uint8_t * to a dereferenced ucvec4 */
#define UCVec4(vec) (*(ucvec4 *) (vec))

/** casts a uint8_t * to a dereferenced const ucvec4 */
#define ConstUCVec4(vec) (*(const ucvec4 *) (vec))


typedef union {
    uint8_t v[16];
    uint8_t m[4][4];
    ucvec4 col[4];
    struct {
        uint8_t v0, v1, v2, v3;
        uint8_t v4, v5, v6, v7;
        uint8_t v8, v9, v10, v11;
        uint8_t v12, v13, v14, v15;
    };
    struct {
        uint8_t m00, m01, m02, m03;
        uint8_t m10, m11, m12, m13;
        uint8_t m20, m21, m22, m23;
        uint8_t m30, m31, m32, m33;
    };
} ucmat4;
static_assert(sizeof(ucmat4) == sizeof(uint8_t) * 16, "[Mathc] wrong expected size");

/** casts a uint8_t * to a dereferenced ucmat4 */
#define UCMat4(mat) (*(ucmat4 *) (mat))

/** casts a uint8_t * to a dereferenced const ucmat4 */
#define ConstUCMat4(mat) (*(const ucmat4 *) (mat))


#endif //MATHC_TYPES_UCHAR_H
