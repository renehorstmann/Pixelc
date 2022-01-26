#ifndef SOME_CAMERA_H
#define SOME_CAMERA_H

//
// PixelPerfect canvas camera with view matrix.
// to control the camera position and size
//

#include <stdbool.h>
#include "mathc/types/float.h"
#include "mathc/types/int.h"

// the camera will unsure a canvas of at least CAMERA_SIZE * CAMERA_SIZE units
#define CAMERA_SIZE 180 // *4=720; *6=1080; *8=1440


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
    mat4 v_p_inv;   // v @ p_inv
} CameraMatrices_s;

typedef struct {
    CameraMatrices_s matrices;

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
} Camera_s;


// creates a new camera
Camera_s camera_new();

// updates the camera matrices
void camera_update(Camera_s *self, ivec2 window_size);

// set the position of the camera in the world
void camera_set_pos(Camera_s *self, float x, float y);

// set the size / zoom of the camera (default = 1.0)
void camera_set_size(Camera_s *self, float size);

// set the rotation of the camera
void camera_set_angle(Camera_s *self, float alpha);

// returns the width in game pixel (!=real pixel)
static int camera_width(const Camera_s *self) {
    return -self->RO.left + self->RO.right;
}

// returns the height in game pixel (!=real pixel)
static int camera_height(const Camera_s *self) {
    return -self->RO.bottom + self->RO.top;
}

// returns true if the camera is in portrait mode (smartphone)
static bool camera_is_portrait_mode(const Camera_s *self) {
    return camera_height(self) > camera_width(self);
}

#endif //SOME_CAMERA_H
