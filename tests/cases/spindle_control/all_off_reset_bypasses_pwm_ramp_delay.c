#include "support/spindle_ramp_host.h"

int main(void)
{
    spindle_ptrs_t *active = prepare_spindle_ramp();
    CHECK(spindle_set_state(active, (spindle_state_t){.on = true}, 6000));
    clear_ramp_records();
    spindle_all_off(true);
    CHECK(!ramp_hardware_state.on && ramp_state_calls == 1);
    CHECK(engine_ticks == 0 && ramp_pwm_calls == 0);
    CHECK(ramp_initial_rpm == 0);
    CHECK(active->param->rpm == 0 && active->param->rpm_overridden == 0);
    CHECK(!active->param->state.on && !active->param->option.restore_rpm);
    return EXIT_SUCCESS;
}
