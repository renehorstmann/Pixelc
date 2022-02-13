#ifndef PIXELC_BRUSH_H
#define PIXELC_BRUSH_H

#include "e/input.h"
#include "u/color.h"
#include "canvas.h"
#include "selection.h"
#include "brushmode.h"

struct Toolbar;

enum brush_modes {
    BRUSH_MODE_FREE,
    BRUSH_MODE_DOT,
    BRUSH_MODE_DITHER,
    BRUSH_MODE_DITHER_INV,
    BRUSH_MODE_FILL,
    BRUSH_MODE_FILL8,
    BRUSH_MODE_REPLACE,
    BRUSH_NUM_MODES
};


typedef struct Brush {
    BrushMode *brushmode;

    Canvas *canvas_ref;
    
    uColor_s current_color;
    uColor_s secondary_color;
    enum brush_modes mode;
    bool secondary_as_current;
    bool shading_active;
    bool render_hover_preview;
    bool auto_save_config;
    
    struct {
        const Selection *selection_ref;
    } in;
    
    struct {
        uImage kernel;
        rTexture kernel_tex;
        int kernel_id;
        int max_kernels;
    } RO; // read only
    
    struct {
        bool hovering;
        bool hovering_change;
        bool change;
        
        char **kernel_files;
    } L;
} Brush;

Brush *brush_new(Canvas *canvas);

void brush_pointer_event(Brush *self, ePointer_s pointer);

bool brush_draw_pixel(Brush *self, int c, int r, uColor_s kernel_color);

bool brush_draw(Brush *self, int c, int r);

void brush_abort_current_draw(Brush *self);

void brush_clear(Brush *self);

// moves ownership of kernel_sink to brush
void brush_set_kernel(Brush *self, uImage kernel_sink);

// loads a kernel by its id
void brush_load_kernel(Brush *self, int id);

// saves kernel_sink into the config and calls brush_set_kernel 
//   (which will take the ownership of kernel_sink)
// calls brush_save_config
void brush_append_kernel(Brush *self, uImage kernel_sink, const char *name);

// creates the default kernel files
// sets self->kernel to the first new kernel file
// also calls brush_save_kernel
void brush_reset_kernel_files(Brush *self);

// saves the config to the savestate config.json 
// uses object "brush"
void brush_save_config(const Brush *self);

// loads the config from the savestate config.json
// uses object "brush"
void brush_load_config(Brush *self);


//
// brush_kernel creation, see brush_kernel_defaults.c
//

// returns a !u_image_valid terminated list of default kernels
// call brush_kernel_kill_defaults to kill the list
uImage *brush_kernel_defaults_new();

void brush_kernel_defaults_kill(uImage **self_ptr);




#endif //PIXELC_BRUSH_H
