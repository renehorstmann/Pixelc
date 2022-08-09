#include "r/r.h"
#include "u/pose.h"
#include "m/int.h"
#include "mod_tiles.h"
#include "canvas.h"
#include "selectionctrl.h"
#include "mod_canvas.h"

struct ModCanvas_Globals mod_canvas;

static struct {
    rFramebuffer fb;
    uSprite sprite;
    rTexture tex;
    RoBatch tiles[MOD_TILES_MAX_FILES];
    ivec2 origin;

    bool was_iso;
} L;


static ivec2 get_framebuffer_size() {
    uSprite c = canvas.RO.sprite;
    int cols, rows;
    if (mod_canvas.iso) {
        cols = MOD_TILES_TILE_COLS
               + (c.img.cols - 1 + c.img.rows - 1) * MOD_TILES_TILE_COLS / 2;
        rows = MOD_TILES_TILE_ROWS
               + (c.img.cols - 1 + c.img.rows - 1) * MOD_TILES_TILE_ROWS / 4
               + (c.rows - 1) * MOD_TILES_TILE_ROWS / 2;

        L.origin.x = cols / 2 + (c.img.rows - c.img.cols - 2) * MOD_TILES_TILE_COLS / 4;
        L.origin.y = -(c.rows - 1) * MOD_TILES_TILE_ROWS / 2;
    } else {
        cols = c.img.cols * MOD_TILES_TILE_COLS;
        rows = c.img.rows * MOD_TILES_TILE_ROWS;
    }

    return (ivec2) {{cols, rows}};
}


static void reset_framebuffer(ivec2 fbo_size, ivec2 sprites) {
    s_log("fbo_size.x, fbo_size.y; sprites.x, sprites.y: %i, %i; %i, %i",
          fbo_size.x, fbo_size.y, sprites.x, sprites.y);

    r_framebuffer_kill(&L.fb);
    L.fb = r_framebuffer_new(fbo_size.x, fbo_size.y * sprites.x * sprites.y);
    u_sprite_kill(&L.sprite);
    L.sprite = u_sprite_new_empty(fbo_size.x, fbo_size.y, sprites.x, sprites.y);
    r_texture_kill(&L.tex);
    L.tex = r_texture_new_sprite_buffer(fbo_size.x, fbo_size.y, sprites.x, sprites.y, NULL);
}

static void set_tile_pose(int tile_id, int batch_id, int c, int r, int sc, int sr, int layer) {
    float x, y;
    x = c * MOD_TILES_TILE_COLS;
    y = -r * MOD_TILES_TILE_ROWS;

    y -= L.sprite.img.rows * layer;
    L.tiles[tile_id].rects[batch_id].pose = u_pose_new_aa(x, y,
                                                          MOD_TILES_TILE_COLS, MOD_TILES_TILE_ROWS);
}

static void set_tile_pose_iso(int tile_id, int batch_id, int c, int r, int sc, int sr, int layer) {
    float x, y;
    x = L.origin.x + (c - r) * MOD_TILES_TILE_COLS / 2;
    y = L.origin.y - (c + r) * MOD_TILES_TILE_ROWS / 4
        + sr * MOD_TILES_TILE_ROWS / 2;

    y -= L.sprite.img.rows * layer;
    L.tiles[tile_id].rects[batch_id].pose = u_pose_new_aa(x, y,
                                                          MOD_TILES_TILE_COLS, MOD_TILES_TILE_ROWS);
}

static void reset_renderobject(int ccols, int crows, int scols, int srows) {
    s_log("ccols, crows; scols, srows: %i, %i; %i, %i", ccols, crows, scols, srows);
    for (int i = 0; i < mod_tiles.size; i++) {
        ro_batch_kill(&L.tiles[i]);
        L.tiles[i] = ro_batch_new(ccols * crows * scols * srows, mod_tiles.textures[i]);
        L.tiles[i].owns_tex = false;
        int t = 0;

        if (mod_canvas.iso) {
            for (int sr = 0; sr < srows; sr++) {
                for (int sc = 0; sc < scols; sc++) {
                    for (int cr = 0; cr < crows; cr++) {
                        for (int cc = 0; cc < ccols; cc++) {
                            int layer = sr*scols + sc;
                            set_tile_pose_iso(i, t++, cc, cr, sc, sr, layer);
                        }
                    }
                }
            }
        } else {
            for (int sr = 0; sr < srows; sr++) {
                for (int sc = 0; sc < scols; sc++) {
                    for (int cr = 0; cr < crows; cr++) {
                        for (int cc = 0; cc < ccols; cc++) {
                            int layer = sr*scols + sc;
                            set_tile_pose(i, t++, cc, cr, sc, sr, layer);
                        }
                    }
                }
            }
        }
    }
}

