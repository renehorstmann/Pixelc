#include <time.h>
#include "r/r.h"
#include "u/json.h"
#include "m/sca/int.h"
#include "m/sca/uchar.h"
#include "e/io.h"
#include "io.h"
#include "animation.h"
#include "canvas.h"
#include "brushmode.h"
#include "brush.h"


struct Brush_Globals brush;

//
// private
//


static struct {
    bool hovering;
    bool hovering_change;
    bool change;

    char **kernel_files;
} L;

enum draw_kernel_mode {
    DRAW_NORMAL,
    DRAW_DITHER,
    DRAW_DITHER_INV,
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


static bool draw_kernel(int c, int r, enum draw_kernel_mode mode) {

    int kernel_offset_col = -(brush.RO.kernel.cols - 0.5) / 2;
    int kernel_offset_row = -(brush.RO.kernel.rows - 0.5) / 2;

    if (mode == DRAW_DITHER || mode == DRAW_DITHER_INV) {
        c = (c - kernel_offset_col) / brush.RO.kernel.cols * brush.RO.kernel.cols;
        r = (r - kernel_offset_row) / brush.RO.kernel.rows * brush.RO.kernel.rows;
    }

    bool changed = false;
    for (int kr = 0; kr < brush.RO.kernel.rows; kr++) {
        // 'd'estination (-0.5 to let even kernels draw more to bottom right, instead of top left)
        int dr = kr + r + kernel_offset_row;
        for (int kc = 0; kc < brush.RO.kernel.cols; kc++) {
            int dc = kc + c + kernel_offset_col;

            uColor_s kernel_color = *u_image_pixel(brush.RO.kernel, kc, kr, 0);

            if (mode == DRAW_DITHER_INV) {
                kernel_color = ucvec4_sub_vec(U_COLOR_WHITE, kernel_color);
            }

            changed |= brush_draw_pixel(dc, dr, kernel_color);
        }
    }
    return changed;
}



//
// public
//

void brush_init() {
    brushmode_init();

    brush.current_color = U_COLOR_TRANSPARENT;
    brush.secondary_color = U_COLOR_WHITE;
    brush.mode = BRUSH_MODE_FREE;
    brush.shading_active = false;
    brush.render_hover_preview = true;
    brush.auto_save_config = true;

    L.hovering = true;

    brush.RO.kernel = u_image_new_empty(1, 1, 1);
    *u_image_pixel_index(brush.RO.kernel, 0, 0) = U_COLOR_WHITE;

    brush.RO.kernel_tex = r_texture_new(
            brush.RO.kernel.cols,
            brush.RO.kernel.rows,
            1, 1, brush.RO.kernel.data);
}

void brush_pointer_event(ePointer_s pointer) {
    if (pointer.id != 0)
        return;

    if (pointer.action == E_POINTER_DOWN)
        L.hovering = false;


    if (L.hovering && L.hovering_change)
        canvas_reload();

    if(brush.shading_active && pointer.action == E_POINTER_DOWN) {
        vec4 flash_color = u_color_to_vec4(brush.secondary_color);
        flash_color.a = 1.0;
        animation_flash(flash_color, 1.0);
    }

    if (L.hovering && pointer.action == E_POINTER_HOVER) {
        switch (brush.mode) {
            case BRUSH_MODE_FREE:
            case BRUSH_MODE_DOT:
            case BRUSH_MODE_LINE:
            case BRUSH_MODE_RECT:
            case BRUSH_MODE_CIRCLE:
            case BRUSH_MODE_DITHER:
            case BRUSH_MODE_DITHER_INV:
                pointer.action = E_POINTER_DOWN;
            default:
                break;
        }
    }

    bool change = false;
    switch (brush.mode) {
        case BRUSH_MODE_NONE:
            break;
        case BRUSH_MODE_FREE:
        case BRUSH_MODE_DITHER:
        case BRUSH_MODE_DITHER_INV:
            change = brushmode_free(pointer);
            break;
        case BRUSH_MODE_DOT:
            change = brushmode_dot(pointer);
            break;
        case BRUSH_MODE_LINE:
            change = brushmode_func(pointer, BRUSHMODE_FUNC_LINE);
            break;
        case BRUSH_MODE_RECT:
            change = brushmode_func(pointer, BRUSHMODE_FUNC_RECT);
            break;
        case BRUSH_MODE_CIRCLE:
            change = brushmode_func(pointer, BRUSHMODE_FUNC_CIRCLE);
            break;
        case BRUSH_MODE_FILL:
            change = brushmode_fill(pointer, false);
            break;
        case BRUSH_MODE_FILL8:
            change = brushmode_fill(pointer, true);
            break;
        case BRUSH_MODE_REPLACE:
            change = brushmode_replace(pointer);
            break;
        case BRUSH_MODE_PIPETTE:
            brushmode_pipette(pointer);
            break;
        default:
            s_log_wtf("unknown mode");
    }

    L.hovering_change = change;

    if (L.hovering)
        return;

    if (change)
        L.change = true;

    if (L.change && pointer.action == E_POINTER_UP) {
        L.change = false;
        canvas_save();
    }

    if (brush.render_hover_preview && pointer.action == E_POINTER_UP)
        L.hovering = true;
}

bool brush_draw_pixel(int c, int r, uColor_s kernel_color) {
    uImage img = canvas.RO.image;
    int layer = canvas.current_layer;
    if (!u_image_contains(img, c, r))
        return false;

    const Selection *selection = brush.selection_ref;
    if (selection && !selection_contains(selection, c, r))
        return false;

    uColor_s *pixel = u_image_pixel(img, c, r, layer);
    
    if (brush.shading_active) {
        if (!u_color_equals(*pixel, brush.secondary_color))
            return false;
    }

    *pixel = blend_color(*pixel, kernel_color, brush.current_color);
    return true;
}


bool brush_draw(int c, int r) {
    if (brush.mode == BRUSH_MODE_DITHER) {
        return draw_kernel(c, r, DRAW_DITHER);
    }
    if (brush.mode == BRUSH_MODE_DITHER_INV) {
        return draw_kernel(c, r, DRAW_DITHER_INV);
    }
    return draw_kernel(c, r, DRAW_NORMAL);
}

void brush_abort_current_draw() {
    s_log("abort");
    if (L.change || (L.hovering && L.hovering_change)) {
        canvas_reload();
        brushmode_reset(); // sets drawing to false
        L.change = false;
    }
}

void brush_clear() {
    s_log("clear");
    uImage img = canvas.RO.image;
    int layer = canvas.current_layer;
    const Selection *selection = brush.selection_ref;
    for (int r = 0; r < img.rows; r++) {
        for (int c = 0; c < img.cols; c++) {
            if (selection && !selection_contains(selection, c, r))
                continue;

            *u_image_pixel(img, c, r, layer) = U_COLOR_TRANSPARENT;
        }
    }
    canvas_save();
}

void brush_set_kernel(uImage kernel_sink) {
    if (!u_image_valid(kernel_sink)) {
        s_log_error("invalid");
        return;
    }

    s_log("set kernel");

    u_image_kill(&brush.RO.kernel);
    brush.RO.kernel = kernel_sink;

    r_texture_kill(&brush.RO.kernel_tex);
    brush.RO.kernel_tex = r_texture_new(
            brush.RO.kernel.cols,
            brush.RO.kernel.rows,
            1, 1, brush.RO.kernel.data);
}

void brush_load_kernel(int id) {
    if (id < 0 || id >= brush.RO.max_kernels) {
        s_log_error("invalid id: %i/%i", id, brush.RO.max_kernels);
        return;
    }

    s_log("load_kernel[%i] = %s", id, L.kernel_files[id]);

    char file[256];
    snprintf(file, sizeof file, "kernel_%s.png", L.kernel_files[id]);

    uImage kernel = u_image_new_file(1, e_io_savestate_file_path(file));

    brush.RO.kernel_id = id;
    brush_set_kernel(kernel);

    if (brush.auto_save_config)
        brush_save_config();
}

void brush_append_kernel(uImage kernel) {
    s_log("append_kernel: %i", brush.RO.max_kernels);

    // create random name
    char name[128];
    srand(time(NULL));
    for(;;) {
        int num = rand() % 1000000;
        snprintf(name, sizeof name, "custom_%i", num);
        for(int i=0; i<brush.RO.max_kernels; i++) {
            if(strcmp(L.kernel_files[i], name) == 0)
                continue;
        }
        break;
    }

    char file[256];
    snprintf(file, sizeof file, "kernel_%s.png", name);
    u_image_save_file(kernel, e_io_savestate_file_path(file));

    int idx = -1;
    for (int i = 0; i < brush.RO.max_kernels; i++) {
        if (strcmp(name, L.kernel_files[i]) == 0) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        ssize len = strlen(name) + 1;
        char *clone = s_malloc(len);
        memcpy(clone, name, len);
        L.kernel_files = s_realloc(L.kernel_files, sizeof *L.kernel_files * ++brush.RO.max_kernels);
        idx = brush.RO.max_kernels - 1;
        L.kernel_files[idx] = clone;
    }

    // save the savestate files (needed for web)
    e_io_savestate_save();

    brush_load_kernel(idx);
}

void brush_delete_kernel(int id) {
    s_assume(id>=0&&id<brush.RO.max_kernels, "not in range");
    if(brush.RO.max_kernels<=1) {
        s_log_warn("can not delete, min. 1 kernel");
        return;
    }
    brush.RO.max_kernels--;
    if(brush.RO.kernel_id >= id) {
        int load = id-1;
        load = isca_mod(load, brush.RO.max_kernels);
        brush_load_kernel(load);
    }
    s_free(L.kernel_files[id]);
    for(int i=id;i<brush.RO.max_kernels;i++)
        L.kernel_files[i] = L.kernel_files[i+1];

}


void brush_reset_kernel_files() {
    s_log("reset kernel files");
    uImage *kernels = brush_kernel_defaults_new();

    for (int i = 0; i < brush.RO.max_kernels; i++)
        s_free(L.kernel_files[i]);

    L.kernel_files = s_realloc(L.kernel_files, sizeof *L.kernel_files * 16);

    int i;
    for (i = 0; u_image_valid(kernels[i]); i++) {
        s_assume(i < 16, "change max default kernels");
        char *name = s_malloc(32);
        snprintf(name, 32, "default_%i", i);
        char file[32];
        snprintf(file, 32, "kernel_%s.png", name);
        u_image_save_file(kernels[i], e_io_savestate_file_path(file));

        L.kernel_files[i] = name;
    }
    brush.RO.max_kernels = i;

    brush.RO.kernel_id = 0;

    // save the savestate files (needed for web)
    e_io_savestate_save();

    brush_set_kernel(u_image_new_clone(kernels[0]));

    brush_kernel_defaults_kill(&kernels);

    if (brush.auto_save_config)
        brush_save_config();
}


void brush_save_config() {
    s_log("save");

    uJson *config = u_json_new_file(io_config_file());

    uJson *member = u_json_append_object(config, "brush");
    uJson *kernel_files = u_json_append_array(member, "kernel_files");
    for (int i = 0; i < brush.RO.max_kernels; i++) {
        u_json_append_string(kernel_files, NULL, L.kernel_files[i]);
    }

    u_json_append_int(member, "kernel_id", brush.RO.kernel_id);

    u_json_save_file(config, io_config_file());
    e_io_savestate_save();

    u_json_kill(&config);
}

void brush_load_config() {
    s_log("load");

    bool reset = false;

    uJson *config = u_json_new_file(io_config_file());

    uJson *member = u_json_get_object(config, "brush");
    uJson *kernel_files = u_json_get_object(member, "kernel_files");

    int kernels_size = u_json_get_size(kernel_files);

    if (kernels_size <= 0) {
        reset = true;
        goto CLEAN_UP;
    }

    for (int i = 0; i < brush.RO.max_kernels; i++)
        s_free(L.kernel_files[i]);

    L.kernel_files = s_realloc(L.kernel_files, sizeof *L.kernel_files * kernels_size);

    brush.RO.max_kernels = kernels_size;

    for (int i = 0; i < kernels_size; i++) {
        const char *file = u_json_get_id_string(kernel_files, i);

        if (!file) {
            reset = true;
            goto CLEAN_UP;
        }

        size_t len = strlen(file) + 1;
        char *clone = s_malloc(len);
        memcpy(clone, file, len);
        L.kernel_files[i] = clone;
    }

    int id;
    if (!u_json_get_object_int(member, "kernel_id", &id)) {
        reset = true;
        goto CLEAN_UP;
    }

    if (id < 0 || id >= brush.RO.max_kernels) {
        s_log_warn("invalid id, setting to 0");
        id = 0;
    }

    brush_load_kernel(id);

    CLEAN_UP:
    if (reset) {
        brush_reset_kernel_files();
    }
    u_json_kill(&config);
}
