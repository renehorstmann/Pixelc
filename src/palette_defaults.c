#include "rhc/alloc.h"
#include "brush.h"


//
// private
// 

static const char *name_0 = "grayscale.png";
static uImage palette_0() {
    uImage self = u_image_new_empty(10, 1, 1);
    for (int i = 0; i < self.cols; i++) {
        uint8_t val = i * 255 / (self.cols-1);
        *u_image_pixel(self, i, 0, 0) = (uColor_s) {val, val, val, 255};
    }
    return self;
}


static const char *name_1 = "grayscale_alpha.png";
static uImage palette_1() {
    uImage self = u_image_new_empty(10, 4, 1);
    for(int r=0; r<self.rows; r++) {
        for (int i = 0; i < self.cols; i++) {
            uint8_t val = i * 255 / (self.cols-1);
            *u_image_pixel(self, i, r, 0) = (uColor_s) {val, val, val, (r+1)*255/(self.rows)};
        }
    }
    return self;
}


static const char *name_2 = "endesga-32.png";
static uImage palette_2() {
    return u_image_new_file(1, "res/palettes/endesga-32-1x.png");
}

static const char *name_3 = "resurrect-64.png";
static uImage palette_3() {
    return u_image_new_file(1, "res/palettes/resurrect-64-1x.png");
}

static const char *name_4 = "pear36.png";
static uImage palette_4() {
    return u_image_new_file(1, "res/palettes/pear36-1x.png");
}

static const char *name_5 = "aap-64.png";
static uImage palette_5() {
    return u_image_new_file(1, "res/palettes/aap-64-1x.png");
}

static const char *name_6 = "lospec500.png";
static uImage palette_6() {
    return u_image_new_file(1, "res/palettes/lospec500-1x.png");
}

static const char *name_7 = "pixilmatt.png";
static uImage palette_7() {
    uImage self = u_image_new_empty(37, 1, 1);
    const char *hex[37] = {
            "#ffffff",
            "#000000",
            "#99c2db",
            "#5d8bb3",
            "#4d6a94",
            "#4c5d7a",
            "#357985",
            "#4c8f82",
            "#78b392",
            "#b5e0ba",
            "#dfeded",
            "#c6dbde",
            "#a7b8c2",
            "#728794",
            "#4e4d5c",
            "#5c4d4d",
            "#997d76",
            "#c7b198",
            "#dfd3c3",
            "#f0ece2",
            "#e6a3a3",
            "#995c95",
            "#5a526b",
            "#3d3957",
            "#391154",
            "#5b106e",
            "#911d55",
            "#bf2651",
            "#f54f4f",
            "#ff8766",
            "#ffac7f",
            "#ffd3a3",
            "#fafac3",
            "#e6cf8a",
            "#d6a57a",
            "#b3785d",
            "#9c4f41"
    };
    for (int i = 0; i < 38; i++) {
        *u_image_pixel(self, i, 0, 0) = u_color_from_hex(hex[i]);
    }
    return self;
}


//
// public
//


uImage *palette_defaults_new() {
    uImage *self = rhc_calloc(sizeof *self * (16));
    uImage *it = self;
    
    *it++ = palette_0(); 
    *it++ = palette_1();
    *it++ = palette_2();
    *it++ = palette_3();
    *it++ = palette_4();
    *it++ = palette_5();
    *it++ = palette_6();
    *it++ = palette_7();
    
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
    assume(id>=0 && id<7, "wtf?");
    char *name = rhc_calloc(32);
    if(id==0)
        strcpy(name, name_0);
    if(id==1)
        strcpy(name, name_1);
    if(id==2)
        strcpy(name, name_2);
    if(id==3)
        strcpy(name, name_3);
    if(id==4)
        strcpy(name, name_4);
    if(id==5)
        strcpy(name, name_5);
    if(id==6)
        strcpy(name, name_6);
    if(id==7)
        strcpy(name, name_7);
    return name;
}
