
#include "mod_tiles.h"
#include "mod_canvas.h"
#include "palette.h"
#include "mod.h"



struct Mod_Globals mod;



//
// public
//

void mod_init() {
    mod_canvas_init();
    mod.opt_mod_on_canvas_update = mod_canvas_on_canvas_update_fn;
    mod.opt_canvas_get_size = mod_canvas_canvas_get_size_fn;
    mod.opt_canvas_get_cr = mod_canvas_canvas_get_cr_fn;
    mod_tiles_init();
    palette_load_palette(0);
}
