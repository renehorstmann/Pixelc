#include "utilc/alloc.h"
#include "canvas.h"
#include "palette.h"
#include "brush.h"
#include "savestate.h"

typedef struct {
    Layer *canvas_layers;
    int canvas_size;
    int canvas_current;
    int palette_color;
    enum brushmodes brush_mode;
} State;


static struct {
    State *states;
    int size;
} L;

static void state_init(State *self,
                       Layer *canvas_layers, int canvas_size, int canvas_current,
                       int palette_color,
                       enum brushmodes brush_mode) {
    self->canvas_layers = New(Layer, canvas_size);
    for(int i=0; i<canvas_size; i++) {
        layer_init(&self->canvas_layers[i]);
        layer_copy(&self->canvas_layers[i], canvas_layers[i]);
    }
    self->canvas_size = canvas_size;
    self->canvas_current = canvas_current;

    self->palette_color = palette_color;
    self->brush_mode = brush_mode;
}

static void state_kill(State *self) {
    for(int i=0; i<self->canvas_size; i++) {
        layer_kill(&self->canvas_layers[i]);
    }
    free(self->canvas_layers);
    *self = (State){0};
}

void savestate_init() {

}

void savestate_save() {
    SDL_Log("savestate_save state: %d", L.size);

    L.states = ReNew(State, L.states, ++L.size);
    State *s = &L.states[L.size - 1];

    state_init(s,
               canvas_layers(),
               canvas_size(),
               canvas_current(),
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
    canvas_set_layers(s->canvas_layers, s->canvas_size);
    canvas_set_current(s->canvas_current);
    palette_set_color(s->palette_color);
    brush_set_mode(s->brush_mode);

    state_kill(s);
}

void savestate_copy_last_layer() {
    State *s = &L.states[L.size - 1];

    int c = canvas_current();
    canvas_set_layer(s->canvas_layers[c], c);
}
