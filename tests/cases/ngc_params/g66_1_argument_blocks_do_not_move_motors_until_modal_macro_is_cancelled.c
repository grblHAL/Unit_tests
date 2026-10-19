#include "support/macro_parser_host.h"
#include "support/canned_motion_host.h"
int main(void)
{
    prepare_canned_motion();
    grbl.on_macro_execute = capture_macro;
    CHECK(ngc_param_set(24, 99));
    CHECK(macro_block("G66.1P100X12Y8") == Status_OK);
    CHECK(macro_calls == 1);
    CHECK(macro_block("X20") == Status_OK);
    CHECK(macro_calls == 2);
    NEAR(macro_x, 20); NEAR(macro_y, 8);
    CHECK(plan_get_current_block() == NULL && ngc_call_level() == 0);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        CHECK(axis_pulses[axis] == 0 && physical_position[axis] == 0);
    CHECK(macro_block("G67") == Status_OK && gc_state.g66_args == NULL);
    CHECK(macro_block("G1X1F100") == Status_OK);
    CHECK(protocol_buffer_synchronize());
    CHECK(macro_calls == 2 && physical_position[X_AXIS] == 80);
    CHECK(axis_pulses[X_AXIS] == 80 && axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    float caller;
    CHECK(ngc_param_get(24, &caller));
    NEAR(caller, 99);
    return EXIT_SUCCESS;
}
