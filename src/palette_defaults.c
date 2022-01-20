#include "rhc/alloc.h"
#include "brush.h"


//
// private
// 

// grayscale
static uImage palette_0() {
    uImage self = u_image_new_empty(10, 1, 1);
    *u_image_pixel_index(self, 0, 0) =  U_COLOR_TRANSPARENT;
    for (int i = 1; i <= 9; i++) {
        uint8_t val = (i - 1) * 255 / 8;
       * u_image_pixel_index(self, i, 0) = (uColor_s) {val, val, val, 255};
    }
    return self;
}
static const char *name_0 = "grayscale.png";


//
// public
//


uImage *palette_defaults_new() {
    uImage *self = rhc_calloc(sizeof *self * (16));
    uImage *it = self;
    
    *it++ = palette_0();
   
    
    *it = u_image_new_invalid();
    return self;
}

void palette_defaults_kill(uImage **self_ptr) {
    uImage *it = *self_ptr;
    if(!it)
        return;
    while(u_image_valid(*it))
        u_image_kill(it++);
    rhc_free(*self_ptr);
    *self_ptr = NULL;
}

char *palette_defaults_name_on_heap(int id) {
    assume(id>=0 && id<1, "wtf?");
    char *name = rhc_malloc(32);
    if(id==0)
        strcpy(name, name_0);
    return name;
}
