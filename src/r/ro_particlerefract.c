#include "m/float.h"
#include "m/sca/int.h"
#include "r/render.h"
#include "r/program.h"
#include "r/rect.h"
#include "r/texture.h"
#include "r/ro_particlerefract.h"


static const vec4 VIEW_AABB_FULLSCREEN = {{0.5, 0.5, 0.5, 0.5}};


static void calc_deltatime_sub(const RoParticleRefract *self, su32 time_ms, int num) {
    for (int i = 0; i < num; i++) {
        rParticleRect_s *r = &self->rects[i];
        r->delta_time = (time_ms - r->start_time_ms) / 1000.0f;
    }
}

// update needs to be called each time before rendering to update the time values
static void update_sub(const RoParticleRefract *self, int num) {
    r_render_error_check("ro_particlerefract_updateBEGIN");
    glBindBuffer(GL_ARRAY_BUFFER, self->L.vbo);
    glBufferSubData(GL_ARRAY_BUFFER,
                    0,
                    num * sizeof(rParticleRect_s),
                    self->rects);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    r_render_error_check("ro_particlerefract_update");
}

//
// public
//


RoParticleRefract ro_particlerefract_new(int num,
                                         rTexture tex_main_sink, rTexture tex_refraction_sink) {
    if(num <= 0)
        return ro_particlerefract_new_invalid();

    r_render_error_check("ro_particlerefract_newBEGIN");
    RoParticleRefract self;

    self.rects = s_malloc(sizeof *self.rects * num);
    for (int i = 0; i < num; i++) {
        self.rects[i] = r_particlerect_new();
    }

    self.num = num;

    self.L.program = r_program_new_file("res/r/particlerefract.glsl");
    const int loc_pose = 0;
    const int loc_uv = 4;
    const int loc_color = 8;
    const int loc_sprite_and_sprite_speed = 9;

    const int loc_speed = 10;
    const int loc_acc = 11;
    const int loc_axis_angle = 12;
    const int loc_color_speed = 13;

    const int loc_delta_time = 14;

    self.tex_main = tex_main_sink;
    self.tex_refraction = tex_refraction_sink;
    self.owns_tex_main = true;
    self.owns_tex_refraction = true;


    // vao scope
    {
        glGenVertexArrays(1, &self.L.vao);
        glBindVertexArray(self.L.vao);

        // vbo
        {
            glGenBuffers(1, &self.L.vbo);
            glBindBuffer(GL_ARRAY_BUFFER, self.L.vbo);
            glBufferData(GL_ARRAY_BUFFER,
                         num * sizeof(rParticleRect_s),
                         self.rects,
                         GL_STREAM_DRAW);

            glBindVertexArray(self.L.vao);

            // pose
            for (int c = 0; c < 4; c++) {
                int loc = loc_pose + c;
                glEnableVertexAttribArray(loc);
                glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE,
                                      sizeof(rParticleRect_s), (void *) (c * sizeof(vec4)));
                glVertexAttribDivisor(loc, 1);
            }

            // uv
            for (int c = 0; c < 4; c++) {
                int loc = loc_uv + c;
                glEnableVertexAttribArray(loc);
                glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE,
                                      sizeof(rParticleRect_s),
                                      (void *) (offsetof(rParticleRect_s, uv) + c * sizeof(vec4)));
                glVertexAttribDivisor(loc, 1);
            }


            // color
            glEnableVertexAttribArray(loc_color);
            glVertexAttribPointer(loc_color, 4, GL_FLOAT, GL_FALSE,
                                  sizeof(rParticleRect_s),
                                  (void *) offsetof(rParticleRect_s, color));
            glVertexAttribDivisor(loc_color, 1);

            // sprite_and_sprite_speed
            glEnableVertexAttribArray(loc_sprite_and_sprite_speed);
            glVertexAttribPointer(loc_sprite_and_sprite_speed, 4, GL_FLOAT, GL_FALSE,
                                  sizeof(rParticleRect_s),
                                  (void *) offsetof(rParticleRect_s, sprite));
            glVertexAttribDivisor(loc_sprite_and_sprite_speed, 1);

            // speed
            glEnableVertexAttribArray(loc_speed);
            glVertexAttribPointer(loc_speed, 4, GL_FLOAT, GL_FALSE,
                                  sizeof(rParticleRect_s),
                                  (void *) offsetof(rParticleRect_s, speed));
            glVertexAttribDivisor(loc_speed, 1);

            // acc
            glEnableVertexAttribArray(loc_acc);
            glVertexAttribPointer(loc_acc, 4, GL_FLOAT, GL_FALSE,
                                  sizeof(rParticleRect_s),
                                  (void *) offsetof(rParticleRect_s, acc));
            glVertexAttribDivisor(loc_acc, 1);

            // axis_angle
            glEnableVertexAttribArray(loc_axis_angle);
            glVertexAttribPointer(loc_axis_angle, 4, GL_FLOAT, GL_FALSE,
                                  sizeof(rParticleRect_s),
                                  (void *) offsetof(rParticleRect_s, axis_angle));
            glVertexAttribDivisor(loc_axis_angle, 1);

            // color_speed
            glEnableVertexAttribArray(loc_color_speed);
            glVertexAttribPointer(loc_color_speed, 4, GL_FLOAT, GL_FALSE,
                                  sizeof(rParticleRect_s),
                                  (void *) offsetof(rParticleRect_s, color_speed));
            glVertexAttribDivisor(loc_color_speed, 1);

            // start_time
            glEnableVertexAttribArray(loc_delta_time);
            glVertexAttribPointer(loc_delta_time, 1, GL_FLOAT, GL_FALSE,
                                  sizeof(rParticleRect_s),
                                  (void *) offsetof(rParticleRect_s, delta_time));
            glVertexAttribDivisor(loc_delta_time, 1);


            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        glBindVertexArray(0);
    }

    r_render_error_check("ro_particlerefract_new");
    return self;
}


