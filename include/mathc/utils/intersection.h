#ifndef MATHC_UTILS_INTERSECTION_H
#define MATHC_UTILS_INTERSECTION_H

#include <stdbool.h>
#include "../vec/vec3.h"
#include "../mat/mat3.h"

#ifndef INTERSECTION_EPSILON
#define INTERSECTION_EPSILON 0.01f
#endif

/** returns false if planes are parallel */
static bool intersection_plane_plane(vec3 *out_pos, vec3 *out_dir,
                                     vec4 plane_hessian_a, vec4 plane_hessian_b) {
    // parallel check
    if (vec3_dot(plane_hessian_a.xyz, plane_hessian_b.xyz) > (1.0f - INTERSECTION_EPSILON))
        return false;

    // line dir is orthogonal to both plane orthogonals (nx ny nz)
    vec3 dir = vec3_cross(plane_hessian_a.xyz, plane_hessian_b.xyz);
    dir = vec3_normalize(dir);

    // hessian: (nx, ny, nz, d)
    // distance point to plane = x*nx + y*ny + z*nz + 1*d

    mat3 A = {{0}};
    A = mat3_set_row(A, plane_hessian_a.xyz, 0);
    A = mat3_set_row(A, plane_hessian_b.xyz, 1);
    A = mat3_set_row(A, dir, 2);

    // distance to planes should be 0, so -1*d
    vec3 B = {{-plane_hessian_a.w, -plane_hessian_b.w, 0}};

    // solve A * X = B
    // X = A^-1 * B
    vec3 X = mat3_mul_vec(mat3_inv(A), B);

    *out_pos = X;
    *out_dir = dir;

    return true;
}
/** returns false if planes are parallel */
static int intersection_plane_plane_v(float *out_pos, float *out_dir,
                                      const float *plane_hessian_a, const float *plane_hessian_b) {
    return intersection_plane_plane((vec3 *) out_pos, (vec3 *) out_dir,
                                    Vec4(plane_hessian_a), Vec4(plane_hessian_b));
}


/** returns false if plane and line are parallel */
static bool intersection_plane_line(vec3 *out_pos, vec4 plane_hessian,
                                    vec3 line_pos, vec3 line_dir) {
    float plane_line_dot = vec3_dot(plane_hessian.xyz, line_dir);

    // parallel check
    if (fabsf(plane_line_dot) < INTERSECTION_EPSILON)
        return false;

    vec3 plane_point = vec3_scale(plane_hessian.xyz, -plane_hessian.w);
    vec3 w = vec3_sub_vec(line_pos, plane_point);
    float si = -vec3_dot(plane_hessian.xyz, w) / plane_line_dot;

    vec3 si_dir = vec3_scale(line_dir, si);

    // pos = w + si_dir + plane_point
    *out_pos = vec3_add_vec(vec3_add_vec(w, si_dir), plane_point);
    return true;
}
/** returns false if plane and line are parallel */
static bool intersection_plane_line_v(float *out_pos, const float *plane_hessian,
                                      const float *line_pos, const float *line_dir) {
    return intersection_plane_line((vec3 *) out_pos, Vec4(plane_hessian), Vec3(line_pos), Vec3(line_dir));
}


/** returns t (line_pos + line_dir * t), or NAN if not intersecting */
static float intersection_triangle_line(vec3 v0, vec3 v1, vec3 v2,
                                        vec3 line_pos, vec3 line_dir,
                                        bool culling) {
    vec3 v0v1 = vec3_sub_vec(v1, v0);
    vec3 v0v2 = vec3_sub_vec(v2, v0);
    vec3 pvec = vec3_cross(line_dir, v0v2);
    float det = vec3_dot(v0v1, pvec);

    if (culling) {
        if (det < INTERSECTION_EPSILON)
            return NAN;
    } else {
        if (fabsf(det) < INTERSECTION_EPSILON)
            return NAN;
    }

    float inv_det = 1.0f / det;

    vec3 tvec = vec3_sub_vec(line_pos, v0);
    float u = vec3_dot(tvec, pvec) * inv_det;
    if (u < 0 || u > 1)
        return NAN;

    vec3 qvec = vec3_cross(tvec, v0v1);
    float v = vec3_dot(line_dir, qvec) * inv_det;
    if (v < 0 || u + v > 1)
        return NAN;

    return vec3_dot(v0v2, qvec) * inv_det;
}
/** returns t (line_pos + line_dir * t), or NAN if not intersecting */
static float intersection_triangle_line_v(const float *v0, const float *v1, const float *v2,
                                          const float *line_pos, const float *line_dir,
                                          bool culling) {
    return intersection_triangle_line(Vec3(v0), Vec3(v1), Vec3(v2), Vec3(line_pos), Vec3(line_dir), culling);
}


/** returns false if lines are parallel, searches for the nearest distance points */
static bool intersection_line_line(float *out_tau_a, float *out_tau_b,
                                   vec3 line_a_pos, vec3 line_a_dir,
                                   vec3 line_b_pos, vec3 line_b_dir) {
    // Book: Real Time Collision Detection: section 5.1.8 Closest Point of Two Lines
    vec3 r = vec3_sub_vec(line_a_pos, line_b_pos);

    float a = vec3_dot(line_a_dir, line_a_dir);
    float b = vec3_dot(line_a_dir, line_b_dir);
    float c = vec3_dot(line_a_dir, r);
    float e = vec3_dot(line_b_dir, line_b_dir);
    float f = vec3_dot(line_b_dir, r);

    float d = a * e - b * b;

    // parallel check
    if (fabsf(d) < INTERSECTION_EPSILON)
        return false;

    *out_tau_a = (b * f - c * e) / d;
    *out_tau_b = (a * f - b * c) / d;
    return true;
}
/** returns false if lines are parallel, searches for the nearest distance points */
static bool intersection_line_line_v(float *out_tau_a, float *out_tau_b,
                                     const float *line_a_pos, const float *line_a_dir,
                                     const float *line_b_pos, const float *line_b_dir) {
    return intersection_line_line(out_tau_a, out_tau_b, Vec3(line_a_pos), Vec3(line_a_dir),
                                  Vec3(line_b_pos), Vec3(line_b_dir));
}


#endif //MATHC_UTILS_INTERSECTION_H
