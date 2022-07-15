#include "r/r.h"
#include "u/pose.h"
#include "canvas.h"
#include "camera.h"
#include "animation.h"


struct Animation_Globals animation;

struct {
    RoText horsimann;
    RoBatch ro[CANVAS_MAX_LAYERS];

    int mcols, mrows;
    float size;
    int frames;
    float time;
    float fps;
    
} L;


static void set_pose(float palette_hud_size, int c, int r) {
    uImage img = canvas.RO.image;

    float w = L.size * img.cols / L.frames;
    float h = L.size * img.rows;

    float x, y;
    if (camera_is_portrait_mode()) {
        x = camera.RO.left + w / 2 + c * w;
        y = camera.RO.bottom + palette_hud_size + h / 2 + r * h;
    } else {
        x = camera.RO.right - palette_hud_size - w / 2 - c * w;
        y = camera.RO.top - h / 2 - r * h;
    }

    mat4 pose = u_pose_new(floorf(x), floorf(y), w, h);
    for (int i = 0; i <= canvas.RO.current_image_layer; i++) {
        L.ro[i].rects[r * L.mcols + c].pose = pose;
    }
}


//
// public
//


void animation_init(int multi_cols, int multi_rows, float size, int frames, float fps) {
    uImage img = canvas.RO.image;
    if(img.cols % frames != 0)
        frames = 1;

    L.mcols = multi_cols;
    L.mrows = multi_rows;
    L.size = size;
    L.frames = frames;
    L.fps = fps;


    for (int i = 0; i < img.layers; i++) {
        rTexture tex = r_texture_new(img.cols, img.rows, frames, 1, u_image_layer(img, i));
        L.ro[i] = ro_batch_new(L.mcols * L.mrows, tex);
    }

    L.horsimann = ro_text_new_font55(9);
    ro_text_set_color(&L.horsimann, (vec4) {{0.25, 0.25, 0.25, 1}});
    ro_text_set_text(&L.horsimann, "horsimann");

}

void animation_update(float palette_hud_size, float dtime) {
    
    if (!animation.show) {
        if (camera_is_portrait_mode())
            u_pose_set_xy(&L.horsimann.pose,
                          camera.RO.left + 1,
                          ceilf(camera.RO.bottom + palette_hud_size + 6));
        else
            u_pose_set_xy(&L.horsimann.pose,
                          camera.RO.left + 40, ceilf(camera.RO.bottom + 6));
        return;
    }


    for (int r = 0; r < L.mrows; r++) {
        for (int c = 0; c < L.mcols; c++) {
            set_pose(palette_hud_size, c, r);
        }
    }

    L.time = fmodf(L.time + dtime, L.frames / L.fps);
    float frame = floorf(L.time * L.fps);
    for (int i = 0; i <= canvas.RO.current_image_layer; i++) {
        for (int j = 0; j < L.ro[i].num; j++) {
            L.ro[i].rects[j].sprite.x = frame;
        }
    }

    uImage img = canvas.RO.image;
    for (int i = 0; i <= canvas.RO.current_image_layer; i++) {
        r_texture_set(L.ro[i].tex, u_image_layer(img, i));
    }
}

void animation_render(const mat4 *cam_mat) {
    
    if (!animation.show) {
        //ro_text_render(&L.horsimann, cam_mat);
        return;
    }

    for (int i = 0; i <= canvas.RO.current_image_layer; i++) {
        ro_batch_render(&L.ro[i], cam_mat, true);
    }
}
