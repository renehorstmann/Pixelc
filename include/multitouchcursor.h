#ifndef PIXELC_MULTITOUCHCURSOR_H
#define PIXELC_MULTITOUCHCURSOR_H

#include "e/input.h"
#include "r/ro_types.h"
#include "camera.h"
#include "brush.h"
#include "palette.h"

typedef struct {
    const Camera_s *cam_ref;
    Palette *palette_ref;

    vec4 pos;
    bool active;
    
    struct {
        RoBatch cursor;
        vec2 start_pos;
        bool start;
        bool pressed;
    } L;
} MultiTouchCursor;


MultiTouchCursor *multitouchcursor_new(const Camera_s *cam, Palette *palette);

void multitouchcursor_kill(MultiTouchCursor **self_ptr);

void multitouchcursor_update(MultiTouchCursor *self, float dtime);

void multitouchcursor_render(const MultiTouchCursor *self, const mat4 *cam_mat);

// changes the pointer, if active
bool multitouchcursor_pointer_event(MultiTouchCursor *self, ePointer_s *in_out_pointer);


#endif //PIXELC_MULTITOUCHCURSOR_H
