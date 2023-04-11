#ifndef PIXELC_FIND_H
#define PIXELC_FIND_H

#include "s/s.h"
#include "u/sprite.h"


uSprite find_get_pattern_template();

void find_set_pattern_template(uSprite sprite);

bool find_sprite_as_pattern_valid(uSprite sprite);

// returns true if the find pattern image has 2 or more frames
// heavy call, loads the pattern and destroys it
bool find_is_valid();

// runs the find pattern replace algorithm (on the canvas)
// ignore color is top left color in the pattern image
void find_run();

// saves the config to the savestate config.json
// uses object "find"
// auto called on find_set_pattern_template
void find_save_config();

// loads the config from the savestate config.json
// uses object "find"
// auto called at first module usage
void find_load_config();

#endif //PIXELC_FIND_H
