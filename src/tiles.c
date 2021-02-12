#include "r/ro_single.h"
#include "r/texture.h"
#include "u/pose.h"
#include "camera.h"
#include "canvas.h"
#include "tiles.h"

#define SIZE 1
 
struct TilesGlobals_s tiles;

static struct {
	rRoSingle ro;
	
} L;


void tiles_init() {
	Image *img = canvas_image();
	GLuint tex = r_texture_init(img->cols, img->rows, image_layer(img, canvas.current_layer));
	
	r_ro_single_init(&L.ro, camera.gl, tex);
	u_pose_set_w(&L.ro.rect.uv, 1.0);
}

void tiles_update(float dtime) {
	Image *img = canvas_image();
	r_texture_update(L.ro.tex, img->cols, img->rows, image_layer(img, canvas.current_layer));
	
	float w = img->cols;
	float h = img->rows;
	
	u_pose_set_size(&L.ro.rect.pose, camera_width(), camera_height());
    u_pose_set_size(&L.ro.rect.uv, camera_width()/w, camera_height()/h);
    
    float ux = -(camera_right() + camera_left()) / (2*w);
    float uy = (camera_bottom() + camera_top()) / (2*h);
    
    u_pose_set_xy(&L.ro.rect.uv, ux, uy);
}

void tiles_render() {
	if(tiles.show)
	    r_ro_single_render(&L.ro);
}
