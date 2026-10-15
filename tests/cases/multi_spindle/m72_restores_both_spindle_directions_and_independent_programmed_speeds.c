#include "support/multi_spindle_modal_host.h"
int main(void)
{
    prepare_multi_spindle_modal_program();
    start_two_modal_spindles();
    CHECK(spindle_program_block("M70") == Status_OK);
    CHECK(spindle_program_block("M5$-1") == Status_OK);
    CHECK(!actual_spindle_states[0].on && !actual_spindle_states[1].on);
    CHECK(spindle_program_block("M72") == Status_OK);
    CHECK(actual_spindle_states[0].on && !actual_spindle_states[0].ccw);
    CHECK(actual_spindle_states[1].on && actual_spindle_states[1].ccw);
    NEAR(actual_spindle_rpm[0], 3000); NEAR(actual_spindle_rpm[1], 7000);
    NEAR(gc_state.modal.spindle[0].rpm, 3000); NEAR(gc_state.modal.spindle[1].rpm, 7000);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
