#include "support/paired_pwm_override_host.h"
int main(void)
{
    prepare_paired_pwm_overrides();
    spindle_ptrs_t *primary = spindle_get(0), *secondary = spindle_get(1);
    CHECK(fabsf(spindle_set_override(primary, 120) - 7200) < .01f);
    float secondary_rpm = spindle_set_override(secondary, 80);
    CHECK(fabsf(secondary_rpm - 6400) < .01f);
    advance_pair_override_tasks(1);
    uint_fast16_t retarget_from = pair_output[0];
    unsigned first_retarget_update = pair_calls[0];
    float primary_rpm = spindle_set_override(primary, 80);
    CHECK(fabsf(primary_rpm - 4800) < .01f);
    CHECK(pair_calls[0] == first_retarget_update);
    advance_pair_override_tasks(10);
    CHECK(pair_output[0] == pair_get_pwm(primary, primary_rpm));
    CHECK(pair_output[1] == pair_get_pwm(secondary, secondary_rpm));
    for(unsigned i = first_retarget_update; i < pair_calls[0]; i++) {
        CHECK(pair_log[0][i] <= retarget_from);
        retarget_from = pair_log[0][i];
    }
    for(unsigned i = 1; i < pair_calls[1]; i++) CHECK(pair_log[1][i] <= pair_log[1][i - 1]);
    CHECK(primary->param->override_pct == 80 && secondary->param->override_pct == 80);
    CHECK(actual_spindle_states[0].on && actual_spindle_states[1].on);
    return EXIT_SUCCESS;
}
