#ifndef PIXELC_DIALOG_H
#define PIXELC_DIALOG_H

#include "e/input.h"
#include "r/ro_single.h"
#include "r/ro_text.h"
#include "u/color.h"
#include "mathc/types/float.h"

#define DIALOG_MAX_TITLE_LEN 16

#define DIALOG_WIDTH 120
#define DIALOG_LEFT -60
#define DIALOG_TOP 60

typedef void (*dialog_on_action_cb)(bool ok);

typedef void (*dialog_kill_fun)(void *impl);

typedef void (*dialog_update_fun)(float dtime);

typedef void (*dialog_render_fun)(const mat4 *cam_mat);

typedef bool (*dialog_pointer_event_fun)(ePointer_s pointer);


struct Dialog_Globals {
    char id[DIALOG_MAX_TITLE_LEN];
    void *impl;
    void *user_data;

    bool textinput_active;

    float impl_height;

    RoSingle bg;
    RoSingle bg_shadow;
    RoText title;
    RoText title_shadow;
    RoSingle cancel, ok;

    // vtable
    // only shows the ok/cancel button, if available
    dialog_on_action_cb opt_on_ok_cb;
    dialog_on_action_cb opt_on_cancel_cb;

    dialog_kill_fun kill;
    dialog_update_fun update;
    dialog_render_fun render;
    dialog_pointer_event_fun pointer_event;
};
extern struct Dialog_Globals dialog;


static bool dialog_valid() {
    return *dialog.id != '\0' && dialog.impl && dialog.kill && dialog.update && dialog.render && dialog.pointer_event;
}

void dialog_init();

void dialog_update(float dtime);

void dialog_render(const mat4 *cam_mat);

bool dialog_pointer_event(ePointer_s pointer);

// kills the internal impl of the custom dialog
void dialog_hide();

void dialog_set_bg_color(uColor_s a, uColor_s b);

void dialog_set_title(const char *title_id, vec4 color);


//
// dialogs
//

void dialog_create_tooltip();

void dialog_create_canvas_size();

void dialog_create_display();

void dialog_create_image_upload();

#endif //PIXELC_DIALOG_H
