#include <assert.h>
#include "rhc/allocator.h"
#include "canvas.h"
#include "palette.h"
#include "brush.h"
#include "savestate.h"

//
// private
//

struct SaveState_State {
    void *data[SAVESTATE_MAX_IDS];
    size_t size[SAVESTATE_MAX_IDS];
    int id_size;
};

struct SaveState {
    struct {
        struct SaveState_State *states;
        int state_size;
        savestate_save_fn save_fns[SAVESTATE_MAX_IDS];
        savestate_load_fn load_fns[SAVESTATE_MAX_IDS];
        void *fn_user_data[SAVESTATE_MAX_IDS];
        int id_size;
        int current_id;
    } L;
};

//
// public
//

typedef struct SaveState_State State;

SaveState *savestate_new() {
    return rhc_calloc_raising(sizeof(SaveState));
}

int savestate_register(SaveState *self, savestate_save_fn save_fn, savestate_load_fn load_fn, void *user_data) {
    int id = self->L.id_size++;
    assert(self->L.id_size <= SAVESTATE_MAX_IDS);

    self->L.save_fns[id] = save_fn;
    self->L.load_fns[id] = load_fn;
    self->L.fn_user_data[id] = user_data;

    return id;
}

void savestate_save_data(SaveState *self, const void *data, size_t size) {
    if (self->L.current_id < 0 || self->L.state_size <= 0) {
        log_error("savestate: save_data failed");
        return;
    }
    State *state = &self->L.states[self->L.state_size - 1];
    if (size > 0) {
        state->data[self->L.current_id] = rhc_malloc_raising(size);
        memcpy(state->data[self->L.current_id], data, size);
        state->size[self->L.current_id] = size;
    } else
        state->size[self->L.current_id] = 0;
}

void savestate_save(SaveState *self) {
    log_info("savestate_save: %d", self->L.state_size);

    self->L.state_size++;
    self->L.states = rhc_realloc_raising(self->L.states, self->L.state_size * sizeof(State));

    State *state = &self->L.states[self->L.state_size - 1];
    *state = (State) {0};

    state->id_size = self->L.id_size;

    for (int i = 0; i < self->L.id_size; i++) {
        self->L.current_id = i;
        self->L.save_fns[i](self, self->L.fn_user_data[i]);
    }
}

void savestate_undo(SaveState *self) {
    log_info("savestate_undo: %d", self->L.state_size - 1);

    if (self->L.state_size <= 1) {
        log_error("savestate_undo failed");
        return;
    }

    // kill last state
    State *state = &self->L.states[self->L.state_size - 1];
    for (int i = 0; i < state->id_size; i++) {
        rhc_free(state->data[i]);
    }
    *state = (State) {0};

    // reduce states by one
    self->L.state_size--;

    // undo new last state
    state = &self->L.states[self->L.state_size - 1];
    for (int i = 0; i < state->id_size; i++) {
        self->L.load_fns[i](self, state->data[i], state->size[i], self->L.fn_user_data[i]);
    }
}

void savestate_redo_id(SaveState *self, int savestate_id) {
    if (self->L.state_size <= 0
        || savestate_id >= self->L.id_size
        || savestate_id >= self->L.states[self->L.state_size - 1].id_size) {
        log_error("savestate_redo failed");
        return;
    }
    State *state = &self->L.states[self->L.state_size - 1];
    self->L.load_fns[savestate_id](self,
                                   state->data[savestate_id],
                                   state->size[savestate_id],
                                   self->L.fn_user_data[savestate_id]);
}
