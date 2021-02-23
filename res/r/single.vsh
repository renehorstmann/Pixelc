out vec2 v_tex_coord;
out vec4 v_color;

uniform mat4 pose;
uniform mat4 vp;
uniform mat4 uv;
uniform vec4 color;


const vec4 vertices[6] = vec4[](
vec4(-0.5, -0.5, 0, 1),
vec4(+0.5, -0.5, 0, 1),
vec4(-0.5, +0.5, 0, 1),
vec4(-0.5, +0.5, 0, 1),
vec4(+0.5, -0.5, 0, 1),
vec4(+0.5, +0.5, 0, 1)
);

// 0-1 may overlap, so using 0-0.9999999 instead
const vec4 tex_coords[6] = vec4[](
vec4(0.0000000, 0.9999999, 0, 1),
vec4(0.9999999, 0.9999999, 0, 1),
vec4(0.0000000, 0.0000000, 0, 1),
vec4(0.0000000, 0.0000000, 0, 1),
vec4(0.9999999, 0.9999999, 0, 1),
vec4(0.9999999, 0.0000000, 0, 1)
);

void main() {
    gl_Position = vp * pose * vertices[gl_VertexID];
    v_tex_coord = (uv * tex_coords[gl_VertexID]).xy;
    v_color = color;
}
