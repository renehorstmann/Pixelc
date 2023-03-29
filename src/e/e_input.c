#include "m/float.h"
#include "m/bool.h"
#include "e/window.h"
#include "e/gui_nk.h"
#include "e/gui.h"
#include "e/input.h"

struct eInput_Globals e_input;

//
// protected
//

void e_window_handle_window_event_(const SDL_Event *event);

void e_gui_input_begin_();

void e_gui_handle_sdl_event_(SDL_Event *event);

void e_gui_input_end_();

typedef struct {
    int pointer_id;
    SDL_FingerID finger_id;
    vec4 pos;
} Touch;

typedef struct {
    ePointerEventFn cb;
    void *ud;
    bool hover;
} RegPointer;

typedef struct {
    RegPointer array[E_MAX_POINTER_EVENTS];
    int size;
} RegPointerArray;


typedef struct {
    eWheelEventFn cb;
    void *ud;
} RegWheel;

typedef struct {
    RegWheel array[E_MAX_WHEEL_EVENTS];
    int size;
} RegWheelArray;


typedef struct {
    eKeyRawEventFn cb;
    void *ud;
} RegKeyRaw;

typedef struct {
    RegKeyRaw array[E_MAX_KEY_RAW_EVENTS];
    int size;
} RegKeyRawArray;


static struct {
    Touch touchs[E_MAX_TOUCH_IDS];
    int touchs_size;

    float last_touched_time;
    
    bool mouse_pressed[E_POINTER_BUTTON_NUM];

    ePointer_s current_pointer_0;

    RegPointerArray reg_pointer;
    RegPointer reg_pointer_e_vip;  // .cb==NULL if none

    RegWheelArray reg_wheel;
    RegWheel reg_wheel_e_vip;  // .cb==NULL if none

    RegKeyRawArray reg_key_raw;
    RegKeyRaw reg_key_raw_e_vip;  // .cb==NULL if none
} L;


static ePointer_s pointer_mouse(enum ePointerAction action, int btn_id) {
    ePointer_s res;
    res.action = action;
    res.id = btn_id;
    int x, y;
    SDL_GetMouseState(&x, &y);

    res.pos.x = (2.0f * x) / e_window.size.x - 1.0f;
    res.pos.y = 1.0f - (2.0f * y) / e_window.size.y;
    res.pos.z = 0;
    res.pos.w = 1;

    return res;
}


static void emit_pointer_events(ePointer_s action) {
    if(action.id == 0)
        L.current_pointer_0 = action;

    if (L.reg_pointer_e_vip.cb) {
        if(action.action == E_POINTER_HOVER && !L.reg_pointer_e_vip.hover)
            return;
        L.reg_pointer_e_vip.cb(action, L.reg_pointer_e_vip.ud);
        return;
    }

    // copy to be safe to unregister in an event
    RegPointerArray array = L.reg_pointer;
    for (int i = 0; i < array.size; i++) {
        if(action.action == E_POINTER_HOVER && !array.array[i].hover)
            continue;
        array.array[i].cb(action, array.array[i].ud);
    }
}

static void emit_wheel_events(vec4 pos, bool up) {
    if (L.reg_wheel_e_vip.cb) {
        L.reg_wheel_e_vip.cb(L.current_pointer_0.pos, up, L.reg_wheel_e_vip.ud);
        return;
    }

    // copy to be safe to unregister in an event
    RegWheelArray array = L.reg_wheel;
    for (int i = 0; i < array.size; i++)
        array.array[i].cb(L.current_pointer_0.pos, up, array.array[i].ud);
}


static bool touch_pointer_id_already_exists(int pointer_id) {
    for(int i=0; i<L.touchs_size; i++) {
        if(L.touchs[i].pointer_id == pointer_id)
            return true;
    }
    return false;
}

