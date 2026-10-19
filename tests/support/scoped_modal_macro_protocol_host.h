#pragma once
#include "support/ram_macro_protocol_host.h"
static unsigned outer_modal_macro_calls;
static status_code_t dispatch_scoped_modal_macro(macro_id_t id, line_number_t line, parameter_words_t words, uint32_t repeats)
{
    if(id == 100) {
        outer_modal_macro_calls++;
        CHECK(ngc_call_level() == 1 && repeats == 1);
        float argument;
        CHECK(ngc_param_get(24, &argument));
        NEAR(argument, 12);
        return Status_OK;
    }
    return ram_execute_macro(id, line, words, repeats);
}
static inline void run_scoped_modal_macro_program(const char *main, const char *sub, const char *leaf, float y)
{
    ram_macro_override = dispatch_scoped_modal_macro;
    // Real redirected RAM files run in parser check mode; no motor execution is claimed.
    run_ram_macro_protocol(main, sub, leaf);
    CHECK(outer_modal_macro_calls == 1);
    CHECK(gc_state.g66_args == NULL && ngc_call_level() == 0);
    NEAR(gc_state.position[X_AXIS], 3);
    NEAR(gc_state.position[Y_AXIS], y);
}
