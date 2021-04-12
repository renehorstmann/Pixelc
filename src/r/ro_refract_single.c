#include "mathc/float.h"
#include "r/render.h"
#include "r/shader.h"
#include "r/ro_refract_single.h"


static const vec4 VIEW_AABB_FULLSCREEN = {{0.5, 0.5, 0.5, 0.5}};


void ro_refract_single_init(RoRefractSingle *self,
        const float *vp, const float *scale_ptr,
        GLuint tex_main_sink, GLuint tex_refraction_sink){
    self->rect.pose = mat4_eye();
    self->rect.uv = mat4_eye();
    self->rect.color = vec4_set(1);

    self->vp = vp;
    self->scale = scale_ptr;
    self->view_aabb = &VIEW_AABB_FULLSCREEN.v0;

    self->program = r_shader_compile_glsl_from_files((char *[]) {
            "res/r/refract_single.vsh",
            "res/r/refract_single.fsh",
            NULL
    });

    self->tex_main = tex_main_sink;
    self->tex_refraction = tex_refraction_sink;
    self->owns_tex_main = true;
    self->owns_tex_refraction = true;
    
    self->tex_framebuffer_ptr = &r_render.framebuffer_tex;

    // vao scope
    {
        glGenVertexArrays(1, &self->vao);
        glBindVertexArray(self->vao);

        // textures
        glUniform1i(glGetUniformLocation(self->program, "tex_main"), 0);
        
        glUniform1i(glGetUniformLocation(self->program, "tex_refraction"), 1);
        
        glUniform1i(glGetUniformLocation(self->program, "tex_framebuffer"), 2);

        glBindVertexArray(0);
    }
}

void ro_refract_single_kill(RoRefractSingle *self) {
    glDeleteProgram(self->program);
    glDeleteVertexArrays(1, &self->vao);
    if (self->owns_tex_main)
        glDeleteTextures(1, &self->tex_main);
    if (self->owns_tex_refraction)
        glDeleteTextures(1, &self->tex_refraction);
    *self = (RoRefractSingle) {0};
}


void ro_refract_single_render(RoRefractSingle *self) {
    glUseProgram(self->program);

    glUniformMatrix4fv(glGetUniformLocation(self->program, "pose"), 1, GL_FALSE, &self->rect.pose.m00);

    glUniformMatrix4fv(glGetUniformLocation(self->program, "vp"), 1, GL_FALSE, self->vp);

    glUniformMatrix4fv(glGetUniformLocation(self->program, "uv"), 1, GL_FALSE, &self->rect.uv.m00);

    glUniform4fv(glGetUniformLocation(self->program, "color"), 1, &self->rect.color.v0);
    
    // fragment shader
    glUniform1f(glGetUniformLocation(self->program, "scale"), *self->scale);
    
    glUniform4fv(glGetUniformLocation(self->program, "view_aabb"), 1, self->view_aabb);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, self->tex_main);
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, self->tex_refraction);
    
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, *self->tex_framebuffer_ptr);

    {
        glBindVertexArray(self->vao);
        // r_shader_validate(self->program); // debug test
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    glUseProgram(0);
}

void ro_refract_single_set_texture_main(RoRefractSingle *self, GLuint tex_main_sink) {
    if (self->owns_tex_main)
        glDeleteTextures(1, &self->tex_main);
    self->tex_main = tex_main_sink;
}

void ro_refract_single_set_texture_refraction(RoRefractSingle *self, GLuint tex_refraction_sink){
    if (self->owns_tex_refraction)
        glDeleteTextures(1, &self->tex_refraction);
    self->tex_refraction = tex_refraction_sink;
}
