#pragma once
#include "support/macro_parser_host.h"
static float uvw_arguments[3];
static status_code_t capture_uvw(macro_id_t id, line_number_t line, parameter_words_t words, uint32_t repeats)
{
    status_code_t status = capture_macro(id, line, words, repeats);
    CHECK(ngc_param_get(21, &uvw_arguments[0]));
    CHECK(ngc_param_get(22, &uvw_arguments[1]));
    CHECK(ngc_param_get(23, &uvw_arguments[2]));
    return status;
}
static inline void check_macro_uvw_arguments(const char *command, float u, float v, float w, bool inches)
{
    prepare_macro_parser();
    grbl.on_macro_execute = capture_uvw;
    CHECK(ngc_param_set(21, 99) && ngc_param_set(22, 88) && ngc_param_set(23, 77));
    int32_t scope = ngc_call_level();
    if(inches) CHECK(macro_block("G20") == Status_OK);
    CHECK(macro_block(command) == Status_OK);
    CHECK(macro_calls == 1 && called_macro == 100 && macro_repeats == 1);
    CHECK(macro_words.u && macro_words.v && macro_words.w);
    NEAR(uvw_arguments[0], u); NEAR(uvw_arguments[1], v); NEAR(uvw_arguments[2], w);
    CHECK(ngc_call_level() == scope);
    float value;
    CHECK(ngc_param_get(21, &value)); NEAR(value, 99);
    CHECK(ngc_param_get(22, &value)); NEAR(value, 88);
    CHECK(ngc_param_get(23, &value)); NEAR(value, 77);
    CHECK(gc_state.modal.units_imperial == inches);
    CHECK(plan_get_current_block() == NULL);
    for(unsigned axis = 0; axis < N_AXIS; axis++) NEAR(gc_state.position[axis], 0);
}
