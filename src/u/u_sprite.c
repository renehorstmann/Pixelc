#include "m/int.h"
#include "m/uchar.h"
#include "u/sprite.h"

// grid to vertical
static void reorder(ucvec4 *dst, const ucvec4 *src, ivec2 sprite_size, ivec2 sprites) {

    for (int sr = 0; sr < sprites.y; sr++) {
        for (int sc = 0; sc < sprites.x; sc++) {
            for (int r = 0; r < sprite_size.y; r++) {
                int src_row = sr * sprite_size.y + r;
                int src_col = sc * sprite_size.x;
                int src_idx = src_row * sprite_size.x * sprites.x + src_col;
                int dst_row = sr * sprite_size.y * sprites.x + sc * sprite_size.y + r;
                int dst_idx = dst_row * sprite_size.x;

                memcpy(&dst[dst_idx], &src[src_idx], sprite_size.x * sizeof(ucvec4));
            }
        }
    }
}


// grid from vertical
static void reorder_back(ucvec4 *dst, const ucvec4 *src, ivec2 sprite_size, ivec2 sprites) {

    for (int sr = 0; sr < sprites.y; sr++) {
        for (int sc = 0; sc < sprites.x; sc++) {
            for (int r = 0; r < sprite_size.y; r++) {
                int dst_row = sr * sprite_size.y + r;
                int dst_col = sc * sprite_size.x;
                int dst_idx = dst_row * sprite_size.x * sprites.x + dst_col;
                int src_row = sr * sprite_size.y * sprites.x + sc * sprite_size.y + r;
                int src_idx = src_row * sprite_size.x;

                memcpy(&dst[dst_idx], &src[src_idx], sprite_size.x * sizeof(ucvec4));
            }
        }
    }
}

//
// public
//

uSprite u_sprite_new_clone_merge_col_down_a(uSprite from, int col_to_merge_down, sAllocator_i a) {
    if(!u_sprite_valid(from))
        return u_sprite_new_invalid_a(a);
    if (from.cols <= 1 || col_to_merge_down <= 0 || col_to_merge_down >= from.cols) {
        s_error_set("sprite new clone merge col down failed");
        s_log_error("failed: wrong col to merge: %i/%i", col_to_merge_down, from.cols);
        return u_sprite_new_invalid_a(a);
    }
    uSprite self = u_sprite_new_empty_a(from.img.cols, from.img.rows, from.cols - 1, from.rows, a);
    
    // sprites to clone up to col_to_merge_down-1
    if (col_to_merge_down > 1) {
        for(int r=0; r<from.rows; r++) {
            for(int c=0; c<col_to_merge_down-1;c++) {
                memcpy(u_sprite_sprite(self, c, r), 
                        u_sprite_sprite(from, c, r), 
                        u_sprite_sprite_data_size(from));
            }
        }
    }
    // sprites to clone behind col_to_merge_down
    if (col_to_merge_down < from.cols - 1) {
        for(int r=0; r<from.rows; r++) {
            for(int c=col_to_merge_down+1; c<from.cols;c++) {
                memcpy(u_sprite_sprite(self, c-1, r), 
                        u_sprite_sprite(from, c, r), 
                        u_sprite_sprite_data_size(from));
            }
        }
    }
    
    // merge the sprites
    for(int row = 0; row<self.rows; row++) {
        for (int r = 0; r < self.img.rows; r++) {
            for (int c = 0; c < self.img.cols; c++) {
                uColor_s col_a = *u_sprite_pixel(from, c, r, col_to_merge_down - 1, row);
                uColor_s col_b = *u_sprite_pixel(from, c, r, col_to_merge_down, row);
                *u_sprite_pixel(self, c, r, col_to_merge_down - 1, row) = u_color_blend(col_a, col_b);
            }
        }
    }
    return self;
}

uSprite u_sprite_new_clone_merge_col_down_full_a(uSprite from, sAllocator_i a) {
    if(!u_sprite_valid(from))
        return u_sprite_new_invalid_a(a);
    if(from.cols == 1)
        return u_sprite_new_clone_a(from, a);
    
    uSprite self = u_sprite_new_clone_merge_col_down_a(from, 1, a);
    while(self.cols>1) {
        uSprite tmp = u_sprite_new_clone_merge_col_down(self, 1);
        u_sprite_kill(&self);
        self = tmp;
    }
    return self;
}


