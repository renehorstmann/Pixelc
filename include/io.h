#ifndef PIXELC_IO_H
#define PIXELC_IO_H

//
// save the canvas image as png or gif
//

#include "s/s.h"

struct Io_Globals {
    // defaults to true
    bool image_save_merged;
    
    // defaults to 8
    int hd_multiplyer;

    // for io_project_apply_loaded
    bool project_applicable;
};
extern struct Io_Globals io;

void io_init();

const char *io_config_file();

void io_config_clear_files();

// saves canvas as image.png
// merges layers if io.image_save_merged
void io_image_save();

// saves canvas scaled by io.hd_multiplyer as image_hd.png
// merges layers if io.image_save_merged
void io_image_hd_save();

// saves the frame animation as animation.gif
// merges layers if io.image_save_merged
void io_gif_save();

// saves the frame animation scaled by io.hd_multiplyer as animation_hd.gif
// merges layers if io.image_save_merged
void io_gif_hd_save();

// saves the tilemap preview as tilemap.png
// only saves if tile.active && tile.canvas_active
// always merges layers
void io_tilemap_save();

// saves the tilemap preview scaled by io.hd_multiplyer as image_hd.png
// only saves if tile.active && tile.canvas_active
// always merges layers
void io_tilemap_hd_save();

// saves the full project as a .tar archive (as project.tar)
// includes:
//      - 9 tab images
//      - 16 tilemaps
//      - some_settings as json
void io_project_save();

// loads a .tar project. call apply_loaded to apply it (see io_project_save)
// returns and sets io.project_applicable
bool io_project_load();

// loads the file project.tar (see io_project_save)
void io_project_apply_loaded();


#endif //PIXELC_IO_H
