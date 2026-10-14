#include "support/spindle_ramp_host.h"
int main(void)
{
    spindle_ptrs_t *active = prepare_spindle_ramp();
    CHECK(spindle_set_state(active,(spindle_state_t){.on=true},6000));
    clear_ramp_records();
    CHECK(spindle_set_state(active,(spindle_state_t){0},0));
    CHECK(!ramp_hardware_state.on && ramp_state_calls == 1 && ramp_pwm_calls > 1);
    for(unsigned i = 1;
    i < ramp_pwm_calls;
    i++) CHECK(ramp_pwm_log[i] <= ramp_pwm_log[i-1]);
    CHECK(ramp_pwm_log[ramp_pwm_calls-1] == active->get_pwm(active,0));
    NEAR(active->param->rpm_overridden,0);
    CHECK(engine_ticks > 0);
    return EXIT_SUCCESS;
}
