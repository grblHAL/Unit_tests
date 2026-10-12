#include "support/multi_spindle_host.h"
#include "check.h"

int main(void)
{
    prepare_multi_spindle_program();
    CHECK(spindle_enable(1) == 1);
    CHECK(spindle_program_block("M3S5000") == Status_OK);
    CHECK(spindle_program_block("M3S7000$1") == Status_OK);
    CHECK(spindle_program_block("M5$1") == Status_OK);
    CHECK(actual_spindle_states[0].on && !actual_spindle_states[1].on);
    NEAR(actual_spindle_rpm[0], 5000);
    CHECK(actual_spindle_rpm[1] == 0);
    return EXIT_SUCCESS;
}
