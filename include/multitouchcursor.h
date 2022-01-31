#ifndef PIXELC_MULTITOUCHCURSOR_H
#define PIXELC_MULTITOUCHCURSOR_H

#include "e/input.h"
#include "r/ro_types.h"
#include "brush.h"
#include "palette.h"

typedef struct {
    Brush *brush_ref;
    Palette *palette_ref;
    
    struct {
        RoBatch cursor;
        vec2 pos;
    } L;
} MultiTouchCursor;


MultiTouchCursor *multitouchcursor_new(Brush *brush, Palette *palette);

void multitouchcursor_kill(MultiTouchCursor **self_ptr);

void multitouchcursor_update(MultiTouchCursor *self, float dtime, const Camera_s *cam);

void multitouchcursor_render(const MultiTouchCursor *self, const mat4 *cam_mat);

bool multitouchcursor_pointer_event(MultiTouchCursor *self, ePointer_s pointer);


#endif //PIXELC_MULTITOUCHCURSOR_H