static void input_handle_pointer_touch(SDL_Event *event) {
    float x = event->tfinger.x;
    float y = event->tfinger.y;
    SDL_FingerID finger_id = event->tfinger.fingerId;
    enum ePointerAction action;
    switch (event->type) {
        case SDL_FINGERDOWN:
            action = E_POINTER_DOWN;
            break;
        case SDL_FINGERMOTION:
            action = E_POINTER_MOVE;
            break;
        case SDL_FINGERUP:
            action = E_POINTER_UP;
            break;
        default:
            return;
    }

    L.last_touched_time = 0;

    vec4 pos;
    pos.x = 2.0f * x - 1.0f;
    pos.y = 1.0f - 2.0f * y;
    pos.z = 0;
    pos.w = 1;

    // check finger ids to cast to touch id
    int id = -1;
    for (int i = 0; i < L.touchs_size; i++) {
        if (L.touchs[i].finger_id == finger_id) {
            id = i;
            break;
        }
    }
    if (id < 0) {
        if(action == E_POINTER_UP) {
            s_log_warn("got an up without an active touch id, ignoring...");
            return;
        }
        if (L.touchs_size >= E_MAX_TOUCH_IDS) {
            e_input_reset_touch();
        }

        // create new id
        int pointer_id = 0;
        while(touch_pointer_id_already_exists(pointer_id)) {
            pointer_id++;
        }

        id = L.touchs_size++;
        L.touchs[id].pointer_id = pointer_id;
        L.touchs[id].finger_id = finger_id;

        if (action == E_POINTER_MOVE) {
            action = E_POINTER_DOWN;
            s_log_warn("e_input_update: touch got new id but action_pressed==move");
        }
    }

    // update pos
    L.touchs[id].pos = pos;
    
    
    // emit
    ePointer_s res;
    res.action = action;
    res.id = L.touchs[id].pointer_id;
    res.pos = pos;
    emit_pointer_events(res);


    // remove ups
    if (action == E_POINTER_UP) {
        for(int i=id; i<L.touchs_size-1; i++) {
            L.touchs[i] = L.touchs[i+1];
        }
        L.touchs_size--;
    }    
}

static void input_handle_pointer_mouse(SDL_Event *event) {
    int btn_sdl = event->button.button;
    int btn_some = 1 - btn_sdl;
    int btn_idx = btn_sdl - 1;
    bool pressed = bvecN_any(L.mouse_pressed, E_POINTER_BUTTON_NUM);
    switch (event->type) {
        case SDL_MOUSEBUTTONDOWN:
            if (btn_idx<0 || btn_idx>=E_POINTER_BUTTON_NUM)
                break;
            emit_pointer_events(pointer_mouse(
                    E_POINTER_DOWN,
                    btn_some));
            L.mouse_pressed[btn_idx] = true;
            break;
        case SDL_MOUSEMOTION:
            emit_pointer_events(pointer_mouse(
                    pressed? E_POINTER_MOVE : E_POINTER_HOVER,
                    0));
            break;
        case SDL_MOUSEBUTTONUP:
            if (btn_idx<0 || btn_idx>=E_POINTER_BUTTON_NUM)
                break;
            emit_pointer_events(pointer_mouse(
                    E_POINTER_UP,
                    btn_some));
            L.mouse_pressed[btn_idx] = false;
            break;
    }
}

static void input_handle_wheel(SDL_Event *event) {
    // it could be possible that y==0, (e. g. x!=0)
    if (event->wheel.y == 0)
        return;
    emit_wheel_events(L.current_pointer_0.pos, event->wheel.y > 0);
}

static void input_handle_keys(SDL_Event *event) {
    if (L.reg_key_raw_e_vip.cb) {
        L.reg_key_raw_e_vip.cb(event, L.reg_key_raw_e_vip.ud);
        return;
    }

    // copy to be safe to unregister in an event
    RegKeyRawArray array = L.reg_key_raw;
    for (int i = 0; i<array.size; i++) {
        array.array[i].cb(event, array.array[i].ud);
    }
    bool down = event->type == SDL_KEYDOWN;
    switch (event->key.keysym.sym) {
        case SDLK_UP:
            e_input.keys.up = down;
            break;
        case SDLK_LEFT:
            e_input.keys.left = down;
            break;
        case SDLK_RIGHT:
            e_input.keys.right = down;
            break;
        case SDLK_DOWN:
            e_input.keys.down = down;
            break;
        case SDLK_RETURN:
            e_input.keys.enter = down;
            break;
        case SDLK_SPACE:
            e_input.keys.space = down;
            break;
        case SDLK_w:
            e_input.keys.w = down;
            break;
        case SDLK_a:
            e_input.keys.a = down;
            break;
        case SDLK_s:
            e_input.keys.s = down;
            break;
        case SDLK_d:
            e_input.keys.d = down;
            break;
    }
}

#ifdef OPTION_GYRO
static void input_handle_sensors(SDL_Event *event) {
    SDL_Sensor *sensor = SDL_SensorFromInstanceID(event->sensor.which);
    if (!sensor || SDL_SensorGetType(sensor) != SDL_SENSOR_ACCEL) {
        s_log_warn("e_input_update: Couldn't get sensor for sensor event\n");
        return;
    }

    const float *data = event->sensor.data;
    memcpy(e_input.accel.v, data, sizeof(e_input.accel));

    // s_log_trace("e_input_update: Gyro update: %.2f, %.2f, %.2f", data[0], data[1], data[2]);
}
#endif



//
// public
//

