#include "e/window.h"
#include "e/io.h"
#include "u/pose.h"
#include "u/json.h"
#include "mathc/utils/camera.h"
#include "mathc/sca/float.h"
#include "camera.h"


// comment out to not use a pixel perfect camera
#define PIXEL_PERFECT


//
// public
//

struct Camera_Globals camera;

void camera_init() {
    camera.matrices.v = mat4_eye();
    camera.matrices.v_inv = mat4_eye();
    camera.matrices.p = mat4_eye();
    camera.matrices.p_inv = mat4_eye();
    camera.matrices.vp = mat4_eye();
//    camera.matrices.v_p_inv = mat4_eye();
    camera.size = CAMERA_SIZE_SMALL;
}

void camera_update() {
    assume(camera.size >= CAMERA_SIZE_MIN && camera.size <= CAMERA_SIZE_MAX, "not in limits");

    int wnd_width = e_window.size.x;
    int wnd_height = e_window.size.y;

    float smaller_size = wnd_width < wnd_height ? wnd_width : wnd_height;
    camera.RO.scale = smaller_size / camera.size;

#ifdef PIXEL_PERFECT
    if (camera.RO.scale > 1) {
        camera.RO.scale = sca_floor(camera.RO.scale);
    }
#endif

    float width_2 = wnd_width / (2 * camera.RO.scale);
    float height_2 = wnd_height / (2 * camera.RO.scale);

    // begin: (top, left) with a full pixel
    // end: (bottom, right) with a maybe splitted pixel
    camera.RO.screen_left = -floorf(width_2);
    camera.RO.screen_top = floorf(height_2);
    camera.RO.screen_right = width_2 + (width_2 - floorf(width_2));
    camera.RO.screen_bottom = -height_2 - (height_2 - floorf(height_2));

    camera.matrices.p = mat4_camera_ortho(camera.RO.screen_left, camera.RO.screen_right, camera.RO.screen_bottom,
                                          camera.RO.screen_top, -1, 1);

    camera.matrices.v_inv = mat4_inv(camera.matrices.v);
    camera.matrices.p_inv = mat4_inv(camera.matrices.p);

    camera.matrices.vp = mat4_mul_mat(camera.matrices.p, camera.matrices.v_inv);

//    camera.matrices.v_p_inv = mat4_mul_mat(camera.matrices.v, camera.matrices.p_inv);

    camera.RO.left = sca_floor(camera.RO.screen_left);
    camera.RO.right = sca_ceil(camera.RO.screen_right);
    camera.RO.bottom = sca_floor(camera.RO.screen_bottom);
    camera.RO.top = sca_ceil(camera.RO.screen_top);
}


void camera_set_pos(float x, float y) {
    u_pose_set_xy(&camera.matrices.v, x, y);
}

void camera_set_zoom(float size) {
    u_pose_set_size(&camera.matrices.v, size, size);
}

void camera_set_angle(float alpha) {
    u_pose_set_angle(&camera.matrices.v, alpha);
}

bool camera_is_portrait_mode() {
    switch (camera.rotate_mode) {
        case CAMERA_ROTATE_MODE_PORTRAIT:
            return true;
        case CAMERA_ROTATE_MODE_LANDSCAPE:
            return false;
        default:
            return camera_height() > camera_width();
    }
}


void camera_save_config() {
    log_info("save");

    uJson *config = u_json_new_file(
            e_io_savestate_file_path("config.json"));

    uJson *member = u_json_append_object(config, "camera");

    u_json_append_int(member, "size", camera.size);
    u_json_append_int(member, "rotate_mode", camera.rotate_mode);

    u_json_save_file(config,
                     e_io_savestate_file_path("config.json"));
    e_io_savestate_save();

    u_json_kill(&config);
}

void camera_load_config() {
    log_info("load");

    uJson *config = u_json_new_file(
            e_io_savestate_file_path("config.json"));

    uJson *member = u_json_get_object(config, "camera");

    int read;
    if (u_json_get_object_int(member, "size", &read)) {
        if (read >= CAMERA_SIZE_MIN && read <= CAMERA_SIZE_MAX)
            camera.size = read;
    }
    if (u_json_get_object_int(member, "rotate_mode", &read)) {
        if (read >= 0 && read < CAMERA_ROTATE_NUM_MODES)
            camera.rotate_mode = read;
    }

    u_json_kill(&config);
}
