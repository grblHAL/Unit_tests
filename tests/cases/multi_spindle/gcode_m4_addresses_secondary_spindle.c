#include "support/multi_spindle_host.h"
#include "check.h"

int main(void)
{
    prepare_multi_spindle_program();
    CHECK(spindle_enable(1) == 1);
    unsigned primary_outputs = spindle_output_calls[0];
    CHECK(spindle_program_block("M4S7000$1") == Status_OK);
    CHECK(actual_spindle_states[1].on && actual_spindle_states[1].ccw);
    NEAR(actual_spindle_rpm[1], 7000);
    CHECK(!actual_spindle_states[0].on && spindle_output_calls[0] == primary_outputs);
    return EXIT_SUCCESS;
}
