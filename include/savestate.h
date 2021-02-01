#ifndef PIXELC_SAVESTATE_H
#define PIXELC_SAVESTATE_H

#include <stdlib.h> // size_t

#define SAVESTATE_MAX_IDS 64

typedef void (*savestate_save_fn)(void **data, size_t *size);
typedef void (*savestate_load_fn)(const void *data, size_t size);

void savestate_init();

int savestate_register(savestate_save_fn save_fn, savestate_load_fn load_fn);

void savestate_save();

void savestate_undo();

void savestate_redo_id(int savestate_id);

#endif //PIXELC_SAVESTATE_H
