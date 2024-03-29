#include "r/r.h"
#include "e/io.h"
#include "u/pose.h"
#include "u/image.h"
#include "u/json.h"
#include "s/file.h"
#include "io.h"
#include "m/sca/int.h"
#include "m/float.h"
#include "m/bool.h"

#include "canvas.h"


#define DEFAULT_WIDTH 32
#define DEFAULT_HEIGHT 32
#define DEFAULT_FRAME_TIME 0.25

#define GRID_RO_ALPHA 0.66

#define ONION_SKINNING_PREV_ALPHA 0.33
#define ONION_SKINNING_REM_ALPHA 0.1


// bright and dark
static const su8 PATTERN_COLORS[2][4] = {
        {204, 200, 192, 187},
        {179, 175, 166, 161}
};

struct Canvas_Globals canvas;

//
// private
//

static struct {
    uImage prev_image;
    RoSingle ro;

    RoSingle bg;

    RoBatch sprite_grid;

    rTexture default_tex;

    vec2 prev_scale;

    struct {
        float frame_times[CANVAS_MAX_FRAMES];
        int current_layer;
        int current_frame;
        bool enable_layers;
        bool enable_frames;
        int save_idx;
        int save_idx_max;
        int save_idx_min;
        struct {
            bool active;
            bool canvas_active;
            bool iso;
        } tile;
    } tab_saves[CANVAS_MAX_TABS];

} L;

_Static_assert(CANVAS_MAX_SAVES <= 999, "see save / load image");

static void clear_image(int tab_id, int save_id) {
    char file_png[128];
    snprintf(file_png, sizeof file_png, "image_%02i_%03i.png", tab_id, save_id);
    s_file_write(e_io_savestate_file_path(file_png), s_strc(""), false);
}

static void save_image(bool savestate_save) {
    char file_png[128];
    char file_json[128];
    snprintf(file_png, sizeof file_png, "image_%02i_%03i.png",
             canvas.RO.current_tab_id,
             L.tab_saves[canvas.RO.current_tab_id].save_idx);
    snprintf(file_json, sizeof file_json, "image_%02i_%03i.json",
             canvas.RO.current_tab_id,
             L.tab_saves[canvas.RO.current_tab_id].save_idx);

    u_sprite_save_file(canvas.RO.sprite,
                       e_io_savestate_file_path(file_png));

    uJson *state = u_json_new_file(e_io_savestate_file_path(file_json));
    u_json_append_int(state, "layer", canvas.RO.layers);
    u_json_append_int(state, "frames", canvas.RO.frames);

    // saves same space in the config file
    struct uJson_Options options = {0};
    options.array_single_line = true;

    u_json_save_file(state,
                     e_io_savestate_file_path(file_json),
                     &options);

    if (savestate_save)
        e_io_savestate_save();

    u_json_kill(&state);
}


static uSprite load_image_file(int tab_id, int save_idx) {
    if (tab_id < 0
        || tab_id >= CANVAS_MAX_TABS
        || save_idx < 0
        || save_idx >= CANVAS_MAX_SAVES)
        return u_sprite_new_zeros(DEFAULT_WIDTH, DEFAULT_HEIGHT, 1, 1);

    char file_png[128];
    char file_json[128];
    snprintf(file_png, sizeof file_png, "image_%02i_%03i.png",
             tab_id, save_idx);
    snprintf(file_json, sizeof file_json, "image_%02i_%03i.json",
             tab_id, save_idx);


    uJson *state = u_json_new_file(e_io_savestate_file_path(file_json));
    int layers, frames;
    if (!u_json_get_object_int(state, "layer", &layers)
        || !u_json_get_object_int(state, "frames", &frames)) {
        s_log_warn("failed to load img info");
        layers = frames = 1;
    }

    u_json_kill(&state);

    uSprite sprite = u_sprite_new_file(
            frames, layers,
            e_io_savestate_file_path(file_png));

    if (!u_sprite_valid(sprite)) {
        return u_sprite_new_zeros(DEFAULT_WIDTH, DEFAULT_HEIGHT, 1, 1);
    }

    return sprite;
}

