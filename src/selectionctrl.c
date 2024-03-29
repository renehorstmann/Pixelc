#include "r/ro_batch.h"
#include "r/ro_text.h"
#include "u/pose.h"
#include "m/int.h"
#include "canvas.h"
#include "palette.h"
#include "camera.h"
#include "brush.h"
#include "selectionctrl.h"


#define TIP_TEXT_LENGTH 128


struct SelectionCtrl_Globals selectionctrl;

//
// private
//

static struct {
    RoText title;
    RoText tip;
    vec2 title_size;
    vec2 tip_size;

    RoBatch border;

    bool moving;
    ivec2 pos;
    ivec2 move_start_selection_lt;
    ivec2 move_start_position;

    bool was_allowed;
    
    bool prev_use_brush_color;
    uColor_s prev_brush_color;
} L;

static void update_canvas() {
    Selection *s = selectionctrl.selection;
    if (!s)
        return;
    canvas_reload();
    selection_paste(s, canvas.RO.image, canvas.RO.current_image_layer);
}

static void setup_border() {
    int x = 0, y = 0, w = 0, h = 0;
    if (selectionctrl.selection) {
        x = selectionctrl.selection->left;
        y = selectionctrl.selection->top;
        w = selectionctrl.selection->cols;
        h = selectionctrl.selection->rows;
    }

    vec2 scale = canvas_get_unit_scale();
    float stretch = sca_max(1, sca_max(w, h) / 10);
    
    // left
    L.border.rects[0].pose = u_pose_new_aa(
            (x-stretch) * scale.x,
            -y * scale.y,
            scale.x * stretch,
            scale.y * h);
            
    // top
    L.border.rects[1].pose = u_pose_new_aa(
            x * scale.x,
            -(y-stretch) * scale.y,
            scale.x * w,
            scale.y * stretch);
    
    // right
    L.border.rects[2].pose = u_pose_new_aa(
            (x+w) * scale.x,
            -y * scale.y,
            scale.x * stretch,
            scale.y * h);
            

    // bottom
    L.border.rects[3].pose = u_pose_new_aa(
            x * scale.x,
            -(y+h) * scale.y,
            scale.x * w,
            scale.y * stretch);


    ro_batch_update(&L.border);
}

static void setup_selection(ePointer_s pointer) {
    uImage img = canvas.RO.image;

    if (selectionctrl.selection && pointer.action == E_POINTER_UP) {
        selectionctrl.mode = SELECTIONCTRL_SET;
        return;
    }
    ivec2 cr = canvas_get_cr(pointer.pos.xy);
    if (L.pos.x < 0 && !u_image_contains(img, cr.x, cr.y))
        return;

    cr.x = isca_clamp(cr.x, 0, img.cols - 1);
    cr.y = isca_clamp(cr.y, 0, img.rows - 1);

    if (L.pos.x < 0) {
        if (pointer.action == E_POINTER_DOWN) {
            L.pos = cr;
            selectionctrl.show_copy_cut = true;
        }
    }

    if (L.pos.x < 0)
        return;

    int left = cr.x < L.pos.x ? cr.x : L.pos.x;
    int top = cr.y < L.pos.y ? cr.y : L.pos.y;
    int cols = 1 + abs(cr.x - L.pos.x);
    int rows = 1 + abs(cr.y - L.pos.y);

    if (selectionctrl.selection) {
        selectionctrl.selection->left = left;
        selectionctrl.selection->top = top;
        selectionctrl.selection->cols = cols;
        selectionctrl.selection->rows = rows;
    } else {
        selectionctrl.selection = selection_new(left, top, cols, rows);
    }
}

static void move_selection(ePointer_s pointer) {
    uImage img = canvas.RO.image;
    int layer = canvas.RO.current_image_layer;

    ivec2 cr = canvas_get_cr(pointer.pos.xy);

    if (pointer.action == E_POINTER_UP)
        L.moving = false;
    else if (pointer.action == E_POINTER_DOWN)
        L.moving = true;

    if (!L.moving)
        return;

    if (pointer.action == E_POINTER_DOWN) {
        if (!selection_contains(selectionctrl.selection, cr.x, cr.y)) {
            // touched outside the selection, so pushing the selection center into that position
            selectionctrl.selection->left = cr.x - selectionctrl.selection->cols / 2;
            selectionctrl.selection->top = cr.y - selectionctrl.selection->rows / 2;
        }
        L.move_start_selection_lt = (ivec2) {{selectionctrl.selection->left, selectionctrl.selection->top}};
        L.move_start_position = cr;
    }

    ivec2 grab_diff = ivec2_sub_vec(cr, L.move_start_position);
    selectionctrl.selection->left = L.move_start_selection_lt.x + grab_diff.x;
    selectionctrl.selection->top = L.move_start_selection_lt.y + grab_diff.y;

    canvas_reload();
    selection_paste(selectionctrl.selection, img, layer);
}


//
// public
//

void selectionctrl_init() {
    L.title = ro_text_new_font55(9);
    L.title_size = ro_text_set_text(&L.title, "Selection");
    u_pose_set_size(&L.title.pose, 1, 2);

    L.tip = ro_text_new_font85(TIP_TEXT_LENGTH);

    L.border = ro_batch_new(4,
                            r_texture_new_file(2, 2, "res/selection_border.png"));
    for (int i = 0; i < L.border.num; i++) {
        L.border.rects[i].color = u_color_to_vec4(u_color_from_hex("#357985"));
        L.border.rects[i].sprite.x = i%2;
        L.border.rects[i].sprite.y = i/2;
    }

    // may be reset by a mod
    selectionctrl.allowed = true;
}

