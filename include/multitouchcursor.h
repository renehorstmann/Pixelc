#ifndef PIXELC_MULTITOUCHCURSOR_H
#define PIXELC_MULTITOUCHCURSOR_H

//
// multi touch cursor for touch devices
//

#include "e/input.h"


struct MultiTouchCursor_Globals {
    vec4 pos;
    bool active;
};
extern struct MultiTouchCursor_Globals multitouchcursor;


void multitouchcursor_init();

void multitouchcursor_update(float dtime);

void multitouchcursor_render(const mat4 *cam_mat);

// changes the pointer, if active
bool multitouchcursor_pointer_event(ePointer_s *in_out_pointer);


#endif //PIXELC_MULTITOUCHCURSOR_H
