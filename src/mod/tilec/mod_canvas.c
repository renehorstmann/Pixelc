#include "r/r.h"
#include "u/pose.h"
#include "m/int.h"
#include "mod_tiles.h"
#include "canvas.h"
#include "mod_canvas.h"

static struct {
    rFramebuffer fb;
    uSprite sprite;
    rTexture tex;
    RoBatch tiles[MOD_TILES_MAX_FILES];
    ivec2 origin;
} L;




static void reset_framebuffer(int sprite_size_x, int sprite_size_y, int sprites_cols, int sprites_rows) {
    s_log("sprite_size_x, sprite_size_y; sprites_cols, sprites_rows: %i, %i; %i, %i",
          sprite_size_x, sprite_size_y, sprites_cols, sprites_rows);
          
    int cols = sprite_size_x;
    int rows = sprite_size_y;
    L.origin = ivec2_set(0);
#ifdef PIXELC_MOD_ISOTILEC
    cols = MOD_TILES_TILE_COLS 
            + (sprite_size_x + sprite_size_y) * MOD_TILES_TILE_COLS/2;
    rows = MOD_TILES_TILE_ROWS 
            + s_max(sprite_size_x, sprite_size_y) * MOD_TILES_TILE_ROWS/4 
            + sprites_rows*MOD_TILES_TILE_ROWS/2;
    
    L.origin.x = (sprite_size_x-sprite_size_y) * MOD_TILES_TILE_COLS/2;
    L.origin.y = -sprites_rows*MOD_TILES_TILE_ROWS/2;
#endif
    
    r_framebuffer_kill(&L.fb);
    L.fb = r_framebuffer_new(cols, rows*sprites_cols*sprites_rows);
    u_sprite_kill(&L.sprite);
    L.sprite = u_sprite_new_empty(cols, rows, sprites_cols, sprites_rows);
    r_texture_kill(&L.tex);
    L.tex = r_texture_new_sprite_buffer(cols, rows, sprites_cols, sprites_rows, NULL);
}

static void reset_renderobject(int ccols, int crows, int clayers) {
    s_log("ccols, crows, clayers: %i, %i, %i", ccols, crows, clayers);
    for(int i=0; i < mod_tiles.size; i++) {
        ro_batch_kill(&L.tiles[i]);
        L.tiles[i] = ro_batch_new(ccols * crows * clayers, mod_tiles.textures[i]);
        L.tiles[i].owns_tex = false;
        int t = 0;
        for(int r=0; r<crows*clayers; r++) {
            for(int c=0; c<ccols; c++) {
                float x, y;
#ifdef PIXELC_MOD_ISOTILEC
                x = L.origin.x + (c-r) * MOD_TILES_TILE_COLS/2;
                y = L.origin.y - (c+r) * MOD_TILES_TILE_ROWS/4 
                        + (r/crows) * MOD_TILES_TILE_ROWS/2;
#else
                x = c * MOD_TILES_TILE_COLS;
                y = -r * MOD_TILES_TILE_ROWS;
#endif
                
                L.tiles[i].rects[t++].pose = u_pose_new_aa(x, y,
                                                           MOD_TILES_TILE_COLS, MOD_TILES_TILE_ROWS);
            }
        }
    }
}

static void set_tile(int batch_id, int col, int row, int layer) {
    uImage img = canvas.RO.image;
    uColor_s color = *u_image_pixel(img, col, row, layer);
    int tile_id = color.r-1;
    int tile_x = color.g;
    int tile_y = color.b;
    for(int t=0; t < mod_tiles.size; t++) {
        if(t == tile_id) {
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
    for(int l=0; l<img.layers; l++) {
        for(int r=0; r<img.rows; r++) {
            for(int c=0; c<img.cols; c++) {
                set_tile(batch_id++, c, r, l);
            }
        }
    }
}


//
// public
//

void mod_canvas_on_canvas_update_fn() {
    uSprite c = canvas.RO.sprite;

    int cols = c.img.cols * MOD_TILES_TILE_COLS;
    int rows = c.img.rows * MOD_TILES_TILE_ROWS;

    // check sizes (also for startup)
    if(cols != L.sprite.img.cols || rows != L.sprite.img.rows
       || c.cols != L.sprite.cols || c.rows != L.sprite.rows) {
        reset_framebuffer(cols, rows, c.cols, c.rows);
        reset_renderobject(c.img.cols, c.img.rows, c.img.layers);
    }

    // set render objects according to the canvas image
    update_ros();

    // draw in the framebuffer
    mat4 cam = r_framebuffer_camera_ortho(L.fb);
    r_render_set_framebuffer(L.fb);
    r_render_clear(R_COLOR_TRANSPARENT);
    for(int i=0; i < mod_tiles.size; i++) {
        ro_batch_render(&L.tiles[i], &cam, true);
    }
    r_render_restore_framebuffer();

    // framebuffer to canvas texture
    r_framebuffer_get(L.fb, L.sprite.img.data);
    // reset sprites size, init with 1, layers
    r_texture_set_sprite_buffer(L.tex, L.sprite.img.data);
    canvas_reset_tex(L.tex);
}
