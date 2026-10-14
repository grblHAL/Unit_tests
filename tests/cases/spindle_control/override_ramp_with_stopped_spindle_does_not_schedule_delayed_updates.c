#include "support/spindle_ramp_host.h"
int main(void)
{
    spindle_ptrs_t *active = prepare_spindle_ramp();
    CHECK(!ramp_hardware_state.on);
    clear_ramp_records();
    spindle_set_override(active,150);
    CHECK(ramp_pwm_calls == 1);
    advance_ramp_tasks(20);
    CHECK(ramp_pwm_calls == 1);
    CHECK(ramp_pwm_log[0] == active->get_pwm(active,0) && !ramp_hardware_state.on);
    return EXIT_SUCCESS;
}
