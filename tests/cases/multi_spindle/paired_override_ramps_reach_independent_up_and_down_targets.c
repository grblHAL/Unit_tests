#include "support/paired_pwm_override_host.h"
int main(void)
{
    prepare_paired_pwm_overrides();
    spindle_ptrs_t *primary = spindle_get(0), *secondary = spindle_get(1);
    uint_fast16_t initial[2] = {pair_output[0], pair_output[1]};
    float primary_rpm = spindle_set_override(primary, 120);
    float secondary_rpm = spindle_set_override(secondary, 80);
    CHECK(fabsf(primary_rpm - 7200) < .01f);
    CHECK(fabsf(secondary_rpm - 6400) < .01f);
    /* PWM quantizes the accepted float RPM, which may sit just below an integer. */
    uint_fast16_t target[2] = {pair_get_pwm(primary, primary_rpm), pair_get_pwm(secondary, secondary_rpm)};
    CHECK(pair_calls[0] == 0 && pair_calls[1] == 0);
    advance_pair_override_tasks(1);
    CHECK(pair_output[0] > initial[0] && pair_output[0] < target[0]);
    CHECK(pair_output[1] < initial[1] && pair_output[1] > target[1]);
    advance_pair_override_tasks(10);
    CHECK(pair_output[0] == target[0] && pair_output[1] == target[1]);
    for(unsigned i = 1; i < pair_calls[0]; i++) CHECK(pair_log[0][i] >= pair_log[0][i - 1]);
    for(unsigned i = 1; i < pair_calls[1]; i++) CHECK(pair_log[1][i] <= pair_log[1][i - 1]);
    CHECK(primary->param->override_pct == 120 && secondary->param->override_pct == 80);
    CHECK(actual_spindle_states[0].on && actual_spindle_states[1].on);
    unsigned completed[2] = {pair_calls[0], pair_calls[1]};
    advance_pair_override_tasks(10);
    CHECK(pair_calls[0] == completed[0] && pair_calls[1] == completed[1]);
    return EXIT_SUCCESS;
}
