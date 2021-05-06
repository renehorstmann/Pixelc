#include "mathc/float.h"
#include "mathc/sca/int.h"
#include "r/render.h"
#include "r/program.h"
#include "r/ro_batch.h"



RoBatch ro_batch_new_a(int num, const float *vp, rTexture tex_sink, Allocator_s alloc) {
    r_render_error_check("ro_batch_newBEGIN");
    RoBatch self;
    self.allocator = alloc;
    
    assume(num>0, "batch needs atleast 1 rect");
    self.rects = alloc.malloc(alloc, num * sizeof(rRect_s));
    assume(self.rects, "allocation failed");
    for(int i=0; i<num; i++) {
        self.rects[i] = r_rect_new();
    }

    self.num = num;
    self.vp = vp;

    self.program = r_program_new_file("res/r/batch.glsl");
    const int loc_pose = 0;
    const int loc_uv = 4;
    const int loc_color = 8;
    const int loc_sprite = 9;

    self.tex = tex_sink;
    self.owns_tex = true;

    // vao scope
    {
        glGenVertexArrays(1, &self.vao);
        glBindVertexArray(self.vao);

        // vbo
        {
            glGenBuffers(1, &self.vbo);
            glBindBuffer(GL_ARRAY_BUFFER, self.vbo);
            glBufferData(GL_ARRAY_BUFFER,
                         num * sizeof(rRect_s),
                         self.rects,
                         GL_STREAM_DRAW);

            glBindVertexArray(self.vao);

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
            
            // sprite
            glEnableVertexAttribArray(loc_sprite);
            glVertexAttribPointer(loc_sprite, 2, GL_FLOAT, GL_FALSE,
                                  sizeof(rRect_s),
                                  (void *) offsetof(rRect_s, sprite));
            glVertexAttribDivisor(loc_sprite, 1);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        glBindVertexArray(0);
    }
    
    r_render_error_check("ro_batch_new");
    return self;
}



void ro_batch_kill(RoBatch *self) {
    self->allocator.free(self->allocator, self->rects);
    glDeleteProgram(self->program);
    glDeleteVertexArrays(1, &self->vao);
    glDeleteBuffers(1, &self->vbo);
    if (self->owns_tex)
        r_texture_kill(&self->tex);
    *self = (RoBatch) {0};
}

void ro_batch_update_sub(RoBatch *self, int offset, int size) {
    r_render_error_check("ro_batch_updateBEGIN");
    glBindBuffer(GL_ARRAY_BUFFER, self->vbo);

    offset = isca_clamp(offset, 0, self->num-1);
    size = isca_clamp(size, 1, self->num);

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
    r_render_error_check("ro_batch_update");
}


void ro_batch_render_sub(RoBatch *self, int num) {
    r_render_error_check("ro_batch_renderBEGIN");
    glUseProgram(self->program);

    // base
    glUniformMatrix4fv(glGetUniformLocation(self->program, "vp"),
                       1, GL_FALSE, self->vp);
                       
    vec2 sprites = vec2_cast_from_int(&self->tex.sprites.v0);
    glUniform2fv(glGetUniformLocation(self->program, "sprites"), 1, &sprites.v0);

    glUniform1i(glGetUniformLocation(self->program, "tex"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, self->tex.tex);

    {
        glBindVertexArray(self->vao);
        // r_program_validate(self->program); // debug test
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, num);
        glBindVertexArray(0);
    }

    glUseProgram(0);
    r_render_error_check("ro_batch_render");
}

void ro_batch_set_texture(RoBatch *self, rTexture tex_sink) {
    if (self->owns_tex)
        r_texture_kill(&self->tex);
    self->tex = tex_sink;
}

