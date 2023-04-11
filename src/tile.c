#include "e/io.h"
#include "r/r.h"
#include "u/button.h"
#include "u/pose.h"
#include "u/json.h"
#include "m/int.h"
#include "m/float.h"
#include "m/utils/camera.h"
#include "io.h"
#include "canvas.h"
#include "brush.h"
#include "palette.h"
#include "cameractrl.h"
#include "selectionctrl.h"
#include "camera.h"
#include "tooltip.h"
#include "tile_palette_camera.h"
#include "tile_palette_cameractrl.h"
#include "tile.h"

#define PALETTE_SIZE 100

struct Tile_Globals tile;


static struct {
    int current_tile_cols;
    int current_tile_rows;
    int max_tile_cols;
    int max_tile_rows;

    rTexture tiles_tex;
    RoBatch tiles;

    struct {
        ivec2 fb_wanted_size;
        rFramebuffer fb;
        uSprite sprite;
        rTexture tex;
        ivec2 origin;
    } canvas;

    struct {
        RoSingle background_ro;
        RoSingle tiles_ro;
        mat4 tiles_pose_inv;

        rFramebuffer fb;
        uImage fb_img;

        RoSingle ro;
        RoSingle select_ro;

        RoSingle clear_tool;
        RoSingle prev_btn;
        RoSingle next_btn;
        RoSingle cam_btn;
        RoSingle tile_toggle;
        RoSingle iso_toggle;

        int last_selected;
        int current_pressed;

        mat4 custom_select_pose;
        bool custom_select_active;
    } palette;

    bool was_active;
    bool was_iso;
} L;


static const char *tilesheet_file(int id) {
    char file[256];
    snprintf(file, sizeof file, "tilesheet_%03i.png", id);
    return e_io_savestate_file_path(file);
}


static ivec2 get_framebuffer_size() {
    uSprite c = canvas.RO.sprite;
    int cols, rows;
    if (tile.iso) {
        cols = tile.RO.tile_size_x
               + (c.img.cols - 1 + c.img.rows - 1) * tile.RO.tile_size_x / 2;
        rows = tile.RO.tile_size_y
               + (c.img.cols - 1 + c.img.rows - 1) * tile.RO.tile_size_y / 4
               + (c.rows - 1) * tile.RO.tile_size_y / 2;

        L.canvas.origin.x = cols / 2 + (c.img.rows - c.img.cols - 2) * tile.RO.tile_size_x / 4;
        L.canvas.origin.y = -(c.rows - 1) * tile.RO.tile_size_y / 2;
    } else {
        cols = c.img.cols * tile.RO.tile_size_x;
        rows = c.img.rows * tile.RO.tile_size_y;
    }

    return (ivec2) {{cols, rows}};
}


static void reset_framebuffer(ivec2 fbo_size, ivec2 sprites) {
    s_log("fbo_size.x, fbo_size.y; sprites.x, sprites.y: %i, %i; %i, %i",
          fbo_size.x, fbo_size.y, sprites.x, sprites.y);
    L.canvas.fb_wanted_size = fbo_size;
    r_framebuffer_kill(&L.canvas.fb);
    if (!r_texture2d_size_in_limits(fbo_size.x, fbo_size.y * sprites.x * sprites.y)) {
        s_log_warn("tilemap to large for the frambuffer");
        tooltip_set("Warning", "Tilemap\n"
                               "to large\n"
                               "to render");
        if (fbo_size.x > fbo_size.y * sprites.x * sprites.y) {
            float scale = (float) fbo_size.y / fbo_size.x;
            fbo_size.x = r_render.limits.max_texture_size;
            fbo_size.y = fbo_size.x * scale;
        } else {
            float scale = (float) fbo_size.x / fbo_size.y;
            fbo_size.y = r_render.limits.max_texture_size / (sprites.x * sprites.y);
            fbo_size.x = fbo_size.y * scale;
        }
    }
    L.canvas.fb = r_framebuffer_new(fbo_size.x, fbo_size.y * sprites.x * sprites.y);
    u_sprite_kill(&L.canvas.sprite);
    L.canvas.sprite = u_sprite_new_empty(fbo_size.x, fbo_size.y, sprites.x, sprites.y);
    r_texture_kill(&L.canvas.tex);
    L.canvas.tex = r_texture_new_sprite_buffer(fbo_size.x, fbo_size.y, sprites.x, sprites.y, NULL);
}

