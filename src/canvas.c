#include "r/r.h"
#include "e/io.h"
#include "u/pose.h"
#include "u/image.h"
#include "u/json.h"
#include "io.h"
#include "m/sca/int.h"
#include "m/mat/float.h"

#include "canvas.h"


#define DEFAULT_WIDTH 32
#define DEFAULT_HEIGHT 32
#define DEFAULT_FRAME_TIME 0.25

struct Canvas_Globals canvas;

//
// private
//

static struct {
    uImage prev_image;
    RoSingle ro;

    RoSingle bg;
    RoSingle grid;

    struct {
        int current_layer;
        int current_frame;
        int save_idx;
        int save_idx_max;
        int save_idx_min;
    } tab_saves[CANVAS_MAX_TABS];

} L;

_Static_assert(CANVAS_MAX_SAVES <= 999, "see save / load image");



static void save_image() {
    char file_png[128];
    char file_json[128];
    snprintf(file_png, sizeof file_png, "image_%02i_%03i.png", 
            canvas.RO.tab_id, 
            L.tab_saves[canvas.RO.tab_id].save_idx);
    snprintf(file_json, sizeof file_json, "image_%02i_%03i.json", 
            canvas.RO.tab_id, 
            L.tab_saves[canvas.RO.tab_id].save_idx);
    
    u_image_save_file(canvas.RO.image,
            e_io_savestate_file_path(file_png));

    uJson *state = u_json_new_file(e_io_savestate_file_path(file_json));
    u_json_append_int(state, "layer", canvas.RO.sprite.rows);
    u_json_append_int(state, "frames", canvas.RO.sprite.cols);
    
    uJson *frame_times = u_json_append_array(state, "frame_times");
    for(int i=0; i<canvas.RO.sprite.cols; i++) {
        u_json_append_float(frame_times, NULL, canvas.frame_times[i]);
    }
    
    // saves same space in the config file
    struct uJson_Options options = {0};
    options.array_single_line = true;
    
    u_json_save_file(state,
            e_io_savestate_file_path(file_json),
            &options);
    e_io_savestate_save();

    u_json_kill(&state);
}


static uSprite load_image_file(int tab_id, int save_idx, bool update_curennt_frame_times) {
    if(tab_id<0 
            || tab_id>=CANVAS_MAX_TABS
            || save_idx<0
            || save_idx>=CANVAS_MAX_SAVES)
        return u_sprite_new_zeros(DEFAULT_WIDTH, DEFAULT_HEIGHT, 1, 1);

    char file_png[128];
    char file_json[128];
    snprintf(file_png, sizeof file_png, "image_%02i_%03i.png", 
            tab_id, save_idx);
    snprintf(file_json, sizeof file_json, "image_%02i_%03i.json", 
            tab_id, save_idx);
    

    uJson *state = u_json_new_file(e_io_savestate_file_path(file_json));
    int layers, frames;
    if(!u_json_get_object_int(state, "layer", &layers)
        || !u_json_get_object_int(state, "frames", &frames)) {
        s_log_warn("failed to load img info");
        layers = frames = 1;
    }
    
    if(update_curennt_frame_times) {
        uJson *frame_times = u_json_get_object(state, "frame_times");
        bool ok = u_json_get_size(frame_times) >= frames;
        for(int i=0; ok && i<frames; i++) {
            ok &= u_json_get_id_float(frame_times, i, &canvas.frame_times[i]) != NULL;
        }
        
        if(!ok) {
            s_log_warn("failed to grep frame times");
            for(int i=0; i<CANVAS_MAX_FRAMES; i++) {
                canvas.frame_times[i] = DEFAULT_FRAME_TIME;
            }
        }
    }
    
    u_json_kill(&state);
    
    uImage image = u_image_new_file(
            frames * layers,
            e_io_savestate_file_path(file_png));
            
    uSprite sprite = {image, frames, layers};
    
    if(!u_sprite_valid(sprite)) {
        return u_sprite_new_zeros(DEFAULT_WIDTH, DEFAULT_HEIGHT, 1, 1);
    }
    
    return sprite;
}

