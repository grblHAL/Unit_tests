#include "support/multi_spindle_host.h"
#include "check.h"

int main(void)
{
    prepare_multi_spindle_program();
    CHECK(spindle_enable(1) == 1);
    unsigned outputs[3];
    memcpy(outputs, spindle_output_calls, sizeof(outputs));
    state_set(STATE_CHECK_MODE);
    CHECK(spindle_program_block("M4S7000$1") == Status_OK);
    CHECK(memcmp(outputs, spindle_output_calls, sizeof(outputs)) == 0);
    CHECK(gc_state.modal.spindle[1].state.on && gc_state.modal.spindle[1].state.ccw);
    NEAR(gc_state.modal.spindle[1].rpm, 7000);
    return EXIT_SUCCESS;
}
