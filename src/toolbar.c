#include "r/ro_single.h"
#include "u/pose.h"
#include "m/float.h"
#include "m/uchar.h"
#include "camera.h"
#include "tooltip.h"
#include "toolbar.h"


#ifdef PIXELC_PREMIUM
#define TB_ACTIVE_BG_A "#555555"
#define TB_ACTIVE_BG_B "#444444"
#define TB_SELECTION_BG_A "#999999"
#define TB_SELECTION_BG_B "#888888"
#define TB_FRAMES_BG_A "#666666"
#define TB_FRAMES_BG_B "#555555"
#define TB_LAYER_BG_A "#777777"
#define TB_LAYER_BG_B "#666666"
#else
#define TB_ACTIVE_BG_A "#9999bb"
#define TB_ACTIVE_BG_B "#8888aa"
#define TB_SELECTION_BG_A "#99bb99"
#define TB_SELECTION_BG_B "#88aa88"
#define TB_FRAMES_BG_A "#bbbb99"
#define TB_FRAMES_BG_B "#aaaa88"
#define TB_LAYER_BG_A "#bb9999"
#define TB_LAYER_BG_B "#aa8888"
#endif


#define HOVER_TIME 1.0

struct Toolbar_Globals toolbar;

//
// private
//

static struct {
    enum selectionctrl_mode last_selectionctrl_mode;
} L;

static ToolbarContainer toolbar_container_new_invalid() {
    return (ToolbarContainer) {0};
}

static ToolbarContainer toolbar_container_new(Tool **tools, int tools_len, uColor_s bg_a, uColor_s bg_b) {
    ToolbarContainer self = {0};
    self.tools = s_malloc0(sizeof *tools * tools_len);
    memcpy(self.tools, tools, sizeof *tools * tools_len);
    self.tools_len = tools_len;
    self.container = u_container_new(tools_len, 0, 0);
    self.align = U_CONTAINER_ALIGN_START;

    uColor_s buf[4];
    buf[0] = buf[3] = bg_a;
    buf[1] = buf[2] = bg_b;
    rTexture tex = r_texture_new(2, 2, 1, 1, buf);
    r_texture_wrap_repeat(tex);
    self.bg = ro_single_new(tex);
    self.bg_packed = true;

    return self;
}

static void toolbar_container_kill(ToolbarContainer *self) {
    if (!toolbar_container_valid(self))
        return;
    s_free(self->tools);
    u_container_kill(&self->container);
    ro_single_kill(&self->bg);
    *self = (ToolbarContainer) {0};
}

static void toolbar_container_update(ToolbarContainer *self, float start_pos, float dtime) {
    if (!toolbar_container_valid(self))
        return;
    self->container.left = camera.RO.left;
    self->container.top = camera.RO.top;
    self->container.max_size = (vec2) {{camera_width(), camera_height()}};

    if (camera_is_portrait_mode()) {
        self->container.top -= start_pos;
        self->container.mode = U_CONTAINER_MODE_FREE_H;
        self->container.align_width = self->align;
        self->container.align_height = U_CONTAINER_ALIGN_START;
    } else {
        self->container.left += start_pos;
        self->container.mode = U_CONTAINER_MODE_FREE_V;
        self->container.align_width = U_CONTAINER_ALIGN_START;
        self->container.align_height = self->align;
    }

    for (int i = 0; i < self->tools_len; i++) {
        self->container.items[i].size = self->tools[i]->size;
    }

    u_container_update(&self->container);

    for (int i = 0; i < self->tools_len; i++) {
        self->tools[i]->in.pos = (vec2) {{
                                                 self->container.items[i].out.left,
                                                 self->container.items[i].out.top
                                         }};
    }

    for (int i = 0; i < self->tools_len; i++) {
        self->tools[i]->update(self->tools[i], dtime);
        
        if(self->tool_hover_times[i]>0) {
            self->tool_hover_times[i]-=dtime;
            if(self->tool_hover_times[i]<=0) {
                tooltip_set(self->tools[i]->name, self->tools[i]->tip);
            }
        }
    }

    // bg
    float bg_l = self->container.out.left;
    float bg_t = self->container.out.top;
    float bg_w = self->container.out.size.x;
    float bg_h = self->container.out.size.y;
    if(!self->bg_packed) {
        if (camera_is_portrait_mode()) {
            bg_l = camera.RO.left;
            bg_w = camera_width();
        } else {
            bg_t = camera.RO.top;
            bg_h = camera_height();
        }
    }

    self->bg.rect.pose = u_pose_new_aa(bg_l, bg_t, bg_w, bg_h);
    self->bg.rect.uv = u_pose_new(0, 0, bg_w / 2, bg_h / 2);
}

