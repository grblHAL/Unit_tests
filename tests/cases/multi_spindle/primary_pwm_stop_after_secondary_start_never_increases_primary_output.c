#include "support/paired_pwm_program_host.h"
int main(void)
{
    prepare_paired_pwm_program();
    CHECK(spindle_program_block("M3S6000$0") == Status_OK);
    CHECK(spindle_program_block("M3S8000$1") == Status_OK);
    uint_fast16_t primary = pair_output[0], secondary = pair_output[1];
    pair_calls[0] = 0;
    CHECK(spindle_program_block("M5$0") == Status_OK);
    fprintf(stderr, "Primary PWM before stop=%u; first stop update=%u\n",
        (unsigned)primary, (unsigned)pair_log[0][0]);
    for(unsigned id = 0; id < pair_calls[0]; id++) CHECK(pair_log[0][id] <= primary);
    CHECK(!actual_spindle_states[0].on && actual_spindle_states[1].on);
    CHECK(pair_output[1] == secondary);
    return EXIT_SUCCESS;
}
