#ifndef PIXELC_TILE_H
#define PIXELC_TILE_H

#include "s/s.h"
#include "m/types/int.h"
#include "m/types/float.h"
#include "e/input.h"
#include "u/image.h"


enum tile_size_modes {
    TILE_MODE_8,
    TILE_MODE_16,
    TILE_MODE_32
};


#define TILE_MAX_TILESHEETS 16

struct Tile_Globals {
    bool active;
    bool canvas_active;
    bool iso;
    struct {
        int tile_size_x;
        int tile_size_y;
        int tilesheet_id;
    } RO; // read only
};
extern struct Tile_Globals tile;


void tile_init();

void tile_update(float dtime);

// returns an invalid image, if !tile.active || !tile.canvas_active
uImage tile_get_tilemap_preview();

vec2 tile_tilesheet_size();

ivec2 tile_canvas_get_size();

ivec2 tile_canvas_get_cr(vec2 pointer_pos);

void tile_on_canvas_update();


void tile_palette_update(float dtime);

void tile_palette_render(const mat4 *cam_mat);

void tile_palette_pointer_event_always(ePointer_s pointer);

void tile_palette_pointer_event(ePointer_s pointer);

vec4 tile_palette_pointer_pos(vec4 hud_pointer_pos);

float tile_palette_get_hud_size();

void tile_palette_set_custom_select(mat4 select_pose);

void tile_palette_next_palette(bool next);


void tile_set_size(int tile_size_x, int tile_size_y);

// loads a tilesheet by its id
void tile_load_tilesheet(int id);

// saves tilesheet into the config and calls tile_load_tilesheet
// will override tilesheet[id]
// calls tile_save_config
void tile_update_tilesheet(uImage tilesheet, int id);

// returns a new image from the given tilesheed id
uImage tile_get_tilesheet(int id);

// creates the default tilesheet files
// sets the tilesheet to the first file
// calls tile_save_config
void tile_reset_tilesheet_files();

// saves the config to the savestate config.json
// uses object "tile"
void tile_save_config();

// loads the config from the savestate config.json
// uses object "tile"
void tile_load_config();


#endif //PIXELC_TILE_H
