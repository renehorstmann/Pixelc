#include "r/r.h"
#include "e/io.h"
#include "u/pose.h"
#include "u/json.h"
#include "s/s_full.h"
#include "m/float.h"
#include "m/int.h"
#include "io.h"
#include "brush.h"
#include "camera.h"
#include "dialog.h"
#include "feedback.h"
#include "tooltip.h"
#include "mod_tiles.h"

#include "mod_palette_camera.h"
#include "mod_palette_cameractrl.h"

#include "palette.h"


#define PALETTE_SIZE 80

#define COLOR_DROP_SIZE 16.0f
#define ADDITIONAL_PALETTE_SPACE 512

#define SWIPE_DISTANCE 50

#define LONGPRESS_TIME 0.75
#define LONGPRESS_RADIUS 8.0

#define INFO_STATIC_TIME 0.5
#define INFO_TIME 1.5

struct Palette_Globals palette;

//
// private
//

static struct {
    RoSingle select_ro;
    RoSingle background_ro;
    RoSingle tiles_ro;

    rFramebuffer fb;
    uImage fb_img;

    RoSingle ro;

    int current_tile_cols;
    int current_tile_rows;

    struct {
        RoSingle bg;
        RoText text;
        int x_offset;
        float time;
    } info;

    // long swipe from side to side to load the next palette
    struct {
        RoBatch arrows;
        vec2 start;
        bool swiping;
        float longpress_time;
    } action;

    int last_selected;
    int current_pressed;


    mat4 custom_select_pose;
    bool custom_select_active;
} L;


// returns the swipe move difference in %
static float swipe_diff(ePointer_s pointer) {
    float diff;
    if (camera_is_portrait_mode()) {
        diff = pointer.pos.x - L.action.start.x;
    } else {
        diff = pointer.pos.y - L.action.start.y;
    }
    return diff / SWIPE_DISTANCE;
}


//
// public
//

void palette_init() {
    mod_palette_camera_init();
    mod_palette_cameractrl_init();

    palette.include_transparent_at_set_colors = true;

    L.current_pressed = -1;

    uColor_s buf[4];
    buf[0] = buf[3] = (uColor_s) {{150, 100, 60, 255}};
    buf[1] = buf[2] = (uColor_s) {{160, 100, 60, 255}};
    rTexture tex = r_texture_new(2, 2, 1, 1, buf);
    r_texture_wrap_repeat(tex);
    L.background_ro = ro_single_new(tex);

    L.select_ro = ro_single_new(r_texture_new_file(1, 1, "res/palette_select.png"));
    L.select_ro.rect.color.r = 0;

    L.tiles_ro = ro_single_new(r_texture_new_invalid());
    L.tiles_ro.owns_tex = false;
    L.ro = ro_single_new(r_texture_new_invalid());

    L.info.bg = ro_single_new(r_texture_new_file(1, 1, "res/palette_info_bg.png"));
    L.info.text = ro_text_new_font55(20);

    L.action.arrows = ro_batch_new(2, r_texture_new_file(1, 1, "res/palette_arrow.png"));

    L.action.longpress_time = -1;
}


void palette_update(float dtime) {
    mod_palette_camera_update(L.fb.tex.size);
    mod_palette_cameractrl_update(dtime);


    if(camera_is_portrait_mode()) {
        float w = camera_width();
        float h = PALETTE_SIZE;
        L.background_ro.rect.pose = u_pose_new_aa(camera.RO.left, camera.RO.bottom+PALETTE_SIZE, w, h);
        u_pose_set_size(&L.background_ro.rect.uv, w / 2, h / 2);
    } else {
        float w = PALETTE_SIZE;
        float h = camera_height();
        L.background_ro.rect.pose = u_pose_new_aa(camera.RO.right-PALETTE_SIZE, camera.RO.top, w, h);
        u_pose_set_size(&L.background_ro.rect.uv, w / 2, h / 2);
    }
    L.ro.rect.pose = L.background_ro.rect.pose;

//    if (L.custom_select_active)
//        L.select_ro.rect.pose = L.custom_select_pose;
//    else
//        L.select_ro.rect.pose = L.palette_ro.rects[L.last_selected].pose;

    // info
    if (L.info.time > 0) {
        L.info.time -= dtime;

        float pos = 4;
        if (L.info.time < INFO_STATIC_TIME) {
            pos = sca_mix(-4, 4, L.info.time / INFO_STATIC_TIME);
        }

        pos += palette_get_hud_size();

        if (camera_is_portrait_mode()) {
            pos += camera.RO.bottom;

            L.info.bg.rect.pose = u_pose_new(
                    0, pos, 128, 8);

            pos += 2;
            L.info.text.pose = u_pose_new(
                    L.info.x_offset, pos,
                    1, 1);

        } else {
            pos = camera.RO.right - pos;

            L.info.bg.rect.pose = u_pose_new_angle(
                    pos, 0, 128, 8, SCA_PI_2);

            pos -= 2;
            L.info.text.pose = u_pose_new_angle(
                    pos, L.info.x_offset,
                    1, 1, SCA_PI_2);
        }
    }

    // action
    if(L.action.longpress_time>=0) {
        L.action.longpress_time -= dtime;
        if(L.action.longpress_time<0) {
            // stop actions
            L.action.swiping = false;
            feedback_longpress(L.action.start, (vec4) {{0.6, 0.6, 0.1, 1.0}});
            dialog_create_palette();
        }
    }

}

