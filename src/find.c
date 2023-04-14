#include "io.h"
#include "e/io.h"
#include "u/json.h"
#include "u/image.h"
#include "m/int.h"
#include "find.h"
#include "canvas.h"
#include "brush.h"


// aabb .xy = top, left, .zw = width, height

typedef struct {
    ivec4 aabb;
    int max_targets;
} PatternItem_s;

#define TYPE PatternItem_s
#define CLASS PatternItemArray
#define FN_NAME patternitemarray
#include "s/dynarray.h"


static struct {
    bool init;
    int frames;
    int layers;
    ivec2 max;
} L;

static bool in_aabb(ivec4 aabb, int c, int r) {
    ivec2 pos = aabb.xy;
    ivec2 wh = aabb.zw;
    return c >= pos.x && c < pos.x + wh.x && r >= pos.y && r < pos.y + wh.y;
}

static void add_in_array(PatternItemArray *rects, int col, int row, uSprite pattern, int layer) {
    uColor_s ignore = *u_sprite_pixel(pattern, 0, 0, 0, layer);

    for (int i = 0; i < rects->size; i++) {
        if (in_aabb(rects->array[i].aabb, col, row)) {
            return;
        }
    }

    // grow aabb
    ivec4 aabb = ivec4_(col, row, 1, 1);
    bool has_grown;
    do {
        has_grown = false;

        int x1 = s_max(0, aabb.x-1);
        int x2 = s_min(pattern.img.cols-1, aabb.x+aabb.v2);
        int y1 = s_max(0, aabb.y-1);
        int y2 = s_min(pattern.img.rows-1, aabb.y+aabb.v3);

        // check up
        if (aabb.y >= 1) {
            for (int c = x1; c < x2; c++) {
                uColor_s color = *u_sprite_pixel(pattern, c, aabb.y - 1, 0, layer);
                if (u_color_equals(color, ignore)) {
                    continue;
                }
                aabb.y--;
                aabb.v3++;
                has_grown = true;
                break;
            }
        }
        // check down
        if (aabb.y + aabb.v3 < pattern.img.rows) {
            for (int c = x1; c < x2; c++) {
                uColor_s color = *u_sprite_pixel(pattern, c, aabb.y + aabb.v3, 0, layer);
                if (u_color_equals(color, ignore)) {
                    continue;
                }
                aabb.v3++;
                has_grown = true;
                break;
            }
        }

        // check left
        if (aabb.x >= 1) {
            for (int r = y1; r < y2; r++) {
                uColor_s color = *u_sprite_pixel(pattern, aabb.x - 1, r, 0, layer);
                if (u_color_equals(color, ignore)) {
                    continue;
                }
                aabb.x--;
                aabb.v2++;
                has_grown = true;
                break;
            }
        }
        // check right
        if (aabb.x + aabb.v2 < pattern.img.cols) {
            for (int r = y1; r < y2; r++) {
                uColor_s color = *u_sprite_pixel(pattern, aabb.x + aabb.v2, r, 0, layer);
                if (u_color_equals(color, ignore)) {
                    continue;
                }
                aabb.v2++;
                has_grown = true;
                break;
            }
        }
    } while (has_grown);

    // minmal 1 target for each pattern, even if empty...
    PatternItem_s add = {
            aabb, 1
    };
    // check max additional targets
    for(int i=2; i<pattern.cols; i++) {
        ignore = *u_sprite_pixel(pattern, 0, 0, i, layer);
        bool valid = false;
        for(int r=aabb.y; r<aabb.y+aabb.v3; r++) {
            for(int c=aabb.x; c<aabb.x+aabb.v2; c++) {
                uColor_s color = *u_sprite_pixel(pattern, c, r, i, layer);
                if (!u_color_equals(color, ignore)) {
                    valid = true;
                }
            }
        }
        if(valid) {
            add.max_targets++;
        } else {
            break;
        }
    }
    patternitemarray_push(rects, add);
}

static PatternItemArray lookup_src_patterns(uSprite pattern, int layer) {
    uColor_s ignore = *u_sprite_pixel(pattern, 0, 0, 0, layer);

    PatternItemArray rects = patternitemarray_new(32);
    for (int r = 0; r < pattern.img.rows; r++) {
        for (int c = 0; c < pattern.img.cols; c++) {
            uColor_s color = *u_sprite_pixel(pattern, c, r, 0, layer);
            if (u_color_equals(color, ignore)) {
                continue;
            }
            add_in_array(&rects, c, r, pattern, layer);
        }
    }
    return rects;
}

