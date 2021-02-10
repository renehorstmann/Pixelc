#include "utilc/alloc.h"
#include "selection.h"

static struct {
	int x, y;
	int rows, cols;
	Color_s *opt_data;
} L;

static bool valid_to_copy(const Image *img, int layer) {
	return L.x>=0 && L.y>=0 
	        && L.cols>0 && L.rows>0
	        && L.x+L.cols < img->cols 
	        && L.y+L.rows < img->rows;
}

void selection_init(int x, int y, int rows, int cols) {
	L.x = x;
	L.y = y;
	L.rows = rows;
	L.cols = cols;
	selection_kill();
}

void selection_kill() {
	L.x = L.y = L.rows = L.cols = 0;
	Free0(L.opt_data);
}

void selection_move(int x, int y) {
	L.x = x;
	L.y = y;
}

bool selection_active() {
	return L.cols > 0 && L.rows > 0;
}

bool selection_contains(int x, int y) {
	return !selection_active() 
	        || (x>=L.x && x<L.x+L.cols
	        && y>=L.y && y<L.y+L.rows);
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
	
	for(int r=0; r<L.rows; r++) {
		for(int c=0; c<L.cols; c++) {
			*image_pixel(from, layer, r+L.x, c+L.y) = replace;
		}
	}
}

void selection_paste(Image *to, int layer) {
	if(!L.opt_data || L.rows <=0 || L.rows <=0) {
	    SDL_Log("selection_paste failed");
	    return;
    }
	for(int r=0; r<L.rows; r++) {
		int to_r = r + L.y;
		if(to_r<0 || to_r >= to->rows)
		    continue;
		for(int c=0; c<L.cols; c++) {
			int to_c = c + L.x;
		    if(to_c<0 || to_c >= to->cols)
		        continue;
		        
		    *image_pixel(to, layer, to_r, to_c) =
		            L.opt_data[r*L.cols + c]; 
		}
	}
}