static void set_tile(int batch_id, int col, int row, int layer) {
    uImage img = canvas.RO.image;
    uColor_s color = *u_image_pixel(img, col, row, layer);
    int tile_id = color.r - 1;
    int tile_x = color.g;
    int tile_y = color.b;
    for (int t = 0; t < mod_tiles.size; t++) {
        if (t == tile_id) {
            L.tiles[t].rects[batch_id].sprite.x = tile_x;
            L.tiles[t].rects[batch_id].sprite.y = tile_y;
            L.tiles[t].rects[batch_id].color.a = 1;
        } else {
            L.tiles[t].rects[batch_id].color.a = 0;
        }
    }
}

static void update_ros() {
    uImage img = canvas.RO.image;
    int batch_id = 0;
    for (int l = 0; l < img.layers; l++) {
        for (int r = 0; r < img.rows; r++) {
            for (int c = 0; c < img.cols; c++) {
                set_tile(batch_id++, c, r, l);
            }
        }
    }
}


//
// public
//

void mod_canvas_init() {
    L.sprite.img.layers = 1;
}

ivec2 mod_canvas_canvas_get_size_fn() {
    if (!mod_canvas.iso) {
        return (ivec2) {{canvas.RO.image.cols, canvas.RO.image.rows}};
    }
    return (ivec2) {{L.fb.tex.size.x, L.fb.tex.size.y / L.sprite.img.layers}};
}

ivec2 mod_canvas_canvas_get_cr_fn(vec2 pointer_pos) {
    if (!mod_canvas.iso) {
        return (ivec2) {{(int) pointer_pos.x, (int) -pointer_pos.y}};
    }

    int layer = canvas.RO.current_layer;

    //// set_tile...
    // x = L.origin.x + (c-r) * MOD_TILES_TILE_COLS/2;
    // y = L.origin.y - (c+r) * MOD_TILES_TILE_ROWS/4
    //    + l * MOD_TILES_TILE_ROWS/2;

    pointer_pos.x -= MOD_TILES_TILE_COLS / 2;

    pointer_pos.x -= L.origin.x;
    pointer_pos.x /= MOD_TILES_TILE_COLS / 2;
    pointer_pos.y -= L.origin.y;
    pointer_pos.y -= layer * MOD_TILES_TILE_ROWS / 2;
    pointer_pos.y /= MOD_TILES_TILE_ROWS / 4;

    pointer_pos.y = -pointer_pos.y;

    // x = c-r      -> c = x+r
    // y = c+r      -> c = y-r
    // x+r = y-r    -> r = (y-x)/2
    float r = (pointer_pos.y - pointer_pos.x) / 2;
    float c = pointer_pos.x + r;
    s_log_trace("%f %f : %f %f", pointer_pos.x, pointer_pos.y, c, r);
    return (ivec2) {{(int) c, (int) r}};
}

void mod_canvas_on_canvas_update_fn() {
    selectionctrl.allowed = !mod_canvas.iso;

    uSprite c = canvas.RO.sprite;

    ivec2 fbo_size = get_framebuffer_size();
    ivec2 sprites = (ivec2) {{c.cols, c.rows}};

    // k sizes (also for startup)chec
    if (mod_canvas.iso != L.was_iso
        || fbo_size.x != L.sprite.img.cols || fbo_size.y != L.sprite.img.rows
        || sprites.x != L.sprite.cols || sprites.y != L.sprite.rows) {
        reset_framebuffer(fbo_size, sprites);
        reset_renderobject(c.img.cols, c.img.rows, sprites.x, sprites.y);
    }
    L.was_iso = mod_canvas.iso;

    // set render objects according to the canvas image
    update_ros();

    // draw in the framebuffer
    mat4 cam = r_framebuffer_camera_ortho(L.fb);
    r_render_set_framebuffer(L.fb);
    r_render_clear(R_COLOR_TRANSPARENT);
    for (int i = 0; i < mod_tiles.size; i++) {
        ro_batch_render(&L.tiles[i], &cam, true);
    }
    r_render_restore_framebuffer();

    // framebuffer to canvas texture
    r_framebuffer_get(L.fb, L.sprite.img.data);
    // reset sprites size, init with 1, layers
    r_texture_set_sprite_buffer(L.tex, L.sprite.img.data);
    canvas_reset_tex(L.tex);
}