static bool is_match(int img_col, int img_row, uSprite pattern, int layer, ivec4 aabb) {
    uImage img = canvas.RO.image;
    int img_layer = canvas.RO.current_image_layer;
    uColor_s ignore = *u_sprite_pixel(pattern, 0, 0, 0, layer);

    for (int r = 0; r < aabb.v3; r++) {
        int img_r = s_clamp(img_row + r, 0, img.rows - 1);
        int pattern_r = aabb.y + r;
        for (int c = 0; c < aabb.v2; c++) {
            int img_c = s_clamp(img_col + c, 0, img.cols - 1);
            int pattern_c = aabb.x + c;

            uColor_s pattern_color = *u_sprite_pixel(pattern, pattern_c, pattern_r, 0, layer);
            if (u_color_equals(pattern_color, ignore)) {
                continue;
            }
            uColor_s image_color = *u_image_pixel(img, img_c, img_r, img_layer);
            if (!u_color_equals(pattern_color, image_color)) {
                return false;
            }
        }
    }
    return true;
}

static bool replace(uImage buffer, int img_col, int img_row, uSprite pattern, int layer, ivec4 aabb, int max_targets) {

    int frame = 1 + (rand() % max_targets);

    bool replaced = false;
    for (int r = 0; r < aabb.v3; r++) {
        int img_r = img_row + r;
        int pattern_r = aabb.y + r;
        for (int c = 0; c < aabb.v2; c++) {
            int img_c = img_col + c;
            int pattern_c = aabb.x + c;

            // check borders
            if(!u_image_contains(buffer, img_c, img_r) || !u_image_contains(pattern.img, pattern_c, pattern_r)) {
                continue;
            }

            uColor_s ignore = *u_sprite_pixel(pattern, 0, 0, frame, layer);
            uColor_s replace_color = *u_sprite_pixel(pattern, pattern_c, pattern_r, frame, layer);
            if (u_color_equals(replace_color, ignore)) {
                continue;
            }

            *u_image_pixel(buffer, img_c, img_r, 0) = replace_color;
            replaced = true;
        }
    }
    return replaced;
}

static void draw_buffer(uImage buffer) {
    for(int r=0; r<buffer.rows; r++) {
        for(int c=0; c<buffer.cols; c++) {
            brush.current_color = *u_image_pixel(buffer, c, r, 0);
            brush_draw_pixel(c, r, U_COLOR_WHITE);
        }
    }
}

static void run_layer(int *out_matches, int *out_replaced, uSprite pattern, int layer) {
    *out_matches = *out_replaced = 0;

    uImage img = canvas.RO.image;
    uImage buffer;
    {
        uImage tmp = img;
        tmp.data = u_image_layer(img, canvas.RO.current_image_layer);
        tmp.layers = 1;
        buffer = u_image_new_clone(tmp);
    }

    PatternItemArray rects = lookup_src_patterns(pattern, layer);
    if(rects.size <= 0) {
        s_log("didnt find any patterns in the lookup");
        return;
    }
    s_log("found %i patterns for the lookup", rects.size);

    // find the biggest rect to offset the matching
    ivec2 offset = {{0, 0}};
    for(int i=0; i<rects.size; i++) {
        if(offset.x < rects.array[i].aabb.v2-1) {
            offset.x = rects.array[i].aabb.v2-1;
        }
        if(offset.y < rects.array[i].aabb.v3-1) {
            offset.y = rects.array[i].aabb.v3-1;
        }
    }

    int matches = 0;
    int replaced = 0;

    // search backwards from bottom right to top left
    // so bigger patterns can overwrite the smallest
    //  else the small may override everything, which will need more complex pattern images
    for (int r = img.rows-1; r >= -offset.y; r--) {
        for (int c = img.cols-1; c >= -offset.x; c--) {
            // check rects backwards
            for (int i = rects.size - 1; i >= 0; i--) {
                if (is_match(c, r, pattern, layer, rects.array[i].aabb)) {
                    matches++;
                    if(replace(buffer, c, r, pattern, layer, rects.array[i].aabb, rects.array[i].max_targets)) {
                        replaced++;
                    }
                }
            }
        }
    }

    if(replaced>0) {
        draw_buffer(buffer);
    }
    u_image_kill(&buffer);

    patternitemarray_kill(&rects);

    *out_matches = matches;
    *out_replaced = replaced;
}

