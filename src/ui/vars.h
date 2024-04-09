#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif



enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_STR_ARR = 0,
    FLOW_GLOBAL_VARIABLE_SEL_INDEX = 1
};


void init_vars();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/