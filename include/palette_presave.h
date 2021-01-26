#ifndef PIXELC_PALETTE_PRESAVE_H
#define PIXELC_PALETTE_PRESAVE_H

#include "palette.h"

static void palette_presave_pixilmatt() {
    color palette[38];
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

    for (int i = 0; i < size; i++)
        palette[i] = color_from_hex(hex[i]);
    palette_set_colors(palette, size);
}

#endif //PIXELC_PALETTE_PRESAVE_H