static void load_image() {
    uSprite sprite = load_image_file(
            canvas.RO.current_tab_id,
            L.tab_saves[canvas.RO.current_tab_id].save_idx);
    canvas.RO.frames = sprite.cols;
    canvas.RO.layers = sprite.rows;
    canvas_set_sprite(sprite, false);
}

// updates the ro tex and sizes
static void update_render_objects() {
    uSprite s = canvas.RO.sprite;
    rTexture tex = r_texture_new_sprite_buffer(s.img.cols, s.img.rows, s.cols, s.rows, s.img.data);

    L.ro.tex = L.default_tex;
    ro_single_set_texture(&L.ro, tex);
    L.default_tex = tex;
    canvas.RO.tex = tex;

    {
        float w = 2.0 * canvas.RO.image.cols / L.bg.tex.sprite_size.x;
        float h = 2.0 * canvas.RO.image.rows / L.bg.tex.sprite_size.y;

        // u_pose_set_size may fail if the previous size is inf (which may happen at start with an invalid bg tex)
        L.bg.rect.uv = u_pose_new(0, 0, w, h);
    }

    int idx = 0;
    vec2 scale = canvas_get_unit_scale();
    if (!canvas.RO.frames_enabled) {
        int img_cols = canvas.RO.sprite.img.cols / canvas.RO.frames;
        for (int i = 1; i < canvas.RO.frames; i++) {
            L.sprite_grid.rects[idx].pose = u_pose_new_aa(
                    (i * img_cols - 0.5) * scale.x,
                    0,
                    1 * scale.x,
                    canvas.RO.sprite.img.rows * scale.y
            );
            L.sprite_grid.rects[idx].sprite.x = 0;
            idx++;
        }
    }
    if (!canvas.RO.layers_enabled) {
        int img_rows = canvas.RO.sprite.img.rows / canvas.RO.layers;
        for (int i = 1; i < canvas.RO.layers; i++) {
            L.sprite_grid.rects[idx].pose = u_pose_new_aa(
                    0,
                    -(i * img_rows - 0.5) * scale.y,
                    canvas.RO.sprite.img.cols * scale.x,
                    1 * scale.y
            );
            L.sprite_grid.rects[idx].sprite.x = 1;
            idx++;
        }
    }
    for (; idx < L.sprite_grid.num; idx++) {
        L.sprite_grid.rects[idx].pose = u_pose_new_hidden();
    }
    ro_batch_update(&L.sprite_grid);
}

// according to layers_, frames_enabled and L.layers, frames
static void update_sprite() {
    uSprite c = canvas.RO.sprite;

    uImage img = u_sprite_reorder_to_new_image(c);
    u_sprite_kill(&c);
    c = (uSprite) {img, 1, img.layers};

    // check layers, show full imahe
    if (!canvas.RO.layers_enabled && c.rows > 1) {
        s_log("layers to full: %i", c.rows);
        c.img.layers /= c.rows;
        c.img.rows *= c.rows;
        c.rows = 1;

    }

    // check layers, use layers
    if (canvas.RO.layers_enabled && c.rows == 1) {
        s_log("layers to sprite: %i", canvas.RO.layers);
        c.img.layers *= canvas.RO.layers;
        c.img.rows /= canvas.RO.layers;
        c.rows = canvas.RO.layers;
    }

    // check frames, morph to full image
    if (!canvas.RO.frames_enabled && c.cols > 1) {
        s_log("frames to full: %i", c.cols);
        // noop, is full in the moment
    }

    // check frames, morph into frames cols
    if (canvas.RO.frames_enabled && c.cols == 1) {
        s_log("frames to sprite: %i", canvas.RO.frames);
        uSprite sprite = u_sprite_new_reorder_from_image(canvas.RO.frames, c.img);
        u_sprite_kill(&c);
        c = sprite;
    }


    canvas.RO.sprite = c;
    canvas.RO.image = c.img;

    canvas.RO.current_frame = s_min(canvas.RO.current_frame, c.cols - 1);
    canvas.RO.current_layer = s_min(canvas.RO.current_layer, c.rows - 1);
    canvas.RO.current_image_layer = u_sprite_pos_to_layer(c.cols,
                                                          canvas.RO.current_frame,
                                                          canvas.RO.current_layer);

    u_image_kill(&L.prev_image);
    L.prev_image = u_image_new_clone(c.img);

    update_render_objects();
}



//
// public
//

