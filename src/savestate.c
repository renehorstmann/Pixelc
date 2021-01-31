#include "utilc/alloc.h"
#include "canvas.h"
#include "palette.h"
#include "brush.h"
#include "savestate.h"

typedef struct {
    int palette_color;
    enum brushmodes brush_mode;
} State;


static struct {
    State *states;
    int size;
} L;

static void state_init(State *self,
                       int palette_color,
                       enum brushmodes brush_mode) {
    self->palette_color = palette_color;
    self->brush_mode = brush_mode;
}

static void state_kill(State *self) {
    *self = (State){0};
}

void savestate_init() {

}

void savestate_save() {
    SDL_Log("savestate_save state: %d", L.size);

    L.states = ReNew(State, L.states, ++L.size);
    State *s = &L.states[L.size - 1];

    state_init(s,
               palette_get_color(),
               brush_get_mode()
    );
}

void savestate_undo() {
    SDL_Log("savestate_undo state: %d", L.size);

    if(L.size<0) {
        SDL_Log("savestate_undo failed hard: size=%d", L.size);
        L.size = 0;
    }
    if(L.size == 0)
        return;

    State *s = &L.states[--L.size];
    palette_set_color(s->palette_color);
    brush_set_mode(s->brush_mode);

    state_kill(s);
}

void savestate_copy_last_layer() {
    State *s = &L.states[L.size - 1];
}
