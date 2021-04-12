#ifndef R_RO_REFRACT_SINGLE_H
#define R_RO_REFRACT_SINGLE_H

#include <stdbool.h>
#include "core.h"
#include "rect.h"


// Renders a single rect in a draw call, with refraction and reflection
//
// Uses 3 textures in total
// 1: default texture
// 2: refraction map
//    r: 128+offset for x refraction
//    g: 128+offset for y
//    b: x_stretch_value + y_stretch_value * 16
//          normal: 12+12*16    (8+4)
//          mirror x: 4+12*16   (8-4)
//    a: refraction alpha
// 3: framebuffer texture, to grab pixels for the refraction
//    defaults to r_render.framebuffer_tex
// view_aabb is the screen space in which the rect is rendered
//    in texture space (origin is top left) [0:1]
//    as center_x, _y, radius_x, _y
//    defaults to fullscreen (0.5, 0.5, 0.5, 0.5)
typedef struct {
    rRect_s rect;
    const float *vp; // mat4
    const float *scale; // float
    const float *view_aabb; // vec4
    GLuint program;
    GLuint vao;
    GLuint tex_main;
    GLuint tex_refraction;
    const GLuint *tex_framebuffer_ptr;  // init as &r_render.framebuffer_tex
    bool owns_tex_main;
    bool owns_tex_refraction;
} RoRefractSingle;

void ro_refract_single_init(RoRefractSingle *self,
        const float *vp, const float *scale_ptr,
        GLuint tex_main_sink, GLuint tex_refraction_sink);

void ro_refract_single_kill(RoRefractSingle *self);

void ro_refract_single_render(RoRefractSingle *self);

void ro_refract_single_set_texture_main(RoRefractSingle *self, GLuint tex_main_sink);

void ro_refract_single_set_texture_refraction(RoRefractSingle *self, GLuint tex_refraction_sink);


#endif //R_RO_REFRACT_SINGLE_H
