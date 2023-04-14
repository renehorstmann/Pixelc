#ifndef PIXELC_FIND_H
#define PIXELC_FIND_H

#include "s/s.h"
#include "u/sprite.h"

#define FIND_MIN_COLS 2

// just a copy of CANVAS_MAX_LAYERS
#define FIND_MAX_RUNS 96

typedef struct {
    int matches[FIND_MAX_RUNS];
    int replaced[FIND_MAX_RUNS];
    int runs;
} FindRunResult_s;

uSprite find_get_pattern_template();

ivec2 find_get_max_targets_runs();

// a sprite with 2 cols has 1 target, 3=2 (targets = cols-1)
// runs = layers
void find_set_pattern_template(uSprite sprite, int max_targets, int max_runs);

// returns true if the find pattern image has 2 or more frames
// heavy call, loads the pattern and destroys it
bool find_is_valid();

// runs the find pattern replace algorithm (on the canvas)
// ignore color is top left color in the pattern image
FindRunResult_s find_run();

// saves the config to the savestate config.json
// uses object "find"
// auto called on find_set_pattern_template
void find_save_config();

// loads the config from the savestate config.json
// uses object "find"
// auto called at first module usage
void find_load_config();

#endif //PIXELC_FIND_H
