#ifndef S_MEMORY_IMPL_H
#define S_MEMORY_IMPL_H
#ifdef S_IMPL

#include "../error.h"
#include "../log.h"
#include "../memory.h"


#ifdef OPTION_SDL
#include <SDL2/SDL.h>
#endif

void *s_realloc_try(void *memory, ssize n) {
    n = s_max(n, 0);
    if(!memory && n==0)
        return NULL;
#ifdef OPTION_SDL
    void *data = SDL_realloc(memory, n);
#else
    void *data = realloc(memory, n);
#endif
    if(n>0 && !data) {
        s_log_error("reallocation failed for a size of: %lli", n);
        s_error_set("allocation error");
        return memory;
    }
    return data;
}

#endif //S_IMPL
#endif //S_MEMORY_IMPL_H