static void set_tile_pose(int batch_id, int c, int r, int sc, int sr, int layer) {
    float x, y;
    x = c * tile.RO.tile_size_x;
    y = -r * tile.RO.tile_size_y;

    y -= L.canvas.fb_wanted_size.y * layer;
    L.tiles.rects[batch_id].pose = u_pose_new_aa(x, y, tile.RO.tile_size_x, tile.RO.tile_size_y);
}

static void set_tile_pose_iso(int batch_id, int c, int r, int sc, int sr, int layer) {
    float x, y;
    x = L.canvas.origin.x + (c - r) * tile.RO.tile_size_x / 2;
    y = L.canvas.origin.y - (c + r) * tile.RO.tile_size_y / 4
        + sr * tile.RO.tile_size_y / 2;

    y -= L.canvas.fb_wanted_size.y * layer;
    L.tiles.rects[batch_id].pose = u_pose_new_aa(x, y, tile.RO.tile_size_x, tile.RO.tile_size_y);
}

static void reset_renderobject(int ccols, int crows, int scols, int srows) {
    s_log("ccols, crows; scols, srows: %i, %i; %i, %i", ccols, crows, scols, srows);
    ro_batch_kill(&L.tiles);
    L.tiles = ro_batch_new(ccols * crows * scols * srows, L.tiles_tex);
    L.tiles.owns_tex = false;

    // uv
    for (int i = 0; i < L.tiles.num; i++) {
        L.tiles.rects[i].uv = u_pose_new(0, 0, 1.0 / L.max_tile_cols, 1.0 / L.max_tile_rows);
    }

    int t = 0;
    if (tile.iso) {
        for (int sr = 0; sr < srows; sr++) {
            for (int sc = 0; sc < scols; sc++) {
                for (int cr = 0; cr < crows; cr++) {
                    for (int cc = 0; cc < ccols; cc++) {
                        int layer = sr * scols + sc;
                        set_tile_pose_iso(t++, cc, cr, sc, sr, layer);
                    }
                }
            }
        }
    } else {
        for (int sr = 0; sr < srows; sr++) {
            for (int sc = 0; sc < scols; sc++) {
                for (int cr = 0; cr < crows; cr++) {
                    for (int cc = 0; cc < ccols; cc++) {
                        int layer = sr * scols + sc;
                        set_tile_pose(t++, cc, cr, sc, sr, layer);
                    }
                }
            }
        }
    }
}

