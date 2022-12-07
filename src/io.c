#include "s/file.h"
#include "s/str.h"
#include "e/io.h"
#include "m/int.h"
#include "m/uchar.h"
#include "canvas.h"
#include "tile.h"
#include "ext_gifenc.h"
#include "io.h"



struct Io_Globals io;


//
// private
//


#define TYPE int
#define KEY uColor_s
#define CLASS ColorMap
#define FN_NAME colormap
#include "s/hashmap_trivial.h"



static void save_gif(uSprite sprite, const char *file) {
    s_assume(sprite.rows == 1, "only for frames");

    int w = sprite.img.cols;
    int h = sprite.img.rows;

    // gifenc expects a color palatte and frames that use indices of the palettes as pixels
    // max. palette size is 256
    ucvec3 *palette = s_new0(ucvec3, 256);
    // pos 0 == transparent
    int size = 1;

    // hashmap from uColor_s as key to the color palette
    ColorMap cm = colormap_new(256);
    for(int idx = 0; idx<w*h*sprite.img.layers; idx++) {
        uColor_s col = *u_image_pixel_index(sprite.img, idx, 0);
        if(col.a == 0) {
            continue;
        }
        int *pos = colormap_get(&cm, col);
        if(*pos<=0) {
            palette[size] = col.rgb;
            *pos = size;
            size++;
            if(size>=256) {
                break;
            }
        }
    }

    ge_GIF *gif = ge_new_gif(
            file,  /* file name */
            w, h,           /* canvas size */
            (su8*) palette,
            8,              /* palette depth == log2(# of colors) */
            0,             /* transparency at palette[0] */
            0               /* infinite loop */
    );

    if(!gif) {
        s_log_error("failed to create gif file header");
        goto CLEAN_UP;
    }

    /* draw some frames */
    for (int frame = 0; frame < sprite.cols; frame++) {
        for (int idx = 0; idx < w*h; idx++) {
            uColor_s col = *u_image_pixel_index(sprite.img, idx, frame);
            int col_id = 0;

            // grab color index of the palette via the hashmap
            if(col.a != 0) {
                int *pos = colormap_get(&cm, col);
                if(*pos>0 && *pos<256)
                    col_id = *pos;
            }
            gif->frame[idx] = (su8) col_id;
        }

        // gifenc delay uses 1/100 of a second
        ge_add_frame(gif, sca_ceil(100*canvas.frame_times[frame]));
    }

    /* remember to close the GIF */
    ge_close_gif(gif);

    CLEAN_UP:

    s_free(palette);
    colormap_kill(&cm);
}


//
// public
//


void io_init() {
    io.image_save_merged = true;
    io.hd_multiplyer = 8;
}

const char *io_config_file() {
    return e_io_savestate_file_path("config.json");
}

void io_config_clear_files() {
    s_log("emptying the files");
    s_file_write(io_config_file(), s_strc(""), true);
    canvas_clear_all_base_tabs();
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

    uImage hd = u_image_new_clone_scaled(img.cols * io.hd_multiplyer, img.rows * io.hd_multiplyer, false, img);

    u_image_save_file(hd, "image_hd.png");
    u_image_kill(&hd);
    u_image_kill(&img);
    e_io_offer_file_as_download("image_hd.png");
}

void io_gif_save() {
    uImage img;
    if(io.image_save_merged)
        img = canvas_get_merged_image();
    else
        img = canvas_get_full_image();
    s_log("save gif merged: %i, size: %i %i",
          io.image_save_merged,
          img.cols, img.rows);


    s_log_trace("reorder");
    uSprite sprite = u_sprite_new_reorder_from_image(canvas.RO.frames, img);

    s_log_trace("saving");
    save_gif(sprite, "animation.gif");
    u_sprite_kill(&sprite);
    u_image_kill(&img);

    s_log_trace("offer as download");
    e_io_offer_file_as_download("animation.gif");
    s_log_trace("end");
}

void io_gif_hd_save() {
    uImage img;
    if(io.image_save_merged)
        img = canvas_get_merged_image();
    else
        img = canvas_get_full_image();
    s_log("save gif merged hd: %i, size: %i %i",
          io.image_save_merged,
          img.cols, img.rows);

    uImage hd = u_image_new_clone_scaled(img.cols * io.hd_multiplyer, img.rows * io.hd_multiplyer, false, img);

    uSprite sprite = u_sprite_new_reorder_from_image(canvas.RO.frames, hd);

    save_gif(sprite, "animation_hd.gif");
    u_sprite_kill(&sprite);
    u_image_kill(&img);
    u_image_kill(&hd);
    e_io_offer_file_as_download("animation_hd.gif");
}

void io_tilemap_save() {
    uImage img = tile_get_tilemap_preview();
    if(!u_image_valid(img)) {
        s_log_error("failed, invalid");
        return;
    }
    s_log("save tilemap: size: %i %i",
          img.cols, img.rows);

    u_image_save_file(img, "tilemap.png");
    u_image_kill(&img);
    e_io_offer_file_as_download("tilemap.png");
}

void io_tilemap_hd_save() {
    uImage img = tile_get_tilemap_preview();
    if(!u_image_valid(img)) {
        s_log_error("failed, invalid");
        return;
    }
    s_log("save tilemap hd: size: %i %i",
          img.cols, img.rows);

    uImage hd = u_image_new_clone_scaled(img.cols * io.hd_multiplyer, img.rows * io.hd_multiplyer, false, img);

    u_image_save_file(hd, "tilemap_hd.png");
    u_image_kill(&img);
    u_image_kill(&hd);
    e_io_offer_file_as_download("tilemap_hd.png");
}