void e_input_init() {
    s_assume(!e_input.init, "should be called only once");
    e_input.init = true;

    s_log("init");

    s_assume(e_window.init, "needs an sdl window to get its size");

    e_input.reset_touch_time = E_INPUT_DEFAULT_TOUCH_RESET_TIME;

#ifdef OPTION_GAMEPAD
    int num_joysticks = SDL_NumJoysticks();
    s_log("found %i joysticks", num_joysticks);
    for (int i = 0; i < SDL_NumJoysticks(); i++) {
        e_input.gamepad.controller = SDL_GameControllerOpen(i);
        if (e_input.gamepad.controller) {
            s_log("opened GameController: %s (%i/%i)", SDL_GameControllerName(e_input.gamepad.controller), i, num_joysticks);
            break;
        }
    }
#endif

#ifdef OPTION_GYRO
    int num_sensors = SDL_NumSensors();
    bool accel_opened = false;
    for (int i = 0; i < num_sensors; i++) {
        if (SDL_SensorGetDeviceType(i) == SDL_SENSOR_ACCEL) {
            SDL_Sensor *sensor = SDL_SensorOpen(i);
            if (sensor) {
                accel_opened = true;
                break;
            }
        }
    }

    e_input.accel_active = accel_opened;
    if (accel_opened)
        s_log("e_input_init: Opened acceleration sensor");
#endif
}

void e_input_kill() {
    if (!e_input.init)
        return;

    memset(&e_input, 0, sizeof e_input);
    memset(&L, 0, sizeof L);
}


void e_input_update(float dt) {
    e_input.is_touch = SDL_GetNumTouchDevices() > 0;

    e_gui_input_begin_();

    void (*input_handle_pointer)(SDL_Event *event) =
    e_input.is_touch ? input_handle_pointer_touch : input_handle_pointer_mouse;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        e_window_handle_window_event_(&event);

        e_gui_handle_sdl_event_(&event);   // NULL safe

        switch (event.type) {
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONUP:
            case SDL_FINGERDOWN:
            case SDL_FINGERMOTION:
            case SDL_FINGERUP:
                input_handle_pointer(&event);
                break;
            case SDL_MOUSEWHEEL:
                input_handle_wheel(&event);
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                input_handle_keys(&event);
                break;
#ifdef OPTION_GYRO
                case SDL_SENSORUPDATE:
                    input_handle_sensors(&event);
                    break;
#endif
        }
    }

    e_gui_input_end_();

    if (e_input.is_touch && L.last_touched_time < e_input.reset_touch_time) {
        L.last_touched_time += dt;
        if (L.last_touched_time >= e_input.reset_touch_time) {
            e_input_reset_touch();
        }
    }

