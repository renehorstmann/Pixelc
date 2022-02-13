#include "r/ro_single.h"
#include "r/texture.h"
#include "u/pose.h"
#include "rhc/alloc.h"
#include "rhc/log.h"
#include "mathc/float.h"
#include "mathc/sca/int.h"
#include "button.h"
#include "tool.h"


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
            "draw free on the canvas", 
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
            "draws in a grid for dithering", 
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
            "draws the inverted kernel in a grid for dithering", 
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
            "fills a touched color with mode4", 
            "res/button_fill.png", 
            fill_pe,
            fill_is_a);
}

static void fill8_pe(struct Tool *super, ePointer_s pointer, ToolRefs refs) {
    ToolButton *self = (ToolButton*) super;
    if(button_pressed(&self->ro.rect, pointer)) {
        log_info("tool mode fill8");
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
    return tool_button_new("fill8", 
            "fills a touched color with mode8", 
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
            "replaces the touched color", 
            "res/button_replace.png", 
            replace_pe,
            replace_is_a);
}
