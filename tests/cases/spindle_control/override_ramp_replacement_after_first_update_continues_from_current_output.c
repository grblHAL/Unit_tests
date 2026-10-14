#include "support/spindle_ramp_host.h"
int main(void)
{
    spindle_ptrs_t *active = prepare_spindle_ramp();
    CHECK(spindle_set_state(active,(spindle_state_t){.on=true},6000));
    clear_ramp_records();
    spindle_set_override(active,150);
    advance_ramp_tasks(1);
    CHECK(ramp_pwm_calls == 1);
    uint_fast16_t previous = ramp_pwm_log[0];
    spindle_set_override(active,50);
    advance_ramp_tasks(20);
    CHECK(ramp_pwm_log[1] < previous);
    for(unsigned i = 2;
    i < ramp_pwm_calls;
    i++) CHECK(ramp_pwm_log[i] <= ramp_pwm_log[i-1]);
    CHECK(ramp_pwm_log[ramp_pwm_calls-1] == active->get_pwm(active,3000));
    return EXIT_SUCCESS;
}