uSprite u_sprite_new_clone_merge_row_down_a(uSprite from, int row_to_merge_down, sAllocator_i a) {
    if(!u_sprite_valid(from))
        return u_sprite_new_invalid_a(a);
    if (from.rows <= 1 || row_to_merge_down <= 0 || row_to_merge_down >= from.rows) {
        s_error_set("sprite new clone merge row down failed");
        s_log_error("failed: wrong row to merge: %i/%i", row_to_merge_down, from.rows);
        return u_sprite_new_invalid_a(a);
    }
    uSprite self = u_sprite_new_empty_a(from.img.cols, from.img.rows, from.cols, from.rows -1, a);
    
    // rows to clone up to row_to_merge_down-1
    if (row_to_merge_down > 1) {
        for(int r=0; r<row_to_merge_down-1; r++) {
            memcpy(u_sprite_row(self, r), 
                    u_sprite_row(from, r), 
                    u_sprite_row_data_size(from));
        }
    }
    // rows to clone behind row_to_merge_down
    if (row_to_merge_down < from.rows - 1) {
        for(int r=row_to_merge_down+1; r<from.rows; r++) {
            memcpy(u_sprite_row(self, r-1), 
                    u_sprite_row(from, r), 
                    u_sprite_row_data_size(from));
        }
    }
    
    // merge the sprites
    for(int col = 0; col<self.cols; col++) {
        for (int r = 0; r < self.img.rows; r++) {
            for (int c = 0; c < self.img.cols; c++) {
                uColor_s col_a = *u_sprite_pixel(from, c, r, col,row_to_merge_down - 1);
                uColor_s col_b = *u_sprite_pixel(from, c, r, col, row_to_merge_down);
                *u_sprite_pixel(self, c, r, col, row_to_merge_down - 1) = u_color_blend(col_a, col_b);
            }
        }
    }
    return self;
}

uSprite u_sprite_new_clone_merge_row_down_full_a(uSprite from, sAllocator_i a) {
    if(!u_sprite_valid(from))
        return u_sprite_new_invalid_a(a);
    if(from.rows == 1)
        return u_sprite_new_clone_a(from, a);
    
    uSprite self = u_sprite_new_clone_merge_row_down_a(from, 1, a);
    while(self.rows>1) {
        uSprite tmp = u_sprite_new_clone_merge_row_down(self, 1);
        u_sprite_kill(&self);
        self = tmp;
    }
    return self;
}



uSprite u_sprite_new_clone_remove_col_a(uSprite from, int col_to_remove, sAllocator_i a) {
    if(!u_sprite_valid(from) || col_to_remove<0 || col_to_remove>=from.cols)
        return u_sprite_new_invalid_a(a);
    
    uSprite self = u_sprite_new_empty_a(from.img.cols, from.img.rows, from.cols-1, from.rows, a);
    int layer = 0;
    for(int i=0; i<from.img.layers; i++) {
        int col = i % from.cols;
        if(col == col_to_remove)
            continue;
        memcpy(u_image_layer(self.img, layer), u_image_layer(from.img, i), u_image_layer_data_size(self.img));
        layer++;
    }
    return self;
}

uSprite u_sprite_new_clone_remove_row_a(uSprite from, int row_to_remove, sAllocator_i a) {
    if(!u_sprite_valid(from) || row_to_remove<0 || row_to_remove>=from.rows)
        return u_sprite_new_invalid_a(a);
    
    uSprite self = u_sprite_new_empty_a(from.img.cols, from.img.rows, from.cols, from.rows-1, a);
    int layer = 0;
    for(int i=0; i<from.img.layers; i++) {
        int row = i / from.cols;
        if(row == row_to_remove)
            continue;
        memcpy(u_image_layer(self.img, layer), u_image_layer(from.img, i), u_image_layer_data_size(self.img));
        layer++;
    }
    return self;
}


uSprite u_sprite_new_clone_insert_col_a(uSprite from, int col_behind, sAllocator_i a) {
    if(!u_sprite_valid(from) || col_behind<-1 || col_behind>=from.cols) 
        return u_sprite_new_invalid_a(a);
    uSprite self = u_sprite_new_empty_a(from.img.cols, from.img.rows, from.cols+1, from.rows, a);
    for(int r=0; r<self.rows; r++) {
        if(col_behind>=0) {
            memcpy(u_sprite_sprite(self, 0, r),
                    u_sprite_sprite(from, 0, r),
                    u_sprite_sprite_data_size(from) * (col_behind+1));
        }
        memset(u_sprite_sprite(self, col_behind+1, r), 0, 
                u_sprite_sprite_data_size(from));
       if(col_behind<from.cols-1) 
            memcpy(u_sprite_sprite(self, col_behind+2, r),
                    u_sprite_sprite(from, col_behind+1, r),
                    u_sprite_sprite_data_size(from) * (from.cols-col_behind-1));
    }
    return self;
}


