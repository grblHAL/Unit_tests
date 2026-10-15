#include "support/multi_spindle_modal_host.h"
int main(void)
{
    prepare_multi_spindle_modal_program();
    start_two_modal_spindles();
    CHECK(spindle_program_block("M70") == Status_OK);
    unsigned primary_calls = spindle_output_calls[0], primary_updates = modal_rpm_update_calls[0];
    CHECK(spindle_program_block("M5$1") == Status_OK);
    CHECK(spindle_program_block("M72") == Status_OK);
    CHECK(spindle_output_calls[0] == primary_calls && modal_rpm_update_calls[0] == primary_updates);
    NEAR(actual_spindle_rpm[0], 3000); NEAR(actual_spindle_rpm[1], 7000);
    CHECK(actual_spindle_states[1].on && actual_spindle_states[1].ccw);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
