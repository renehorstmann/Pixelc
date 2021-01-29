#ifndef PIXELC_SAVESTATE_H
#define PIXELC_SAVESTATE_H

void savestate_init();

void savestate_save();

void savestate_undo();

void savestate_copy_last_layer();

#endif //PIXELC_SAVESTATE_H
