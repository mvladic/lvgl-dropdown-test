#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "ui.h"

objects_t objects;
lv_obj_t *tick_value_change_obj;

static void event_handler_cb_main_obj0(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        int32_t value = lv_roller_get_selected(ta);
        if (tick_value_change_obj != ta) {
            assignIntegerProperty(flowState, 1, 4, value, "Failed to assign Selected in Roller widget");
        }
    }
}

static void event_handler_cb_main_obj1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = e->user_data;
    if (event == LV_EVENT_PRESSED) {
        flowPropagateValue(flowState, 0, 0);
    }
}

void create_screen_main() {
    void *flowState = getFlowState(0, 0);
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_roller_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 272, 157);
            lv_obj_set_size(obj, 128, 168);
            lv_roller_set_options(obj, "", LV_ROLLER_MODE_NORMAL);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj0, LV_EVENT_ALL, flowState);
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 430, 158);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj1, LV_EVENT_ALL, flowState);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "Delete");
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
}

void tick_screen_main() {
    void *flowState = getFlowState(0, 0);
    {
        const char *new_val = evalStringArrayPropertyAndJoin(flowState, 1, 3, "Failed to evaluate Options in Roller widget", "\n");
        const char *cur_val = lv_roller_get_options(objects.obj0);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj0;
            lv_roller_set_options(objects.obj0, new_val, LV_ROLLER_MODE_NORMAL);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 1, 4, "Failed to evaluate Selected in Roller widget");
        int32_t cur_val = lv_roller_get_selected(objects.obj0);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj0;
            lv_roller_set_selected(objects.obj0, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
}


void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
}

typedef void (*tick_screen_func_t)();

tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
};

void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
