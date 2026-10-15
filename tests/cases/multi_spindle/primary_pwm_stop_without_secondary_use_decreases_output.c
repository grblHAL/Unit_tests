#include "support/paired_pwm_program_host.h"
int main(void)
{
    prepare_paired_pwm_program();
    CHECK(spindle_program_block("M3S6000$0") == Status_OK);
    uint_fast16_t before = pair_output[0];
    pair_calls[0] = 0;
    CHECK(spindle_program_block("M5$0") == Status_OK);
    CHECK(pair_calls[0] > 1);
    for(unsigned id = 0; id < pair_calls[0]; id++) CHECK(pair_log[0][id] <= before);
    CHECK(!actual_spindle_states[0].on && !actual_spindle_states[1].on);
    return EXIT_SUCCESS;
}
