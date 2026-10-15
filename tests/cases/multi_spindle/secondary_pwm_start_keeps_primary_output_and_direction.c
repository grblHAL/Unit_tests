#include "support/paired_pwm_program_host.h"
int main(void)
{
    prepare_paired_pwm_program();
    CHECK(spindle_program_block("M3S6000$0") == Status_OK);
    uint_fast16_t primary = pair_output[0];
    unsigned primary_calls = pair_calls[0];
    CHECK(spindle_program_block("M4S8000$1") == Status_OK);
    CHECK(pair_output[0] == primary && pair_calls[0] == primary_calls);
    CHECK(actual_spindle_states[0].on && !actual_spindle_states[0].ccw);
    CHECK(actual_spindle_states[1].on && actual_spindle_states[1].ccw);
    CHECK(pair_output[1] == pair_get_pwm(spindle_get(1), 8000));
    return EXIT_SUCCESS;
}
