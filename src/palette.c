#include <float.h>  // FLT_MAX
#include <assert.h>
#include "e/input.h"
#include "r/r.h"
#include "u/pose.h"
#include "u/json.h"
#include "e/io.h"
#include "rhc/alloc.h"
#include "brush.h"
#include "palette.h"

#define COLOR_DROP_SIZE 16.0f
#define MAX_ROWS 10


//
// private
//



static int palette_cols(const Palette *self) {
    assert(camera_width(self->camera_ref) > 0 && camera_height(self->camera_ref) > 0 && "startup bug?");
    if (camera_is_portrait_mode(self->camera_ref))
        return (int) floorf(camera_width(self->camera_ref) / COLOR_DROP_SIZE);
    return (int) floorf(camera_height(self->camera_ref) / COLOR_DROP_SIZE);
}

static bool pos_in_palette(const Palette *self, vec2 pos) {
    int cols = palette_cols(self);
    int rows = 1 + self->RO.palette_size / cols;
    int size = rows * COLOR_DROP_SIZE;
    if (camera_is_portrait_mode(self->camera_ref)) {
        return pos.y <= self->camera_ref->RO.bottom + size;
    }
    return pos.x >= self->camera_ref->RO.right - size;
}


static mat4 setup_palette_color_pose(const Palette *self, int r, int c) {
    mat4 pose = mat4_eye();
    u_pose_set_size(&pose, COLOR_DROP_SIZE, COLOR_DROP_SIZE);
    if (camera_is_portrait_mode(self->camera_ref)) {
        u_pose_set_xy(&pose, self->camera_ref->RO.left + COLOR_DROP_SIZE / 2 + c * COLOR_DROP_SIZE,
                      self->camera_ref->RO.bottom + COLOR_DROP_SIZE / 2 + r * COLOR_DROP_SIZE);
    } else {
        u_pose_set_xy(&pose, self->camera_ref->RO.right - COLOR_DROP_SIZE / 2 - r * COLOR_DROP_SIZE,
                      self->camera_ref->RO.bottom + COLOR_DROP_SIZE / 2 + c * COLOR_DROP_SIZE);
        u_pose_set_angle(&pose, M_PI_2);
    }
    return pose;
}


//
// public
//

Palette *palette_new(const Camera_s *camera, Brush *brush) {
    Palette *self = rhc_calloc(sizeof *self);

    self->camera_ref = camera;
    self->brush_ref = brush;
    
    self->ro_color = R_COLOR_WHITE;
    self->include_transparent_at_set_colors = true;

    self->L.palette_ro = ro_batch_new(PALETTE_MAX, r_texture_new_file(1, 1, "res/color_drop.png"));

    self->L.background_ro = ro_batch_new(PALETTE_MAX + MAX_ROWS,
                                         r_texture_new_file(2, 2, "res/palette_background.png"));

    self->L.select_ro = ro_single_new(r_texture_new_file(1, 1, "res/palette_select.png"));

    // default palette:
    {
        uColor_s palette[4] = {
                {0,   0,   0,   0},
                {0,   0,   0,   255},
                {128, 128, 128, 255},
                {255, 255, 255, 255}
        };
        palette_set_colors(self, palette, 4, NULL);
    }

    return self;
}


void palette_update(Palette *self, float dtime) {
    int cols = palette_cols(self);
    int last_row = (self->RO.palette_size - 1) / cols;
    for (int i = 0; i < PALETTE_MAX; i++) {
        int r = i / cols;
        int c = i % cols;

        // pose
        mat4 pose = mat4_eye();
        if (r <= last_row)
            pose = setup_palette_color_pose(self, r, c);
        else
            u_pose_set(&pose, FLT_MAX, FLT_MAX, 0, 0, 0);
        self->L.palette_ro.rects[i].pose = pose;
        self->L.background_ro.rects[i].pose = pose;

        // color
        vec4 col;
        if (i < self->RO.palette_size)
            col = u_color_to_vec4(self->RO.palette[i]);
        else
            col = R_COLOR_TRANSPARENT;

        self->L.palette_ro.rects[i].color = vec4_scale_vec(col, self->ro_color);


        // background sprite
        {
            float u = i < self->RO.palette_size ? 0 : 1;
            float v = r < last_row ? 1 : 0;
            self->L.background_ro.rects[i].sprite = (vec2) {{u, v}};
        }
    }

    // background continuation
    for (int r = 0; r < MAX_ROWS; r++) {
        int idx = self->L.background_ro.num - r - 1;
        // pose
        mat4 pose = mat4_eye();
        if (r <= last_row)
            pose = setup_palette_color_pose(self, r, cols);
        else
            u_pose_set(&pose, FLT_MAX, FLT_MAX, 0, 0, 0);
        self->L.background_ro.rects[idx].pose = pose;

        // background uv
        {
            float u = 1;
            float v = r < last_row ? 1 : 0;
            self->L.background_ro.rects[idx].sprite = (vec2) {{u, v}};
        }
    }

    self->L.select_ro.rect.pose = self->L.palette_ro.rects[self->L.last_selected].pose;
}

