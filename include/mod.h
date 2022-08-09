#ifndef PIXELC_MOD_H
#define PIXELC_MOD_H
#ifdef PIXELC_USE_MOD

//
// For mods like Tilec
// To create a mod,
//     set PIXELC_USE_MOD as compile definition
//     and implement all of the following functions
//     and create "struct Mod_Globals mod;"
//

#include "s/s.h"
#include "m/types/float.h"
#include "m/types/int.h"

typedef ivec2 (*mod_canvas_get_size_fn)();
typedef ivec2 (*mod_canvas_get_cr_fn)(vec2 pointer_pos);
typedef void (*mod_on_canvas_update_fn)();

struct Mod_Globals {
    mod_canvas_get_size_fn opt_canvas_get_size;
    mod_canvas_get_cr_fn opt_canvas_get_cr;
    mod_on_canvas_update_fn opt_mod_on_canvas_update;
};
extern struct Mod_Globals mod;

// called last
void mod_init();



#else
typedef void ignore_empty_mod_file__;
#endif //PIXELC_USE_MOD
#endif //PIXELC_MOD_H
