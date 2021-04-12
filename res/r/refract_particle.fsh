in vec2 v_tex_coord;
in vec4 v_color;

out vec4 out_frag_color;

uniform float scale; // aka real_pixel_per_pixel
// in texture space (origin is top left) [0:1]
// as center_x, _y, radius_x, _y
// example for fullscreen: 0.5, 0.5, 0.5, 0.5
uniform vec4 view_aabb;


uniform sampler2D tex_main;
uniform sampler2D tex_refraction;
uniform sampler2D tex_framebuffer;


// returns the distance to the border of space
// space as aabb in center_x, center_y, radius_x, radius_y
float space_distance(vec2 pos, vec4 space) {
    vec2 center = space.xy;
    vec2 radius = space.zw;
    vec2 dist = max(vec2(0, 0), radius - abs(pos-center));
    return min(dist.x, dist.y);
}


void main() {
    
    vec2 size = vec2(textureSize(tex_framebuffer, 0));
    
    vec4 refract = texture(tex_refraction, v_tex_coord);
    
    vec2 offset = (refract.xy - 0.5f) * 256.0f * scale;
    
    vec2 r_coord;
    r_coord.x = (gl_FragCoord.x + offset.x) / size.x;
    r_coord.y = 1.0f - (gl_FragCoord.y + offset.y) / size.y;
    
    float alpha = mix(refract.a, 0.0f, 
            max(0.0f, 1.0f-5.0f*space_distance(r_coord, view_aabb)));
    
    vec4 color = texture(tex_main, v_tex_coord);
    color.rgb = mix(color.rgb,
            texture(tex_framebuffer, r_coord).rgb, alpha);
           
    out_frag_color = color * v_color;
}
