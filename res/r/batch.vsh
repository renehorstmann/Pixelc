layout(location = 0) in mat4 in_pose;
// uses location [0:3] (for each col)

layout(location = 4) in mat4 in_uv;
// uses location [4:7] (for each col)

layout(location = 8) in vec4 in_color;

out vec2 v_tex_coord;
out vec4 v_color;

uniform mat4 vp;

const vec4 vertices[6] = vec4[](
  vec4(-0.5, -0.5, 0, 1),
  vec4(+0.5, -0.5, 0, 1),
  vec4(-0.5, +0.5, 0, 1),
  vec4(-0.5, +0.5, 0, 1),
  vec4(+0.5, -0.5, 0, 1),
  vec4(+0.5, +0.5, 0, 1)
);

// 0-1 may overlap, so using 0-0.999999 instead
const vec4 tex_coords[6] = vec4[](
  vec4(0.000000, 0.999999, 0, 1),
  vec4(0.999999, 0.999999, 0, 1),
  vec4(0.000000, 0.000000, 0, 1),
  vec4(0.000000, 0.000000, 0, 1),
  vec4(0.999999, 0.999999, 0, 1),
  vec4(0.999999, 0.000000, 0, 1)
);

void main() {
  gl_Position = vp * in_pose * vertices[gl_VertexID];
  v_tex_coord = (in_uv * tex_coords[gl_VertexID]).xy;
  v_color = in_color;
}
