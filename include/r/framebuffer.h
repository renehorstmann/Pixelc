#ifndef R_FRAMEBUFFER_H
#define R_FRAMEBUFFER_H

//
// A framebuffer is the buffer on the gpu in which all draw calls are rendered
// The default window framebuffer can be grabbed by r/render.h
//

#include "texture2d.h"
#include "m/types/float.h"

// A framebuffer and its size
typedef struct {
    GLuint fbo;         // GL_FRAMEBUFFER
    rTexture2D tex;
} rFramebuffer;


static bool r_framebuffer_valid(rFramebuffer self) {
    return self.fbo > 0 && r_texture2d_valid(self.tex);
}

static rFramebuffer r_framebuffer_new_invalid() {
    return (rFramebuffer) {0};
}

// creates a new framebuffer with the given size
rFramebuffer r_framebuffer_new(int cols, int rows);

void r_framebuffer_kill(rFramebuffer *self);

// updates buffer with the content of the framebuffer
// buffer has to be the size of:
//     4 * size.x * _y
// may be not as costly as r_texture2d_get which will create a new framebuffer
// must not be r_render.framebuffer which has no texture
void r_framebuffer_get(rFramebuffer self, void *buffer);

// returns an orthogonal camera for the given Framebuffer
// 0, 0 is in the top left corner
mat4 r_framebuffer_camera_ortho(rFramebuffer self);

#endif //R_FRAMEBUFFER_H
