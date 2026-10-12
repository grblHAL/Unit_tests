#include "support/multi_spindle_host.h"
#include "check.h"

int main(void)
{
    prepare_multi_spindle_program();
    CHECK(spindle_program_block("M3S5000") == Status_OK);
    CHECK(actual_spindle_states[0].on && !actual_spindle_states[0].ccw);
    NEAR(actual_spindle_rpm[0], 5000);
    CHECK(spindle_output_calls[1] == 0);
    return EXIT_SUCCESS;
}
