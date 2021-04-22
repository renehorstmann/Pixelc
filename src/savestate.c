#include <assert.h>
#include "rhc/allocator.h"
#include "canvas.h"
#include "palette.h"
#include "brush.h"
#include "savestate.h"

typedef struct {
    void *data[SAVESTATE_MAX_IDS];
    size_t size[SAVESTATE_MAX_IDS];
    int id_size;
} State;


static struct {
    State *states;
    int state_size;
    savestate_save_fn save_fns[SAVESTATE_MAX_IDS];
    savestate_load_fn load_fns[SAVESTATE_MAX_IDS];
    int id_size;
    int current_id;
} L;


void savestate_init() {

}

int savestate_register(savestate_save_fn save_fn, savestate_load_fn load_fn) {
    int id = L.id_size++;
    assert(L.id_size <= SAVESTATE_MAX_IDS);

    L.save_fns[id] = save_fn;
    L.load_fns[id] = load_fn;

    return id;
}

void savestate_save_data(const void *data, size_t size) {
    if(L.current_id <0 || L.state_size <= 0) {
        log_error("savestate: save_data failed");
        return;
    }
    State *state = &L.states[L.state_size - 1];
    if (size > 0) {
        state->data[L.current_id] = rhc_malloc_raising(size);
        memcpy(state->data[L.current_id], data, size);
        state->size[L.current_id] = size;
    } else
        state->size[L.current_id] = 0;
}

void savestate_save() {
    log_info("savestate_save: %d", L.state_size);

    L.state_size++;
    L.states = rhc_realloc_raising(L.states, L.state_size * sizeof(State));

    State *state = &L.states[L.state_size - 1];
    *state = (State) {0};

    state->id_size = L.id_size;

    for (int i = 0; i < L.id_size; i++) {
        L.current_id = i;
        L.save_fns[i]();
    }
}

void savestate_undo() {
    log_info("savestate_undo: %d", L.state_size - 1);

    if (L.state_size <= 1) {
        log_error("savestate_undo failed");
        return;
    }

    // kill last state
    State *state = &L.states[L.state_size - 1];
    for (int i = 0; i < state->id_size; i++) {
        rhc_free(state->data[i]);
    }
    *state = (State) {0};

    // reduce states by one
    L.state_size--;

    // undo new last state
    state = &L.states[L.state_size - 1];
    for (int i = 0; i < state->id_size; i++) {
        L.load_fns[i](state->data[i], state->size[i]);
    }
}

void savestate_redo_id(int savestate_id) {
    if (L.state_size <= 0
        || savestate_id >= L.id_size
        || savestate_id >= L.states[L.state_size - 1].id_size) {
        log_error("savestate_redo failed");
        return;
    }
    State *state = &L.states[L.state_size - 1];
    L.load_fns[savestate_id](state->data[savestate_id], state->size[savestate_id]);
}
