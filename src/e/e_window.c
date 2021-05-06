#include <stdbool.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "e/window.h"
#include "e/definitions.h"

// rhc implementation source file, only once in a project
#include "rhc/rhc_impl.h"


#define MAX_DELTA_TIME 5.0 // seconds

// not declared in window.h
void e_window_handle_window_event(const SDL_Event *event);


struct eWindowGlobals_s e_window;



//
// private 
//

typedef struct {
    e_window_pause_callback_fn cb;
    void *ud;    
} RegPause;

static struct {
    bool pause;
    bool running;

    e_window_main_loop_fn main_loop_fn;
    Uint32 last_time;
    
    RegPause reg_pause_e[E_WINDOW_MAX_PAUSE_EVENTS];
    int reg_pause_e_size;
} L;

static void check_resume() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        e_window_handle_window_event(&event); 
    }
}

static void loop() {
    if(L.pause) {
        check_resume();
        return;
    }
                
    SDL_GetWindowSize(e_window.window, &e_window.size.x, &e_window.size.y);

    Uint32 time = SDL_GetTicks();
    float dtime = (time - L.last_time) / 1000.0f;
    L.last_time = time;

    if(dtime < MAX_DELTA_TIME)
        L.main_loop_fn(dtime);
}

static void pause() {
    if(L.pause)
        return;
    log_info("e_window: pause");
    L.pause = true;
    for(int i=0; i<L.reg_pause_e_size; i++) {
        L.reg_pause_e[i].cb(false, L.reg_pause_e[i].ud);
    }
}

static void resume() {
    if(!L.pause)
        return;
    log_info("e_window: resume");
    for(int i=0; i<L.reg_pause_e_size; i++) {
        L.reg_pause_e[i].cb(true, L.reg_pause_e[i].ud);
    }
    
    // delta_time should not be near infinity...
    L.last_time = SDL_GetTicks();
    L.pause = false;
}



//
// public
//

