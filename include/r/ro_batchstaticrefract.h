#ifndef R_RO_BATCHSTATICREFRACT_H
#define R_RO_BATCHSTATICREFRACT_H

//
// class to render multiple rects with a single draw call.
// its like ro_batch, but with additional reflection / refraction support.
// renders much faster than the default RoBatchStaticRefract, but the update call is more heavy
// so good to use it for large static batches, like tilemaps
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

// Like RoBatch, but with refraction
typedef struct {
    rRect_s *rects;
    int num;
    rTexture tex_main;          // used main texture
    rTexture tex_refraction;    // used refraction texture
    bool owns_tex_main;         // if true (default), tex_main will be killed by this class
    bool owns_tex_refraction;   // if true (default), tex_refraction will be killer by this clasd

    struct {
        struct rRectStatic_s *srects;
        GLuint program;         // shader
        GLuint vao;             // internal vertex array object
        GLuint vbo;             // internal vertex buffer object
    } L;
} RoBatchStaticRefract;

// returns true if the batch seems to be in a valid state, GL errors ignored
static bool ro_batchstaticrefract_valid(const RoBatchStaticRefract *self) {
    return self->rects!=NULL && self->num;
}

// returns a new invalid batch
static RoBatchStaticRefract ro_batchstaticrefract_new_invalid() {
    return (RoBatchStaticRefract) {0};
}

// creates a new batch with refraction enabled and num rRect's
// this class takes ownership of tex_*_sink (see .owns_*_tex)
// returns an invalid, for num<=0
RoBatchStaticRefract ro_batchstaticrefract_new(int num, rTexture tex_main_sink, rTexture tex_refraction_sink);


void ro_batchstaticrefract_kill(RoBatchStaticRefract *self);

// updates a subset of the batch into the gpu
void ro_batchstaticrefract_update_sub(const RoBatchStaticRefract *self, int offset, int size);

// updates only color and sprite values (faster, because the static pos and uv positions are not recomputed on the cpu)
void ro_batchstaticrefract_update_color_sprite_sub(const RoBatchStaticRefract *self, int offset, int size);

// renders a subset of the batch with refraction enabled
// scale: real pixels per pixel
// opt_view_aabb, opt_framebuffer: see note at the top of the file
// if update is true, update is called before rendering
void ro_batchstaticrefract_render_sub(const RoBatchStaticRefract *self, int num, const mat4 *camera_mat, float scale,
                                const vec4 *opt_view_aabb, const rTexture2D *opt_framebuffer,
                                bool update_sub);

// resets the texture, if .owns_tex_main is true, it will delete the old texture
void ro_batchstaticrefract_set_texture_main(RoBatchStaticRefract *self, rTexture tex_main_sink);

// resets the texture, if .owns_tex_refraction is true, it will delete the old texture
void ro_batchstaticrefract_set_texture_refraction(RoBatchStaticRefract *self, rTexture tex_refraction_sink);

// updates the natch into the gpu
static void ro_batchstaticrefract_update(const RoBatchStaticRefract *self) {
    ro_batchstaticrefract_update_sub(self, 0, self->num);
}
// updates the natch into the gpu
// updates only color and sprite values (faster, because the static pos and uv positions are not recomputed on the cpu)
static void ro_batchstaticrefract_update_color_sprite(const RoBatchStaticRefract *self) {
    ro_batchstaticrefract_update_color_sprite_sub(self, 0, self->num);
}

// rensers the batch with refraction enabled
// scale: real pixels per pixel
// opt_view_aabb, opt_framebuffer: see note at the top of the file
// if update is true, update is called before rendering
static void ro_batchstaticrefract_render(const RoBatchStaticRefract *self, const mat4 *camera_mat, float scale,
                                   const vec4 *opt_view_aabb, const rTexture2D *opt_framebuffer,
                                   bool update) {
    ro_batchstaticrefract_render_sub(self, self->num, camera_mat, scale,
                               opt_view_aabb, opt_framebuffer, update);
}


#endif //R_RO_BATCHSTATICREFRACT_H
