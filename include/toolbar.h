#ifndef PIXELC_TOOLBAR_H
#define PIXELC_TOOLBAR_H

#include "r/ro_types.h"
#include "u/color.h"
#include "u/container.h"
#include "tool.h"

#define TOOLBAR_TOOLS_LEN 3
#define TOLLBAR_SELECTION_TOOLS_LEN 10

typedef struct {
    Tool **tools;
    int tools_len;
    
    uContainer container;
    
    RoSingle bg;
} ToolbarContainer;

typedef struct {
    ToolRefs refs;

    ToolbarContainer active;
    ToolbarContainer secondary;
    ToolbarContainer selection;

    union {
        Tool *all_tools[TOOLBAR_TOOLS_LEN];
        struct {
            Tool *undo;
            Tool *redo;
            Tool *import;
        } tools;
    };
    
    union {
        Tool *all_selection_tools[TOOLBAR_TOOLS_LEN];
        struct {
            Tool *move;
            Tool *cut;
            Tool *copy;
            Tool *rot_left;
            Tool *rot_right;
            Tool *mirror_h;
            Tool *mirror_v;
            Tool *blend;
            Tool *paste;
            Tool *ok;
        } selection_tools;
    };

    struct {
        uColor_s active_bg_a, active_bg_b;
        uColor_s secondary_bg_a, secondary_bg_b;
        uColor_s selection_bg_a, selection_bg_b;
    } L;
} Toolbar;


Toolbar *toolbar_new(Camera_s *cam, Canvas *canvas,
        Brush *brush, Palette *palette, 
        uColor_s active_bg_a, uColor_s active_bg_b,
        uColor_s secondary_bg_a, uColor_s secondary_bg_b,
        uColor_s selection_bg_a, uColor_s selection_bg_b);

void toolbar_update(Toolbar *self, float dtime);

void toolbar_render(const Toolbar *self, const mat4 *cam_mat);

// returns toolbar_contains(pointer.pos.xy)
bool toolbar_pointer_event(Toolbar *self, ePointer_s pointer);

float toolbar_size(const Toolbar *self);

// returns true if pos is within the toolbar
bool toolbar_contains(const Toolbar *self, vec2 pos);

void toolbar_show_selection(Toolbar *self);

void toolbar_hide_selection(Toolbar *self);

#endif //PIXELC_TOOLBAR_H
