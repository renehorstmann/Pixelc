#ifndef PIXELC_BRUSH_H
#define PIXELC_BRUSH_H

#include "r/texture.h"
#include "e/input.h"
#include "u/color.h"
#include "selection.h"

struct Toolbar;

enum brush_modes {
    BRUSH_MODE_NONE,
    BRUSH_MODE_FREE,
    BRUSH_MODE_DOT,
    BRUSH_MODE_LINE,
    BRUSH_MODE_RECT,
    BRUSH_MODE_CIRCLE,
    BRUSH_MODE_DITHER,
    BRUSH_MODE_DITHER_INV,
    BRUSH_MODE_FILL,
    BRUSH_MODE_FILL8,
    BRUSH_MODE_REPLACE,
    BRUSH_MODE_PIPETTE,
    BRUSH_NUM_MODES
};

struct Brush_Globals {
    uColor_s current_color;
    uColor_s secondary_color;
    enum brush_modes mode;
    bool secondary_as_current;
    bool shading_active;
    bool render_hover_preview;
    bool auto_save_config;

    const Selection *selection_ref;

    struct {
        uImage kernel;
        rTexture kernel_tex;
        int kernel_id;
        int max_kernels;
    } RO; // read only
};
extern struct Brush_Globals brush;


void brush_init();

void brush_pointer_event(ePointer_s pointer);

bool brush_draw_pixel(int c, int r, uColor_s kernel_color);

bool brush_draw(int c, int r);

void brush_abort_current_draw();

void brush_clear();

// moves ownership of kernel_sink to brush
void brush_set_kernel(uImage kernel_sink);

// loads a kernel by its id
void brush_load_kernel(int id);

// saves kernel into the config and calls brush_load_kernel
// calls brush_save_config
void brush_append_kernel(uImage kernel);

// deletes the kernel with the given id from the config, may change the current kernel to the previous config kernel
// there must be at least 2 kernels in the config to delete a kernel (min. 1 kernel)
// call brush_save_config to save it
void brush_delete_kernel(int id);

// creates the default kernel files
// sets self->kernel to the first new kernel file
// also calls brush_save_kernel
void brush_reset_kernel_files();

// saves the config to the savestate config.json 
// uses object "brush"
void brush_save_config();

// loads the config from the savestate config.json
// uses object "brush"
void brush_load_config();


//
// brush_kernel creation, see brush_kernel_defaults.c
//

// returns a !u_image_valid terminated list of default kernels
// call brush_kernel_kill_defaults to kill the list
uImage *brush_kernel_defaults_new();

void brush_kernel_defaults_kill(uImage **self_ptr);


#endif //PIXELC_BRUSH_H
