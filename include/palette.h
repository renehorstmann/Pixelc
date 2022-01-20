#ifndef PIXELC_PALETTE_H
#define PIXELC_PALETTE_H

#include "r/ro_types.h"
#include "e/input.h"
#include "u/color.h"
#include "camera.h"
#include "brush.h"

#define PALETTE_MAX 80


typedef struct {
    const Camera_s *camera_ref;
    Brush *brush_ref;

    vec4 ro_color; // render object color (default R_COLOR_WHITE)
    
    struct {
        uImage palette;
        int palette_size;
        int palette_id;
        const char *palette_name;
        int max_palettes;
    } RO; // read only

    struct {
        RoBatch palette_ro;
        RoSingle select_ro;
        RoBatch background_ro;
        int last_selected;
        float last_camera_width, last_camera_height;
        
        char **palette_files;
    } L;
} Palette;

Palette *palette_new(const Camera_s *camera, Brush *brush);

void palette_update(Palette *self, float dtime);

void palette_render(Palette *self, const mat4 *camera_mat);

// return true if the pointer was used (indicate event done)
bool palette_pointer_event(Palette *self, ePointer_s pointer);

float palette_get_hud_size(const Palette *self);

int palette_get_color(const Palette *self);

void palette_set_color(Palette *self, int index);

// creates an uImage and calls palette_set_palette
void palette_set_colors(Palette *self, const uColor_s *palette, int size);

// moves ownership of palette_sink to palette
void palette_set_palette(Palette *self, uImage palette_sink, const char *name);

// loads a palette by its id
void palette_load_palette(Palette *self, int id);

// saves palette_sink into the config and calls palette_set_palette
//   (which will take the ownership of palette_sink)
// calls palette_save_config
void palette_append_file(Palette *self, uImage palette_sink, const char *name);

// creates the default palette files
// sets the palette to the first file
// calls palette_save_config
void palette_reset_palette_files(Palette *self);

// saves the config to the savestate config.json 
// uses object "palette"
void palette_save_config(const Palette *self);

// loads the config from the savestate config.json
// uses object "palette"
void palette_load_config(Palette *self);


//
// palette_defaults creation, see palette_defaults.c
//

// returns a !u_image_valid terminated list of default palette
// call palette_kill_defaults to kill the list
uImage *palette_defaults_new();

void palette_defaults_kill(uImage **self_ptr);

// returns the name of the default palette id
// name created with malloc and return, so free it...
char *palette_defaults_name_on_heap(int id);



#endif //PIXELC_PALETTE_H
