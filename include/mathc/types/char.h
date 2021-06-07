#ifndef MATHC_TYPES_CHAR_H
#define MATHC_TYPES_CHAR_H

#ifndef __cplusplus
#define static_assert _Static_assert
#endif


#include <stdint.h>


typedef union {
    int8_t v[2];
    struct {
        int8_t v0, v1;
    };
    struct {
        int8_t x, y;
    };
    struct {
        int8_t r, g;
    };
} cvec2;
static_assert(sizeof(cvec2) == sizeof(int8_t) * 2, "[Mathc] wrong expected size");

/** casts a int8_t * to a dereferenced cvec2 */
#define CVec2(vec) (*(cvec2 *) (vec))

/** casts a int8_t * to a dereferenced const cvec2 */
#define ConstCVec2(vec) (*(const cvec2 *) (vec))


typedef union {
    int8_t v[4];
    int8_t m[2][2];
    cvec2 col[2];
    struct {
        int8_t v0, v1;
        int8_t v2, v3;
    };
    struct {
        int8_t m00, m01;
        int8_t m10, m11;
    };
} cmat2;
static_assert(sizeof(cmat2) == sizeof(int8_t) * 4, "[Mathc] wrong expected size");

/** casts a int8_t * to a dereferenced cmat2 */
#define CMat2(mat) (*(cmat2 *) (mat))

/** casts a int8_t * to a dereferenced const cmat2 */
#define ConstCMat2(mat) (*(const cmat2 *) (mat))

typedef union {
    int8_t v[3];
    struct {
        int8_t v0, v1, v2;
    };
    cvec2 xy;
    struct {
        int8_t x;
        union {
            struct {
                int8_t y, z;
            };
            cvec2 yz;
        };
    };
    cvec2 rg;
    struct {
        int8_t r;
        union {
            struct {
                int8_t g, b;
            };
            cvec2 gb;
        };
    };
} cvec3;
static_assert(sizeof(cvec3) == sizeof(int8_t) * 3, "[Mathc] wrong expected size");

/** casts a int8_t * to a dereferenced cvec3 */
#define CVec3(vec) (*(cvec3 *) (vec))

/** casts a int8_t * to a dereferenced const cvec3 */
#define ConstCVec3(vec) (*(const cvec3 *) (vec))


typedef union {
    int8_t v[9];
    int8_t m[3][3];
    cvec3 col[3];
    struct {
        int8_t v0, v1, v2;
        int8_t v3, v4, v5;
        int8_t v6, v7, v8;
    };
    struct {
        int8_t m00, m01, m02;
        int8_t m10, m11, m12;
        int8_t m20, m21, m22;
    };
} cmat3;
static_assert(sizeof(cmat3) == sizeof(int8_t) * 9, "[Mathc] wrong expected size");

/** casts a int8_t * to a dereferenced cmat3 */
#define CMat3(mat) (*(cmat3 *) (mat))

/** casts a int8_t * to a dereferenced const cmat3 */
#define ConstCMat3(mat) (*(const cmat3 *) (mat))


typedef union {
    int8_t v[4];
    struct {
        int8_t v0, v1, v2, v3;
    };
    cvec2 xy;
    cvec3 xyz;
    struct {
        int8_t x;
        union {
            struct {
                int8_t y;
                union {
                    struct {
                        int8_t z, w;
                    };
                    cvec2 zw;
                };
            };
            cvec2 yz;
            cvec3 yzw;
        };
    };
    cvec2 rg;
    cvec3 rgb;
    struct {
        int8_t r;
        union {
            struct {
                int8_t g;
                union {
                    struct {
                        int8_t b, a;
                    };
                    cvec2 ba;
                };
            };
            cvec2 gb;
            cvec3 gba;
        };
    };
} cvec4;
static_assert(sizeof(cvec4) == sizeof(int8_t) * 4, "[Mathc] wrong expected size");

/** casts a int8_t * to a dereferenced cvec4 */
#define CVec4(vec) (*(cvec4 *) (vec))

/** casts a int8_t * to a dereferenced const cvec4 */
#define ConstCVec4(vec) (*(const cvec4 *) (vec))


typedef union {
    int8_t v[16];
    int8_t m[4][4];
    cvec4 col[4];
    struct {
        int8_t v0, v1, v2, v3;
        int8_t v4, v5, v6, v7;
        int8_t v8, v9, v10, v11;
        int8_t v12, v13, v14, v15;
    };
    struct {
        int8_t m00, m01, m02, m03;
        int8_t m10, m11, m12, m13;
        int8_t m20, m21, m22, m23;
        int8_t m30, m31, m32, m33;
    };
} cmat4;
static_assert(sizeof(cmat4) == sizeof(int8_t) * 16, "[Mathc] wrong expected size");

/** casts a int8_t * to a dereferenced cmat4 */
#define CMat4(mat) (*(cmat4 *) (mat))

/** casts a int8_t * to a dereferenced const cmat4 */
#define ConstCMat4(mat) (*(const cmat4 *) (mat))


#endif //MATHC_TYPES_CHAR_H
