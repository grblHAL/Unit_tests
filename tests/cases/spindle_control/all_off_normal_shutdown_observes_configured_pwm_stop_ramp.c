#include "support/spindle_ramp_host.h"

int main(void)
{
    spindle_ptrs_t *active = prepare_spindle_ramp();
    CHECK(spindle_set_state(active, (spindle_state_t){.on = true}, 6000));
    clear_ramp_records();
    spindle_all_off(false);
    CHECK(!ramp_hardware_state.on && ramp_pwm_calls > 1);
    for(unsigned i = 1; i < ramp_pwm_calls; i++)
        CHECK(ramp_pwm_log[i] <= ramp_pwm_log[i - 1]);
    CHECK(ramp_pwm_log[ramp_pwm_calls - 1] == active->get_pwm(active, 0));
    CHECK(engine_ticks > 0);
    CHECK(active->param->rpm == 0 && active->param->rpm_overridden == 0);
    CHECK(!active->param->state.on && !active->param->option.restore_rpm);
    return EXIT_SUCCESS;
}
