#include "mathc/float.h"
#include "utilc/assume.h"
#include "e/window.h"
#include "e/gui.h"
#include "e/input.h"

eInputKeys e_input_keys;

bool e_input_accel_active;
float e_input_accel[3];

typedef struct {
    ePointerEventFn cb;
    void *ud;
} RegPointer;

typedef struct {
    eWheelEventFn cb;
    void *ud;
} RegWheel;

static struct {
    RegPointer reg_pointer_e[E_MAX_POINTER_EVENTS];
    int reg_pointer_e_size;

    RegWheel reg_wheel_e[E_MAX_WHEEL_EVENTS];
    int reg_wheel_e_size;
} L;

static ePointer_s pointer_mouse(enum ePointerAction action) {
    ePointer_s res;
    res.action = action;
    res.id = 0;
    int x, y;
    SDL_GetMouseState(&x, &y);

    res.pos.x = (2.0f * x) / e_window_size[0] - 1.0f;
    res.pos.y = 1.0f - (2.0f * y) / e_window_size[1];
    res.pos.z = 0;
    res.pos.w = 1;

    return res;
}

static ePointer_s pointer_finger(enum ePointerAction action, float x, float y, int finger_id) {
    ePointer_s res;
    res.action = action;
    res.id = finger_id;

    res.pos.x = 2.0f * x - 1.0f;
    res.pos.y = 1.0f - 2.0f * y;
    res.pos.z = 0;
    res.pos.w = 1;

    return res;
}

static void input_handle_pointer(SDL_Event *event) {
    switch (event->type) {
#ifdef GLES
        case SDL_FINGERDOWN: {
            ePointer_s action = pointer_finger(E_POINTER_DOWN,
                                              event->tfinger.x, event->tfinger.y, event->tfinger.fingerId);
            for (int i = 0; i < L.reg_pointer_e_size; i++)
                L.reg_pointer_e[i].cb(action, L.reg_pointer_e[i].ud);
        }
            break;
        case SDL_FINGERMOTION: {
            ePointer_s action = pointer_finger(E_POINTER_MOVE,
                                              event->tfinger.x, event->tfinger.y, event->tfinger.fingerId);
            for (int i = 0; i < L.reg_pointer_e_size; i++)
                L.reg_pointer_e[i].cb(action, L.reg_pointer_e[i].ud);
        }
            break;
        case SDL_FINGERUP: {
            ePointer_s action = pointer_finger(E_POINTER_UP,
                                              event->tfinger.x, event->tfinger.y, event->tfinger.fingerId);
            for (int i = 0; i < L.reg_pointer_e_size; i++)
                L.reg_pointer_e[i].cb(action, L.reg_pointer_e[i].ud);
        }
            break;
#else
        case SDL_MOUSEBUTTONDOWN: {
            if(event->button.button<=0 || event->button.button>3)
                break;
            ePointer_s action = pointer_mouse(
            (int[]) {E_POINTER_DOWN, E_POINTER_MIDDLE_DOWN, E_POINTER_RIGHT_DOWN}[event->button.button-1]);
            for (int i = 0; i < L.reg_pointer_e_size; i++)
                L.reg_pointer_e[i].cb(action, L.reg_pointer_e[i].ud);
        }
            break;
        case SDL_MOUSEMOTION: {
            ePointer_s action = pointer_mouse(E_POINTER_MOVE);
            for (int i = 0; i < L.reg_pointer_e_size; i++)
                L.reg_pointer_e[i].cb(action, L.reg_pointer_e[i].ud);
        }
            break;
        case SDL_MOUSEBUTTONUP: {
            if(event->button.button<=0 || event->button.button>3)
                break;
            ePointer_s action = pointer_mouse(
            (int[]) {E_POINTER_UP, E_POINTER_MIDDLE_UP, E_POINTER_RIGHT_UP}[event->button.button-1]);
            for (int i = 0; i < L.reg_pointer_e_size; i++)
                L.reg_pointer_e[i].cb(action, L.reg_pointer_e[i].ud);
        }
            break;
#endif
    }
}

static void input_handle_wheel(SDL_Event *event) {
    if (event->wheel.y > 0) {
        for (int i = 0; i < L.reg_wheel_e_size; i++)
            L.reg_wheel_e[i].cb(true, L.reg_pointer_e[i].ud);
    } else if (event->wheel.y < 0) {
        for (int i = 0; i < L.reg_wheel_e_size; i++)
            L.reg_wheel_e[i].cb(false, L.reg_pointer_e[i].ud);
    }

    // it could be possible that y==0, (e. g. x!=0)
}

static void input_handle_keys(SDL_Event *event) {
    bool down = event->type == SDL_KEYDOWN;
    switch (event->key.keysym.sym) {
        case SDLK_UP:
            e_input_keys.up = down;
            break;
        case SDLK_LEFT:
            e_input_keys.left = down;
            break;
        case SDLK_RIGHT:
            e_input_keys.right = down;
            break;
        case SDLK_DOWN:
            e_input_keys.down = down;
            break;
        case SDLK_RETURN:
            e_input_keys.enter = down;
            break;
        case SDLK_SPACE:
            e_input_keys.space = down;
            break;
    }
}


#ifdef GLES
static void input_handle_sensors(SDL_Event *event) {
    SDL_Sensor *sensor = SDL_SensorFromInstanceID(event->sensor.which);
    if (!sensor
        || SDL_SensorGetType(sensor) != SDL_SENSOR_ACCEL) {
        SDL_Log("Couldn't get sensor for sensor event\n");
        return;
    }
    
    const float *data = event->sensor.data;
    memcpy(e_input_accel, data, sizeof(e_input_accel));
    
    //SDL_Log("Gyro update: %.2f, %.2f, %.2f\n", data[0], data[1], data[2]);
      
}
#endif

void e_input_init() {

#ifdef GLES
    int num_sensors = SDL_NumSensors();
    bool accel_opened = false;
    for(int i=0; i<num_sensors; i++) {
        if (SDL_SensorGetDeviceType(i) == SDL_SENSOR_ACCEL) {
            SDL_Sensor *sensor = SDL_SensorOpen(i);
            if (sensor) {
                accel_opened = true;
                break;
            }
        }
    }

    e_input_accel_active = accel_opened;
    if(accel_opened)
        SDL_Log("Opened acceleration sensor");
#endif
}

void e_input_update() {
    if (e_gui_ctx) nk_input_begin(e_gui_ctx);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (e_gui_ctx) nk_sdl_handle_event(&event);

        switch (event.type) {
            case SDL_QUIT:
                e_window_kill();
                return;
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
#ifdef GLES
                case SDL_SENSORUPDATE:
                    input_handle_sensors(&event);
                    break;
#endif
        }
    }

    if (e_gui_ctx) nk_input_end(e_gui_ctx);
}


void e_input_register_pointer_event(ePointerEventFn event, void *user_data) {
    assume(L.reg_pointer_e_size < E_MAX_POINTER_EVENTS, "too many registered pointer events");
    L.reg_pointer_e[L.reg_pointer_e_size++] = (RegPointer) {event, user_data};
}


void e_input_register_wheel_event(eWheelEventFn event, void *user_data) {
    assume(L.reg_wheel_e_size < E_MAX_WHEEL_EVENTS, "too many registered wheel events");
    L.reg_wheel_e[L.reg_wheel_e_size++] = (RegWheel) {event, user_data};
}
