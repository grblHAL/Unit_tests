#include "support/paired_pwm_program_host.h"
int main(void)
{
    prepare_paired_pwm_program();
    CHECK(spindle_program_block("M3S6000$0") == Status_OK);
    CHECK(spindle_program_block("M3S8000$1") == Status_OK);
    uint_fast16_t before = pair_output[0];
    unsigned calls = pair_calls[0];
    CHECK(spindle_program_block("M5$1") == Status_OK);
    CHECK(actual_spindle_states[0].on && !actual_spindle_states[1].on);
    CHECK(pair_output[0] == before && pair_calls[0] == calls);
    return EXIT_SUCCESS;
}
