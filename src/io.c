#include "s/file.h"
#include "s/str.h"
#include "e/io.h"
#include "m/int.h"
#include "canvas.h"
#include "io.h"

#define HD_MIN_SIZE 1024


struct Io_Globals io;


void io_init() {
    io.image_save_merged = true;
}

const char *io_config_file() {
    return e_io_savestate_file_path("config.json");
}

void io_config_clear_files() {
    s_log("emptying the files");
    s_file_write(io_config_file(), s_strc(""), true);
    
    e_io_savestate_save();
}

void io_image_save() {
    uImage img;
    if(io.image_save_merged)
        img = canvas_get_merged_image();
    else
        img = canvas_get_full_image();
    s_log("save merged: %i, size: %i %i", 
            io.image_save_merged, 
            img.cols, img.rows);
    
    u_image_save_file(img, "image.png");
    u_image_kill(&img);
    e_io_offer_file_as_download("image.png");
}

void io_image_hd_save() {
    uImage img;
    if(io.image_save_merged)
        img = canvas_get_merged_image();
    else
        img = canvas_get_full_image();
    s_log("save merged hd: %i, size: %i %i", 
            io.image_save_merged, 
            img.cols, img.rows);
    
    
    int scale_w = sca_ceil((float) HD_MIN_SIZE / img.cols);
    int scale_h = sca_ceil((float) HD_MIN_SIZE / img.rows);
    int scale = isca_max(scale_w, scale_h);
    uImage hd = u_image_new_clone_scaled(img.cols * scale, img.rows * scale, false, img);
    
    u_image_save_file(hd, "image_hd.png");
    u_image_kill(&hd);
    u_image_kill(&img);
    e_io_offer_file_as_download("image_hd.png");
}

void io_gif_save() {
    
}

void io_gif_hd_save() {
    
}

void io_image_import() {
    s_log("import");
    
}