bool canvas_size_valid(int cols, int rows, int frames, int layers) {
    if(cols <= 0 || rows <=0 || frames <=0 || layers <= 0)
        return false;
    ssize memory = (ssize) cols * (ssize) rows * (ssize) frames * (ssize) layers * (ssize) sizeof(uColor_s);
    if (memory < 0 || memory > CANVAS_MAX_MEMORY) {
        return false;
    }
    if (cols > r_render.limits.max_texture_size
        || rows > r_render.limits.max_texture_size
        || frames * layers > r_render.limits.max_texture_layers) {
        return false;
    }
    if(cols > CANVAS_MAX_SIZE || rows > CANVAS_MAX_SIZE
            || frames > CANVAS_MAX_FRAMES || layers > CANVAS_MAX_LAYERS)
        return false;
    return true;
}


void canvas_init() {
    canvas.show_bg = true;

    canvas.blend_mode = CANVAS_BLEND_LAYER_ONION;

    for (int i = 0; i < CANVAS_MAX_FRAMES; i++) {
        canvas.frame_times[i] = DEFAULT_FRAME_TIME;
    }

    canvas.RO.pose = mat4_eye();

    canvas.RO.frames = 1;
    canvas.RO.layers = 1;

    L.ro = ro_single_new(r_texture_new_invalid());

    L.sprite_grid = ro_batch_new(
            CANVAS_MAX_FRAMES + CANVAS_MAX_LAYERS,
            r_texture_new_file(2, 1, "res/canvas_sprite_grid.png"));
    for (int i = 0; i < L.sprite_grid.num; i++) {
        L.sprite_grid.rects[i].color = (vec4) {{0.33, 0.66, 0.33, 0.33}};
    }

    L.bg = ro_single_new(r_texture_new_invalid());
    uSprite sprite = u_sprite_new_zeros(DEFAULT_WIDTH, DEFAULT_HEIGHT, 1, 1);

    canvas_set_sprite(sprite, false);
    canvas_set_pattern_size(8, 8);
}

void canvas_update(float dtime) {
    canvas.RO.tex = L.default_tex;

    ivec2 size = canvas_get_size();
    canvas.RO.pose = u_pose_new_aa(0, 0, size.x, size.y);

    r_texture_set_sprite_buffer(L.default_tex, canvas.RO.sprite.img.data);

    // set pose
    L.ro.rect.pose = canvas.RO.pose;

    L.bg.rect.pose = canvas.RO.pose;

    if (tile.active && tile.canvas_active)
        tile_on_canvas_update();

    // update render objects if scale differs too much (tile on off, etc.)
    vec2 scale = canvas_get_unit_scale();
    if(!bvec2_all(vec2_equal_eps_vec(scale, L.prev_scale, 0.01))) {
        s_log("scale changed");
        update_render_objects();
    }
    L.prev_scale = scale;
}

