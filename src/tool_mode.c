#include "r/ro_single.h"
#include "r/texture.h"
#include "u/pose.h"
#include "rhc/alloc.h"
#include "rhc/log.h"
#include "mathc/float.h"
#include "mathc/sca/int.h"
#include "button.h"
#include "tool.h"


static void none_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(button_pressed(&self->ro.rect, pointer)) {
        log_info("tool mode none");
        refs.brush->mode = BRUSH_MODE_NONE;
    } 
}
static bool none_is_a(struct Tool *super, float dtime, ToolRefs refs) {
    ToolButton *self = (ToolButton *) super;
    button_set_pressed(&self->ro.rect, refs.brush->mode == BRUSH_MODE_NONE);
    // always active
    return true;
}      
Tool *tool_new_mode_none() {
    return tool_button_new("none", 
            "does nothing\non the canvas", 
            "res/button_cross.png", 
            none_pe,
            none_is_a);
}


static void free_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(button_pressed(&self->ro.rect, pointer)) {
        log_info("tool mode free");
        refs.brush->mode = BRUSH_MODE_FREE;
    } 
}
static bool free_is_a(struct Tool *super, float dtime, ToolRefs refs) {
    ToolButton *self = (ToolButton *) super;
    button_set_pressed(&self->ro.rect, refs.brush->mode == BRUSH_MODE_FREE);
    // always active
    return true;
}      
Tool *tool_new_mode_free() {
    return tool_button_new("free", 
            "draw free\non the canvas", 
            "res/button_free.png", 
            free_pe,
            free_is_a);
}


static void dot_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(button_pressed(&self->ro.rect, pointer)) {
        log_info("tool mode dot");
        refs.brush->mode = BRUSH_MODE_DOT;
    } 
}
static bool dot_is_a(struct Tool *super, float dtime, ToolRefs refs) {
    ToolButton *self = (ToolButton *) super;
    button_set_pressed(&self->ro.rect, refs.brush->mode == BRUSH_MODE_DOT);
    // always active
    return true;
}      
Tool *tool_new_mode_dot() {
    return tool_button_new("dot", 
            "draw on each tip", 
            "res/button_dot.png", 
            dot_pe,
            dot_is_a);
}


static void line_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(button_pressed(&self->ro.rect, pointer)) {
        log_info("tool mode line");
        refs.brush->mode = BRUSH_MODE_LINE;
    } 
}
static bool line_is_a(struct Tool *super, float dtime, ToolRefs refs) {
    ToolButton *self = (ToolButton *) super;
    button_set_pressed(&self->ro.rect, refs.brush->mode == BRUSH_MODE_LINE);
    // always active
    return true;
}      
Tool *tool_new_mode_line() {
    return tool_button_new("line", 
            "draw a line\non the canvas", 
            "res/button_line.png", 
            line_pe,
            line_is_a);
}


static void rect_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(button_pressed(&self->ro.rect, pointer)) {
        log_info("tool mode rect");
        refs.brush->mode = BRUSH_MODE_RECT;
    } 
}
static bool rect_is_a(struct Tool *super, float dtime, ToolRefs refs) {
    ToolButton *self = (ToolButton *) super;
    button_set_pressed(&self->ro.rect, refs.brush->mode == BRUSH_MODE_RECT);
    // always active
    return true;
}      
Tool *tool_new_mode_rect() {
    return tool_button_new("rect", 
            "draws a rect\non the canvas", 
            "res/button_rect.png", 
            rect_pe,
            rect_is_a);
}



static void circle_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(button_pressed(&self->ro.rect, pointer)) {
        log_info("tool mode circle");
        refs.brush->mode = BRUSH_MODE_CIRCLE;
    } 
}
static bool circle_is_a(struct Tool *super, float dtime, ToolRefs refs) {
    ToolButton *self = (ToolButton *) super;
    button_set_pressed(&self->ro.rect, refs.brush->mode == BRUSH_MODE_CIRCLE);
    // always active
    return true;
}      
Tool *tool_new_mode_circle() {
    return tool_button_new("circle", 
            "draws a circle\non the canvas\nstart pos is\nthe circle center", 
            "res/button_circle.png", 
            circle_pe,
            circle_is_a);
}


