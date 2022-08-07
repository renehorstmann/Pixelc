#ifndef PIXELC_MOD_TILEC_MOD_TILES_H
#define PIXELC_MOD_TILEC_MOD_TILES_H

#include "r/core.h"
#include "r/texture.h"
#include "u/image.h"

#define MOD_TILES_MAX_FILES 128
#define MOD_TILES_TILE_COLS 32
#define MOD_TILES_TILE_ROWS 32

struct ModTilesGlobals_s {
    uImage imgs[MOD_TILES_MAX_FILES];
    rTexture textures[MOD_TILES_MAX_FILES];
    int ids[MOD_TILES_MAX_FILES];
    int size;
};
extern struct ModTilesGlobals_s mod_tiles;

void mod_tiles_init();

#endif //PIXELC_MOD_TILEMOD_C_TILES_H