uSprite u_sprite_new_clone_insert_row_a(uSprite from, int row_behind, sAllocator_i a) {
    if(!u_sprite_valid(from) || row_behind<-1 || row_behind>=from.rows) 
        return u_sprite_new_invalid_a(a);
    uSprite self = u_sprite_new_empty_a(from.img.cols, from.img.rows, from.cols, from.rows+1, a);
    if(row_behind>=0)
        memcpy(self.img.data, from.img.data,
                u_sprite_row_data_size(from) * (row_behind+1));
    memset(u_sprite_row(self, row_behind+1), 0, 
            u_sprite_row_data_size(from));
    if(row_behind<from.rows-1) 
        memcpy(u_sprite_row(self, row_behind+2),
                u_sprite_row(from, row_behind+1),
                u_sprite_row_data_size(from) * (from.rows-row_behind-1));
    return self;
}


uSprite u_sprite_new_clone_swap_cols_a(uSprite from, int col_a, int col_b, sAllocator_i a) {
    if(!u_sprite_valid(from))
        return u_sprite_new_invalid_a(a);
    uSprite swap = u_sprite_new_clone_a(from, a);
    for(int r=0;r<swap.rows;r++) {
        memcpy(u_sprite_sprite(swap, col_a, r), 
                u_sprite_sprite(from, col_b, r),    
                u_sprite_sprite_data_size(swap));
        memcpy(u_sprite_sprite(swap, col_b, r), 
                u_sprite_sprite(from, col_a, r),    
                u_sprite_sprite_data_size(swap));
    }
    return swap;
}

uSprite u_sprite_new_clone_swap_rows_a(uSprite from, int row_a, int row_b, sAllocator_i a) {
    if(!u_sprite_valid(from))
        return u_sprite_new_invalid_a(a);
    uSprite swap = u_sprite_new_clone_a(from, a);
    memcpy(u_sprite_row(swap, row_a), 
            u_sprite_row(from, row_b),    
            u_sprite_row_data_size(swap));
    memcpy(u_sprite_row(swap, row_b), 
            u_sprite_row(from, row_a),    
            u_sprite_row_data_size(swap));
    return swap;
}


uSprite u_sprite_new_reorder_from_image_a(int sprite_cols, uImage from, sAllocator_i a) {
    if(!u_image_valid(from))
        return u_sprite_new_invalid_a(a);
    if(from.cols%sprite_cols!=0) {
        s_log_warn("failed to set sprite_cols: %i%%%i=%i", from.cols, sprite_cols, from.cols%sprite_cols);
        return u_sprite_new_invalid_a(a);
    }
    uSprite self = u_sprite_new_empty_a(from.cols/sprite_cols, from.rows, sprite_cols, from.layers, a);
    reorder(self.img.data, from.data, 
            (ivec2) {{self.img.cols, self.img.rows}},
            (ivec2) {{self.cols, self.rows}});
    return self;
}


uSprite u_sprite_new_sdl_surface_a(int sprite_cols, int sprite_rows, struct SDL_Surface *surface, sAllocator_i a) {
    uImage img = u_image_new_sdl_surface_a(sprite_rows, surface, a);
    uSprite self = u_sprite_new_reorder_from_image(sprite_cols, img);
    u_image_kill(&img);
    return self;
}

uSprite u_sprite_new_file_a(int sprite_cols, int sprite_rows, const char *file, sAllocator_i a) {
    uImage img = u_image_new_file_a(sprite_rows, file, a);
    uSprite self = u_sprite_new_reorder_from_image(sprite_cols, img);
    u_image_kill(&img);
    return self;
}

void u_sprite_kill(uSprite *self) {
    u_image_kill(&self->img);
    *self = u_sprite_new_invalid_a(self->img.a);
}

uImage u_sprite_reorder_to_new_image_a(uSprite self, sAllocator_i a) {
    if(!u_sprite_valid(self))
        return u_image_new_invalid_a(a);
    uImage img = u_image_new_empty_a(self.img.cols*self.cols, self.img.rows, self.rows, a);
    reorder_back(img.data, self.img.data, 
            (ivec2) {{self.img.cols, self.img.rows}},
            (ivec2) {{self.cols, self.rows}});
    return img;
}

struct SDL_Surface *u_sprite_to_sdl_surface(uSprite self) {
    uImage img = u_sprite_reorder_to_new_image(self);
    struct SDL_Surface *ret = u_image_to_sdl_surface(img);
    u_image_kill(&img);
    return ret;
}

bool u_sprite_save_file(uSprite self, const char *file) {
    uImage img = u_sprite_reorder_to_new_image(self);
    bool ret = u_image_save_file(img, file);
    u_image_kill(&img);
    return ret;
}