static void load_image() {
    uSprite sprite = load_image_file(
            canvas.RO.tab_id, 
            L.tab_saves[canvas.RO.tab_id].save_idx,
            true);
    canvas_set_sprite(sprite, false);
}

// updates the ro tex and sizes
static void update_render_objects() {
    uSprite s = canvas.RO.sprite;
    rTexture tex = r_texture_new_sprite_buffer(s.img.cols, s.img.rows, s.cols, s.rows, s.img.data);
    
    ro_single_set_texture(&L.ro, tex);
    canvas.RO.tex = tex;

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
    canvas.blend_mode = CANVAS_BLEND_LAYER_ONION;
    
    for(int i=0; i<CANVAS_MAX_FRAMES; i++) {
        canvas.frame_times[i] = DEFAULT_FRAME_TIME;
    }

    canvas.RO.pose = mat4_eye();

    canvas.RO.pattern_cols = 8;
    canvas.RO.pattern_rows = 8;

    L.ro = ro_single_new(r_texture_new_invalid());
        
    rTexture grid_tex = r_texture_new_file(1, 1, "res/canvas_grid.png");
    r_texture_wrap_repeat(grid_tex);
    L.grid = ro_single_new(grid_tex);

    uColor_s buf[4];
    buf[0] = buf[3] = u_color_from_hex("#999999");
    buf[1] = buf[2] = u_color_from_hex("#777777");
    rTexture bg_tex = r_texture_new(2, 2, 1, 1, buf);
    r_texture_wrap_repeat(bg_tex);
    L.bg = ro_single_new(bg_tex);

    uSprite sprite = u_sprite_new_zeros(DEFAULT_WIDTH, DEFAULT_HEIGHT, 1, 1);
    canvas_set_sprite(sprite, false);
}

void canvas_update(float dtime) {

    canvas.RO.pose = u_pose_new_aa(0, 0, canvas.RO.image.cols, canvas.RO.image.rows);

    r_texture_set_sprite_buffer(L.ro.tex, canvas.RO.sprite.img.data);

    // set pose
    L.ro.rect.pose = canvas.RO.pose;

    L.ro.rect.color = canvas.ro_color;

    L.grid.rect.pose = canvas.RO.pose;
    L.bg.rect.pose = canvas.RO.pose;
}

void canvas_render(const mat4 *canvascam_mat) {
    ro_single_render(&L.bg, canvascam_mat);
    
    switch(canvas.blend_mode) {
    case CANVAS_BLEND_NONE:
        L.ro.rect.color.a = 1;
        L.ro.rect.sprite.x = canvas.RO.current_frame;
        L.ro.rect.sprite.y = canvas.RO.current_layer;
        ro_single_render(&L.ro, canvascam_mat);
        break;
    case CANVAS_BLEND_FRAMES_ONION:
        L.ro.rect.sprite.y = canvas.RO.current_layer;
        for(int i=0; i<=canvas.RO.current_frame; i++) {
            float alpha = 0.05;
            if(i==canvas.RO.current_frame-1)
                alpha = 0.33;
            else if(i==canvas.RO.current_frame)
                alpha = 1;
            L.ro.rect.color.a = alpha;
            L.ro.rect.sprite.x = i;
            ro_single_render(&L.ro, canvascam_mat);
        }
        break;
    case CANVAS_BLEND_FRAMES_FULL:
        L.ro.rect.color.a = 1;
        L.ro.rect.sprite.y = canvas.RO.current_layer;
        for(int i=0; i<=canvas.RO.current_frame; i++) {
            L.ro.rect.sprite.x = i;
            ro_single_render(&L.ro, canvascam_mat);
        }
        break;
    case CANVAS_BLEND_LAYER_ONION:
        L.ro.rect.sprite.x = canvas.RO.current_frame;
        for(int i=0; i<=canvas.RO.current_layer; i++) {
            float alpha = 0.05;
            if(i==canvas.RO.current_layer-1)
                alpha = 0.33;
            else if(i==canvas.RO.current_layer)
                alpha = 1;
            L.ro.rect.color.a = alpha;
            L.ro.rect.sprite.y = i;
            ro_single_render(&L.ro, canvascam_mat);
        }
        break;
    case CANVAS_BLEND_LAYER_FULL:
        L.ro.rect.color.a = 1;
        L.ro.rect.sprite.x = canvas.RO.current_frame;
        for(int i=0; i<=canvas.RO.current_layer; i++) {
            L.ro.rect.sprite.y = i;
            ro_single_render(&L.ro, canvascam_mat);
        }
        break;
    default:
        s_assume(false, "invalid blend mode");
    }

    
    if (canvas.show_grid)
        ro_single_render(&L.grid, canvascam_mat);

}

