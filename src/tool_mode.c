#include "r/ro_single.h"
#include "r/texture.h"
#include "u/pose.h"
#include "rhc/alloc.h"
#include "rhc/log.h"
#include "mathc/float.h"
#include "mathc/sca/int.h"
#include "button.h"
#include "brush.h"
#include "tool.h"

_Static_assert(sizeof(enum brush_modes) <= TOOL_BUTTON_ADDITIONAL_DATA_SIZE, "wtf");

static void mode_pe(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
    enum brush_modes mode = *((enum brush_modes *) self->additional_data);
    if (button_pressed(&self->ro.rect, pointer)) {
        log_info("tool mode: %i", mode);
        brush.mode = mode;
    }
}

static bool mode_is_a(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    enum brush_modes mode = *((enum brush_modes *) self->additional_data);
    button_set_pressed(&self->ro.rect, brush.mode == mode);
    // always active
    return true;
}

static Tool *mode_new(const char *name, const char *tip, const char *button_file, enum brush_modes mode) {
    Tool *super = tool_button_new(name, tip, button_file, mode_pe, mode_is_a);
    ToolButton *self = (ToolButton *) super;
    *((enum brush_modes *) self->additional_data) = mode;
    return super;
}


Tool *tool_new_mode_none() {
    return mode_new("none",
                    "does nothing\non the canvas",
                    "res/button_cross.png",
                    BRUSH_MODE_NONE);
}

Tool *tool_new_mode_free() {
    return mode_new("free",
                    "draw free\non the canvas",
                    "res/button_free.png",
                    BRUSH_MODE_FREE);
}

Tool *tool_new_mode_dot() {
    return mode_new("dot",
                    "draw on each tip",
                    "res/button_dot.png",
                    BRUSH_MODE_DOT);
}

Tool *tool_new_mode_line() {
    return mode_new("line",
                    "draw a line\non the canvas",
                    "res/button_line.png",
                    BRUSH_MODE_LINE);
}

Tool *tool_new_mode_rect() {
    return mode_new("rect",
                    "draws a rect\non the canvas",
                    "res/button_rect.png",
                    BRUSH_MODE_RECT);
}

Tool *tool_new_mode_circle() {
    return mode_new("circle",
                    "draws a circle\non the canvas\nstart pos is\nthe circle center",
                    "res/button_circle.png",
                    BRUSH_MODE_CIRCLE);
}

Tool *tool_new_mode_dither() {
    return mode_new("dither",
                    "draws in a grid\nfor dithering",
                    "res/button_dither.png",
                    BRUSH_MODE_DITHER);
}

Tool *tool_new_mode_dither_inv() {
    return mode_new("dither inverted",
                    "draws the\ninverted kernel\nin a grid\nfor dithering",
                    "res/button_dither_inv.png",
                    BRUSH_MODE_DITHER_INV);
}

Tool *tool_new_mode_fill() {
    return mode_new("fill",
                    "fills a\ntouched color\nwith mode 4\n\ngood to\nfill holes",
                    "res/button_fill.png",
                    BRUSH_MODE_FILL);
}

Tool *tool_new_mode_fill8() {
    return mode_new("fill 8",
                    "fills a\ntouched color\nwith mode 8\n\ngood to replace\nlines",
                    "res/button_fill8.png",
                    BRUSH_MODE_FILL8);
}

Tool *tool_new_mode_replace() {
    return mode_new("replace",
                    "replaces the\ntouched color",
                    "res/button_replace.png",
                    BRUSH_MODE_REPLACE);
}

Tool *tool_new_mode_pipette() {
    return mode_new("pipette",
                    "select a color\non the canvas\nas secondary color",
                    "res/button_pipette.png",
                    BRUSH_MODE_PIPETTE);
}
