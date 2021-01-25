#ifndef PIXELC_PALETTE_H
#define PIXELC_PALETTE_H

void palette_init();

// return true if the pointer was used (indicate event done)
bool palette_pointer_event(ePointer_s pointer);

void palette_update(float dtime);

void palette_render();

#endif //PIXELC_PALETTE_H