//
// public
//

uSprite find_get_pattern_template() {
    if (!L.init) {
        find_load_config();
        L.init = true;
    }
    uImage img = u_image_new_file(1, e_io_savestate_file_path("find_pattern.png"));
    if (!u_image_valid(img) || L.frames <= 1 || L.layers <= 0 || img.cols % L.frames != 0 || img.rows % L.layers != 0) {
        s_log_warn("invalid pattern size");
        L.frames = 2;
        L.layers = 1;
        L.max = ivec2_set(1);
        return u_sprite_new_file(2, 1, "res/find_pattern_example.png");
    }

    img.layers = L.layers;
    img.rows /= L.layers;
    return u_sprite_new_reorder_from_image(L.frames, img);
}

ivec2 find_get_max_targets_runs() {
    if (!L.init) {
        find_load_config();
        L.init = true;
    }
    return L.max;
}

void find_set_pattern_template(uSprite sprite, int max_targets, int max_runs) {
    s_log("set pattern template");
    if (!u_sprite_valid(sprite) || sprite.cols < FIND_MIN_COLS || sprite.rows > FIND_MAX_RUNS) {
        s_log_warn("invalid sprite, ignoring");
        return;
    }
    u_sprite_save_file(sprite, e_io_savestate_file_path("find_pattern.png"));
    L.frames = sprite.cols;
    L.layers = sprite.rows;
    L.max.x = max_targets;
    L.max.y = max_runs;
    find_save_config();
}

bool find_is_valid() {
    if (!L.init) {
        find_load_config();
        L.init = true;
    }
    uSprite sprite = find_get_pattern_template();
    bool valid = u_sprite_valid(sprite) && sprite.cols >= FIND_MIN_COLS;
    u_sprite_kill(&sprite);
    return valid;
}

FindRunResult_s find_run() {
    if (!L.init) {
        find_load_config();
        L.init = true;
    }
    s_log("run");
    uSprite pattern = find_get_pattern_template();

    uColor_s prev_color = brush.current_color;
    canvas_reload();

    FindRunResult_s res = {0};
    res.runs = L.layers;

    for (int i = 0; i < L.layers; i++) {
        run_layer(&res.matches[i], &res.replaced[i], pattern, i);
    }

    // restore old color
    brush.current_color = prev_color;

    canvas_save();

    return res;
}


void find_save_config() {
    if (!L.init) {
        s_log_error("not init?");
        return;
    }
    s_log("save");

    uJson *config = u_json_new_file(io_config_file());

    uJson *member = u_json_append_object(config, "find");
    u_json_append_int(member, "frames", L.frames);
    u_json_append_int(member, "layers", L.layers);

    u_json_append_int(member, "max_targets", L.max.x);
    u_json_append_int(member, "max_runs", L.max.y);

    u_json_save_file(config, io_config_file(), NULL);
    e_io_savestate_save();

    u_json_kill(&config);
}

void find_load_config() {
    s_log("load");

    uJson *config = u_json_new_file(io_config_file());
    uJson *member = u_json_get_object(config, "find");

    int frames, layers;
    if (!u_json_get_object_int(member, "frames", &frames)
        || !u_json_get_object_int(member, "layers", &layers)) {
        goto CLEAN_UP;
    }

    if (frames <= 1 || layers <= 0) {
        s_log_warn("invalid pattern size");
        goto CLEAN_UP;
    }

    L.frames = frames;
    L.layers = layers;

    ivec2 max;
    if (!u_json_get_object_int(member, "max_targets", &max.x)
        || !u_json_get_object_int(member, "max_runs", &max.y)) {
        goto CLEAN_UP;
    }

    if(max.x < 1 || max.y < 1) {
        s_log_warn("invalid max targets, runs");
        goto CLEAN_UP;
    }

    L.max = max;

    CLEAN_UP:
    u_json_kill(&config);
}
