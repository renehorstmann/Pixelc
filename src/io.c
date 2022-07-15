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
    canvas_reload();
    uSprite c = canvas.RO.sprite;
    s_log("save merged: %i, size: %i %i %i %i", 
            io.image_save_merged, 
            c.img.cols, c.img.rows,
            c.cols, c.rows);
    
    if(io.image_save_merged) {
        uSprite sprite = u_sprite_new_clone_merge_row_down_full(c);
        
        s_log_debug("merged size: %i %i %i %i",
                sprite.img.cols, sprite.img.rows,
                sprite.cols, sprite.rows);
        u_sprite_save_file(sprite, "image.png");
        u_sprite_kill(&sprite);
    } else {
        u_sprite_save_file(c, "image.png");
    }
    e_io_offer_file_as_download("image.png");
}

void io_image_hd_save() {
    canvas_reload();
    uSprite c = canvas.RO.sprite;
    s_log("save merged: %i, size: %i %i %i %i", 
            io.image_save_merged, 
            c.img.cols, c.img.rows,
            c.cols, c.rows);
    
    uSprite sprite = c;
    if(io.image_save_merged) {
        sprite = u_sprite_new_clone_merge_row_down_full(sprite);
        s_log_debug("merged size: %i %i %i %i",
                sprite.img.cols, sprite.img.rows,
                sprite.cols, sprite.rows);
    }
    
    int scale_w = sca_ceil((float) HD_MIN_SIZE / sprite.img.cols);
    int scale_h = sca_ceil((float) HD_MIN_SIZE / sprite.img.rows);
    int scale = isca_max(scale_w, scale_h);
    uSprite hd = u_sprite_new_clone_scaled(sprite.img.cols * scale, sprite.img.rows * scale, false, sprite);
    
    u_sprite_save_file(hd, "image_hd.png");
    u_sprite_kill(&hd);
    if(io.image_save_merged) {
        u_sprite_kill(&sprite);
    }
    e_io_offer_file_as_download("image_hd.png");
}

void io_image_import() {
    s_log("import");
    
}
