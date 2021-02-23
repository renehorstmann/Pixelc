#include "r/ro_single.h"
#include "r/ro_text.h"
#include "r/texture.h"
#include "u/pose.h"
#include "camera.h"
#include "canvas.h"
#include "palette.h"
#include "animation.h"

#define SIZE 1

struct AnimationGlobals_s animation;


static struct {
	rRoText horsimann;
	rRoSingle ro;
	int mcols, mrows;
    int frames;
    float time;	
    float fps;
} L;

static void set_pose(int c, int r) {
	Image *img = canvas_image();
	r_texture_update(L.ro.tex, img->cols, img->rows, image_layer(img, canvas.current_layer));

    float w = SIZE * img->cols / L.frames;
    float h = SIZE * img->rows;
    
    float x, y;
    if(camera_is_portrait_mode()) {
    	x = camera_left() + w / 2 + 2 + c*w;
        y = camera_bottom() + palette_get_hud_size() + h / 2 + r*h;
    } else {
    	x = camera_right() - palette_get_hud_size() - w / 2 - c*w;
    	y = camera_top() - h / 2 - 2 - r*h;
    }
    
    u_pose_set(&L.ro.rect.pose, 
        floorf(x), floorf(y), w, h, 0);
}

void animation_init(int multi_cols, int multi_rows, int frames, float fps) {
	L.mcols = multi_cols;
	L.mrows = multi_rows;
	L.frames = frames;
	L.fps = fps;
	
	Image *img = canvas_image();
	GLuint tex = r_texture_init(img->cols, img->rows, image_layer(img, canvas.current_layer));
	
	r_ro_single_init(&L.ro, camera.gl, tex);
	u_pose_set_w(&L.ro.rect.uv, 1.0/frames);
	
	r_ro_text_init_font55(&L.horsimann, 9, camera.gl);
	vec4 color = {{0.25, 0.25, 0.25, 1}};
	for(int i=0; i<L.horsimann.ro.num; i++) {
		L.horsimann.ro.rects[i].color = color;
	}
	r_ro_text_set_text(&L.horsimann, "horsimann");
	
}

void animation_update(float dtime) {
	if(!animation.show) {
	    if(camera_is_portrait_mode())
		    u_pose_set_xy(&L.horsimann.pose,
		        camera_left()+1, 
		        ceilf(camera_bottom() + palette_get_hud_size() + 6));
	    else
		    u_pose_set_xy(&L.horsimann.pose,
		       camera_left()+30, ceilf(camera_bottom() + 6));	
	    return;
	}
	
	L.time = fmodf(L.time + dtime, L.frames / L.fps);
	float u = floorf(L.time * L.fps) / L.frames;
	u_pose_set_x(&L.ro.rect.uv, u);
}

void animation_render() {
	if(!animation.show) {
	    r_ro_text_render(&L.horsimann);
	    return;
	}
	    
	for(int r=0; r<L.mrows; r++) {
		for(int c=0; c<L.mcols; c++) {
			set_pose(c, r);
			r_ro_single_render(&L.ro);
		}
	}
}

