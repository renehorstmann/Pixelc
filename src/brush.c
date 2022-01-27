#include <assert.h>
#include "e/io.h"
#include "r/texture.h"
#include "mathc/sca/int.h"
#include "brush.h"
#include "u/json.h"

//
// private
//

enum draw_kernel_mode {
    DRAW_NORMAL,
    DRAW_DITHER_A,
    DRAW_DITHER_B,
    DRAW_NUM_MODES
};

static uColor_s blend_color(uColor_s prev, uColor_s kernel, uColor_s color) {
    vec4 p = u_color_to_vec4(prev);
    vec4 k = u_color_to_vec4(kernel);
    vec4 c = u_color_to_vec4(color);
      
    // kernel * color for each channel
    vec4 kc = vec4_scale_vec(k, c);
    
    // kernel sets the resulting opacity
    vec4 b = vec4_mix(p, kc, k.a);
    
    return u_color_from_vec4(b);
}


static bool draw_kernel(Brush *self, int c, int r, enum draw_kernel_mode mode) {
   
   int kernel_offset_col = -(self->RO.kernel.cols-0.5)/2;
   int kernel_offset_row = -(self->RO.kernel.rows-0.5)/2;
   
   if(mode == DRAW_DITHER_A || mode == DRAW_DITHER_B) {
       c = (c-kernel_offset_col)/self->RO.kernel.cols * self->RO.kernel.cols;
       r = (r-kernel_offset_row)/self->RO.kernel.rows * self->RO.kernel.rows;
   }
   
   bool changed = false;
   for(int kr=0; kr<self->RO.kernel.rows; kr++) {
       // 'd'estination (-0.5 to let even kernels draw more to bottom right, instead of top left)
       int dr = kr + r + kernel_offset_row;
       for(int kc=0; kc<self->RO.kernel.cols; kc++) {
           int dc = kc + c + kernel_offset_col;
           
           uColor_s kernel_color = *u_image_pixel(self->RO.kernel, kc, kr, 0);
           
           if(mode == DRAW_DITHER_B) {
               kernel_color = ucvec4_sub_vec(U_COLOR_WHITE, kernel_color);
           }
           
           changed |= brush_draw_pixel(self, dc, dr, kernel_color);
       } 
   } 
   return changed;
}



//
// public
//

Brush *brush_new(Canvas *canvas) {
    Brush *self = rhc_calloc(sizeof *self);

    self->canvas_ref = canvas;
    
    self->brushmode = brushmode_new(self, canvas);

    self->current_color = U_COLOR_TRANSPARENT;
    self->secondary_color = U_COLOR_TRANSPARENT;
    self->mode = BRUSH_MODE_FREE;
    self->shading_active = false;
    
    self->RO.kernel = u_image_new_empty(1, 1, 1);
    *u_image_pixel_index(self->RO.kernel, 0, 0) = U_COLOR_WHITE;
    
    self->RO.kernel_tex = r_texture_new(
            self->RO.kernel.cols, 
            self->RO.kernel.rows,
            1, 1, self->RO.kernel.data);
    
    return self;
}

void brush_pointer_event(Brush *self, ePointer_s pointer) {
    if (pointer.id != 0)
        return;

    bool change = false;
    switch (self->mode) {
        case BRUSH_MODE_FREE:
        case BRUSH_MODE_DITHER:
        case BRUSH_MODE_DITHER2:
            change = brushmode_free(self->brushmode, pointer);
            break;
        case BRUSH_MODE_DOT:
            change = brushmode_dot(self->brushmode, pointer);
            break;
        case BRUSH_MODE_FILL:
            change = brushmode_fill(self->brushmode, pointer, false);
            break;
        case BRUSH_MODE_FILL8:
            change = brushmode_fill(self->brushmode, pointer, true);
            break;
        case BRUSH_MODE_REPLACE:
            change = brushmode_replace(self->brushmode, pointer);
            break;
        default:
            log_wtf("brush unknown mode");
    }

    if (change)
        self->L.change = true;

    if (self->L.change && pointer.action == E_POINTER_UP) {
        self->L.change = false;
        canvas_save(self->canvas_ref);
    }

}