void canvas_render(const mat4 *canvascam_mat) {
    L.ro.tex = canvas.RO.tex;

    float ro_alpha = canvas.show_grid ? GRID_RO_ALPHA : 1;

    bool tile_iso = tile.active && tile.canvas_active && tile.iso;
    if (canvas.show_bg && !tile_iso) {
        ro_single_render(&L.bg, canvascam_mat);
    }

    switch (canvas.blend_mode) {
        case CANVAS_BLEND_NONE:
            L.ro.rect.color.a = ro_alpha;
            L.ro.rect.sprite.x = canvas.RO.current_frame;
            L.ro.rect.sprite.y = canvas.RO.current_layer;
            ro_single_render(&L.ro, canvascam_mat);
            break;
        case CANVAS_BLEND_FRAMES_ONION:
            L.ro.rect.sprite.y = canvas.RO.current_layer;
            for (int i = 0; i <= canvas.RO.current_frame; i++) {
                float alpha = ONION_SKINNING_REM_ALPHA;
                if (i == canvas.RO.current_frame - 1)
                    alpha = ONION_SKINNING_PREV_ALPHA;
                else if (i == canvas.RO.current_frame)
                    alpha = 1;
                L.ro.rect.color.a = alpha * ro_alpha;
                L.ro.rect.sprite.x = i;
                ro_single_render(&L.ro, canvascam_mat);
            }
            break;
        case CANVAS_BLEND_FRAMES_FULL:
            L.ro.rect.color.a = ro_alpha;
            L.ro.rect.sprite.y = canvas.RO.current_layer;
            for (int i = 0; i <= canvas.RO.current_frame; i++) {
                L.ro.rect.sprite.x = i;
                ro_single_render(&L.ro, canvascam_mat);
            }
            break;
        case CANVAS_BLEND_LAYER_ONION:
            L.ro.rect.sprite.x = canvas.RO.current_frame;
            for (int i = 0; i <= canvas.RO.current_layer; i++) {
                float alpha = ONION_SKINNING_REM_ALPHA;
                if (i == canvas.RO.current_layer - 1)
                    alpha = ONION_SKINNING_PREV_ALPHA;
                else if (i == canvas.RO.current_layer)
                    alpha = 1;
                L.ro.rect.color.a = alpha * ro_alpha;
                L.ro.rect.sprite.y = i;
                ro_single_render(&L.ro, canvascam_mat);
            }
            break;
        case CANVAS_BLEND_LAYER_FULL:
            L.ro.rect.color.a = ro_alpha;
            L.ro.rect.sprite.x = canvas.RO.current_frame;
            for (int i = 0; i <= canvas.RO.current_layer; i++) {
                L.ro.rect.sprite.y = i;
                ro_single_render(&L.ro, canvascam_mat);
            }
            break;
        default:
            s_assume(false, "invalid blend mode");
    }


    if (canvas.show_grid) {
        ro_batch_render(&L.sprite_grid, canvascam_mat, false);
    }
}

uImage canvas_get_full_image() {
    canvas_reload();
    uImage img = u_sprite_reorder_to_new_image(canvas.RO.sprite);
    img.rows *= img.layers;
    img.layers = 1;
    return img;
}

uImage canvas_get_merged_image() {
    uImage img = canvas_get_full_image();
    img.rows /= canvas.RO.layers;
    img.layers = canvas.RO.layers;
    uImage merged = u_image_new_clone_merge_down_full(img);
    u_image_kill(&img);
    return merged;
}

uSprite canvas_get_sprite() {
    uImage img = canvas_get_full_image();
    img.rows /= canvas.RO.layers;
    img.layers = canvas.RO.layers;
    uSprite sprite = u_sprite_new_reorder_from_image(canvas.RO.frames, img);
    u_image_kill(&img);
    return sprite;
}

void canvas_set_frame(int sprite_col) {
    sprite_col = sca_clamp(sprite_col, 0, canvas.RO.sprite.cols - 1);
    s_log("frame: %i/%i", sprite_col, canvas.RO.sprite.cols);
    canvas.RO.current_frame = sprite_col;
    canvas.RO.current_image_layer = u_sprite_pos_to_layer(canvas.RO.sprite.cols,
                                                          canvas.RO.current_frame,
                                                          canvas.RO.current_layer);
}

void canvas_set_layer(int sprite_row) {
    sprite_row = sca_clamp(sprite_row, 0, canvas.RO.sprite.rows - 1);
    s_log("layer: %i/%i", sprite_row, canvas.RO.sprite.rows);
    canvas.RO.current_layer = sprite_row;
    canvas.RO.current_image_layer = u_sprite_pos_to_layer(canvas.RO.sprite.cols,
                                                          canvas.RO.current_frame,
                                                          canvas.RO.current_layer);
}

void canvas_enable_frames(bool enable) {
    s_log("enable: %i", enable);
    canvas_reload();
    if (enable == canvas.RO.frames_enabled) {
        s_log_warn("nothing changed");
        return;
    }
    canvas.RO.frames_enabled = enable;
    canvas.RO.current_frame = enable ? canvas.RO.frames - 1 : 0;
    update_sprite();
    canvas_save_config();
}


void canvas_enable_layers(bool enable) {
    s_log("enable: %i", enable);
    canvas_reload();
    if (enable == canvas.RO.layers_enabled) {
        s_log_warn("nothing changed");
        return;
    }
    canvas.RO.layers_enabled = enable;
    canvas.RO.current_layer = enable ? canvas.RO.layers - 1 : 0;
    update_sprite();
    canvas_save_config();
}


