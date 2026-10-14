#include "support/spindle_ramp_host.h"
int main(void)
{
    spindle_ptrs_t *active = prepare_spindle_ramp();
    CHECK(spindle_set_state(active,(spindle_state_t){.on=true},6000));
    uint_fast16_t before = ramp_pwm_log[ramp_pwm_calls-1];
    ramp_pwm_calls = ramp_state_calls = 0;
    spindle_set_override(active,150);
    CHECK(ramp_pwm_calls == 0);
    CHECK(spindle_set_state(active,(spindle_state_t){0},0));
    CHECK(!ramp_hardware_state.on && ramp_pwm_calls > 0);
    fprintf(stderr,"PWM before stop=%u, first stop update=%u\n",(unsigned)before,(unsigned)ramp_pwm_log[0]);
    for(unsigned i = 0; i < ramp_pwm_calls; i++) CHECK(ramp_pwm_log[i] <= before);
    return EXIT_SUCCESS;
}
