#include "r/r.h"
#include "e/io.h"
#include "u/pose.h"
#include "u/json.h"
#include "rhc/rhc_full.h"
#include "mathc/float.h"
#include "brush.h"
#include "camera.h"
#include "palette.h"

#define COLOR_DROP_SIZE 16.0f
#define MAX_ROWS 10

#define SWIPE_DISTANCE 50

#define INFO_STATIC_TIME 0.5
#define INFO_TIME 1.5

struct Palette_Globals palette;

//
// private
//

static struct {
    RoBatch palette_ro;
    RoSingle select_ro;
    RoBatch background_ro;

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
    } swipe;

    int last_selected;
    int current_pressed;


    mat4 custom_select_pose;
    bool custom_select_active;

    char **palette_files;
} L;

static int palette_cols() {
    assert(camera_width() > 0 && camera_height() > 0 && "startup bug?");
    if (camera_is_portrait_mode())
        return (int) floorf(camera_width() / COLOR_DROP_SIZE);
    return (int) floorf(camera_height() / COLOR_DROP_SIZE);
}


static mat4 setup_palette_color_pose(int r, int c) {
    mat4 pose = mat4_eye();
    u_pose_set_size(&pose, COLOR_DROP_SIZE, COLOR_DROP_SIZE);
    if (camera_is_portrait_mode()) {
        u_pose_set_xy(&pose, camera.RO.left + COLOR_DROP_SIZE / 2 + c * COLOR_DROP_SIZE,
                      camera.RO.bottom + COLOR_DROP_SIZE / 2 + r * COLOR_DROP_SIZE);
    } else {
        u_pose_set_xy(&pose, camera.RO.right - COLOR_DROP_SIZE / 2 - r * COLOR_DROP_SIZE,
                      camera.RO.bottom + COLOR_DROP_SIZE / 2 + c * COLOR_DROP_SIZE);
        u_pose_set_angle(&pose, M_PI_2);
    }
    return pose;
}


// returns the swipe move difference in %
static float swipe_diff(ePointer_s pointer) {
    float diff;
    if (camera_is_portrait_mode()) {
        diff = pointer.pos.x - L.swipe.start.x;
    } else {
        diff = pointer.pos.y - L.swipe.start.y;
    }
    return diff / SWIPE_DISTANCE;
}


//
// public
//

void palette_init() {
    palette.ro_color = R_COLOR_WHITE;
    palette.include_transparent_at_set_colors = true;
    palette.auto_save_config = true;

    L.current_pressed = -1;

    L.palette_ro = ro_batch_new(PALETTE_MAX, r_texture_new_file(1, 1, "res/color_drop.png"));

    L.background_ro = ro_batch_new(PALETTE_MAX + MAX_ROWS,
                                   r_texture_new_file(2, 2, "res/palette_background.png"));

    L.select_ro = ro_single_new(r_texture_new_file(1, 1, "res/palette_select.png"));


    L.info.bg = ro_single_new(r_texture_new_file(1, 1, "res/palette_info_bg.png"));
    L.info.text = ro_text_new_font55(20);

    L.swipe.arrows = ro_batch_new(2, r_texture_new_file(1, 1, "res/palette_arrow.png"));


    // default palette:
    {
        uColor_s palette[4] = {
                {0,   0,   0,   0},
                {0,   0,   0,   255},
                {128, 128, 128, 255},
                {255, 255, 255, 255}
        };
        palette_set_colors(palette, 4, NULL);
    }

    return;
}