void canvas_set_frame(int sprite_col) {
    s_log("frame: %i/%i", sprite_col, canvas.RO.sprite.cols);
    s_assume(sprite_col>=0&&sprite_col<canvas.RO.sprite.cols, "invalid frame");
    canvas.RO.current_frame = sprite_col;
    canvas.RO.current_image_layer = u_sprite_pos_to_layer(canvas.RO.sprite.cols, 
            canvas.RO.current_frame,
            canvas.RO.current_layer);
}

void canvas_set_layer(int sprite_row) {
    s_log("layer: %i/%i", sprite_row, canvas.RO.sprite.rows);
    s_assume(sprite_row>=0&&sprite_row<canvas.RO.sprite.rows, "invalid layer");
    canvas.RO.current_layer = sprite_row;
    canvas.RO.current_image_layer = u_sprite_pos_to_layer(canvas.RO.sprite.cols, 
            canvas.RO.current_frame,
            canvas.RO.current_layer);
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
    s_log("set_image");

    u_sprite_kill(&canvas.RO.sprite);
    canvas.RO.sprite = image_sink;
    canvas.RO.image = canvas.RO.sprite.img;
    
    canvas.RO.current_frame = s_min(canvas.RO.current_frame, canvas.RO.sprite.cols-1);
    canvas.RO.current_layer = s_min(canvas.RO.current_layer, canvas.RO.sprite.rows-1);
    canvas.RO.current_image_layer = u_sprite_pos_to_layer(canvas.RO.sprite.cols, 
            canvas.RO.current_frame, 
            canvas.RO.current_layer);

    u_image_kill(&L.prev_image);
    L.prev_image = u_image_new_zeros(image_sink.img.cols, image_sink.img.rows, image_sink.cols * image_sink.rows);
   
    if (save) {
        canvas_save();
    } else {
        u_image_copy(L.prev_image, image_sink.img);
    }

    update_render_objects();
}

void canvas_set_pattern_size(int cols, int rows) {
    cols = isca_clamp(cols, 1, canvas.RO.image.cols);
    rows = isca_clamp(rows, 1, canvas.RO.image.rows);
    canvas.RO.pattern_cols = cols;
    canvas.RO.pattern_rows = rows;
    update_render_objects();
    canvas_save_config();
}

void canvas_save() {
    s_log("save");
    if (u_image_equals(canvas.RO.image, L.prev_image)) {
        s_log("failed, not changed");
        return;
    }

    u_image_copy(L.prev_image, canvas.RO.image);

    int t = canvas.RO.tab_id;
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
    int t = canvas.RO.tab_id;
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
    int t = canvas.RO.tab_id;
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
    int t = canvas.RO.tab_id;
    return L.tab_saves[t].save_idx != L.tab_saves[t].save_idx_min;
}

bool canvas_redo_available() {
    int t = canvas.RO.tab_id;
    return L.tab_saves[t].save_idx != L.tab_saves[t].save_idx_max;
}