void e_window_init(const char *name) {
#ifdef NDEBUG
    rhc_log_set_min_level(RHC_LOG_WARN);
#else
    rhc_log_set_min_level(RHC_LOG_TRACE);
#endif

    if (SDL_Init(E_SDL_INIT_FLAGS) != 0) {
        log_error("e_window_init: SDL_Init failed: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }


    // initialize IMG
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        log_error("e_window_init: IMG_Init failed: %s", IMG_GetError());
        exit(EXIT_FAILURE);
    }

#ifdef OPTION_TTF
    // initialize TTF
    if (TTF_Init() == -1) {
        log_error("e_window_init: TTF_Init failed: %s", TTF_GetError());
        exit(EXIT_FAILURE);
    }
#endif

    // setup OpenGL usage
    log_info("e_window_init: OpenGL minimal version: %d.%d", E_GL_MAJOR_VERSION, E_GL_MINOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, E_GL_MAJOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, E_GL_MINOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, E_GL_PROFILE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // create window
    e_window.window = SDL_CreateWindow(name,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640, 480,
            SDL_WINDOW_OPENGL 
            | SDL_WINDOW_RESIZABLE
            );
    if (!e_window.window) {
        log_error("e_window_init: SDL_CreateWindow failed: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_SetWindowMinimumSize(e_window.window, 480, 320);
    

    // Not necessary, but recommended to create a gl context:
    e_window.gl_context = SDL_GL_CreateContext(e_window.window);
    if (!e_window.gl_context) {
        log_error("e_window_init: SDL_GL_CreateContext failed: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_GL_SetSwapInterval(1);  // (0=off, 1=V-Sync, -1=addaptive V-Sync)

#ifdef OPTION_GLEW
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        /* Problem: glewInit failed, something is seriously wrong. */
        log_error( "e_window_init faled: %s", glewGetErrorString(err));
        exit(EXIT_FAILURE);
    }
    log_info("e_window_init: Using GLEW version: %s", glewGetString(GLEW_VERSION));
#endif

    SDL_GetWindowSize(e_window.window, &e_window.size.x, &e_window.size.y);
}

void e_window_kill() {
    log_info("e_window_kill: killing...");
    L.running = false;
    
#ifdef __EMSCRIPTEN__
    emscripten_cancel_main_loop();
#endif
}

void e_window_main_loop(e_window_main_loop_fn main_loop) {
    L.main_loop_fn = main_loop;
    L.pause = false;
    L.running = true;
    L.last_time = SDL_GetTicks();

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(loop, 0, true);
#else
    while (L.running)
        loop();
#endif


    SDL_DestroyWindow(e_window.window);
#ifdef OPTION_TTF
    TTF_Quit();
#endif 
    IMG_Quit();
    SDL_Quit();
    log_info("e_window_kill: killed");
}

void e_window_set_screen_mode(enum e_window_screen_modes mode) {
    Uint32 sdl_mode = 0;
    
    // emscripten is always fullscreen
#ifndef __EMSCRIPTEN__
    log_info("e_window_set_screen_mode: %i", mode);
    if(mode == E_WINDOW_MODE_MAXIMIZED) {
        sdl_mode = SDL_WINDOW_FULLSCREEN_DESKTOP;
    } else if(mode == E_WINDOW_MODE_FULLSCREEN) {
        sdl_mode = SDL_WINDOW_FULLSCREEN;
    }
#endif
    SDL_SetWindowFullscreen(e_window.window, sdl_mode);
}


void e_window_register_pause_callback(e_window_pause_callback_fn event, void *user_data) {
    assume(L.reg_pause_e_size < E_WINDOW_MAX_PAUSE_EVENTS, "too many registered pause events");
    L.reg_pause_e[L.reg_pause_e_size++] = (RegPause){event, user_data};
}

void e_window_unregister_pause_callback(e_window_pause_callback_fn event_to_unregister) {
    bool found = false;
    for (int i = 0; i < L.reg_pause_e_size; i++) {
        if (L.reg_pause_e[i].cb == event_to_unregister) {
            found = true;
            // move to close hole
            for (int j = i; j < L.reg_pause_e_size - 1; j++) {
                L.reg_pause_e[j] = L.reg_pause_e[j + 1];
            }
            L.reg_pause_e_size--;
            i--; // check moved
        }
    }
    if (!found) {
        log_warn("e_window_unregister_pause_callback failed: event not registered");
    }
}


static void log_window_event(const SDL_Event *event);

// not in the window.h header, used by e_input.c
void e_window_handle_window_event(const SDL_Event *event) {
    if (event->type == SDL_QUIT) {
        e_window_kill();
        return;
    }
    if(event->type == SDL_WINDOWEVENT) {
//        log_window_event(event);
        switch (event->window.event) {
//        case SDL_WINDOWEVENT_SHOWN:
//        case SDL_WINDOWEVENT_RESTORED:
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            resume();
            break;
//        case SDL_WINDOWEVENT_HIDDEN:
//        case SDL_WINDOWEVENT_MINIMIZED:
        case SDL_WINDOWEVENT_FOCUS_LOST:
            pause();
            break;
        }
    }
}


static void log_window_event(const SDL_Event *event) {
    if (event->type == SDL_WINDOWEVENT){
        switch (event->window.event) {
        case SDL_WINDOWEVENT_SHOWN:
            log_trace("Window %d shown", event->window.windowID);
            break;       
        case SDL_WINDOWEVENT_HIDDEN:
            log_trace("Window %d hidden", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_EXPOSED:
            log_trace("Window %d exposed", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_MOVED:
            log_trace("Window %d moved to %d,%d", event->window.windowID, event->window.data1, event->window.data2);
            break;
        case SDL_WINDOWEVENT_RESIZED:
            log_trace("Window %d resized to %dx%d", event->window.windowID, event->window.data1, event->window.data2);
            break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            log_trace("Window %d size changed to %dx%d", event->window.windowID, event->window.data1, event->window.data2);
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            log_trace("Window %d minimized", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            log_trace("Window %d maximized", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_RESTORED:
            log_trace("Window %d restored", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_ENTER:
            log_trace("Mouse entered window %d", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_LEAVE:
            log_trace("Mouse left window %d", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            log_trace("Window %d gained keyboard focus", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            log_trace("Window %d lost keyboard focus", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_CLOSE:
            log_trace("Window %d closed", event->window.windowID);
            break;
#if SDL_VERSION_ATLEAST(2, 0, 5) 
            case SDL_WINDOWEVENT_TAKE_FOCUS : log_trace("Window %d is offered a focus", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_HIT_TEST:
            log_trace("Window %d has a special hit test", event->window.windowID);
            break;
#endif 
            default : log_trace("Window %d got unknown event %d", event->window.windowID, event->window.event);
            break;
        }
    }
}