void palette_update(float dtime) {

    int cols = palette_cols();
    int last_row = (palette.RO.palette_size - 1) / cols;
    for (int i = 0; i < PALETTE_MAX; i++) {
        int r = i / cols;
        int c = i % cols;

        // pose
        mat4 pose = mat4_eye();
        if (r <= last_row)
            pose = setup_palette_color_pose(r, c);
        else
            u_pose_set(&pose, FLT_MAX, FLT_MAX, 0, 0, 0);
        L.palette_ro.rects[i].pose = pose;
        L.background_ro.rects[i].pose = pose;

        // color
        vec4 col;
        if (i < palette.RO.palette_size)
            col = u_color_to_vec4(palette.RO.palette[i]);
        else
            col = R_COLOR_TRANSPARENT;

        L.palette_ro.rects[i].color = vec4_scale_vec(col, palette.ro_color);


        // background sprite
        {
            float u = i < palette.RO.palette_size ? 0 : 1;
            float v = r < last_row ? 1 : 0;
            L.background_ro.rects[i].sprite = (vec2) {{u, v}};
        }
    }

    // background continuation
    for (int r = 0; r < MAX_ROWS; r++) {
        int idx = L.background_ro.num - r - 1;
        // pose
        mat4 pose = mat4_eye();
        if (r <= last_row)
            pose = setup_palette_color_pose(r, cols);
        else
            u_pose_set(&pose, FLT_MAX, FLT_MAX, 0, 0, 0);
        L.background_ro.rects[idx].pose = pose;

        // background uv
        {
            float u = 1;
            float v = r < last_row ? 1 : 0;
            L.background_ro.rects[idx].sprite = (vec2) {{u, v}};
        }
    }

    if (L.custom_select_active)
        L.select_ro.rect.pose = L.custom_select_pose;
    else
        L.select_ro.rect.pose = L.palette_ro.rects[L.last_selected].pose;

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
                    pos, 0, 128, 8, M_PI_2);

            pos -= 2;
            L.info.text.pose = u_pose_new_angle(
                    pos, L.info.x_offset,
                    1, 1, M_PI_2);
        }
    }

}

void palette_render(const mat4 *cam_mat) {
    if (L.info.time > 0) {
        ro_single_render(&L.info.bg, cam_mat);
        ro_text_render(&L.info.text, cam_mat);
    }

    ro_batch_render(&L.background_ro, cam_mat, true);
    ro_batch_render(&L.palette_ro, cam_mat, true);
    ro_single_render(&L.select_ro, cam_mat);

    if (L.swipe.swiping)
        ro_batch_render(&L.swipe.arrows, cam_mat, true);
}


bool palette_pointer_event(ePointer_s pointer) {
    if (!palette_contains_pos(pointer.pos.xy)) {
        for (int i = 0; i < 2; i++)
            L.swipe.arrows.rects[i].color.a = 0;
        L.swipe.swiping = false;
        return false;
    }

    if (pointer.action == E_POINTER_DOWN) {
        for (int i = 0; i < 2; i++)
            L.swipe.arrows.rects[i].color.a = 0;
        L.swipe.start = pointer.pos.xy;
        L.swipe.swiping = true;

        for (int i = 0; i < palette.RO.palette_size; i++) {
            // pose will be rotated in landscape mode (so do not use _aa_)!
            if (u_pose_contains(L.palette_ro.rects[i].pose, pointer.pos)) {
                L.current_pressed = i;
                return true;
            }
        }

        L.current_pressed = -1;
        return true;
    }

    if (pointer.action == E_POINTER_UP) {
        for (int i = 0; i < 2; i++)
            L.swipe.arrows.rects[i].color.a = 0;
        L.swipe.swiping = false;
    }

    if (L.current_pressed != -1
        // pose will be rotated in landscape mode (so do not use _aa_)!
        && !u_pose_contains(L.palette_ro.rects[L.current_pressed].pose,
                            pointer.pos)) {
        L.current_pressed = -1;
    }

    if (L.current_pressed != -1 && pointer.action == E_POINTER_UP) {
        palette_set_color(L.current_pressed);
        L.current_pressed = -1;
    }

    if (L.swipe.swiping && pointer.action == E_POINTER_MOVE) {
        float diff = swipe_diff(pointer);
        if (diff > 1) {
            int id = palette.RO.palette_id - 1;
            if (id < 0)
                id = palette.RO.max_palettes - 1;
            palette_load_palette(id);
            L.swipe.swiping = false;

        } else if (diff <= -1) {
            int id = palette.RO.palette_id + 1;
            id %= palette.RO.max_palettes;
            palette_load_palette(id);
            L.swipe.swiping = false;

        }

        float alpha = sca_smoothstep(sca_abs(diff), 0.25, 1);
        for (int i = 0; i < 2; i++)
            L.swipe.arrows.rects[i].color.a = alpha;
        if (camera_is_portrait_mode()) {
            for (int i = 0; i < 2; i++) {
                L.swipe.arrows.rects[i].pose = u_pose_new_angle(
                        (int[]) {-1, 1}[i] * (camera_width() / 2 - 20),
                        camera.RO.bottom + 16,
                        32, 32,
                        sca_sign(diff) * M_PI_2 - M_PI_2
                );
            }
        } else {
            for (int i = 0; i < 2; i++) {
                L.swipe.arrows.rects[i].pose = u_pose_new_angle(
                        camera.RO.right - 16,
                        (int[]) {-1, 1}[i] * (camera_height() / 2 - 20),
                        32, 32,
                        sca_sign(diff) * M_PI_2
                );
            }
        }
    }

    return true;
}