void canvas_set_tab_id(int id) {
    s_assume(id>=0 && id<CANVAS_MAX_TABS, "invalid tab id");
    L.tab_saves[canvas.RO.tab_id].current_layer = canvas.RO.current_layer;
    L.tab_saves[canvas.RO.tab_id].current_frame = canvas.RO.current_frame;
    canvas_save_config();
    canvas.RO.tab_id = id;
    load_image();
    u_image_kill(&L.prev_image);
    L.prev_image = u_image_new_clone(canvas.RO.image);
    
    canvas_set_frame(L.tab_saves[id].current_frame);
    canvas_set_layer(L.tab_saves[id].current_layer);
}

uSprite canvas_get_tab(int id) {
    s_log("id=%i", id);
    s_assume(id>=0 && id<CANVAS_MAX_TABS, "invalid tab id");
    return load_image_file(id, L.tab_saves[id].save_idx, false);
}

void canvas_save_config() {
    s_log("save");
    
    save_image();

    uJson *config = u_json_new_file(io_config_file());

    uJson *member = u_json_append_object(config, "canvas");

    u_json_append_int(member, "pattern_cols", canvas.RO.pattern_cols);
    u_json_append_int(member, "pattern_rows", canvas.RO.pattern_rows);
    u_json_append_int(member, "tab_id", canvas.RO.tab_id);
    
    
    L.tab_saves[canvas.RO.tab_id].current_layer = canvas.RO.current_layer;
    L.tab_saves[canvas.RO.tab_id].current_frame = canvas.RO.current_frame;
    
    for(int t=0; t<CANVAS_MAX_TABS; t++) {
        char name[16];
        snprintf(name, sizeof name, "tab_%02i", t);
        
        uJson *tab = u_json_append_object(member, name);
        
        u_json_append_int(tab, "current_layer", L.tab_saves[t].current_layer);
        u_json_append_int(tab, "current_frame", L.tab_saves[t].current_frame);
        u_json_append_int(tab, "save_idx", L.tab_saves[t].save_idx);
        u_json_append_int(tab, "save_idx_max", L.tab_saves[t].save_idx_max);
        u_json_append_int(tab, "save_idx_min", L.tab_saves[t].save_idx_min);
    }

    u_json_save_file(config,io_config_file(), NULL);
    e_io_savestate_save();

    u_json_kill(&config);
}

void canvas_load_config() {
    s_log("load");

    uJson *config = u_json_new_file(io_config_file());

    uJson *member = u_json_get_object(config, "canvas");

    int pattern_cols, pattern_rows;
    if (u_json_get_object_int(member, "pattern_cols", &pattern_cols)
        && u_json_get_object_int(member, "pattern_rows", &pattern_rows)) {
        canvas.RO.pattern_cols = pattern_cols;
        canvas.RO.pattern_rows = pattern_rows;
    }
    
    for(int t=0; t<CANVAS_MAX_TABS; t++) {
        char name[16];
        snprintf(name, sizeof name, "tab_%02i", t);
        
        uJson *tab = u_json_get_object(member, name);
        bool ok = true;
        ok &= u_json_get_object_int(tab, "current_layer", &L.tab_saves[t].current_layer) != NULL;
        ok &= u_json_get_object_int(tab, "current_frame", &L.tab_saves[t].current_frame) != NULL;
        ok &= u_json_get_object_int(tab, "save_idx", &L.tab_saves[t].save_idx) != NULL;
        ok &= u_json_get_object_int(tab, "save_idx_max", &L.tab_saves[t].save_idx_max) != NULL;
        ok &= u_json_get_object_int(tab, "save_idx_min", &L.tab_saves[t].save_idx_min) != NULL;
        
        if(!ok) {
            s_log_debug("failed to load tab %i info, resetting to 0", t);
            memset(&L.tab_saves[t], 0, sizeof L.tab_saves[t]);
        }
    }


    int tab_id;
    if ( u_json_get_object_int(member, "tab_id", &tab_id)) {
        canvas.RO.tab_id = tab_id;
        load_image();
        canvas_set_layer(canvas.RO.sprite.rows-1);
    } else {
        s_log("failed, saving the empty image as index 0");
        save_image();
    }

    update_render_objects();

    u_json_kill(&config);
}
