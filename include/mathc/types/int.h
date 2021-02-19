#ifndef MATHC_TYPES_INT_H
#define MATHC_TYPES_INT_H

#ifndef __cplusplus
#define static_assert _Static_assert
#endif


typedef union {
    int v[2];
    struct {
        int v0, v1;
    };
    struct {
        int x, y;
    };
    struct {
        int r, g;
    };
} ivec2;
static_assert(sizeof(ivec2) == sizeof(int) * 2, "[Mathc] wrong expected size");

/** casts a int * to a dereferenced ivec2 */
#define IVec2(vec) (*(ivec2 *) (vec))

/** casts a int * to a dereferenced const ivec2 */
#define ConstIVec2(vec) (*(const ivec2 *) (vec))


typedef union {
    int v[4];
    int m[2][2];
    ivec2 col[2];
    struct {
        int v0, v1;
        int v2, v3;
    };
    struct {
        int m00, m01;
        int m10, m11;
    };
} imat2;
static_assert(sizeof(imat2) == sizeof(int) * 4, "[Mathc] wrong expected size");

/** casts a int * to a dereferenced imat2 */
#define IMat2(mat) (*(imat2 *) (mat))

/** casts a int * to a dereferenced const imat2 */
#define ConstIMat2(mat) (*(const imat2 *) (mat))

typedef union {
    int v[3];
    struct {
        int v0, v1, v2;
    };
    ivec2 xy;
    struct {
        int x;
        union {
            struct {
                int y, z;
            };
            ivec2 yz;
        };
    };
    ivec2 rg;
    struct {
        int r;
        union {
            struct {
                int g, b;
            };
            ivec2 gb;
        };
    };
} ivec3;
static_assert(sizeof(ivec3) == sizeof(int) * 3, "[Mathc] wrong expected size");

/** casts a int * to a dereferenced ivec3 */
#define IVec3(vec) (*(ivec3 *) (vec))

/** casts a int * to a dereferenced const ivec3 */
#define ConstIVec3(vec) (*(const ivec3 *) (vec))


typedef union {
    int v[9];
    int m[3][3];
    ivec3 col[3];
    struct {
        int v0, v1, v2;
        int v3, v4, v5;
        int v6, v7, v8;
    };
    struct {
        int m00, m01, m02;
        int m10, m11, m12;
        int m20, m21, m22;
    };
} imat3;
static_assert(sizeof(imat3) == sizeof(int) * 9, "[Mathc] wrong expected size");

/** casts a int * to a dereferenced imat3 */
#define IMat3(mat) (*(imat3 *) (mat))

/** casts a int * to a dereferenced const imat3 */
#define ConstIMat3(mat) (*(const imat3 *) (mat))


typedef union {
    int v[4];
    struct {
        int v0, v1, v2, v3;
    };
    ivec2 xy;
    ivec3 xyz;
    struct {
        int x;
        union {
            struct {
                int y;
                union {
                    struct {
                        int z, w;
                    };
                    ivec2 zw;
                };
            };
            ivec2 yz;
            ivec3 yzw;
        };
    };
    ivec2 rg;
    ivec3 rgb;
    struct {
        int r;
        union {
            struct {
                int g;
                union {
                    struct {
                        int b, a;
                    };
                    ivec2 ba;
                };
            };
            ivec2 gb;
            ivec3 gba;
        };
    };
} ivec4;
static_assert(sizeof(ivec4) == sizeof(int) * 4, "[Mathc] wrong expected size");

/** casts a int * to a dereferenced ivec4 */
#define IVec4(vec) (*(ivec4 *) (vec))

/** casts a int * to a dereferenced const ivec4 */
#define ConstIVec4(vec) (*(const ivec4 *) (vec))


typedef union {
    int v[16];
    int m[4][4];
    ivec4 col[4];
    struct {
        int v0, v1, v2, v3;
        int v4, v5, v6, v7;
        int v8, v9, v10, v11;
        int v12, v13, v14, v15;
    };
    struct {
        int m00, m01, m02, m03;
        int m10, m11, m12, m13;
        int m20, m21, m22, m23;
        int m30, m31, m32, m33;
    };
} imat4;
static_assert(sizeof(imat4) == sizeof(int) * 16, "[Mathc] wrong expected size");

/** casts a int * to a dereferenced imat4 */
#define IMat4(mat) (*(imat4 *) (mat))

/** casts a int * to a dereferenced const imat4 */
#define ConstIMat4(mat) (*(const imat4 *) (mat))


#endif //MATHC_TYPES_INT_H
