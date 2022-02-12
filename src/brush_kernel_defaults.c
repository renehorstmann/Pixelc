#include "rhc/alloc.h"
#include "brush.h"


//
// private
// 

// dot
static uImage kernel_0() {
    uImage self = u_image_new_empty(1, 1, 1);
    *u_image_pixel(self, 0, 0, 0) = U_COLOR_WHITE;
    return self;
}

// dither 2x2
static uImage kernel_1() {
    uImage self = u_image_new_empty(2, 2, 1);
    for(int r=0; r<2; r++) {
        for(int c=0; c<2; c++) {
            *u_image_pixel(self, c, r, 0) = c%2==r%2? U_COLOR_WHITE : U_COLOR_TRANSPARENT;
        }
    }
    return self;
}

// square 2x2
static uImage kernel_2() {
    uImage self = u_image_new_empty(2, 2, 1);
    for(int i=0; i<2*2; i++)
        *u_image_pixel_index(self, i, 0) = U_COLOR_WHITE;
    return self;
}

// dither 3x3
static uImage kernel_3() {
    uImage self = u_image_new_empty(3, 3, 1);
    for(int i=0; i<3*3; i++)
        *u_image_pixel_index(self, i, 0) = i%2? U_COLOR_WHITE : U_COLOR_TRANSPARENT;
    return self;
}


// plus 3x3
static uImage kernel_4() {
    uImage self = u_image_new_zeros(3, 3, 1);
    for(int i=0; i<3; i++) {
        *u_image_pixel(self, i, 1, 0) = U_COLOR_WHITE;
        *u_image_pixel(self, 1, i, 0) = U_COLOR_WHITE;
    }
    return self;
}


// square 3x3
static uImage kernel_5() {
    uImage self = u_image_new_empty(3, 3, 1);
    for(int i=0; i<3*3; i++)
        *u_image_pixel_index(self, i, 0) = U_COLOR_WHITE;
    return self;
}


// dither 4x4
static uImage kernel_6() {
    uImage self = u_image_new_empty(4, 4, 1);
    for(int r=0; r<4; r++) {
        for(int c=0; c<4; c++) {
            *u_image_pixel(self, c, r, 0) = c%2==r%2? U_COLOR_WHITE : U_COLOR_TRANSPARENT;
        }
    }
    return self;
}

// dither wide 4x4
static uImage kernel_7() {
    uImage self = u_image_new_empty(4, 4, 1);
    for(int r=0; r<4; r++) {
        for(int c=0; c<4; c++) {
            *u_image_pixel(self, c, r, 0) = c%2==(r%4>=2)? U_COLOR_WHITE : U_COLOR_TRANSPARENT;
        }
    }
    return self;
}

// dither high 4x4
static uImage kernel_8() {
    uImage self = kernel_7(); // dither wide
    u_image_rotate(&self, true);
    return self;
}

// ball 4*4
static uImage kernel_9() {
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
static uImage kernel_10() {
    uImage self = u_image_new_empty(4, 4, 1);
    for(int i=0; i<4*4; i++)
        *u_image_pixel_index(self, i, 0) = U_COLOR_WHITE;
    return self;
}



//
// public
//


uImage *brush_kernel_defaults_new() {
    uImage *self = rhc_calloc(sizeof *self * (16));
    uImage *it = self;
    
    *it++ = kernel_0();
    *it++ = kernel_1();
    *it++ = kernel_2();
    *it++ = kernel_3();
    *it++ = kernel_4();
    *it++ = kernel_5();
    *it++ = kernel_6();
    *it++ = kernel_7();
    *it++ = kernel_8();
    *it++ = kernel_9();
    *it++ = kernel_10();
    
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