bool brush_draw_pixel(Brush *self, int c, int r, uColor_s kernel_color) {
    uImage img = self->canvas_ref->RO.image;
    int layer = self->canvas_ref->current_layer;
    if (!u_image_contains(img, c, r))
        return false;

    const Selection *selection = self->in.selection_ref;
    if (selection && !selection_contains(selection, c, r))
        return false;

    uColor_s *pixel = u_image_pixel(img, c, r, layer);
    if (self->shading_active) {
        if (!u_color_equals(*pixel, self->secondary_color))
            return false;
    }
    
    *pixel = blend_color(*pixel, kernel_color, self->current_color);
    return true;
}


bool brush_draw(Brush *self, int c, int r) {
    if (self->mode == BRUSH_MODE_DITHER) {
        return draw_kernel(self, c, r, DRAW_DITHER_A);
    }
    if (self->mode == BRUSH_MODE_DITHER2) {
        return draw_kernel(self, c, r, DRAW_DITHER_B);
    }
    return draw_kernel(self, c, r, DRAW_NORMAL);
}

void brush_abort_current_draw(Brush *self) {
    log_info("brush: abort_current_draw");
    if (self->L.change) {
        canvas_reload(self->canvas_ref);
        brushmode_reset(self->brushmode); // sets drawing to false
        self->L.change = false;
    }
}

void brush_clear(Brush *self) {
    log_info("brush: clear");
    uImage img = self->canvas_ref->RO.image;
    int layer = self->canvas_ref->current_layer;
    const Selection *selection = self->in.selection_ref;
    for (int r = 0; r < img.rows; r++) {
        for (int c = 0; c < img.cols; c++) {
            if (selection && !selection_contains(selection, c, r))
                continue;

            *u_image_pixel(img, c, r, layer) = U_COLOR_TRANSPARENT;
        }
    }
    canvas_save(self->canvas_ref);
}

void brush_set_kernel(Brush *self, uImage kernel_sink) {
    if(!u_image_valid(kernel_sink)) {
        log_error("brush: set_kernel failed, invalid");
        return;
    }
    
    log_info("brush: set_kernel");
    
    u_image_kill(&self->RO.kernel);
    self->RO.kernel = kernel_sink;
    
    r_texture_kill(&self->RO.kernel_tex);
    self->RO.kernel_tex = r_texture_new(
            self->RO.kernel.cols, 
            self->RO.kernel.rows,
            1, 1, self->RO.kernel.data);
}

void brush_load_kernel(Brush *self, int id) {
    if(id<0 || id>=self->RO.max_kernels) {
        log_error("brush: load_kernel failed, invalid id: %i/%i", id, self->RO.max_kernels);
        return;
    }

    log_info("brush: load_kernel[%i] = %s", id, self->L.kernel_files[id]);
            
    char file[256];
    snprintf(file, sizeof file, "kernel_%s", self->L.kernel_files[id]);
    self->RO.kernel_id = id;
    brush_set_kernel(self, 
            u_image_new_file(1,
            e_io_savestate_file_path(file).s
            ));
            
    brush_save_config(self);
}

void brush_append_kernel(Brush *self, uImage kernel_sink, const char *name) {
    log_info("brush: append_file: %s", name);
    
    u_image_save_file(kernel_sink, e_io_savestate_file_path(name).s);
    
    bool found = false;
    for(int i=0; i<self->RO.max_kernels; i++) {
        if(strcmp(name, self->L.kernel_files[i]) == 0) {
            found = true;
            break;
        }
    }
    
    if(!found) {
        size_t len = strlen(name) + 1;
        char *clone = rhc_malloc(len);
        memcpy(clone, name, len);
        self->L.kernel_files = rhc_realloc(self->L.kernel_files, sizeof *self->L.kernel_files * ++self->RO.max_kernels);
        self->L.kernel_files[self->RO.max_kernels-1] = clone;
    }
    
    // save the savestate files (needed for web)
    e_io_savestate_save();
    
    brush_set_kernel(self, kernel_sink);
    self->RO.kernel_id = self->RO.max_kernels-1;
    brush_save_config(self);
}