void palette_render(const mat4 *cam_mat) {

    // framebuffer size and ro pose
    int render_cols, render_rows;
    if(camera_is_portrait_mode()) {
        render_cols = camera.RO.scale * camera_width();
        render_rows = camera.RO.scale * PALETTE_SIZE;
    } else {
        render_rows = camera.RO.scale * camera_height();
        render_cols = camera.RO.scale * PALETTE_SIZE;
    }

    // resize framebuffer?
    if(render_cols != L.fb.tex.size.x || render_rows != L.fb.tex.size.y) {
        s_log("resize framebuffer: %i, %i", render_cols, render_rows);
        r_framebuffer_kill(&L.fb);
        u_image_kill(&L.fb_img);
        L.fb = r_framebuffer_new(render_cols, render_rows);
        L.fb_img = u_image_new_empty(render_cols, render_rows, 1);
        rTexture tex = r_texture_new(render_cols, render_rows, 1, 1, NULL);
        ro_single_set_texture(&L.ro, tex);
    }

    // render into L.ro.tex
    r_render_set_framebuffer(L.fb);
    r_render_clear(R_COLOR_TRANSPARENT);
    ro_single_render(&L.tiles_ro, &mod_palette_camera.matrices.vp);
    r_render_restore_framebuffer();

    r_framebuffer_get(L.fb, L.fb_img.data);
    r_texture_set(L.ro.tex, L.fb_img.data);


    if (L.info.time > 0) {
        ro_single_render(&L.info.bg, cam_mat);
        ro_text_render(&L.info.text, cam_mat);
    }

    ro_single_render(&L.background_ro, cam_mat);
    ro_single_render(&L.ro, cam_mat);
    ro_single_render(&L.select_ro, cam_mat);

    if (L.action.swiping)
        ro_batch_render(&L.action.arrows, cam_mat, true);
}


