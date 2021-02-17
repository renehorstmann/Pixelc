#include "utilc/dynarray.h"
#include "canvas.h"
#include "brush.h"
#include "brush_mode.h"


DynArray(ivec2, PosStack, pos_stack)


bool brush_mode_fill(ePointer_s pointer, bool mode8) {
    if (pointer.action != E_POINTER_DOWN)
        return false;

    Image *img = canvas_image();
    int layer = canvas.current_layer;

    ivec2 cr = canvas_get_cr(pointer.pos);
    if(!image_contains(img, cr.x, cr.y))
        return false;
    
    brush.secondary_color = *image_pixel(img, layer, cr.x, cr.y);
    if(color_equals(brush.current_color, brush.secondary_color))
        return false;
    
    bool shading_was_active = brush.shading_active;
    brush.shading_active = true;
    
    // PosStack needs to be killed
    PosStack stack = {0};
    pos_stack_push(&stack, cr);
    
    while(stack.size>0) 	{
    	ivec2 p = pos_stack_pop(&stack);
    	
    	if(!brush_draw_pixel(p.x, p.y))
    	    continue;
    	
    	pos_stack_push(&stack, 
    	    (ivec2) {{p.x-1, p.y}});
    	pos_stack_push(&stack, 
    	    (ivec2) {{p.x+1, p.y}});
    	pos_stack_push(&stack, 
    	    (ivec2) {{p.x, p.y-1}});
    	pos_stack_push(&stack, 
    	    (ivec2) {{p.x, p.y+1}});
    	
    	// mode8 edges
    	if(!mode8)
    	    continue;
    	pos_stack_push(&stack, 
    	    (ivec2) {{p.x-1, p.y-1}});
    	pos_stack_push(&stack, 
    	    (ivec2) {{p.x+1, p.y-1}});
    	pos_stack_push(&stack, 
    	    (ivec2) {{p.x-1, p.y+1}});
    	pos_stack_push(&stack, 
    	    (ivec2) {{p.x+1, p.y+1}});
    }
    
    pos_stack_kill(&stack);
    
    brush.shading_active = shading_was_active;
    return true;
}

bool brush_mode_replace(ePointer_s pointer) {
	if (pointer.action != E_POINTER_DOWN)
        return false;

    Image *img = canvas_image();
    int layer = canvas.current_layer;

    ivec2 cr = canvas_get_cr(pointer.pos);
    if(!image_contains(img, cr.x, cr.y))
        return false;
    
    brush.secondary_color = *image_pixel(img, layer, cr.x, cr.y);
    if(color_equals(brush.current_color, brush.secondary_color))
        return false;
    
    bool shading_was_active = brush.shading_active;
    brush.shading_active = true;

	for(int r=0; r<img->rows; r++) {
		for(int c=0; c<img->cols; c++) {
			brush_draw_pixel(c, r);
		}
	}
	
	brush.shading_active = shading_was_active;
    return true;
}

