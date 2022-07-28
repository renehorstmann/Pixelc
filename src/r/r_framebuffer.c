#include "m/utils/camera.h"
#include "r/render.h"
#include "r/framebuffer.h"


rFramebuffer r_framebuffer_new(int cols, int rows) {
    r_render_error_check("r_framebuffer_newBEGIN");
    rFramebuffer self;
    glGenFramebuffers(1, &self.fbo);
    self.tex = r_texture2d_new(cols, rows, NULL);

    glBindFramebuffer(GL_FRAMEBUFFER, self.fbo);
    // 3D not working in WebGL2
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, self.tex.tex, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    r_render_error_check("r_framebuffer_new");
    return self;
}

void r_framebuffer_kill(rFramebuffer *self) {
    // invalid safe
    glDeleteFramebuffers(1, &self->fbo);
    r_texture2d_kill(&self->tex);
    *self = r_framebuffer_new_invalid();
}

void r_framebuffer_get(rFramebuffer self, void *buffer) {
    r_render_error_check("r_framebuffer_getBEGIN");

    glBindFramebuffer(GL_FRAMEBUFFER, self.fbo);
    glReadPixels(0, 0, self.tex.size.x, self.tex.size.y, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    r_render_error_check("r_framebuffer_getframebuffer");
}

mat4 r_framebuffer_camera_ortho(rFramebuffer self) {
    return mat4_camera_ortho( 0,  self.tex.size.x, 0, -self.tex.size.y, -1, 1);
}
