#include "mathc/float.h"
#include "utilc/alloc.h"
#include "r/r.h"
#include "r/ro_refract_batch.h"


static const vec4 VIEW_AABB_FULLSCREEN = {{0.5, 0.5, 0.5, 0.5}};


static void init_rects(rRect_s *instances, int num) {
    for (int i = 0; i < num; i++) {
        rRect_s *r = &instances[i];
        r->pose = mat4_eye();
        r->uv = mat4_eye();
        r->color = vec4_set(1);
    }
}

static int clamp_range(int i, int begin, int end) {
    if (i < begin)
        i = begin;
    if (i >= end)
        i = end - 1;
    return i;
}

void r_ro_refract_batch_init(rRoRefractBatch *self, int num, 
        const float *vp, const float *scale_ptr,
        GLuint tex_main_sink, GLuint tex_refraction_sink) {
    self->rects = New(rRect_s, num);
    init_rects(self->rects, num);

    self->num = num;
    self->vp = vp;
    self->scale = scale_ptr;
    self->view_aabb = &VIEW_AABB_FULLSCREEN.v0;

    self->program = r_shader_compile_glsl_from_files((char *[]) {
            "res/r/refract_batch.vsh",
            "res/r/refract_batch.fsh",
            NULL});
    const int loc_pose = 0;
    const int loc_uv = 4;
    const int loc_color = 8;

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

        // vbo
        {
            glGenBuffers(1, &self->vbo);
            glBindBuffer(GL_ARRAY_BUFFER, self->vbo);
            glBufferData(GL_ARRAY_BUFFER,
                         num * sizeof(rRect_s),
                         self->rects,
                         GL_STREAM_DRAW);

            glBindVertexArray(self->vao);

            // pose
            for (int c = 0; c < 4; c++) {
                int loc = loc_pose + c;
                glEnableVertexAttribArray(loc);
                glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE,
                                      sizeof(rRect_s), (void *) (c * sizeof(vec4)));
                glVertexAttribDivisor(loc, 1);
            }

            // uv
            for (int c = 0; c < 4; c++) {
                int loc = loc_uv + c;
                glEnableVertexAttribArray(loc);
                glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE,
                                      sizeof(rRect_s), (void *) (offsetof(rRect_s, uv) + c * sizeof(vec4)));
                glVertexAttribDivisor(loc, 1);
            }

            // color
            glEnableVertexAttribArray(loc_color);
            glVertexAttribPointer(loc_color, 4, GL_FLOAT, GL_FALSE,
                                  sizeof(rRect_s),
                                  (void *) offsetof(rRect_s, color));
            glVertexAttribDivisor(loc_color, 1);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        glBindVertexArray(0);
    }
}

void r_ro_refract_batch_kill(rRoRefractBatch *self) {
    free(self->rects);
    glDeleteProgram(self->program);
    glDeleteVertexArrays(1, &self->vao);
    glDeleteBuffers(1, &self->vbo);
    if (self->owns_tex_main)
        glDeleteTextures(1, &self->tex_main);
    if (self->owns_tex_refraction)
        glDeleteTextures(1, &self->tex_refraction);
    *self = (rRoRefractBatch) {0};
}

void r_ro_refract_batch_update_sub(rRoRefractBatch *self, int offset, int size) {
    glBindBuffer(GL_ARRAY_BUFFER, self->vbo);

    offset = clamp_range(offset, 0, self->num);
    size = clamp_range(size, 1, self->num + 1);

    if (offset + size > self->num) {
        int to_end = self->num - offset;
        int from_start = size - to_end;
        glBufferSubData(GL_ARRAY_BUFFER,
                        offset * sizeof(rRect_s),
                        to_end * sizeof(rRect_s),
                        self->rects + offset);

        glBufferSubData(GL_ARRAY_BUFFER,
                        0,
                        from_start * sizeof(rRect_s),
                        self->rects);
    } else {
        glBufferSubData(GL_ARRAY_BUFFER,
                        offset * sizeof(rRect_s),
                        size * sizeof(rRect_s),
                        self->rects + offset);

    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void r_ro_refract_batch_render_sub(rRoRefractBatch *self, int num) {
    glUseProgram(self->program);

    glUniformMatrix4fv(glGetUniformLocation(self->program, "vp"),
                       1, GL_FALSE, self->vp);

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
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, num);
        glBindVertexArray(0);
    }

    glUseProgram(0);
}

void r_ro_refract_batch_set_texture_main(rRoRefractBatch *self, GLuint tex_main_sink) {
    if (self->owns_tex_main)
        glDeleteTextures(1, &self->tex_main);
    self->tex_main = tex_main_sink;
}

void r_ro_refract_batch_set_texture_refraction(rRoRefractBatch *self, GLuint tex_refraction_sink){
    if (self->owns_tex_refraction)
        glDeleteTextures(1, &self->tex_refraction);
    self->tex_refraction = tex_refraction_sink;
}
