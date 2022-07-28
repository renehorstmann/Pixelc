#ifndef E_CORE_H
#define E_CORE_H

//
// this file just includes SDL and OpenGL headers
// and has a emscripten compatible exit failure function
//

#include "s/s.h"

#define GL_GLEXT_PROTOTYPES

#ifdef OPTION_GLEW

#include <GL/glew.h>

#endif

#include <SDL2/SDL.h>

#ifdef OPTION_TTF
#include <SDL2/SDL_ttf.h>
#endif

#ifdef OPTION_SOCKET
#include <SDL2/SDL_net.h>
#endif

#ifndef OPTION_GLEW
#include <SDL2/SDL_opengl.h>
#endif


#ifdef PLATFORM_EMSCRIPTEN
#include <emscripten.h>
// #include <emscripten/html5.h>
#endif


// exit the app, on emscripten an error message will be shown
static void e_exit_failure() {
#ifdef PLATFORM_EMSCRIPTEN
    emscripten_cancel_main_loop();
    EM_ASM(
            set_exit_failure_error_msg();
            );
#endif
    exit(EXIT_FAILURE);
}

#ifdef PLATFORM_ANDROID
#ifndef SOME_ANDROID_PACKAGE
#define SOME_ANDROID_PACKAGE                                 de_horsimann_some
#endif
#define SOME_ANDROID_CONCAT1(prefix, class, function)        SOME_ANDROID_CONCAT2(prefix, class, function)
#define SOME_ANDROID_CONCAT2(prefix, class, function)        Java_ ## prefix ## _ ## class ## _ ## function
#define SOME_ANDROID_INTERFACE(function)                     SOME_ANDROID_CONCAT1(SOME_ANDROID_PACKAGE, SDLActivity, function)
#endif


#endif //E_CORE_H
