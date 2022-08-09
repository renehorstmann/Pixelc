#ifndef PIXELC_MOD_TILEC_MOD_CANVAS_H
#define PIXELC_MOD_TILEC_MOD_CANVAS_H

#include "s/s.h"
#include "m/types/int.h"

struct ModCanvas_Globals {
    bool iso;
};
extern struct ModCanvas_Globals mod_canvas;

void mod_canvas_init();

ivec2 mod_canvas_canvas_get_size_fn();

ivec2 mod_canvas_canvas_get_cr_fn(vec2 pointer_pos);

void mod_canvas_on_canvas_update_fn();

#endif //PIXELC_MOD_TILEC_MOD_CANVAS_H
