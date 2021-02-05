#ifndef PIXELC_PALETTE_PRESAVE_H
#define PIXELC_PALETTE_PRESAVE_H

#include "palette.h"


static void palette_presave_grayscale() {
    Color_s palette[10];
    int size = 10;
    palette[0] = COLOR_TRANSPARENT;
    for (int i = 1; i <= 9; i++) {
        uint8_t val = (i - 1) * 255 / 8;
        palette[i] = (Color_s) {val, val, val, 255};
    }
    palette_set_colors(palette, size);
}

static void palette_presave_grayscale_alpha() {
    Color_s palette[40];
    int size = 40;
    for (int r = 0; r < 4; r++) {
        palette[0 + r * 10] = COLOR_TRANSPARENT;
        for (int i = 1; i <= 9; i++) {
            uint8_t val = (i - 1) * 255 / 8;
            uint8_t alpha = (r + 1) * 255 / 4;
            palette[i + r * 10] = (Color_s) {val, val, val, alpha};
        }
    }
    palette_set_colors(palette, size);
}

static void palette_presave_pixilmatt() {
    Color_s palette[38];
    int size = 38;
    const char *hex[38] = {
            "#00000000",
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

    for (int i = 0; i < size; i++) {
        palette[i] = color_from_hex(hex[i]);
    }

    palette_set_colors(palette, size);
}

static void palette_presave_slso8() {
    Color_s palette[10];
    int size = 10;
    const char *hex[10] = {
            "#00000000",
            "#000000",
            "#0d2b45",
            "#203c56",
            "#544e68",
            "#8d697a",
            "#d08159",
            "#ffaa5e",
            "#ffd4a3",
            "#ffecd6"
    };

    for (int i = 0; i < size; i++) {
        palette[i] = color_from_hex(hex[i]);
    }

    palette_set_colors(palette, size);
}


static void palette_presave_gameboy() {
    Color_s palette[5];
    int size = 5;
    const char *hex[5] = {
            "#00000000",
            "#00131a",
            "#3d8026",
            "#abcc47",
            "#f9ffb3"
    };

    for (int i = 0; i < size; i++) {
        palette[i] = color_from_hex(hex[i]);
    }

    palette_set_colors(palette, size);
}


static void palette_presave_endesga32() {
    Color_s palette[33];
    int size = 33;
    const char *hex[33] = {
            "#00000000",
            "#be4a2f",
            "#d77643",
            "#ead4aa",
            "#e4a672",
            "#b86f50",
            "#733e39",
            "#3e2731",
            "#a22633",
            "#e43b44",
            "#f77622",
            "#feae34",
            "#fee761",
            "#63c74d",
            "#3e8948",
            "#265c42",
            "#193c3e",
            "#124e89",
            "#0099db",
            "#2ce8f5",
            "#ffffff",
            "#c0cbdc",
            "#8b9bb4",
            "#5a6988",
            "#3a4466",
            "#262b44",
            "#181425",
            "#ff0044",
            "#68386c",
            "#b55088",
            "#f6757a",
            "#e8b796",
            "#c28569"
    };

    for (int i = 0; i < size; i++) {
        palette[i] = color_from_hex(hex[i]);
    }

    palette_set_colors(palette, size);
}


static void palette_presave_endesga64() {
    Color_s palette[65];
    int size = 65;
    const char *hex[65] = {
            "#00000000",
            "#ff0040",
            "#131313",
            "#1b1b1b",
            "#272727",
            "#3d3d3d",
            "#5d5d5d",
            "#858585",
            "#b4b4b4",
            "#ffffff",
            "#c7cfdd",
            "#92a1b9",
            "#657392",
            "#424c6e",
            "#2a2f4e",
            "#1a1932",
            "#0e071b",
            "#1c121c",
            "#391f21",
            "#5d2c28",
            "#8a4836",
            "#bf6f4a",
            "#e69c69",
            "#f6ca9f",
            "#f9e6cf",
            "#edab50",
            "#e07438",
            "#c64524",
            "#8e251d",
            "#ff5000",
            "#ed7614",
            "#ffa214",
            "#ffc825",
            "#ffeb57",
            "#d3fc7e",
            "#99e65f",
            "#5ac54f",
            "#33984b",
            "#1e6f50",
            "#134c4c",
            "#0c2e44",
            "#00396d",
            "#0069aa",
            "#0098dc",
            "#00cdf9",
            "#0cf1ff",
            "#94fdff",
            "#fdd2ed",
            "#f389f5",
            "#db3ffd",
            "#7a09fa",
            "#3003d9",
            "#0c0293",
            "#03193f",
            "#3b1443",
            "#622461",
            "#93388f",
            "#ca52c9",
            "#c85086",
            "#f68187",
            "#f5555d",
            "#ea323c",
            "#c42430",
            "#891e2b",
            "#571c27"
    };

    for (int i = 0; i < size; i++) {
        palette[i] = color_from_hex(hex[i]);
    }

    palette_set_colors(palette, size);
}



static void palette_presave_nes() {
    Color_s palette[56];
    int size = 56;
    const char *hex[56] = {
            "#00000000",
            "#000000",
            "#fcfcfc",
            "#f8f8f8",
            "#bcbcbc",
            "#7c7c7c",
            "#a4e4fc",
            "#3cbcfc",
            "#0078f8",
            "#0000fc",
            "#b8b8f8",
            "#6888fc",
            "#0058f8",
            "#0000bc",
            "#d8b8f8",
            "#9878f8",
            "#6844fc",
            "#4428bc",
            "#f8b8f8",
            "#f878f8",
            "#d800cc",
            "#940084",
            "#f8a4c0",
            "#f85898",
            "#e40058",
            "#a80020",
            "#f0d0b0",
            "#f87858",
            "#f83800",
            "#a81000",
            "#fce0a8",
            "#fca044",
            "#e45c10",
            "#881400",
            "#f8d878",
            "#f8b800",
            "#ac7c00",
            "#503000",
            "#d8f878",
            "#b8f818",
            "#00b800",
            "#007800",
            "#b8f8b8",
            "#58d854",
            "#00a800",
            "#006800",
            "#b8f8d8",
            "#58f898",
            "#00a844",
            "#005800",
            "#00fcfc",
            "#00e8d8",
            "#008888",
            "#004058",
            "#f8d8f8",
            "#787878"
    };

    for (int i = 0; i < size; i++) {
        palette[i] = color_from_hex(hex[i]);
    }

    palette_set_colors(palette, size);
}


static void palette_presave_aap64() {
    Color_s palette[65];
    int size = 65;
    const char *hex[65] = {
            "#00000000",
            "#060608",
            "#141013",
            "#3b1725",
            "#73172d",
            "#b4202a",
            "#df3e23",
            "#fa6a0a",
            "#f9a31b",
            "#ffd541",
            "#fffc40",
            "#d6f264",
            "#9cdb43",
            "#59c135",
            "#14a02e",
            "#1a7a3e",
            "#24523b",
            "#122020",
            "#143464",
            "#285cc4",
            "#249fde",
            "#20d6c7",
            "#a6fcdb",
            "#ffffff",
            "#fef3c0",
            "#fad6b8",
            "#f5a097",
            "#e86a73",
            "#bc4a9b",
            "#793a80",
            "#403353",
            "#242234",
            "#221c1a",
            "#322b28",
            "#71413b",
            "#bb7547",
            "#dba463",
            "#f4d29c",
            "#dae0ea",
            "#b3b9d1",
            "#8b93af",
            "#6d758d",
            "#4a5462",
            "#333941",
            "#422433",
            "#5b3138",
            "#8e5252",
            "#ba756a",
            "#e9b5a3",
            "#e3e6ff",
            "#b9bffb",
            "#849be4",
            "#588dbe",
            "#477d85",
            "#23674e",
            "#328464",
            "#5daf8d",
            "#92dcba",
            "#cdf7e2",
            "#e4d2aa",
            "#c7b08b",
            "#a08662",
            "#796755",
            "#5a4e44",
            "#423934"
    };

    for (int i = 0; i < size; i++) {
        palette[i] = color_from_hex(hex[i]);
    }

    palette_set_colors(palette, size);
}

#endif //PIXELC_PALETTE_PRESAVE_H
