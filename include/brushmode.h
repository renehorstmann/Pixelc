#ifndef PIXELC_BRUSHMODE_H
#define PIXELC_BRUSHMODE_H

//
// draw routines that are called by brush.h and call brush.h's actual drawing functions
//

#include "e/input.h"
#include "m/types/int.h"

enum brushmode_func {
    BRUSHMODE_FUNC_LINE,
    BRUSHMODE_FUNC_RECT,
    BRUSHMODE_FUNC_CIRCLE,
    BRUSHMODE_NUM_FUNCS
};

struct BrushMode_Globals {
    struct {
        bool is_drawing;
        ivec2 start;
    } L;
};
extern struct BrushMode_Globals brushmode;

void brushmode_init();

void brushmode_reset();

bool brushmode_dot(ePointer_s pointer);

bool brushmode_free(ePointer_s pointer);

bool brushmode_func(ePointer_s pointer, enum brushmode_func func);

void brushmode_pipette(ePointer_s pointer, bool single);

bool brushmode_fill(ePointer_s pointer, bool mode8);

bool brushmode_replace(ePointer_s pointer);

#endif //PIXELC_BRUSHMODE_H
