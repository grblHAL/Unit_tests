#include "support/spindle_ramp_host.h"
int main(void)
{
    spindle_ptrs_t *active = prepare_spindle_ramp();
    CHECK(spindle_set_state(active,(spindle_state_t){.on=true},6000));
    clear_ramp_records();
    settings.spindle.off_delay = DWELL_TIME_STEP;
    CHECK(spindle_set_state(active,(spindle_state_t){0},0));
    CHECK(ramp_pwm_calls == 1 && ramp_pwm_log[0] == active->get_pwm(active,0));
    CHECK(ramp_state_calls == 1 && !ramp_hardware_state.on && engine_ticks == 0);
    return EXIT_SUCCESS;
}
