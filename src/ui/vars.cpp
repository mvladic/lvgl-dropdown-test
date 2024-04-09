#include <lvgl/lvgl.h>

#include <eez/core/assets.h>
#include <eez/core/value.h>
#include <eez/flow/flow.h>

#include "vars.h"
#include "screens.h"
#include "ui.h"

// Define native variables here

static const char *str_arr[] = {
    "Apple", "Banana", "Cherry", "Date", "Elderberry", "Fig", "Grape", "Honeydew", "Kiwi", "Lemon"
};

extern "C" void init_vars() {
    using namespace eez;
    using namespace eez::flow;

    // create a flow value that will contain strings from the str_arr variable defined above
    int num_items = sizeof(str_arr) / sizeof(const char *);

    auto str_arr_flow_value = Value::makeArrayRef(num_items, defs_v3::ARRAY_TYPE_STRING, 0);    
    auto str_arr_flow_array = str_arr_flow_value.getArray();

    for (int i = 0; i < num_items; i++) {
        str_arr_flow_array->values[i] = str_arr[i];
    }

    // set the flow global variable `str_arr` with the value create above
    setGlobalVariable(g_mainAssets, FLOW_GLOBAL_VARIABLE_STR_ARR, str_arr_flow_value);
}
