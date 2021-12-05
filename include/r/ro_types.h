#ifndef SOME_RO_TYPES_H
#define SOME_RO_TYPES_H

#include "types.h"

// Renders a single rect in a draw call
typedef struct {
    rRect_s rect;
    rTexture tex;       // used texture
    bool owns_tex;      // if true (default), tex will be killed by this class

    struct {
        GLuint program;     // shader
        GLuint vao;         // internal vertex array object
    } L;
} RoSingle;


// Renders multiple rects in a draw call
typedef struct {
    rRect_s *rects;
    int num;
    rTexture tex;       // used texture
    bool owns_tex;      // if true (default), text will be killed by this class

    struct {
        GLuint program;     // shader
        GLuint vao;         // internal vertex array object
        GLuint vbo;         // internal vertex buffer object
    } L;
} RoBatch;


// Renders multiple particle rects in a draw call
typedef struct {
    rParticleRect_s *rects;
    int num;
    rTexture tex;       // used texture
    bool owns_tex;      // if true (default), tex will be killed by this class

    struct {
        GLuint program;     // shader
        GLuint vao;         // internal vertex array object
        GLuint vbo;         // internal vertex buffer object
    } L;
} RoParticle;


// Like RoSingle, but with refraction
typedef struct {
    rRect_s rect;
    rTexture tex_main;          // used main texture
    rTexture tex_refraction;    // used refraction texture
    bool owns_tex_main;         // if true (default), tex_main will be killed by this class
    bool owns_tex_refraction;   // if true (default), tex_refraction will be killer by this clasd
    
    struct {
        GLuint program;         // shader
        GLuint vao;             // internal vertex array object
    } L;
} RoSingleRefract;


// Like RoBatch, but with refraction
typedef struct {
    rRect_s *rects;
    int num;
    rTexture tex_main;          // used main texture
    rTexture tex_refraction;    // used refraction texture
    bool owns_tex_main;         // if true (default), tex_main will be killed by this class
    bool owns_tex_refraction;   // if true (default), tex_refraction will be killer by this clasd

    struct {
        GLuint program;         // shader
        GLuint vao;             // internal vertex array object
        GLuint vbo;             // internal vertex buffer object
    } L;
} RoBatchRefract;


// Like RoParticle, but with refraction
typedef struct {
    rParticleRect_s *rects;
    int num;
    rTexture tex_main;          // used main texture
    rTexture tex_refraction;    // used refraction texture
    bool owns_tex_main;         // if true (default), tex_main will be killed by this class
    bool owns_tex_refraction;   // if true (default), tex_refraction will be killer by this clasd

    struct {
        GLuint program;         // shader
        GLuint vao;             // internal vertex array object
        GLuint vbo;             // internal vertex buffer object
    } L;
} RoParticleRefract;


// text sprite from char callback
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
