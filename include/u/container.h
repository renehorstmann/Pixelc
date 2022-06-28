#ifndef U_CONTAINER_H
#define U_CONTAINER_H

//
// to place render objects in a stack or flow container, with different alignment options
//

#include "s/s.h"
#include "s/allocator.h"
#include "m/types/float.h"


#define U_CONTAINER_MAX_COLS_ROWS 128

// mode stack: all items are ordered in a line
// mode free: like stack, but generates a new row if max_size is reached
enum u_container_mode {
    U_CONTAINER_MODE_STACK_V,
    U_CONTAINER_MODE_STACK_H,
    U_CONTAINER_MODE_FREE_V,
    U_CONTAINER_MODE_FREE_H,
    U_CONTAINER_NUM_MODES
};

// align start: to left or top
// align end: to right or bottom
// align center: to the middle
// align block: to both ends with equal sized offsets between the items
enum u_container_align {
    U_CONTAINER_ALIGN_START,
    U_CONTAINER_ALIGN_END,
    U_CONTAINER_ALIGN_CENTER,
    U_CONTAINER_ALIGN_BLOCK,
    U_CONTAINER_ALIGN_NUM_MODES
};

// Container item
// set the size
// if u_container_update is called, out will be filled
typedef struct {
    vec2 size;
    struct {
        float left, top;
        int col, row;
    } out;
} uContainerItem_s;

typedef struct {
    uContainerItem_s *items;
    int num;

    enum u_container_mode mode;
    enum u_container_align align_width;
    enum u_container_align align_height;

    // true (default): ceils the item sizes
    //        so left and top are integers
    bool on_integer_positions;

    vec2 max_size;
    float left, top;

    struct {
        vec2 size;
        float left, top;
        int cols, rows;
        int items_placed;
    } out;

    sAllocator_i a;
} uContainer;


static vec2 u_container_item_center_pos(uContainerItem_s self) {
    return (vec2) {{self.out.left + self.size.x / 2, self.out.top - self.size.y / 2}};
}

static void u_container_item_set_invalid(uContainerItem_s *self) {
    self->out.left = SCA_MAX;
    self->out.top = SCA_MAX;
    self->out.col = -1;
    self->out.row = -1;
}

static bool u_container_valid(uContainer self) {
    return self.items && self.num > 0 && s_allocator_valid(self.a);
}

static uContainer u_container_new_invalid() {
    return (uContainer) {0};
}

uContainer u_container_new_a(int num, float left, float top, sAllocator_i a);

static uContainer u_container_new(int num, float left, float top) {
    return u_container_new_a(num, left, top, S_ALLOCATOR_DEFAULT);
}

void u_container_kill(uContainer *self);

void u_container_set_num(uContainer *self, int num);

// returns true if all items could be placed
//     (out.items_placed<=num)
// if an item could not be placed, its set to pos inf
bool u_container_update(uContainer *self);

#endif //U_CONTAINER_H