bool palette_pointer_event(ePointer_s pointer) {
    if (!palette_contains_pos(pointer.pos.xy)) {
        for (int i = 0; i < 2; i++)
            L.action.arrows.rects[i].color.a = 0;
        L.action.swiping = false;
        L.action.longpress_time = -1;
        return false;
    }

    // back to all and into the
    ePointer_s t_pointer = pointer;
    if(camera_is_portrait_mode()) {
        t_pointer.pos.y -= (camera.RO.bottom + PALETTE_SIZE/2);
    } else {
        t_pointer.pos.x -= (camera.RO.right - PALETTE_SIZE/2);
    }
    t_pointer.pos = mat4_mul_vec(camera.matrices.p, t_pointer.pos);
    t_pointer.pos = mat4_mul_vec(mod_palette_camera.matrices.v_p_inv, t_pointer.pos);
    vec2_println(t_pointer.pos.xy);

    mod_palette_cameractrl_pointer_event(t_pointer);

    if(pointer.id != 0) {
        return false;
    }

    if (pointer.action == E_POINTER_DOWN) {
        tooltip_set("palette", "Tip to select\n"
                "a color\n\n"
                "Swipe left or\n"
                "right to change\n"
                "the palette\n\n"
                "Swipe up for\n"
                "Multitouch Mode\n\n"
                "Hold for options");

        for (int i = 0; i < 2; i++)
            L.action.arrows.rects[i].color.a = 0;
        L.action.start = pointer.pos.xy;
        L.action.swiping = true;
        L.action.longpress_time = LONGPRESS_TIME;
//        for (int i = 0; i < palette.RO.palette_size; i++) {
//            // pose will be rotated in landscape mode (so do not use _aa_)!
//            if (u_pose_contains(L.palette_ro.rects[i].pose, pointer.pos)) {
//                L.current_pressed = i;
//                return true;
//            }
//        }

        L.current_pressed = -1;
        return true;
    }

    if (pointer.action == E_POINTER_UP) {
        for (int i = 0; i < 2; i++)
            L.action.arrows.rects[i].color.a = 0;
        L.action.swiping = false;
        L.action.longpress_time = -1;
    }

//    if (L.current_pressed != -1
//        // pose will be rotated in landscape mode (so do not use _aa_)!
//        && !u_pose_contains(L.palette_ro.rects[L.current_pressed].pose,
//                            pointer.pos)) {
//        L.current_pressed = -1;
//    }

    if (L.current_pressed != -1 && pointer.action == E_POINTER_UP) {
        palette_set_color(L.current_pressed);
        L.current_pressed = -1;
    }

    if (L.action.swiping && pointer.action == E_POINTER_MOVE) {
        float diff = swipe_diff(pointer);
        if (diff > 1) {
            int id = palette.RO.palette_id - 1;
            if (id < 0)
                id = palette.RO.max_palettes - 1;
            palette_load_palette(id);
            L.action.swiping = false;

        } else if (diff <= -1) {
            int id = palette.RO.palette_id + 1;
            id %= palette.RO.max_palettes;
            palette_load_palette(id);
            L.action.swiping = false;

        }

        float alpha = sca_smoothstep(sca_abs(diff), 0.25, 1);
        for (int i = 0; i < 2; i++)
            L.action.arrows.rects[i].color.a = alpha;
        if (camera_is_portrait_mode()) {
            for (int i = 0; i < 2; i++) {
                L.action.arrows.rects[i].pose = u_pose_new_angle(
                        (int[]) {-1, 1}[i] * (camera_width() / 2 - 20),
                        camera.RO.bottom + 16,
                        32, 32,
                        sca_sign(diff) * SCA_PI_2 - SCA_PI_2
                );
            }
        } else {
            for (int i = 0; i < 2; i++) {
                L.action.arrows.rects[i].pose = u_pose_new_angle(
                        camera.RO.right - 16,
                        (int[]) {-1, 1}[i] * (camera_height() / 2 - 20),
                        32, 32,
                        sca_sign(diff) * SCA_PI_2
                );
            }
        }
    }

    if(L.action.longpress_time>=0 && pointer.action == E_POINTER_MOVE) {
        if(vec2_distance(L.action.start, pointer.pos.xy) > LONGPRESS_RADIUS) {
            L.action.longpress_time = -1;
        }
    }

    return true;
}

float palette_get_hud_size() {
    return PALETTE_SIZE;
}

uImage palette_as_image() {
    uImage ret = u_image_new_empty(palette.RO.palette_size, 1, 1);
    memcpy(ret.data, palette.RO.palette, u_image_data_size(ret));
    return ret;
}

bool palette_contains_pos(vec2 pos) {
    int size = palette_get_hud_size();
    if (camera_is_portrait_mode()) {
        return pos.y <= camera.RO.bottom + size;
    }
    return pos.x >= camera.RO.right - size;
}

void palette_set_color(int index) {
    if (index < 0 || index >= palette.RO.palette_size) {
        s_log_error("invalid index (%i/%i)",
                  index, palette.RO.palette_size);
        return;
    }
    brush.current_color = palette.RO.palette[index];
    brush.secondary_as_current = false;
//    L.select_ro.rect.pose = L.palette_ro.rects[index].pose;
    L.last_selected = index;
    L.custom_select_active = false;
}

void palette_set_custom_select(mat4 select_pose) {
    L.custom_select_pose = select_pose;
    L.custom_select_active = true;
    L.last_selected = -1;
}

void palette_set_info(const char *info) {
    if (!info) {
        // hide it immediately
        L.info.time = -1;
        return;
    }
    vec2 size = ro_text_set_text(&L.info.text, info);
    L.info.x_offset = (int) -sca_ceil(size.x / 2);
    L.info.time = INFO_TIME;
}

void palette_set_colors(const uColor_s *colors, int size, const char *name) {
    s_log("noop");
}


void palette_set_palette(uImage colors, const char *name) {
    s_log("noop");
}