void ro_particlerefract_kill(RoParticleRefract *self) {
    if(!ro_particlerefract_valid(self))
        return;
    s_free(self->rects);
    glDeleteProgram(self->L.program);
    glDeleteVertexArrays(1, &self->L.vao);
    glDeleteBuffers(1, &self->L.vbo);
    if (self->owns_tex_main)
        r_texture_kill(&self->tex_main);
    if (self->owns_tex_refraction)
        r_texture_kill(&self->tex_refraction);
    *self = (RoParticleRefract) {0};
}


void ro_particlerefract_render_raw_sub(const RoParticleRefract *self, int num, const mat4 *camera_mat,
                                       float scale, const vec4 *opt_view_aabb, const rTexture2D *opt_framebuffer) {
    if(!ro_particlerefract_valid(self))
        return;

    num = isca_clamp(num, 1, self->num);

    update_sub(self, num);

    r_render_error_check("ro_particlerefract_render_rawBEGIN");

    if (!opt_view_aabb)
        opt_view_aabb = &VIEW_AABB_FULLSCREEN;
    if (!opt_framebuffer) {
        opt_framebuffer = &r_render.framebuffer_tex;

    }

    glUseProgram(self->L.program);

    // base
    glUniformMatrix4fv(glGetUniformLocation(self->L.program, "vp"),
                       1, GL_FALSE, &camera_mat->m00);

    vec2 sprites = vec2_cast_from_int(&self->tex_main.sprites.v0);
    glUniform2fv(glGetUniformLocation(self->L.program, "sprites"), 1, &sprites.v0);

    // camera_scale_2 = camera_scale*2
    glUniform1f(glGetUniformLocation(self->L.program, "camera_scale_2"), r_render.camera_scale*2);

    // fragment shader
    glUniform1f(glGetUniformLocation(self->L.program, "scale"), scale);

    glUniform4fv(glGetUniformLocation(self->L.program, "view_aabb"), 1, opt_view_aabb->v);

    glUniform1i(glGetUniformLocation(self->L.program, "tex_main"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, self->tex_main.tex);

    glUniform1i(glGetUniformLocation(self->L.program, "tex_refraction"), 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D_ARRAY, self->tex_refraction.tex);

    glUniform1i(glGetUniformLocation(self->L.program, "tex_framebuffer"), 2);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, opt_framebuffer->tex);

    {
        glBindVertexArray(self->L.vao);
        // r_program_validate(self->L.program); // debug test
        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, num);
        glBindVertexArray(0);
    }

    glUseProgram(0);
    r_render_error_check("ro_particlerefract_render_raw");
}

void ro_particlerefract_render_sub(const RoParticleRefract *self, uint32_t time_ms, int num, const mat4 *camera_mat,
                                   float scale, const vec4 *opt_view_aabb, const rTexture2D *opt_framebuffer) {
    if(!ro_particlerefract_valid(self))
        return;

    num = isca_clamp(num, 1, self->num);
    calc_deltatime_sub(self, time_ms, num);
    ro_particlerefract_render_raw_sub(self, num, camera_mat, scale, opt_view_aabb, opt_framebuffer);
}

void ro_particlerefract_set_texture_main(RoParticleRefract *self, rTexture tex_main_sink) {
    if(!ro_particlerefract_valid(self))
        return;

    if (self->owns_tex_main)
        r_texture_kill(&self->tex_main);
    self->tex_main = tex_main_sink;
}

void ro_particlerefract_set_texture_refraction(RoParticleRefract *self, rTexture tex_refraction_sink) {
    if(!ro_particlerefract_valid(self))
        return;

    if (self->owns_tex_refraction)
        r_texture_kill(&self->tex_refraction);
    self->tex_refraction = tex_refraction_sink;
}
