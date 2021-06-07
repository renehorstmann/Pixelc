#ifndef MATHC_TYPES_UCHAR_H
#define MATHC_TYPES_UCHAR_H

#ifndef __cplusplus
#define static_assert _Static_assert
#endif


typedef union {
    unsigned char v[2];
    struct {
        unsigned char v0, v1;
    };
    struct {
        unsigned char x, y;
    };
    struct {
        unsigned char r, g;
    };
} ucvec2;
static_assert(sizeof(ucvec2) == sizeof(unsigned char) * 2, "[Mathc] wrong expected size");

/** casts a unsigned char * to a dereferenced ucvec2 */
#define UCVec2(vec) (*(ucvec2 *) (vec))

/** casts a unsigned char * to a dereferenced const ucvec2 */
#define ConstUCVec2(vec) (*(const ucvec2 *) (vec))


typedef union {
    unsigned char v[4];
    unsigned char m[2][2];
    ucvec2 col[2];
    struct {
        unsigned char v0, v1;
        unsigned char v2, v3;
    };
    struct {
        unsigned char m00, m01;
        unsigned char m10, m11;
    };
} ucmat2;
static_assert(sizeof(ucmat2) == sizeof(unsigned char) * 4, "[Mathc] wrong expected size");

/** casts a unsigned char * to a dereferenced ucmat2 */
#define UCMat2(mat) (*(ucmat2 *) (mat))

/** casts a unsigned char * to a dereferenced const ucmat2 */
#define ConstUCMat2(mat) (*(const ucmat2 *) (mat))

typedef union {
    unsigned char v[3];
    struct {
        unsigned char v0, v1, v2;
    };
    ucvec2 xy;
    struct {
        unsigned char x;
        union {
            struct {
                unsigned char y, z;
            };
            ucvec2 yz;
        };
    };
    ucvec2 rg;
    struct {
        unsigned char r;
        union {
            struct {
                unsigned char g, b;
            };
            ucvec2 gb;
        };
    };
} ucvec3;
static_assert(sizeof(ucvec3) == sizeof(unsigned char) * 3, "[Mathc] wrong expected size");

/** casts a unsigned char * to a dereferenced ucvec3 */
#define UCVec3(vec) (*(ucvec3 *) (vec))

/** casts a unsigned char * to a dereferenced const ucvec3 */
#define ConstUCVec3(vec) (*(const ucvec3 *) (vec))


typedef union {
    unsigned char v[9];
    unsigned char m[3][3];
    ucvec3 col[3];
    struct {
        unsigned char v0, v1, v2;
        unsigned char v3, v4, v5;
        unsigned char v6, v7, v8;
    };
    struct {
        unsigned char m00, m01, m02;
        unsigned char m10, m11, m12;
        unsigned char m20, m21, m22;
    };
} ucmat3;
static_assert(sizeof(ucmat3) == sizeof(unsigned char) * 9, "[Mathc] wrong expected size");

/** casts a unsigned char * to a dereferenced ucmat3 */
#define UCMat3(mat) (*(ucmat3 *) (mat))

/** casts a unsigned char * to a dereferenced const ucmat3 */
#define ConstUCMat3(mat) (*(const ucmat3 *) (mat))


typedef union {
    unsigned char v[4];
    struct {
        unsigned char v0, v1, v2, v3;
    };
    ucvec2 xy;
    ucvec3 xyz;
    struct {
        unsigned char x;
        union {
            struct {
                unsigned char y;
                union {
                    struct {
                        unsigned char z, w;
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
        unsigned char r;
        union {
            struct {
                unsigned char g;
                union {
                    struct {
                        unsigned char b, a;
                    };
                    ucvec2 ba;
                };
            };
            ucvec2 gb;
            ucvec3 gba;
        };
    };
} ucvec4;
static_assert(sizeof(ucvec4) == sizeof(unsigned char) * 4, "[Mathc] wrong expected size");

/** casts a unsigned char * to a dereferenced ucvec4 */
#define UCVec4(vec) (*(ucvec4 *) (vec))

/** casts a unsigned char * to a dereferenced const ucvec4 */
#define ConstUCVec4(vec) (*(const ucvec4 *) (vec))


typedef union {
    unsigned char v[16];
    unsigned char m[4][4];
    ucvec4 col[4];
    struct {
        unsigned char v0, v1, v2, v3;
        unsigned char v4, v5, v6, v7;
        unsigned char v8, v9, v10, v11;
        unsigned char v12, v13, v14, v15;
    };
    struct {
        unsigned char m00, m01, m02, m03;
        unsigned char m10, m11, m12, m13;
        unsigned char m20, m21, m22, m23;
        unsigned char m30, m31, m32, m33;
    };
} ucmat4;
static_assert(sizeof(ucmat4) == sizeof(unsigned char) * 16, "[Mathc] wrong expected size");

/** casts a unsigned char * to a dereferenced ucmat4 */
#define UCMat4(mat) (*(ucmat4 *) (mat))

/** casts a unsigned char * to a dereferenced const ucmat4 */
#define ConstUCMat4(mat) (*(const ucmat4 *) (mat))


#endif //MATHC_TYPES_UCHAR_H
