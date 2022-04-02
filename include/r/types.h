#ifndef SOME_R_TYPES_H
#define SOME_R_TYPES_H

#include <stddef.h> // offsetof
#include "core.h"
#include "mathc/types/int.h"

// Texture, with sprite grid -> 2D array texture
typedef struct {
    GLuint tex;    // GL_TEXTURE_2D_ARRAY
    ivec2 sprite_size;
    ivec2 sprites;
} rTexture;


// Simple Texture, without a sprite grid
typedef struct {
    GLuint tex;    // GL_TEXTURE_2D
    ivec2 size;
} rTexture2D;


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
    float start_time;   // dt = current_time - start_time
} rParticleRect_s;

// checks padding
_Static_assert(offsetof(rParticleRect_s, sprite_speed)
               - offsetof(rParticleRect_s, sprite)
               == 2 * sizeof(float),
               "sprite_speed must not be padded");



#endif //SOME_R_TYPES_H
