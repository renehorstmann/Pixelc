#include "m/float.h"
#include "m/sca/int.h"

#include "u/container.h"


uContainer u_container_new_a(int num, float left, float top, sAllocator_i a) {
    uContainer self = {0};
    self.a = a;
    self.items = s_a_malloc0(a, sizeof *self.items * num);
    self.num = num;
    self.on_integer_positions = true;
    self.left = left;
    self.top = top;
    self.max_size = (vec2) {{SCA_MAX, SCA_MAX}};
    return self;
}

void u_container_kill(uContainer *self) {
    s_a_free(self->a, self->items);
    *self = u_container_new_invalid();
}

void u_container_set_num(uContainer *self, int num) {
    self->items = s_a_realloc(self->a, self->items, sizeof *self->items * num);
    for (int i = self->num; i < num; i++)
        self->items[i] = (uContainerItem_s) {0};
    self->num = num;
}


bool u_container_update(uContainer *self) {
    memset(&self->out, 0, sizeof self->out);

    // for flow containers: will set the size (cols, rows) for each col or row (depending on H or V)
    int size_list[U_CONTAINER_MAX_COLS_ROWS] = {0};

    // for flow containers: will set the remaining size of the col or row (depending on H or V)
    float remaining_list[U_CONTAINER_MAX_COLS_ROWS] = {0};

    // remaining sizes (max_size - used_size)
    float remaining_x = 0;
    float remaining_y = 0;

    bool placed_all = true;

    if (self->mode == U_CONTAINER_MODE_STACK_V) {
        float max_x = 0;
        float pos_y = 0;
        remaining_y = self->max_size.y;

        for (int i = 0; i < self->num; i++) {
            uContainerItem_s *item = &self->items[i];
            if (item->size.x > self->max_size.x
                || pos_y + item->size.y > self->max_size.y) {
                placed_all = false;
                self->out.items_placed = i;
                u_container_item_set_invalid(item);
                break;
            }

            item->out.left = 0;
            item->out.top = -pos_y;
            item->out.col = self->out.cols;
            item->out.row = self->out.rows++;
            pos_y += item->size.y;

            if (max_x < item->size.x) {
                max_x = item->size.x;
            }
            remaining_y -= item->size.y;

            if (self->on_integer_positions) {
                pos_y = sca_ceil(pos_y);
                max_x = sca_ceil(max_x);
                remaining_y = sca_floor(remaining_y);
            }
        }
        self->out.cols++;
        remaining_x = self->max_size.x - max_x;
    }


    if (self->mode == U_CONTAINER_MODE_STACK_H) {
        float max_y = 0;
        float pos_x = 0;
        remaining_x = self->max_size.x;

        for (int i = 0; i < self->num; i++) {
            uContainerItem_s *item = &self->items[i];
            if (pos_x + item->size.x > self->max_size.x
                || item->size.y > self->max_size.y) {
                placed_all = false;
                self->out.items_placed = i;
                u_container_item_set_invalid(item);
                break;
            }

            item->out.left = pos_x;
            item->out.top = 0;
            item->out.col = self->out.cols++;
            item->out.row = self->out.rows;
            pos_x += item->size.x;

            if (max_y < item->size.y) {
                max_y = item->size.y;
            }
            remaining_x -= item->size.x;

            if (self->on_integer_positions) {
                pos_x = sca_ceil(pos_x);
                max_y = sca_ceil(max_y);
                remaining_x = sca_floor(remaining_x);
            }
        }
        self->out.rows++;
        remaining_y = self->max_size.y - max_y;
    }

    if (self->mode == U_CONTAINER_MODE_FREE_V) {
        float max_x = 0;
        float pos_x = 0;
        float pos_y = 0;
        int row = 0;
        remaining_x = self->max_size.x;

        for (int i = 0; i < self->num; i++) {
            uContainerItem_s *item = &self->items[i];
            if (pos_y + item->size.y > self->max_size.y) {
                remaining_x -= max_x;
                remaining_list[self->out.cols] = self->max_size.y - pos_y;
                size_list[self->out.cols] = row;
                self->out.cols++;
                pos_y = 0;
                pos_x += max_x;
                max_x = 0;
                row = 0;
            }
            if (pos_x + item->size.x > self->max_size.x
                || pos_y + item->size.y > self->max_size.y) {
                placed_all = false;
                self->out.items_placed = i;
                u_container_item_set_invalid(item);
                break;
            }

            if (max_x < item->size.x)
                max_x = item->size.x;

            item->out.left = pos_x;
            item->out.top = -pos_y;
            item->out.col = self->out.cols;
            item->out.row = row++;
            pos_y += item->size.y;

            if (self->out.rows < row) {
                self->out.rows = row;
            }

            if (self->on_integer_positions) {
                pos_y = sca_ceil(pos_y);
                max_x = sca_ceil(max_x);
            }
        }

        // set the last column
        if (row != 0) {
            remaining_x -= max_x;
            remaining_list[self->out.cols] = self->max_size.y - pos_y;
            size_list[self->out.cols] = row;
            self->out.cols++;
        }
    }

    if (self->mode == U_CONTAINER_MODE_FREE_H) {
        float max_y = 0;
        float pos_x = 0;
        float pos_y = 0;
        int col = 0;
        remaining_y = self->max_size.y;

        for (int i = 0; i < self->num; i++) {
            uContainerItem_s *item = &self->items[i];
            if (pos_x + item->size.x > self->max_size.x) {
                remaining_y -= max_y;
                remaining_list[self->out.rows] = self->max_size.x - pos_x;
                size_list[self->out.rows] = col;
                self->out.rows++;
                pos_x = 0;
                pos_y += max_y;
                max_y = 0;
                col = 0;
            }
            if (pos_x + item->size.x > self->max_size.x
                || pos_y + item->size.y > self->max_size.y) {
                placed_all = false;
                self->out.items_placed = i;
                u_container_item_set_invalid(item);
                break;
            }

            if (max_y < item->size.y)
                max_y = item->size.y;

            item->out.left = pos_x;
            item->out.top = -pos_y;
            item->out.col = col++;
            item->out.row = self->out.rows;
            pos_x += item->size.x;

            if (self->out.cols < col) {
                self->out.cols = col;
            }

            if (self->on_integer_positions) {
                pos_x = sca_ceil(pos_x);
                max_y = sca_ceil(max_y);
            }
        }

        // set the last row
        if (col != 0) {
            remaining_y -= max_y;
            remaining_list[self->out.rows] = self->max_size.x - pos_x;
            size_list[self->out.rows] = col;
            self->out.rows++;
        }
    }

    if (placed_all)
        self->out.items_placed = self->num;

    for (int i = self->out.items_placed; i < self->num; i++) {
        self->items[i].out.left = SCA_MAX;
        self->items[i].out.top = SCA_MAX;
    }

    // move with offset and alignment
    for (int i = 0; i < self->out.items_placed; i++) {
        uContainerItem_s *item = &self->items[i];

        int cols = self->mode == U_CONTAINER_MODE_FREE_H ? size_list[item->out.row] : self->out.cols;
        int rows = self->mode == U_CONTAINER_MODE_FREE_V ? size_list[item->out.col] : self->out.rows;
        float rem_x = self->mode == U_CONTAINER_MODE_FREE_H ? remaining_list[item->out.row] : remaining_x;
        float rem_y = self->mode == U_CONTAINER_MODE_FREE_V ? remaining_list[item->out.col] : remaining_y;
        float rem_x_half = rem_x / 2;
        float rem_y_half = rem_y / 2;
        if (self->on_integer_positions) {
            rem_x_half = sca_floor(rem_x_half);
            rem_y_half = sca_ceil(rem_y_half);
        }

        switch (self->align_width) {
            case U_CONTAINER_ALIGN_START:
                item->out.left += self->left;
                break;
            case U_CONTAINER_ALIGN_END:
                item->out.left += self->left + rem_x;
                break;
            case U_CONTAINER_ALIGN_CENTER:
                item->out.left += self->left + rem_x_half;
                break;
            case U_CONTAINER_ALIGN_BLOCK:
                item->out.left += self->left + (item->out.col * rem_x) / isca_max(1, cols - 1);
                break;
            default:
                s_assume(false, "u_container: invalid align option");
                break;
        }

        switch (self->align_height) {
            case U_CONTAINER_ALIGN_START:
                item->out.top += self->top;
                break;
            case U_CONTAINER_ALIGN_END:
                item->out.top += self->top - rem_y;
                break;
            case U_CONTAINER_ALIGN_CENTER:
                item->out.top += self->top - rem_y_half;
                break;
            case U_CONTAINER_ALIGN_BLOCK:
                item->out.top += self->top - (item->out.row * rem_y) / isca_max(1, rows - 1);
                break;
            default:
                s_assume(false, "u_container: invalid align option");
                break;
        }
    }

    float min_remaining_x = remaining_x;
    float min_remaining_y = remaining_y;
    if (self->mode == U_CONTAINER_MODE_FREE_V) {
        min_remaining_y = SCA_MAX;
        for (int c = 0; c < self->out.cols; c++) {
            if (min_remaining_y > remaining_list[c])
                min_remaining_y = remaining_list[c];
        }
    } else if (self->mode == U_CONTAINER_MODE_FREE_H) {
        min_remaining_x = SCA_MAX;
        for (int r = 0; r < self->out.rows; r++) {
            if (min_remaining_x > remaining_list[r])
                min_remaining_x = remaining_list[r];
        }
    }

    // calc out.size and out.left, top
    switch (self->align_width) {
        case U_CONTAINER_ALIGN_START:
            self->out.left = self->left;
            self->out.size.x = self->max_size.x - min_remaining_x;
            break;
        case U_CONTAINER_ALIGN_END:
            self->out.left = self->left + min_remaining_x;
            self->out.size.x = self->max_size.x - min_remaining_x;
            break;
        case U_CONTAINER_ALIGN_CENTER:
            self->out.left = self->left + min_remaining_x / 2;
            self->out.size.x = self->max_size.x - min_remaining_x;
            break;
        case U_CONTAINER_ALIGN_BLOCK:
            self->out.left = self->left;
            self->out.size.x = self->max_size.x;
            break;
        default:
            s_assume(false, "u_container: invalid align option");
            break;
    }

    switch (self->align_height) {
        case U_CONTAINER_ALIGN_START:
            self->out.top = self->top;
            self->out.size.y = self->max_size.y - min_remaining_y;
            break;
        case U_CONTAINER_ALIGN_END:
            self->out.top = self->top - min_remaining_y;
            self->out.size.y = self->max_size.y - min_remaining_y;
            break;
        case U_CONTAINER_ALIGN_CENTER:
            self->out.top = self->top - min_remaining_y / 2;
            self->out.size.y = self->max_size.y - min_remaining_y;
            break;
        case U_CONTAINER_ALIGN_BLOCK:
            self->out.top = self->top;
            self->out.size.y = self->max_size.y;
            break;
        default:
            s_assume(false, "u_container: invalid align option");
            break;
    }

    if (self->on_integer_positions) {
        self->out.left = sca_floor(self->out.left);
        self->out.top = sca_ceil(self->out.top);
    }

    return placed_all;
}

