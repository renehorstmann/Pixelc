#include "utilc/alloc.h"
#include "selection.h"

static struct {
	int left, top;
	int cols, rows;
	Color_s *opt_data;
} L;

static bool valid_to_copy(const Image *img, int layer) {
	return L.left>=0 && L.top>=0 
	        && L.cols>0 && L.rows>0
	        && L.left+L.cols < img->cols 
	        && L.top+L.rows < img->rows;
}

void selection_init(int left, int top, int cols, int rows) {
	Free0(L.opt_data);
	L.left = left;
	L.top = top;
	L.cols = cols;
	L.rows = rows;
}

void selection_kill() {
	L.left = L.top = L.rows = L.cols = 0;
	Free0(L.opt_data);
}

bool selection_active() {
	return L.cols > 0 && L.rows > 0;
}

ivec2 selection_pos() {
    return (ivec2) {{L.left, L.top}};	
}
ivec2 selection_size() {
	return (ivec2) {{L.cols, L.rows}};
}


void selection_move(int left, int top) {
	L.left = left;
	L.top = top;
}

bool selection_contains(int c, int r) {
	return !selection_active() 
	        || (c>=L.left && c<L.left+L.cols
	        && r>=L.top && r<L.top+L.rows);
}

void selection_copy(const Image *from, int layer) {
    if(!valid_to_copy(from, layer)) {
		SDL_Log("selection_copy failed");
		return;
	}
    L.opt_data = ReNew(Color_s, L.opt_data, L.rows * L.cols);
    
    for(int r=0; r<L.rows; r++) {
		for(int c=0; c<L.cols; c++) {
		    L.opt_data[r*L.cols + c] =
		            *image_pixel((Image *)from, layer, 
		            c+L.left, r+L.top);
		}
	}
}

void selection_cut(Image *from, int layer, Color_s replace) {
	if(!valid_to_copy(from, layer)) {
		SDL_Log("selection_cut failed");
		return;
	}
	selection_copy(from, layer);
	
	for(int r=0; r<L.rows; r++) {
		for(int c=0; c<L.cols; c++) {
			*image_pixel(from, layer, c+L.left, r+L.top) = replace;
		}
	}
}

void selection_paste(Image *to, int layer) {
	if(!L.opt_data || L.rows <=0 || L.rows <=0) {
	    SDL_Log("selection_paste failed");
	    return;
    }
	for(int r=0; r<L.rows; r++) {
		int to_r = r + L.top;
		if(to_r<0 || to_r >= to->rows)
		    continue;
		for(int c=0; c<L.cols; c++) {
			int to_c = c + L.left;
		    if(to_c<0 || to_c >= to->cols)
		        continue;
		        
		    *image_pixel(to, layer, to_c, to_r) =
		            L.opt_data[r*L.cols + c]; 
		}
	}
}

