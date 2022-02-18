#ifndef PIXELC_DIALOG_H
#define PIXELC_DIALOG_H

#include "e/input.h"
#include "r/ro_types.h"
#include "u/color.h"
#include "mathc/types/float.h"

#define DIALOG_MAX_TITLE_LEN 16

#define DIALOG_WIDTH 120
#define DIALOG_LEFT -60
#define DIALOG_TOP 60

struct eWindow;
struct eInput;
struct Dialog;
struct Toolbar;
struct Palette;
struct Canvas;

typedef void (*dialog_on_action_cb)(struct Dialog *self, bool ok);
typedef void (*dialog_kill_fun)(void *impl);
typedef void (*dialog_update_fun)(struct Dialog *self, float dtime);
typedef void (*dialog_render_fun)(struct Dialog *self, const mat4 *cam_mat);
typedef bool (*dialog_pointer_event_fun)(struct Dialog *self, ePointer_s pointer);

typedef struct Dialog {
    char id[DIALOG_MAX_TITLE_LEN];
    void *impl;
    void *user_data;

    struct {
        float impl_height;
    } in;

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
} Dialog;

static bool dialog_valid(const Dialog *self) {
    return *self->id != '\0' && self->impl && self->kill && self->update && self->render && self->pointer_event;
}

Dialog *dialog_new();

void dialog_update(Dialog *self, float dtime);

void dialog_render(Dialog *self, const mat4 *cam_mat);

bool dialog_pointer_event(Dialog *self, ePointer_s pointer);

// kills the internal impl of the custom dialog
void dialog_hide(Dialog *self);

void dialog_set_bg_color(Dialog *self, uColor_s a, uColor_s b);

void dialog_set_title(Dialog *self, const char *title_id, vec4 color);


//
// dialogs
//

void dialog_create_delete(Dialog *self, const char *msg, dialog_on_action_cb on_action_cb, void *user_data);

void dialog_create_upload(Dialog *self, const char *msg, dialog_pointer_event_fun on_action_cb, void *user_data);

void dialog_create_tooltip(Dialog *self, const struct Toolbar *toolbar, const struct Palette *palette);

void dialog_create_canvas_size(Dialog *self, const struct eWindow *window, struct eInput *input_ref, struct Canvas *canvas);

#endif //PIXELC_DIALOG_H