#ifdef OPTION_GAMEPAD
    // gamepad
    if(e_input.gamepad.controller) {
        SDL_GameController *c = e_input.gamepad.controller;
        vec2 stick;
        stick.x = SDL_GameControllerGetAxis(c, SDL_CONTROLLER_AXIS_LEFTX);
        stick.y = -SDL_GameControllerGetAxis(c, SDL_CONTROLLER_AXIS_LEFTY);
        e_input.gamepad.stick_l = vec2_div(stick, 32768.0f);
        stick.x = SDL_GameControllerGetAxis(c, SDL_CONTROLLER_AXIS_RIGHTX);
        stick.y = -SDL_GameControllerGetAxis(c, SDL_CONTROLLER_AXIS_RIGHTY);
        e_input.gamepad.stick_r = vec2_div(stick, 32768.0f);
        e_input.gamepad.btn_stick_l = SDL_GameControllerGetButton(c, SDL_CONTROLLER_BUTTON_LEFTSTICK);
        e_input.gamepad.btn_shoulder_l = SDL_GameControllerGetButton(c, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
        e_input.gamepad.btn_stick_r = SDL_GameControllerGetButton(c, SDL_CONTROLLER_BUTTON_RIGHTSTICK);
        e_input.gamepad.btn_shoulder_r = SDL_GameControllerGetButton(c, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
        e_input.gamepad.btn_x = SDL_GameControllerGetButton(c, SDL_CONTROLLER_BUTTON_X);
        e_input.gamepad.btn_y = SDL_GameControllerGetButton(c, SDL_CONTROLLER_BUTTON_Y);
        e_input.gamepad.btn_a = SDL_GameControllerGetButton(c, SDL_CONTROLLER_BUTTON_A);
        e_input.gamepad.btn_b = SDL_GameControllerGetButton(c, SDL_CONTROLLER_BUTTON_B);
    }
#endif

}


void e_input_reset_touch() {
    if(L.touchs_size>0) {
        s_log_warn("resetting touch pointers");
    }
    for(int i=0; i<L.touchs_size; i++) {
        ePointer_s action = {
                L.touchs[i].pos,
                E_POINTER_UP,
                L.touchs[i].pointer_id
        };
        emit_pointer_events(action);
    }
    L.touchs_size = 0;
}


void e_input_register_pointer_event(ePointerEventFn event, void *user_data) {
    s_assume(L.reg_pointer.size < E_MAX_POINTER_EVENTS, "too many registered pointer events");
    L.reg_pointer.array[L.reg_pointer.size++] = (RegPointer) {event, user_data, false};
}

void e_input_register_pointer_event_with_hovering(ePointerEventFn event, void *user_data) {
    s_assume(L.reg_pointer.size < E_MAX_POINTER_EVENTS, "too many registered pointer events");
    L.reg_pointer.array[L.reg_pointer.size++] = (RegPointer) {event, user_data, true};
}

void e_input_unregister_pointer_event(ePointerEventFn event_to_unregister) {
    bool found = false;
    for (int i = 0; i < L.reg_pointer.size; i++) {
        if (L.reg_pointer.array[i].cb == event_to_unregister) {
            found = true;
            // move to close hole
            for (int j = i; j < L.reg_pointer.size - 1; j++) {
                L.reg_pointer.array[j] = L.reg_pointer.array[j + 1];
            }
            L.reg_pointer.size--;
            i--; // check moved
        }
    }
    if (!found) {
        s_log_warn("failed: event not registered");
    }
}

void e_input_set_vip_pointer_event(ePointerEventFn event, void *user_data) {
    L.reg_pointer_e_vip.cb = event;
    L.reg_pointer_e_vip.ud = user_data;
    L.reg_pointer_e_vip.hover = false;
}

void e_input_set_vip_pointer_event_with_hovering(ePointerEventFn event, void *user_data) {
    L.reg_pointer_e_vip.cb = event;
    L.reg_pointer_e_vip.ud = user_data;
    L.reg_pointer_e_vip.hover = true;
}

void e_input_emit_pointer_event(ePointer_s pointer) {
    emit_pointer_events(pointer);
}

void e_input_register_wheel_event(eWheelEventFn event, void *user_data) {
    s_assume(L.reg_wheel.size < E_MAX_WHEEL_EVENTS, "too many registered wheel events");
    L.reg_wheel.array[L.reg_wheel.size++] = (RegWheel) {event, user_data};
}

void e_input_unregister_wheel_event(eWheelEventFn event_to_unregister) {
    bool found = false;
    for (int i = 0; i < L.reg_wheel.size; i++) {
        if (L.reg_wheel.array[i].cb == event_to_unregister) {
            found = true;
            // move to close hole
            for (int j = i; j < L.reg_wheel.size - 1; j++) {
                L.reg_wheel.array[j] = L.reg_wheel.array[j + 1];
            }
            L.reg_wheel.size--;
            i--; // check moved
        }
    }
    if (!found) {
        s_log_warn("failed: event not registered");
    }
}

void e_input_set_vip_wheel_event(eWheelEventFn event, void *user_data) {
    L.reg_wheel_e_vip.cb = event;
    L.reg_wheel_e_vip.ud = user_data;
}

void e_input_emit_wheel_event(bool up, vec4 *opt_cursor_pos) {
    vec4 pos = L.current_pointer_0.pos;
    if(opt_cursor_pos) {
        pos = *opt_cursor_pos;
    }
    emit_wheel_events(pos, up);
}

void e_input_register_key_raw_event(eKeyRawEventFn event, void *user_data) {
    s_assume(L.reg_key_raw.size < E_MAX_KEY_RAW_EVENTS, "too many registered key raw events");
    L.reg_key_raw.array[L.reg_key_raw.size++] = (RegKeyRaw) {event, user_data};
}

void e_input_unregister_key_raw_event(eKeyRawEventFn event_to_unregister) {
    bool found = false;
    for (int i = 0; i < L.reg_key_raw.size; i++) {
        if (L.reg_key_raw.array[i].cb == event_to_unregister) {
            found = true;
            // move to close hole
            for (int j = i; j < L.reg_key_raw.size - 1; j++) {
                L.reg_key_raw.array[j] = L.reg_key_raw.array[j + 1];
            }
            L.reg_key_raw.size--;
            i--; // check moved
        }
    }
    if (!found) {
        s_log_warn("failed: event not registered");
    }
}

void e_input_set_vip_key_raw_event(eKeyRawEventFn event, void *user_data) {
    L.reg_key_raw_e_vip.cb = event;
    L.reg_key_raw_e_vip.ud = user_data;
}
