#include <stdio.h>

#include <lvgl/lvgl.h>

#include <eez/core/assets.h>
#include <eez/core/value.h>
#include <eez/flow/flow.h>

#include "actions.h"
#include "screens.h"
#include "ui.h"
#include "vars.h"

extern void action_dump_vars(lv_event_t * e) {
    using namespace eez;
    using namespace eez::flow;

    printf("----------------\n");
    printf("Dump str_arr:\n");

    // get flow variable `str_var`
    Value str_arr_flow_value = getGlobalVariable(g_mainAssets, FLOW_GLOBAL_VARIABLE_STR_ARR);
    auto str_arr_flow_array = str_arr_flow_value.getArray();
    for (uint32_t i = 0; i < str_arr_flow_array->arraySize; i++) {
        // get string at index i
        const char *str = str_arr_flow_array->values[i].getString();
        printf("\t%s\n", str);
    }    
}