#pragma once
#include "support/ram_macro_motion_host.h"
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
    ram_prepare_assets = install_scoped_motion;
    char synchronized_main[512];
    CHECK(strlen(main) + sizeof("G4P0.01\n") <= sizeof(synchronized_main));
    strcpy(synchronized_main, main);
    strcat(synchronized_main, "G4P0.01\n");
    run_ram_macro_protocol(synchronized_main, sub, leaf);
    CHECK(scoped_motion_services > 0 && plan_get_current_block() == NULL);
    CHECK(wake_calls > 0 && !st_is_stepping());
    for(unsigned i = 0; i < 3; i++)
        CHECK(ram_macro_errors[i] == 0 && ram_return_status[i] == Status_OK);
    CHECK(physical_position[X_AXIS] == 240 && sys.position[X_AXIS] == 240);
    CHECK(axis_pulses[X_AXIS] == 240);
    CHECK(physical_position[Y_AXIS] == (int32_t)lroundf(y * settings.axis[Y_AXIS].steps_per_mm));
    CHECK(physical_position[Z_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(outer_modal_macro_calls == 1);
    CHECK(gc_state.g66_args == NULL && ngc_call_level() == 0);
    NEAR(gc_state.position[X_AXIS], 3);
    NEAR(gc_state.position[Y_AXIS], y);
}