// protected for mod_palette_cameractrl scrool event
vec2 mod_palette_tiles_size() {
    float w, h;
    if(L.current_tile_cols < L.current_tile_rows) {
        w = 100.0*L.current_tile_cols/L.current_tile_rows;
        h = 100;
    } else {
        w = 100;
        h = 100.0*L.current_tile_rows/L.current_tile_cols;
    }
    return (vec2) {{w, h}};
}

void palette_load_palette(int id) {
    palette.RO.max_palettes = mod_tiles.size;
    if (id < 0 || id >= palette.RO.max_palettes) {
        s_log_error("invalid id: %i/%i", id, palette.RO.max_palettes);
        return;
    }

    uImage tile_img = mod_tiles.imgs[id];
    ro_single_set_texture(&L.tiles_ro, r_texture_new(tile_img.cols, tile_img.rows, 1, 1, tile_img.data));

    L.current_tile_cols = tile_img.cols / MOD_TILES_TILE_COLS;
    L.current_tile_rows = tile_img.rows / MOD_TILES_TILE_ROWS;

    vec2 tile_size = mod_palette_tiles_size();
    L.tiles_ro.rect.pose = u_pose_new(0, 0, tile_size.x, tile_size.y);

    palette.RO.palette = s_renew(uColor_s, palette.RO.palette, L.current_tile_cols * L.current_tile_rows);
    palette.RO.palette_size = 0;
    for(int r=0; r<L.current_tile_rows; r++) {
        for(int c=0; c<L.current_tile_cols; c++) {
            palette.RO.palette[palette.RO.palette_size++] = (uColor_s) {{id+1, c, r, 1}};
        }
    }

    snprintf(palette.RO.palette_name, sizeof palette.RO.palette_name, "Tileset: %i", id+1);
    palette_set_info(palette.RO.palette_name);
    palette.RO.palette_id = id;

    palette_save_config();
}

void palette_append_palette(uImage colors, const char *name) {
    s_log("noop");
}

bool palette_name_exists(const char *name) {
    s_log("noop");
    return false;
}

void palette_delete_palette(int id) {
    s_log("noop");
}

void palette_reset_palette_files() {
    s_log("noop");
}

void palette_save_config() {
    s_log("save");

//    uJson *config = u_json_new_file(io_config_file());
//
//    uJson *member = u_json_append_object(config, "palette");
//    uJson *palette_files = u_json_append_array(member, "palette_files");
//    for (int i = 0; i < palette.RO.max_palettes; i++) {
//        u_json_append_string(palette_files, NULL, L.palette_files[i]);
//    }
//
//    u_json_append_int(member, "palette_id", palette.RO.palette_id);
//
//    u_json_save_file(config, io_config_file(), NULL);
//    e_io_savestate_save();
//
//    u_json_kill(&config);
}

void palette_load_config() {
    s_log("load");

//    bool reset = false;
//
//    uJson *config = u_json_new_file(io_config_file());
//
//
//    uJson *member = u_json_get_object(config, "palette");
//    uJson *palette_files = u_json_get_object(member, "palette_files");
//
//    int palettes_size = u_json_get_size(palette_files);
//
//    if (palettes_size <= 0) {
//        reset = true;
//        goto CLEAN_UP;
//    }
//
//    for (int i = 0; i < palette.RO.max_palettes; i++)
//        s_free(L.palette_files[i]);
//
//    L.palette_files = s_realloc(L.palette_files, sizeof *L.palette_files * palettes_size);
//
//    palette.RO.max_palettes = palettes_size;
//
//    for (int i = 0; i < palettes_size; i++) {
//        const char *file = u_json_get_id_string(palette_files, i);
//
//        if (!file) {
//            reset = true;
//            goto CLEAN_UP;
//        }
//
//        size_t len = strlen(file) + 1;
//        char *clone = s_malloc(len);
//        memcpy(clone, file, len);
//        L.palette_files[i] = clone;
//    }
//
//    int id;
//    if (!u_json_get_object_int(member, "palette_id", &id)) {
//        reset = true;
//        goto CLEAN_UP;
//    }
//
//    if (id < 0 || id >= palette.RO.max_palettes) {
//        s_log_warn("invalid id, setting to 0");
//        id = 0;
//    }
//
//    palette_load_palette(id);
//
//    CLEAN_UP:
//    if (reset) {
//        palette_reset_palette_files();
//    }
//    u_json_kill(&config);
}