static void toolbar_container_render(const ToolbarContainer *self, const mat4 *cam_mat) {
    if (!toolbar_container_valid(self))
        return;
    ro_single_render(&self->bg, cam_mat);
    for (int i = 0; i < self->tools_len; i++) {
        self->tools[i]->render(self->tools[i], cam_mat);
    }
}

// returns true if pos is within the toolbar
static bool toolbar_container_contains(const ToolbarContainer *self, vec2 pos) {
    if (!toolbar_container_valid(self))
        return false;
    return u_pose_aa_contains(u_pose_new_aa(
            self->container.out.left,
            self->container.out.top,
            self->container.out.size.x,
            self->container.out.size.y), pos);
}

// returns NULL if not found
static Tool *toolbar_container_get_tool_by_pos(const ToolbarContainer *self, vec2 pos) {
    if (!toolbar_container_contains(self, pos))
        return NULL;
    for (int i = 0; i < self->tools_len; i++) {
        Tool *t = self->tools[i];
        if (pos.x >= t->in.pos.x
            && pos.y <= t->in.pos.y
            && pos.x <= t->in.pos.x + t->size.x
            && pos.y >= t->in.pos.y - t->size.y)
            return t;
    }
    return NULL;
}

// returns toolbar_contains(pointer.pos.xy)
static bool toolbar_container_pointer_event(ToolbarContainer *self, ePointer_s pointer) {
    if (!toolbar_container_valid(self))
        return false;
    bool contains = toolbar_container_contains(self, pointer.pos.xy);
    if (pointer.action != E_POINTER_UP && !contains)
        return false;

    float x = pointer.pos.x;
    float y = pointer.pos.y;
    for (int i = 0; i < self->tools_len; i++) {
        const uContainerItem_s *item = &self->container.items[i];
        bool in_tool = x>=item->out.left 
                && x<=item->out.left+item->size.x
                && y<=item->out.top
                && y>=item->out.top-item->size.y;
                
        if(in_tool && pointer.action == E_POINTER_DOWN) {
            tooltip_set(self->tools[i]->name, self->tools[i]->tip);
        }
        
        if(in_tool && pointer.action == E_POINTER_HOVER) {
            if(self->tool_hover_times[i]<=0) {
                self->tool_hover_times[i] = HOVER_TIME;
            } 
        } else {
            self->tool_hover_times[i] = 0;
        }
        self->tools[i]->pointer_event(self->tools[i], pointer);
    }

    return contains;
}

float toolbar_constainer_size(const ToolbarContainer *self) {
    if (!toolbar_container_valid(self))
        return 0;
    return camera_is_portrait_mode() ? self->container.out.size.y : self->container.out.size.x;
}


static void hide_selection() {
    s_log("toolbar: hide_selection");
    toolbar_container_kill(&toolbar.selection);
}

static void show_selection_set() {
    s_log("toolbar: show_selection_set");
    toolbar_container_kill(&toolbar.selection);
    toolbar.selection = toolbar_container_new(
            toolbar.selection_set_tools,
            toolbar.selection_set_tools_size,
            u_color_from_hex(TB_SELECTION_BG_A),
            u_color_from_hex(TB_SELECTION_BG_B));
    toolbar.selection.align = U_CONTAINER_ALIGN_CENTER;

}

static void show_selection_move() {
    s_log("toolbar: show_selection_move");
    toolbar_container_kill(&toolbar.selection);
    toolbar.selection = toolbar_container_new(
            toolbar.selection_paste_tools,
            toolbar.selection_paste_tools_size,
            u_color_from_hex(TB_SELECTION_BG_A),
            u_color_from_hex(TB_SELECTION_BG_B));
    toolbar.selection.align = U_CONTAINER_ALIGN_CENTER;
}


static void add_tool(Tool *tool) {
    s_assume(toolbar.tools_size<TOOLBAR_MAX_TOOLS, "too many tools?");
    toolbar.tools[toolbar.tools_size++] = tool;
}

