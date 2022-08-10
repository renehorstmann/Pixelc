#ifndef PIXELC_TILE_PALETTE_CAMERA_H
#define PIXELC_TILE_PALETTE_CAMERA_H


//
// PixelPerfect canvas tile_palette_camera with view matrix.
// to control the tile_palette_camera position and size
//

#include "s/s.h"
#include "m/types/float.h"
#include "m/types/int.h"


typedef struct {
    // view / pose of the tile_palette_camera in 3d space
    mat4 v;
    mat4 v_inv;     // inv(v)

    // projection of the tile_palette_camera (perspective / orthogonal)
    // pass 'p' to a render object, 
    //     to draw it at a static position on the screen (HUD)
    // use 'p_inv' to transform a touch position to the screen units
    mat4 p;
    mat4 p_inv;     // inv(p)

    // combination of view and projection
    // pass 'vp' to a render object,
    //     to draw it in the world, 
    //     so that the tile_palette_camera movement of 'v' is used
    // use 'v_p_inv' to transform a touch position to the world
    mat4 vp;        // p @ v_inv
    mat4 v_p_inv;   // v @ p_inv
} TilePaletteCameraMatrices_s;

struct TilePaletteCamera_Globals {
    TilePaletteCameraMatrices_s matrices;

    int size;

    struct {
        // units per pixel
        float scale;

        // static tile_palette_camera borders in units
        // bottom and right may be a little behind the actual screen border (depending on the real resolution)
        int left, right, bottom, top;

        // static tile_palette_camera borders in units
        // bottom and right are on the actual screen borders
        float screen_left, screen_right, screen_bottom, screen_top;
    } RO;   // read only
};
extern struct TilePaletteCamera_Globals tile_palette_camera;


// initializes a new tile_palette_camera
void tile_palette_camera_init();

// updates the tile_palette_camera matrices
void tile_palette_camera_update(ivec2 window_size);

// set the position of the tile_palette_camera in the world
void tile_palette_camera_set_pos(float x, float y);

// set the zoom of the tile_palette_camera (default = 1.0)
void tile_palette_camera_set_zoom(float size);

// set the rotation of the tile_palette_camera
void tile_palette_camera_set_angle(float alpha);


// returns the width in game pixel (!=real pixel)
static int tile_palette_camera_width() {
    return -tile_palette_camera.RO.left + tile_palette_camera.RO.right;
}

// returns the height in game pixel (!=real pixel)
static int tile_palette_camera_height() {
    return -tile_palette_camera.RO.bottom + tile_palette_camera.RO.top;
}

#endif //PIXELC_TILE_PALETTE_CAMERA_H
