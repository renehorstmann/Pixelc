#ifndef SOME_RO_TYPES_H
#define SOME_RO_TYPES_H

#include "rhc/types.h"
#include "types.h"

// Renders a single rect in a draw call
typedef struct {
    rRect_s rect;
    bool owns_tex;      // if true, the texture will be deleted by this class

    struct {
        GLuint program;     // shader
        GLuint vao;         // internal vertex array object
        rTexture tex;       // used texture
    } L;
} RoSingle;


// Renders multiple rects in a draw call
typedef struct {
    rRect_s *rects;
    int num;
    bool owns_tex;      // if true, the texture will be deleted by this class

    struct {
        GLuint program;     // shader
        GLuint vao;         // internal vertex array object
        GLuint vbo;         // internal vertex buffer object
        rTexture tex;       // used texture
        Allocator_i allocator;
    } L;
} RoBatch;


// Renders multiple particle rects in a draw call
typedef struct {
    rParticleRect_s *rects;
    int num;
    bool owns_tex;      // if true, the texture will be deleted by this class

    struct {
        GLuint program;     // shader
        GLuint vao;         // internal vertex array object
        GLuint vbo;         // internal vertex buffer object
        rTexture tex;       // used texture
        Allocator_i allocator;
    } L;
} RoParticle;


// Like RoSingle, but with refraction
typedef struct {
    rRect_s rect;
    const float *scale;                     // float
    const float *view_aabb;                 // vec4
    bool owns_tex_main;                     // if true, the textures will be deleted by this class
    bool owns_tex_refraction;
    const rTexture2D *tex_framebuffer_ptr;  // init as &r_render.framebuffer_tex

    struct {
        GLuint program;                         // shader
        GLuint vao;                             // internal vertex array object
        rTexture tex_main;                      // used main texture
        rTexture tex_refraction;                // used refraction texture
    } L;
} RoSingleRefract;


// Like RoBatch, but with refraction
typedef struct {
    rRect_s *rects;
    int num;
    const float *scale;                 // float
    const float *view_aabb;             // vec4
    bool owns_tex_main;                 // if true, the textures will be deleted by this class
    bool owns_tex_refraction;
    const rTexture2D *tex_framebuffer_ptr;  // init as &r_render.framebuffer_tex

    struct {
        GLuint program;                     // shader
        GLuint vao;                         // internal vertex array object
        GLuint vbo;                         // internal vertex buffer object
        rTexture tex_main;                  // used main texture
        rTexture tex_refraction;            // used refraction texture
        Allocator_i allocator;
    } L;
} RoBatchRefract;


// Like RoParticle, but with refraction
typedef struct {
    rParticleRect_s *rects;
    int num;
    const float *scale;                 // float
    const float *view_aabb;             // vec4
    bool owns_tex_main;                 // if true, the textures will be deleted by this class
    bool owns_tex_refraction;
    const rTexture2D *tex_framebuffer_ptr;  // init as &r_render.framebuffer_tex

    struct {
        GLuint program;                     // shader
        GLuint vao;                         // internal vertex array object
        GLuint vbo;                         // internal vertex buffer object
        rTexture tex_main;                  // used main texture
        rTexture tex_refraction;            // used refraction texture
        Allocator_i allocator;
    } L;
} RoParticleRefract;



// return true for a newline
typedef bool (*ro_text_sprite_fn)(vec2 *sprite, char c);

// Renders monospace text, with a texture
typedef struct {
    RoBatch ro;             // internal batch to render
    ro_text_sprite_fn sprite_fn;    // conversion function of character to sprite mapping
    mat4 pose;              // pose (top left) for the text
    vec2 size;              // character size
    vec2 offset;            // offset to next character
} RoText;


#ifdef OPTION_TTF
#include <SDL2/SDL_ttf.h>
// Renders ttf text
typedef struct {
    RoSingle ro;
    TTF_Font *font;
    float ratio;    // width / height
} RoTtfText;
#endif

#endif //SOME_RO_TYPES_H
