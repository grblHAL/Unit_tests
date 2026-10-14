#include "support/spindle_ramp_host.h"
int main(void)
{
    spindle_ptrs_t *active = prepare_spindle_ramp();
    CHECK(spindle_set_state(active,(spindle_state_t){.on=true},8000));
    clear_ramp_records();
    CHECK(spindle_set_state(active,(spindle_state_t){.on=true},2000));
    CHECK(ramp_hardware_state.on && ramp_state_calls == 0 && ramp_pwm_calls > 1);
    for(unsigned i = 1;
    i < ramp_pwm_calls;
    i++) CHECK(ramp_pwm_log[i] <= ramp_pwm_log[i-1]);
    CHECK(ramp_pwm_log[ramp_pwm_calls-1] == active->get_pwm(active,2000));
    return EXIT_SUCCESS;
}
