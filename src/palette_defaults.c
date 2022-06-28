#include "brush.h"


//
// private
// 

static const char *name_0 = "grayscale.png";

static uImage palette_0() {
    uImage self = u_image_new_empty(10, 1, 1);
    for (int i = 0; i < self.cols; i++) {
        uint8_t val = i * 255 / (self.cols - 1);
        *u_image_pixel(self, i, 0, 0) = (uColor_s) {val, val, val, 255};
    }
    return self;
}


static const char *name_1 = "grayscale_alpha.png";

static uImage palette_1() {
    uImage self = u_image_new_empty(10, 4, 1);
    for (int r = 0; r < self.rows; r++) {
        for (int i = 0; i < self.cols; i++) {
            uint8_t val = i * 255 / (self.cols - 1);
            *u_image_pixel(self, i, r, 0) = (uColor_s) {val, val, val, (r + 1) * 255 / (self.rows)};
        }
    }
    return self;
}


static const char *name_2 = "endesga 32.png";

static uImage palette_2() {
    return u_image_new_file(1, "res/palettes/endesga-32-1x.png");
}

static const char *name_3 = "resurrect 64.png";

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

static const char *name_7 = "vinik24.png";

static uImage palette_7() {
    return u_image_new_file(1, "res/palettes/vinik24-1x.png");
}

static const char *name_8 = "journey.png";

static uImage palette_8() {
    return u_image_new_file(1, "res/palettes/journey-1x.png");
}

static const char *name_9 = "zughy 32.png";

static uImage palette_9() {
    return u_image_new_file(1, "res/palettes/zughy-32-1x.png");
}

static const char *name_10 = "endedga 64.png";

static uImage palette_10() {
    return u_image_new_file(1, "res/palettes/endesga-64-1x.png");
}

static const char *name_11 = "sweetie 16.png";

static uImage palette_11() {
    return u_image_new_file(1, "res/palettes/sweetie-16-1x.png");
}

static const char *name_12 = "fantasy 24.png";

static uImage palette_12() {
    return u_image_new_file(1, "res/palettes/fantasy-24-1x.png");
}

static const char *name_13 = "slso8.png";

static uImage palette_13() {
    return u_image_new_file(1, "res/palettes/slso8-1x.png");
}

static const char *name_14 = "alollo.png";

static uImage palette_14() {
    return u_image_new_file(1, "res/palettes/apollo-1x.png");
}

static const char *name_15 = "pico-8.png";

static uImage palette_15() {
    return u_image_new_file(1, "res/palettes/pico-8-1x.png");
}

static const char *name_16 = "cc-29.png";

static uImage palette_16() {
    return u_image_new_file(1, "res/palettes/cc-29-1x.png");
}

static const char *name_17 = "oil 6.png";

static uImage palette_17() {
    return u_image_new_file(1, "res/palettes/oil-6-1x.png");
}

static const char *name_18 = "na16.png";

static uImage palette_18() {
    return u_image_new_file(1, "res/palettes/na16-1x.png");
}

static const char *name_19 = "famicube.png";

static uImage palette_19() {
    return u_image_new_file(1, "res/palettes/famicube-1x.png");
}

static const char *name_20 = "chocomilk-8.png";

static uImage palette_20() {
    return u_image_new_file(1, "res/palettes/chocomilk-8-1x.png");
}

static const char *name_21 = "kirokaze gameboy.png";

static uImage palette_21() {
    return u_image_new_file(1, "res/palettes/kirokaze-gameboy-1x.png");
}

static const char *name_22 = "steam lords.png";

static uImage palette_22() {
    return u_image_new_file(1, "res/palettes/steam-lords-1x.png");
}

static const char *name_23 = "nes.png";

static uImage palette_23() {
    return u_image_new_file(1, "res/palettes/nintendo-entertainment-system-1x.png");
}


static const char *name_998 = "gameboy.png";

static uImage palette_998() {
    uImage self = u_image_new_empty(4, 1, 1);
    const char *hex[4] = {
            "#00131a", "#3d8026", "#abcc47", "#f9ffb3"
    };
    for (int i = 0; i < 4; i++) {
        *u_image_pixel(self, i, 0, 0) = u_color_from_hex(hex[i]);
    }
    return self;
}


static const char *name_999 = "pixilmatt.png";

static uImage palette_999() {
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
    for (int i = 0; i < 37; i++) {
        *u_image_pixel(self, i, 0, 0) = u_color_from_hex(hex[i]);
    }
    return self;
}


//
// public
//


uImage *palette_defaults_new() {
    uImage *self = s_malloc0(sizeof *self * (32));
    uImage *it = self;

    *it++ = palette_0();
    *it++ = palette_1();
    *it++ = palette_2();
    *it++ = palette_3();
    *it++ = palette_4();
    *it++ = palette_5();
    *it++ = palette_6();
    *it++ = palette_7();
    *it++ = palette_8();
    *it++ = palette_9();
    *it++ = palette_10();
    *it++ = palette_11();
    *it++ = palette_12();
    *it++ = palette_13();
    *it++ = palette_14();
    *it++ = palette_15();
    *it++ = palette_16();
    *it++ = palette_17();
    *it++ = palette_18();
    *it++ = palette_19();
    *it++ = palette_20();
    *it++ = palette_21();
    *it++ = palette_22();
    *it++ = palette_23();


    *it++ = palette_998();
    *it++ = palette_999();

    *it = u_image_new_invalid();
    return self;
}

void palette_defaults_kill(uImage **self_ptr) {
    uImage *it = *self_ptr;
    if (!it)
        return;
    while (u_image_valid(*it))
        u_image_kill(it++);
    s_free(*self_ptr);
    *self_ptr = NULL;
}

char *palette_defaults_name_on_heap(int id) {
    s_assume(id >= 0 && id <= 25, "wtf?");
    char *name = s_malloc0(32);
    if (id == 0)
        strcpy(name, name_0);
    if (id == 1)
        strcpy(name, name_1);
    if (id == 2)
        strcpy(name, name_2);
    if (id == 3)
        strcpy(name, name_3);
    if (id == 4)
        strcpy(name, name_4);
    if (id == 5)
        strcpy(name, name_5);
    if (id == 6)
        strcpy(name, name_6);
    if (id == 7)
        strcpy(name, name_7);
    if (id == 8)
        strcpy(name, name_8);
    if (id == 9)
        strcpy(name, name_9);
    if (id == 10)
        strcpy(name, name_10);
    if (id == 11)
        strcpy(name, name_11);
    if (id == 12)
        strcpy(name, name_12);
    if (id == 13)
        strcpy(name, name_13);
    if (id == 14)
        strcpy(name, name_14);
    if (id == 15)
        strcpy(name, name_15);
    if (id == 16)
        strcpy(name, name_16);
    if (id == 17)
        strcpy(name, name_17);
    if (id == 18)
        strcpy(name, name_18);
    if (id == 19)
        strcpy(name, name_19);
    if (id == 20)
        strcpy(name, name_20);
    if (id == 21)
        strcpy(name, name_21);
    if (id == 22)
        strcpy(name, name_22);
    if (id == 23)
        strcpy(name, name_23);

    if (id == 24)
        strcpy(name, name_998);
    if (id == 25)
        strcpy(name, name_999);
    return name;
}