float palette_get_hud_size() {
    int cols = palette_cols();
    int rows = 1 + (palette.RO.palette_size - 1) / cols;
    return rows * COLOR_DROP_SIZE;
}

mat4 palette_get_pose() {
    int size = palette_get_hud_size();
    if (camera_is_portrait_mode()) {
        return u_pose_new(0, camera.RO.bottom + size / 2,
                          camera_width(),
                          size);

    }
    return u_pose_new(camera.RO.right - size / 2, 0,
                      size,
                      camera_height());
}

bool palette_contains_pos(vec2 pos) {
    int size = palette_get_hud_size();
    if (camera_is_portrait_mode()) {
        return pos.y <= camera.RO.bottom + size;
    }
    return pos.x >= camera.RO.right - size;
}

int palette_get_color() {
    return L.last_selected;
}

void palette_set_color(int index) {
    if (index < 0 || index >= palette.RO.palette_size) {
        log_error("invalid index (%i/%i)",
                  index, palette.RO.palette_size);
        return;
    }
    brush.current_color = palette.RO.palette[index];
    brush.secondary_as_current = false;
    L.select_ro.rect.pose = L.palette_ro.rects[index].pose;
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

void palette_set_colors(const uColor_s *colors, int size, const char *name_ref) {
    log_info("set_colors: %s", name_ref);
    assume(size > 0, "palette set_colors failed");

    palette.RO.palette_size = 0;

    if (palette.include_transparent_at_set_colors) {
        palette.RO.palette[palette.RO.palette_size++] = U_COLOR_TRANSPARENT;
    }

    // copy unique colors
    for (int i = 0; i < size && palette.RO.palette_size < PALETTE_MAX; i++) {
        bool found = false;
        for (int j = 0; j < palette.RO.palette_size; j++) {
            if (u_color_equals(colors[i], palette.RO.palette[j])) {
                found = true;
                break;
            }
        }
        if (!found) {
            palette.RO.palette[palette.RO.palette_size++] = colors[i];
        }
    }

    palette_set_color(0);
    palette.RO.palette_name = name_ref ? name_ref : "custom palette";

    palette_set_info(palette.RO.palette_name);
}


void palette_set_palette(uImage colors, const char *name_ref) {
    if (!u_image_valid(colors)) {
        log_error("invalid");
        return;
    }

    int size = colors.cols * colors.rows;

    if (size > PALETTE_MAX || colors.layers != 1) {
        log_error("to large, or multiple layers (%i/%i)",
                  size, PALETTE_MAX);
        return;
    }

    palette_set_colors(colors.data, size, name_ref);
}

void palette_load_palette(int id) {
    if (id < 0 || id >= palette.RO.max_palettes) {
        log_error("invalid id: %i/%i", id, palette.RO.max_palettes);
        return;
    }

    log_info("load_palette[%i] = %s", id, L.palette_files[id]);

    char file[256];
    snprintf(file, sizeof file, "palette_%s", L.palette_files[id]);

    char name[32];
    snprintf(name, sizeof name, "%s", L.palette_files[id]);

    // name to lower and without .png
    Str_s name_s = strc(name);
    name_s = str_tolower(name_s);
    name_s = str_eat_back_str(name_s, strc(".png"));
    name_s.data[name_s.size] = '\0';

    uImage colors = u_image_new_file(1,
                                     e_io_savestate_file_path(file)
    );

    palette.RO.palette_id = id;
    palette_set_palette(colors, name);

    u_image_kill(&colors);

    if (palette.auto_save_config)
        palette_save_config();
}

void palette_append_file(uImage colors, const char *name) {
    log_info("append_file: %s", name);

    u_image_save_file(colors, e_io_savestate_file_path(name));

    int idx = -1;
    for (int i = 0; i < palette.RO.max_palettes; i++) {
        if (strcmp(name, L.palette_files[i]) == 0) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        size_t len = strlen(name) + 1;
        char *clone = rhc_malloc(len);
        memcpy(clone, name, len);
        L.palette_files = rhc_realloc(L.palette_files, sizeof *L.palette_files * ++palette.RO.max_palettes);
        idx = palette.RO.max_palettes - 1;
        L.palette_files[idx] = clone;
    }

    // save the savestate files (needed for web)
    e_io_savestate_save();

    palette_set_palette(colors, L.palette_files[idx]);
    palette.RO.palette_id = idx;
    if (palette.auto_save_config)
        palette_save_config();
}

void palette_reset_palette_files() {
    log_info("reset");
    uImage *palettes = palette_defaults_new();

    for (int i = 0; i < palette.RO.max_palettes; i++)
        rhc_free(L.palette_files[i]);

    L.palette_files = rhc_realloc(L.palette_files, sizeof *L.palette_files * 32);

    int i;
    for (i = 0; u_image_valid(palettes[i]); i++) {
        assume(i < 32, "change max default palettes");
        char *name = palette_defaults_name_on_heap(i);
        char file[256];
        snprintf(file, sizeof file, "palette_%s", name);
        u_image_save_file(palettes[i], e_io_savestate_file_path(file));

        L.palette_files[i] = name;
    }
    palette.RO.max_palettes = i;

    palette.RO.palette_id = 0;

    // save the savestate files (needed for web)
    e_io_savestate_save();

    palette_set_palette(palettes[0], L.palette_files[0]);

    palette_defaults_kill(&palettes);

    if (palette.auto_save_config)
        palette_save_config();
}

void palette_save_config() {
    log_info("save");

    uJson *config = u_json_new_file(
            e_io_savestate_file_path("config.json"));

    uJson *member = u_json_append_object(config, "palette");
    uJson *palette_files = u_json_append_array(member, "palette_files");
    for (int i = 0; i < palette.RO.max_palettes; i++) {
        u_json_append_string(palette_files, NULL, L.palette_files[i]);
    }

    u_json_append_int(member, "palette_id", palette.RO.palette_id);

    u_json_save_file(config,
                     e_io_savestate_file_path("config.json"));
    e_io_savestate_save();

    u_json_kill(&config);
}

void palette_load_config() {
    log_info("load");

    bool reset = false;

    uJson *config = u_json_new_file(
            e_io_savestate_file_path("config.json"));


    uJson *member = u_json_get_object(config, "palette");
    uJson *palette_files = u_json_get_object(member, "palette_files");

    int palettes_size = u_json_get_size(palette_files);

    if (palettes_size <= 0) {
        reset = true;
        goto CLEAN_UP;
    }

    for (int i = 0; i < palette.RO.max_palettes; i++)
        rhc_free(L.palette_files[i]);

    L.palette_files = rhc_realloc(L.palette_files, sizeof *L.palette_files * palettes_size);

    palette.RO.max_palettes = palettes_size;

    for (int i = 0; i < palettes_size; i++) {
        const char *file = u_json_get_id_string(palette_files, i);

        if (!file) {
            reset = true;
            goto CLEAN_UP;
        }

        size_t len = strlen(file) + 1;
        char *clone = rhc_malloc(len);
        memcpy(clone, file, len);
        L.palette_files[i] = clone;
    }

    int id;
    if (!u_json_get_object_int(member, "palette_id", &id)) {
        reset = true;
        goto CLEAN_UP;
    }

    if (id < 0 || id >= palette.RO.max_palettes) {
        log_warn("invalid id, setting to 0");
        id = 0;
    }

    palette_load_palette(id);

    CLEAN_UP:
    if (reset) {
        palette_reset_palette_files();
    }
    u_json_kill(&config);
}
