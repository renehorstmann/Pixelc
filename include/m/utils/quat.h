#ifndef M_UTILS_QUAT_H
#define M_UTILS_QUAT_H


#include <math.h>
#include "../types/float.h"
#include "../sca/float.h"
#include "../vec/vec3.h"
#include "../vec/vec4.h"
#include "../mat/mat4.h"


/** vec4 = [0, 0, 0, 1] */
static vec4 quat_eye() {
    vec4 self;
    self.x = 0;
    self.y = 0;
    self.z = 0;
    self.w = 1;
    return self;
}


/** dst = -x, -y, -z, w */
static vec4 quat_conj(vec4 q) {
    vec4 self;
    self.x = -q.x;
    self.y = -q.y;
    self.z = -q.z;
    self.w = q.w;
    return self;
}

/** dst = inv(vec4) */
static vec4 quat_inv(vec4 q) {
    vec4 conj = quat_conj(q);
    return vec4_scale(conj, 1.0f / vec4_dot(q, q));
}


/** dst = a @ b Hamilton Product */
static vec4 quat_mul(vec4 q_a, vec4 q_b) {
    // from cglm/vec4/glm_quat_mul
    vec4 res;
    res.v[0] = q_a.v[3] * q_b.v[0] + q_a.v[0] * q_b.v[3] + q_a.v[1] * q_b.v[2] - q_a.v[2] * q_b.v[1];
    res.v[1] = q_a.v[3] * q_b.v[1] - q_a.v[0] * q_b.v[2] + q_a.v[1] * q_b.v[3] + q_a.v[2] * q_b.v[0];
    res.v[2] = q_a.v[3] * q_b.v[2] + q_a.v[0] * q_b.v[1] - q_a.v[1] * q_b.v[0] + q_a.v[2] * q_b.v[3];
    res.v[3] = q_a.v[3] * q_b.v[3] - q_a.v[0] * q_b.v[0] - q_a.v[1] * q_b.v[1] - q_a.v[2] * q_b.v[2];
    return res;
}


/** angle_axis = xyz + w=angle in rad */
static vec4 quat_from_angle_axis(vec4 angle_axis) {
    // from cglm/vec4/glm_quatv
    float a = angle_axis.w * 0.5f;
    float c = sca_cos(a);
    float s = sca_sin(a);

    vec3 axis = vec3_normalize(angle_axis.xyz);

    vec4 res;
    res.xyz = vec3_scale(axis, s);
    res.w = c;
    return res;
}


/** angle_axis = xyz + w=angle in rad */
static vec4 quat_to_angle_axis(vec4 q) {
    // from cglm/vec4/glm_quat_angle
    /*
     sin(theta / 2) = length(x*x + y*y + z*z)
     cos(theta / 2) = w
     theta          = 2 * atan(sin(theta / 2) / cos(theta / 2))
     */
    float imag_len = vec3_norm(q.xyz);
    float angle = (float) 2 * sca_atan2(imag_len, q.w);

    vec4 angle_axis;
    angle_axis.xyz = vec3_normalize(q.xyz);
    angle_axis.w = angle;
    return angle_axis;
}

/** returns the orientation of vec4 as 3*3 rotation matrix */
static mat3 quat_to_rotation_matrix(vec4 q) {
    // from cglm/vec4/glm_quat_mat3
    float norm = vec4_norm(q);
    float s = norm > 0 ? (float) 2 / norm : 0;

    float x = q.x;
    float y = q.y;
    float z = q.z;
    float w = q.w;

    float xx, xy, wx;
    float yy, yz, wy;
    float zz, xz, wz;
    xx = s * x * x;
    xy = s * x * y;
    wx = s * w * x;
    yy = s * y * y;
    yz = s * y * z;
    wy = s * w * y;
    zz = s * z * z;
    xz = s * x * z;
    wz = s * w * z;

    mat3 res;
    res.m[0][0] = (float) 1 - yy - zz;
    res.m[1][1] = (float) 1 - xx - zz;
    res.m[2][2] = (float) 1 - xx - yy;

    res.m[0][1] = xy + wz;
    res.m[1][2] = yz + wx;
    res.m[2][0] = xz + wy;

    res.m[1][0] = xy - wz;
    res.m[2][1] = yz - wx;
    res.m[0][2] = xz - wy;
    return res;
}


