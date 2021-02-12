#ifndef PIXELC_TILES_H
#define PIXELC_TILES_H

#include <stdbool.h>

struct TilesGlobals_s {
    bool show;
};
extern struct TilesGlobals_s tiles;


void tiles_init();

void tiles_update(float dtime);

void tiles_render();

#endif //PIXELC_TILES_H