void palette_render(Palette *self, const mat4 *camera_mat) {
    ro_batch_render(&self->L.background_ro, camera_mat, true);
    ro_batch_render(&self->L.palette_ro, camera_mat, true);
    ro_single_render(&self->L.select_ro, camera_mat);
}


bool palette_pointer_event(Palette *self, ePointer_s pointer) {
    if (!pos_in_palette(self, pointer.pos.xy))
        return false;

    if (pointer.action != E_POINTER_DOWN)
        return true;

    for (int i = 0; i < self->RO.palette_size; i++) {
        if (u_pose_contains(self->L.palette_ro.rects[i].pose, pointer.pos)) {
            palette_set_color(self, i);
            return true;
        }
    }

    return true;
}

float palette_get_hud_size(const Palette *self) {
    int cols = palette_cols(self);
    int rows = 1 + self->RO.palette_size / cols;
    return rows * COLOR_DROP_SIZE;
}

int palette_get_color(const Palette *self) {
    return self->L.last_selected;
}

void palette_set_color(Palette *self, int index) {
    if(index<0 || index>=self->RO.palette_size) {
        log_error("palette: set_color failed, invalid index (%i/%i)", 
                index, self->RO.palette_size);
        return;
    }
    self->brush_ref->current_color = self->RO.palette[index];
    self->L.select_ro.rect.pose = self->L.palette_ro.rects[index].pose;
    self->L.last_selected = index;
}

void palette_set_colors(Palette *self, const uColor_s *palette, int size, const char *name_ref) {
    log_info("palette: set_colors: %s", name_ref);
    assume(size>0, "palette set_colors failed");
    
    self->RO.palette_size = 0;
    
    if(self->include_transparent_at_set_colors) {
        self->RO.palette[self->RO.palette_size++] = U_COLOR_TRANSPARENT;
    }
    
    // copy unique colors
    for(int i=0; i<size && self->RO.palette_size<PALETTE_MAX; i++) {
        bool found = false;
        for(int j=0; j<self->RO.palette_size; j++) {
            if(u_color_equals(palette[i], self->RO.palette[j])) {
                found = true;
                break;
            }
        }
        if(!found) {
            self->RO.palette[self->RO.palette_size++] = palette[i];
        }
    }
    
    palette_set_color(self, 0);
    self->RO.palette_name = name_ref? name_ref : "custom palette";
}


void palette_set_palette(Palette *self, uImage palette, const char *name_ref) {
    if(!u_image_valid(palette)) {
        log_error("palette: set_palette failed, invalid");
        return;
    } 
    
    int size = palette.cols * palette.rows;
    
    if(size > PALETTE_MAX || palette.layers != 1) {
        log_error("palette: set_palette failed, to large, or multiple layers (%i/%i)", 
                size, PALETTE_MAX);
        return;
    }
    
    palette_set_colors(self, palette.data, size, name_ref);
}

void palette_load_palette(Palette *self, int id) {
    if(id<0 || id>=self->RO.max_palettes) {
        log_error("palette: load_palette failed, invalid id: %i/%i", id, self->RO.max_palettes);
        return;
    }

    log_info("palette: load_palette[%i] = %s", id, self->L.palette_files[id]);
            
    // mount and load savestate (needed for web)
    e_io_savestate_load();
    
    uImage palette = u_image_new_file(1,
            e_io_savestate_file_path(self->L.palette_files[id]).s
            );
    
    self->RO.palette_id = id;
    palette_set_palette(self, palette,
            self->L.palette_files[id]);
            
    u_image_kill(&palette);        
    
    palette_save_config(self);
}

