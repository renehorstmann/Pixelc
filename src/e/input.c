#include "mathc/float.h"
#include "utilc/assume.h"
#include "e/window.h"
#include "e/gui.h"
#include "e/input.h"

bool e_input_up;
bool e_input_left;
bool e_input_right;
bool e_input_down;
bool e_input_enter;
bool e_input_space;


bool e_input_accel_active;
float e_input_accel[3];
const mat4 *e_input_camera_p_inv_ptr;

static const mat4 camera_p_inv_init = MAT4_INIT_EYE;

static struct {
    void (*cb)(ePointer_s, void *);

    void *ud;
} reg_pointer_e[E_MAX_POINTER_EVENTS];

static int reg_pointer_e_size = 0;

static void to_perspective(float gl_x, float gl_y, float *x, float *y) {
    vec4 res = mat4_mul_vec(*e_input_camera_p_inv_ptr, (vec4) {{gl_x, gl_y, 0, 1}});
    *x = res.x;
    *y = res.y;
}

static ePointer_s pointer_mouse(enum ePointerAction action) {
    ePointer_s res;
    res.action = action;
    res.id = 0;

    int x, y;
    SDL_GetMouseState(&x, &y);

    float gl_x = (2.0f * x) / e_window_size[0] - 1.0f;
    float gl_y = 1.0f - (2.0f * y) / e_window_size[1];

    to_perspective(gl_x, gl_y, &res.x, &res.y);
    return res;
}

static ePointer_s pointer_finger(enum ePointerAction action, float x, float y, int finger_id) {
    ePointer_s res;
    res.action = action;
    res.id = finger_id;

    float gl_x = 2.0f * x - 1.0f;
    float gl_y = 1.0f - 2.0f * y;

    to_perspective(gl_x, gl_y, &res.x, &res.y);
    return res;
}


static void input_handle_pointer(SDL_Event *event) {
    switch (event->type) {
#ifdef GLES
        case SDL_FINGERDOWN: {
            ePointer_s action = pointer_finger(E_POINTER_DOWN,
                                              event->tfinger.x, event->tfinger.y, event->tfinger.fingerId);
            for (int i = 0; i < reg_pointer_e_size; i++)
                reg_pointer_e[i].cb(action, reg_pointer_e[i].ud);
        }
            break;
        case SDL_FINGERMOTION: {
            ePointer_s action = pointer_finger(E_POINTER_MOVE,
                                              event->tfinger.x, event->tfinger.y, event->tfinger.fingerId);
            for (int i = 0; i < reg_pointer_e_size; i++)
                reg_pointer_e[i].cb(action, reg_pointer_e[i].ud);
        }
            break;
        case SDL_FINGERUP: {
            ePointer_s action = pointer_finger(E_POINTER_UP,
                                              event->tfinger.x, event->tfinger.y, event->tfinger.fingerId);
            for (int i = 0; i < reg_pointer_e_size; i++)
                reg_pointer_e[i].cb(action, reg_pointer_e[i].ud);
        }
            break;
#else
        case SDL_MOUSEBUTTONDOWN: {
            ePointer_s action = pointer_mouse(E_POINTER_DOWN);
            for (int i = 0; i < reg_pointer_e_size; i++)
                reg_pointer_e[i].cb(action, reg_pointer_e[i].ud);
        }
            break;
        case SDL_MOUSEMOTION: {
            ePointer_s action = pointer_mouse(E_POINTER_MOVE);
            for (int i = 0; i < reg_pointer_e_size; i++)
                reg_pointer_e[i].cb(action, reg_pointer_e[i].ud);
        }
            break;
        case SDL_MOUSEBUTTONUP: {
            ePointer_s action = pointer_mouse(E_POINTER_UP);
            for (int i = 0; i < reg_pointer_e_size; i++)
                reg_pointer_e[i].cb(action, reg_pointer_e[i].ud);
        }
            break;
#endif
    }
}

static void input_handle_keys(SDL_Event *event) {
    bool down = event->type == SDL_KEYDOWN;
    switch (event->key.keysym.sym) {
        case SDLK_UP:
            e_input_up = down;
            break;
        case SDLK_LEFT:
            e_input_left = down;
            break;
        case SDLK_RIGHT:
            e_input_right = down;
            break;
        case SDLK_DOWN:
            e_input_down = down;
            break;
        case SDLK_RETURN:
            e_input_enter = down;
            break;
        case SDLK_SPACE:
            e_input_space = down;
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
	e_input_camera_p_inv_ptr = &camera_p_inv_init;

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
    if(e_gui_ctx) nk_input_begin(e_gui_ctx);

	SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if(e_gui_ctx) nk_sdl_handle_event(&event);

        switch(event.type) {
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

    if(e_gui_ctx) nk_input_end(e_gui_ctx);
}


void e_input_register_pointer_event(ePointerEventFn event, void *user_data) {
    assume(reg_pointer_e_size < E_MAX_POINTER_EVENTS, "too many registered pointer events");
    reg_pointer_e[reg_pointer_e_size].cb = event;
    reg_pointer_e[reg_pointer_e_size++].ud = user_data;
}