static void dither_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(button_pressed(&self->ro.rect, pointer)) {
        log_info("tool mode dither");
        refs.brush->mode = BRUSH_MODE_DITHER;
    } 
}
static bool dither_is_a(struct Tool *super, float dtime, ToolRefs refs) {
    ToolButton *self = (ToolButton *) super;
    button_set_pressed(&self->ro.rect, refs.brush->mode == BRUSH_MODE_DITHER);
    // always active
    return true;
}      
Tool *tool_new_mode_dither() {
    return tool_button_new("dither", 
            "draws in a grid\nfor dithering", 
            "res/button_dither.png", 
            dither_pe,
            dither_is_a);
}

static void dither_inv_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(button_pressed(&self->ro.rect, pointer)) {
        log_info("tool mode dither_inv");
        refs.brush->mode = BRUSH_MODE_DITHER_INV;
    } 
}
static bool dither_inv_is_a(struct Tool *super, float dtime, ToolRefs refs) {
    ToolButton *self = (ToolButton *) super;
    button_set_pressed(&self->ro.rect, refs.brush->mode == BRUSH_MODE_DITHER_INV);
    // always active
    return true;
}      
Tool *tool_new_mode_dither_inv() {
    return tool_button_new("dither inverted", 
            "draws the\ninverted kernel\nin a grid\nfor dithering", 
            "res/button_dither_inv.png", 
            dither_inv_pe,
            dither_inv_is_a);
}


static void fill_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(button_pressed(&self->ro.rect, pointer)) {
        log_info("tool mode fill");
        refs.brush->mode = BRUSH_MODE_FILL;
    } 
}
static bool fill_is_a(struct Tool *super, float dtime, ToolRefs refs) {
    ToolButton *self = (ToolButton *) super;
    button_set_pressed(&self->ro.rect, refs.brush->mode == BRUSH_MODE_FILL);
    // always active
    return true;
}      
Tool *tool_new_mode_fill() {
    return tool_button_new("fill", 
            "fills a\ntouched color\nwith mode 4\n\ngood to\nfill holes", 
            "res/button_fill.png", 
            fill_pe,
            fill_is_a);
}

static void fill8_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(button_pressed(&self->ro.rect, pointer)) {
        log_info("tool mode fill 8");
        refs.brush->mode = BRUSH_MODE_FILL8;
    } 
}
static bool fill8_is_a(struct Tool *super, float dtime, ToolRefs refs) {
    ToolButton *self = (ToolButton *) super;
    button_set_pressed(&self->ro.rect, refs.brush->mode == BRUSH_MODE_FILL8);
    // always active
    return true;
}      
Tool *tool_new_mode_fill8() {
    return tool_button_new("fill 8", 
            "fills a\ntouched color\nwith mode 8\n\ngood to replace\nlines", 
            "res/button_fill8.png", 
            fill8_pe,
            fill8_is_a);
}


static void replace_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(button_pressed(&self->ro.rect, pointer)) {
        log_info("tool mode replace");
        refs.brush->mode = BRUSH_MODE_REPLACE;
    } 
}
static bool replace_is_a(struct Tool *super, float dtime, ToolRefs refs) {
    ToolButton *self = (ToolButton *) super;
    button_set_pressed(&self->ro.rect, refs.brush->mode == BRUSH_MODE_REPLACE);
    // always active
    return true;
}      
Tool *tool_new_mode_replace() {
    return tool_button_new("replace", 
            "replaces the\ntouched color", 
            "res/button_replace.png", 
            replace_pe,
            replace_is_a);
}

static void pipette_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(button_pressed(&self->ro.rect, pointer)) {
        log_info("tool mode pipette");
        refs.brush->mode = BRUSH_MODE_PIPETTE;
    } 
}
static bool pipette_is_a(struct Tool *super, float dtime, ToolRefs refs) {
    ToolButton *self = (ToolButton *) super;
    button_set_pressed(&self->ro.rect, refs.brush->mode == BRUSH_MODE_PIPETTE);
    // always active
    return true;
}      
Tool *tool_new_mode_pipette() {
    return tool_button_new("pipette", 
            "select a color\non the canvas\nas secondary color", 
            "res/button_pipette.png", 
            pipette_pe,
            pipette_is_a);
}
