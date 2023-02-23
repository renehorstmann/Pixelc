#include "brush.h"
#include "canvas.h"
#include "brushmode.h"
#include "tooltip.h"
#include "m/int.h"


#define TYPE ivec2
#define CLASS PosStack
#define FN_NAME posstack

#include "s/dynarray.h"


bool brushmode_fill(ePointer_s pointer, bool mode8) {
    if (pointer.action != E_POINTER_DOWN)
        return false;

    uImage img = canvas.RO.image;
    int layer = canvas.RO.current_image_layer;
    
    ivec2 cr = canvas_get_cr(pointer.pos.xy);
    if (!u_image_contains(img, cr.x, cr.y))
        return false;

    uColor_s prev_secondary_color = brush.secondary_color;
    brush.secondary_color = *u_image_pixel(img, cr.x, cr.y, layer);
    if (u_color_equals(brush.current_color, brush.secondary_color))
        return false;

    bool shading_was_active = brush.shading_active;
    brush.shading_active = true;

    // PosStack needs to be killed
    PosStack stack = posstack_new(32);
    posstack_push(&stack, cr);

    while (stack.size > 0) {
        ivec2 p = posstack_pop(&stack);

        if (!brush_draw_pixel(p.x, p.y, U_COLOR_WHITE))
            continue;

        posstack_push(&stack,
                      (ivec2) {{p.x - 1, p.y}});
        posstack_push(&stack,
                      (ivec2) {{p.x + 1, p.y}});
        posstack_push(&stack,
                      (ivec2) {{p.x, p.y - 1}});
        posstack_push(&stack,
                      (ivec2) {{p.x, p.y + 1}});

        // mode8 edges
        if (!mode8)
            continue;
        posstack_push(&stack,
                      (ivec2) {{p.x - 1, p.y - 1}});
        posstack_push(&stack,
                      (ivec2) {{p.x + 1, p.y - 1}});
        posstack_push(&stack,
                      (ivec2) {{p.x - 1, p.y + 1}});
        posstack_push(&stack,
                      (ivec2) {{p.x + 1, p.y + 1}});
    }

    posstack_kill(&stack);

    brush.shading_active = shading_was_active;
    brush.secondary_color = prev_secondary_color;
    return true;
}

bool brushmode_replace(ePointer_s pointer) {
    if (pointer.action != E_POINTER_DOWN)
        return false;

    uImage img = canvas.RO.image;
    int layer = canvas.RO.current_image_layer;
    
    ivec2 cr = canvas_get_cr(pointer.pos.xy);
    if (!u_image_contains(img, cr.x, cr.y))
        return false;

    uColor_s prev_secondary_color = brush.secondary_color;
    brush.secondary_color = *u_image_pixel(img, cr.x, cr.y, layer);
    if (u_color_equals(brush.current_color, brush.secondary_color))
        return false;

    bool shading_was_active = brush.shading_active;
    brush.shading_active = true;

    for (int r = 0; r < img.rows; r++) {
        for (int c = 0; c < img.cols; c++) {
            brush_draw_pixel(c, r, U_COLOR_WHITE);
        }
    }

    brush.shading_active = shading_was_active;
    brush.secondary_color = prev_secondary_color;
    return true;
}



static bool outline_check(int c, int r, int l, uImage img, uImage kernel, uColor_s color) {
    for(int kr=0; kr<kernel.rows; kr++) {
        int ir = r - kernel.rows/2 + kr;
        ir = isca_clamp(ir, 0, img.rows-1);
        for(int kc=0; kc<kernel.cols; kc++) {

            // only check none transparent kernel fields
            if(u_color_equals(*u_image_pixel(kernel, kc, kr, 0), U_COLOR_TRANSPARENT)) {
                continue;
            }

            int ic = c - kernel.cols/2 + kc;
            ic = isca_clamp(ic, 0, img.cols-1);

            // if img color at this position is not the clicked color, check is true to redraw
            if(!u_color_equals(*u_image_pixel(img, ic, ir, l), color)) {
                return true;
            }
        }
    }
    return false;
}

bool brushmode_outline(ePointer_s pointer) {
    if (pointer.action != E_POINTER_DOWN)
        return false;

    uImage img = canvas.RO.image;
    int layer = canvas.RO.current_image_layer;

    ivec2 cr = canvas_get_cr(pointer.pos.xy);
    if (!u_image_contains(img, cr.x, cr.y))
        return false;

    uColor_s color = *u_image_pixel(img, cr.x, cr.y, layer);

    // needs to be killed
    uImage kernel;
    if(brush.RO.kernel.cols==1 && brush.RO.kernel.rows==1) {
        // one pixel kernel will result in a 3x3 "+" kernel
        kernel = u_image_new_zeros(3, 3, 1);
        for(int r=0; r<3; r++) {
            for(int c=0; c<3; c++) {
                if(r==1 || c == 1) {
                    *u_image_pixel(kernel, c, r, 0) = U_COLOR_WHITE;
                }
            }
        }
    } else {
        kernel = u_image_new_clone(brush.RO.kernel);
    }

    // needs to be killed
    PosStack stack = posstack_new(32);

    for(int r=0; r<img.rows; r++) {
        for(int c=0; c<img.cols; c++) {
            if(!u_color_equals(color, *u_image_pixel(img, c, r, layer))) {
                continue;
            }
            if(outline_check(c, r, layer, img, kernel, color)) {
                posstack_push(&stack, (ivec2) {{c, r}});
            }
        }
    }

    // draw all positions
    bool changed = false;
    for(ssize i=0; i<stack.size; i++) {
        ivec2 pos = stack.array[i];
        changed |= brush_draw_pixel(pos.v0, pos.v1, U_COLOR_WHITE);
    }

    posstack_kill(&stack);
    u_image_kill(&kernel);
    return changed;
}

