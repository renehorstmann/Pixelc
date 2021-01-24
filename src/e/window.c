#include <stdbool.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "e/window.h"
#include "e/definitions.h"



SDL_Window *e_window;
int e_window_size[2];

static bool running;

static eWindowMainLoopFn main_loop_fn;
static Uint32 last_time;

static void loop() {
	Uint32 time = SDL_GetTicks();
    float dtime = (time - last_time) / 1000.0f;
    last_time = time;
    
    main_loop_fn(dtime);
}


void e_window_init(const char *name) {

    if(SDL_Init(E_SDL_INIT_FLAGS) != 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
    
    // initialize IMG
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
        SDL_Log("IMG_Init failed: %s", IMG_GetError());
        exit(EXIT_FAILURE);
    }
    
    // initialize TTF
    if (TTF_Init() == -1) {
		SDL_Log("TTF_Init failed: %s", TTF_GetError());
        exit(EXIT_FAILURE);
	}

    // setup OpenGL usage
    SDL_Log("OpenGL minimal version: %d.%d", E_GL_MAJOR_VERSION, E_GL_MINOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, E_GL_MAJOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, E_GL_MINOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, E_GL_PROFILE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // 8 bits per color
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);


    // create window
    e_window = SDL_CreateWindow(name,
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            640, 480,
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!e_window) {
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindow failed: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Not necessary, but recommended to create a gl context:
    SDL_GL_CreateContext(e_window);
    SDL_GL_SetSwapInterval(1);  // (0=off, 1=V-Sync, -1=addaptive V-Sync)
    

    e_window_update();
}

void e_window_kill() {
	SDL_Log("Window killed");
	running = false;
}

void e_window_update() {
	SDL_GetWindowSize(e_window, &e_window_size[0], &e_window_size[1]);
}

void e_window_main_loop(eWindowMainLoopFn main_loop) {
    main_loop_fn = main_loop;
    running = true;
    last_time = SDL_GetTicks();

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(loop, 0, true);
#else
    while (running)
        loop();
#endif


// ?
#ifndef __EMSCRIPTEN__
    SDL_DestroyWindow(e_window);
    SDL_Quit();
#endif
}


