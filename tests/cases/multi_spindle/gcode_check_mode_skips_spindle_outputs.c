#include "support/multi_spindle_host.h"
#include "check.h"

int main(void)
{
    prepare_multi_spindle_program();
    CHECK(spindle_enable(1) == 1);
    unsigned primary_outputs = spindle_output_calls[0], secondary_outputs = spindle_output_calls[1];
    CHECK(!actual_spindle_states[0].on && !actual_spindle_states[1].on);
    state_set(STATE_CHECK_MODE);
    CHECK(spindle_program_block("M4S7000$1") == Status_OK);
    CHECK(spindle_output_calls[0] == primary_outputs && spindle_output_calls[1] == secondary_outputs);
    CHECK(!actual_spindle_states[0].on && !actual_spindle_states[1].on);
    NEAR(actual_spindle_rpm[0], 0);
    NEAR(actual_spindle_rpm[1], 0);
    CHECK(gc_state.modal.spindle[1].state.on && gc_state.modal.spindle[1].state.ccw);
    NEAR(gc_state.modal.spindle[1].rpm, 7000);
    return EXIT_SUCCESS;
}