void palette_append_file(Palette *self, uImage palette, const char *name) {
    log_info("palette: append_file: %s", name);
    // mount and load savestate (needed for web)
    e_io_savestate_load();
    
    u_image_save_file(palette, e_io_savestate_file_path(name).s);
    
    int idx = -1;
    for(int i=0; i<self->RO.max_palettes; i++) {
        if(strcmp(name, self->L.palette_files[i]) == 0) {
            idx = i;
            break;
        }
    }
    
    if(idx==-1) {
        size_t len = strlen(name) + 1;
        char *clone = rhc_malloc(len);
        memcpy(clone, name, len);
        self->L.palette_files = rhc_realloc(self->L.palette_files, sizeof *self->L.palette_files * ++self->RO.max_palettes);
        idx = self->RO.max_palettes-1;
        self->L.palette_files[idx] = clone;
    }
    
    // save the savestate files (needed for web)
    e_io_savestate_save();
    
    palette_set_palette(self, palette, self->L.palette_files[idx]);
    self->RO.palette_id = idx;
    palette_save_config(self);
}

void palette_reset_palette_files(Palette *self) {
    log_info("palette: reset_palette_files");
    uImage *palettes = palette_defaults_new();
    
    // mount and load savestate (needed for web)
    e_io_savestate_load();
    
    for(int i=0; i<self->RO.max_palettes; i++)
        rhc_free(self->L.palette_files[i]);
    
    self->L.palette_files = rhc_realloc(self->L.palette_files, sizeof *self->L.palette_files * 16);
    
    int i;
    for(i=0; u_image_valid(palettes[i]); i++) {
        assume(i<16, "change max default palettes");
        char *name = palette_defaults_name_on_heap(i);
        u_image_save_file(palettes[i], e_io_savestate_file_path(name).s);
        
        self->L.palette_files[i] = name;
    }
    self->RO.max_palettes = i;
    
    self->RO.palette_id = 0;
    
    // save the savestate files (needed for web)
    e_io_savestate_save();
    
    palette_set_palette(self, palettes[0], self->L.palette_files[0]);
    
    palette_defaults_kill(&palettes);
    
    palette_save_config(self);
}

void palette_save_config(const Palette *self) {
    log_info("palette: save_config");
    
    String config_string;
    uJson *config;
    
    config_string = e_io_savestate_read("config.json", true);
    config = u_json_new_str(config_string.str);
    string_kill(&config_string);
    
    uJson *palette = u_json_append_object(config, "palette");
    uJson *palette_files = u_json_append_array(palette, "palette_files");
    for(int i=0; i<self->RO.max_palettes; i++) {
        u_json_append_string(palette_files, NULL, self->L.palette_files[i]);
    }
    
    u_json_append_int(palette, "palette_id", self->RO.palette_id);
    
    config_string = u_json_to_string(config);
    e_io_savestate_write("config.json", config_string.str, true);
    string_kill(&config_string);
    
    u_json_kill(&config);
}

void palette_load_config(Palette *self) {
    log_info("palette: load_config");
    
    uJson *config;
    bool reset = false;
    
    String config_string = e_io_savestate_read("config.json", true);
    config = u_json_new_str(config_string.str);
    string_kill(&config_string);
    
    uJson *palette = u_json_get_object(config, "palette");
    uJson *palette_files = u_json_get_object(palette, "palette_files");
    
    int palettes_size = u_json_get_size(palette_files);
    
    if(palettes_size <= 0) {
        reset = true;
        goto CLEAN_UP;
    }
    
    for(int i=0; i<self->RO.max_palettes; i++)
        rhc_free(self->L.palette_files[i]);
    
    self->L.palette_files = rhc_realloc(self->L.palette_files, sizeof *self->L.palette_files * palettes_size);
    
    self->RO.max_palettes = palettes_size;
    
    for(int i=0; i<palettes_size; i++) {
        const char *file = u_json_get_id_string(palette_files, i);
                
        if(!file) {
            reset = true;
            goto CLEAN_UP;
        }
        
        size_t len = strlen(file) + 1;
        char *clone = rhc_malloc(len);
        memcpy(clone, file, len);
        self->L.palette_files[i] = clone;
    }
    
    int id;
    if(!u_json_get_object_int(palette, "palette_id", &id)) {
        reset = true;
        goto CLEAN_UP;
    }
    
    if(id<0 || id>=self->RO.max_palettes) {
        log_warn("palette: load_config failed, invalid id, setting to 0");
        id = 0;
    }
    
    palette_load_palette(self, id);
    
    CLEAN_UP:
    if(reset) {
        palette_reset_palette_files(self);
    }   
    u_json_kill(&config);
}
