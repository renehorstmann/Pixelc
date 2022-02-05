#ifndef PIXELC_TOOLBAR_H
#define PIXELC_TOOLBAR_H

#include "u/container.h"
#include "tool.h"

typedef struct {
    ToolRefs refs;
    
    Tool **all;
    int all_len;
    
    Tool **active;
    int active_len;
    
    uContainer container;
    
} Toolbar;


Toolbar *toolbar_new(Camera_s *cam, Canvas *canvas,
        Brush *brush, Palette *palette);

void toolbar_update(Toolbar *self, float dtime);

void toolbar_render(const Toolbar *self, const mat4 *cam_mat);

// returns toolbar_contains(pointer.pos.xy)
bool toolbar_pointer_event(Toolbar *self, ePointer_s pointer);

float toolbar_size(const Toolbar *self);

// returns true if pos is within the toolbar
bool toolbar_contains(const Toolbar *self, vec2 pos);

#endif //PIXELC_TOOLBAR_H
