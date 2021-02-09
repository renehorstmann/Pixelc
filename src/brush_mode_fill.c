#include "utilc/dynarray.h"
#include "brush.h"
#include "canvas.h"
#include "brush_mode.h"


DynArray(ivec2, PosStack, pos_stack)


bool brush_mode_fill(ePointer_s pointer, bool mode8) {
    if (pointer.action != E_POINTER_DOWN)
        return false;

    Image *img = canvas_image();
    int layer = canvas_current_layer;

    ivec2 uv = canvas_get_uv(pointer.pos);
    if(!image_contains_uv(img, uv))
        return false;
    
    Color_s replace = *image_pixel_uv(img, layer, uv);
    if(color_equals(brush_current_color, replace))
        return false;
    
    // PosStack needs to be killed
    PosStack stack = {0};
    pos_stack_push(&stack, uv);
    
    while(stack.size>0) 	{
    	ivec2 p = pos_stack_pop(&stack);
    	if(!image_contains_uv(img, p))
    	    continue;
    	    
    	Color_s *pixel = image_pixel_uv(img, layer, p);
    	if(!color_equals(*pixel, replace))
    	    continue;
    	    
    	*pixel = brush_current_color;
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
    return true;
}

