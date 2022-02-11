#ifndef PIXELC_TOOL_H
#define PIXELC_TOOL_H

#include "e/input.h"
#include "r/ro_types.h"
#include "camera.h"
#include "canvas.h"
#include "brush.h"
#include "palette.h"
#include "selectionctrl.h"

#define TOOL_NAME_LEN 16
#define TOOL_TIP_LEN 128


typedef struct {
    Camera_s *cam;
    Canvas *canvas;
    Brush *brush;
    Palette *palette;
    SelectionCtrl *selectionctrl;
} ToolRefs;


struct Tool;

typedef void (*tool_kill_fun)(struct Tool **self_ptr);

typedef void (*tool_update_fun)(struct Tool *self, float dtime, ToolRefs refs);

typedef void (*tool_render_fun)(const struct Tool *self, const mat4 *cam_mat);

typedef void (*tool_pointer_event_fun)(struct Tool *self, ePointer_s pointer, ToolRefs refs);


typedef struct Tool {
    char name[TOOL_NAME_LEN];
    char tip[TOOL_TIP_LEN];
    
    vec2 size;
    
    struct {
        // as left, top
        vec2 pos;
    } in;
    
    // vtable
    tool_kill_fun kill;
    tool_update_fun update;
    tool_render_fun render;
    tool_pointer_event_fun pointer_event;
} Tool;


typedef bool (*tool_button_active)(Tool *self, float dtime, ToolRefs refs);

typedef struct {
    Tool super;
    RoSingle ro;
    vec4 padding_lrbt; // left, right, bottom, top
    bool active;
    // vtable
    tool_button_active opt_is_active;
} ToolButton;

// Returns a ToolButton
Tool *tool_button_new(const char *name, 
        const char *tip, 
        const char *tex_file, 
        tool_pointer_event_fun pointer_event,
        tool_button_active opt_is_active);
        
//
// tool list
//

Tool *tool_new_undo();
Tool *tool_new_redo();
Tool *tool_new_import();
Tool *tool_new_selection();

Tool *tool_new_selection_set_move();
Tool *tool_new_selection_set_copy();
Tool *tool_new_selection_set_cut();

Tool *tool_new_selection_paste_copy();
Tool *tool_new_selection_paste_ok();


#endif //PIXELC_TOOL_H
