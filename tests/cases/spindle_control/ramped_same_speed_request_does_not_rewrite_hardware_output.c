#include "support/spindle_ramp_host.h"
int main(void)
{
    spindle_ptrs_t *active = prepare_spindle_ramp();
    CHECK(spindle_set_state(active,(spindle_state_t){.on=true},6000));
    clear_ramp_records();
    CHECK(spindle_set_state(active,(spindle_state_t){.on=true},6000));
    CHECK(ramp_state_calls == 0 && ramp_pwm_calls == 0 && engine_ticks == 0);
    CHECK(ramp_hardware_state.on);
    NEAR(active->param->rpm_overridden,6000);
    return EXIT_SUCCESS;
}
