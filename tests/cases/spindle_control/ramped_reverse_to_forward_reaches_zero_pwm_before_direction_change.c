#include "support/spindle_ramp_host.h"
int main(void)
{
    spindle_ptrs_t *active = prepare_spindle_ramp();
    active->cap.direction = true;
    CHECK(spindle_set_state(active,(spindle_state_t){.on=true,.ccw=true},6000));
    clear_ramp_records();
    CHECK(spindle_set_state(active,(spindle_state_t){.on=true},4000));
    CHECK(ramp_hardware_state.on && !ramp_hardware_state.ccw && ramp_state_calls == 1);
    CHECK(!ramp_state_log[0].ccw && ramp_pwm_calls > 2);
    CHECK(ramp_pwm_log[ramp_pwm_calls-1] == active->get_pwm(active,4000));
    return EXIT_SUCCESS;
}
