#include "r/r.h"
#include "u/pose.h"
#include "rhc/alloc.h"
#include "mathc/float.h"
#include "multitouchcursor.h"


#define INNER_RADIUS 8

MultiTouchCursor *multitouchcursor_new(Brush *brush, Palette *palette) {
    MultiTouchCursor *self = rhc_calloc(sizeof *self);
    
    
    self->L.cursor = ro_batch_new(4, r_texture_new_white_pixel());
    for(int i=0; i<4; i++) {
        self->L.cursor.rects[i].color = (vec4) {{0.25, 0.25, 0.25, 0.5}};        
    }
    
    return self;
}

void multitouchcursor_kill(MultiTouchCursor **self_ptr) {
    MultiTouchCursor *self = *self_ptr;
    if(!self)
        return;
    
    ro_batch_kill(&self->L.cursor);    
        
    rhc_free(self);
    *self_ptr = NULL;
}

void multitouchcursor_update(MultiTouchCursor *self, float dtime, const Camera_s *cam) {
    float x = self->L.pos.x;
    float y = self->L.pos.y;
    float l = x-INNER_RADIUS;
    float r = x+INNER_RADIUS+1;
    float b = y-INNER_RADIUS-1;
    float t = y+INNER_RADIUS;
    
    self->L.cursor.rects[0].pose = u_pose_new_aa_lrbt(cam->RO.left, l, y-1, y);
    self->L.cursor.rects[1].pose = u_pose_new_aa_lrbt(r, cam->RO.right, y-1, y);
    self->L.cursor.rects[2].pose = u_pose_new_aa_lrbt(x, x+1, cam->RO.bottom, b);
    self->L.cursor.rects[3].pose = u_pose_new_aa_lrbt(x, x+1, t, cam->RO.top);
}

void multitouchcursor_render(const MultiTouchCursor *self, const mat4 *cam_mat) {
    ro_batch_render(&self->L.cursor, cam_mat, true);
}

bool multitouchcursor_pointer_event(MultiTouchCursor *self, ePointer_s pointer) {
    if(pointer.id==0) {
        self->L.pos = vec2_floor(pointer.pos.xy);
        self->L.pos.y += 64;
        
    }
    
    return true;
}
