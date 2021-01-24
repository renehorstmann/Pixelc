#ifndef MATHC_UTILS_ROTATION_H
#define MATHC_UTILS_ROTATION_H

#include "../vec/vec3.h"
#include "../mat/mat3.h"
#include "../mat/mat4.h"


/** creates a rotation matrix from angle_axis as xyz = axis and w = angle [rad] */
static mat3 mat3_rotation_from_angle_axis(vec4 angle_axis) {
    // from cglm/affine/glm_rotate_make
    float c = cosf(angle_axis.w);
    float s = sinf(angle_axis.w);

    vec3 axis = vec3_normalize(angle_axis.xyz);
    vec3 v = vec3_scale(axis, 1.0f - c);
    vec3 vs = vec3_scale(axis, s);

    mat3 res;
    res.col[0] = vec3_scale(axis, v.x);
    res.col[1] = vec3_scale(axis, v.y);
    res.col[2] = vec3_scale(axis, v.z);

    res.m[0][0] += c;      res.m[1][0] -= vs.z;   res.m[2][0] += vs.y;
    res.m[0][1] += vs.z;   res.m[1][1] += c;      res.m[2][1] -= vs.x;
    res.m[0][2] -= vs.y;   res.m[1][2] += vs.x;   res.m[2][2] += c;
    return res;
}
/** creates a rotation matrix from angle_axis as xyz = axis and w = angle [rad] */
static mat3 mat3_rotation_from_angle_axis_v(const float *angle_axis) {
    return mat3_rotation_from_angle_axis(Vec4(angle_axis));
}


/** creates a rotation matrix aligned to x (or y if dir_z~=x), so that the z axis is dir_z */
static mat3 mat3_rotation_from_dir_z(vec3 dir_z) {
    vec3 z = vec3_normalize(dir_z);

    // align rotation x to unit x (if unit x ~= dir_z, align to unit y)
    vec3 align_x = vec3_unit_x();
    if(fabsf(vec3_dot(z, align_x)) > 0.9f)
        align_x = vec3_unit_y();

    vec3 y = vec3_normalize(vec3_cross(z, align_x));

    vec3 x = vec3_cross(y, z);

    mat3 res;
    res.col[0] = x;
    res.col[1] = y;
    res.col[2] = z;
    return res;
}
/** creates a rotation matrix aligned to x (or y if dir_z~=x), so that the z axis is dir_z */
static mat3 mat3_rotation_from_dir_z_v(const float *dir_z) {
    return mat3_rotation_from_dir_z(Vec3(dir_z));
}


/** uses mat3_rotation_from_dir with ray_dir and sets the pose translation to ray_start */
static mat4 mat4_pose_from_ray(vec3 ray_start, vec3 ray_dir) {
    mat4 pose = mat4_eye();
    pose = mat4_set_upper_left3(pose, mat3_rotation_from_dir_z(ray_dir));
    pose.col[3].xyz = ray_start;
    return pose;
}
/** uses mat3_rotation_from_dir with ray_dir and sets the pose translation to ray_start */
static mat4 mat4_pose_from_ray_v(const float *ray_start, const float *ray_dir) {
    return mat4_pose_from_ray(Vec3(ray_start), Vec3(ray_dir));
}


#endif //MATHC_UTILS_ROTATION_H
