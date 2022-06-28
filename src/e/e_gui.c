#define NK_IMPLEMENTATION
#define NK_SDL_GLES2_IMPLEMENTATION
#define NK_SDL_GL3_IMPLEMENTATION


#include "e/window.h"
#include "e/gui_nk.h"
#include "e/gui.h"

#define MAX_VERTEX_MEMORY 512 * 1024
#define MAX_ELEMENT_MEMORY 128 * 1024


struct eGui_Globals e_gui;

static struct {
    int auto_offset;
} L;


//
// protected
//

void e_gui_input_begin_() {
    if (!e_gui.init)
        return;
    nk_input_begin(e_gui.ctx);
}

void e_gui_handle_sdl_event_(SDL_Event *event) {
    if (!e_gui.init)
        return;
    nk_sdl_handle_event(event);
}

void e_gui_input_end_() {
    if (!e_gui.init)
        return;
    nk_input_end(e_gui.ctx);
}


//
// private
//

static struct nk_rect window_rect(float w, float h) {
    int row = L.auto_offset / 3;
    int col = L.auto_offset % 3;
    L.auto_offset++;
    return nk_rect(50 + col * 100, 50 + row * 200, w, h);
}


//
// public
//

void e_gui_init() {
    s_assume(!e_gui.init, "should be called only once");
    e_gui.init = true;

    s_log("init");

    e_gui.ctx = nk_sdl_init(e_window.sdl_window);

    struct nk_font_atlas *atlas;
    nk_sdl_font_stash_begin(&atlas);
    nk_sdl_font_stash_end();
}

void e_gui_kill() {
    if (!e_gui.init)
        return;

    nk_sdl_shutdown();

    memset(&e_gui, 0, sizeof e_gui);
    memset(&L, 0, sizeof L);
}

void e_gui_render() {
    if (!e_gui.init)
        return;
    L.auto_offset = 0;
    nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
}

