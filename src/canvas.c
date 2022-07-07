#include "r/r.h"
#include "u/pose.h"
#include "u/image.h"
#include "u/json.h"
#include "e/io.h"
#include "m/sca/int.h"
#include "m/mat/float.h"

#include "canvas.h"


struct Canvas_Globals canvas;

//
// private
//

static struct {
    uImage prev_image;
    RoSingle render_objects[CANVAS_MAX_LAYERS];

    RoSingle bg;
    RoSingle grid;

    int save_idx;
    int save_idx_max;
    int save_idx_min;

    int save_layers[CANVAS_MAX_SAVES];
} L;

_Static_assert(CANVAS_MAX_SAVES <= 999, "see save / load image");


static void save_image() {
    char file[128];
    snprintf(file, sizeof file, "image_%02i_%03i.png", canvas.RO.tab_id, L.save_idx);
    u_image_save_file(canvas.RO.image,
                      e_io_savestate_file_path(file));
    e_io_savestate_save();
    L.save_layers[L.save_idx] = canvas.RO.image.layers;
}

static uImage load_image_file(int tab_id, int save_idx) {
    char file[128];
    snprintf(file, sizeof file, "image_%02i_%03i.png", tab_id, save_idx);
    int layers = L.save_layers[L.save_idx];
    layers = isca_clamp(layers, 1, CANVAS_MAX_LAYERS);
    uImage img = u_image_new_file(1,
                                  e_io_savestate_file_path(file));
    if (img.rows % layers == 0) {
        img.rows /= layers;
        img.layers = layers;
    }
    return img;
}

static void load_image() {
    uImage img = load_image_file(canvas.RO.tab_id, L.save_idx);
    canvas_set_image(img, false);
}

// updates the ro tex and sizes
static void update_render_objects() {
    for (int i = 0; i < canvas.RO.image.layers; i++) {
        rTexture tex = r_texture_new(canvas.RO.image.cols, canvas.RO.image.rows, 1, 1,
                                     u_image_layer(canvas.RO.image, i));
        ro_single_set_texture(&L.render_objects[i], tex);
    }

    u_pose_set_size(&L.grid.rect.uv, canvas.RO.image.cols, canvas.RO.image.rows);
    {
        float w = (float) canvas.RO.image.cols / (2 * canvas.RO.pattern_cols);
        float h = (float) canvas.RO.image.rows / (2 * canvas.RO.pattern_rows);
        u_pose_set_size(&L.bg.rect.uv, w, h);
    }
}




//
// public
//


void canvas_init() {
    canvas.ro_color = R_COLOR_WHITE;

    canvas.alpha = 1.0;
    canvas.blend_layers = true;
    canvas.import_file = "import.png";
    canvas.auto_save_config = true;

    canvas.RO.pose = mat4_eye();

    canvas.RO.pattern_cols = 8;
    canvas.RO.pattern_rows = 8;
    
    canvas.RO.max_tabs = 9;

    for (int i = 0; i < CANVAS_MAX_LAYERS; i++) {
        L.render_objects[i] = ro_single_new(r_texture_new_invalid());
    }

    rTexture grid_tex = r_texture_new_file(1, 1, "res/canvas_grid.png");
    r_texture_wrap_repeat(grid_tex);
    L.grid = ro_single_new(grid_tex);

    uColor_s buf[4];
    buf[0] = buf[3] = u_color_from_hex("#999999");
    buf[1] = buf[2] = u_color_from_hex("#777777");
    rTexture bg_tex = r_texture_new(2, 2, 1, 1, buf);
    r_texture_wrap_repeat(bg_tex);
    L.bg = ro_single_new(bg_tex);

    uImage img = u_image_new_zeros(32, 32, 1);
    canvas_set_image(img, false);
}

void canvas_update(float dtime) {

    canvas.RO.pose = u_pose_new_aa(0, 0, canvas.RO.image.cols, canvas.RO.image.rows);

    for (int i = 0; i < canvas.RO.image.layers; i++) {
        r_texture_set(L.render_objects[i].tex, u_image_layer(canvas.RO.image, i));

        // set pose
        L.render_objects[i].rect.pose = canvas.RO.pose;

        L.render_objects[i].rect.color = canvas.ro_color;
    }

    L.grid.rect.pose = canvas.RO.pose;
    L.bg.rect.pose = canvas.RO.pose;
}

void canvas_render(const mat4 *canvascam_mat) {
    ro_single_render(&L.bg, canvascam_mat);

    if (canvas.blend_layers) {
        for (int i = 0; i < canvas.current_layer; i++) {
            float alpha = (i + 1.0) / (canvas.current_layer + 1.0);
            L.render_objects[i].rect.color.a = alpha * canvas.alpha;
            ro_single_render(&L.render_objects[i], canvascam_mat);
        }
    }

    L.render_objects[canvas.current_layer].rect.color.a = 1.0;
    ro_single_render(&L.render_objects[canvas.current_layer], canvascam_mat);

    if (canvas.show_grid)
        ro_single_render(&L.grid, canvascam_mat);

}

void canvas_set_image(uImage image_sink, bool save) {
    if (!u_image_valid(image_sink)) {
        s_log_warn("invalid img");
        return;
    }
    if (image_sink.layers > CANVAS_MAX_LAYERS) {
        s_log_warn("to much layers!");
        return;
    }
    s_log("set_image");

    u_image_kill(&canvas.RO.image);
    canvas.RO.image = image_sink;

    u_image_kill(&L.prev_image);
    L.prev_image = u_image_new_clone(image_sink);

    if (save)
        canvas_save();

    update_render_objects();
}

