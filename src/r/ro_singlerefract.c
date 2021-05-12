#include "mathc/float.h"
#include "r/render.h"
#include "r/program.h"
#include "r/ro_singlerefract.h"


static const vec4 VIEW_AABB_FULLSCREEN = {{0.5, 0.5, 0.5, 0.5}};


RoSingleRefract ro_singlerefract_new(
        const float *vp, const float *scale_ptr,
        rTexture tex_main_sink, rTexture tex_refraction_sink){
                                
    r_render_error_check("ro_singlerefract_newBEGIN");
    RoSingleRefract self;
    
    self.rect = r_rect_new();

    self.vp = vp;
    self.scale = scale_ptr;
    self.view_aabb = &VIEW_AABB_FULLSCREEN.v0;

    self.L.program = r_program_new_file("res/r/singlerefract.glsl");
    
    self.L.tex_main = tex_main_sink;
    self.L.tex_refraction = tex_refraction_sink;
    self.owns_tex_main = true;
    self.owns_tex_refraction = true;
    
    self.tex_framebuffer_ptr = &r_render.framebuffer_tex;

    // needs a vao, even if its empty
    glGenVertexArrays(1, &self.L.vao);

    r_render_error_check("ro_singlerefract_new");
    return self;
}

void ro_singlerefract_kill(RoSingleRefract *self) {
    glDeleteProgram(self->L.program);
    if (self->owns_tex_main)
        r_texture_kill(&self->L.tex_main);
    if (self->owns_tex_refraction)
        r_texture_kill(&self->L.tex_refraction);
    *self = (RoSingleRefract) {0};
}


void ro_singlerefract_render(RoSingleRefract *self) {
    r_render_error_check("ro_singlerefract_renderBEGIN");
    glUseProgram(self->L.program);

    // rect
    glUniformMatrix4fv(glGetUniformLocation(self->L.program, "pose"), 1, GL_FALSE, &self->rect.pose.m00);

    glUniformMatrix4fv(glGetUniformLocation(self->L.program, "uv"), 1, GL_FALSE, &self->rect.uv.m00);

    glUniform4fv(glGetUniformLocation(self->L.program, "color"), 1, &self->rect.color.v0);
    
    glUniform2fv(glGetUniformLocation(self->L.program, "sprite"), 1, &self->rect.sprite.v0);

    // base
    glUniformMatrix4fv(glGetUniformLocation(self->L.program, "vp"), 1, GL_FALSE, self->vp);
    
    vec2 sprites = vec2_cast_from_int(&self->L.tex_main.sprites.v0);
    glUniform2fv(glGetUniformLocation(self->L.program, "sprites"), 1, &sprites.v0);

    
    // fragment shader
    glUniform1f(glGetUniformLocation(self->L.program, "scale"), *self->scale);
    
    glUniform4fv(glGetUniformLocation(self->L.program, "view_aabb"), 1, self->view_aabb);

    glUniform1i(glGetUniformLocation(self->L.program, "tex_main"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, self->L.tex_main.tex);
    
    glUniform1i(glGetUniformLocation(self->L.program, "tex_refract"), 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D_ARRAY, self->L.tex_refraction.tex);
    
    glUniform1i(glGetUniformLocation(self->L.program, "tex_framebuffer"), 2);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, self->tex_framebuffer_ptr->tex);

    {
        glBindVertexArray(self->L.vao);
//        r_program_validate(self->L.program); // debug test
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    glUseProgram(0);
    r_render_error_check("ro_singlerefract_render");
}

void ro_singlerefract_set_texture_main(RoSingleRefract *self, rTexture tex_main_sink) {
    if (self->owns_tex_main)
        r_texture_kill(&self->L.tex_main);
    self->L.tex_main = tex_main_sink;
}

void ro_singlerefract_set_texture_refraction(RoSingleRefract *self, rTexture tex_refraction_sink){
    if (self->owns_tex_refraction)
        r_texture_kill(&self->L.tex_refraction);
    self->L.tex_refraction = tex_refraction_sink;
}
