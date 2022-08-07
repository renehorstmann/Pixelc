#include "r/texture.h"
#include "mod_tiles.h"

#ifdef PIXELC_MOD_ISOTILEC
#define TILE_DIR "isotiles"
#else
#define TILE_DIR "tiles"
#endif

struct ModTilesGlobals_s mod_tiles;

void mod_tiles_init() {
    int tile_id = 1;
    mod_tiles.size = 0;
    for (; mod_tiles.size < MOD_TILES_MAX_FILES;) {
        char file[128];
        sprintf(file, TILE_DIR "/tile_%02i.png", tile_id);

        uImage img = u_image_new_file(2, file);
        if (!u_image_valid(img))
            break;

        s_assume(img.cols % MOD_TILES_TILE_COLS == 0
                 && img.rows % MOD_TILES_TILE_ROWS == 0,
                 "wrong tiles size");

        int sprites_x = img.cols / MOD_TILES_TILE_COLS;
        int sprites_y = img.rows / MOD_TILES_TILE_ROWS;

        rTexture tex = r_texture_new(img.cols, img.rows, sprites_x, sprites_y, u_image_layer(img, 0));


        mod_tiles.imgs[mod_tiles.size] = img;
        mod_tiles.textures[mod_tiles.size] = tex;
        mod_tiles.ids[mod_tiles.size] = tile_id;

        tile_id++;
        mod_tiles.size++;
    }
    s_log_info("mod_tiles: loaded %i", mod_tiles.size);
    if (mod_tiles.size == 0)
        s_log_error("mod_tiles: WARNING: 0 tiles loaded! Put some into " TILE_DIR "/tile_xx.png, starting with xx=01");
}
