#include "support/paired_pwm_override_host.h"
int main(void)
{
    prepare_paired_pwm_overrides();
    spindle_ptrs_t *primary = spindle_get(0), *secondary = spindle_get(1);
    CHECK(fabsf(spindle_set_override(primary, 120) - 7200) < .01f);
    float secondary_rpm = spindle_set_override(secondary, 80);
    CHECK(fabsf(secondary_rpm - 6400) < .01f);
    advance_pair_override_tasks(1);
    uint_fast16_t before_stop = pair_output[0];
    pair_calls[0] = 0;
    CHECK(spindle_program_block("M5$0") == Status_OK);
    CHECK(!actual_spindle_states[0].on && actual_spindle_states[1].on);
    CHECK(pair_output[0] == pair_get_pwm(primary, 0));
    for(unsigned i = 0; i < pair_calls[0]; i++) CHECK(pair_log[0][i] <= before_stop);
    advance_pair_override_tasks(10);
    CHECK(pair_output[0] == pair_get_pwm(primary, 0));
    CHECK(pair_output[1] == pair_get_pwm(secondary, secondary_rpm));
    CHECK(secondary->param->override_pct == 80 && actual_spindle_states[1].on);
    return EXIT_SUCCESS;
}
