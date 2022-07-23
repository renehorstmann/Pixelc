#include "r/ro_single.h"
#include "u/pose.h"
#include "m/float.h"
#include "m/uchar.h"
#include "camera.h"
#include "toolbar.h"


#define TB_ACTIVE_BG_A "#9999bb"
#define TB_ACTIVE_BG_B "#888888"
#define TB_SELECTION_BG_A "#99bb99"
#define TB_SELECTION_BG_B "#888888"
#define TB_FRAMES_BG_A "#bbbb99"
#define TB_FRAMES_BG_B "#888888"
#define TB_LAYER_BG_A "#bb9999"
#define TB_LAYER_BG_B "#888888"

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
    }

    // bg
    float bg_w, bg_h;
    if (camera_is_portrait_mode()) {
        bg_w = camera_width();
        bg_h = self->container.out.size.y;
    } else {
        bg_w = self->container.out.size.x;
        bg_h = camera_height();
    }


    bg_w = self->container.out.size.x;
    bg_h = self->container.out.size.y;
    self->bg.rect.pose = u_pose_new_aa(self->container.out.left, self->container.out.top, bg_w, bg_h);
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

    for (int i = 0; i < self->tools_len; i++) {
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
            toolbar.all_selection_set_tools,
            TOOLBAR_SELECTION_SET_TOOLS_LEN,
            u_color_from_hex(TB_SELECTION_BG_A),
            u_color_from_hex(TB_SELECTION_BG_B));
    toolbar.selection.align = U_CONTAINER_ALIGN_CENTER;

}

static void show_selection_move() {
    s_log("toolbar: show_selection_move");
    toolbar_container_kill(&toolbar.selection);
    toolbar.selection = toolbar_container_new(
            toolbar.all_selection_paste_tools,
            TOOLBAR_SELECTION_PASTE_TOOLS_LEN,
            u_color_from_hex(TB_SELECTION_BG_A),
            u_color_from_hex(TB_SELECTION_BG_B));
    toolbar.selection.align = U_CONTAINER_ALIGN_CENTER;
}


//
// public
//

void toolbar_init() {

    toolbar.tools.tooltip = tool_new_tooltip();
    toolbar.tools.save = tool_new_save();
    toolbar.tools.import = tool_new_import();
    toolbar.tools.clear = tool_new_clear();
    toolbar.tools.undo = tool_new_undo();
    toolbar.tools.redo = tool_new_redo();
    toolbar.tools.selection = tool_new_selection();
    toolbar.tools.layer = tool_new_layer();
    toolbar.tools.frames = tool_new_frames();
    toolbar.tools.tab = tool_new_tab();
    toolbar.tools.kernel = tool_new_kernel();
    toolbar.tools.rgb = tool_new_rgb();
    toolbar.tools.secondary_color = tool_new_secondary_color();
    toolbar.tools.shading = tool_new_shading();
    toolbar.tools.camera = tool_new_camera();
    toolbar.tools.grid = tool_new_grid();
    toolbar.tools.size = tool_new_size();
    toolbar.tools.display = tool_new_display();

    toolbar.tools.mode_none = tool_new_mode_none();
    toolbar.tools.mode_free = tool_new_mode_free();
    toolbar.tools.mode_dot = tool_new_mode_dot();
    toolbar.tools.mode_line = tool_new_mode_line();
    toolbar.tools.mode_rect = tool_new_mode_rect();
    toolbar.tools.mode_circle = tool_new_mode_circle();
    toolbar.tools.mode_dither = tool_new_mode_dither();
    toolbar.tools.mode_dither_inv = tool_new_mode_dither_inv();
    toolbar.tools.mode_fill = tool_new_mode_fill();
    toolbar.tools.mode_fill8 = tool_new_mode_fill8();
    toolbar.tools.mode_replace = tool_new_mode_replace();
    toolbar.tools.mode_pipette = tool_new_mode_pipette();

    for(int i=0; i<TOOL_FRAMES_SELECT_NUM; i++) {
        toolbar.frames_tools.select[i] = tool_new_frames_select(i);
    }
    toolbar.frames_tools.blend = tool_new_frames_blend();
    toolbar.frames_tools.add = tool_new_frames_add();

    for(int i=0; i<TOOL_LAYER_SELECT_NUM; i++) {
        toolbar.layer_tools.select[i] = tool_new_layer_select(i);
    }
    toolbar.layer_tools.blend = tool_new_layer_blend();
    toolbar.layer_tools.add = tool_new_layer_add();

    

    toolbar.selection_set_tools.move = tool_new_selection_set_move();
    toolbar.selection_set_tools.copy = tool_new_selection_set_copy();
    toolbar.selection_set_tools.cut = tool_new_selection_set_cut();
    toolbar.selection_set_tools.crop = tool_new_selection_set_crop();

    toolbar.selection_paste_tools.rotate_l = tool_new_selection_paste_rotate_l();
    toolbar.selection_paste_tools.rotate_r = tool_new_selection_paste_rotate_r();
    toolbar.selection_paste_tools.mirror_v = tool_new_selection_paste_mirror_v();
    toolbar.selection_paste_tools.mirror_h = tool_new_selection_paste_mirror_h();
    toolbar.selection_paste_tools.blend = tool_new_selection_paste_blend();
    toolbar.selection_paste_tools.copy = tool_new_selection_paste_copy();
    toolbar.selection_paste_tools.ok = tool_new_selection_paste_ok();
    
    toolbar.active = toolbar_container_new(toolbar.all_tools, TOOLBAR_TOOLS_LEN, 
            u_color_from_hex(TB_ACTIVE_BG_A),
            u_color_from_hex(TB_ACTIVE_BG_B));
    toolbar.active.align = U_CONTAINER_ALIGN_CENTER;
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
            toolbar.all_frames_tools,
            TOOLBAR_FRAMES_TOOLS_LEN,
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
            toolbar.all_layer_tools,
            TOOLBAR_LAYER_TOOLS_LEN,
            u_color_from_hex(TB_LAYER_BG_A),
            u_color_from_hex(TB_LAYER_BG_B));
    toolbar.layer.align = U_CONTAINER_ALIGN_CENTER;
}


