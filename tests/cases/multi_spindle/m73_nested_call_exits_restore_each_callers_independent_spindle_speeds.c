#include "support/multi_spindle_modal_host.h"
int main(void)
{
    prepare_multi_spindle_modal_program();
    start_two_modal_spindles();
    int outer, inner;
    CHECK(ngc_call_push(&outer));
    CHECK(spindle_program_block("M73") == Status_OK);
    CHECK(spindle_program_block("S5000$0") == Status_OK);
    CHECK(spindle_program_block("S9000$1") == Status_OK);
    CHECK(ngc_call_push(&inner));
    CHECK(spindle_program_block("M73") == Status_OK);
    CHECK(spindle_program_block("M5$-1") == Status_OK);
    (void)ngc_call_pop();
    CHECK(ngc_call_level() == 1);
    CHECK(actual_spindle_states[0].on && actual_spindle_states[1].on);
    NEAR(actual_spindle_rpm[0], 5000); NEAR(actual_spindle_rpm[1], 9000);
    (void)ngc_call_pop();
    CHECK(ngc_call_level() == 0);
    NEAR(actual_spindle_rpm[0], 3000); NEAR(actual_spindle_rpm[1], 7000);
    CHECK(ngc_modal_state_get() == NULL);
    return EXIT_SUCCESS;
}
