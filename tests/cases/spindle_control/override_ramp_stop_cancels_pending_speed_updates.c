#include "support/spindle_ramp_host.h"
int main(void)
{
    spindle_ptrs_t *active = prepare_spindle_ramp();
    CHECK(spindle_set_state(active,(spindle_state_t){.on=true},6000));
    clear_ramp_records();
    spindle_set_override(active,150);
    CHECK(ramp_pwm_calls == 0);
    CHECK(spindle_set_state(active,(spindle_state_t){0},0));
    CHECK(!ramp_hardware_state.on);
    unsigned updates = ramp_pwm_calls;
    advance_ramp_tasks(20);
    CHECK(ramp_pwm_calls == updates);
    CHECK(ramp_pwm_log[updates-1] == active->get_pwm(active,0));
    return EXIT_SUCCESS;
}