void canvas_set_pattern_size(int cols, int rows) {
    cols = isca_clamp(cols, 1, canvas.RO.image.cols);
    rows = isca_clamp(rows, 1, canvas.RO.image.rows);
    canvas.RO.pattern_cols = cols;
    canvas.RO.pattern_rows = rows;
    update_render_objects();
    if (canvas.auto_save_config)
        canvas_save_config();
}

void canvas_save() {
    s_log("save");
    if (u_image_equals(canvas.RO.image, L.prev_image)) {
        s_log("failed, not changed");
        return;
    }

    u_image_copy(L.prev_image, canvas.RO.image);

    L.save_idx++;
    L.save_idx %= CANVAS_MAX_SAVES;
    L.save_idx_max = L.save_idx;
    if (L.save_idx == L.save_idx_min) {
        L.save_idx_min++;
        L.save_idx_min %= CANVAS_MAX_SAVES;
    }

    save_image();

    if (canvas.auto_save_config)
        canvas_save_config();
}

void canvas_reload() {
    u_image_copy(canvas.RO.image, L.prev_image);
}

void canvas_undo() {
    s_log("undo");
    if (L.save_idx == L.save_idx_min) {
        s_log("failed, on min idx");
        return;
    }

    L.save_idx--;
    if (L.save_idx < 0)
        L.save_idx = CANVAS_MAX_SAVES - 1;

    load_image();

    if (canvas.auto_save_config)
        canvas_save_config();
}

void canvas_redo() {
    s_log("redo");
    if (L.save_idx == L.save_idx_max) {
        s_log("failed, on max idx");
        return;
    }

    L.save_idx++;
    L.save_idx %= CANVAS_MAX_SAVES;

    load_image();

    if (canvas.auto_save_config)
        canvas_save_config();
}

bool canvas_undo_available() {
    return L.save_idx != L.save_idx_min;
}

bool canvas_redo_available() {
    return L.save_idx != L.save_idx_max;
}


void canvas_set_tab_id(int id) {
    s_assume(id>=0 && id<canvas.RO.max_tabs, "invalid tab id");
    
    canvas.RO.tab_id = id;
    load_image();
}

uImage canvas_get_tab(int id) {
    // todo
    return u_image_new_invalid();
}

void canvas_save_config() {
    s_log("save");

    uJson *config = u_json_new_file(
            e_io_savestate_file_path("config.json"));

    uJson *member = u_json_append_object(config, "canvas");

    u_json_append_int(member, "pattern_cols", canvas.RO.pattern_cols);
    u_json_append_int(member, "pattern_rows", canvas.RO.pattern_rows);
    u_json_append_int(member, "save_idx", L.save_idx);
    u_json_append_int(member, "save_idx_min", L.save_idx_min);
    u_json_append_int(member, "save_idx_max", L.save_idx_max);
    u_json_append_int(member, "tab_id", canvas.RO.tab_id);

    uJson *save_layers = u_json_append_array(member, "save_layers");
    for (int i = 0; i < CANVAS_MAX_SAVES; i++) {
        u_json_append_int(save_layers, NULL, L.save_layers[i]);
    }

    u_json_save_file(config,
                     e_io_savestate_file_path("config.json"));
    e_io_savestate_save();

    u_json_kill(&config);
}

void canvas_load_config() {
    s_log("load");

    uJson *config = u_json_new_file(
            e_io_savestate_file_path("config.json"));

    uJson *member = u_json_get_object(config, "canvas");

    int pattern_cols, pattern_rows;
    if (u_json_get_object_int(member, "pattern_cols", &pattern_cols)
        && u_json_get_object_int(member, "pattern_rows", &pattern_rows)) {
        canvas.RO.pattern_cols = pattern_cols;
        canvas.RO.pattern_rows = pattern_rows;
    }

    int tmp_layers[CANVAS_MAX_SAVES];
    int tmp_layers_size = 0;

    uJson *save_layers = u_json_get_object(member, "save_layers");
    if (save_layers) {
        for (int i = 0; i < u_json_get_size(save_layers); i++) {
            int layers;
            if (u_json_get_id_int(save_layers, i, &layers)) {
                tmp_layers[tmp_layers_size++] = layers;
            } else {
                tmp_layers_size = 0;
                break;
            }
        }
    }

    int save_idx, save_idx_min, save_idx_max;
    int tab_id;
    if (u_json_get_object_int(member, "save_idx", &save_idx)
        && u_json_get_object_int(member, "save_idx_min", &save_idx_min)
        && u_json_get_object_int(member, "save_idx_max", &save_idx_max)
        && u_json_get_object_int(member, "tab_id", &tab_id)
        && tmp_layers_size > 0) {
        L.save_idx = save_idx;
        L.save_idx_min = save_idx_min;
        L.save_idx_max = save_idx_max;
        canvas.RO.tab_id = tab_id;
        for (int i = 0; i < tmp_layers_size; i++)
            L.save_layers[i] = tmp_layers[i];
        load_image();
    } else {
        s_log("failed, saving the empty image as index 0");
        save_image();
    }

    update_render_objects();

    u_json_kill(&config);
}
