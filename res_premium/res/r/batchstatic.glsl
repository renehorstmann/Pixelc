#ifdef VERTEX

    layout(location = 0) in vec2 in_pos;
    layout(location = 1) in vec2 in_uv;
    layout(location = 2) in vec4 in_color;
    layout(location = 3) in vec2 in_sprite;

    out vec3 v_tex_coord;
    out vec4 v_color;

    uniform mat4 vp;
    uniform vec2 sprites;
    uniform float camera_scale_2;

    void main() {
        vec2 pos = in_pos;

        // floor into the camera grid (enable half positions for centering uneven sizes)
        pos[0] = floor(pos[0] * camera_scale_2) / camera_scale_2;
        pos[1] = floor(pos[1] * camera_scale_2) / camera_scale_2;

        gl_Position = vp * vec4(pos.x, pos.y, 0, 1);
        v_tex_coord.xy = in_uv;
        
        // glsl: actual_layer = max(0, min(d - 1, floor(layer + 0.5)) )
        vec2 s_pos = floor(mod(in_sprite+0.5, sprites));
        s_pos = clamp(s_pos, vec2(0), sprites-1.0);
        v_tex_coord.z = s_pos.y * sprites.x + s_pos.x;
        
        v_color = in_color;
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
