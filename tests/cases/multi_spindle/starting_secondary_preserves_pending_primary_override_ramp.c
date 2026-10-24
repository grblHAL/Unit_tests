#include "support/paired_pwm_override_host.h"

int main(void)
{
    prepare_paired_pwm_program();
    CHECK(spindle_program_block("M3S6000$0") == Status_OK);
    spindle_ptrs_t *primary = spindle_get(0), *secondary = spindle_get(1);
    float requested = spindle_set_override(primary, 120);
    uint_fast16_t target = pair_get_pwm(primary, requested);
    advance_pair_override_tasks(1);
    uint_fast16_t before_secondary = pair_output[0];
    CHECK(before_secondary > pair_get_pwm(primary, 6000) && before_secondary < target);
    CHECK(spindle_program_block("M3S8000$1") == Status_OK);
    CHECK(actual_spindle_states[0].on && actual_spindle_states[1].on);
    CHECK(pair_output[1] == pair_get_pwm(secondary, 8000));
    advance_pair_override_tasks(10);
    uint_fast16_t completed_primary = pair_output[0];
    CHECK(primary->param->override_pct == 120);
    CHECK(fabsf(primary->param->rpm_overridden - requested) < .01f);
    fprintf(stderr, "Primary override across secondary start: before=%u after=%u target=%u\n",
        (unsigned)before_secondary, (unsigned)completed_primary, (unsigned)target);
    float retry = spindle_set_override(primary, 125);
    advance_pair_override_tasks(10);
    CHECK(pair_output[0] == pair_get_pwm(primary, retry));
    CHECK(pair_output[1] == pair_get_pwm(secondary, 8000));
    CHECK(actual_spindle_states[0].on && actual_spindle_states[1].on);
    CHECK(completed_primary == target);
    return EXIT_SUCCESS;
}
