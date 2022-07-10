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

const char *io_config_canvas_save_file() {
    return e_io_savestate_file_path("config_canvas_save.json");
}

void io_config_clear_files() {
    s_log("emptying the files");
    s_file_write(io_config_file(), s_strc(""), true);

    s_file_write(io_config_canvas_save_file(), s_strc(""), true);
    e_io_savestate_save();
}

void io_image_save() {
    s_log("save merged: %i", io.image_save_merged);
    if(io.image_save_merged) {
        uImage img = u_image_new_clone_merge_down_full(canvas.RO.image);
        u_image_save_file(img, "image.png");
        u_image_kill(&img);
    } else {
        u_image_save_file(canvas.RO.image, "image.png");
    }
    e_io_offer_file_as_download("image.png");
}

void io_image_hd_save() {
    s_log("save merged: %i", io.image_save_merged);
    uImage img = canvas.RO.image;
    if(io.image_save_merged) {
        img = u_image_new_clone_merge_down_full(img);
    }
    
    int scale_w = sca_ceil((float) HD_MIN_SIZE / img.cols);
    int scale_h = sca_ceil((float) HD_MIN_SIZE / img.rows);
    int scale = isca_max(scale_w, scale_h);
    uImage hd = u_image_new_clone_scaled(img.cols * scale, img.rows * scale, false, img);
    
    u_image_save_file(hd, "image_hd.png");
    u_image_kill(&hd);
    if(io.image_save_merged) {
        u_image_kill(&img);
    }
    e_io_offer_file_as_download("image_hd.png");
}

void io_image_import() {
    s_log("import");
    
}
