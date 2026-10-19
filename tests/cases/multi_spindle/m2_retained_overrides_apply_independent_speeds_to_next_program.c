#include "support/multi_spindle_program_end_host.h"
int main(void)
{
    prepare_multi_spindle_program_end(false);
    CHECK(spindle_program_block("M2") == Status_OK);
    check_multi_spindle_program_end(false, ProgramFlow_CompletedM2);
    CHECK(spindle_program_block("M3S4000$0") == Status_OK);
    CHECK(spindle_program_block("M3S6000$1") == Status_OK);
    CHECK(fabsf(actual_spindle_rpm[0] - 4400.0f) < 0.01f);
    CHECK(fabsf(actual_spindle_rpm[1] - 7200.0f) < 0.01f);
    CHECK(actual_spindle_states[0].on && actual_spindle_states[1].on);
    return EXIT_SUCCESS;
}
