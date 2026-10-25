#include "support/multi_spindle_host.h"
int main(void)
{
    prepare_multi_spindle_program();
    CHECK(spindle_get(1) == NULL);
    CHECK(!spindle_is_on());
    unsigned calls = spindle_output_calls[0];
    CHECK(spindle_program_block("M3S5000") == Status_OK);
    CHECK(actual_spindle_states[0].on);
    NEAR(actual_spindle_rpm[0], 5000);
    CHECK(spindle_is_on());
    CHECK(spindle_output_calls[0] == calls + 1);
    CHECK(spindle_program_block("M5") == Status_OK);
    CHECK(!actual_spindle_states[0].on && !spindle_is_on());
    CHECK(spindle_output_calls[0] == calls + 2);
    CHECK(spindle_output_calls[1] == 0 && spindle_output_calls[2] == 0);
    CHECK(spindle_get(1) == NULL && plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
