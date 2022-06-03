#ifdef VERTEX

    out vec3 v_tex_coord;
    out vec4 v_color;

    uniform mat4 pose;
    uniform mat4 uv;
    uniform vec4 color;
    uniform vec2 sprite;
    
    uniform mat4 vp;
    uniform vec2 sprites;

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
        v_tex_coord.xy = (uv * tex_coords[gl_VertexID]).xy;
        
        // glsl: actual_layer = max(0, min(d​ - 1, floor(layer​ + 0.5)) )
        vec2 s_pos = floor(mod(sprite+0.5, sprites));
        s_pos = clamp(s_pos, vec2(0), sprites-1.0);
        v_tex_coord.z = s_pos.y * sprites.x + s_pos.x;
        
        v_color = color;
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
