#define NK_IMPLEMENTATION
#define NK_SDL_GLES2_IMPLEMENTATION
#define NK_SDL_GL3_IMPLEMENTATION

#include "e/window.h"
#include "e/gui.h"

#define MAX_VERTEX_MEMORY 512 * 1024
#define MAX_ELEMENT_MEMORY 128 * 1024

struct nk_context *e_gui_ctx;

static int auto_offset;


static struct nk_rect window_rect(float w, float h) {
    int row = auto_offset / 3;
    int col = auto_offset % 3;
    auto_offset++;
    return nk_rect(50 + col * 100, 50 + row * 200, w, h);
}

void e_gui_init() {
    e_gui_ctx = nk_sdl_init(e_window);

    struct nk_font_atlas *atlas;
    nk_sdl_font_stash_begin(&atlas);
    nk_sdl_font_stash_end();
}

void e_gui_kill() {
    nk_sdl_shutdown();
}

void e_gui_wnd_float_attribute(const char *title, float *attribute, float min, float max, float step) {

    struct nk_context *ctx = e_gui_ctx;
    if (nk_begin(ctx, title, window_rect(300, 100),
                 NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
                 NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
    {
        nk_layout_row_static(ctx, 30, 120, 2);
        nk_slider_float(ctx, min, attribute, max, step);
        nk_labelf(ctx, NK_TEXT_LEFT, "%f", *attribute);
    }
    nk_end(ctx);
}

void e_gui_test() {

    /* GUI */
    struct nk_context *ctx = e_gui_ctx;
    static struct nk_colorf bg;
    if (nk_begin(ctx, "Demo", window_rect(300, 600),
                 NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
                 NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
    {
        enum {EASY, HARD};
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
        if (nk_combo_begin_color(ctx, nk_rgb_cf(bg), nk_vec2(nk_widget_width(ctx),400))) {
            nk_layout_row_dynamic(ctx, 120, 1);
            bg = nk_color_picker(ctx, bg, NK_RGBA);
            nk_layout_row_dynamic(ctx, 25, 1);
            bg.r = nk_propertyf(ctx, "#R:", 0, bg.r, 1.0f, 0.01f,0.005f);
            bg.g = nk_propertyf(ctx, "#G:", 0, bg.g, 1.0f, 0.01f,0.005f);
            bg.b = nk_propertyf(ctx, "#B:", 0, bg.b, 1.0f, 0.01f,0.005f);
            bg.a = nk_propertyf(ctx, "#A:", 0, bg.a, 1.0f, 0.01f,0.005f);
            nk_combo_end(ctx);
        }
    }
    nk_end(ctx);


    printf("bg: %f %f %f %f\n", bg.r, bg.g, bg.b, bg.a);
}

void e_gui_render() {
    auto_offset = 0;
    nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
}
