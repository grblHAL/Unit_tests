#include "support/spindle_ramp_host.h"
int main(void)
{
    spindle_ptrs_t *active = prepare_spindle_ramp();
    settings.spindle.on_delay = DWELL_TIME_STEP;
    CHECK(spindle_set_state(active,(spindle_state_t){.on=true},6000));
    CHECK(ramp_state_calls == 1 && ramp_pwm_calls == 0);
    NEAR(ramp_initial_rpm,6000);
    CHECK(engine_ticks == 0 && ramp_hardware_state.on);
    return EXIT_SUCCESS;
}