void canvas_set_sprite(uSprite image_sink, bool save) {
    if (!u_sprite_valid(image_sink)) {
        s_log_warn("invalid img");
        return;
    }
    if (image_sink.rows > CANVAS_MAX_LAYERS) {
        s_log_warn("to much layers!");
        return;
    }
    if (image_sink.cols > CANVAS_MAX_FRAMES) {
        s_log_warn("to much frames!");
        return;
    }
    if (image_sink.img.cols > CANVAS_MAX_SIZE
        || image_sink.img.rows > CANVAS_MAX_SIZE) {
        s_log_warn("to large");
        return;
    }
    s_log("set_sprite: size %i:%i sprite: %i:%i",
          image_sink.img.cols, image_sink.img.rows,
          image_sink.cols, image_sink.rows);

    // new frames copy last frame time
    for (int i = canvas.RO.frames; i < image_sink.cols; i++) {
        canvas.frame_times[i] = canvas.frame_times[canvas.RO.frames - 1];
    }
    canvas.RO.cols = image_sink.img.cols;
    canvas.RO.rows = image_sink.img.rows;
    canvas.RO.frames = image_sink.cols;
    canvas.RO.layers = image_sink.rows;

    u_sprite_kill(&canvas.RO.sprite);
    canvas.RO.sprite = image_sink;
    update_sprite();

    if (save) {
        // bypass equals test
        L.prev_image.data[0].x++;
        canvas_save();
    }
}

void canvas_set_pattern_size(int cols, int rows) {
    s_log("size: %i, %i", cols, rows);
    canvas.RO.pattern_size = (ivec2) {{cols, rows}};
    // each pixel has 4 colors, and we need a bright and a dark pattern
    uImage img = u_image_new_empty(cols * 4, rows * 4, 1);
    for (int r = 0; r < img.rows; r++) {
        for (int c = 0; c < img.cols; c++) {
            bool dark = r < img.rows / 2 ? (c < img.cols / 2 ? false : true) : (c < img.cols / 2 ? true : false);
            bool even_row = (r / 2) % 2 == 0;
            int dark_idx = dark ? 1 : 0;
            int idx;

            // swap each pixel row
            if (even_row)
                idx = c % 4;
            else
                idx = (c + 2) % 4;

            // bottom order of a pixel
            if (r % 2 == 1)
                idx = (int[]) {1, 0, 3, 2}[idx];
            su8 col = PATTERN_COLORS[dark_idx][idx];
            *u_image_pixel(img, c, r, 0) = (uColor_s) {{col, col, col, 255}};
        }
    }
    rTexture tex = r_texture_new(img.cols, img.rows, 1, 1, img.data);
    r_texture_wrap_repeat(tex);
    ro_single_set_texture(&L.bg, tex);
    update_render_objects();

    u_image_kill(&img);
}

void canvas_save() {
    s_log("save");
    if (u_image_equals(canvas.RO.image, L.prev_image)) {
        s_log("failed, not changed");
        return;
    }

    u_image_copy(L.prev_image, canvas.RO.image);

    int t = canvas.RO.current_tab_id;
    L.tab_saves[t].save_idx++;
    L.tab_saves[t].save_idx %= CANVAS_MAX_SAVES;
    L.tab_saves[t].save_idx_max = L.tab_saves[t].save_idx;
    if (L.tab_saves[t].save_idx == L.tab_saves[t].save_idx_min) {
        L.tab_saves[t].save_idx_min++;
        L.tab_saves[t].save_idx_min %= CANVAS_MAX_SAVES;
    }

    canvas_save_config();
}

void canvas_reload() {
    u_image_copy(canvas.RO.image, L.prev_image);
}

void canvas_undo() {
    s_log("undo");
    int t = canvas.RO.current_tab_id;
    if (L.tab_saves[t].save_idx == L.tab_saves[t].save_idx_min) {
        s_log("failed, on min idx");
        return;
    }

    L.tab_saves[t].save_idx--;
    if (L.tab_saves[t].save_idx < 0)
        L.tab_saves[t].save_idx = CANVAS_MAX_SAVES - 1;

    load_image();
    canvas_save_config();
}

