#ifndef MATHC_TYPES_FLOAT_H
#define MATHC_TYPES_FLOAT_H

#ifndef __cplusplus
#define static_assert _Static_assert
#endif


typedef union {
    float v[2];
    struct {
        float v0, v1;
    };
    struct {
        float x, y;
    };
    struct {
        float r, g;
    };
} vec2;
static_assert(sizeof(vec2) == sizeof(float) * 2, "[Mathc] wrong expected size");

/** casts a float * to a dereferenced vec2 */
#define Vec2(vec) (*(vec2 *) (vec))

/** casts a float * to a dereferenced const vec2 */
#define ConstVec2(vec) (*(const vec2 *) (vec))


typedef union {
    float v[4];
    float m[2][2];
    vec2 col[2];
    struct {
        float v0, v1;
        float v2, v3;
    };
    struct {
        float m00, m01;
        float m10, m11;
    };
} mat2;
static_assert(sizeof(mat2) == sizeof(float) * 4, "[Mathc] wrong expected size");

/** casts a float * to a dereferenced mat2 */
#define Mat2(mat) (*(mat2 *) (mat))

/** casts a float * to a dereferenced const mat2 */
#define ConstMat2(mat) (*(const mat2 *) (mat))

typedef union {
    float v[3];
    struct {
        float v0, v1, v2;
    };
    vec2 xy;
    struct {
        float x;
        union {
            struct {
                float y, z;
            };
            vec2 yz;
        };
    };
    vec2 rg;
    struct {
        float r;
        union {
            struct {
                float g, b;
            };
            vec2 gb;
        };
    };
} vec3;
static_assert(sizeof(vec3) == sizeof(float) * 3, "[Mathc] wrong expected size");

/** casts a float * to a dereferenced vec3 */
#define Vec3(vec) (*(vec3 *) (vec))

/** casts a float * to a dereferenced const vec3 */
#define ConstVec3(vec) (*(const vec3 *) (vec))


typedef union {
    float v[9];
    float m[3][3];
    vec3 col[3];
    struct {
        float v0, v1, v2;
        float v3, v4, v5;
        float v6, v7, v8;
    };
    struct {
        float m00, m01, m02;
        float m10, m11, m12;
        float m20, m21, m22;
    };
} mat3;
static_assert(sizeof(mat3) == sizeof(float) * 9, "[Mathc] wrong expected size");

/** casts a float * to a dereferenced mat3 */
#define Mat3(mat) (*(mat3 *) (mat))

/** casts a float * to a dereferenced const mat3 */
#define ConstMat3(mat) (*(const mat3 *) (mat))


typedef union {
    float v[4];
    struct {
        float v0, v1, v2, v3;
    };
    vec2 xy;
    vec3 xyz;
    struct {
        float x;
        union {
            struct {
                float y;
                union {
                    struct {
                        float z, w;
                    };
                    vec2 zw;
                };
            };
            vec2 yz;
            vec3 yzw;
        };
    };
    vec2 rg;
    vec3 rgb;
    struct {
        float r;
        union {
            struct {
                float g;
                union {
                    struct {
                        float b, a;
                    };
                    vec2 ba;
                };
            };
            vec2 gb;
            vec3 gba;
        };
    };
} vec4;
static_assert(sizeof(vec4) == sizeof(float) * 4, "[Mathc] wrong expected size");

/** casts a float * to a dereferenced vec4 */
#define Vec4(vec) (*(vec4 *) (vec))

/** casts a float * to a dereferenced const vec4 */
#define ConstVec4(vec) (*(const vec4 *) (vec))


typedef union {
    float v[16];
    float m[4][4];
    vec4 col[4];
    struct {
        float v0, v1, v2, v3;
        float v4, v5, v6, v7;
        float v8, v9, v10, v11;
        float v12, v13, v14, v15;
    };
    struct {
        float m00, m01, m02, m03;
        float m10, m11, m12, m13;
        float m20, m21, m22, m23;
        float m30, m31, m32, m33;
    };
} mat4;
static_assert(sizeof(mat4) == sizeof(float) * 16, "[Mathc] wrong expected size");

/** casts a float * to a dereferenced mat4 */
#define Mat4(mat) (*(mat4 *) (mat))

/** casts a float * to a dereferenced const mat4 */
#define ConstMat4(mat) (*(const mat4 *) (mat))


// quaternion type
typedef vec4 quat;
#define Quat Vec4
#define ConstQuat ConstVec4

#endif //MATHC_TYPES_FLOAT_H
