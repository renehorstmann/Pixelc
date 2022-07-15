#ifndef R_RECT_H
#define R_RECT_H

//
// rect pod structs, used by some renderobjects (ro)
//

#include "core.h"

// Basic rect for rendering
typedef struct {
    mat4 pose;      // 3d pose for the rect position (see u/pose.h)
    mat4 uv;        // 3d pose for the uv texture map (see u/pose.h)
    vec4 color;     // additional color (texture_color * color)
    vec2 sprite;    // position of the sprite in the grid
} rRect_s;


// Rect with additional values for a particle system
typedef struct {
    union {
        rRect_s rect;
        struct {
            mat4 pose;
            mat4 uv;
            vec4 color;
            vec2 sprite;
        };
    };
    vec2 sprite_speed;  // sprite += sprite_speed * dt
    vec4 speed;         // position += speed * dt
    vec4 acc;           // position += acc * dt * dt
    vec4 axis_angle;    // orientation += axis_angle * dt   (nx, ny, nz, rad)
    vec4 color_speed;   // color += color_speed * dt
    float delta_time;   // delta_time computed in the render function

    // not used in the shader:
    su32 start_time_ms;   // delta_time = (current_time - start_time)/1000.0f
} rParticleRect_s;


// checks padding
_Static_assert(offsetof(rParticleRect_s, sprite_speed)
               - offsetof(rParticleRect_s, sprite)
               == 2 * sizeof(float),
               "sprite_speed must not be padded");


// creates a new rect with:
// pose = uv = eye
// color = 1
// sprite = 0
rRect_s r_rect_new();

// as new, but xy=MAX, alpha=0
rRect_s r_rect_new_hidden();

// creates a new particle rect with:
// rect = rect_new
// sprite_speed, speed, acc, color_speed = 0
// axis_angle = 0, 0, 1, 0
// start_time = 0
rParticleRect_s r_particlerect_new();

// as new, but xy=MAX, alpha=0
rParticleRect_s r_particlerect_new_hidden();


#endif //R_RECT_H
