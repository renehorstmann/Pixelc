#ifndef MATHC_UTILS_CAMERA_H
#define MATHC_UTILS_CAMERA_H

#include "../vec/vec3.h"

/**
 * Creates an orthogonal camera matrix
 * @param near: near clipping plane
 * @param far: far flipping plane
 */
static mat4 mat4_camera_ortho(float left, float right,
                              float bottom, float top,
                              float near, float far) {
    // from cglm/cam.h/glm_ortho
    float rl = 1.0f / (right - left);
    float tb = 1.0f / (top - bottom);
    float fn = -1.0f / (far - near);

    mat4 res = MAT4_INIT_ZERO;
    res.m[0][0] = 2.0f * rl;
    res.m[1][1] = 2.0f * tb;
    res.m[2][2] = 2.0f * fn;
    res.m[3][0] = -(right + left) * rl;
    res.m[3][1] = -(top + bottom) * tb;
    res.m[3][2] = (far + near) * fn;
    res.m[3][3] = 1.0f;
    return res;
}

/** 
 * Creates a perspective (frustum) camera matrix
 * @param near: near clipping plane
 * @param far: far flipping plane
 */
static mat4 mat4_camera_frustum(float left, float right,
                                float bottom, float top,
                                float near, float far) {
    // from cglm/cam.h/glm_frustum
    float rl = 1.0f / (right  - left);
    float tb = 1.0f / (top    - bottom);
    float fn =-1.0f / (far - near);
    float nv = 2.0f * near;

    mat4 res = MAT4_INIT_ZERO;
    res.m[0][0] = nv * rl;
    res.m[1][1] = nv * tb;
    res.m[2][0] = (right  + left)    * rl;
    res.m[2][1] = (top    + bottom)  * tb;
    res.m[2][2] = (far + near) * fn;
    res.m[2][3] =-1.0f;
    res.m[3][2] = far * nv * fn;
    return res;
}

/**
 * Creates a perspective camera matrix.
 * @param fovy: field of view angle [rad]
 * @param aspect: width/height ratio
 * @param near: near clipping plane
 * @param far: far flipping plane
 */
static mat4 mat4_camera_perspective(float fovy, float aspect, float near, float far) {
    // from cglm/cam.h/glm_perspective
    float f = 1.0f / tanf(fovy * 0.5f);
    float fn = 1.0f / (near - far);

    mat4 res = MAT4_INIT_ZERO;
    res.m[0][0] = f / aspect;
    res.m[1][1] = f;
    res.m[2][2] = (near + far) * fn;
    res.m[2][3] = -1.0f;
    res.m[3][2] = 2.0f * near * far * fn;
    return res;
}

/**
 * Creates the view matrix for a 3d camera.
 * up vector must not be parallel with eye to center vector
 */

static mat4 mat4_camera_lookat(vec3 eye, vec3 center, vec3 up) {
    // from cglm/cam.h/glm_lookar

    vec3 f = vec3_sub_vec(center, eye);
    f = vec3_normalize(f);

    vec3 s = vec3_cross(f, up);
    s = vec3_normalize(s);
    
    vec3 u = vec3_cross(s, f);

    mat4 res = MAT4_INIT_EYE;
    res.col[0].xyz = s;
    res.col[1].xyz = u;
    res.col[2].xyz = vec3_neg(f);
    res.col[3].x = -vec3_dot(s, eye);
    res.col[3].y = -vec3_dot(u, eye);
    res.col[3].z = vec3_dot(f, eye);
    return res;
}

#endif //MATHC_UTILS_CAMERA_H
