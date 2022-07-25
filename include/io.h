#ifndef PIXELC_IO_H
#define PIXELC_IO_H

#include "s/s.h"

struct Io_Globals {
    // defaults to true
    bool image_save_merged;
    
    // defaults to 1024
    int hd_min_size;
};
extern struct Io_Globals io;

void io_init();

const char *io_config_file();

void io_config_clear_files();

void io_image_save();

void io_image_hd_save();

void io_gif_save();

void io_gif_hd_save();


#endif //PIXELC_IO_H