/** returns the orientation of a 3*3 rotation matrix as vec4 */
static vec4 quat_from_rotation_matrix(mat3 mat) {
    // from cglm/mat3/glm_mat3_quat
    vec4 res;
    float trace, r, rinv;
    trace = mat.m[0][0] + mat.m[1][1] + mat.m[2][2];
    if (trace >= 0) {
        r = sca_sqrt((float) 1 + trace);
        rinv = (float) 0.5 / r;

        res.v[0] = rinv * (mat.m[1][2] - mat.m[2][1]);
        res.v[1] = rinv * (mat.m[2][0] - mat.m[0][2]);
        res.v[2] = rinv * (mat.m[0][1] - mat.m[1][0]);
        res.v[3] = r * (float) 0.5;
    } else if (mat.m[0][0] >= mat.m[1][1] && mat.m[0][0] >= mat.m[2][2]) {
        r = sca_sqrt((float) 1 - mat.m[1][1] - mat.m[2][2] + mat.m[0][0]);
        rinv = (float) 0.5 / r;

        res.v[0] = r * (float) 0.5;
        res.v[1] = rinv * (mat.m[0][1] + mat.m[1][0]);
        res.v[2] = rinv * (mat.m[0][2] + mat.m[2][0]);
        res.v[3] = rinv * (mat.m[1][2] - mat.m[2][1]);
    } else if (mat.m[1][1] >= mat.m[2][2]) {
        r = sca_sqrt((float) 1 - mat.m[0][0] - mat.m[2][2] + mat.m[1][1]);
        rinv = (float) 0.5 / r;

        res.v[0] = rinv * (mat.m[0][1] + mat.m[1][0]);
        res.v[1] = r * (float) 0.5;
        res.v[2] = rinv * (mat.m[1][2] + mat.m[2][1]);
        res.v[3] = rinv * (mat.m[2][0] - mat.m[0][2]);
    } else {
        r = sca_sqrt((float) 1 - mat.m[0][0] - mat.m[1][1] + mat.m[2][2]);
        rinv = (float) 0.5 / r;

        res.v[0] = rinv * (mat.m[0][2] + mat.m[2][0]);
        res.v[1] = rinv * (mat.m[1][2] + mat.m[2][1]);
        res.v[2] = r * (float) 0.5;
        res.v[3] = rinv * (mat.m[0][1] - mat.m[1][0]);
    }

    return res;
}

/** returns the orientation of a 3*3 rotation matrix as vec4 */
static void quat_pose_from_pose_matrix(vec3 *out_pose_pos, vec4 *out_pose_quat, mat4 mat_pose) {
    *out_pose_pos = mat_pose.col[3].xyz;
    *out_pose_quat = quat_from_rotation_matrix(mat4_get_upper_left3(mat_pose));
}

/** returns the orientation of a 3*3 rotation matrix as vec4 */
static mat4 quat_pose_to_pose_matrix(vec3 pose_pos, vec4 pose_quat) {
    mat4 pose = mat4_eye();
    pose.col[3].xyz = pose_pos;
    mat4_set_this_upper_left3(&pose, quat_to_rotation_matrix(pose_quat));
    return pose;
}


/** returns the rotated position pos with the rotation of q */
static vec3 quat_rotate_pos(vec4 q, vec3 pos) {
    vec4 p;
    p.xyz = pos;
    p.w = 0;
    // res = q @ pos(w=0) @ conj(q)
    return quat_mul(q, quat_mul(p, quat_conj(q))).xyz;
}


/**
 * Inverts the given pose (position + orientation)
 * Same as inverting a mat4 pose
 */
static void quat_pose_inv(vec3 *out_pose_inv_pos, vec4 *out_pose_inv_quat, vec3 pose_pos, vec4 pose_quat) {
    *out_pose_inv_quat = quat_inv(pose_quat);
    *out_pose_inv_pos = vec3_neg(quat_rotate_pos(*out_pose_inv_quat, pose_pos));
}


/** returns pos transform by pose a @ b */
static vec3 quat_pose_transform_pos(vec3 a_pos, vec4 a_quat, vec3 pos_b) {
    return vec3_add_vec(a_pos, quat_rotate_pos(a_quat, pos_b));
}


/** returns pose transform of a @ b */
static void quat_pose_transform_pose(vec3 *out_pos, vec4 *out_quat,
                                     vec3 a_pos, vec4 a_quat,
                                     vec3 b_pos, vec4 b_quat) {
    *out_pos = quat_pose_transform_pos(a_pos, a_quat, b_pos);
    *out_quat = quat_mul(a_quat, b_quat);
}


/** spherical linear interpolation between a and b, t in [0 : 1] */
static vec4 quat_slerp(vec4 q_a, vec4 q_b, float t) {
    // from cglm/vec4/glm_quat_slerp
    float cos_theta = vec4_dot(q_a, q_b);

    if (sca_abs(cos_theta) >= 1)
        return q_a;

    if (cos_theta < 0) {
        q_a = vec4_neg(q_a);
        cos_theta = -cos_theta;
    }

    float sin_theta = sca_sqrt((float) 1 - cos_theta * cos_theta);

    /* LERP q_b avoid zero division */
    if (sca_abs(sin_theta) < (float) 0.001)
        return vec4_mix(q_a, q_b, t);

    /* SLERP */
    float angle = sca_acos(cos_theta);
    vec4 q1 = vec4_scale(q_a, sca_sin(((float) 1 - t) * angle));
    vec4 q2 = vec4_scale(q_b, sca_sin(t * angle));

    q1 = vec4_add_vec(q1, q2);
    return vec4_scale(q1, (float) 1 / sin_theta);
}


#endif //M_UTILS_QUAT_H
