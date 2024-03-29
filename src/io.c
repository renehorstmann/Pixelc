#include "s/file.h"
#include "s/str.h"
#include "e/io.h"
#include "m/int.h"
#include "m/uchar.h"
#include "u/json.h"
#include "canvas.h"
#include "tile.h"
#include "cameractrl.h"
#include "ext_gifenc.h"
#include "ext_microtar.h"
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
    for (int idx = 0; idx < w * h * sprite.img.layers; idx++) {
        uColor_s col = *u_image_pixel_index(sprite.img, idx, 0);
        if (col.a == 0) {
            continue;
        }
        int *pos = colormap_get(&cm, col);
        if (*pos <= 0) {
            palette[size] = col.rgb;
            *pos = size;
            size++;
            if (size >= 256) {
                break;
            }
        }
    }

    ge_GIF *gif = ge_new_gif(
            file,  /* file name */
            w, h,           /* canvas size */
            (su8 *) palette,
            8,              /* palette depth == log2(# of colors) */
            0,             /* transparency at palette[0] */
            0               /* infinite loop */
    );

    if (!gif) {
        s_log_error("failed to create gif file header");
        goto CLEAN_UP;
    }

    /* draw some frames */
    for (int frame = 0; frame < sprite.cols; frame++) {
        for (int idx = 0; idx < w * h; idx++) {
            uColor_s col = *u_image_pixel_index(sprite.img, idx, frame);
            int col_id = 0;

            // grab color index of the palette via the hashmap
            if (col.a != 0) {
                int *pos = colormap_get(&cm, col);
                if (*pos > 0 && *pos < 256)
                    col_id = *pos;
            }
            gif->frame[idx] = (su8) col_id;
        }

        // gifenc delay uses 1/100 of a second
        ge_add_frame(gif, sca_ceil(100 * canvas.frame_times[frame]));
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
    if (io.image_save_merged)
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
    if (io.image_save_merged)
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
    if (io.image_save_merged)
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
    if (io.image_save_merged)
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
    if (!u_image_valid(img)) {
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
    if (!u_image_valid(img)) {
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


void io_project_save() {
    s_log("project save");

    //
    // load resources and create copies
    //
    uJson *config = u_json_new_empty();

    for (int i = 0; i < CANVAS_MAX_TABS; i++) {
        char tab_name[64];
        char file_name[64];
        snprintf(tab_name, sizeof tab_name, "tab_%2i", i);
        snprintf(file_name, sizeof file_name, "project_save_tab_%02i.png", i);

        uSprite sprite = canvas_get_tab(i);
        if (!u_sprite_valid(sprite)) {
            sprite = u_sprite_new_zeros(32, 32, 1, 1);
        }
        u_sprite_save_file(sprite, file_name);

        uJson *tab = u_json_append_object(config, tab_name);
        u_json_append_int(tab, "frames", sprite.cols);
        u_json_append_int(tab, "layers", sprite.rows);
        // todo frame times?

        u_sprite_kill(&sprite);
    }

    for (int i = 0; i < TILE_MAX_TILESHEETS; i++) {
        char file_name[64];
        snprintf(file_name, sizeof file_name, "project_save_tilesheet_%02i.png", i);
        uImage img = tile_get_tilesheet(i);
        if (!u_image_valid(img)) {
            img = u_image_new_zeros(32, 32, 1);
        }
        u_image_save_file(img, file_name);
        u_image_kill(&img);
    }

    uJson *tiles = u_json_append_object(config, "tiles");
    u_json_append_int(tiles, "size_x", tile.RO.tile_size_x);
    u_json_append_int(tiles, "size_y", tile.RO.tile_size_y);

    u_json_save_file(config, "project_save_config.json", NULL);
    u_json_kill(&config);

    //
    // create the project.tar archive
    //

    mtar_t tar;

    // Open archive for writing
    mtar_open(&tar, "project_save.tar", "w");

    // Write files and headers
    for (int i = 0; i < CANVAS_MAX_TABS; i++) {
        char from[64];
        char to[64];
        snprintf(from, sizeof from, "project_save_tab_%02i.png", i);
        snprintf(to, sizeof to, "tab_%02i.png", i);
        sString *content = s_file_read(from, false);
        if (s_string_valid(content)) {
            mtar_write_file_header(&tar, to, content->size);
            mtar_write_data(&tar, content->data, content->size);
        }
        s_string_kill(&content);
    }
    for (int i = 0; i < TILE_MAX_TILESHEETS; i++) {
        char from[64];
        char to[64];
        snprintf(from, sizeof from, "project_save_tilesheet_%02i.png", i);
        snprintf(to, sizeof to, "tilesheet_%02i.png", i);
        sString *content = s_file_read(from, false);
        if (s_string_valid(content)) {
            mtar_write_file_header(&tar, to, content->size);
            mtar_write_data(&tar, content->data, content->size);
        }
        s_string_kill(&content);
    }
    {
        sString *content = s_file_read("project_save_config.json", false);
        if (s_string_valid(content)) {
            mtar_write_file_header(&tar, "config.json", content->size);
            mtar_write_data(&tar, content->data, content->size);
        }
        s_string_kill(&content);
    }

    // Finalize -- this needs to be the last thing done before closing
    mtar_finalize(&tar);

    // Close archive
    mtar_close(&tar);

    e_io_offer_file_as_download("project_save.tar");
}

bool io_project_load() {
    s_log("project load");

    mtar_t tar;
    mtar_header_t h;
    bool valid = true;

    valid = mtar_open(&tar, "project_load.tar", "r") == MTAR_ESUCCESS;
    if (!valid){
        s_log_info("failed to load project.tar");

        // its not ok to close not opened tar, so early return here
        io.project_applicable = valid;
        return io.project_applicable;
    }

    {
        valid = mtar_find(&tar, "config.json", &h) == MTAR_ESUCCESS;
        if(!valid) {
            s_log_warn("failed to read config.json");
            goto CLEAN_UP;
        }
        sString *content = s_string_new(h.size);
        content->size = h.size;
        valid = mtar_read_data(&tar, content->data, h.size) == MTAR_ESUCCESS;
        if(valid) {
            valid = s_file_write("project_load_config.json", s_string_get_str(content), false);
        }
        s_string_kill(&content);
        if(!valid) {
            s_log_error("failed to read and copy config.json data");
            goto CLEAN_UP;
        }
    }

    for (int i = 0; i < CANVAS_MAX_TABS; i++) {
        char from[64];
        char to[64];
        snprintf(from, sizeof from, "project_load_tab_%02i.png", i);
        snprintf(to, sizeof to, "tab_%02i.png", i);
        valid = mtar_find(&tar, to, &h) == MTAR_ESUCCESS;
        if(!valid) {
            s_log_warn("failed to read a tab: %s", to);
            goto CLEAN_UP;
        }
        sString *content = s_string_new(h.size);
        content->size = h.size;
        valid = mtar_read_data(&tar, content->data, h.size) == MTAR_ESUCCESS;
        if(valid) {
            valid = s_file_write(from, s_string_get_str(content), false);
        }
        s_string_kill(&content);
        if(!valid) {
            s_log_error("failed to read and copy tab data [%i]", i);
            goto CLEAN_UP;
        }
    }

    for (int i = 0; i < TILE_MAX_TILESHEETS; i++) {
        char from[64];
        char to[64];
        snprintf(from, sizeof from, "project_load_tilesheet_%02i.png", i);
        snprintf(to, sizeof to, "tilesheet_%02i.png", i);
        valid = mtar_find(&tar, to, &h) == MTAR_ESUCCESS;
        if(!valid) {
            s_log_warn("failed to read a tilesheet: %s", to);
            goto CLEAN_UP;
        }
        sString *content = s_string_new(h.size);
        content->size = h.size;
        valid = mtar_read_data(&tar, content->data, h.size) == MTAR_ESUCCESS;
        if(valid) {
            valid = s_file_write(from, s_string_get_str(content), false);
        }
        s_string_kill(&content);
        if(!valid) {
            s_log_error("failed to read and copy tilesheet data [%i]", i);
            goto CLEAN_UP;
        }
    }

    CLEAN_UP:
    mtar_close(&tar);

    io.project_applicable = valid;
    return io.project_applicable;
}

void io_project_apply_loaded() {
    s_log("project apply loaded");
    if(!io.project_applicable) {
        s_log_warn("not applicable...");
        return;
    }

    uJson *config = u_json_new_file("project_load_config.json");

    {
        uJson *tiles = u_json_get_object(config, "tiles");
        int size_x, size_y;
        if(!u_json_get_object_int(tiles, "size_x", &size_x)
           || !u_json_get_object_int(tiles, "size_y", &size_y)) {
            s_log_error("failed to read tile sizes");
        } else {
            tile_set_size(size_x, size_y);
        }
    }

    // backwars, so last saves tab change is on tab 0
    for(int i=CANVAS_MAX_TABS-1; i>=0; i--) {
        char tab_name[64];
        char file_name[64];
        snprintf(tab_name, sizeof tab_name, "tab_%2i", i);
        snprintf(file_name, sizeof file_name, "project_load_tab_%02i.png", i);

        uJson *tab = u_json_get_object(config, tab_name);
        int frames, layers;
        if(!u_json_get_object_int(tab, "frames", &frames)
                || !u_json_get_object_int(tab, "layers", &layers)
                || frames<=0 || frames > CANVAS_MAX_FRAMES
                || layers<=0 || layers > CANVAS_MAX_LAYERS) {
            s_log_error("failed to load tab config: %i", i);
            continue;
        }

        uSprite sprite = u_sprite_new_file(frames, layers, file_name);
        if(!u_sprite_valid(sprite)) {
            s_log_error("failed to load tab sprite: %i", i);
        }
        canvas_set_tab_id(i);
        // sink
        canvas_set_sprite(sprite, true);
    }

    // home first tab
    cameractrl_set_home();

    for(int i=0; i<TILE_MAX_TILESHEETS; i++) {
        char file_name[64];
        snprintf(file_name, sizeof file_name, "project_load_tilesheet_%02i.png", i);
        uImage img = u_image_new_file(1, file_name);
        tile_update_tilesheet(img, i);
        u_image_kill(&img);
    }

    u_json_kill(&config);
}
