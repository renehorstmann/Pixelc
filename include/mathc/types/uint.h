#ifndef MATHC_TYPES_UINT_H
#define MATHC_TYPES_UINT_H

#ifndef __cplusplus
#define static_assert _Static_assert
#endif


typedef union {
    unsigned v[2];
    struct {
        unsigned v0, v1;
    };
    struct {
        unsigned x, y;
    };
    struct {
        unsigned r, g;
    };
} uvec2;
static_assert(sizeof(uvec2) == sizeof(unsigned) * 2, "[Mathc] wrong expected size");

/** casts a unsigned * to a dereferenced uvec2 */
#define UVec2(vec) (*(uvec2 *) (vec))

/** casts a unsigned * to a dereferenced const uvec2 */
#define ConstUVec2(vec) (*(const uvec2 *) (vec))


typedef union {
    unsigned v[4];
    unsigned m[2][2];
    uvec2 col[2];
    struct {
        unsigned v0, v1;
        unsigned v2, v3;
    };
    struct {
        unsigned m00, m01;
        unsigned m10, m11;
    };
} umat2;
static_assert(sizeof(umat2) == sizeof(unsigned) * 4, "[Mathc] wrong expected size");

/** casts a unsigned * to a dereferenced umata2 */
#define UMat2(mat) (*(umat2 *) (mat))

/** casts a unsigned * to a dereferenced const umata2 */
#define ConstUMat2(mat) (*(const umat2 *) (mat))

typedef union {
    unsigned v[3];
    struct {
        unsigned v0, v1, v2;
    };
    uvec2 xy;
    struct {
        unsigned x;
        union {
            struct {
                unsigned y, z;
            };
            uvec2 yz;
        };
    };
    uvec2 rg;
    struct {
        unsigned r;
        union {
            struct {
                unsigned g, b;
            };
            uvec2 gb;
        };
    };
} uvec3;
static_assert(sizeof(uvec3) == sizeof(unsigned) * 3, "[Mathc] wrong expected size");

/** casts a unsigned * to a dereferenced uvec3 */
#define UVec3(vec) (*(uvec3 *) (vec))

/** casts a unsigned * to a dereferenced const uvec3 */
#define ConstUVec3(vec) (*(const uvec3 *) (vec))


typedef union {
    unsigned v[9];
    unsigned m[3][3];
    uvec3 col[3];
    struct {
        unsigned v0, v1, v2;
        unsigned v3, v4, v5;
        unsigned v6, v7, v8;
    };
    struct {
        unsigned m00, m01, m02;
        unsigned m10, m11, m12;
        unsigned m20, m21, m22;
    };
} umat3;
static_assert(sizeof(umat3) == sizeof(unsigned) * 9, "[Mathc] wrong expected size");

/** casts a unsigned * to a dereferenced umata3 */
#define UMat3(mat) (*(umat3 *) (mat))

/** casts a unsigned * to a dereferenced const umata3 */
#define ConstUMat3(mat) (*(const umat3 *) (mat))


typedef union {
    unsigned v[4];
    struct {
        unsigned v0, v1, v2, v3;
    };
    uvec2 xy;
    uvec3 xyz;
    struct {
        unsigned x;
        union {
            struct {
                unsigned y;
                union {
                    struct {
                        unsigned z, w;
                    };
                    uvec2 zw;
                };
            };
            uvec2 yz;
            uvec3 yzw;
        };
    };
    uvec2 rg;
    uvec3 rgb;
    struct {
        unsigned r;
        union {
            struct {
                unsigned g;
                union {
                    struct {
                        unsigned b, a;
                    };
                    uvec2 ba;
                };
            };
            uvec2 gb;
            uvec3 gba;
        };
    };
} uvec4;
static_assert(sizeof(uvec4) == sizeof(unsigned) * 4, "[Mathc] wrong expected size");

/** casts a unsigned * to a dereferenced uvec4 */
#define UVec4(vec) (*(uvec4 *) (vec))

/** casts a unsigned * to a dereferenced const uvec4 */
#define ConstUVec4(vec) (*(const uvec4 *) (vec))


typedef union {
    unsigned v[16];
    unsigned m[4][4];
    uvec4 col[4];
    struct {
        unsigned v0, v1, v2, v3;
        unsigned v4, v5, v6, v7;
        unsigned v8, v9, v10, v11;
        unsigned v12, v13, v14, v15;
    };
    struct {
        unsigned m00, m01, m02, m03;
        unsigned m10, m11, m12, m13;
        unsigned m20, m21, m22, m23;
        unsigned m30, m31, m32, m33;
    };
} umat4;
static_assert(sizeof(umat4) == sizeof(unsigned) * 16, "[Mathc] wrong expected size");

/** casts a unsigned * to a dereferenced umata4 */
#define UMat4(mat) (*(umat4 *) (mat))

/** casts a unsigned * to a dereferenced const umata4 */
#define ConstUMat4(mat) (*(const umat4 *) (mat))


#endif //MATHC_TYPES_UINT_H
