#ifndef PIXELC_TOOLBAR_H
#define PIXELC_TOOLBAR_H

#include "r/ro_types.h"
#include "u/color.h"
#include "u/container.h"
#include "tool.h"

#define TOOLBAR_TOOLS_LEN 4
#define TOOLBAR_SELECTION_SET_TOOLS_LEN 3
#define TOOLBAR_SELECTION_PASTE_TOOLS_LEN 2


typedef struct {
    Tool **tools;
    int tools_len;
    
    uContainer container;
    enum u_container_align align;
    
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
            Tool *selection;
        } tools;
    };
    
    union {
        Tool *all_selection_set_tools[TOOLBAR_SELECTION_SET_TOOLS_LEN];
        struct {
            Tool *move;
            Tool *cut;
            Tool *copy;
        } selection_set_tools;
    };
    
    union {
        Tool *all_selection_paste_tools[TOOLBAR_SELECTION_PASTE_TOOLS_LEN];
        struct {
            Tool *copy;
            Tool *ok;
        } selection_paste_tools;
    };

    struct {
        enum selectionctrl_mode last_selectionctrl_mode;
        
        uColor_s active_bg_a, active_bg_b;
        uColor_s secondary_bg_a, secondary_bg_b;
        uColor_s selection_bg_a, selection_bg_b;
    } L;
} Toolbar;


Toolbar *toolbar_new(Camera_s *cam, Canvas *canvas,
        Brush *brush, Palette *palette, 
        SelectionCtrl *selectionctrl,
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

#endif //PIXELC_TOOLBAR_H
