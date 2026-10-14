#include "support/spindle_ramp_host.h"
int main(void)
{
    spindle_ptrs_t *active = prepare_spindle_ramp();
    CHECK(spindle_set_state(active,(spindle_state_t){.on=true},6000));
    clear_ramp_records();
    NEAR(spindle_set_override(active,150),9000);
    CHECK(ramp_pwm_calls == 0);
    engine_ticks = DWELL_TIME_STEP - 1;
    engine_execute_tasks(STATE_IDLE);
    CHECK(ramp_pwm_calls == 0);
    engine_ticks = DWELL_TIME_STEP;
    engine_execute_tasks(STATE_IDLE);
    CHECK(ramp_pwm_calls == 1);
    CHECK(ramp_pwm_log[0] > active->get_pwm(active,6000) && ramp_pwm_log[0] < active->get_pwm(active,9000));
    advance_ramp_tasks(20);
    CHECK(ramp_pwm_log[ramp_pwm_calls-1] == active->get_pwm(active,9000));
    unsigned updates = ramp_pwm_calls;
    advance_ramp_tasks(10);
    CHECK(ramp_pwm_calls == updates);
    return EXIT_SUCCESS;
}