void canvas_redo() {
    s_log("redo");
    int t = canvas.RO.current_tab_id;
    if (L.tab_saves[t].save_idx == L.tab_saves[t].save_idx_max) {
        s_log("failed, on max idx");
        return;
    }

    L.tab_saves[t].save_idx++;
    L.tab_saves[t].save_idx %= CANVAS_MAX_SAVES;

    load_image();

    canvas_save_config();
}

bool canvas_undo_available() {
    int t = canvas.RO.current_tab_id;
    return L.tab_saves[t].save_idx != L.tab_saves[t].save_idx_min;
}

bool canvas_redo_available() {
    int t = canvas.RO.current_tab_id;
    return L.tab_saves[t].save_idx != L.tab_saves[t].save_idx_max;
}


void canvas_set_tab_id(int id) {
    s_assume(id >= 0 && id < CANVAS_MAX_TABS, "invalid tab id");
    L.tab_saves[canvas.RO.current_tab_id].current_layer = canvas.RO.current_layer;
    L.tab_saves[canvas.RO.current_tab_id].current_frame = canvas.RO.current_frame;
    canvas_save_config();
    canvas.RO.current_tab_id = id;
    load_image();
    u_image_kill(&L.prev_image);
    L.prev_image = u_image_new_clone(canvas.RO.image);

    canvas_set_frame(L.tab_saves[id].current_frame);
    canvas_set_layer(L.tab_saves[id].current_layer);
    tile.active = L.tab_saves[id].tile.active;
    tile.canvas_active = L.tab_saves[id].tile.canvas_active;
    tile.iso = L.tab_saves[id].tile.iso;

    vecN_copy(canvas.frame_times, L.tab_saves[id].frame_times, CANVAS_MAX_FRAMES);

    // a call to canvas_enable_* may save with the wrong current setting,
    // so that the second call may be wrong
    // we save the settings and call them with these values instead
    bool enable_frames = L.tab_saves[id].enable_frames;
    bool enable_layers = L.tab_saves[id].enable_layers;
    s_log("enable frames, layers: %i, %i", enable_frames, enable_layers);
    canvas_enable_frames(enable_frames);
    canvas_enable_layers(enable_layers);
}

uSprite canvas_get_tab(int id) {
    s_log("id=%i", id);
    s_assume(id >= 0 && id < CANVAS_MAX_TABS, "invalid tab id");
    return load_image_file(id, L.tab_saves[id].save_idx);
}

void canvas_clear_all_base_tabs() {
    for(int i=0; i<CANVAS_MAX_TABS; i++) {
        clear_image(i, 0);
    }
}

void canvas_save_config() {
    s_log("save");

    save_image(false);

    uJson *config = u_json_new_file(io_config_file());

    uJson *member = u_json_append_object(config, "canvas");

    u_json_append_int(member, "current_tab_id", canvas.RO.current_tab_id);

    int tab = canvas.RO.current_tab_id;
    L.tab_saves[tab].current_layer = canvas.RO.current_layer;
    L.tab_saves[tab].current_frame = canvas.RO.current_frame;
    L.tab_saves[tab].enable_layers = canvas.RO.layers_enabled;
    L.tab_saves[tab].enable_frames = canvas.RO.frames_enabled;
    L.tab_saves[tab].tile.active = tile.active;
    L.tab_saves[tab].tile.canvas_active = tile.canvas_active;
    L.tab_saves[tab].tile.iso = tile.iso;
    vecN_copy(L.tab_saves[tab].frame_times, canvas.frame_times, CANVAS_MAX_FRAMES);

    for (int t = 0; t < CANVAS_MAX_TABS; t++) {
        char name[16];
        snprintf(name, sizeof name, "tab_%02i", t);

        uJson *tab = u_json_append_object(member, name);

        u_json_append_int(tab, "current_layer", L.tab_saves[t].current_layer);
        u_json_append_int(tab, "current_frame", L.tab_saves[t].current_frame);

        u_json_append_bool(tab, "enable_layers", L.tab_saves[t].enable_layers);
        u_json_append_bool(tab, "enable_frames", L.tab_saves[t].enable_frames);

        u_json_append_int(tab, "save_idx", L.tab_saves[t].save_idx);
        u_json_append_int(tab, "save_idx_max", L.tab_saves[t].save_idx_max);
        u_json_append_int(tab, "save_idx_min", L.tab_saves[t].save_idx_min);

        u_json_append_bool(tab, "tile_active", L.tab_saves[t].tile.active);
        u_json_append_bool(tab, "tile_canvas_active", L.tab_saves[t].tile.canvas_active);
        u_json_append_bool(tab, "tile_iso", L.tab_saves[t].tile.iso);

        uJson *frame_times = u_json_append_array(tab, "frame_times");
        for (int i = 0; i < CANVAS_MAX_FRAMES; i++) {
            u_json_append_float(frame_times, NULL, L.tab_saves[t].frame_times[i]);
        }
    }

    u_json_append_int(member, "pattern_cols", canvas.RO.pattern_size.x);
    u_json_append_int(member, "pattern_rows", canvas.RO.pattern_size.y);

    u_json_save_file(config, io_config_file(), NULL);

    e_io_savestate_save();

    u_json_kill(&config);
}

