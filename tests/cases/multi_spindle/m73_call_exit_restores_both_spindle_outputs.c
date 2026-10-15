#include "support/multi_spindle_modal_host.h"
int main(void)
{
    prepare_multi_spindle_modal_program();
    start_two_modal_spindles();
    int context;
    CHECK(ngc_call_push(&context));
    CHECK(spindle_program_block("M73") == Status_OK);
    CHECK(spindle_program_block("M5$-1") == Status_OK);
    (void)ngc_call_pop();
    CHECK(ngc_call_level() == 0);
    CHECK(actual_spindle_states[0].on && !actual_spindle_states[0].ccw);
    CHECK(actual_spindle_states[1].on && actual_spindle_states[1].ccw);
    NEAR(actual_spindle_rpm[0], 3000); NEAR(actual_spindle_rpm[1], 7000);
    CHECK(ngc_modal_state_get() == NULL);
    return EXIT_SUCCESS;
}