void e_gui_float(const char *title, float *attribute, float min, float max) {
    if (!e_gui.init)
        return;
    struct nk_context *ctx = e_gui.ctx;
    if (nk_begin(ctx, title, window_rect(300, 90),
                 NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                 NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {
        nk_layout_row_dynamic(ctx, 30, 1);
        *attribute = nk_propertyf(ctx, title, min, *attribute, max, 0, (max - min) / 100);
    }
    nk_end(ctx);
}

void e_gui_vec2(const char *title, vec2 *attribute, vec2 min, vec2 max) {
    if (!e_gui.init)
        return;
    struct nk_context *ctx = e_gui.ctx;
    if (nk_begin(ctx, title, window_rect(300, 125),
                 NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                 NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {
        nk_layout_row_dynamic(ctx, 25, 1);
        for (int i = 0; i < 2; i++) {
            char name[3] = "vX";
            name[1] = '0' + i;
            attribute->v[i] = nk_propertyf(ctx,
                                           name,
                                           min.v[i], attribute->v[i], max.v[i], 0, (max.v[i] - min.v[i]) / 100);
        }
    }
    nk_end(ctx);
}

void e_gui_vec3(const char *title, vec3 *attribute, vec3 min, vec3 max) {
    if (!e_gui.init)
        return;
    struct nk_context *ctx = e_gui.ctx;
    if (nk_begin(ctx, title, window_rect(300, 150),
                 NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                 NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {
        nk_layout_row_dynamic(ctx, 25, 1);
        for (int i = 0; i < 3; i++) {
            char name[3] = "vX";
            name[1] = '0' + i;
            attribute->v[i] = nk_propertyf(ctx,
                                           name,
                                           min.v[i], attribute->v[i], max.v[i], 0, (max.v[i] - min.v[i]) / 100);
        }
    }
    nk_end(ctx);
}

void e_gui_vec4(const char *title, vec4 *attribute, vec4 min, vec4 max) {
    if (!e_gui.init)
        return;
    struct nk_context *ctx = e_gui.ctx;
    if (nk_begin(ctx, title, window_rect(300, 175),
                 NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                 NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {
        nk_layout_row_dynamic(ctx, 25, 1);
        for (int i = 0; i < 4; i++) {
            char name[3] = "vX";
            name[1] = '0' + i;
            attribute->v[i] = nk_propertyf(ctx,
                                           name,
                                           min.v[i], attribute->v[i], max.v[i], 0, (max.v[i] - min.v[i]) / 100);
        }
    }
    nk_end(ctx);
}


void e_gui_rgb(const char *title, vec3 *attribute) {
    if (!e_gui.init)
        return;
    struct nk_context *ctx = e_gui.ctx;
    struct nk_colorf color = {
            .r = attribute->r,
            .g = attribute->g,
            .b = attribute->b,
            .a = 1
    };
    if (nk_begin(ctx, title, window_rect(300, 275),
                 NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                 NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {
        nk_layout_row_dynamic(ctx, 120, 1);
        color = nk_color_picker(ctx, color, NK_RGB);
        nk_layout_row_dynamic(ctx, 25, 1);
        color.r = nk_propertyf(ctx, "red", 0, color.r, 1, 0, 0.01f);
        color.g = nk_propertyf(ctx, "green", 0, color.g, 1, 0, 0.01f);
        color.b = nk_propertyf(ctx, "blue", 0, color.b, 1, 0, 0.01f);
    }
    nk_end(ctx);

    *attribute = (vec3) {{
                                 color.r,
                                 color.g,
                                 color.b
                         }};
}

void e_gui_rgba(const char *title, vec4 *attribute) {
    if (!e_gui.init)
        return;
    struct nk_context *ctx = e_gui.ctx;
    struct nk_colorf color = {
            .r = attribute->r,
            .g = attribute->g,
            .b = attribute->b,
            .a = attribute->a
    };
    if (nk_begin(ctx, title, window_rect(300, 300),
                 NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                 NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {
        nk_layout_row_dynamic(ctx, 120, 1);
        color = nk_color_picker(ctx, color, NK_RGBA);
        nk_layout_row_dynamic(ctx, 25, 1);
        color.r = nk_propertyf(ctx, "red", 0, color.r, 1, 0, 0.01f);
        color.g = nk_propertyf(ctx, "green", 0, color.g, 1, 0, 0.01f);
        color.b = nk_propertyf(ctx, "blue", 0, color.b, 1, 0, 0.01f);
        color.a = nk_propertyf(ctx, "alpha", 0, color.a, 1, 0, 0.01f);
    }
    nk_end(ctx);

    *attribute = (vec4) {{
                                 color.r,
                                 color.g,
                                 color.b,
                                 color.a
                         }};
}

void e_gui_test() {
    if (!e_gui.init)
        return;

    /* GUI */
    struct nk_context *ctx = e_gui.ctx;
    static struct nk_colorf bg;
    if (nk_begin(ctx, "Demo", window_rect(300, 600),
                 NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                 NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {
        enum {
            EASY, HARD
        };
        static int op = EASY;
        static int property = 20;

        nk_layout_row_static(ctx, 30, 80, 1);
        if (nk_button_label(ctx, "button"))
            printf("button pressed!\n");
        nk_layout_row_dynamic(ctx, 30, 2);
        if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
        if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;
        nk_layout_row_dynamic(ctx, 22, 1);
        nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);

        nk_layout_row_dynamic(ctx, 20, 1);
        nk_label(ctx, "background:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(ctx, 25, 1);
        if (nk_combo_begin_color(ctx, nk_rgb_cf(bg), nk_vec2(nk_widget_width(ctx), 400))) {
            nk_layout_row_dynamic(ctx, 120, 1);
            bg = nk_color_picker(ctx, bg, NK_RGBA);
            nk_layout_row_dynamic(ctx, 25, 1);
            bg.r = nk_propertyf(ctx, "#R:", 0, bg.r, 1.0f, 0.01f, 0.005f);
            bg.g = nk_propertyf(ctx, "#G:", 0, bg.g, 1.0f, 0.01f, 0.005f);
            bg.b = nk_propertyf(ctx, "#B:", 0, bg.b, 1.0f, 0.01f, 0.005f);
            bg.a = nk_propertyf(ctx, "#A:", 0, bg.a, 1.0f, 0.01f, 0.005f);
            nk_combo_end(ctx);
        }
    }
    nk_end(ctx);


    printf("bg: %f %f %f %f\n", bg.r, bg.g, bg.b, bg.a);
}
