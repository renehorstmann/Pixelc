#include <stdbool.h>
#include <float.h>  // FLT_MAX
#include "e/input.h"
#include "r/r.h"
#include "u/pose.h"
#include "mathc/float.h"
#include "utilc/alloc.h"
#include "hud_camera.h"
#include "brush.h"
#include "palette.h"


static struct {
    Color_s palette[PALETTE_MAX];
    int palette_size;
    rRoBatch palette_ro;
    rRoSingle select_ro;
    rRoBatch background_ro;
    int last_selected;
    float last_screen_ratio_for_updates;
} L;


static bool in_rect(ePointer_s pointer, mat4 pose) {
    vec4 screen_pos = {{pointer.x, pointer.y, 0, 1}};

    mat4 pose_inv = mat4_inv(pose);
    mat4 screen_to_rect = mat4_mul_mat(pose_inv, hud_camera_p_inv);

    vec4 rect_pos = mat4_mul_vec(screen_to_rect, screen_pos);

    float x = rect_pos.x;
    float y = rect_pos.y;
    
    return x>=-1 && x<=1 && y>=-1 && y<=1;
}

static mat4 setup_palette_color_pose(int r, int c) {
    mat4 pose = mat4_eye();
    u_pose_set_size(&pose, 18, 18);
    if(hud_camera_is_portrait_mode()) {
        u_pose_set_xy(&pose, -81 + c * 18, hud_camera_bottom() + 9 + r * 18);
    } else {
        u_pose_set_xy(&pose, hud_camera_right() - 9 - r * 18, -81 + c * 18);
        u_pose_set_angle(&pose, M_PI_2);
    }
    return pose;
}

static void setup_ro() {
    int last_row = (L.palette_size-1) / PALETTE_COLS;
    for(int i=0; i<PALETTE_MAX; i++) {
        int r = i / PALETTE_COLS;
        int c = i % PALETTE_COLS;
        
        
        mat4 pose = mat4_eye();
        if(r<=last_row)
            pose = setup_palette_color_pose(r, c);
        else
        	u_pose_set(&pose, FLT_MAX, FLT_MAX, 0, 0, 0);
        L.palette_ro.rects[i].pose = pose;
        L.background_ro.rects[i].pose = pose;
        	
        vec4 col;
        if(i<L.palette_size)
        	col = color_to_vec4(L.palette[i]);
        else
            col = R_COLOR_TRANSPARENT;
        
        L.palette_ro.rects[i].color = col;
        
        
        // background uv
        {
            float u = 0, v = 0;
            if(r < last_row) {
        	    v = 0.5;
            } else if(i >= L.palette_size) {
        	    u = 0.5;
            }
            u_pose_set(&L.background_ro.rects[i].uv, u, v, 0.5, 0.5, 0);
        }
    }
    L.select_ro.rect.pose = L.palette_ro.rects[L.last_selected].pose;

    r_ro_batch_update(&L.palette_ro, 0, PALETTE_MAX);    r_ro_batch_update(&L.background_ro, 0, PALETTE_MAX);
}


void palette_init() {
    GLuint drop_tex = r_texture_init_file("res/palette_color_drop.png", NULL);
    r_texture_filter_nearest(drop_tex);
    
    r_ro_batch_init(&L.palette_ro, PALETTE_MAX, &hud_camera_p.m00, drop_tex);
    
    
    GLuint bg_tex = r_texture_init_file("res/palette_background.png", NULL);
    r_texture_filter_nearest(bg_tex);
    
    r_ro_batch_init(&L.background_ro, PALETTE_MAX, &hud_camera_p.m00, bg_tex);
    

    GLuint select_tex = r_texture_init_file("res/palette_select.png", NULL);
    r_texture_filter_nearest(select_tex);
    r_ro_single_init(&L.select_ro, &hud_camera_p.m00, select_tex);
    
    // default palette:
    {
        Color_s palette[4] = {
        	{0, 0, 0, 0},
        	{0, 0, 0, 255},
        	{128, 128, 128, 255},
        	{255, 255, 255, 255}
        };
        palette_set_colors(palette, 4);
    }
}

bool palette_pointer_event(ePointer_s pointer) {
    if(pointer.action != E_POINTER_DOWN)
        return false;

    for(int i = 0; i<L.palette_size; i++) {
    	if(in_rect(pointer, L.palette_ro.rects[i].pose)) {
    	    palette_select_color(i);
    		return true;
    	}
   }  
    
    return false;
}


void palette_set_colors(const Color_s *palette, int size) {
    memcpy(L.palette, palette, sizeof(Color_s) * size);
    L.palette_size = size;
    palette_select_color(0);
}

void palette_select_color(int index) {
    brush_set_color(L.palette[index]);
    L.select_ro.rect.pose = L.palette_ro.rects[index].pose;
    L.last_selected = index;
}

void palette_update(float dtime) {
    // check update
    float ratio = hud_camera_width() / hud_camera_height();
    bool update = fabsf(ratio - L.last_screen_ratio_for_updates) > 0.01f;
    L.last_screen_ratio_for_updates = ratio;

    if(update) {
        setup_ro();
    }
}

void palette_render() {
    r_ro_batch_render(&L.background_ro);
    r_ro_batch_render(&L.palette_ro);
    r_ro_single_render(&L.select_ro);
}
