#include "support/multi_spindle_program_end_host.h"
int main(void)
{
    prepare_multi_spindle_program_end(true);
    CHECK(spindle_program_block("M2") == Status_OK);
    check_multi_spindle_program_end(true, ProgramFlow_CompletedM2);
    CHECK(spindle_program_block("M3S4000$0") == Status_OK);
    CHECK(spindle_program_block("M3S6000$1") == Status_OK);
    NEAR(actual_spindle_rpm[0], 4000);
    NEAR(actual_spindle_rpm[1], 6000);
    CHECK(actual_spindle_states[0].on && actual_spindle_states[1].on);
    return EXIT_SUCCESS;
}
