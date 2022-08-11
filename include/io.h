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


#endif //PIXELC_IO_H
