#ifdef VERTEX
    
    layout(location = 0) in mat4 in_pose;
    // uses location [0:4] (for each col)

    layout(location = 4) in mat4 in_uv;
    // uses location [4:7] (for each col)

    layout(location = 8) in vec4 in_color;
    layout(location = 9) in vec4 in_sprite_and_sprite_speed;
    
    layout(location = 10) in vec4 in_speed;
    layout(location = 11) in vec4 in_acc;
    layout(location = 12) in vec4 in_axis_angle;
    layout(location = 13) in vec4 in_color_speed;

    layout(location = 14) in float in_delta_time;

    // on some Browsers (Chrome on Desktop?!?) location = 15 is not valid, even if GL_MAX_VERTEX_ATTRIBS == 16

    out vec3 v_tex_coord;
    out vec4 v_color;

    uniform mat4 vp;
    uniform vec2 sprites;
    uniform float camera_scale_2;

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


    // axis must be normalized
    mat4 axis_angle_to_rot_mat(vec3 axis, float angle) {
        // equation from: https://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToMatrix/index.htm
        float c = cos(angle);
        float s = sin(angle);
        float t = 1.0f - c;
        float x = axis.x;
        float y = axis.y;
        float z = axis.z;
        return mat4(
        t*x*x+c, t*x*y+z*s, t*x*z-y*s, 0, // col 0=x_axis
        t*x*y-z*s, t*y*y+c, t*y*z+x*s, 0, // col 1=y_axis
        t*x*z+y*s, t*y*z-x*s, t*z*z+c, 0, // col 2=z_axis
        0, 0, 0, 1
        );
    }


    void main() {
        vec2 in_sprite = in_sprite_and_sprite_speed.xy;
        vec2 in_sprite_speed = in_sprite_and_sprite_speed.zw;
        
        
        float dt = in_delta_time;

        vec4 pos = vertices[gl_VertexID];


        pos = axis_angle_to_rot_mat(in_axis_angle.xyz, in_axis_angle.w * dt) * pos;

        pos = in_pose * pos;
        pos += in_speed * dt;
        pos += in_acc * (dt * dt);

        // floor into the camera grid (enable half positions for centering uneven sizes)
        pos.xy = floor(pos.xy * camera_scale_2) / camera_scale_2;

        gl_Position = vp * pos;

        v_tex_coord.xy = (in_uv * tex_coords[gl_VertexID]).xy;
        
        // glsl: actual_layer = max(0, min(d - 1, floor(layer + 0.5)) )
        vec2 sprite = in_sprite + in_sprite_speed * dt;
        vec2 s_pos = floor(mod(sprite+0.5, sprites));
        s_pos = clamp(s_pos, vec2(0), sprites-1.0);
        v_tex_coord.z = s_pos.y * sprites.x + s_pos.x;
        

        v_color = in_color + (in_color_speed * dt);
    }

#endif


#ifdef FRAGMENT
    #ifdef OPTION_GLES
        precision mediump float;
        precision lowp sampler2DArray;
    #endif

    in vec3 v_tex_coord;
    in vec4 v_color;

    out vec4 out_frag_color;

    uniform sampler2DArray tex;

    void main() {
        out_frag_color = texture(tex, v_tex_coord) * v_color;
    }
#endif
