#ifndef R_RO_SINGLEREFRACT_H
#define R_RO_SINGLEREFRACT_H

//
// class to render a single rect with a draw call
// its like ro_single, but with additional reflection / refraction support.
//
//// uses 3 textures in total
//// 1: default texture
//// 2: refraction map_refract
////    r: 128+offset for x refraction
////    g: 128+offset for y
////    b: x_stretch_value + y_stretch_value * 16
////          normal: 12+12*16    (8+4)
////          mirror x: 4+12*16   (8-4)
////    a: refraction alpha
//// 3: framebuffer texture, to grab pixels for the refraction
////    defaults to r_render.framebuffer_tex
//// view_aabb is the screen space in which the rect is rendered
////    in texture space (origin is top left) [0:1]
////    as center_x, _y, radius_x, _y
////    defaults to fullscreen (0.5, 0.5, 0.5, 0.5)
//

#include "rect.h"
#include "texture.h"
#include "texture2d.h"


// Like RoSingle, but with refraction
typedef struct {
    rRect_s rect;
    rTexture tex_main;          // used main texture
    rTexture tex_refraction;    // used refraction texture
    bool owns_tex_main;         // if true (default), tex_main will be killed by this class
    bool owns_tex_refraction;   // if true (default), tex_refraction will be killer by this clasd

    struct {
        GLuint program;         // shader
        GLuint vao;             // internal vertex array object
    } L;
} RoSingleRefract;

// creates a single with refraction enabled for one rRect
// this class takes ownership of tex_sink (see .owns_tex)
RoSingleRefract ro_singlerefract_new(
        rTexture tex_main_sink, rTexture tex_refraction_sink);

void ro_singlerefract_kill(RoSingleRefract *self);

// renders the single rRect with refraction enabled
// scale: real pixels per pixel
// opt_view_aabb, opt_framebuffer: see note at the top of the file
void ro_singlerefract_render(const RoSingleRefract *self, const mat4 *camera_mat, float scale,
                             const vec4 *opt_view_aabb, const rTexture2D *opt_framebuffer);

// resets the texture, if .owns_tex_main is true, it will delete the old texture
void ro_singlerefract_set_texture_main(RoSingleRefract *self, rTexture tex_main_sink);

// resets the texture, if .owns_tex_refraction is true, it will delete the old texture
void ro_singlerefract_set_texture_refraction(RoSingleRefract *self, rTexture tex_refraction_sink);


#endif //R_RO_SINGLEREFRACT_H
