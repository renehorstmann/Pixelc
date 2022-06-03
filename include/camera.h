#ifndef SOME_CAMERA_H
#define SOME_CAMERA_H

//
// PixelPerfect canvas camera with view matrix.
// to control the camera position and size
//

#include "rhc/rhc.h"
#include "mathc/types/float.h"
#include "mathc/types/int.h"

// the camera will unsure a canvas of at least CAMERA_SIZE * CAMERA_SIZE units
#define CAMERA_SIZE_MIN 128
#define CAMERA_SIZE_MAX 512
#define CAMERA_SIZE_SMALL 180 // *4=720; *6=1080; *8=1440
#define CAMERA_SIZE_BIG 270


enum camera_rotate_mode {
    CAMERA_ROTATE_MODE_PORTRAIT,
    CAMERA_ROTATE_MODE_LANDSCAPE,
    CAMERA_ROTATE_MODE_AUTO,
    CAMERA_ROTATE_NUM_MODES
};


typedef struct {
    // view / pose of the camera in 3d space
    mat4 v;
    mat4 v_inv;     // inv(v)

    // projection of the camera (perspective / orthogonal)
    // pass 'p' to a render object, 
    //     to draw it at a static position on the screen (HUD)
    // use 'p_inv' to transform a touch position to the screen units
    mat4 p;
    mat4 p_inv;     // inv(p)

    // combination of view and projection
    // pass 'vp' to a render object,
    //     to draw it in the world, 
    //     so that the camera movement of 'v' is used
    // use 'v_p_inv' to transform a touch position to the world
    mat4 vp;        // p @ v_inv
//    mat4 v_p_inv;   // v @ p_inv
} CameraMatrices_s;

struct Camera_Globals {
    CameraMatrices_s matrices;

    int size;
    enum camera_rotate_mode rotate_mode;

    struct {
        // units per pixel
        float scale;

        // static camera borders in units
        // bottom and right may be a little behind the actual screen border (depending on the real resolution)
        int left, right, bottom, top;

        // static camera borders in units
        // bottom and right are on the actual screen borders
        float screen_left, screen_right, screen_bottom, screen_top;
    } RO;   // read only
};
extern struct Camera_Globals camera;


// initializes a new camera
void camera_init();

// updates the camera matrices
void camera_update();

// set the position of the camera in the world
void camera_set_pos(float x, float y);

// set the zoom of the camera (default = 1.0)
void camera_set_zoom(float size);

// set the rotation of the camera
void camera_set_angle(float alpha);

// see camera.rotate_mode
// on AUTO, the camera_width, height determines thr mode
bool camera_is_portrait_mode();


// saves the config to the savestate config.json 
// uses object "canvas"
void camera_save_config();

// loads the config from the savestate config.json
// uses object "canvas"
void camera_load_config();


// returns the width in game pixel (!=real pixel)
static int camera_width() {
    return -camera.RO.left + camera.RO.right;
}

// returns the height in game pixel (!=real pixel)
static int camera_height() {
    return -camera.RO.bottom + camera.RO.top;
}


#endif //SOME_CAMERA_H