void selectionctrl_update(float dtime) {
    if(selectionctrl.selection) {
        selectionctrl.selection->apply_color = selectionctrl.use_brush_color;
        selectionctrl.selection->color = u_color_to_vec4(brush.current_color);
        if(L.prev_use_brush_color != selectionctrl.use_brush_color || !u_color_equals(L.prev_brush_color, brush.current_color)) {
            update_canvas();
        }
        L.prev_use_brush_color = selectionctrl.use_brush_color;
        L.prev_brush_color = brush.current_color;
    }
    
    if(L.was_allowed != selectionctrl.allowed) {
        selectionctrl_stop();
    }
    L.was_allowed = selectionctrl.allowed;
    if(!selectionctrl.allowed)
        return;

    if (selectionctrl.mode == SELECTIONCTRL_COPY
        || selectionctrl.mode == SELECTIONCTRL_CUT) {
        uImage img = canvas.RO.image;
        int layer = canvas.RO.current_image_layer;

        if (selectionctrl.mode == SELECTIONCTRL_COPY)
            selection_copy(selectionctrl.selection, img, layer);
        else
            selection_cut(selectionctrl.selection, img, layer, U_COLOR_TRANSPARENT);

        canvas_save();
        selection_paste(selectionctrl.selection, img, layer);
        selectionctrl.mode = SELECTIONCTRL_PASTE;

        selectionctrl.show_ok = true;
    }
    setup_border();

    int x, y, cols, rows;
    if(selectionctrl.selection) {
        x = selectionctrl.selection->left;
        y = selectionctrl.selection->top;
        cols = selectionctrl.selection->cols;
        rows = selectionctrl.selection->rows;
    } else {
        x = y = cols = rows = 0;
    }

    char buf[TIP_TEXT_LENGTH];
    snprintf(buf, sizeof buf, "x: %i\ny: %i\ncols: %i\nrows: %i", x, y, cols, rows);
    L.tip_size = ro_text_set_text(&L.tip, buf);


    float phs = palette_get_hud_size();

    float w = s_max(L.title_size.x, L.tip_size.x);
    float h = L.title_size.y*2 + L.tip_size.y + 2;

    float left, top;
    if(camera_is_portrait_mode()) {
        left = camera.RO.left + 6;
        top = camera.RO.bottom + phs + h + 2;
    } else {
        left = camera.RO.right - phs - w - 2;
        top = camera.RO.bottom + h + 2;
    }

    u_pose_set_xy(&L.title.pose, left, top);
    u_pose_set_xy(&L.tip.pose, left, top-L.title_size.y*2-2);
}

void selectionctrl_render(const mat4 *hud_cam_mat, const mat4 *canvas_cam_mat) {
    if (!selectionctrl.selection || !selectionctrl.allowed)
        return;

    u_pose_shift_xy(&L.title.pose, 1, -1);
    u_pose_shift_xy(&L.tip.pose, 1, -1);
    ro_text_set_color(&L.title, (vec4) {{0.3, 0.3, 0.3, 0.5}});
    ro_text_set_color(&L.tip, (vec4) {{0.2, 0.2, 0.2, 0.5}});

    ro_text_render(&L.title, hud_cam_mat);
    ro_text_render(&L.tip, hud_cam_mat);

    u_pose_shift_xy(&L.title.pose, -1, 1);
    u_pose_shift_xy(&L.tip.pose, -1, 1);
    ro_text_set_color(&L.title, (vec4) {{1, 1, 1, 1}});
    ro_text_set_color(&L.tip, (vec4) {{0.95, 0.95, 0.95, 1}});

    ro_text_render(&L.title, hud_cam_mat);
    ro_text_render(&L.tip, hud_cam_mat);

    ro_batch_render(&L.border, canvas_cam_mat, false);
}

bool selectionctrl_pointer_event(ePointer_s pointer) {
    if (pointer.id != 0
        || !selectionctrl.allowed
        || selectionctrl.mode == SELECTIONCTRL_NONE
        || selectionctrl.mode == SELECTIONCTRL_SET)
        return false;

    if (selectionctrl.mode == SELECTIONCTRL_ACQUIRE)
        setup_selection(pointer);
    else
        move_selection(pointer);
    return true;
}

void selectionctrl_stop() {
    s_log("stop");
    L.pos = (ivec2) {{-1, -1}};
    selection_kill(&selectionctrl.selection);
    selectionctrl.mode = SELECTIONCTRL_NONE;
}

void selectionctrl_acquire() {
    s_log("acquire");
    if(!selectionctrl.allowed) {
        s_log("not allowed");
        return;
    }
    L.pos = (ivec2) {{-1, -1}};
    selection_kill(&selectionctrl.selection);
    selectionctrl.mode = SELECTIONCTRL_ACQUIRE;
}

void selectionctrl_paste_image(uImage img) {
    s_log("paste_image");
    if(!selectionctrl.allowed) {
        s_log("not allowed");
        return;
    }
    L.pos = (ivec2) {{-1, -1}};
    selection_kill(&selectionctrl.selection);
    selectionctrl.selection = selection_new(0, 0, img.cols, img.rows);
    selection_copy(selectionctrl.selection, img, 0);
    canvas_reload();
    selection_paste(selectionctrl.selection, canvas.RO.image, canvas.RO.current_image_layer);
    selectionctrl.mode = SELECTIONCTRL_PASTE;
}


