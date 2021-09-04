#define NK_IMPLEMENTATION
#define NK_SDL_GLES2_IMPLEMENTATION
#define NK_SDL_GL3_IMPLEMENTATION


#include "e/window.h"
#include "e/gui_nk.h"
#include "e/gui.h"
#include "rhc/error.h"

#define MAX_VERTEX_MEMORY 512 * 1024
#define MAX_ELEMENT_MEMORY 128 * 1024
 
 
struct eGui {
    struct nk_context *ctx;
    int auto_offset;
};

//
// singleton
//
static eGui singleton;
static bool singleton_created;
//
//
//

//
// protected
//
eGui *e_gui_singleton_;

void e_gui_input_begin_(const eGui *self) {
    if(!self)
        return;
    assume(self == &singleton, "singleton?");
    nk_input_begin(singleton.ctx);
}
void e_gui_handle_sdl_event_(const eGui *self, SDL_Event *event) {
    if(!self)
        return;
    assume(self == &singleton, "singleton?");
    nk_sdl_handle_event(event);
}

void e_gui_input_end_(const eGui *self) {
    if(!self)
        return;
    assume(self == &singleton, "singleton?");
    nk_input_end(singleton.ctx);
}


//
// private
//

static struct nk_rect window_rect(float w, float h) {
    int row = singleton.auto_offset / 3;
    int col = singleton.auto_offset % 3;
    singleton.auto_offset++;
    return nk_rect(50 + col * 100, 50 + row * 200, w, h);
}


//
// public
//

eGui *e_gui_new(const struct eWindow *window) {
    assume(!singleton_created, "e_gui_new should be called only onve");
    singleton_created = true;

    singleton.ctx = nk_sdl_init(e_window_get_sdl_window(window));

    struct nk_font_atlas *atlas;
    nk_sdl_font_stash_begin(&atlas);
    nk_sdl_font_stash_end();

    e_gui_singleton_ = &singleton;
    return &singleton;
}

void e_gui_kill(eGui **self_ptr) {
    // safe to free NULL
    if(!self_ptr)
        return;

    if(!singleton.ctx)
        return;

    nk_sdl_shutdown();

    assume(*self_ptr == &singleton, "singleton?");
    memset(&singleton, 0, sizeof(singleton));
    *self_ptr = NULL;
}

void e_gui_render(const eGui *self) {
    if(!self)
        return;
    assume(self == &singleton, "singleton?");
    singleton.auto_offset = 0;
    nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
}

struct nk_context *e_gui_get_nk_context(const eGui *self) {
    if(!self)
        return NULL;
    assume(self == &singleton, "singleton?");
    return singleton.ctx;
}

void e_gui_wnd_float_attribute(const eGui *self, const char *title, float *attribute, float min, float max, float step) {
    if(!self)
        return;
    assume(self == &singleton, "singleton?");
    if(!singleton.ctx)
        return;
    struct nk_context *ctx = singleton.ctx;
    if (nk_begin(ctx, title, window_rect(300, 100),
                 NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                 NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {
        nk_layout_row_static(ctx, 30, 120, 2);
        nk_slider_float(ctx, min, attribute, max, step);
        nk_labelf(ctx, NK_TEXT_LEFT, "%f", *attribute);
    }
    nk_end(ctx);
}

void e_gui_test(const eGui *self) {
    if(!self)
        return;
    assume(self == &singleton, "singleton?");
    if(!singleton.ctx)
        return;

    /* GUI */
    struct nk_context *ctx = singleton.ctx;
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