static void add_frames_tool(Tool *tool) {
    s_assume(toolbar.frames_tools_size<TOOLBAR_MAX_TOOLS, "too many tools?");
    toolbar.frames_tools[toolbar.frames_tools_size++] = tool;
}

static void add_layer_tool(Tool *tool) {
    s_assume(toolbar.layer_tools_size<TOOLBAR_MAX_TOOLS, "too many tools?");
    toolbar.layer_tools[toolbar.layer_tools_size++] = tool;
}

static void add_selection_set_tool(Tool *tool) {
    s_assume(toolbar.selection_set_tools_size<TOOLBAR_MAX_TOOLS, "too many tools?");
    toolbar.selection_set_tools[toolbar.selection_set_tools_size++] = tool;
}

static void add_selection_paste_tool(Tool *tool) {
    s_assume(toolbar.selection_paste_tools_size<TOOLBAR_MAX_TOOLS, "too many tools?");
    toolbar.selection_paste_tools[toolbar.selection_paste_tools_size++] = tool;
}


//
// public
//

void toolbar_init() {

    add_tool(tool_new_tooltip());
    add_tool(tool_new_save());
    add_tool(tool_new_import());
    add_tool(tool_new_display());
    add_tool(tool_new_size());
    add_tool(tool_new_tile());
    add_tool(tool_new_tab());
    add_tool(tool_new_frames());
    add_tool(tool_new_layer());
    add_tool(tool_new_camera());
    add_tool(tool_new_grid());
    add_tool(tool_new_clear());
    add_tool(tool_new_undo());
    add_tool(tool_new_redo());
    add_tool(tool_new_selection());
    add_tool(tool_new_find());
    add_tool(tool_new_rgb());
    add_tool(tool_new_shading());
    add_tool(tool_new_secondary_color());

    add_tool(tool_new_mode_pipette());
    add_tool(tool_new_mode_none());
    add_tool(tool_new_mode_dot());
    add_tool(tool_new_mode_free());
    add_tool(tool_new_mode_line());
    add_tool(tool_new_mode_rect());
    add_tool(tool_new_mode_circle());
    add_tool(tool_new_mode_dither());
    add_tool(tool_new_mode_dither_inv());
    add_tool(tool_new_mode_fill());
    add_tool(tool_new_mode_fill8());
    add_tool(tool_new_mode_replace());
    add_tool(tool_new_mode_outline());

    add_tool(tool_new_kernel());

    for(int i=0; i<TOOL_FRAMES_SELECT_NUM; i++) {
        add_frames_tool(tool_new_frames_select(i));
    }
    add_frames_tool(tool_new_frames_blend());
    add_frames_tool(tool_new_frames_add());

    for(int i=0; i<TOOL_LAYER_SELECT_NUM; i++) {
        add_layer_tool(tool_new_layer_select(i));
    }
    add_layer_tool(tool_new_layer_blend());
    add_layer_tool(tool_new_layer_add());

    

    add_selection_set_tool(tool_new_selection_set_move());
    add_selection_set_tool(tool_new_selection_set_copy());
    add_selection_set_tool(tool_new_selection_set_cut());
    add_selection_set_tool(tool_new_selection_set_crop());

    add_selection_paste_tool(tool_new_selection_paste_rotate_l());
    add_selection_paste_tool(tool_new_selection_paste_rotate_r());
    add_selection_paste_tool(tool_new_selection_paste_mirror_v());
    add_selection_paste_tool(tool_new_selection_paste_mirror_h());
    add_selection_paste_tool(tool_new_selection_paste_color());
     add_selection_paste_tool(tool_new_selection_paste_blend());
    add_selection_paste_tool(tool_new_selection_paste_copy());
    add_selection_paste_tool(tool_new_selection_paste_ok());
    
    toolbar.active = toolbar_container_new(toolbar.tools, toolbar.tools_size,
            u_color_from_hex(TB_ACTIVE_BG_A),
            u_color_from_hex(TB_ACTIVE_BG_B));
    toolbar.active.align = U_CONTAINER_ALIGN_CENTER;
    toolbar.active.bg_packed = false;
}

