#include "rhc/alloc.h"
#include "brush.h"


//
// private
// 

// dot
uImage kernel_0() {
    uImage self = u_image_new_empty(1, 1, 1);
    *u_image_pixel(self, 0, 0, 0) = U_COLOR_WHITE;
    return self;
}

// square 2x2
uImage kernel_1() {
    uImage self = u_image_new_empty(2, 2, 1);
    for(int i=0; i<2*2; i++)
        *u_image_pixel_index(self, i, 0) = U_COLOR_WHITE;
    return self;
}

// plus 3x3
uImage kernel_2() {
    uImage self = u_image_new_zeros(3, 3, 1);
    for(int i=0; i<3; i++) {
        *u_image_pixel(self, i, 1, 0) = U_COLOR_WHITE;
        *u_image_pixel(self, 1, i, 0) = U_COLOR_WHITE;
    }
    return self;
}

// square 3x3
uImage kernel_3() {
    uImage self = u_image_new_empty(3, 3, 1);
    for(int i=0; i<3*3; i++)
        *u_image_pixel_index(self, i, 0) = U_COLOR_WHITE;
    return self;
}

// ball 4*4
uImage kernel_4() {
    uImage self = u_image_new_zeros(4, 4, 1);
    for(int i=0; i<4; i++) {
        *u_image_pixel(self, i, 1, 0) = U_COLOR_WHITE;
        *u_image_pixel(self, i, 2, 0) = U_COLOR_WHITE;
        *u_image_pixel(self, 1, i, 0) = U_COLOR_WHITE;
        *u_image_pixel(self, 2, i, 0) = U_COLOR_WHITE;
    }
    return self;
}

// square 4x4
uImage kernel_5() {
    uImage self = u_image_new_empty(4, 4, 1);
    for(int i=0; i<4*4; i++)
        *u_image_pixel_index(self, i, 0) = U_COLOR_WHITE;
    return self;
}


//
// public
//


uImage *brush_kernel_defaults_new() {
    uImage *self = rhc_calloc(sizeof *self * (6+1));
    uImage *it = self;
    
    *it++ = kernel_0();
    *it++ = kernel_1();
    *it++ = kernel_2();
    *it++ = kernel_3();
    *it++ = kernel_4();
    *it++ = kernel_5();
    
    *it = u_image_new_invalid();
    return self;
}

void brush_kernel_defaults_kill(uImage **self_ptr) {
    uImage *it = *self_ptr;
    if(!it)
        return;
    while(u_image_valid(*it))
        u_image_kill(it++);
    rhc_free(*self_ptr);
    *self_ptr = NULL;
}
