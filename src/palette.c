#include <float.h>  // FLT_MAX
#include <assert.h>
#include "e/input.h"
#include "r/r.h"
#include "u/pose.h"
#include "u/json.h"
#include "e/io.h"
#include "rhc/alloc.h"
#include "mathc/float.h"
#include "palette.h"

#define COLOR_DROP_SIZE 16.0f
#define MAX_ROWS 10

#define SWIPE_DISTANCE 50

#define INFO_STATIC_TIME 0.5
#define INFO_TIME 1.5

//
// private
//



static int palette_cols(const Palette *self) {
    assert(camera_width(self->camera_ref) > 0 && camera_height(self->camera_ref) > 0 && "startup bug?");
    if (camera_is_portrait_mode(self->camera_ref))
        return (int) floorf(camera_width(self->camera_ref) / COLOR_DROP_SIZE);
    return (int) floorf(camera_height(self->camera_ref) / COLOR_DROP_SIZE);
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


// returns the swipe move difference in %
static float swipe_diff(const Palette *self, ePointer_s pointer) {
    float diff;
    if(camera_is_portrait_mode(self->camera_ref)) {
        diff = pointer.pos.x - self->L.swipe.start.x;
    } else {
        diff = pointer.pos.y - self->L.swipe.start.y;
    }
    return diff / SWIPE_DISTANCE;
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
    self->auto_save_config = true;

    self->L.current_pressed = -1;

    self->L.palette_ro = ro_batch_new(PALETTE_MAX, r_texture_new_file(1, 1, "res/color_drop.png"));

    self->L.background_ro = ro_batch_new(PALETTE_MAX + MAX_ROWS,
                                         r_texture_new_file(2, 2, "res/palette_background.png"));

    self->L.select_ro = ro_single_new(r_texture_new_file(1, 1, "res/palette_select.png"));
    
    
    self->L.info.bg = ro_single_new(r_texture_new_file(1, 1, "res/palette_info_bg.png"));
    self->L.info.text = ro_text_new_font55(20);
    
    self->L.swipe.arrows = ro_batch_new(2, r_texture_new_file(1, 1, "res/palette_arrow.png"));
    

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

    if(self->L.custom_select_active)
        self->L.select_ro.rect.pose = self->L.custom_select_pose;
    else
        self->L.select_ro.rect.pose = self->L.palette_ro.rects[self->L.last_selected].pose;
    
    // info
    if(self->L.info.time>0) {
        self->L.info.time -= dtime;
    
        float pos = 4;
        if(self->L.info.time<INFO_STATIC_TIME) {
            pos = sca_mix(-4, 4, self->L.info.time/INFO_STATIC_TIME);
        }
        
        pos += palette_get_hud_size(self);
        
        if(camera_is_portrait_mode(self->camera_ref)) {
            pos += self->camera_ref->RO.bottom;
            
            self->L.info.bg.rect.pose = u_pose_new(
                    0, pos, 128, 8);
                    
            pos += 2;
            self->L.info.text.pose = u_pose_new(
                    self->L.info.x_offset, pos, 
                    1, 1);
                    
        } else {
            pos = self->camera_ref->RO.right - pos;
            
            self->L.info.bg.rect.pose = u_pose_new_angle(
                    pos, 0, 128, 8, M_PI_2);
            
            pos -= 2;
            self->L.info.text.pose = u_pose_new_angle(
                    pos, self->L.info.x_offset, 
                    1, 1, M_PI_2);
        }
    }
    
}

void palette_render(Palette *self, const mat4 *cam_mat) {
    if(self->L.info.time>0) {
        ro_single_render(&self->L.info.bg, cam_mat);
        ro_text_render(&self->L.info.text, cam_mat);
    }
    
    ro_batch_render(&self->L.background_ro, cam_mat, true);
    ro_batch_render(&self->L.palette_ro, cam_mat, true);
    ro_single_render(&self->L.select_ro, cam_mat);
    
    if(self->L.swipe.swiping)
        ro_batch_render(&self->L.swipe.arrows, cam_mat, true);
}


bool palette_pointer_event(Palette *self, ePointer_s pointer) {
    if (!palette_contains_pos(self, pointer.pos.xy)) {
        for(int i=0;i<2;i++)
            self->L.swipe.arrows.rects[i].color.a = 0;
        self->L.swipe.swiping = false;
        return false;
    }

    if (pointer.action == E_POINTER_DOWN) {
        for(int i=0;i<2;i++)
            self->L.swipe.arrows.rects[i].color.a = 0;
        self->L.swipe.start = pointer.pos.xy;
        self->L.swipe.swiping = true;
        
        for (int i = 0; i < self->RO.palette_size; i++) {
            // pose will be rotated in landscape mode (so do not use _aa_)!
            if (u_pose_contains(self->L.palette_ro.rects[i].pose, pointer.pos)) {
                self->L.current_pressed = i;
                return true;
            }
        }
        
        self->L.current_pressed = -1;
        return true;
    }
    
    if(pointer.action == E_POINTER_UP) {
        for(int i=0;i<2;i++)
            self->L.swipe.arrows.rects[i].color.a = 0;
        self->L.swipe.swiping = false;
    }
    
    if(self->L.current_pressed!=-1
            // pose will be rotated in landscape mode (so do not use _aa_)!
            && !u_pose_contains(self->L.palette_ro.rects[self->L.current_pressed].pose,
                    pointer.pos)) {
        self->L.current_pressed = -1;
    }
    
    if(self->L.current_pressed!=-1 && pointer.action == E_POINTER_UP) {
        palette_set_color(self, self->L.current_pressed);
        self->L.current_pressed = -1;
    }
    
    if(self->L.swipe.swiping && pointer.action == E_POINTER_MOVE) {
        float diff = swipe_diff(self, pointer);
        if(diff>1) {
            int id = self->RO.palette_id-1;
            if(id<0)
                id = self->RO.max_palettes-1;
            palette_load_palette(self, id);
            self->L.swipe.swiping = false;
            
        } else if(diff<=-1) {
            int id = self->RO.palette_id+1;
            id %= self->RO.max_palettes;
            palette_load_palette(self, id);
            self->L.swipe.swiping = false;
            
        }
        
        float alpha = sca_smoothstep(sca_abs(diff), 0.25, 1);
        for(int i=0;i<2;i++)
            self->L.swipe.arrows.rects[i].color.a = alpha;
        if(camera_is_portrait_mode(self->camera_ref)) {
            for(int i=0;i<2;i++) {
                self->L.swipe.arrows.rects[i].pose = u_pose_new_angle(
                (int[]){-1,1}[i] * (camera_width(self->camera_ref)/2 - 20), 
                self->camera_ref->RO.bottom + 16,
                32, 32,
                sca_sign(diff) * M_PI_2 - M_PI_2
                );
            }
        } else {
            for(int i=0;i<2;i++) {
                self->L.swipe.arrows.rects[i].pose = u_pose_new_angle(
                self->camera_ref->RO.right - 16,
                (int[]){-1,1}[i] * (camera_height(self->camera_ref)/2 - 20),
                32, 32,
                sca_sign(diff) * M_PI_2
                );
            }
        }
    }

    return true;
}

float palette_get_hud_size(const Palette *self) {
    int cols = palette_cols(self);
    int rows = 1 + (self->RO.palette_size-1) / cols;
    return rows * COLOR_DROP_SIZE;
}

mat4 palette_get_pose(const Palette *self) {
    int size = palette_get_hud_size(self);
    if (camera_is_portrait_mode(self->camera_ref)) {
        return u_pose_new(0, self->camera_ref->RO.bottom + size/2,
                camera_width(self->camera_ref),
                size);
        
    }
    return u_pose_new(self->camera_ref->RO.right -size/2, 0,
                size,
                camera_height(self->camera_ref));
}

bool palette_contains_pos(const Palette *self, vec2 pos) {
    int size = palette_get_hud_size(self);
    if (camera_is_portrait_mode(self->camera_ref)) {
        return pos.y <= self->camera_ref->RO.bottom + size;
    }
    return pos.x >= self->camera_ref->RO.right - size;
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
    self->brush_ref->secondary_as_current = false;
    self->L.select_ro.rect.pose = self->L.palette_ro.rects[index].pose;
    self->L.last_selected = index;
    self->L.custom_select_active = false;
}

void palette_set_custom_select(Palette *self, mat4 select_pose) {
    self->L.custom_select_pose = select_pose;
    self->L.custom_select_active = true;
    self->L.last_selected = -1;
}

void palette_set_info(Palette *self, const char *info) {
    if(!info) {
        // hide it immediately
        self->L.info.time = -1;
        return;
    }
    vec2 size = ro_text_set_text(&self->L.info.text, info);
    self->L.info.x_offset = (int) -sca_ceil(size.x/2);
    self->L.info.time = INFO_TIME;
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
    
    palette_set_info(self, self->RO.palette_name);
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
     
    char file[256];
    snprintf(file, sizeof file, "palette_%s", self->L.palette_files[id]);       
    
    char name[32];
    snprintf(name, sizeof name, "%s", self->L.palette_files[id]);
    
    // name to lower and without .png
    Str_s name_s = strc(name);
    name_s = str_tolower(name_s);
    name_s = str_eat_back_str(name_s, strc(".png"));
    name_s.data[name_s.size] = '\0';
    
    uImage palette = u_image_new_file(1,
            e_io_savestate_file_path(file).s
            );
    
    self->RO.palette_id = id;
    palette_set_palette(self, palette, name);
            
    u_image_kill(&palette);        
   
    if(self->auto_save_config)
        palette_save_config(self);
}

void palette_append_file(Palette *self, uImage palette, const char *name) {
    log_info("palette: append_file: %s", name);
    
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
    if(self->auto_save_config)
        palette_save_config(self);
}

void palette_reset_palette_files(Palette *self) {
    log_info("palette: reset_palette_files");
    uImage *palettes = palette_defaults_new();
    
    for(int i=0; i<self->RO.max_palettes; i++)
        rhc_free(self->L.palette_files[i]);
    
    self->L.palette_files = rhc_realloc(self->L.palette_files, sizeof *self->L.palette_files * 32);
    
    int i;
    for(i=0; u_image_valid(palettes[i]); i++) {
        assume(i<32, "change max default palettes");
        char *name = palette_defaults_name_on_heap(i);
        char file[256];
        snprintf(file, sizeof file, "palette_%s", name);
        u_image_save_file(palettes[i], e_io_savestate_file_path(file).s);
        
        self->L.palette_files[i] = name;
    }
    self->RO.max_palettes = i;
    
    self->RO.palette_id = 0;
    
    // save the savestate files (needed for web)
    e_io_savestate_save();
    
    palette_set_palette(self, palettes[0], self->L.palette_files[0]);
    
    palette_defaults_kill(&palettes);
    
    if(self->auto_save_config)
        palette_save_config(self);
}

void palette_save_config(const Palette *self) {
    log_info("palette: save_config");
    
    uJson *config = u_json_new_file(
            e_io_savestate_file_path("config.json").s);
    
    uJson *palette = u_json_append_object(config, "palette");
    uJson *palette_files = u_json_append_array(palette, "palette_files");
    for(int i=0; i<self->RO.max_palettes; i++) {
        u_json_append_string(palette_files, NULL, self->L.palette_files[i]);
    }
    
    u_json_append_int(palette, "palette_id", self->RO.palette_id);
    
    u_json_save_file(config,
                       e_io_savestate_file_path("config.json").s);
    e_io_savestate_save();
    
    u_json_kill(&config);
}

void palette_load_config(Palette *self) {
    log_info("palette: load_config");
    
    bool reset = false;
    
    uJson *config = u_json_new_file(
            e_io_savestate_file_path("config.json").s);
    
    
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
