#include "brush.h"
#include "canvas.h"
#include "brushmode.h"


#define TYPE ivec2
#define CLASS PosStack
#define FN_NAME posstack

#include "s/dynarray.h"


bool brushmode_fill(ePointer_s pointer, bool mode8) {
    if (pointer.action != E_POINTER_DOWN)
        return false;

    uImage img = canvas.RO.image;
    int layer = canvas.RO.current_image_layer;
    
    ivec2 cr = {{pointer.pos.x, -pointer.pos.y}};
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
    
    ivec2 cr = {{pointer.pos.x, -pointer.pos.y}};
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