static void set_tile(int batch_id, int col, int row, int layer) {
    uImage img = canvas.RO.image;
    uColor_s color = *u_image_pixel(img, col, row, layer);
    int tile_id = color.r;
    int tile_x = color.g;
    int tile_y = color.b;
    float u = (float) tile_x / L.max_tile_cols;
    float v = (float) tile_y / L.max_tile_rows;
    if (tile_id >= 0 && tile_id < TILE_MAX_TILESHEETS) {
        u_pose_set_xy(&L.tiles.rects[batch_id].uv, u, v);
        L.tiles.rects[batch_id].sprite.y = tile_id;
        L.tiles.rects[batch_id].color.a = color.a / 255.0;
    } else {
        L.tiles.rects[batch_id].color.a = 0;
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


static void update_tiles() {
    s_log("update");
    // sizes
    uImage imgs[TILE_MAX_TILESHEETS];
    int max_cols = 0;
    int max_rows = 0;
    for (int i = 0; i < TILE_MAX_TILESHEETS; i++) {
        imgs[i] = u_image_new_file(1, tilesheet_file(i));
        if (!u_image_valid(imgs[i]) || imgs[i].cols % tile.RO.tile_size_x != 0 ||
            imgs[i].rows % tile.RO.tile_size_y != 0) {
            s_log_error("img size invalid");
            continue;
        }
        int cols = imgs[i].cols / tile.RO.tile_size_x;
        int rows = imgs[i].rows / tile.RO.tile_size_y;
        max_cols = s_max(max_cols, cols);
        max_rows = s_max(max_rows, rows);
    }

    L.max_tile_cols = max_cols;
    L.max_tile_rows = max_rows;

    // create full image containing all sprite sheets
    int tile_img_cols = max_cols * tile.RO.tile_size_x;
    int tile_img_rows = max_rows * tile.RO.tile_size_y;

    uImage full = u_image_new_zeros(tile_img_cols, TILE_MAX_TILESHEETS * tile_img_rows, 1);

    for (int i = 0; i < TILE_MAX_TILESHEETS; i++) {
        for (int row = 0; row < imgs[i].rows; row++) {
            for (int col = 0; col < imgs[i].cols; col++) {
                *u_image_pixel(full, col, i * tile_img_rows + row, 0)
                        = *u_image_pixel(imgs[i], col, row, 0);
            }
        }

        u_image_kill(&imgs[i]);
    }

    r_texture_kill(&L.tiles_tex);

    // each image is a sprite.y (webgl max layers 256 on mobile...)
    L.tiles_tex = r_texture_new(full.cols, full.rows,
                                1, TILE_MAX_TILESHEETS,
                                full.data);
    u_image_kill(&full);

    // mark update
    u_sprite_kill(&L.canvas.sprite);
}

static void set_color(int id) {
    s_log("id: %i", id);
    int col = id % L.current_tile_cols;
    int row = id / L.current_tile_cols;
    uColor_s code = {{tile.RO.tilesheet_id, col, row, 255}};
    brush.current_color = code;
    brush.secondary_as_current = false;
    L.palette.last_selected = id;
    L.palette.custom_select_active = false;
}


//
// public
//

void tile_init() {
    L.canvas.sprite.img.layers = 1;

    tile.RO.tile_size_x = 16;
    tile.RO.tile_size_y = 16;
    tile.active = false;
    tile.canvas_active = true;
    tile.iso = false;

    tile_palette_camera_init();
    tile_palette_cameractrl_init();

    uColor_s buf[4];
    buf[0] = buf[3] = (uColor_s) {{153, 125, 118, 255}};
    buf[1] = buf[2] = (uColor_s) {{170, 140, 130, 255}};
    rTexture tex = r_texture_new(2, 2, 1, 1, buf);
    r_texture_wrap_repeat(tex);
    L.palette.background_ro = ro_single_new(tex);


    L.palette.tiles_ro = ro_single_new(r_texture_new_invalid());
    L.palette.ro = ro_single_new(r_texture_new_invalid());

    L.palette.select_ro = ro_single_new(r_texture_new_file(1, 1, "res/palette_select.png"));

    L.palette.clear_tool = ro_single_new(r_texture_new_file(1, 1, "res/toolbar_color_bg.png"));
    L.palette.prev_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_prev.png"));
    L.palette.next_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_next.png"));
    L.palette.cam_btn = ro_single_new(r_texture_new_file(2, 1, "res/button_camera.png"));
    L.palette.tile_toggle = ro_single_new(r_texture_new_file(2, 1, "res/button_tile.png"));
    L.palette.iso_toggle = ro_single_new(r_texture_new_file(2, 1, "res/button_iso.png"));

}

void tile_update(float dtime) {
    selectionctrl.allowed = !(tile.active && tile.iso);
    if (tile.active && !L.was_active) {
        set_color(0);
        tile.canvas_active = true;
    }
    if (!tile.active && L.was_active) {
        palette_set_color(s_min(1, palette.RO.palette_size-1));
    }
    L.was_active = tile.active;
}

uImage tile_get_tilemap_preview() {
    if (!(tile.active && tile.canvas_active)) {
        return u_image_new_invalid();
    }
    uSprite sprite = u_sprite_new_clone_merge_row_down_full(L.canvas.sprite);
    uImage img = u_sprite_reorder_to_new_image(sprite);
    u_sprite_kill(&sprite);
    return img;
}

bool tile_get_tile_from_colorcode(rTexture *out_tex_ref, rRect_s *inout_rect, uColor_s colorcode) {
    int tile_id = colorcode.r;
    int tile_x = colorcode.g;
    int tile_y = colorcode.b;
    float u = (float) tile_x / L.max_tile_cols;
    float v = (float) tile_y / L.max_tile_rows;
    *out_tex_ref = L.tiles_tex;

    if (tile_id >= 0 && tile_id < TILE_MAX_TILESHEETS) {
        inout_rect->uv = u_pose_new(u, v, 1.0 / L.max_tile_cols, 1.0 / L.max_tile_rows);
        inout_rect->sprite = vec2_(0, tile_id);
        inout_rect->color = vec4_(1, 1, 1, colorcode.a / 255.0);
        return colorcode.a > 0;
    }

    inout_rect->color.a = 0;
    return false;
}

vec2 tile_tilesheet_size() {
    return (vec2) {{L.current_tile_cols * tile.RO.tile_size_x,
                    L.current_tile_rows * tile.RO.tile_size_y}};
}

ivec2 tile_canvas_get_size() {
    // layers may be ==0 on the first frame
    if (!tile.iso || L.canvas.sprite.img.layers <= 0) {
        return (ivec2) {{canvas.RO.image.cols * tile.RO.tile_size_x, canvas.RO.image.rows * tile.RO.tile_size_y}};
    }
    return (ivec2) {{L.canvas.fb_wanted_size.x, L.canvas.fb_wanted_size.y}};
}

ivec2 tile_canvas_get_cr(vec2 pointer_pos) {
    if (!tile.iso) {
        return (ivec2) {{(int) pointer_pos.x / tile.RO.tile_size_x, (int) -pointer_pos.y / tile.RO.tile_size_y}};
    }

    int layer = canvas.RO.current_layer;

    //// set_tile...
    // x = L.canvas.origin.x + (c-r) * tile.RO.tile_size_x/2;
    // y = L.canvas.origin.y - (c+r) * tile.RO.tile_size_y/4
    //    + l * tile.RO.tile_size_y/2;

    pointer_pos.x -= tile.RO.tile_size_x / 2;

    pointer_pos.x -= L.canvas.origin.x;
    pointer_pos.x /= tile.RO.tile_size_x / 2;
    pointer_pos.y -= L.canvas.origin.y;
    pointer_pos.y -= layer * tile.RO.tile_size_y / 2;
    pointer_pos.y /= tile.RO.tile_size_y / 4;

    pointer_pos.y = -pointer_pos.y;

    // x = c-r      -> c = x+r
    // y = c+r      -> c = y-r
    // x+r = y-r    -> r = (y-x)/2
    float r = (pointer_pos.y - pointer_pos.x) / 2;
    float c = pointer_pos.x + r;
    return (ivec2) {{(int) c, (int) r}};
}

void tile_on_canvas_update() {
    uSprite c = canvas.RO.sprite;

    ivec2 fbo_size = get_framebuffer_size();
    ivec2 sprites = (ivec2) {{c.cols, c.rows}};

    // check sizes (also for startup)
    if (tile.iso != L.was_iso
        || fbo_size.x != L.canvas.fb_wanted_size.x || fbo_size.y != L.canvas.fb_wanted_size.y
        || sprites.x != L.canvas.sprite.cols || sprites.y != L.canvas.sprite.rows) {
        reset_framebuffer(fbo_size, sprites);
        reset_renderobject(c.img.cols, c.img.rows, sprites.x, sprites.y);
    }
    L.was_iso = tile.iso;

    // set render objects according to the canvas image
    update_ros();

    // draw in the framebuffer
//    mat4 cam = r_framebuffer_camera_ortho(L.canvas.fb);
    mat4 cam = mat4_camera_ortho(0,
                                 L.canvas.fb_wanted_size.x,
                                 0,
                                 -L.canvas.fb_wanted_size.y * L.canvas.sprite.cols * L.canvas.sprite.rows,
                                 -1, 1);
    r_render_set_framebuffer(L.canvas.fb);
    r_render_clear(R_COLOR_TRANSPARENT);
    ro_batch_render(&L.tiles, &cam, true);
    r_render_restore_framebuffer();

    // framebuffer to canvas texture
    r_framebuffer_get(L.canvas.fb, L.canvas.sprite.img.data);
    // reset sprites size, init with 1, layers
    r_texture_set_sprite_buffer(L.canvas.tex, L.canvas.sprite.img.data);
    canvas_reset_tex(L.canvas.tex);
}


void tile_palette_update(float dtime) {
    tile_palette_camera_update(L.palette.fb.tex.size);
    tile_palette_cameractrl_update(dtime);

    if (camera_is_portrait_mode()) {
        float w = camera_width();
        float h = PALETTE_SIZE;
        L.palette.background_ro.rect.pose = u_pose_new_aa(camera.RO.left, camera.RO.bottom + PALETTE_SIZE, w, h);
        u_pose_set_size(&L.palette.background_ro.rect.uv, w / 2, h / 2);
    } else {
        float w = PALETTE_SIZE;
        float h = camera_height();
        L.palette.background_ro.rect.pose = u_pose_new_aa(camera.RO.right - PALETTE_SIZE, camera.RO.top, w, h);
        u_pose_set_size(&L.palette.background_ro.rect.uv, w / 2, h / 2);
    }
    L.palette.ro.rect.pose = L.palette.background_ro.rect.pose;

    if (L.palette.custom_select_active) {
        L.palette.select_ro.rect.pose = L.palette.custom_select_pose;
    } else {
        int x = L.palette.last_selected % L.current_tile_cols;
        int y = L.palette.last_selected / L.current_tile_cols;
        L.palette.select_ro.rect.pose = u_pose_new_aa(
                x * tile.RO.tile_size_x,
                -y * tile.RO.tile_size_y,
                tile.RO.tile_size_x, tile.RO.tile_size_y);
    }

    // tools
    if (camera_is_portrait_mode()) {
        L.palette.clear_tool.rect.pose = u_pose_new(camera.RO.left + 10, camera.RO.bottom + PALETTE_SIZE - 10, 16, 16);

        L.palette.prev_btn.rect.pose = u_pose_new(camera.RO.right - 30, camera.RO.bottom + PALETTE_SIZE - 10, 16, 16);
        L.palette.next_btn.rect.pose = u_pose_new(camera.RO.right - 10, camera.RO.bottom + PALETTE_SIZE - 10, 16, 16);
        L.palette.cam_btn.rect.pose = u_pose_new(camera.RO.right - 10, camera.RO.bottom + PALETTE_SIZE - 40, 16, 16);
        L.palette.tile_toggle.rect.pose = u_pose_new(camera.RO.right - 10, camera.RO.bottom + PALETTE_SIZE - 60, 16,
                                                     16);
        L.palette.iso_toggle.rect.pose = u_pose_new(camera.RO.right - 10, camera.RO.bottom + PALETTE_SIZE - 80, 16, 16);
    } else {
        L.palette.clear_tool.rect.pose = u_pose_new(camera.RO.right - PALETTE_SIZE + 10, camera.RO.bottom + 10, 16, 16);

        L.palette.prev_btn.rect.pose = u_pose_new(camera.RO.right - PALETTE_SIZE + 10, camera.RO.top - 30, 16, 16);
        L.palette.next_btn.rect.pose = u_pose_new(camera.RO.right - PALETTE_SIZE + 10, camera.RO.top - 10, 16, 16);
        L.palette.cam_btn.rect.pose = u_pose_new(camera.RO.right - PALETTE_SIZE + 40, camera.RO.top - 10, 16, 16);
        L.palette.tile_toggle.rect.pose = u_pose_new(camera.RO.right - PALETTE_SIZE + 60, camera.RO.top - 10, 16, 16);
        L.palette.iso_toggle.rect.pose = u_pose_new(camera.RO.right - PALETTE_SIZE + 80, camera.RO.top - 10, 16, 16);
    }
    L.palette.tile_toggle.rect.sprite.x = tile.canvas_active ? 1 : 0;
    L.palette.iso_toggle.rect.sprite.x = tile.iso ? 1 : 0;
}


void tile_palette_render(const mat4 *cam_mat) {
    // framebuffer size and ro pose
    int render_cols, render_rows;
    if (camera_is_portrait_mode()) {
        render_cols = camera.RO.scale * camera_width();
        render_rows = camera.RO.scale * PALETTE_SIZE;
    } else {
        render_rows = camera.RO.scale * camera_height();
        render_cols = camera.RO.scale * PALETTE_SIZE;
    }

    // resize framebuffer?
    if (render_cols != L.palette.fb.tex.size.x || render_rows != L.palette.fb.tex.size.y) {
        s_log("resize framebuffer: %i, %i", render_cols, render_rows);
        r_framebuffer_kill(&L.palette.fb);
        u_image_kill(&L.palette.fb_img);
        L.palette.fb = r_framebuffer_new(render_cols, render_rows);
        L.palette.fb_img = u_image_new_empty(render_cols, render_rows, 1);
        rTexture tex = r_texture_new(render_cols, render_rows, 1, 1, NULL);
        ro_single_set_texture(&L.palette.ro, tex);
    }

    // render into L.ro.tex
    r_render_set_framebuffer(L.palette.fb);
    r_render_clear(R_COLOR_TRANSPARENT);
    ro_single_render(&L.palette.tiles_ro, &tile_palette_camera.matrices.vp);
    if (!L.palette.custom_select_active)
        ro_single_render(&L.palette.select_ro, &tile_palette_camera.matrices.vp);
    r_render_restore_framebuffer();

    r_framebuffer_get(L.palette.fb, L.palette.fb_img.data);
    r_texture_set(L.palette.ro.tex, L.palette.fb_img.data);

    ro_single_render(&L.palette.background_ro, cam_mat);
    ro_single_render(&L.palette.ro, cam_mat);

    ro_single_render(&L.palette.clear_tool, cam_mat);
    ro_single_render(&L.palette.prev_btn, cam_mat);
    ro_single_render(&L.palette.next_btn, cam_mat);
    ro_single_render(&L.palette.cam_btn, cam_mat);
    ro_single_render(&L.palette.tile_toggle, cam_mat);
    ro_single_render(&L.palette.iso_toggle, cam_mat);

    if (L.palette.custom_select_active)
        ro_single_render(&L.palette.select_ro, cam_mat);
}

void tile_palette_pointer_event_always(ePointer_s pointer) {
    if (pointer.action != E_POINTER_UP
        && !palette_contains_pos(pointer.pos.xy)) {
        return;
    }

    // in tiles view
    ePointer_s t_pointer = pointer;
    t_pointer.pos = tile_palette_pointer_pos(pointer.pos);

    tile_palette_cameractrl_pointer_event(t_pointer);
}

void tile_palette_pointer_event(ePointer_s pointer) {
    if (pointer.id != 0) {
        return;
    }

    // in tiles view
    ePointer_s t_pointer = pointer;
    t_pointer.pos = tile_palette_pointer_pos(pointer.pos);


    if (pointer.action == E_POINTER_DOWN
        && u_pose_aa_contains(L.palette.clear_tool.rect.pose, pointer.pos.xy)) {
        s_log("clear_tool");
        tooltip_set("clear", "Tip to use\n"
                             "clear color");
        brush.current_color = U_COLOR_TRANSPARENT;
        brush.secondary_as_current = false;
        palette_set_custom_select(L.palette.clear_tool.rect.pose);
        return;
    }

    if (u_button_clicked(&L.palette.prev_btn.rect, pointer)) {
        s_log("prev_btn");
        // extra spaces and newline to get above the palette info
        tooltip_set("previous", "Load the\n"
                                "previous\n"
                                "tilesheet  \n");
        tile_palette_next_palette(false);
        return;
    }

    if (u_button_clicked(&L.palette.next_btn.rect, pointer)) {
        s_log("next_btn");
        // extra spaces and newline to get above the palette info
        tooltip_set("next", "Load the\n"
                            "next\n"
                            "tilesheet  \n");
        tile_palette_next_palette(true);
        return;
    }

    if (u_button_clicked(&L.palette.cam_btn.rect, pointer)) {
        s_log("cam_btn");
        tooltip_set("tile camera", "Reset the\n"
                                   "tilesheet camera");
        tile_palette_cameractrl_set_home();
        return;
    }

    if (u_button_toggled(&L.palette.tile_toggle.rect, pointer)) {
        s_log("tile_toggle");
        tooltip_set("tile", "Render in\n"
                            "tile mode or\n"
                            "color code mode");
        tile.canvas_active = u_button_is_pressed(&L.palette.tile_toggle.rect);
        tile_save_config();
        cameractrl_set_home();
        return;
    }

    if (u_button_toggled(&L.palette.iso_toggle.rect, pointer)) {
        s_log("iso_toggle");
        tooltip_set("tile", "Render in\n"
                            "isometric mode");
        tile.iso = u_button_is_pressed(&L.palette.iso_toggle.rect);
        if (tile.iso) {
            tile.canvas_active = true;
        }
        tile_save_config();
        cameractrl_set_home();
        return;
    }


    // tooltip
    if (pointer.action == E_POINTER_DOWN) {
        tooltip_set("tile palette", "Tip to select\n"
                                    "a tile\n\n"
                                    "Swipe up for\n"
                                    "Multitouch Mode\n\n"
                                    "Hold for options");
    }

    // in tiles ro as [-0.5 : 0.5]
    vec4 in_tiles = mat4_mul_vec(L.palette.tiles_pose_inv, t_pointer.pos);

    int tile_pos_x = (int) sca_floor((in_tiles.x + 0.5) * L.current_tile_cols);
    int tile_pos_y = (int) sca_floor((0.5 - in_tiles.y) * L.current_tile_rows);

    int tile_id = -1;
    if (tile_pos_x >= 0
        && tile_pos_x < L.current_tile_cols
        && tile_pos_y >= 0
        && tile_pos_y < L.current_tile_rows)
        tile_id = tile_pos_y * L.current_tile_cols + tile_pos_x;

    if (pointer.action == E_POINTER_DOWN) {
        if (tile_id >= 0) {
            L.palette.current_pressed = tile_id;
            return;
        }
        L.palette.current_pressed = -1;
        return;
    }

    if (L.palette.current_pressed != -1
        && L.palette.current_pressed != tile_id) {
        L.palette.current_pressed = -1;
    }

    if (L.palette.current_pressed != -1 && pointer.action == E_POINTER_UP) {
        set_color(L.palette.current_pressed);
        L.palette.current_pressed = -1;
    }
}

vec4 tile_palette_pointer_pos(vec4 hud_pointer_pos) {
    // transform into the render object coordinates
    mat4 pose_inv = mat4_inv(L.palette.ro.rect.pose);
    vec4 ro_pos = mat4_mul_vec(pose_inv, hud_pointer_pos);

    // from [-0.5 : 0.5] to [-1.0 : 1.0]
    // and y top is -, bottom +, for the fbo
    ro_pos.x *= 2;
    ro_pos.y *= -2;

    ro_pos = mat4_mul_vec(tile_palette_camera.matrices.p_inv, ro_pos);

    // in tiles view
    return mat4_mul_vec(tile_palette_camera.matrices.v, ro_pos);
}

float tile_palette_get_hud_size() {
    return PALETTE_SIZE;
}

void tile_palette_set_custom_select(mat4 select_pose) {
    L.palette.custom_select_pose = select_pose;
    L.palette.custom_select_active = true;
    L.palette.last_selected = -1;
}

void tile_palette_next_palette(bool next) {
    int id;
    if (!next) {
        id = tile.RO.tilesheet_id - 1;
        if (id < 0)
            id = TILE_MAX_TILESHEETS - 1;
    } else {
        id = tile.RO.tilesheet_id + 1;
        id %= TILE_MAX_TILESHEETS;
    }
    tile_load_tilesheet(id);
}


void tile_set_size(int tile_size_x, int tile_size_y) {
    if (tile_size_x % 8 != 0 || tile_size_y % 8 != 0) {
        s_log_error("invalid sizes");
        return;
    }
    s_log("size: %i, %i", tile_size_x, tile_size_y);
    tile.RO.tile_size_x = tile_size_x;
    tile.RO.tile_size_y = tile_size_y;
    update_tiles();
    tile_load_tilesheet(tile.RO.tilesheet_id);
    tile_save_config();
}

void tile_load_tilesheet(int id) {
    if (id < 0 || id >= TILE_MAX_TILESHEETS) {
        s_log_error("invalid id: %i/%i", id, TILE_MAX_TILESHEETS);
        id = 0;
    }

    s_log("load: %i", id);
    tile.RO.tilesheet_id = id;

    uImage tile_img = u_image_new_file(1, tilesheet_file(id));
    if (!u_image_valid(tile_img)) {
        s_log_error("invalid image?");
        return;
    }
    ro_single_set_texture(&L.palette.tiles_ro, r_texture_new(tile_img.cols, tile_img.rows, 1, 1, tile_img.data));

    L.current_tile_cols = tile_img.cols / tile.RO.tile_size_x;
    L.current_tile_rows = tile_img.rows / tile.RO.tile_size_y;

    u_image_kill(&tile_img);

    vec2 tile_size = tile_tilesheet_size();
    L.palette.tiles_ro.rect.pose = u_pose_new_aa(0, 0, tile_size.x, tile_size.y);
    L.palette.tiles_pose_inv = mat4_inv(L.palette.tiles_ro.rect.pose);

    char info[128];
    snprintf(info, sizeof info, "Tileset: %i", id);
    palette_set_info(info);

    set_color(0);

    tile_palette_cameractrl_set_home();

    tile_save_config();
}

void tile_update_tilesheet(uImage tilesheet, int id) {
    if (id < 0 || id >= TILE_MAX_TILESHEETS) {
        s_log_error("not in range");
        return;
    }
    if (!u_image_valid(tilesheet)) {
        s_log_error("not valid");
        return;
    }
    s_log("update: %i", id);

    tilesheet.layers = 1;

    if (tilesheet.cols >= 32 && tilesheet.cols % 32 == 0 && tilesheet.rows >= 32 && tilesheet.rows % 32 == 0) {
        u_image_save_file(tilesheet, tilesheet_file(id));
    } else {
        int cols = tilesheet.cols;
        if (cols < 32)
            cols = 32;
        if (cols % 32 != 0)
            cols = (1 + (cols / 32)) * 32;
        int rows = tilesheet.rows;
        if (rows < 32)
            rows = 32;
        if (rows % 32 != 0)
            rows = (1 + (rows / 32)) * 32;
        uImage img = u_image_new_zeros(cols, rows, 1);
        u_image_copy_top_left(img, tilesheet);
        u_image_save_file(img, tilesheet_file(id));
        u_image_kill(&img);
    }


    // save the savestate files (needed for web)
    e_io_savestate_save();

    update_tiles();
    tile_load_tilesheet(id);
}

uImage tile_get_tilesheet(int id) {
    if (id < 0 || id >= TILE_MAX_TILESHEETS) {
        s_log_error("not in range");
        return u_image_new_invalid();
    }
    return u_image_new_file(1, tilesheet_file(id));
}

void tile_reset_tilesheet_files() {
    s_log("reset tilesheets files");
    uImage example[4];
    example[0] = u_image_new_file(1, "res/tilesheets/a.png");
    example[1] = u_image_new_file(1, "res/tilesheets/b.png");
    example[2] = u_image_new_file(1, "res/tilesheets/c.png");
    example[3] = u_image_new_file(1, "res/tilesheets/d.png");

    for (int i = 0; i < TILE_MAX_TILESHEETS; i++) {
        u_image_save_file(example[i % 4], tilesheet_file(i));
    }

    for (int i = 0; i < 4; i++) {
        u_image_kill(&example[i]);
    }

    tile.RO.tilesheet_id = 0;

    tile.RO.tile_size_x = 16;
    tile.RO.tile_size_y = 16;

    // save the savestate files (needed for web)
    e_io_savestate_save();

    update_tiles();
    tile_load_tilesheet(0);
}


void tile_save_config() {
    s_log("save");

    uJson *config = u_json_new_file(io_config_file());

    uJson *member = u_json_append_object(config, "tile");
    u_json_append_bool(member, "active", tile.active);
    u_json_append_bool(member, "canvas_active", tile.canvas_active);
    u_json_append_bool(member, "iso", tile.iso);
    u_json_append_int(member, "id", tile.RO.tilesheet_id);
    u_json_append_int(member, "tile_size_x", tile.RO.tile_size_x);
    u_json_append_int(member, "tile_size_y", tile.RO.tile_size_y);

    u_json_save_file(config, io_config_file(), NULL);
    e_io_savestate_save();

    u_json_kill(&config);
}

void tile_load_config() {
    s_log("load");

    bool reset = false;

    uJson *config = u_json_new_file(io_config_file());
    uJson *member = u_json_get_object(config, "tile");

    const bool *active = u_json_get_object_bool(member, "active");
    const bool *canvas_active = u_json_get_object_bool(member, "canvas_active");
    const bool *iso = u_json_get_object_bool(member, "iso");
    if (active && canvas_active && iso) {
        tile.active = *active;
        tile.canvas_active = *canvas_active;
        tile.iso = *iso;
    }

    int id;
    if (!u_json_get_object_int(member, "id", &id)) {
        reset = true;
        goto CLEAN_UP;
    }

    int tile_size_x, tile_size_y;
    if (!u_json_get_object_int(member, "tile_size_x", &tile_size_x)
        || !u_json_get_object_int(member, "tile_size_y", &tile_size_y)) {
        reset = true;
        goto CLEAN_UP;
    }

    if ((tile_size_x != 8 && tile_size_x != 16 && tile_size_y != 32)
        || (tile_size_y != 8 && tile_size_y != 16 && tile_size_y != 32)) {
        s_log_warn("invalid tile size");
        reset = true;
        goto CLEAN_UP;
    }

    CLEAN_UP:
    u_json_kill(&config);

    if (reset) {
        tile_reset_tilesheet_files();
    } else {
        tile_set_size(tile_size_x, tile_size_y);
        tile_load_tilesheet(id);
    }
}
