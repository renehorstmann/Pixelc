
#include "r/ro_single.h"
#include "r/texture.h"
#include "u/pose.h"
#include "m/float.h"
#include "m/sca/int.h"
#include "u/button.h"
#include "brush.h"
#include "tool.h"

_Static_assert(sizeof(enum brush_modes) <= TOOL_BUTTON_ADDITIONAL_DATA_SIZE, "wtf");

static void mode_pe(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
    enum brush_modes mode = *((enum brush_modes *) self->additional_data);
    if (u_button_pressed(&self->ro.rect, pointer)) {
        s_log("tool mode: %i", mode);
        brush.mode = mode;
    }
}

static bool mode_is_a(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    enum brush_modes mode = *((enum brush_modes *) self->additional_data);
    u_button_set_pressed(&self->ro.rect, brush.mode == mode);
    // always active
    return true;
}

static Tool *mode_new(const char *name, const char *tip, const char *u_button_file, enum brush_modes mode) {
    Tool *super = tool_button_new(name, tip, u_button_file, mode_pe, mode_is_a);
    ToolButton *self = (ToolButton *) super;
    *((enum brush_modes *) self->additional_data) = mode;
    return super;
}


Tool *tool_new_mode_none() {
    return mode_new("none",
                    "Does nothing\n"
                    "on the canvas",
                    "res/button_cross.png",
                    BRUSH_MODE_NONE);
}

Tool *tool_new_mode_free() {
    return mode_new("free",
                    "Draw free\n"
                    "on the canvas",
                    "res/button_free.png",
                    BRUSH_MODE_FREE);
}

Tool *tool_new_mode_dot() {
    return mode_new("dot",
                    "Draw on each tip",
                    "res/button_dot.png",
                    BRUSH_MODE_DOT);
}

Tool *tool_new_mode_line() {
    return mode_new("line",
                    "Draw a line\n"
                    "on the canvas",
                    "res/button_line.png",
                    BRUSH_MODE_LINE);
}

Tool *tool_new_mode_rect() {
    return mode_new("rect",
                    "Draws a rect\n"
                    "on the canvas",
                    "res/button_rect.png",
                    BRUSH_MODE_RECT);
}

Tool *tool_new_mode_circle() {
    return mode_new("circle",
                    "Draws a circle\n"
                    "on the canvas\n\n"
                    "start pos is\n"
                    "the circle center",
                    "res/button_circle.png",
                    BRUSH_MODE_CIRCLE);
}

Tool *tool_new_mode_dither() {
    return mode_new("dither",
                    "Draws in a grid\n"
                    "for dithering",
                    "res/button_dither.png",
                    BRUSH_MODE_DITHER);
}

Tool *tool_new_mode_dither_inv() {
    return mode_new("dither inverted",
                    "Draws the\n"
                    "inverted kernel\n"
                    "in a grid\n"
                    "for dithering",
                    "res/button_dither_inv.png",
                    BRUSH_MODE_DITHER_INV);
}

Tool *tool_new_mode_fill() {
    return mode_new("fill",
                    "Fills a\n"
                    "touched color\n"
                    "with mode 4\n\n"
                    "Good to\n"
                    "fill blobs",
                    "res/button_fill.png",
                    BRUSH_MODE_FILL);
}

Tool *tool_new_mode_fill8() {
    return mode_new("fill 8",
                    "Fills a\n"
                    "touched color\n"
                    "with mode 8\n\n"
                    "Good to replace\n"
                    "lines",
                    "res/button_fill8.png",
                    BRUSH_MODE_FILL8);
}

Tool *tool_new_mode_replace() {
    return mode_new("replace",
                    "Replaces the\n"
                    "touched color",
                    "res/button_replace.png",
                    BRUSH_MODE_REPLACE);
}

Tool *tool_new_mode_pipette() {
    return mode_new("pipette",
                    "Select a color\n"
                    "on the canvas as\n"
                    "secondary color\n\n"
                    "flashes the\n"
                    "screen\n"
                    "while active",
                    "res/button_pipette.png",
                    BRUSH_MODE_PIPETTE);
}
