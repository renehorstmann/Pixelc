#include "u/image.h"
#include "u/pose.h"
#include "u/button.h"
#include "dialog.h"
#include "selectionctrl.h"
#include "feedback.h"
#include "tool.h"

//
// private
//

_Static_assert(sizeof(TOOL_BUTTON_ADDITIONAL_DATA_SIZE) >= sizeof(float), "wtf");

static void pointer_event(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
    if (u_button_pressed(&self->ro.rect, pointer)) {
        s_log("tool import");
        dialog_create_import();
    }
}

static bool is_active(struct Tool *super, float dtime) {
    ToolButton *self = (ToolButton *) super;
    u_button_set_pressed(&self->ro.rect, strcmp(dialog.id, "import") == 0);
    // always actice
    return true;
}

//
// public
//

Tool *tool_new_import() {
    return tool_button_new("import",
                           "Opens the\n"
                           "import dialog\n\n"
                           "To load a\n"
                           "PNG image",
                           "res/button_import.png",
                           pointer_event,
                           is_active);
}