void brush_reset_kernel_files(Brush *self) {
    log_info("brush: reset_kernel_files");
    uImage *kernels = brush_kernel_defaults_new();
    
    for(int i=0; i<self->RO.max_kernels; i++)
        rhc_free(self->L.kernel_files[i]);
    
    self->L.kernel_files = rhc_realloc(self->L.kernel_files, sizeof *self->L.kernel_files * 16);
    
    int i;
    for(i=0; u_image_valid(kernels[i]); i++) {
        assume(i<16, "change max default kernels");
        char *name = rhc_malloc(32);
        snprintf(name, 32, "default_%i.png", i);
        char file[32];
        snprintf(file, 32, "kernel_%s", name);
        u_image_save_file(kernels[i], e_io_savestate_file_path(file).s);
        
        self->L.kernel_files[i] = name;
    }
    self->RO.max_kernels = i;
    
    self->RO.kernel_id = 0;
    
    // save the savestate files (needed for web)
    e_io_savestate_save();
    
    brush_set_kernel(self, u_image_new_clone(kernels[0]));
    
    brush_kernel_defaults_kill(&kernels);
    
    brush_save_config(self);
}


void brush_save_config(const Brush *self) {
    log_info("brush: save_config");
    
    uJson *config = u_json_new_file(
            e_io_savestate_file_path("config.json").s);
    
    uJson *brush = u_json_append_object(config, "brush");
    uJson *kernel_files = u_json_append_array(brush, "kernel_files");
    for(int i=0; i<self->RO.max_kernels; i++) {
        u_json_append_string(kernel_files, NULL, self->L.kernel_files[i]);
    }
    
    u_json_append_int(brush, "kernel_id", self->RO.kernel_id);
    
    u_json_save_file(config,
                       e_io_savestate_file_path("config.json").s);
    e_io_savestate_save();
    
    u_json_kill(&config);
}

void brush_load_config(Brush *self) {
    log_info("brush: load_config");
    
    bool reset = false;
    
    uJson *config = u_json_new_file(
            e_io_savestate_file_path("config.json").s);
    
    uJson *brush = u_json_get_object(config, "brush");
    uJson *kernel_files = u_json_get_object(brush, "kernel_files");
    
    int kernels_size = u_json_get_size(kernel_files);
    
    if(kernels_size <= 0) {
        reset = true;
        goto CLEAN_UP;
    }
    
    for(int i=0; i<self->RO.max_kernels; i++)
        rhc_free(self->L.kernel_files[i]);
    
    self->L.kernel_files = rhc_realloc(self->L.kernel_files, sizeof *self->L.kernel_files * kernels_size);
    
    self->RO.max_kernels = kernels_size;
    
    for(int i=0; i<kernels_size; i++) {
        const char *file = u_json_get_id_string(kernel_files, i);
                
        if(!file) {
            reset = true;
            goto CLEAN_UP;
        }
        
        size_t len = strlen(file) + 1;
        char *clone = rhc_malloc(len);
        memcpy(clone, file, len);
        self->L.kernel_files[i] = clone;
    }
    
    int id;
    if(!u_json_get_object_int(brush, "kernel_id", &id)) {
        reset = true;
        goto CLEAN_UP;
    }
    
    if(id<0 || id>=self->RO.max_kernels) {
        log_warn("brush: load_config failed, invalid id, setting to 0");
        id = 0;
    }
    
    brush_load_kernel(self, id);
    
    CLEAN_UP:
    if(reset) {
        brush_reset_kernel_files(self);
    }   
    u_json_kill(&config);
}
