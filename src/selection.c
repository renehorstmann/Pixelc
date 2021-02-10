#include "utilc/alloc.h"
#include "selection.h"

static struct {
	int x, y;
	int w, h;
	Color_s *opt_data;
} L;

static bool valid_to_copy(const Image *img, int layer) {
	return L.x>=0 && L.y>=0 
	        && L.w>0 && L.h>0
	        && L.x+L.w < img->cols 
	        && L.y+L.h < img->rows;
}

void selection_init(int x, int y, int w, int h) {
	Free0(L.opt_data);
	L.x = x;
	L.y = y;
	L.w = w;
	L.h = h;
}

void selection_kill() {
	L.x = L.y = L.h = L.w = 0;
	Free0(L.opt_data);
}

bool selection_active() {
	return L.w > 0 && L.h > 0;
}

ivec2 selection_pos() {
    return (ivec2) {{L.x, L.y}};	
}
ivec2 selection_size() {
	return (ivec2) {{L.w, L.h}};
}


void selection_move(int x, int y) {
	L.x = x;
	L.y = y;
}

bool selection_contains(int x, int y) {
	return !selection_active() 
	        || (x>=L.x && x<L.x+L.w
	        && y>=L.y && y<L.y+L.h);
}

void selection_copy(const Image *from, int layer) {
    if(!valid_to_copy(from, layer)) {
		SDL_Log("selection_copy failed");
		return;
	}
    L.opt_data = ReNew(Color_s, L.opt_data, L.h * L.w);
    
    for(int r=0; r<L.h; r++) {
		for(int c=0; c<L.w; c++) {
		    L.opt_data[r*L.w + c] =
		            *image_pixel((Image *)from, layer, 
		            r+L.y, c+L.x);
		}
	}
}

void selection_cut(Image *from, int layer, Color_s replace) {
	if(!valid_to_copy(from, layer)) {
		SDL_Log("selection_cut failed");
		return;
	}
	selection_copy(from, layer);
	
	for(int r=0; r<L.h; r++) {
		for(int c=0; c<L.w; c++) {
			*image_pixel(from, layer, r+L.x, c+L.y) = replace;
		}
	}
}

void selection_paste(Image *to, int layer) {
	if(!L.opt_data || L.h <=0 || L.h <=0) {
	    SDL_Log("selection_paste failed");
	    return;
    }
	for(int r=0; r<L.h; r++) {
		int to_r = r + L.y;
		if(to_r<0 || to_r >= to->rows)
		    continue;
		for(int c=0; c<L.w; c++) {
			int to_c = c + L.x;
		    if(to_c<0 || to_c >= to->cols)
		        continue;
		        
		    *image_pixel(to, layer, to_r, to_c) =
		            L.opt_data[r*L.w + c]; 
		}
	}
}

