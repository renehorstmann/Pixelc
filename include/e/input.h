#ifndef E_INPUT_H
#define E_INPUT_H

//
// handles input like keys, mouse, touchscreen, gyro
//

#include "core.h"
#include "m/types/float.h"

#define E_MAX_TOUCH_IDS 16

#define E_MAX_POINTER_EVENTS 32
#define E_MAX_WHEEL_EVENTS 32
#define E_MAX_KEY_RAW_EVENTS 32

// ePointer_s::id for middle and right button clicks
#define E_POINTER_BUTTON_MIDDLE -1
#define E_POINTER_BUTTON_RIGHT -2
#define E_POINTER_BUTTON_NUM 3


// seconds of no touch updates to reset em
#define E_INPUT_DEFAULT_TOUCH_RESET_TIME 5.0

// Keyboard state
typedef struct {
    bool up, left, down, right;
    bool enter, space;
    bool w, a, s, d;
    bool ac_back;
} eInputKeys;

typedef struct {
    // is NULL if not available
    SDL_GameController *controller;

    // heap copy of sdls name
    char *name;

    vec2 stick_l, stick_r;
    bool btn_shoulder_l, btn_shoulder_r;
    bool btn_stick_l, btn_stick_r;
    bool btn_x, btn_y, btn_a, btn_b;
} eInputGamepad;

enum ePointerAction {
    E_POINTER_DOWN,       // start of a press
    E_POINTER_MOVE,       // updates while pressed
    E_POINTER_UP,         // end of press
    E_POINTER_HOVER,      // not pressed (only for e_input_register_pointer_event_with_hovering)
    E_POINTER_NUM_ACTIONS
};

typedef struct {
    vec4 pos; // x, y, 0, 1
    enum ePointerAction action;
    int id;   // 0 = default; >0 multitouch; <0 m+r click
} ePointer_s;


// mouse and touch callback
typedef void (*ePointerEventFn)(ePointer_s, void *user_data);

// mouse wheel callback
// pos = position of the cursor (id==0) as x, y, 0, 1
typedef void (*eWheelEventFn)(vec4 pos, bool up, void *user_data);

// keyboard key event
typedef void (*eKeyRawEventFn)(const SDL_Event *event, void *user_data);


struct eInput_Globals {
    bool init;
    bool is_touch;

    // defaults to E_INPUT_DEFAULT_TOUCH_RESET_TIME
    // if nothing happens in that time, all pointers are set up
    // sometimes UP is not coming...
    float reset_touch_time;

    // acceleration sensor (mobile)
    bool accel_active;
    vec3 accel;

    eInputKeys keys;
    eInputGamepad gamepad;
};
extern struct eInput_Globals e_input;


// initializes the input interface
void e_input_init();

void e_input_kill();

// runs the sdl event loop
void e_input_update(float dt);

// will emit UP for all pointer and restarts counting
void e_input_reset_touch();

// registers a callback for mouse and touch
void e_input_register_pointer_event(ePointerEventFn event, void *user_data);

// registers a callback for mouse and touch
// mouse events will receive E_POINTER_HOVER if no button is pressed while moving
void e_input_register_pointer_event_with_hovering(ePointerEventFn event, void *user_data);

// unregisters a callback
void e_input_unregister_pointer_event(ePointerEventFn event_to_unregister);

// sets a pointer event to a vip call, pass event=NULL to reset
// a vip event will block all other events
void e_input_set_vip_pointer_event(ePointerEventFn event, void *user_data);

// sets a pointer event to a vip call, pass event=NULL to reset
// a vip event will block all other events
// mouse events will receive E_POINTER_HOVER if no button is pressed while moving
void e_input_set_vip_pointer_event_with_hovering(ePointerEventFn event, void *user_data);

// calls each registered pointer event with the given pointer, usable for virtual cursors, etc.
void e_input_emit_pointer_event(ePointer_s pointer);

// registers a callback for mouse wheel
void e_input_register_wheel_event(eWheelEventFn event, void *user_data);

// unregisters a callback
void e_input_unregister_wheel_event(eWheelEventFn event_to_unregister);

// sets a wheel event to a vip call, pass event=NULL to reset
// a vip event will block all other events
void e_input_set_vip_wheel_event(eWheelEventFn event, void *user_data);

// calls each registered wheel event with the given pointer pos and wheel up, usable for virtual cursors, etc.
void e_input_emit_wheel_event(bool up, vec4 *opt_cursor_pos);

// registers a callback for sdl key events
void e_input_register_key_raw_event(eKeyRawEventFn event, void *user_data);

// unregisters a callback
void e_input_unregister_key_raw_event(eKeyRawEventFn event_to_unregister);

// sets a key raw event to a vip call, pass event=NULL to reset
// a vip event will block all other events
void e_input_set_vip_key_raw_event(eKeyRawEventFn event, void *user_data);

#endif //E_INPUT_H
