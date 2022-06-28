#include "e/io.h"
#include "u/image.h"
#include "m/int.h"
#include "u/button.h"
#include "canvas.h"
#include "tool.h"

#define HD_MIN_SIZE 1024

//
// private
//


static void pointer_event(struct Tool *super, ePointer_s pointer) {
    ToolButton *self = (ToolButton *) super;
    if (self->active && u_button_clicked(&self->ro.rect, pointer)) {
        s_log("tool save hd");
        uImage img = canvas.RO.image;
        int scale_w = sca_ceil((float) HD_MIN_SIZE / img.cols);
        int scale_h = sca_ceil((float) HD_MIN_SIZE / img.rows);
        int scale = isca_max(scale_w, scale_h);
        img = u_image_new_clone_scaled(img.cols * scale, img.rows * scale, false, img);
        u_image_save_file(img, "image_hd.png");
        u_image_kill(&img);
        e_io_offer_file_as_download("image_hd.png");
    }
}

//
// public
//

Tool *tool_new_save_hd() {
    return tool_button_new("save hd",
                           "saves the canvas\nas hd version\nas image_hd.png\n\n"
                           "The hd version\nhas a size of\nat least 1024px",
                           "res/button_save_hd.png",
                           pointer_event,
                           NULL);
}
