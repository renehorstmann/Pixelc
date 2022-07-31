#include "r/r.h"
#include "e/io.h"
#include "u/pose.h"
#include "u/json.h"
#include "io.h"
#include "camera.h"
#include "palette.h"
#include "tooltip.h"


#define SHOW_TIME 5.0
#define FADE_TIME 1.0

struct Tooltip_Globals tooltip;

static struct {
    RoText title;
    RoText tip;
    vec2 title_size;
    vec2 tip_size;
    float time;
} L;


//
// public
//


void tooltip_init() {
    tooltip.show = true;
    
    L.title = ro_text_new_font55(TOOLTIP_TITLE_MAX);
    L.tip = ro_text_new_font85(TOOLTIP_TIP_MAX);
    
    u_pose_set_size(&L.title.pose, 1, 2);
}

void tooltip_update(float dtime) {
    if(!tooltip.show || L.time < 0)
        return;
    L.time -= dtime;
    
    
    
    float phs = palette_get_hud_size();

    float w = s_max(L.title_size.x, L.tip_size.x);
    float h = L.title_size.y*2 + L.tip_size.y + 2;
    
    float left, top;
    if(camera_is_portrait_mode()) {
        left = camera.RO.right - w - 6;
        top = camera.RO.bottom + phs + h + 2;
    } else {
        left = camera.RO.right - phs - w - 2;
        top = camera.RO.top - 2;
    }
    
    u_pose_set_xy(&L.title.pose, left, top);
    u_pose_set_xy(&L.tip.pose, left, top-L.title_size.y*2-2);
}

void tooltip_render(const mat4 *cam_mat) {
    if (!tooltip.show || L.time < 0)
        return;

    float alpha = sca_min(1, sca_mix(0, 1, L.time));

    u_pose_shift_xy(&L.title.pose, 1, -1);
    u_pose_shift_xy(&L.tip.pose, 1, -1);
    ro_text_set_color(&L.title, (vec4) {{0.3, 0.3, 0.3, alpha*0.25}});
    ro_text_set_color(&L.tip, (vec4) {{0.2, 0.2, 0.2, alpha*0.25}});
    
    ro_text_render(&L.title, cam_mat);
    ro_text_render(&L.tip, cam_mat);
    
    u_pose_shift_xy(&L.title.pose, -1, 1);
    u_pose_shift_xy(&L.tip.pose, -1, 1);
    ro_text_set_color(&L.title, (vec4) {{1, 1, 1, alpha}});
    ro_text_set_color(&L.tip, (vec4) {{0.95, 0.95, 0.95, alpha}});
    
    ro_text_render(&L.title, cam_mat);
    ro_text_render(&L.tip, cam_mat);
}

void tooltip_set(const char *title, const char *tip) {
    if(!tooltip.show)
        return;
    s_log("set: %s", title);
    
    L.title_size = ro_text_set_text(&L.title, title);
    L.tip_size = ro_text_set_text(&L.tip, tip);
    
    L.time = SHOW_TIME;
}


void tooltip_save_config() {
    s_log("save");

    uJson *config = u_json_new_file(io_config_file());

    uJson *member = u_json_append_object(config, "tooltip");

    u_json_append_bool(member, "show", tooltip.show);
    u_json_save_file(config, io_config_file(), NULL);
    e_io_savestate_save();

    u_json_kill(&config);
}

void tooltip_load_config() {
    s_log("load");

    uJson *config = u_json_new_file(io_config_file());

    uJson *member = u_json_get_object(config, "tooltip");

   const bool *read = u_json_get_object_bool(member, "show");
    if(read) {
        tooltip.show = *read;
    }
    
    u_json_kill(&config);
}