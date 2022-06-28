#include "m/float.h"
#include "r/rect.h"

rRect_s r_rect_new() {
    rRect_s self;
    self.pose = mat4_eye();
    self.uv = mat4_eye();
    self.color = vec4_set(1);
    self.sprite = vec2_set(0);
    return self;
}

rRect_s r_rect_new_hidden() {
    rRect_s self = r_rect_new();
    // x + y
    self.pose.m30 = self.pose.m31 = SCA_MAX;
    self.color.a = 0;
    return self;
}

rParticleRect_s r_particlerect_new() {
    rParticleRect_s self;
    self.rect = r_rect_new();

    self.sprite_speed = vec2_set(0);
    self.speed = vec4_set(0);
    self.acc = vec4_set(0);
    self.axis_angle = (vec4) {0, 0, 1, 0};
    self.color_speed = vec4_set(0);
    self.start_time_ms = 0;
    return self;
}

rParticleRect_s r_particlerect_new_hidden() {
    rParticleRect_s self = r_particlerect_new();
    // x + y
    self.pose.m30 = self.pose.m31 = SCA_MAX;
    self.color.a = 0;
    return self;
}
