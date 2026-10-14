#include "support/spindle_ramp_host.h"
int main(void)
{
    spindle_ptrs_t *active = prepare_spindle_ramp();
    CHECK(spindle_set_state(active,(spindle_state_t){.on=true},6000));
    clear_ramp_records();
    NEAR(spindle_set_override(active,100),6000);
    advance_ramp_tasks(20);
    CHECK(ramp_pwm_calls == 0 && ramp_state_calls == 0);
    return EXIT_SUCCESS;
}