void canvas_load_config() {
    s_log("load");

    uJson *config = u_json_new_file(io_config_file());

    uJson *member = u_json_get_object(config, "canvas");

    for (int t = 0; t < CANVAS_MAX_TABS; t++) {
        char name[16];
        snprintf(name, sizeof name, "tab_%02i", t);

        uJson *tab = u_json_get_object(member, name);
        bool ok = true;
        ok &= u_json_get_object_int(tab, "current_layer", &L.tab_saves[t].current_layer) != NULL;
        ok &= u_json_get_object_int(tab, "current_frame", &L.tab_saves[t].current_frame) != NULL;

        const bool *enable_layers = u_json_get_object_bool(tab, "enable_layers");
        const bool *enable_frames = u_json_get_object_bool(tab, "enable_frames");

        ok &= enable_layers && enable_frames;
        if(ok) {
            L.tab_saves[t].enable_layers = *enable_layers;
            L.tab_saves[t].enable_frames = *enable_frames;
        }

        ok &= u_json_get_object_int(tab, "save_idx", &L.tab_saves[t].save_idx) != NULL;
        ok &= u_json_get_object_int(tab, "save_idx_max", &L.tab_saves[t].save_idx_max) != NULL;
        ok &= u_json_get_object_int(tab, "save_idx_min", &L.tab_saves[t].save_idx_min) != NULL;

        const bool *tile_active = u_json_get_object_bool(tab, "tile_active");
        const bool *tile_canvas_active = u_json_get_object_bool(tab, "tile_canvas_active");
        const bool *tile_iso = u_json_get_object_bool(tab, "tile_iso");

        ok &= tile_active && tile_canvas_active && tile_iso;
        if(ok) {
            L.tab_saves[t].tile.active = *tile_active;
            L.tab_saves[t].tile.canvas_active = *tile_canvas_active;
            L.tab_saves[t].tile.iso = *tile_iso;
        }

        uJson *frame_times = u_json_get_object(tab, "frame_times");
        for (int i = 0; i < CANVAS_MAX_FRAMES; i++) {
            if(!u_json_get_id_float(frame_times, i, &L.tab_saves[t].frame_times[i])) {
                L.tab_saves[t].frame_times[i] = DEFAULT_FRAME_TIME;
            }
        }

        if (!ok) {
            s_log_debug("failed to load tab %i info, resetting to 0", t);
            memset(&L.tab_saves[t], 0, sizeof L.tab_saves[t]);
            vecN_set(L.tab_saves[t].frame_times, DEFAULT_FRAME_TIME, CANVAS_MAX_FRAMES);
        }
    }

    int tab_id;
    if (u_json_get_object_int(member, "current_tab_id", &tab_id)) {
        canvas.RO.current_tab_id = tab_id;
        load_image();
        canvas_set_layer(canvas.RO.sprite.rows - 1);
    } else {
        s_log("failed, saving the empty image as index 0");
        save_image(true);
    }

    int pattern_cols, pattern_rows;
    if (u_json_get_object_int(member, "pattern_cols", &pattern_cols)
        && u_json_get_object_int(member, "pattern_rows", &pattern_rows)) {
        canvas_set_pattern_size(pattern_cols, pattern_rows);
    }

    vecN_copy(canvas.frame_times, L.tab_saves[canvas.RO.current_tab_id].frame_times, CANVAS_MAX_FRAMES);

    update_render_objects();

    u_json_kill(&config);
}
