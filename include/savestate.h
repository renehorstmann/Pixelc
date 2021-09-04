#ifndef PIXELC_SAVESTATE_H
#define PIXELC_SAVESTATE_H

#include <stdlib.h> // size_t

#define SAVESTATE_MAX_IDS 64

typedef struct SaveState SaveState;

typedef void (*savestate_save_fn)(SaveState *savestate, void *user_data);

typedef void (*savestate_load_fn)(SaveState *savestate, const void *data, size_t size, void *user_data);

SaveState *savestate_new();

int savestate_register(SaveState *self, savestate_save_fn save_fn, savestate_load_fn load_fn, void *user_data);

void savestate_save_data(SaveState *self, const void *data, size_t size);

void savestate_save(SaveState *self);

void savestate_undo(SaveState *self);

void savestate_redo_id(SaveState *self, int savestate_id);

#endif //PIXELC_SAVESTATE_H
