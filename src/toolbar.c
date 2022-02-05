#include "u/pose.h"
#include "rhc/alloc.h"
#include "rhc/log.h"
#include "mathc/float.h"
#include "toolbar.h"

Toolbar *toolbar_new(Camera_s *cam, Canvas *canvas,
        Brush *brush, Palette *palette) {
    Toolbar *self = rhc_calloc(sizeof *self);
    
    self->refs = (ToolRefs) {
        cam, canvas, brush, palette       
    };
    
    // todo init lists
    self->all = rhc_calloc(sizeof *self->all * 32);
    self->active = rhc_calloc(sizeof *self->all * 32);
    
    self->all[0] = tool_new_undo();
    self->all[1] = tool_new_redo();
    self->all[2] = tool_new_import();
    
    
    memcpy(self->active, self->all, sizeof *self->all * 32);
    
    self->all_len = self->active_len = 3;
    
    self->container = u_container_new(3, cam->RO.left, cam->RO.top);
    
    return self;
}

void toolbar_update(Toolbar *self, float dtime) {
    self->container.left = self->refs.cam->RO.left;
    self->container.top = self->refs.cam->RO.top;
    self->container.max_size = (vec2) {{
            camera_width(self->refs.cam), 
            camera_height(self->refs.cam)
    }};
    
    if(camera_is_portrait_mode(self->refs.cam)) {
        self->container.mode = U_CONTAINER_MODE_FREE_H;
    } else {
        self->container.mode = U_CONTAINER_MODE_FREE_V;
    }
    
    for(int i=0;i<self->active_len; i++) {
        self->container.items[i].size = self->active[i]->size;
    }
    
    u_container_update(&self->container);
    
    for(int i=0; i<self->active_len; i++) {
        self->active[i]->in.pos = (vec2) {{
                self->container.items[i].out.left,
                self->container.items[i].out.top
        }};
    }
    
    for(int i=0; i<self->active_len; i++) {
        self->active[i]->update(self->active[i], dtime, self->refs);
    }
}

void toolbar_render(const Toolbar *self, const mat4 *cam_mat) {
    for(int i=0; i<self->active_len; i++) {
        self->active[i]->render(self->active[i], cam_mat);
    }
}

// returns toolbar_contains(pointer.pos.xy)
bool toolbar_pointer_event(Toolbar *self, ePointer_s pointer) {
    bool contains = toolbar_contains(self, pointer.pos.xy);
    if(pointer.action != E_POINTER_UP && !contains)
        return false;
        
    for(int i=0; i<self->active_len; i++) {
        self->active[i]->pointer_event(self->active[i], pointer, self->refs);
    }
    
    return contains;
}

float toolbar_size(const Toolbar *self) {
    return camera_is_portrait_mode(self->refs.cam)?
            self->container.out.size.y 
            : self->container.out.size.x;
}

// returns true if pos is within the toolbar
bool toolbar_contains(const Toolbar *self, vec2 pos) {
    return u_pose_aa_contains(u_pose_new_aa(
            self->container.left, 
            self->container.top, 
            self->container.out.size.x, 
            self->container.out.size.y), pos);
}

