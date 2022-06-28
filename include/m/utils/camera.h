#ifndef M_UTILS_CAMERA_H
#define M_UTILS_CAMERA_H


#include "../vec/vec3.h"
#include "../mat/mat4.h"

/**
 * Creates an orthogonal camera matrix
 * @param near_z: near clipping plane
 * @param far_z: far flipping plane
 */
static mat4 mat4_camera_ortho(float left, float right,
                              float bottom, float top,
                              float near_z, float far_z) {
    // from cglm/cam.h/glm_ortho
    float rl = (float) 1 / (right - left);
    float tb = (float) 1 / (top - bottom);
    float fn = (float) -1 / (far_z - near_z);

    mat4 res = {{0}};
    res.m[0][0] = (float) 2 * rl;
    res.m[1][1] = (float) 2 * tb;
    res.m[2][2] = (float) 2 * fn;
    res.m[3][0] = -(right + left) * rl;
    res.m[3][1] = -(top + bottom) * tb;
    res.m[3][2] = (far_z + near_z) * fn;
    res.m[3][3] = (float) 1;
    return res;
}

/** 
 * Creates a perspective (frustum) camera matrix
 * @param near_z: near clipping plane
 * @param far_z: far flipping plane
 */
static mat4 mat4_camera_frustum(float left, float right,
                                float bottom, float top,
                                float near_z, float far_z) {
    // from cglm/cam.h/glm_frustum
    float rl = (float) 1 / (right - left);
    float tb = (float) 1 / (top - bottom);
    float fn = (float) -1 / (far_z - near_z);
    float nv = (float) 2 * near_z;

    mat4 res = {{0}};
    res.m[0][0] = nv * rl;
    res.m[1][1] = nv * tb;
    res.m[2][0] = (right + left) * rl;
    res.m[2][1] = (top + bottom) * tb;
    res.m[2][2] = (far_z + near_z) * fn;
    res.m[2][3] = (float) -1;
    res.m[3][2] = far_z * nv * fn;
    return res;
}

/**
 * Creates a perspective camera matrix.
 * @param fovy: field of view angle [rad]
 * @param aspect: width/height ratio
 * @param near_z: near clipping plane
 * @param far_z: far flipping plane
 */
static mat4 mat4_camera_perspective(float fovy, float aspect, float near_z, float far_z) {
    // from cglm/cam.h/glm_perspective
    float f = (float) 1 / sca_tan(fovy * (float) 0.5);
    float fn = (float) 1 / (near_z - far_z);

    mat4 res = {{0}};
    res.m[0][0] = f / aspect;
    res.m[1][1] = f;
    res.m[2][2] = (near_z + far_z) * fn;
    res.m[2][3] = (float) -1;
    res.m[3][2] = (float) 2 * near_z * far_z * fn;
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

    mat4 res = mat4_eye();
    res.col[0].xyz = s;
    res.col[1].xyz = u;
    res.col[2].xyz = vec3_neg(f);
    res.col[3].x = -vec3_dot(s, eye);
    res.col[3].y = -vec3_dot(u, eye);
    res.col[3].z = vec3_dot(f, eye);
    return res;
}

#endif //M_UTILS_CAMERA_H