void toolbar_update(float dtime) {
    enum selectionctrl_mode sc_mode = selectionctrl.mode;
    if (sc_mode != L.last_selectionctrl_mode) {
        L.last_selectionctrl_mode = sc_mode;
        switch (sc_mode) {
            case SELECTIONCTRL_NONE:
            case SELECTIONCTRL_ACQUIRE:
                hide_selection();
                break;
            case SELECTIONCTRL_SET:
            case SELECTIONCTRL_COPY:
            case SELECTIONCTRL_CUT:
                show_selection_set();
                break;
            case SELECTIONCTRL_PASTE:
                show_selection_move();
                break;
            default:
                break;
        }
    }

    float start_pos = 0;
    toolbar_container_update(&toolbar.active, start_pos, dtime);
    start_pos += toolbar_constainer_size(&toolbar.active);

    toolbar_container_update(&toolbar.frames, start_pos, dtime);
    start_pos += toolbar_constainer_size(&toolbar.frames);

    toolbar_container_update(&toolbar.layer, start_pos, dtime);
    start_pos += toolbar_constainer_size(&toolbar.layer);
     

    toolbar_container_update(&toolbar.selection, start_pos, dtime);
}

void toolbar_render(const mat4 *cam_mat) {
    toolbar_container_render(&toolbar.active, cam_mat);
    toolbar_container_render(&toolbar.frames, cam_mat);
    toolbar_container_render(&toolbar.layer, cam_mat);
    toolbar_container_render(&toolbar.selection, cam_mat);
}

// returns toolbar_contains(pointer.pos.xy)
bool toolbar_pointer_event(ePointer_s pointer) {
    if (pointer.id != 0)
        return false;

    bool contains = false;
    bool go = true;
    bool set_go = pointer.action == E_POINTER_UP ? true : false;
    if (toolbar_container_pointer_event(&toolbar.active, pointer)) {
        contains = true;
        go = set_go;
    }
    if (go && toolbar_container_pointer_event(&toolbar.frames, pointer)) {
        contains = true;
        go = set_go;
    }
    if (go && toolbar_container_pointer_event(&toolbar.layer, pointer)) {
        contains = true;
        go = set_go;
    }
    if (go && toolbar_container_pointer_event(&toolbar.selection, pointer)) {
        contains = true;
    }
    return contains;
}

float toolbar_size() {
    return toolbar_constainer_size(&toolbar.active)
           + toolbar_constainer_size(&toolbar.frames)
           + toolbar_constainer_size(&toolbar.layer)
           + toolbar_constainer_size(&toolbar.selection);
}

bool toolbar_contains(vec2 pos) {
    return toolbar_container_contains(&toolbar.active, pos)
           || toolbar_container_contains(&toolbar.frames, pos)
           || toolbar_container_contains(&toolbar.layer, pos)
           || toolbar_container_contains(&toolbar.selection, pos);
}

Tool *toolbar_get_tool_by_pos(vec2 pos) {
    Tool *t;
    t = toolbar_container_get_tool_by_pos(&toolbar.active, pos);
    if (t)
        return t;
         
    t = toolbar_container_get_tool_by_pos(&toolbar.frames, pos);
    if (t)
        return t;

    t = toolbar_container_get_tool_by_pos(&toolbar.layer, pos);
    if (t)
        return t;

    t = toolbar_container_get_tool_by_pos(&toolbar.selection, pos);
    return t;
}

void toolbar_hide_frames() {
    s_log("hide");
    toolbar_container_kill(&toolbar.frames);
}

void toolbar_show_frames() {
    s_log("show");
    toolbar_container_kill(&toolbar.frames);
    toolbar.frames = toolbar_container_new(
            toolbar.frames_tools,
            toolbar.frames_tools_size,
            u_color_from_hex(TB_FRAMES_BG_A),
            u_color_from_hex(TB_FRAMES_BG_B));
    toolbar.frames.align = U_CONTAINER_ALIGN_CENTER;
}

void toolbar_hide_layer() {
    s_log("hide");
    toolbar_container_kill(&toolbar.layer);
}

void toolbar_show_layer() {
    s_log("show");
    toolbar_container_kill(&toolbar.layer);
    toolbar.layer = toolbar_container_new(
            toolbar.layer_tools,
            toolbar.layer_tools_size,
            u_color_from_hex(TB_LAYER_BG_A),
            u_color_from_hex(TB_LAYER_BG_B));
    toolbar.layer.align = U_CONTAINER_ALIGN_CENTER;
}


