#ifndef E_INPUT_H
#define E_INPUT_H

#include <stdbool.h>
#include "mathc/types/float.h"
#include "core.h"


#define E_MAX_POINTER_EVENTS 32


enum ePointerAction {E_POINTER_DOWN, E_POINTER_MOVE, E_POINTER_UP, E_POINTER_NUM_ACTIONS};

typedef struct {
    vec4 pos; // x, y, 0, 1
    enum ePointerAction action;
    int id;
} ePointer_s;

typedef void (*ePointerEventFn)(ePointer_s, void *user_data);

typedef struct {
    bool up, left, right, down;
    bool enter, space;
} eInputKeys;

extern eInputKeys e_input_keys;

extern bool e_input_accel_active;
extern float e_input_accel[3];



void e_input_init();

void e_input_update();

void e_input_register_pointer_event(ePointerEventFn event, void *user_data);

#endif //E_INPUT_H
