#include "e/io.h"
#include "u/image.h"
#include "button.h"
#include "canvas.h"
#include "tool.h"

//
// private
//

static void pointer_event(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
    if (self->active && button_clicked(&self->ro.rect, pointer)) {
        log_info("tool save");
        u_image_save_file(canvas.RO.image, "image.png");
        e_io_offer_file_as_download("image.png");
    }
}

//
// public
//

Tool *tool_new_save() {
    return tool_button_new("save",
                           "saves the canvas\nas image.png",
                           "res/button_save.png",
                           pointer_event,
                           NULL);
}
