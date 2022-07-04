#ifndef PIXELC_PALETTE_H
#define PIXELC_PALETTE_H

#include "e/input.h"
#include "u/color.h"
#include "u/image.h"

#define PALETTE_MAX 128
#define PALETTE_NAME_MAX 32

struct Palette_Globals {
    vec4 ro_color; // render object color (default R_COLOR_WHITE)

    bool include_transparent_at_set_colors;
    bool auto_save_config;

    struct {
        uColor_s palette[PALETTE_MAX];
        int palette_size;
        int palette_id;
        char palette_name[PALETTE_NAME_MAX];
        int max_palettes;
    } RO; // read only
};
extern struct Palette_Globals palette;


void palette_init();

void palette_update(float dtime);

void palette_render(const mat4 *camera_mat);

// return true if the pointer was used (indicate event done)
bool palette_pointer_event(ePointer_s pointer);

float palette_get_hud_size();

mat4 palette_get_pose();

// returns a new image which has to be killed
uImage palette_as_image();

bool palette_contains_pos(vec2 pos);

// may return -1, if custom color is selected
int palette_get_color();

void palette_set_color(int index);

// sets the "select" render object to the given pose
void palette_set_custom_select(mat4 select_pose);

// displays info above the palette for a few seconds
// pass NULL to hide it immediately
void palette_set_info(const char *info);

// creates an uImage and calls palette_set_palette
void palette_set_colors(const uColor_s *colors, int size, const char *name);

// calls palette_set_colors with the unique colors of palette
void palette_set_palette(uImage colors, const char *name);

// loads a palette by its id
void palette_load_palette(int id);

// saves the given palette into the config and calls palette_set_palette
//   (which will take the ownership of palette_sink)
// calls palette_save_config
void palette_append_palette(uImage colors, const char *name);

// deletes the palette with the given id from the config, may change the current palette to the previous config palette
// there must be at least 2 palettes in the config to delete a palette (min. 1 palette)
// call palette_save_config to save it
void palette_delete_palette(int id);

// creates the default palette files
// sets the palette to the first file
// calls palette_save_config
void palette_reset_palette_files();

// saves the config to the savestate config.json 
// uses object "palette"
void palette_save_config();

// loads the config from the savestate config.json
// uses object "palette"
void palette_load_config();


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
